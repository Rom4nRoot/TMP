/********************************************************************************
** Form generated from reading UI file 'statWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATWINDOW_H
#define UI_STATWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StatWindow
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLabel *task1Label;
    QLabel *task2Label;
    QLabel *task3Label;
    QLabel *task4Label;
    QPushButton *exitButton;

    void setupUi(QWidget *StatWindow)
    {
        if (StatWindow->objectName().isEmpty())
            StatWindow->setObjectName("StatWindow");
        StatWindow->resize(400, 300);
        verticalLayout = new QVBoxLayout(StatWindow);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(StatWindow);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        task1Label = new QLabel(StatWindow);
        task1Label->setObjectName("task1Label");

        verticalLayout->addWidget(task1Label);

        task2Label = new QLabel(StatWindow);
        task2Label->setObjectName("task2Label");

        verticalLayout->addWidget(task2Label);

        task3Label = new QLabel(StatWindow);
        task3Label->setObjectName("task3Label");

        verticalLayout->addWidget(task3Label);

        task4Label = new QLabel(StatWindow);
        task4Label->setObjectName("task4Label");

        verticalLayout->addWidget(task4Label);

        exitButton = new QPushButton(StatWindow);
        exitButton->setObjectName("exitButton");

        verticalLayout->addWidget(exitButton);


        retranslateUi(StatWindow);

        QMetaObject::connectSlotsByName(StatWindow);
    } // setupUi

    void retranslateUi(QWidget *StatWindow)
    {
        StatWindow->setWindowTitle(QCoreApplication::translate("StatWindow", "Statistics", nullptr));
        titleLabel->setText(QCoreApplication::translate("StatWindow", "Statistics", nullptr));
        task1Label->setText(QCoreApplication::translate("StatWindow", "Task 1: 0 correct, 0 incorrect", nullptr));
        task2Label->setText(QCoreApplication::translate("StatWindow", "Task 2: 0 correct, 0 incorrect", nullptr));
        task3Label->setText(QCoreApplication::translate("StatWindow", "Task 3: 0 correct, 0 incorrect", nullptr));
        task4Label->setText(QCoreApplication::translate("StatWindow", "Task 4: 0 correct, 0 incorrect", nullptr));
        exitButton->setText(QCoreApplication::translate("StatWindow", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StatWindow: public Ui_StatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATWINDOW_H
