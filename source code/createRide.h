#ifndef CREATERIDE_H
#define CREATERIDE_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QPainter>
#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>

namespace Ui {
class createRide;
}

class createRide : public QDialog
{
    Q_OBJECT

public:
    explicit createRide(QWidget *parent = 0);
    ~createRide();

    void paintEvent(QPaintEvent *);
    void clearInput();

private slots:
    void on_submitBtn_clicked();
    void getInput();

private:
    Ui::createRide *ui;

    QSqlQuery sql;

    QString newCarName;
    QString newCarModel;
    QString newCarCapacity;
    QString newCarEngine;
    QString newCarColor;
    QString newCarOwner;

};

#endif // CREATERIDE_H
