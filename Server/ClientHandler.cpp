/**
 * @file ClientHandler.cpp
 * @brief Реализация класса обработчика клиентских соединений
 * @author Roman
 * @date 2024
 * 
 * @details
 * Реализует методы класса ClientHandler для обработки
 * клиентских соединений и выполнения задач.
 */

#include "ClientHandler.h"
#include "DatabaseManager.h"
#include "vigenere.h"
#include "sha1.h"
#include "newton.h"
#include "wavembed.h"
#include <QRandomGenerator>
#include <QStandardPaths>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

ClientHandler::ClientHandler(QTcpSocket* socket, QObject *parent)
    : QObject(parent), socket(socket), userId(-1), isAuthenticated(false)
{
    socketId = socket->socketDescriptor();
    
    // Настройка таймаута
    timeoutTimer = new QTimer(this);
    timeoutTimer->setSingleShot(false);
    timeoutTimer->setInterval(300000); // 5 минут
    connect(timeoutTimer, &QTimer::timeout, this, &ClientHandler::onTimeout);
    
    // Подключение сигналов сокета
    connect(socket, &QTcpSocket::readyRead, this, &ClientHandler::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &ClientHandler::onDisconnected);
    connect(socket, &QTcpSocket::errorOccurred, this, &ClientHandler::onError);
    
    timeoutTimer->start();
    
    // Отправляем приветственное сообщение
    QJsonObject welcome;
    welcome["command"] = "system";
    welcome["message"] = "Добро пожаловать! Используйте команды: register или login";
    sendResponse(QJsonDocument(welcome).toJson(QJsonDocument::Compact));
    
    qDebug() << "Новый клиент подключен. Socket ID:" << socketId;
}

ClientHandler::~ClientHandler()
{
    if (userId != -1) {
        DatabaseManager::getInstance()->setUserOffline(userId);
    }
    qDebug() << "Клиент отключен. Socket ID:" << socketId;
}

void ClientHandler::sendResponse(const QString& response)
{
    if (socket && socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(response.toUtf8() + "\n");
        socket->flush();
    }
}

void ClientHandler::onReadyRead()
{
    timeoutTimer->start(); // Перезапуск таймера при активности

    while (socket->bytesAvailable() > 0) {
        QByteArray data = socket->readLine();
        QJsonParseError parseError;
        QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
        if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
            QJsonObject errorResp;
            errorResp["command"] = "error";
            errorResp["success"] = false;
            errorResp["message"] = "Некорректный JSON";
            sendResponse(QJsonDocument(errorResp).toJson(QJsonDocument::Compact));
            continue;
        }
        QJsonObject request = doc.object();
        QJsonObject response = processCommand(request);
        sendResponse(QJsonDocument(response).toJson(QJsonDocument::Compact));
    }
}

void ClientHandler::onDisconnected()
{
    timeoutTimer->stop();
    emit clientDisconnected(socketId);
}

void ClientHandler::onError(QAbstractSocket::SocketError error)
{
    Q_UNUSED(error);
    QString errorString = socket->errorString();
    qDebug() << "Ошибка сокета" << socketId << ":" << errorString;
    emit clientError(socketId, errorString);
}

void ClientHandler::onTimeout()
{
    qDebug() << "Таймаут для клиента" << socketId;
    sendResponse("ERROR|Соединение закрыто по таймауту");
    socket->disconnectFromHost();
}

QJsonObject ClientHandler::processCommand(const QJsonObject& request)
{
    QString cmd = request["command"].toString().toLower();
    QJsonObject response;
    response["command"] = cmd;

    if (cmd == "register" || cmd == "login") {
        return processAuthCommand(request);
    }
    if (!isAuthenticated) {
        response["success"] = false;
        response["message"] = "Необходима авторизация";
        return response;
    }
    if (cmd == "statistics") {
        DatabaseManager* db = DatabaseManager::getInstance();
        QJsonObject stats = db->getUserStatsJson(userId);
        response["success"] = true;
        response["stats"] = stats;
        response["message"] = "Статистика пользователя";
        return response;
    }
    if (cmd == "task1") {
        DatabaseManager* db = DatabaseManager::getInstance();
        QJsonObject resp;
        resp["command"] = "task1";
        // Генерация задания
        if (!request.contains("question")) {
            QStringList testMessages = {"hello world", "cryptography", "security test", "hash function", "qt programming"};
            QString message = testMessages[QRandomGenerator::global()->bounded(testMessages.size())];
            resp["success"] = true;
            resp["question"] = message;
            resp["message"] = "Вычислите SHA1 для строки";
            return resp;
        }
        // Проверка ответа
        QString originalMessage = request["question"].toString();
        QString userAnswer = request["answer"].toString().toLower();
        QString correctAnswer = computeSHA1(originalMessage).toLower();
        bool isCorrect = (userAnswer == correctAnswer);
        db->updateTaskStats(userId, "SHA1", isCorrect);
        resp["success"] = isCorrect;
        resp["message"] = isCorrect ? "Правильно! SHA-1 вычислен верно" : ("Неправильно. Правильный ответ: " + correctAnswer);
        return resp;
    }
    if (cmd == "task2") {
        DatabaseManager* db = DatabaseManager::getInstance();
        QJsonObject resp;
        resp["command"] = "task2";
        if (!request.contains("question")) {
            QList<double> testNumbers = {4.0, 9.0, 16.0, 25.0, 36.0, 49.0, 64.0, 81.0, 100.0};
            double number = testNumbers[QRandomGenerator::global()->bounded(testNumbers.size())];
            resp["success"] = true;
            resp["question"] = QString::number(number);
            resp["message"] = QString("Найти квадратный корень из %1 методом Ньютона").arg(number);
            return resp;
        }
        bool ok1, ok2;
        double number = request["question"].toString().toDouble(&ok1);
        double userAnswer = request["answer"].toString().toDouble(&ok2);
        QJsonObject failResp = resp;
        if (!ok1 || !ok2) {
            db->updateTaskStats(userId, "NEWTON", false);
            failResp["success"] = false;
            failResp["message"] = "Неверный формат числа";
            return failResp;
        }
        double correctAnswer = newtonMethod(number);
        bool isCorrect = qAbs(userAnswer - correctAnswer) < 0.01;
        db->updateTaskStats(userId, "NEWTON", isCorrect);
        resp["success"] = isCorrect;
        resp["message"] = isCorrect ? "Правильно! Корень вычислен верно" : QString("Неправильно. Правильный ответ: %1").arg(correctAnswer, 0, 'f', 6);
        return resp;
    }
    if (cmd == "task3") {
        DatabaseManager* db = DatabaseManager::getInstance();
        QJsonObject resp;
        resp["command"] = "task3";
        if (!request.contains("message")) {
            resp["success"] = true;
            resp["message"] = "Введите сообщение для внедрения в WAV-файл";
            return resp;
        }
        QString message = request["message"].toString();
        QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        QString filePath = desktopPath + "/output.wav";
        QString result = embedMessageInWAV(filePath, message);
        bool success = result.contains("успешно");
        db->updateTaskStats(userId, "HIDE", success);
        resp["success"] = success;
        resp["message"] = success ? "Сообщение успешно внедрено в файл output.wav на рабочем столе" : result;
        return resp;
    }
    if (cmd == "task4") {
        DatabaseManager* db = DatabaseManager::getInstance();
        QJsonObject resp;
        resp["command"] = "task4";
        if (!request.contains("question")) {
            QStringList testMessages = {"HELLO", "WORLD", "SECRET", "MESSAGE", "CRYPTO"};
            QStringList testKeys = {"KEY", "CODE", "PASS", "LOCK", "SAFE"};
            QString message = testMessages[QRandomGenerator::global()->bounded(testMessages.size())];
            QString key = testKeys[QRandomGenerator::global()->bounded(testKeys.size())];
            resp["success"] = true;
            resp["question"] = message;
            resp["key"] = key;
            resp["message"] = QString("Зашифруйте сообщение '%1' ключом '%2' (шифр Виженера)").arg(message, key);
            return resp;
        }
        QString message = request["question"].toString();
        QString key = request["key"].toString();
        QString userAnswer = request["answer"].toString().toUpper();
        QString correctAnswer = vigenereEncrypt(message, key).toUpper();
        bool isCorrect = (userAnswer == correctAnswer);
        db->updateTaskStats(userId, "ENCRYPT", isCorrect);
        resp["success"] = isCorrect;
        resp["message"] = isCorrect ? "Правильно! Шифр Виженера применен верно" : ("Неправильно. Правильный ответ: " + correctAnswer);
        return resp;
    }
    response["success"] = false;
    response["message"] = "Неизвестная команда";
    return response;
}

QJsonObject ClientHandler::processAuthCommand(const QJsonObject& request)
{
    QString cmd = request["command"].toString().toLower();
    QJsonObject response;
    response["command"] = cmd;
    QString login = request["username"].toString();
    QString password = request["password"].toString();
    
    qDebug() << "Processing auth command:" << cmd << "for user:" << login;
    
    DatabaseManager* db = DatabaseManager::getInstance();
    if (cmd == "register") {
        if (login.isEmpty() || password.isEmpty()) {
            qDebug() << "Empty login or password";
            response["success"] = false;
            response["message"] = "Пустой логин или пароль";
            return response;
        }
        if (db->registerUser(login, password)) {
            qDebug() << "User registered successfully";
            response["success"] = true;
            response["message"] = "Регистрация успешна";
        } else {
            qDebug() << "User already exists";
            response["success"] = false;
            response["message"] = "Пользователь уже существует";
        }
        return response;
    }
    if (cmd == "login") {
        if (login.isEmpty() || password.isEmpty()) {
            qDebug() << "Empty login or password";
            response["success"] = false;
            response["message"] = "Пустой логин или пароль";
            return response;
        }
        int authUserId = db->authenticateUser(login, password);
        if (authUserId != -1) {
            qDebug() << "User authenticated successfully, userId:" << authUserId;
            userId = authUserId;
            db->setUserSocketId(userId, socketId);
            response["success"] = true;
            response["message"] = "Вход выполнен успешно";
        } else {
            qDebug() << "Authentication failed for user:" << login;
            response["success"] = false;
            response["message"] = "Неверный логин или пароль";
        }
        return response;
    }
    response["success"] = false;
    response["message"] = "Неизвестная команда аутентификации";
    return response;
}

QString ClientHandler::getStats()
{
    DatabaseManager* db = DatabaseManager::getInstance();
    QMap<QString, QPair<int, int>> stats = db->getUserStats(userId);
    
    QString result = "STATS|";
    result += QString("SHA1:%1:%2|").arg(stats["SHA1"].first).arg(stats["SHA1"].second);
    result += QString("NEWTON:%1:%2|").arg(stats["NEWTON"].first).arg(stats["NEWTON"].second);
    result += QString("HIDE:%1:%2|").arg(stats["HIDE"].first).arg(stats["HIDE"].second);
    result += QString("ENCRYPT:%1:%2").arg(stats["ENCRYPT"].first).arg(stats["ENCRYPT"].second);
    
    return result;
}