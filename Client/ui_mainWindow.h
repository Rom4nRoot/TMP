/********************************************************************************
** Form generated from reading UI file 'mainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QPushButton *task1Button;
    QPushButton *task2Button;
    QPushButton *task3Button;
    QPushButton *task4Button;
    QPushButton *statButton;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(400, 400);
        verticalLayout = new QVBoxLayout(MainWindow);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(MainWindow);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        task1Button = new QPushButton(MainWindow);
        task1Button->setObjectName("task1Button");

        verticalLayout->addWidget(task1Button);

        task2Button = new QPushButton(MainWindow);
        task2Button->setObjectName("task2Button");

        verticalLayout->addWidget(task2Button);

        task3Button = new QPushButton(MainWindow);
        task3Button->setObjectName("task3Button");

        verticalLayout->addWidget(task3Button);

        task4Button = new QPushButton(MainWindow);
        task4Button->setObjectName("task4Button");

        verticalLayout->addWidget(task4Button);

        statButton = new QPushButton(MainWindow);
        statButton->setObjectName("statButton");

        verticalLayout->addWidget(statButton);


        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Tasks", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "Tasks", nullptr));
        task1Button->setText(QCoreApplication::translate("MainWindow", "Task 1 - SHA1 Hashing", nullptr));
        task2Button->setText(QCoreApplication::translate("MainWindow", "Task 2 - Newton's Method", nullptr));
        task3Button->setText(QCoreApplication::translate("MainWindow", "Task 3 - Audio Steganography", nullptr));
        task4Button->setText(QCoreApplication::translate("MainWindow", "Task 4 - Vigenere Cipher", nullptr));
        statButton->setText(QCoreApplication::translate("MainWindow", "Statistics", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
