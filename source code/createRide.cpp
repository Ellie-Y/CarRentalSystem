#include "createRide.h"
#include "ui_createRide.h"


createRide::createRide(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createRide)
{
    ui->setupUi(this);
    this->setWindowTitle("Create new ride");


}

createRide::~createRide()
{
    delete ui;
}

void createRide::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/images/rose2.png");
    painter.drawPixmap(0,0,pix);

}

void createRide::on_submitBtn_clicked()
{
//    QString appendData;
//    appendData = "Insert into vehicles (carName,carModel,carCapacity,engineCapacity,colour,carOwner) "
//                 "values('"+newCarName+"','"+newCarModel+"','"+newCarCapacity+"','"+newCarEngine+"','"
//                          +newCarColor+"','"+newCarOwner+"')";
//     QSqlQueryModel *model = new QSqlQueryModel;
    getInput();
    //retrieve data from database
    sql.prepare("Insert Into vehicles(carName,carModel,carCapacity,engineCapacity,colour,carOwner)"
                "Values (:carName, :carModel, :carCapacity, :engineCapacity, :colour, :carOwner)");
    sql.bindValue(":carName", newCarName);
    sql.bindValue(":carModel", newCarModel);
    sql.bindValue(":carCapacity", newCarCapacity);
    sql.bindValue(":engineCapacity", newCarEngine);
    sql.bindValue(":colour", newCarColor);
    sql.bindValue(":carOwner", newCarOwner);

    if(newCarName.isEmpty() || newCarModel.isEmpty() || newCarEngine.isEmpty()
            || newCarColor.isEmpty() || newCarOwner.isEmpty())
    {
        QMessageBox::information(this, "failed", "please fill in all inforamtion");
    }
    else if(sql.exec())
    {
        QMessageBox::information(this, "Submited", "Submited successful");
        this->hide();
        clearInput();
    }
    else
    {
         QMessageBox::about(this, "failed", "Submited failed, please check all the informations");
         qDebug()<<sql.lastError();
    }

}

void createRide::getInput()
{
    newCarName = ui->carName->text();
    newCarModel = ui->carModel->text();
    newCarCapacity = ui->carCapacity->text();
    newCarEngine = ui->carEngine->text();
    newCarColor = ui->carColor->text();
    newCarOwner = ui->carOwner->text();
}

void createRide::clearInput()
{
    ui->carName->clear();
    ui->carModel->clear();
    ui->carCapacity->clear();
    ui->carEngine->clear();
    ui->carColor->clear();
    ui->carOwner->clear();
}

