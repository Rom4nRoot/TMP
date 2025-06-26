/**
 * @file authWindow.h
 * @brief Заголовочный файл окна аутентификации
 * @date 2024
 * 
 * @details
 * Класс AuthWindow реализует окно входа в систему,
 * содержащее поля для ввода логина и пароля.
 */

#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include "client.h"
#include "mainWindow.h"

namespace Ui {
class AuthWindow;
}

/**
 * @class AuthWindow
 * @brief Класс окна аутентификации
 * 
 * @details
 * Класс наследуется от QWidget и обеспечивает:
 * 1. Ввод учетных данных
 * 2. Отправку запроса на аутентификацию
 * 3. Обработку результата аутентификации
 * 4. Переход к регистрации
 */
class AuthWindow : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класса
     * @param parent Родительский объект Qt
     */
    explicit AuthWindow(Client *client, QWidget *parent = nullptr);

    /**
     * @brief Деструктор класса
     */
    ~AuthWindow();

    /**
     * @brief Установка клиента
     * @param client Указатель на объект клиента
     */
    void setClient(Client* client);

private slots:
    /**
     * @brief Обработчик нажатия кнопки входа
     */
    void onLoginClicked();

    /**
     * @brief Обработчик нажатия кнопки регистрации
     */
    void onRegisterClicked();

    /**
     * @brief Обработчик успешной аутентификации
     */
    void onLoginSuccess();

    /**
     * @brief Обработчик неудачной аутентификации
     * @param reason Причина ошибки
     */
    void onLoginFailed(const QString &reason);

    /**
     * @brief Обработчик успешной регистрации
     */
    void onRegisterSuccess();

    /**
     * @brief Обработчик неудачной регистрации
     * @param reason Причина ошибки
     */
    void onRegisterFailed(const QString &reason);

private:
    Ui::AuthWindow *ui;      ///< Указатель на форму
    Client *client;          ///< Указатель на клиента
    QLineEdit *loginEdit;    ///< Поле ввода логина
    QLineEdit *passwordEdit; ///< Поле ввода пароля
    QPushButton *loginButton;///< Кнопка входа
    QPushButton *registerButton; ///< Кнопка регистрации
    MainWindow *mainWindow;

    /**
     * @brief Инициализация интерфейса
     */
    void setupUI();

    /**
     * @brief Подключение сигналов
     */
    void connectSignals();
};

#endif // AUTHWINDOW_H
