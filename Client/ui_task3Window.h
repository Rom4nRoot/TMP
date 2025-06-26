/********************************************************************************
** Form generated from reading UI file 'task3Window.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASK3WINDOW_H
#define UI_TASK3WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Task3Window
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLabel *descriptionLabel;
    QLineEdit *messageEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *okButton;
    QPushButton *exitButton;

    void setupUi(QWidget *Task3Window)
    {
        if (Task3Window->objectName().isEmpty())
            Task3Window->setObjectName("Task3Window");
        Task3Window->resize(500, 300);
        verticalLayout = new QVBoxLayout(Task3Window);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(Task3Window);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        descriptionLabel = new QLabel(Task3Window);
        descriptionLabel->setObjectName("descriptionLabel");
        descriptionLabel->setWordWrap(true);

        verticalLayout->addWidget(descriptionLabel);

        messageEdit = new QLineEdit(Task3Window);
        messageEdit->setObjectName("messageEdit");

        verticalLayout->addWidget(messageEdit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        okButton = new QPushButton(Task3Window);
        okButton->setObjectName("okButton");

        horizontalLayout->addWidget(okButton);

        exitButton = new QPushButton(Task3Window);
        exitButton->setObjectName("exitButton");

        horizontalLayout->addWidget(exitButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Task3Window);

        QMetaObject::connectSlotsByName(Task3Window);
    } // setupUi

    void retranslateUi(QWidget *Task3Window)
    {
        Task3Window->setWindowTitle(QCoreApplication::translate("Task3Window", "Task 3 - Audio Steganography", nullptr));
        titleLabel->setText(QCoreApplication::translate("Task3Window", "Audio Steganography", nullptr));
        descriptionLabel->setText(QCoreApplication::translate("Task3Window", "Enter a message to embed in the audio file:", nullptr));
        messageEdit->setPlaceholderText(QCoreApplication::translate("Task3Window", "Enter your message", nullptr));
        okButton->setText(QCoreApplication::translate("Task3Window", "OK", nullptr));
        exitButton->setText(QCoreApplication::translate("Task3Window", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Task3Window: public Ui_Task3Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASK3WINDOW_H
