#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include <QMainWindow>
#include <QRegularExpressionValidator>
#include <QDebug>
#include <QtSql>
#include <QMessageBox>
#include <QFontDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void prepare_table();

    int user_exists(QString _email, QString _password);

private slots:

    void on_close_clicked();

    void on_show_clicked();

    void on_le_password_textChanged(const QString &arg1);

    void on_sign_up_clicked();

    void on_next_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
