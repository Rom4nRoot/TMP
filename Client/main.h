#ifndef MAIN_H
#define MAIN_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "authWindow.h"
#include "mainWindow.h"
#include "client.h"

class Main : public QMainWindow
{
    Q_OBJECT

public:
    Main(QWidget *parent = nullptr);
    ~Main();

private slots:
    void onClientError(const QString &error);
    void onLoginSuccess();

private:
    AuthWindow *authWindow;
    MainWindow *mainWindow;
    Client *client;
};

#endif // MAIN_H 