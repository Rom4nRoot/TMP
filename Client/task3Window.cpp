#include "task3Window.h"
#include <QMessageBox>

Task3Window::Task3Window(Client *client, QWidget *parent)
    : QWidget(parent)
    , client(client)
{
    setupUI();
    connectSignals();
}

Task3Window::~Task3Window()
{
}

void Task3Window::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Title
    titleLabel = new QLabel("Audio Steganography", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    // Message input
    messageEdit = new QLineEdit(this);
    messageEdit->setPlaceholderText("Enter message to embed in audio file");
    layout->addWidget(messageEdit);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    okButton = new QPushButton("OK", this);
    exitButton = new QPushButton("Exit", this);

    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(exitButton);
    layout->addLayout(buttonLayout);

    setLayout(layout);
}

void Task3Window::connectSignals()
{
    connect(okButton, &QPushButton::clicked, this, &Task3Window::onOkClicked);
    connect(exitButton, &QPushButton::clicked, this, &Task3Window::onExitClicked);
    connect(client, &Client::taskResult, this, &Task3Window::onTaskResult);
}

void Task3Window::onOkClicked()
{
    QString message = messageEdit->text();
    if (message.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter a message");
        return;
    }

    client->submitTask3Message(message);
}

void Task3Window::onExitClicked()
{
    this->hide();
    emit backToMain();
}

void Task3Window::onTaskResult(bool success, const QString &message)
{
    QMessageBox::information(this, success ? "Success" : "Error", message);
    if (success) {
        messageEdit->clear();
    }
}
