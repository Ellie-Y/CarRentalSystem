#ifndef RESERVECAR_H
#define RESERVECAR_H
#include <QDialog>
#include <QStringList>
#include <QPainter>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QSqlDatabase>
#include <QDateTime>
#include <QtGlobal>

namespace Ui {
class reserveCar;
}



class reserveCar : public QDialog
{
    Q_OBJECT

public:
    explicit reserveCar(QWidget *parent = 0);
    ~reserveCar();

    void setReserveData(QStringList rowData);
    void paintEvent(QPaintEvent *);
    void confirm_Button_On();

    QString inputName;
    QString generateOrderNumber(int length);

private:
    Ui::reserveCar *ui;

};

#endif // RESERVECAR_H
