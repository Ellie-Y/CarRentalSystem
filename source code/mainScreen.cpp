#include "mainScreen.h"
#include "ui_mainScreen.h"

MainScreen::MainScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainScreen)
{
    ui->setupUi(this);
    this->setFixedSize(1100, 700);   //fix screen size
    this->setWindowTitle("Main Page");

    updatePage = new updateProfile;
    findRide = new findRidePage;

   //Widget default by the second screen
    ui->stackedWidget->setCurrentIndex(1);
    //switch to my trip
    connect(ui->tripsBtn, &QPushButton::clicked, [=](){
        myTrips();
        ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->backAccountBtn, &QPushButton::clicked, [=](){
        ui->stackedWidget->setCurrentIndex(1);
    });


    connect(ui->goBack, &clickableLabel::clicked, [=](){
        emit this->backToLogIn();
       //emit reminds it is signal
    });

    //go to reserve interface
    connect(ui->findRideBtn, &QPushButton::clicked, [=](){
        findRide->inputName = usersNames;
        findRide->show();
        this->hide();
    });

    connect(findRide, &findRidePage::backToMainPage, [=](){
        findRide->hide();
        this->show();
    });

   createRidePage = new createRide;
   connect(ui->creatRideBtn, &QPushButton::clicked, [=](){
       createRidePage->show();
   });

}

void MainScreen::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/images/rose2.png");
    painter.drawPixmap(0,0,pix);
}

void MainScreen::init()
{
    //testing if get username from login class
    qDebug() <<usersNames;
    QString sql_user;
//    To get the name, email, phone number separately, because the areas of table view are not together
    sql_user ="select userName as userName from users where userName='"+usersNames+"'";
    QSqlQueryModel *sqlModel = new QSqlQueryModel;
    sqlModel->setQuery(sql_user);\
    ui->showUserName->horizontalHeader()->setVisible(false);
    ui->showUserName->verticalHeader()->setVisible(false);
    ui->showUserName->setShowGrid(false);
    ui->showUserName->setModel(sqlModel);

    //for phone number
    QString sql_user2;
    sql_user2 ="select phoneNumber as phoneNumber from users where userName='"+usersNames+"'";
    QSqlQueryModel *sqlModel2 = new QSqlQueryModel;
    sqlModel2->setQuery(sql_user2);
    ui->showPhoneNumber->horizontalHeader()->setVisible(false);
    ui->showPhoneNumber->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->showPhoneNumber->verticalHeader()->setVisible(false);
    ui->showPhoneNumber->setShowGrid(false);
    ui->showPhoneNumber->setModel(sqlModel2);

//    //for email
    QString sql_user3;
    sql_user3 ="select email as Email from users where userName='"+usersNames+"'";
    QSqlQueryModel *sqlModel3 = new QSqlQueryModel;
    sqlModel3->setQuery(sql_user3);\
    ui->showEmail->horizontalHeader()->setVisible(false);
    ui->showEmail->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->showEmail->verticalHeader()->setVisible(false);
    ui->showEmail->setShowGrid(false);
    ui->showEmail->setModel(sqlModel3);
}

void MainScreen::myTrips()
{
    QString sql_orderNum;
    sql_orderNum ="select orderNumber as orderNumber from users where userName='"+usersNames+"'";
    QSqlQueryModel *sqlModel4 = new QSqlQueryModel;
    sqlModel4->setQuery(sql_orderNum);\
    ui->orderNumber->horizontalHeader()->setVisible(false);
    ui->orderNumber->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->orderNumber->verticalHeader()->setVisible(false);
    ui->orderNumber->setShowGrid(false);
    ui->orderNumber->setModel(sqlModel4);
}

void MainScreen::on_editBtn_clicked()
{
    updatePage->show();
}

MainScreen::~MainScreen()
{
    delete ui;
}
