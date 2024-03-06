#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "welcomewindow.h"
#include "registerwindow.h"
#include "users.h"
#include <QKeyEvent>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    ui->label_err->setVisible(false);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    for (int i = 0; i < 100; i++) {
        if (usernames[i] != "" && usernames[i] == username) {
            if (passwords[i] != "" && passwords[i] == password) {
                hide();
                WelcomeWindow* welcomeWindow = new WelcomeWindow(username, ages[i], this);
                welcomeWindow->show();
                return;
            } else {
                break;
            }
        }
    }
    ui->label_err->setVisible(true);
    ui->lineEdit_username->setFocus();
}


void LoginWindow::keyPressEvent(QKeyEvent* pressEvent) {
    if (pressEvent->key() == Qt::Key_Return) {
        on_pushButton_login_clicked();
    }
}

void LoginWindow::on_pushButton_register_clicked()
{
    hide();
    RegisterWindow* registerWindow = new RegisterWindow(this);
    registerWindow->show();
}

