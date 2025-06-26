#include "task2Window.h"
#include <QMessageBox>
#include <QJsonObject>

Task2Window::Task2Window(Client *client, QWidget *parent)
    : QWidget(parent), client(client)
{
    setWindowTitle("Task 2 - Newton's Method");
    resize(500, 300);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Title
    QLabel *titleLabel = new QLabel("Newton's Method", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel);

    // Task description
    taskLabel = new QLabel("Solve the equation using Newton's method:", this);
    taskLabel->setWordWrap(true);
    mainLayout->addWidget(taskLabel);

    // Answer input
    answerInput = new QLineEdit(this);
    answerInput->setPlaceholderText("Enter your answer");
    mainLayout->addWidget(answerInput);

    // Result label
    resultLabel = new QLabel(this);
    resultLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(resultLabel);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    okButton = new QPushButton("OK", this);
    exitButton = new QPushButton("Exit", this);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(exitButton);
    mainLayout->addLayout(buttonLayout);

    // Connect signals
    connect(okButton, &QPushButton::clicked, this, &Task2Window::onOkClicked);
    connect(exitButton, &QPushButton::clicked, this, &Task2Window::onExitClicked);
    connect(client, &Client::taskResult, this, &Task2Window::onTaskResult);
    connect(client, &Client::task2Question, this, &Task2Window::onTask2Question);

    // Запросить задание у сервера при открытии окна
    QJsonObject req;
    req["command"] = "task2";
    client->sendRequest(req);
}

void Task2Window::onOkClicked()
{
    QString answer = answerInput->text();
    if (answer.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter your answer");
        return;
    }
    // Отправить ответ с вопросом
    QJsonObject req;
    req["command"] = "task2";
    req["question"] = currentQuestion;
    req["answer"] = answer;
    client->sendRequest(req);
}

void Task2Window::onExitClicked()
{
    emit backToMain();
    close();
}

void Task2Window::onTask2Question(const QJsonObject &response)
{
    if (response.contains("question")) {
        currentQuestion = response["question"].toString();
        taskLabel->setText("Найти квадратный корень из: " + currentQuestion);
    }
    if (response.contains("message")) {
        QMessageBox::information(this, "Task", response["message"].toString());
    }
}

void Task2Window::onTaskResult(bool success, const QString &message)
{
    if (success) {
        resultLabel->setText("Correct!");
        resultLabel->setStyleSheet("color: green");
        answerInput->clear();
        // Запросить новое задание
        QJsonObject req;
        req["command"] = "task2";
        client->sendRequest(req);
    } else {
        resultLabel->setText("Incorrect: " + message);
        resultLabel->setStyleSheet("color: red");
    }
}

Task2Window::~Task2Window() {}

