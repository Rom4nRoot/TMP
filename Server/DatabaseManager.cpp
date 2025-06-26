/**
 * @file DatabaseManager.cpp
 * @brief Реализация класса управления базой данных
 * @author Roman
 * @date 2024
 * 
 * @details
 * Реализует методы класса DatabaseManager для работы с базой данных,
 * включая аутентификацию пользователей и управление статистикой.
 */

#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCryptographicHash>

DatabaseManager* DatabaseManager::instance = nullptr;
QMutex DatabaseManager::mutex;

DatabaseManager* DatabaseManager::getInstance()
{
    QMutexLocker locker(&mutex);
    if (!instance) {
        instance = new DatabaseManager();
    }
    return instance;
}

void DatabaseManager::destroyInstance()
{
    QMutexLocker locker(&mutex);
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("server.db");
    
    if (!db.open()) {
        qDebug() << "Error: Failed to connect database:" << db.lastError().text();
        return;
    }

    if (!initializeDatabase()) {
        qDebug() << "Error: Failed to initialize database";
        db.close();
    }
}

DatabaseManager::~DatabaseManager()
{
    if (db.isOpen()) {
        db.close();
    }
}

bool DatabaseManager::initializeDatabase()
{
    return createTables();
}

bool DatabaseManager::createTables()
{
    QSqlQuery query;
    
    // Создаем таблицу пользователей
    if (!query.exec("CREATE TABLE IF NOT EXISTS users ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "username TEXT UNIQUE NOT NULL,"
                   "password_hash TEXT NOT NULL)")) {
        qDebug() << "Error creating users table:" << query.lastError().text();
        return false;
    }
    
    // Создаем таблицу статистики
    if (!query.exec("CREATE TABLE IF NOT EXISTS task_statistics ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "user_id INTEGER NOT NULL,"
                   "task_id INTEGER NOT NULL,"
                   "success_count INTEGER DEFAULT 0,"
                   "failure_count INTEGER DEFAULT 0,"
                   "FOREIGN KEY (user_id) REFERENCES users(id),"
                   "UNIQUE(user_id, task_id))")) {
        qDebug() << "Error creating task_statistics table:" << query.lastError().text();
        return false;
    }
    
    return true;
}

int DatabaseManager::authenticateUser(const QString& username, const QString& password)
{
    QMutexLocker locker(&mutex);
    QSqlQuery query;
    
    // Получаем хеш пароля из базы
    query.prepare("SELECT id, password_hash FROM users WHERE username = ?");
    query.addBindValue(username);
    
    if (!query.exec()) {
        qDebug() << "Error querying user:" << query.lastError().text();
        return -1;
    }
    
    if (query.next()) {
        int userId = query.value(0).toInt();
        QString storedHash = query.value(1).toString();
        
        // Проверяем хеш пароля
        QString inputHash = QCryptographicHash::hash(
            password.toUtf8(),
            QCryptographicHash::Sha1
        ).toHex();
        
        if (inputHash == storedHash) {
        return userId;
        }
    }
    
    return -1;
}

void DatabaseManager::updateTaskStatistics(int userId, int taskId, bool success)
{
    QMutexLocker locker(&mutex);
    QSqlQuery query;
    
    // Обновляем статистику
    if (success) {
        query.prepare("INSERT INTO task_statistics (user_id, task_id, success_count) "
                     "VALUES (?, ?, 1) "
                     "ON CONFLICT(user_id, task_id) "
                     "DO UPDATE SET success_count = success_count + 1");
    } else {
        query.prepare("INSERT INTO task_statistics (user_id, task_id, failure_count) "
                     "VALUES (?, ?, 1) "
                     "ON CONFLICT(user_id, task_id) "
                     "DO UPDATE SET failure_count = failure_count + 1");
    }
    
    query.addBindValue(userId);
    query.addBindValue(taskId);
    
    if (!query.exec()) {
        qDebug() << "Error updating statistics:" << query.lastError().text();
    }
}

QJsonObject DatabaseManager::getUserStatistics(int userId)
{
    QMutexLocker locker(&mutex);
    QSqlQuery query;
    QJsonObject statistics;
    
    query.prepare("SELECT task_id, success_count, failure_count "
                 "FROM task_statistics WHERE user_id = ?");
    query.addBindValue(userId);
    
    if (!query.exec()) {
        qDebug() << "Error getting statistics:" << query.lastError().text();
        return statistics;
    }

        while (query.next()) {
        int taskId = query.value(0).toInt();
        int successCount = query.value(1).toInt();
        int failureCount = query.value(2).toInt();
        
        QJsonObject taskStats;
        taskStats["success_count"] = successCount;
        taskStats["failure_count"] = failureCount;
        taskStats["total_count"] = successCount + failureCount;
        
        statistics[QString::number(taskId)] = taskStats;
    }
    
    return statistics;
}