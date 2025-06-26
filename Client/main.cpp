#include "main.h"
#include "logger.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include <iostream>

Main::Main(QWidget *parent)
    : QMainWindow(parent)
    , client(nullptr)
    , authWindow(nullptr)
    , mainWindow(nullptr)
{
    qDebug() << "Creating Main application window";
    
    client = new Client(this);
    
    // Подключаем сигналы ошибок
    connect(client, &Client::error, this, &Main::onClientError);
    
    // Подключаемся к серверу
    if (!client->connectToServer("localhost", 55555)) {
        QMessageBox::critical(this, "Ошибка подключения", 
            "Не удалось подключиться к серверу. Проверьте, что сервер запущен.");
        return;
    }
    
    // Создаем только окно авторизации
    authWindow = new AuthWindow(client, this);
    setCentralWidget(authWindow);
    
    // Подключаем сигнал успешной авторизации
    connect(client, &Client::loginSuccess, this, &Main::onLoginSuccess);
    
    setWindowTitle("Client Application");
    resize(400, 300);
}

void Main::onClientError(const QString &error)
{
    QMessageBox::warning(this, "Ошибка клиента", error);
}

void Main::onLoginSuccess()
{
    qDebug() << "Login success in Main window";
    
    // Создаем главное окно только после успешной авторизации
    if (!mainWindow) {
        mainWindow = new MainWindow(client, this);
    }
    
    // Меняем центральный виджет
    setCentralWidget(mainWindow);
    
    // Скрываем окно авторизации
    if (authWindow) {
        authWindow->hide();
    }
}

Main::~Main()
{
    qDebug() << "Destroying Main application window";
    if (client) delete client;
    if (authWindow) delete authWindow;
    if (mainWindow) delete mainWindow;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Инициализируем логгер
    Logger::init();
    std::cout << "Starting client application..." << std::endl;
    qDebug() << "Starting client application...";
    
    Main w;
    w.show();
    return a.exec();
}
