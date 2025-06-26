/**
 * @file client.cpp
 * @brief Реализация класса клиента
 * @date 2024
 * 
 * @details
 * Реализует методы класса Client для взаимодействия с сервером.
 */

#include "client.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

Client::Client(QObject *parent)
    : QObject(parent)
    , socket(new QTcpSocket(this))
{
    // Подключаем сигналы сокета
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error),
            this, &Client::onError);
}

Client::~Client()
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->disconnectFromHost();
    }
}

bool Client::connectToServer(const QString& host, quint16 port)
{
    socket->connectToHost(host, port);
    return socket->waitForConnected(5000);
}

void Client::disconnectFromServer()
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->disconnectFromHost();
    }
}

bool Client::isConnected() const
{
    return socket->state() == QAbstractSocket::ConnectedState;
}

bool Client::login(const QString &username, const QString &password)
{
    QJsonObject request;
    request["command"] = "login";
    request["username"] = username;
    request["password"] = password;
    sendRequest(request);
    return true;
}

bool Client::registerUser(const QString &username, const QString &password)
{
    QJsonObject request;
    request["command"] = "register";
    request["username"] = username;
    request["password"] = password;
    sendRequest(request);
    return true;
}

bool Client::submitTask1Answer(const QString &answer)
{
    QJsonObject request;
    request["command"] = "task1";
    request["answer"] = answer;
    sendRequest(request);
    return true;
}

bool Client::submitTask2Answer(const QString &answer)
{
    QJsonObject request;
    request["command"] = "task2";
    request["answer"] = answer;
    sendRequest(request);
    return true;
}

bool Client::submitTask3Message(const QString &message)
{
    QJsonObject request;
    request["command"] = "task3";
    request["message"] = message;
    sendRequest(request);
    return true;
}

bool Client::submitTask4Answer(const QString &answer)
{
    QJsonObject request;
    request["command"] = "task4";
    request["answer"] = answer;
    sendRequest(request);
    return true;
}

QJsonObject Client::getStatistics()
{
    QJsonObject request;
    request["command"] = "statistics";
    sendRequest(request);
    return QJsonObject();
}

bool Client::sendRequest(const QJsonObject& request)
{
    if (!isConnected()) {
        emit error("Not connected to server");
        return false;
    }

    QJsonDocument doc(request);
    QByteArray data = doc.toJson();
    qint64 written = socket->write(data);
    
    if (written != data.size()) {
        emit error("Failed to send complete request");
        return false;
    }

    return socket->waitForBytesWritten(5000);
}

void Client::onReadyRead()
{
    QByteArray data = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    
    if (doc.isNull() || !doc.isObject()) {
        emit error("Invalid response format");
        return;
    }

    QJsonObject response = doc.object();
    processResponse(response);
}

void Client::onDisconnected()
{
    emit disconnected();
}

void Client::onError(QAbstractSocket::SocketError error)
{
    emit this->error(socket->errorString());
}

void Client::processResponse(const QJsonObject& response)
{
    QString type = response["type"].toString();

    if (type == "login_success") {
        emit loginSuccess();
    }
    else if (type == "error") {
        QString message = response["message"].toString();
        if (type == "login") {
            emit loginFailed(message);
        }
        else {
            emit error(message);
        }
    }
    else if (type == "task_result") {
        bool success = response["success"].toBool();
        QString message = response["result"].toString();
        emit taskResult(success, message);
    }
    else if (type == "statistics") {
        emit statisticsReceived(response["data"].toObject());
    }
    else {
        emit responseReceived(response);
    }
}
