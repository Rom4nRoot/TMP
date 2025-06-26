/**
 * @file authWindow.cpp
 * @brief Реализация окна аутентификации
 * @date 2024
 * 
 * @details
 * Реализует методы класса AuthWindow для входа в систему
 * и регистрации новых пользователей.
 */

#include "authWindow.h"
#include "ui_authWindow.h"
#include "registerWindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDebug>

AuthWindow::AuthWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AuthWindow)
    , client(nullptr)
{
    ui->setupUi(this);
    setupUi();
}

AuthWindow::~AuthWindow()
{
    delete ui;
}

void AuthWindow::setClient(Client* newClient)
{
    client = newClient;
    connectSignals();
}

void AuthWindow::setupUi()
{
    setWindowTitle("Login");
    QVBoxLayout* layout = new QVBoxLayout(this);

    // Создаем элементы интерфейса
    QLabel* titleLabel = new QLabel("Login to Task Manager", this);
    loginEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    loginButton = new QPushButton("Login", this);
    registerButton = new QPushButton("Register", this);

    // Настраиваем элементы
    titleLabel->setAlignment(Qt::AlignCenter);
    loginEdit->setPlaceholderText("Username");
    passwordEdit->setPlaceholderText("Password");
    passwordEdit->setEchoMode(QLineEdit::Password);

    // Добавляем элементы на форму
    layout->addWidget(titleLabel);
    layout->addWidget(loginEdit);
    layout->addWidget(passwordEdit);
    layout->addWidget(loginButton);
    layout->addWidget(registerButton);

    // Подключаем сигналы
    connect(loginButton, &QPushButton::clicked, this, &AuthWindow::onLoginClicked);
    connect(registerButton, &QPushButton::clicked, this, &AuthWindow::onRegisterClicked);
}

void AuthWindow::connectSignals()
{
    if (client) {
    connect(client, &Client::loginSuccess, this, &AuthWindow::onLoginSuccess);
    connect(client, &Client::loginFailed, this, &AuthWindow::onLoginFailed);
    }
}

void AuthWindow::onLoginClicked()
{
    if (!client) {
        QMessageBox::critical(this, "Error", "Client not initialized");
        return;
    }

    QString username = loginEdit->text();
    QString password = passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter username and password");
        return;
    }

    QJsonObject request;
    request["type"] = "login";
    request["username"] = username;
    request["password"] = password;

    if (!client->sendRequest(request)) {
        QMessageBox::critical(this, "Error", "Failed to send login request");
    }
}

void AuthWindow::onRegisterClicked()
{
    RegisterWindow* registerWindow = new RegisterWindow(client, this);
    registerWindow->show();
    hide();
}

void AuthWindow::onLoginSuccess()
{
    emit loginSuccessful();
}

void AuthWindow::onLoginFailed(const QString& reason)
{
    QMessageBox::critical(this, "Login Failed", reason);
}

void AuthWindow::onBackToAuth()
{
    show();
}
