/**
 * @file client.h
 * @brief Заголовочный файл класса клиента
 * @date 2024
 * 
 * @details
 * Класс Client реализует сетевой клиент для взаимодействия с сервером.
 * Обеспечивает отправку запросов и получение ответов от сервера.
 */

#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "logger.h"

/**
 * @class Client
 * @brief Класс сетевого клиента
 * 
 * @details
 * Класс наследуется от QObject и обеспечивает:
 * 1. Подключение к серверу
 * 2. Отправку запросов
 * 3. Получение ответов
 * 4. Обработку ошибок
 */
class Client : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класса
     * @param parent Родительский объект Qt
     */
    explicit Client(QObject *parent = nullptr);
    ~Client();

    /**
     * @brief Подключение к серверу
     * @param host Адрес сервера
     * @param port Порт сервера
     * @return true если подключение успешно
     */
    bool connectToServer(const QString &host, quint16 port);
    void disconnectFromServer();
    bool isConnected() const;

    // Authentication methods
    bool login(const QString &username, const QString &password);
    bool registerUser(const QString &username, const QString &password);

    // Task methods
    bool submitTask1Answer(const QString &answer);
    bool submitTask2Answer(const QString &answer);
    bool submitTask3Message(const QString &message);
    bool submitTask4Answer(const QString &answer);
    QJsonObject getStatistics();

    /**
     * @brief Отправка запроса на сервер
     * @param request JSON объект с запросом
     * @return true если запрос отправлен успешно
     */
    bool sendRequest(const QJsonObject &request);

signals:
    /**
     * @brief Сигнал получения ответа от сервера
     * @param response JSON объект с ответом
     */
    void responseReceived(const QJsonObject &response);

    /**
     * @brief Сигнал ошибки подключения
     * @param error Сообщение об ошибке
     */
    void error(const QString &error);

    /**
     * @brief Сигнал отключения от сервера
     */
    void disconnected();
    void loginSuccess();
    void loginFailed(const QString &reason);
    void registerSuccess();
    void registerFailed(const QString &reason);
    void taskResult(bool success, const QString &message);
    void statisticsReceived(const QJsonObject &stats);
    void task1Question(const QJsonObject &response);
    void task2Question(const QJsonObject &response);
    void task4Question(const QJsonObject &response);

private slots:
    /**
     * @brief Обработчик входящих данных
     */
    void onReadyRead();
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket *socket;
    Logger logger;
    void processResponse(const QJsonObject &response);
};

#endif // CLIENT_H
