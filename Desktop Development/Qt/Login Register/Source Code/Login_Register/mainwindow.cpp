#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sign_up.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Delete frame
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);

    // Regex email
    QRegularExpression rx_email("^[a-zA-Z0-9.!#$%&’*+/=?^_`{|}~-]+@[a-zA-Z0-9-]+(?:\\.[a-zA-Z0-9-]+)*$");
    QRegularExpressionValidator *val_email = new QRegularExpressionValidator(rx_email, this);

    // Prepare line edits
    ui->le_email->setValidator(val_email);

    ui->le_password->setEchoMode(QLineEdit::Password);
    ui->le_password->setText("");
    this->on_le_password_textChanged("");

    ui->success->setVisible(false);

    // Load Fonts
    QFontDatabase::addApplicationFont(":/Others/Assets/Fonts/Fira Code Regular Nerd Font Complete.ttf");
    QFontDatabase::addApplicationFont(":/Others/Assets/Fonts/SF-Pro-Text-Bold.otf");
    QFontDatabase::addApplicationFont(":/Others/Assets/Fonts/SF-Pro-Text-Regular.otf");
    QFontDatabase::addApplicationFont(":/Others/Assets/Fonts/SF-Pro-Text-Semibold.otf");
    QFontDatabase::addApplicationFont(":/Others/Assets/Fonts/SFUIText-Regular.otf");

    //  Create database
    QString path = "main.sqlite";
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName(path);

    if (!dbase.open())
            qDebug() << "Database fail";

    // Create Table
    prepare_table();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::prepare_table()
{
    QString command;
    QSqlQuery create;

    command.append("CREATE TABLE if not exists data("
                   "id integer primary key autoincrement not null,"
                   " name text not null,"
                   " email text not null,"
                   " password text not null);");

    create.prepare(command);

    if (!create.exec())
        qDebug() << "Table cannot be created";
}

int MainWindow::user_exists(QString _email, QString _password)
{
    QSqlQuery search;

    QString temp_pass;
    QString temp_email;
    QString command;
    command.append("select * from data where email = '" + _email + "';");

    search.prepare(command);
    search.exec();

    while (search.next())
    {
        temp_email = search.value(2).toByteArray().constData();
        temp_pass  = search.value(3).toByteArray().constData();
    }

    // 0 email and password match, 1 email doesnt exists, 2 password is incorrect
    if (_email == temp_email)
    {
        if (_password == temp_pass)
        {
            return 0;
        }
        else
         {
            return 2;
         }
    }
    else
    {
        return 1;
    }
}

/*
 ______               _
|  ____|             | |
| |____   _____ _ __ | |_ ___
|  __\ \ / / _ \ '_ \| __/ __|
| |___\ V /  __/ | | | |_\__ \
|______\_/ \___|_| |_|\__|___/

*/

void MainWindow::on_close_clicked()
{
    QCoreApplication::quit();
}


void MainWindow::on_show_clicked()
{
    if (ui->show->text() == "")
        ui->show->setText("");
    else
        ui->show->setText("");

    if (ui->le_password->echoMode() == QLineEdit::Password)
        ui->le_password->setEchoMode(QLineEdit::Normal);
    else
        ui->le_password->setEchoMode(QLineEdit::Password);
}


void MainWindow::on_le_password_textChanged(const QString &arg1)
{
    if (arg1 == "")
        ui->show->setVisible(false);
    else
        ui->show->setVisible(true);
}

void MainWindow::on_sign_up_clicked()
{
    Sign_up *r = new Sign_up();
    hide();
    r->show();
}


void MainWindow::on_next_clicked()
{
    bool error = false;

    QString error_ss = "border: none;"
            "border-bottom: 1px solid red;"
            "background-color: transparent;"
            "padding-bottom: 10px;"
            "font: 63 10pt 'SF Pro Text';";

    QString normal_ss = "border: none;"
            "border-bottom: 1px solid rgb(243,240,236);"
            "background-color: transparent;"
            "padding-bottom: 10px;"
            "font: 63 10pt 'SF Pro Text';";

    if (ui->le_email->text() == "")
    {
        ui->Error1->setText("Please enter your email");
        ui->le_email->setStyleSheet(error_ss);
        error = true;
    }
    else
    {
        ui->Error1->setText("");
        ui->le_email->setStyleSheet(normal_ss);
    }

    if (ui->le_password->text() == "")
    {
        ui->Error2->setText("Please enter your password");
        ui->le_password->setStyleSheet(error_ss);
        error = true;
    }
    else
    {
        ui->Error2->setText("");
        ui->le_password->setStyleSheet(normal_ss);
    }

    if (!error)
    {
        QString email = ui->le_email->text();
        QString pass  = ui->le_password->text();
        switch (user_exists(email, pass)) {
            case 0:
                    ui->success->setVisible(true);
                break;
            case 1:
                ui->Error1->setText("The email doesnt exists");
                ui->success->setVisible(false);
                break;
            case 2:
                ui->Error2->setText("The password is incorrect");
                ui->success->setVisible(false);
                break;
        }
    }
    else
    {
        ui->success->setVisible(false);
    }
}
