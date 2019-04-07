#ifndef UPDATEPROFILE_H
#define UPDATEPROFILE_H

#include <QDialog>
#include <QPainter>
#include <QSqlQueryModel>
#include <QMessageBox>

namespace Ui {
class updateProfile;
}

class updateProfile : public QDialog
{
    Q_OBJECT

public:
    explicit updateProfile(QWidget *parent = 0);
    ~updateProfile();

    void paintEvent(QPaintEvent *);


private slots:
    void on_updateBtn_clicked();

    void on_cancelBtn_clicked();


private:
    Ui::updateProfile *ui;


};

#endif // UPDATEPROFILE_H
