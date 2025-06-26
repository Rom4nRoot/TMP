/********************************************************************************
** Form generated from reading UI file 'task4Window.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASK4WINDOW_H
#define UI_TASK4WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Task4Window
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLabel *taskLabel;
    QLineEdit *answerEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *okButton;
    QPushButton *exitButton;

    void setupUi(QWidget *Task4Window)
    {
        if (Task4Window->objectName().isEmpty())
            Task4Window->setObjectName("Task4Window");
        Task4Window->resize(500, 300);
        verticalLayout = new QVBoxLayout(Task4Window);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(Task4Window);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        taskLabel = new QLabel(Task4Window);
        taskLabel->setObjectName("taskLabel");
        taskLabel->setWordWrap(true);

        verticalLayout->addWidget(taskLabel);

        answerEdit = new QLineEdit(Task4Window);
        answerEdit->setObjectName("answerEdit");

        verticalLayout->addWidget(answerEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        okButton = new QPushButton(Task4Window);
        okButton->setObjectName("okButton");

        horizontalLayout->addWidget(okButton);

        exitButton = new QPushButton(Task4Window);
        exitButton->setObjectName("exitButton");

        horizontalLayout->addWidget(exitButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Task4Window);

        QMetaObject::connectSlotsByName(Task4Window);
    } // setupUi

    void retranslateUi(QWidget *Task4Window)
    {
        Task4Window->setWindowTitle(QCoreApplication::translate("Task4Window", "Task 4 - Vigenere Cipher", nullptr));
        titleLabel->setText(QCoreApplication::translate("Task4Window", "Vigenere Cipher", nullptr));
        taskLabel->setText(QCoreApplication::translate("Task4Window", "Decrypt the following message using the Vigenere cipher:", nullptr));
        answerEdit->setPlaceholderText(QCoreApplication::translate("Task4Window", "Enter your answer", nullptr));
        okButton->setText(QCoreApplication::translate("Task4Window", "OK", nullptr));
        exitButton->setText(QCoreApplication::translate("Task4Window", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Task4Window: public Ui_Task4Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASK4WINDOW_H
