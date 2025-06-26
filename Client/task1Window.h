#ifndef TASK1WINDOW_H
#define TASK1WINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "client.h"

class Task1Window : public QWidget
{
    Q_OBJECT

public:
    explicit Task1Window(Client *client, QWidget *parent = nullptr);
    ~Task1Window();

private slots:
    void onOkClicked();
    void onExitClicked();
    void onTaskResult(bool success, const QString &message);
    void onTask1Question(const QJsonObject &response);

private:
    Client *client;
    QLabel *titleLabel;
    QLabel *taskLabel;
    QLineEdit *answerEdit;
    QPushButton *okButton;
    QPushButton *exitButton;
    QString currentQuestion;

    void setupUI();
    void connectSignals();

signals:
    void backToMain();
};

#endif // TASK1WINDOW_H
