#include "sign_up.h"
#include "ui_sign_up.h"
#include "mainwindow.h"

Sign_up::Sign_up(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sign_up)
{
    ui->setupUi(this);

    //Delete frame
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);

    // Regex email
    QRegularExpression rx_email("^[a-zA-Z0-9.!#$%&’*+/=?^_`{|}~-]+@[a-zA-Z0-9-]+(?:\\.[a-zA-Z0-9-]+)*$");
    QRegularExpressionValidator *val_email = new QRegularExpressionValidator(rx_email, this);

    // Prepare line edits
    ui->le_email->setValidator(val_email);

    ui->le_password->setEchoMode(QLineEdit::Normal);
    ui->le_password->setText("");
    this->on_le_password_textChanged("");

    ui->success->setVisible(false);

    // Load Fonts
    QFontDatabase::addApplicationFont(":/Others/Assets/Fonts/Fira Code Regular Nerd Font Complete.ttf");
    QFontDatabase::addApplicationFont(":/Others/Assets/Fonts/SF-Pro-Text-Bold.otf");
    QFontDatabase::addApplicationFont(":/Others/Assets/Fonts/SF-Pro-Text-Regular.otf");
    QFontDatabase::addApplicationFont(":/Others/Assets/Fonts/SF-Pro-Text-Semibold.otf");
    QFontDatabase::addApplicationFont(":/Others/Assets/Fonts/SFUIText-Regular.otf");

}

Sign_up::~Sign_up()
{
    delete ui;
}

void Sign_up::sign_up(QString _name, QString _email, QString _password)
{
    QSqlQuery signup;

    QString command = "insert into data(name, email, password) values( '" + _name + "','" + _email + "', '" + _password + "');";

    signup.prepare(command);
    signup.exec();
}

int Sign_up::user_exists(QString _email, QString _password)
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

void Sign_up::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
        this->on_next_clicked();
}

/*
 ______               _
|  ____|             | |
| |____   _____ _ __ | |_ ___
|  __\ \ / / _ \ '_ \| __/ __|
| |___\ V /  __/ | | | |_\__ \
|______\_/ \___|_| |_|\__|___/

*/

void Sign_up::on_show_clicked()
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

void Sign_up::on_le_password_textChanged(const QString &arg1)
{
    if (arg1 == "")
        ui->show->setVisible(false);
    else
        ui->show->setVisible(true);
}


void Sign_up::on_sign_in_clicked()
{
    hide();
    MainWindow *r = new MainWindow();
    r->show();
}


void Sign_up::on_close_clicked()
{
    QCoreApplication::quit();
}


void Sign_up::on_back_clicked()
{
    hide();
    MainWindow *r = new MainWindow();
    r->show();
}


void Sign_up::on_next_clicked()
{
    bool error = false;

    QString error_ss = "QLineEdit {"
                       "border: none;"
                       "border-bottom: 1px solid red;"
                       "background-color: transparent;"
                       "padding-bottom: 10px;}";

    QString normal_ss = "QLineEdit {"
                        "border: none;"
                        "border-bottom: 1px solid rgb(243,240,236);"
                        "background-color: transparent;"
                        "padding-bottom: 10px;}";

    // Check if line edit is empty

    // Name
    if (ui->le_name->text() == "")
    {
        ui->Error1->setText("Please enter your name");
        ui->le_name->setStyleSheet(error_ss);
        error = true;
    }
    else
    {
        ui->Error1->setText("");
        ui->le_name->setStyleSheet(normal_ss);
    }

    // Email
    if (ui->le_email->text() == "")
    {
        ui->Error2->setText("Please enter your email");
        ui->le_email->setStyleSheet(error_ss);
        error = true;
    }
    else
    {
        QString email = ui->le_email->text();
        if (user_exists(email, "") == 2)
        {
            ui->Error2->setText("This email already exists");
            ui->le_email->setStyleSheet(error_ss);
            error = true;
        }
        else
        {
            ui->Error2->setText("");
            ui->le_email->setStyleSheet(normal_ss);
        }
    }

    // Password
    if (ui->le_password->text() == "")
    {
        ui->Error3->setText("Please enter your password");
        ui->le_password->setStyleSheet(error_ss);
        error = true;
    }
    else
    {
        ui->Error3->setText("");
        ui->le_password->setStyleSheet(normal_ss);
    }

    // Register user
    if (!error)
    {
        QString name        = ui->le_name->text();
        QString email       = ui->le_email->text();
        QString password    = ui->le_password->text();

        sign_up(name, email, password);

        ui->success->setVisible(true);

        // Clear line edits
        ui->le_name->setText("");
        ui->le_email->setText("");
        ui->le_password->setText("");
    }
    else
    {
        ui->success->setVisible(false);
    }
}

