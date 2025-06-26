#ifndef TASK4WINDOW_H
#define TASK4WINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "client.h"

class Task4Window : public QWidget
{
    Q_OBJECT

public:
    explicit Task4Window(Client *client, QWidget *parent = nullptr);
    ~Task4Window();

private slots:
    void onOkClicked();
    void onExitClicked();
    void onTaskResult(bool success, const QString &message);
    void onTask4Question(const QJsonObject &response);

private:
    Client *client;
    QLabel *titleLabel;
    QLabel *taskLabel;
    QLineEdit *answerEdit;
    QPushButton *okButton;
    QPushButton *exitButton;
    QString currentQuestion;
    QString currentKey;

    void setupUI();
    void connectSignals();

signals:
    void backToMain();
};

#endif // TASK4WINDOW_H
