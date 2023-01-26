#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    double convert(int _c1, int _c2, double num);

    void change_prefix(int a, int index);

    void equalto(int _c1, int _c2);

private slots:
    void on_Dsba_valueChanged(double arg1);

    void on_Dsbb_valueChanged(double arg1);

    void on_Cba_currentIndexChanged(int index);

    void on_Cbb_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
