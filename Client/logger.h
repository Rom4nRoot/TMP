/**
 * @file logger.h
 * @brief Заголовочный файл класса логгера
 * @date 2024
 * 
 * @details
 * Класс Logger реализует функциональность логирования событий
 * в файл и консоль.
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

/**
 * @class Logger
 * @brief Класс для логирования событий
 * 
 * @details
 * Класс обеспечивает:
 * 1. Запись логов в файл
 * 2. Вывод логов в консоль
 * 3. Форматирование сообщений
 * 4. Уровни логирования
 */
class Logger : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класса
     * @param parent Родительский объект Qt
     */
    explicit Logger(QObject *parent = nullptr);

    /**
     * @brief Деструктор класса
     */
    ~Logger();

    /**
     * @brief Инициализация логгера
     * @param filename Имя файла для записи логов
     * @return true если инициализация успешна
     */
    bool init(const QString& filename);

    /**
     * @brief Запись информационного сообщения
     * @param message Текст сообщения
     */
    void info(const QString& message);

    /**
     * @brief Запись предупреждения
     * @param message Текст предупреждения
     */
    void warning(const QString& message);

    /**
     * @brief Запись ошибки
     * @param message Текст ошибки
     */
    void error(const QString& message);

private:
    QFile logFile;           ///< Файл для записи логов
    QTextStream logStream;   ///< Поток для записи в файл
    bool isInitialized;      ///< Флаг инициализации

    /**
     * @brief Запись сообщения в лог
     * @param level Уровень сообщения
     * @param message Текст сообщения
     */
    void log(const QString& level, const QString& message);
};

#endif // LOGGER_H 