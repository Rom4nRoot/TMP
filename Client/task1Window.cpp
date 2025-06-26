#include "task1Window.h"
#include <QMessageBox>
#include <QJsonObject>

Task1Window::Task1Window(Client *client, QWidget *parent)
    : QWidget(parent)
    , client(client)
{
    setupUI();
    connectSignals();
    // Запросить задание у сервера при открытии окна
    QJsonObject req;
    req["command"] = "task1";
    client->sendRequest(req);
}

Task1Window::~Task1Window()
{
}

void Task1Window::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Title
    titleLabel = new QLabel("SHA1 Hashing", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    // Task description
    taskLabel = new QLabel("Hash the following text using SHA1:", this);
    layout->addWidget(taskLabel);

    // Answer input
    answerEdit = new QLineEdit(this);
    answerEdit->setPlaceholderText("Enter your answer");
    layout->addWidget(answerEdit);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    okButton = new QPushButton("OK", this);
    exitButton = new QPushButton("Exit", this);

    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(exitButton);
    layout->addLayout(buttonLayout);

    setLayout(layout);
}

void Task1Window::connectSignals()
{
    connect(okButton, &QPushButton::clicked, this, &Task1Window::onOkClicked);
    connect(exitButton, &QPushButton::clicked, this, &Task1Window::onExitClicked);
    connect(client, &Client::taskResult, this, &Task1Window::onTaskResult);
    connect(client, &Client::task1Question, this, &Task1Window::onTask1Question);
}

void Task1Window::onOkClicked()
{
    QString answer = answerEdit->text();
    if (answer.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter your answer");
        return;
    }
    // Отправить ответ с вопросом
    QJsonObject req;
    req["command"] = "task1";
    req["question"] = currentQuestion;
    req["answer"] = answer;
    client->sendRequest(req);
}

void Task1Window::onExitClicked()
{
    this->hide();
    emit backToMain();
}

void Task1Window::onTaskResult(bool success, const QString &message)
{
    QMessageBox::information(this, success ? "Success" : "Error", message);
    if (success) {
        answerEdit->clear();
        // Запросить новое задание
        QJsonObject req;
        req["command"] = "task1";
        client->sendRequest(req);
    }
}

void Task1Window::onTask1Question(const QJsonObject &response)
{
    if (response.contains("question")) {
        currentQuestion = response["question"].toString();
        taskLabel->setText("Hash the following text using SHA1: " + currentQuestion);
    }
    if (response.contains("message")) {
        QMessageBox::information(this, "Task", response["message"].toString());
    }
}
