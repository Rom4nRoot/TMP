#include "task4Window.h"
#include <QMessageBox>
#include <QJsonObject>

Task4Window::Task4Window(Client *client, QWidget *parent)
    : QWidget(parent)
    , client(client)
{
    setupUI();
    connectSignals();
    // Запросить задание у сервера при открытии окна
    QJsonObject req;
    req["command"] = "task4";
    client->sendRequest(req);
}

Task4Window::~Task4Window()
{
}

void Task4Window::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Title
    titleLabel = new QLabel("Vigenere Cipher", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    // Task description
    taskLabel = new QLabel("Decrypt the following message using the Vigenere cipher:", this);
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

void Task4Window::connectSignals()
{
    connect(okButton, &QPushButton::clicked, this, &Task4Window::onOkClicked);
    connect(exitButton, &QPushButton::clicked, this, &Task4Window::onExitClicked);
    connect(client, &Client::taskResult, this, &Task4Window::onTaskResult);
    connect(client, &Client::task4Question, this, &Task4Window::onTask4Question);
}

void Task4Window::onOkClicked()
{
    QString answer = answerEdit->text();
    if (answer.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter your answer");
        return;
    }
    // Отправить ответ с вопросом и ключом
    QJsonObject req;
    req["command"] = "task4";
    req["question"] = currentQuestion;
    req["key"] = currentKey;
    req["answer"] = answer;
    client->sendRequest(req);
}

void Task4Window::onExitClicked()
{
    this->hide();
    emit backToMain();
}

void Task4Window::onTask4Question(const QJsonObject &response)
{
    if (response.contains("question")) {
        currentQuestion = response["question"].toString();
    }
    if (response.contains("key")) {
        currentKey = response["key"].toString();
    }
    if (response.contains("question") && response.contains("key")) {
        taskLabel->setText(QString("Зашифруйте сообщение '%1' ключом '%2'").arg(currentQuestion, currentKey));
    }
    if (response.contains("message")) {
        QMessageBox::information(this, "Task", response["message"].toString());
    }
}

void Task4Window::onTaskResult(bool success, const QString &message)
{
    QMessageBox::information(this, success ? "Success" : "Error", message);
    if (success) {
        answerEdit->clear();
        // Запросить новое задание
        QJsonObject req;
        req["command"] = "task4";
        client->sendRequest(req);
    }
}
