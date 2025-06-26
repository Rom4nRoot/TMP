/********************************************************************************
** Form generated from reading UI file 'task2Window.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASK2WINDOW_H
#define UI_TASK2WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Task2Window
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLabel *taskLabel;
    QLineEdit *answerEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *okButton;
    QPushButton *exitButton;

    void setupUi(QWidget *Task2Window)
    {
        if (Task2Window->objectName().isEmpty())
            Task2Window->setObjectName("Task2Window");
        Task2Window->resize(500, 300);
        verticalLayout = new QVBoxLayout(Task2Window);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(Task2Window);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        taskLabel = new QLabel(Task2Window);
        taskLabel->setObjectName("taskLabel");
        taskLabel->setWordWrap(true);

        verticalLayout->addWidget(taskLabel);

        answerEdit = new QLineEdit(Task2Window);
        answerEdit->setObjectName("answerEdit");

        verticalLayout->addWidget(answerEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        okButton = new QPushButton(Task2Window);
        okButton->setObjectName("okButton");

        horizontalLayout->addWidget(okButton);

        exitButton = new QPushButton(Task2Window);
        exitButton->setObjectName("exitButton");

        horizontalLayout->addWidget(exitButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Task2Window);

        QMetaObject::connectSlotsByName(Task2Window);
    } // setupUi

    void retranslateUi(QWidget *Task2Window)
    {
        Task2Window->setWindowTitle(QCoreApplication::translate("Task2Window", "Task 2 - Newton's Method", nullptr));
        titleLabel->setText(QCoreApplication::translate("Task2Window", "Newton's Method", nullptr));
        taskLabel->setText(QCoreApplication::translate("Task2Window", "Solve the following equation using Newton's method:", nullptr));
        answerEdit->setPlaceholderText(QCoreApplication::translate("Task2Window", "Enter your answer", nullptr));
        okButton->setText(QCoreApplication::translate("Task2Window", "OK", nullptr));
        exitButton->setText(QCoreApplication::translate("Task2Window", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Task2Window: public Ui_Task2Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASK2WINDOW_H
