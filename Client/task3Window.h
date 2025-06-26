#ifndef TASK3WINDOW_H
#define TASK3WINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "client.h"

class Task3Window : public QWidget
{
    Q_OBJECT

public:
    explicit Task3Window(Client *client, QWidget *parent = nullptr);
    ~Task3Window();

private slots:
    void onOkClicked();
    void onExitClicked();
    void onTaskResult(bool success, const QString &message);

private:
    Client *client;
    QLabel *titleLabel;
    QLineEdit *messageEdit;
    QPushButton *okButton;
    QPushButton *exitButton;

    void setupUI();
    void connectSignals();

signals:
    void backToMain();
};

#endif // TASK3WINDOW_H
