#ifndef STATWINDOW_H
#define STATWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include "client.h"

class StatWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StatWindow(Client *client, QWidget *parent = nullptr);
    ~StatWindow();

signals:
    void backToMain();

private slots:
    void onExitClicked();
    void onStatisticsReceived(const QJsonObject &stats);

private:
    Client *client;
    QLabel *titleLabel;
    QLabel *task1Label;
    QLabel *task2Label;
    QLabel *task3Label;
    QLabel *task4Label;
    QPushButton *exitButton;

    void setupUI();
    void connectSignals();
    void updateStatistics(const QJsonObject &stats);
};

#endif // STATWINDOW_H
