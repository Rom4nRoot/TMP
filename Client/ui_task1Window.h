/********************************************************************************
** Form generated from reading UI file 'task1Window.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASK1WINDOW_H
#define UI_TASK1WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Task1Window
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLabel *taskLabel;
    QLineEdit *answerEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *okButton;
    QPushButton *exitButton;

    void setupUi(QWidget *Task1Window)
    {
        if (Task1Window->objectName().isEmpty())
            Task1Window->setObjectName("Task1Window");
        Task1Window->resize(500, 300);
        verticalLayout = new QVBoxLayout(Task1Window);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(Task1Window);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        taskLabel = new QLabel(Task1Window);
        taskLabel->setObjectName("taskLabel");
        taskLabel->setWordWrap(true);

        verticalLayout->addWidget(taskLabel);

        answerEdit = new QLineEdit(Task1Window);
        answerEdit->setObjectName("answerEdit");

        verticalLayout->addWidget(answerEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        okButton = new QPushButton(Task1Window);
        okButton->setObjectName("okButton");

        horizontalLayout->addWidget(okButton);

        exitButton = new QPushButton(Task1Window);
        exitButton->setObjectName("exitButton");

        horizontalLayout->addWidget(exitButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Task1Window);

        QMetaObject::connectSlotsByName(Task1Window);
    } // setupUi

    void retranslateUi(QWidget *Task1Window)
    {
        Task1Window->setWindowTitle(QCoreApplication::translate("Task1Window", "Task 1 - SHA1 Hashing", nullptr));
        titleLabel->setText(QCoreApplication::translate("Task1Window", "SHA1 Hashing", nullptr));
        taskLabel->setText(QCoreApplication::translate("Task1Window", "Hash the following text using SHA1:", nullptr));
        answerEdit->setPlaceholderText(QCoreApplication::translate("Task1Window", "Enter your answer", nullptr));
        okButton->setText(QCoreApplication::translate("Task1Window", "OK", nullptr));
        exitButton->setText(QCoreApplication::translate("Task1Window", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Task1Window: public Ui_Task1Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASK1WINDOW_H
