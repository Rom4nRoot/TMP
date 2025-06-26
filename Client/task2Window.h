#ifndef TASK2WINDOW_H
#define TASK2WINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "client.h"

namespace Ui {
class Task2Window;
}

class Task2Window : public QWidget
{
    Q_OBJECT

public:
    explicit Task2Window(Client *client, QWidget *parent = nullptr);
    ~Task2Window();

signals:
    void backToMain();

private slots:
    void onOkClicked();
    void onExitClicked();
    void onTaskResult(bool success, const QString &message);
    void onTask2Question(const QJsonObject &response);

private:
    Client *client;
    QLabel *taskLabel;
    QLineEdit *answerInput;
    QLabel *resultLabel;
    QPushButton *okButton;
    QPushButton *exitButton;
    QString currentQuestion;

    void setupUI();
    void connectSignals();
};

#endif // TASK2WINDOW_H
