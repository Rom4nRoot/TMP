/**
 * @file main.cpp
 * @brief Главный файл сервера, точка входа в приложение
 * @author Roman
 * @date 2024
 * 
 * @details
 * Этот файл содержит функцию main(), которая:
 * 1. Инициализирует Qt приложение
 * 2. Создает и запускает TCP сервер
 * 3. Обрабатывает сигналы завершения работы
 * 
 * @see MyTcpServer
 */

#include <QCoreApplication>
#include <QDebug>
#include "mytcpserver.h"

/**
 * @brief Точка входа в приложение сервера
 * 
 * @param argc Количество аргументов командной строки
 * @param argv Массив аргументов командной строки
 * @return int Код возврата приложения
 * 
 * @details
 * Функция создает экземпляр QCoreApplication и MyTcpServer,
 * запускает сервер на порту 55555 и входит в главный цикл обработки событий.
 */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyTcpServer server;
    if (!server.startServer()) {
        qDebug() << "Не удалось запустить сервер";
        return -1;
    }

    qDebug() << "Сервер готов к работе...";

    return a.exec();
}
