#include "reserveCar.h"
#include "ui_reserveCar.h"


reserveCar::reserveCar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reserveCar)
{
    ui->setupUi(this);
    this->setFixedSize(500, 500);   //fix screen size
    this->setWindowTitle("Reserve Cars");

    connect(ui->confirmBtn, &clickableLabel::clicked, [=](){
        confirm_Button_On();
    });

}

reserveCar::~reserveCar()
{
    delete ui;
}

void reserveCar::setReserveData(QStringList rowData)
{
    ui->carName->setText(rowData.at(0));
    ui->carModel->setText(rowData.at(1));
    ui->carSeats->setText(rowData.at(2));
    ui->carEngine->setText(rowData.at(3) + "L");
    ui->carColour->setText(rowData.at(4));
    ui->carOwner->setText(rowData.at(5));
}

void reserveCar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/images/white.png");
    painter.drawPixmap(0,0,pix);

}

void reserveCar::confirm_Button_On()
{
    qDebug() <<inputName;
    QString orderNumber = generateOrderNumber(6);
    QMessageBox::information(this, "Order Number", "Thank you! "
                            "Your order number is: " + orderNumber);
    QString orders;
    orders = QString("Update users "
                     "set orderNumber = '"+orderNumber+"' Where userName = '"+inputName+"' ");

    QSqlQuery sql;
    if(sql.exec(orders)) {
        qDebug() <<"Update successed";
    }
    else {
        qDebug() <<"failed to get Order Number";
        qDebug() <<sql.lastError();
    }

}

QString reserveCar::generateOrderNumber(int length)
{
    qsrand(QDateTime::currentMSecsSinceEpoch());
    const char chrs[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        int chrs_size = sizeof(chrs);

        char* ch = new char[length + 1];
        memset(ch, 0, length + 1);
        int randomx = 0;
        for (int i = 0; i < length; ++i)
        {
            randomx= rand() % (chrs_size - 1);
            ch[i] = chrs[randomx];
        }
        QString ret(ch);
        delete[] ch;
        return ret;
}
