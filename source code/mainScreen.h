#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>
#include <QPainter>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QDebug>
#include <QSqlError>
#include <QSqlQueryModel>
#include "updateProfile.h"
#include "clickableLabel.h"
#include "findRidePage.h"
#include "createRide.h"



namespace Ui {
class MainScreen;
}

class MainScreen : public QWidget
{
    Q_OBJECT

public:
    explicit MainScreen(QWidget *parent = 0);
    ~MainScreen();

    void paintEvent(QPaintEvent *);

    //User name entered on the connection login page
    QString usersNames;
    void init();
    void myTrips();

    updateProfile *updatePage;
    findRidePage* findRide;
    createRide* createRidePage;



signals:
    void backToLogIn();

private slots:
    void on_editBtn_clicked();

private:
    Ui::MainScreen *ui;

    QSqlDatabase dataBase;
    QSqlTableModel *tableModel;
};

#endif // MAINSCREEN_H
