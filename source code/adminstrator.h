#ifndef ADMINSTRATOR_H
#define ADMINSTRATOR_H

#include <QWidget>
#include <QtSql>
#include <QSqlTableModel>
#include <QPainter>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class adminstrator;
}

class adminstrator : public QWidget
{
    Q_OBJECT

public:
    explicit adminstrator(QWidget *parent = 0);
    ~adminstrator();

    void appendData();
    void paintEvent(QPaintEvent *);


private slots:
    void search();

    void on_pushButton_clicked();


signals:
    void backToLogIn();

private:
    Ui::adminstrator *ui;

    QSqlTableModel* tableModel;
};

#endif // ADMINSTRATOR_H
