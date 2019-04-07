#include "adminstrator.h"
#include "ui_adminstrator.h"

adminstrator::adminstrator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminstrator)
{
    ui->setupUi(this);
    this->setFixedSize(800, 600);
    this->setWindowTitle("Adminstrator");

    appendData();
    connect(ui->searchLine, SIGNAL(textChanged(QString)),this, SLOT(search()));
}


void adminstrator::appendData()
{
    tableModel = new QSqlTableModel;
    tableModel->setTable("users");
    tableModel->select();
    tableModel->removeColumn(5); //id will not be showed
    ui->usersView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
////    ui->usersView->verticalHeader()->setVisible(false);
    ui->usersView->setModel(tableModel);

}

void adminstrator::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/images/blue.png");
    painter.drawPixmap(0,0,pix);

}


void adminstrator::search()
{
    QSqlQueryModel *model=new QSqlQueryModel;
    QString search,
            data;
    search = ui->searchLine->text();
    data = "select userName as userName ,password as password,email as email, phoneNumber as "
           "phoneNumber, orderNumber as orderNumber from users where userName LIKE '%"+search+"%'";
    model->setQuery(data);
    ui->usersView->setModel(model);

}

adminstrator::~adminstrator()
{
    delete ui;
}

void adminstrator::on_pushButton_clicked()
{
    emit this->backToLogIn();
}

