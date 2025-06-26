/********************************************************************************
** Form generated from reading UI file 'authWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHWINDOW_H
#define UI_AUTHWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AuthWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLineEdit *loginEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
    QPushButton *registerButton;

    void setupUi(QWidget *AuthWindow)
    {
        if (AuthWindow->objectName().isEmpty())
            AuthWindow->setObjectName("AuthWindow");
        AuthWindow->resize(400, 300);
        verticalLayout = new QVBoxLayout(AuthWindow);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(AuthWindow);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        loginEdit = new QLineEdit(AuthWindow);
        loginEdit->setObjectName("loginEdit");

        verticalLayout->addWidget(loginEdit);

        passwordEdit = new QLineEdit(AuthWindow);
        passwordEdit->setObjectName("passwordEdit");
        passwordEdit->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(passwordEdit);

        loginButton = new QPushButton(AuthWindow);
        loginButton->setObjectName("loginButton");

        verticalLayout->addWidget(loginButton);

        registerButton = new QPushButton(AuthWindow);
        registerButton->setObjectName("registerButton");

        verticalLayout->addWidget(registerButton);


        retranslateUi(AuthWindow);

        QMetaObject::connectSlotsByName(AuthWindow);
    } // setupUi

    void retranslateUi(QWidget *AuthWindow)
    {
        AuthWindow->setWindowTitle(QCoreApplication::translate("AuthWindow", "Authentication", nullptr));
        titleLabel->setText(QCoreApplication::translate("AuthWindow", "Authentication", nullptr));
        loginEdit->setPlaceholderText(QCoreApplication::translate("AuthWindow", "Login", nullptr));
        passwordEdit->setPlaceholderText(QCoreApplication::translate("AuthWindow", "Password", nullptr));
        loginButton->setText(QCoreApplication::translate("AuthWindow", "Login", nullptr));
        registerButton->setText(QCoreApplication::translate("AuthWindow", "Register", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AuthWindow: public Ui_AuthWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHWINDOW_H
