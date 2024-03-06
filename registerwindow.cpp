#include "registerwindow.h"
#include "ui_registerwindow.h"
#include <QDate>
#include "users.h"
#include <welcomewindow.h>

RegisterWindow::RegisterWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);

    ui->label_err_existing->setVisible(false);
    ui->label_err_notMatching->setVisible(false);
    ui->label_err_age->setVisible(false);
    ui->label_err_notFilled->setVisible(false);
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::on_pushButton_register_clicked()
{
    // Reseting Validation Errors
    ui->label_err_existing->setVisible(false);
    ui->label_err_notMatching->setVisible(false);
    ui->label_err_age->setVisible(false);
    ui->label_err_notFilled->setVisible(false);


    // Retrieving data from input fields
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    QString repassword = ui->lineEdit_repassword->text();
    QString sdobMonth = ui->comboBox_month->currentText();
    int idobMonth = ui->comboBox_month->currentIndex();
    int idobDay = ui->lineEdit_day->text().toInt();
    int idobYear = ui->lineEdit_year->text().toInt();
    QString gender;
    if (ui->radioButton_male->isChecked()) {
        gender = "male";
    } else if (ui->radioButton_female->isChecked()) {
        gender = "female";
    }
    QString accType;
    if (ui->radioButton_admin->isChecked()) {
        accType = "admin";
    } else if (ui->radioButton_user->isChecked()) {
        accType = "user";
    }
    bool genres[6] = {false, false, false, false, false, false};
    if (ui->checkBox_action->isChecked()) {
        genres[0] = true;
    }
    if (ui->checkBox_comedy->isChecked()) {
        genres[1] = true;
    }
    if (ui->checkBox_romance->isChecked()) {
        genres[2] = true;
    }
    if (ui->checkBox_drama->isChecked()) {
        genres[3] = true;
    }
    if (ui->checkBox_horror->isChecked()) {
        genres[4] = true;
    }
    if (ui->checkBox_other->isChecked()) {
        genres[5] = true;
    }


    // Validations
    bool valid = true;
    for (int i = 0; i < 100; i++) {
        if (username != "" && usernames[i] == username) {
            ui->label_err_existing->setVisible(true);
            ui->lineEdit_username->setFocus();
            valid = false;
            break;
        }
    }

    if (password != "" && repassword != "" && password != repassword) {
        ui->label_err_notMatching->setVisible(true);
        ui->lineEdit_password->setFocus();
        valid = false;
    }

    int age = QDate::currentDate().year() - idobYear;
    if (idobYear != 0 && idobDay != 0 && age < 12) {
        ui->label_err_age->setVisible(true);
        ui->lineEdit_year->setFocus();
        valid = false;
    }

    if (username == ""
        || password == ""
        || repassword == ""
        || idobDay == 0
        || idobYear == 0
        || (!ui->radioButton_male->isChecked() && !ui->radioButton_female->isChecked())
        || (!ui->radioButton_admin->isChecked() && !ui->radioButton_user->isChecked())
        || (genres[0] == false && genres[1] == false && genres[2] == false && genres[3] == false && genres[4] == false && genres[5] == false))
    {
        ui->label_err_notFilled->setVisible(true);
        ui->lineEdit_username->setFocus();
        valid = false;
    }


    // Registering new user
    if (valid) {
        usernames[usersCount] = username;
        passwords[usersCount] = password;
        ages[usersCount] = age;
        usersCount++;

        hide();
        WelcomeWindow* welcomeWindow = new WelcomeWindow(username, age, this);
        welcomeWindow->show();
    }
}

