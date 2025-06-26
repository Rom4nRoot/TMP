/**
 * @file mainWindow.h
 * @brief Заголовочный файл главного окна приложения
 * @date 2024
 * 
 * @details
 * Класс MainWindow реализует главное окно приложения,
 * содержащее меню задач и управление пользователем.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "client.h"
#include "task1Window.h"
#include "task2Window.h"
#include "task3Window.h"
#include "task4Window.h"
#include "statWindow.h"

namespace Ui {
class MainWindow;
}

/**
 * @class MainWindow
 * @brief Класс главного окна приложения
 * 
 * @details
 * Класс наследуется от QMainWindow и обеспечивает:
 * 1. Отображение списка доступных задач
 * 2. Управление пользовательским сеансом
 * 3. Навигацию между задачами
 * 4. Отображение статистики
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор класса
     * @param parent Родительский объект Qt
     */
    explicit MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Деструктор класса
     */
    ~MainWindow();

    /**
     * @brief Установка клиента
     * @param client Указатель на объект клиента
     */
    void setClient(Client* client);

private slots:
    /**
     * @brief Обработчик нажатия кнопки задачи 1
     */
    void onTask1Clicked();

    /**
     * @brief Обработчик нажатия кнопки задачи 2
     */
    void onTask2Clicked();

    /**
     * @brief Обработчик нажатия кнопки задачи 3
     */
    void onTask3Clicked();

    /**
     * @brief Обработчик нажатия кнопки задачи 4
     */
    void onTask4Clicked();

    /**
     * @brief Обработчик нажатия кнопки статистики
     */
    void onStatsClicked();

    /**
     * @brief Обработчик нажатия кнопки выхода
     */
    void onLogoutClicked();

    void onTaskResult(bool success, const QString &message);
    void onStatisticsReceived(const QJsonObject &stats);
    void onBackToMain();

private:
    Ui::MainWindow *ui;      ///< Указатель на форму
    Client* client;          ///< Указатель на клиента
    QString username;        ///< Имя пользователя

    QPushButton *task1Button;
    QPushButton *task2Button;
    QPushButton *task3Button;
    QPushButton *task4Button;
    QPushButton *statButton;

    Task1Window *task1Window;
    Task2Window *task2Window;
    Task3Window *task3Window;
    Task4Window *task4Window;
    StatWindow *statWindow;

    /**
     * @brief Инициализация интерфейса
     */
    void setupUi();

    /**
     * @brief Создание кнопок задач
     */
    void createTaskButtons();

    void connectSignals();
};

#endif // MAINWINDOW_H
