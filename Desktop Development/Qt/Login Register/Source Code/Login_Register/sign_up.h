#ifndef SIGN_UP_H
#define SIGN_UP_H

#include <QWidget>
#include <QKeyEvent>

namespace Ui {
class Sign_up;
}

class Sign_up : public QWidget
{
    Q_OBJECT

public:
    explicit Sign_up(QWidget *parent = nullptr);
    ~Sign_up();

    void sign_up(QString _name, QString _email, QString _password);

    int user_exists(QString _email, QString _password);

    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_show_clicked();

    void on_le_password_textChanged(const QString &arg1);

    void on_sign_in_clicked();

    void on_close_clicked();

    void on_back_clicked();

    void on_next_clicked();

private:
    Ui::Sign_up *ui;
};

#endif // SIGN_UP_H
