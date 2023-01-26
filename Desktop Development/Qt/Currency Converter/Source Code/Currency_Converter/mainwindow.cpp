#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDoubleValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ComboBox
    ui->Cba->setModelColumn(0);

    ui->Cba->setItemIcon(0, QIcon(":/images/Assets/flags/usd.svg"));
    ui->Cba->setItemIcon(1, QIcon(":/images/Assets/flags/eur.svg"));
    ui->Cba->setItemIcon(2, QIcon(":/images/Assets/flags/gbp.svg"));
    ui->Cba->setItemIcon(3, QIcon(":/images/Assets/flags/chf.svg"));
    ui->Cba->setItemIcon(4, QIcon(":/images/Assets/flags/cad.svg"));
    ui->Cba->setItemIcon(5, QIcon(":/images/Assets/flags/zar.svg"));
    ui->Cba->setItemIcon(6, QIcon(":/images/Assets/flags/mxn.svg"));
    ui->Cba->setItemIcon(7, QIcon(":/images/Assets/flags/inr.svg"));
    ui->Cba->setItemIcon(8, QIcon(":/images/Assets/flags/jpy.svg"));
    ui->Cba->setItemIcon(9, QIcon(":/images/Assets/flags/cny.svg"));
    ui->Cba->setIconSize(QSize(17, 17));

    ui->Cbb->setModelColumn(0);

    ui->Cbb->setItemIcon(0, QIcon(":/images/Assets/flags/usd.svg"));
    ui->Cbb->setItemIcon(1, QIcon(":/images/Assets/flags/eur.svg"));
    ui->Cbb->setItemIcon(2, QIcon(":/images/Assets/flags/gbp.svg"));
    ui->Cbb->setItemIcon(3, QIcon(":/images/Assets/flags/chf.svg"));
    ui->Cbb->setItemIcon(4, QIcon(":/images/Assets/flags/cad.svg"));
    ui->Cbb->setItemIcon(5, QIcon(":/images/Assets/flags/zar.svg"));
    ui->Cbb->setItemIcon(6, QIcon(":/images/Assets/flags/mxn.svg"));
    ui->Cbb->setItemIcon(7, QIcon(":/images/Assets/flags/inr.svg"));
    ui->Cbb->setItemIcon(8, QIcon(":/images/Assets/flags/jpy.svg"));
    ui->Cbb->setItemIcon(9, QIcon(":/images/Assets/flags/cny.svg"));
    ui->Cbb->setIconSize(QSize(17, 17));

    // Line Edit
    ui->Dsba->setValue(0.0);
    ui->Dsbb->setValue(0.0);

    int b = ui->Cbb->currentIndex();
    int a = ui->Cba->currentIndex();

    equalto(a, b);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Dsba_valueChanged(double arg1)
{
    int a = ui->Cba->currentIndex();
    int b = ui->Cbb->currentIndex();

    ui->Dsbb->setValue(convert(a, b, arg1));
}

void MainWindow::on_Dsbb_valueChanged(double arg1)
{
    int a = ui->Cba->currentIndex();
    int b = ui->Cbb->currentIndex();

    ui->Dsba->setValue(convert(b, a, arg1));
}

void MainWindow::on_Cba_currentIndexChanged(int index)
{
    int     b = ui->Cbb->currentIndex();
    double  num = ui->Dsba->value();

    ui->Dsbb->setValue(convert(index, b, num));
    change_prefix(1, index);
    equalto(index, b);
}

void MainWindow::on_Cbb_currentIndexChanged(int index)
{
    int     a = ui->Cba->currentIndex();
    double  num = ui->Dsbb->value();

    ui->Dsba->setValue(convert(index, a, num));
    change_prefix(2, index);
    equalto(a, index);
}

double MainWindow::convert(int _c1, int _c2, double num)
{   //                       USD  EURO       GBP       CHF        CAD         ZAR          MXN          INR          JPY           CNY
    double currencies[10] = {1.0, 1.1631742, 1.375634, 1.0837848, 0.80953148, 0.068208822, 0.049065588, 0.013296287, 0.0087551897, 0.15581922};
    double res = (currencies[_c1] / currencies[_c2]) * num;

    return res;
}

void MainWindow::change_prefix(int a, int index)
{
    const std::string prefix[10] = {" $ ", " € ", " £ ", " CHF ", " $ ", " R ", " $ ", " INR ", " ¥ ", " ¥ "};

    if (a == 1)
    {
        ui->Dsba->setPrefix(QString::fromStdString(prefix[index]));
    }
    else {
        ui->Dsbb->setPrefix(QString::fromStdString(prefix[index]));
    }
}

void MainWindow::equalto(int _c1, int _c2)
{
    //                       USD  EURO       GBP       CHF        CAD         ZAR          MXN          INR          JPY           CNY
    double currencies[10] = {1.0, 1.1631742, 1.375634, 1.0837848, 0.80953148, 0.068208822, 0.049065588, 0.013296287, 0.0087551897, 0.15581922};
    std::string prefix[10] = {"USD", "EUR", "GBP", "CHF", "CAD", "ZAR", "MXN", "INR", "JPY", "CNY"};

    double conv1 = currencies[_c1] / currencies[_c2];
    double conv2 = currencies[_c2] / currencies[_c1];

    std::string label1 = "1 " + prefix[_c1] + " = " + std::to_string(conv1) + " " + prefix[_c2];

    ui->La->setText(QString::fromStdString(label1));

    std::string label2 = "1 " + prefix[_c2] + " = " + std::to_string(conv2) + " " + prefix[_c1];

    ui->Lb->setText(QString::fromStdString(label2));
}
