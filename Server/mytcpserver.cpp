/**
 * @file mytcpserver.cpp
 * @brief Реализация TCP сервера для обработки клиентских подключений
 */

#include "mytcpserver.h"
#include "DatabaseManager.h"

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    // Создаем TCP сервер и подключаем сигнал нового подключения
    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection, this, &MyTcpServer::onNewConnection);
}

MyTcpServer::~MyTcpServer()
{
    // При уничтожении сервера останавливаем его
    stopServer();
}

bool MyTcpServer::startServer(quint16 port)
{
    // Инициализируем базу данных перед запуском сервера
    if (!DatabaseManager::getInstance()) {
        qDebug() << "Ошибка инициализации базы данных";
        return false;
    }
    
    // Пытаемся запустить сервер на указанном порту
    if (!tcpServer->listen(QHostAddress::Any, port)) {
        qDebug() << "Ошибка запуска сервера:" << tcpServer->errorString();
        return false;
    }
    
    qDebug() << "Сервер запущен на порту" << port;
    return true;
}

void MyTcpServer::stopServer()
{
    // Останавливаем прослушивание порта
    if (tcpServer->isListening()) {
        tcpServer->close();
    }
    
    // Отключаем всех клиентов и освобождаем ресурсы
    for (auto client : clients) {
        client->deleteLater();
    }
    clients.clear();
    
    // Уничтожаем экземпляр базы данных
    DatabaseManager::destroyInstance();
    qDebug() << "Сервер остановлен";
}

void MyTcpServer::onNewConnection()
{
    // Обрабатываем все ожидающие подключения
    while (tcpServer->hasPendingConnections()) {
        // Получаем сокет нового подключения
        QTcpSocket* socket = tcpServer->nextPendingConnection();
        quintptr socketId = socket->socketDescriptor();
        
        // Создаем обработчик для нового клиента
        ClientHandler* client = new ClientHandler(socket, this);
        clients[socketId] = client;
        
        // Подключаем сигналы для обработки отключения и ошибок
        connect(client, &ClientHandler::clientDisconnected, 
                this, &MyTcpServer::onClientDisconnected);
        connect(client, &ClientHandler::clientError, 
                this, &MyTcpServer::onClientError);
        
        qDebug() << "Новое подключение. Всего клиентов:" << clients.size();
    }
}

void MyTcpServer::onClientDisconnected(quintptr socketId)
{
    // Удаляем отключившегося клиента
    removeClient(socketId);
    qDebug() << "Клиент отключен. Осталось клиентов:" << clients.size();
}

void MyTcpServer::onClientError(quintptr socketId, const QString& error)
{
    // Обрабатываем ошибку клиента
    qDebug() << "Ошибка клиента" << socketId << ":" << error;
    removeClient(socketId);
}

void MyTcpServer::removeClient(quintptr socketId)
{
    // Удаляем клиента из списка и освобождаем ресурсы
    if (clients.contains(socketId)) {
        clients[socketId]->deleteLater();
        clients.remove(socketId);
    }
}
