#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();

    QString getLogin() const { return loginEdit->text().trimmed(); }
    QString getPassword() const { return passwordEdit->text().trimmed(); }

private slots:
    void onOkClicked();
    void onCancelClicked();

private:
    void setupUI();

    QVBoxLayout* mainLayout;
    QLineEdit* loginEdit;
    QLineEdit* passwordEdit;
    QLineEdit* confirmPasswordEdit;
    QPushButton* okButton;
    QPushButton* cancelButton;
    
    Ui::RegisterDialog *ui;
};

#endif // REGISTERDIALOG_H
