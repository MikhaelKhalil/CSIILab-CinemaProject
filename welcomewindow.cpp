#include "welcomewindow.h"
#include "ui_welcomewindow.h"
#include "loginwindow.h"

WelcomeWindow::WelcomeWindow(QString username, int age, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::WelcomeWindow)
{
    ui->setupUi(this);

    ui->label_welcome->setText("Hello " + username + " " + QString::number(age) + ",");

    QPixmap img(":/assets/imgs/welcome2.jpg");
    int width = ui->label_img->width();
    int height = ui->label_img->height();
    ui->label_img->setPixmap(img.scaled(width, height, Qt::KeepAspectRatio));
}

WelcomeWindow::~WelcomeWindow()
{
    delete ui;
}

void WelcomeWindow::on_pushButton_logout_clicked()
{
    hide();
    LoginWindow* loginWindow = new LoginWindow(this);
    loginWindow->show();
}

