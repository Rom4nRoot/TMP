/**
 * @file ClientHandler.h
 * @brief Заголовочный файл класса обработчика клиентских соединений
 * @author Roman
 * @date 2024
 * 
 * @details
 * Класс ClientHandler отвечает за:
 * 1. Обработку входящих сообщений от клиента
 * 2. Выполнение запрошенных операций
 * 3. Отправку ответов клиенту
 * 4. Управление состоянием клиентского соединения
 * 
 * @see MyTcpServer
 * @see DatabaseManager
 */

#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include "DatabaseManager.h"

/**
 * @class ClientHandler
 * @brief Класс обработчика клиентских соединений
 * 
 * @details
 * Класс наследуется от QObject и обрабатывает все взаимодействия
 * с конкретным клиентом. Он отвечает за аутентификацию, выполнение
 * задач и отправку результатов.
 */
class ClientHandler : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класса
     * @param socket Сокет клиентского соединения
     * @param parent Родительский объект Qt
     */
    explicit ClientHandler(QTcpSocket* socket, QObject *parent = nullptr);

    /**
     * @brief Деструктор класса
     * 
     * @details
     * Закрывает соединение и освобождает ресурсы
     */
    ~ClientHandler();
    
    quintptr getSocketId() const { return socketId; }
    int getUserId() const { return userId; }
    bool isAuthenticated() const { return userId != -1; }
    
signals:
    /**
     * @brief Сигнал отключения клиента
     * @param socketId Идентификатор сокета отключившегося клиента
     */
    void clientDisconnected(quintptr socketId);

    /**
     * @brief Сигнал ошибки клиента
     * @param socketId Идентификатор сокета клиента
     * @param error Сообщение об ошибке
     */
    void clientError(quintptr socketId, const QString& error);

private slots:
    /**
     * @brief Обработчик входящих данных от клиента
     * 
     * @details
     * Читает данные из сокета, парсит JSON сообщение и
     * вызывает соответствующий обработчик.
     */
    void onReadyRead();

    /**
     * @brief Обработчик отключения клиента
     * 
     * @details
     * Вызывается при отключении клиента, отправляет сигнал
     * и освобождает ресурсы.
     */
    void onDisconnected();

    /**
     * @brief Обработчик ошибок сокета
     * @param error Тип ошибки сокета
     * 
     * @details
     * Обрабатывает ошибки, возникшие при работе с сокетом,
     * и отправляет сигнал с информацией об ошибке.
     */
    void onError(QAbstractSocket::SocketError error);

    void onTimeout();

private:
    QTcpSocket* socket;           ///< Сокет клиентского соединения
    quintptr socketId;
    int userId;
    QTimer* timeoutTimer;
    bool isAuthenticated;         ///< Флаг аутентификации клиента
    QString username;             ///< Имя пользователя
    
    /**
     * @brief Обрабатывает входящее JSON сообщение
     * @param message JSON сообщение от клиента
     * 
     * @details
     * Анализирует тип сообщения и вызывает соответствующий
     * обработчик (аутентификация, задача и т.д.).
     */
    void handleMessage(const QJsonObject& message);

    /**
     * @brief Отправляет ответ клиенту
     * @param response JSON ответ для клиента
     * 
     * @details
     * Преобразует JSON объект в строку и отправляет
     * через сокет.
     */
    void sendResponse(const QString& response);

    /**
     * @brief Отправляет ответ клиенту
     * @param response JSON ответ для клиента
     */
    void sendResponse(const QJsonObject& response);

    /**
     * @brief Обрабатывает запрос на аутентификацию
     * @param message JSON сообщение с данными аутентификации
     * 
     * @details
     * Проверяет учетные данные пользователя через DatabaseManager
     * и отправляет результат клиенту.
     */
    void handleLogin(const QJsonObject& message);

    /**
     * @brief Обрабатывает запрос на выполнение задачи
     * @param message JSON сообщение с данными задачи
     * 
     * @details
     * Выполняет запрошенную задачу и отправляет результат
     * клиенту. Также обновляет статистику в базе данных.
     */
    void handleTask(const QJsonObject& message);

    QJsonObject processCommand(const QJsonObject& request);
    QJsonObject processAuthCommand(const QJsonObject& request);
    QString processTaskCommand(const QString& input);
    
    // Обработчики для каждого задания
    QString processTask1(const QStringList& tokens);  // SHA-1
    QString processTask2(const QStringList& tokens);  // Newton
    QString processTask3(const QStringList& tokens);  // WAV embed
    QString processTask4(const QStringList& tokens);  // Vigenere
    QString getStats();
};

#endif // CLIENTHANDLER_H