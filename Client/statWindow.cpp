#include "statWindow.h"
#include <QMessageBox>

StatWindow::StatWindow(Client *client, QWidget *parent)
    : QWidget(parent)
    , client(client)
{
    setupUI();
    connectSignals();
    client->getStatistics();
}

StatWindow::~StatWindow()
{
}

void StatWindow::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Title
    titleLabel = new QLabel("Statistics", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    // Task statistics
    task1Label = new QLabel("Task 1: 0 correct, 0 incorrect", this);
    task2Label = new QLabel("Task 2: 0 correct, 0 incorrect", this);
    task3Label = new QLabel("Task 3: 0 correct, 0 incorrect", this);
    task4Label = new QLabel("Task 4: 0 correct, 0 incorrect", this);

    layout->addWidget(task1Label);
    layout->addWidget(task2Label);
    layout->addWidget(task3Label);
    layout->addWidget(task4Label);

    // Exit button
    exitButton = new QPushButton("Exit", this);
    layout->addWidget(exitButton);

    setLayout(layout);
}

void StatWindow::connectSignals()
{
    connect(exitButton, &QPushButton::clicked, this, &StatWindow::onExitClicked);
    connect(client, &Client::statisticsReceived, this, &StatWindow::onStatisticsReceived);
}

void StatWindow::onExitClicked()
{
    this->hide();
    emit backToMain();
}

void StatWindow::onStatisticsReceived(const QJsonObject &response)
{
    if (response.contains("stats")) {
        QJsonObject stats = response["stats"].toObject();
        updateStatistics(stats);
    }
}

void StatWindow::updateStatistics(const QJsonObject &stats)
{
    task1Label->setText(QString("Task 1: %1 correct, %2 incorrect")
        .arg(stats["task1_OK"].toInt())
        .arg(stats["task1_FALSE"].toInt()));

    task2Label->setText(QString("Task 2: %1 correct, %2 incorrect")
        .arg(stats["task2_OK"].toInt())
        .arg(stats["task2_FALSE"].toInt()));

    task3Label->setText(QString("Task 3: %1 correct, %2 incorrect")
        .arg(stats["task3_OK"].toInt())
        .arg(stats["task3_FALSE"].toInt()));

    task4Label->setText(QString("Task 4: %1 correct, %2 incorrect")
        .arg(stats["task4_OK"].toInt())
        .arg(stats["task4_FALSE"].toInt()));
}
