/**
 * @file mainWindow.cpp
 * @brief Реализация главного окна приложения
 * @date 2024
 * 
 * @details
 * Реализует методы класса MainWindow для управления
 * пользовательским интерфейсом и навигацией.
 */

#include "mainWindow.h"
#include "ui_mainWindow.h"
#include "task1Window.h"
#include "task2Window.h"
#include "task3Window.h"
#include "task4Window.h"
#include "statWindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , client(nullptr)
    , task1Window(nullptr)
    , task2Window(nullptr)
    , task3Window(nullptr)
    , task4Window(nullptr)
    , statWindow(nullptr)
{
    ui->setupUi(this);
    setupUI();
    connectSignals();
    setWindowTitle("Main Menu");
    resize(400, 300);
}

MainWindow::~MainWindow()
{
    qDebug() << "Destroying MainWindow";
    if (task1Window) delete task1Window;
    if (task2Window) delete task2Window;
    if (task3Window) delete task3Window;
    if (task4Window) delete task4Window;
    if (statWindow) delete statWindow;
    delete ui;
}

void MainWindow::setClient(Client* newClient)
{
    client = newClient;
    connectSignals();
}

void MainWindow::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(ui->centralWidget);

    // Title
    QLabel *titleLabel = new QLabel("Tasks", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    // Task buttons
    task1Button = new QPushButton("Task 1 - SHA1 Hashing", this);
    task2Button = new QPushButton("Task 2 - Newton's Method", this);
    task3Button = new QPushButton("Task 3 - Audio Steganography", this);
    task4Button = new QPushButton("Task 4 - Vigenere Cipher", this);
    statButton = new QPushButton("Statistics", this);

    layout->addWidget(task1Button);
    layout->addWidget(task2Button);
    layout->addWidget(task3Button);
    layout->addWidget(task4Button);
    layout->addWidget(statButton);

    setLayout(layout);
}

void MainWindow::connectSignals()
{
    connect(task1Button, &QPushButton::clicked, this, &MainWindow::onTask1Clicked);
    connect(task2Button, &QPushButton::clicked, this, &MainWindow::onTask2Clicked);
    connect(task3Button, &QPushButton::clicked, this, &MainWindow::onTask3Clicked);
    connect(task4Button, &QPushButton::clicked, this, &MainWindow::onTask4Clicked);
    connect(statButton, &QPushButton::clicked, this, &MainWindow::onStatClicked);
    connect(client, &Client::taskResult, this, &MainWindow::onTaskResult);
    connect(client, &Client::statisticsReceived, this, &MainWindow::onStatisticsReceived);
}

void MainWindow::onTask1Clicked()
{
    qDebug() << "Task1 button clicked";
    if (!task1Window) {
    task1Window = new Task1Window(client);
        connect(task1Window, &Task1Window::backToMain, this, &MainWindow::onBackToMain);
    }
    task1Window->show();
    this->hide();
}

void MainWindow::onTask2Clicked()
{
    qDebug() << "Task2 button clicked";
    if (!task2Window) {
    task2Window = new Task2Window(client);
        connect(task2Window, &Task2Window::backToMain, this, &MainWindow::onBackToMain);
    }
    task2Window->show();
    this->hide();
}

void MainWindow::onTask3Clicked()
{
    qDebug() << "Task3 button clicked";
    if (!task3Window) {
    task3Window = new Task3Window(client);
        connect(task3Window, &Task3Window::backToMain, this, &MainWindow::onBackToMain);
    }
    task3Window->show();
    this->hide();
}

void MainWindow::onTask4Clicked()
{
    qDebug() << "Task4 button clicked";
    if (!task4Window) {
    task4Window = new Task4Window(client);
        connect(task4Window, &Task4Window::backToMain, this, &MainWindow::onBackToMain);
    }
    task4Window->show();
    this->hide();
}

void MainWindow::onStatClicked()
{
    qDebug() << "Statistics button clicked";
    if (!statWindow) {
    statWindow = new StatWindow(client);
        connect(statWindow, &StatWindow::backToMain, this, &MainWindow::onBackToMain);
    }
    statWindow->show();
    this->hide();
}

void MainWindow::onBackToMain()
{
    qDebug() << "Back to main window";
    this->show();
}

void MainWindow::onTaskResult(bool success, const QString &message)
{
    QMessageBox::information(this, success ? "Success" : "Error", message);
}

void MainWindow::onStatisticsReceived(const QJsonObject &stats)
{
    Q_UNUSED(stats);
    // This will be handled by StatWindow
}
