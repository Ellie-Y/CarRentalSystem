#ifndef SIGN_IN_H
#define SIGN_IN_H

#include <QMessageBox>
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QPainter>

namespace Ui {
class Sign_In;
}

class Sign_In : public QWidget
{
    Q_OBJECT

public:
    explicit Sign_In(QWidget *parent = 0);
    ~Sign_In();

    void paintEvent(QPaintEvent *);
    void cleanLineEdit();
    void connectDatabase();
    void insertData();

signals:
    //signals no need to complement
    void backLogIn();

private slots:
    void on_signBtn_clicked();
    void getInput();

private:
    Ui::Sign_In *ui;
    QSqlDatabase myData;

    QString signName;
    QString signPassword;
    QString signEmail;
    QString signPhone;


};

#endif // SIGN_IN_H
