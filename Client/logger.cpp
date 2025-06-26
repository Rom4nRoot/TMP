/**
 * @file logger.cpp
 * @brief Реализация класса логгера
 * @date 2024
 * 
 * @details
 * Реализует методы класса Logger для записи логов
 * в файл и консоль.
 */

#include "logger.h"
#include <QDir>
#include <QDateTime>

Logger::Logger(QObject *parent)
    : QObject(parent)
    , isInitialized(false)
{
}

Logger::~Logger()
{
    if (logFile.isOpen()) {
        logFile.close();
    }
}

bool Logger::init(const QString& filename)
{
    // Создаем директорию для логов, если она не существует
    QDir dir;
    if (!dir.exists("logs")) {
        dir.mkdir("logs");
    }

    // Открываем файл для записи
    logFile.setFileName("logs/" + filename);
    if (!logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        return false;
    }

    logStream.setDevice(&logFile);
    isInitialized = true;
    return true;
}

void Logger::info(const QString& message)
{
    log("INFO", message);
}

void Logger::warning(const QString& message)
{
    log("WARNING", message);
}

void Logger::error(const QString& message)
{
    log("ERROR", message);
}

void Logger::log(const QString& level, const QString& message)
{
    if (!isInitialized) {
        return;
    }

    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString logMessage = QString("[%1] [%2] %3\n")
        .arg(timestamp)
        .arg(level)
        .arg(message);

    // Записываем в файл
    logStream << logMessage;
    logStream.flush();

    // Выводим в консоль
    qDebug().noquote() << logMessage;
} 