/**
 * @file mytcpserver.h
 * @brief Заголовочный файл основного класса TCP сервера
 * 
 * Класс MyTcpServer реализует:
 * 1. Прослушивание входящих TCP подключений
 * 2. Управление подключенными клиентами
 * 3. Обработку подключения/отключения клиентов
 * 4. Распределение клиентских соединений между обработчиками
 */

#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMap>
#include <QDebug>
#include "ClientHandler.h"

class MyTcpServer : public QObject
{
    Q_OBJECT

public:
    explicit MyTcpServer(QObject *parent = nullptr);
    ~MyTcpServer();

    /**
     * @brief Запускает сервер на указанном порту
     * @param port Порт для прослушивания (по умолчанию 55555)
     * @return true если сервер успешно запущен
     */
    bool startServer(quint16 port = 55555);

    /**
     * @brief Останавливает сервер и отключает всех клиентов
     */
    void stopServer();

    /**
     * @brief Возвращает количество подключенных клиентов
     * @return Количество активных клиентских соединений
     */
    int getConnectedClientsCount() const { return clients.size(); }

private slots:
    /**
     * @brief Обработчик новых подключений
     * Создает новый ClientHandler для каждого подключения
     */
    void onNewConnection();

    /**
     * @brief Обработчик отключения клиента
     * @param socketId Идентификатор сокета отключившегося клиента
     */
    void onClientDisconnected(quintptr socketId);

    /**
     * @brief Обработчик ошибок клиента
     * @param socketId Идентификатор сокета клиента
     * @param error Сообщение об ошибке
     */
    void onClientError(quintptr socketId, const QString& error);

private:
    QTcpServer* tcpServer;                    ///< TCP сервер
    QMap<quintptr, ClientHandler*> clients;   ///< Карта подключенных клиентов

    /**
     * @brief Удаляет клиента из списка и освобождает ресурсы
     * @param socketId Идентификатор сокета клиента
     */
    void removeClient(quintptr socketId);
};

#endif // MYTCPSERVER_H
