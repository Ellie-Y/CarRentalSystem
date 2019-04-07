#ifndef FINDRIDEPAGE_H
#define FINDRIDEPAGE_H

#include <QMainWindow>
#include <QPainter>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>
#include <QAbstractItemModel>
#include "reserveCar.h"
#include <QString>

namespace Ui {
class findRidePage;
}

class findRidePage : public QMainWindow
{
    Q_OBJECT

public:
    explicit findRidePage(QWidget *parent = 0);
    ~findRidePage();

    void paintEvent(QPaintEvent *);

    void connectData();
    void appendData();
    void refreshData();
    QStringList getCurrentData();
    QString inputName;

signals:
    void backToMainPage();

private slots:
    void on_backBtn_clicked();

    void on_reserveBtn_clicked();

    void searchFunc();

private:
    Ui::findRidePage *ui;

    QSqlQueryModel *sqlModel;
    QSqlDatabase database;

    reserveCar* reservePage;
};

#endif // FINDRIDEPAGE_H
