/**
 * @file DatabaseManager.h
 * @brief Заголовочный файл класса управления базой данных
 * @date 2024
 * 
 * @details
 * Класс DatabaseManager реализует:
 * 1. Синглтон для доступа к базе данных
 * 2. Управление пользователями
 * 3. Хранение статистики выполнения задач
 * 4. Потокобезопасный доступ к данным
 */

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QString>
#include <QMap>
#include <QPair>
#include <QDebug>
#include <QCryptographicHash>
#include <QJsonObject>
#include <QMutex>

/**
 * @class DatabaseManager
 * @brief Класс управления базой данных
 * 
 * @details
 * Класс реализует паттерн Singleton для обеспечения единой точки
 * доступа к базе данных. Использует мьютекс для обеспечения
 * потокобезопасности при работе с базой данных.
 */
class DatabaseManager : public QObject
{
    Q_OBJECT

private:
    static DatabaseManager* instance;
    static QMutex mutex;
    QSqlDatabase db;
    
    /**
     * @brief Конструктор класса
     * @param parent Родительский объект Qt
     * 
     * @details
     * Приватный конструктор для реализации паттерна Singleton.
     * Инициализирует соединение с базой данных.
     */
    DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();
    
    // Запрет копирования
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

public:
    /**
     * @brief Получает единственный экземпляр DatabaseManager
     * @return Указатель на экземпляр DatabaseManager
     * 
     * @details
     * Создает экземпляр класса, если он еще не существует,
     * и возвращает указатель на него.
     */
    static DatabaseManager* getInstance();

    /**
     * @brief Уничтожает экземпляр DatabaseManager
     * 
     * @details
     * Закрывает соединение с базой данных и освобождает
     * ресурсы экземпляра.
     */
    static void destroyInstance();
    
    /**
     * @brief Инициализация базы данных
     * @return true если инициализация успешна
     * 
     * @details
     * Создает необходимые таблицы и индексы в базе данных.
     */
    bool initializeDatabase();
    
    // Работа с пользователями
    bool registerUser(const QString& login, const QString& password);
    /**
     * @brief Проверяет учетные данные пользователя
     * @param username Имя пользователя
     * @param password Пароль
     * @return ID пользователя или -1 если аутентификация не удалась
     * 
     * @details
     * Проверяет хеш пароля и возвращает ID пользователя
     * при успешной аутентификации.
     */
    int authenticateUser(const QString& username, const QString& password);
    bool setUserSocketId(int userId, quintptr socketId);
    bool setUserOffline(int userId);
    bool isUserOnline(int userId);
    
    // Работа со статистикой
    /**
     * @brief Обновляет статистику выполнения задачи
     * @param userId ID пользователя
     * @param taskId ID задачи
     * @param success Результат выполнения
     * 
     * @details
     * Обновляет счетчики успешных и неуспешных попыток
     * выполнения задачи для пользователя.
     */
    void updateTaskStatistics(int userId, int taskId, bool success);
    QMap<QString, QPair<int, int>> getUserStats(int userId);
    /**
     * @brief Получает статистику пользователя
     * @param userId ID пользователя
     * @return JSON объект со статистикой
     * 
     * @details
     * Возвращает статистику выполнения всех задач
     * для указанного пользователя в формате JSON.
     */
    QJsonObject getUserStatistics(int userId);
    
private:
    QString hashPassword(const QString& password);
    /**
     * @brief Создает необходимые таблицы
     * @return true если таблицы созданы успешно
     * 
     * @details
     * Создает таблицы users и task_statistics, если они
     * еще не существуют.
     */
    bool createTables();
};

#endif // DATABASEMANAGER_H