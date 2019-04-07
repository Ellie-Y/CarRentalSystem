#include "updateProfile.h"
#include "ui_updateProfile.h"

updateProfile::updateProfile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updateProfile)
{
    ui->setupUi(this);
    this->setFixedSize(350, 400);   //fix screen size
    this->setWindowTitle("Change profile");
}

updateProfile::~updateProfile()
{
    delete ui;
}

void updateProfile::paintEvent(QPaintEvent *)
{
    //set background image
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/images/rose2.png");
    painter.drawPixmap(0,0,pix);

}

void updateProfile::on_updateBtn_clicked()
{

    //get the input of users
    QString currentName = ui->currentlName->text();
    QString newEmail = ui->newEmail->text();
    QString newPhone = ui->newPhoneNumber->text();
    QString newPassword = ui->newPassword->text();


    QString getData;
    //count（*） is to determine how many the currentName have in database
    getData = "select count (*) from users where userName='"+currentName+"'";
    QSqlQueryModel *modelx = new QSqlQueryModel;
    modelx->setQuery(getData);
    QModelIndex index1 = modelx->index(0,0);
    if(index1.data() == 0)
    {
        QMessageBox::information(this, "change failed", "Change failed, Check your name");
    }
    else if(currentName.isEmpty() || newEmail.isEmpty() || newPhone.isEmpty() || newPassword.isEmpty())
    {
        QMessageBox::about(this, "change failed", "Please fill in all the information");
    }
    else
    {
        QString getData2;
        QSqlQueryModel *model2 = new QSqlQueryModel;
        getData2 = "update users set email ='"+newEmail+"',phoneNumber='"+newPhone+"',"
                    "password='"+newPassword+"' where userName='"+currentName+"'";
        model2->setQuery(getData2);

        QMessageBox::information(this, "successed", "update successed");
        this->hide();
    }

}


void updateProfile::on_cancelBtn_clicked()
{
    this->hide();
}
