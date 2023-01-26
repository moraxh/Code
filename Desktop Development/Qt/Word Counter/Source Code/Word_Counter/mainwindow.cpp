#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::word_counter(QString _text)
{
    int length = _text.length();
    bool last_is_char = false;
    int nword = 0;

    for (int i = 0; i < length; i++)
    {
        if(_text[i] == ' ' || _text[i] == '\n')
            last_is_char = false;
        else if(!last_is_char)
        {
            nword ++;
            last_is_char = true;
        }


    }
    return nword;
}

void MainWindow::on_Pte_textChanged()
{
    QString text = ui->Pte->toPlainText();

    int nchar = text.length();
    int nword = word_counter(text); // XD


    // Text Generator
    QString counter_text = "";
    counter_text.append(QString::number(nword));

    if (nword == 1)
        counter_text.append(" word, ");
    else
        counter_text.append(" words, ");

    counter_text.append(QString::number(nchar));
    if (nchar == 1)
        counter_text.append(" character");
    else
        counter_text.append(" characters");

    ui->Counter->setText(counter_text);
}

