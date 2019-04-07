#include "Sign_In.h"
#include "ui_Sign_In.h"
#include "log_in.h"

Sign_In::Sign_In(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sign_In)
{
    ui->setupUi(this);
    this->setFixedSize(1100, 700);   //fix screen size
    this->setWindowTitle("Sign up");

    connect(ui->backLog, &clickableLabel::clicked, [=](){
        cleanLineEdit();
        emit this->backLogIn();
    });
}

void Sign_In::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/images/CoverMain.png");
    painter.drawPixmap(0,0,pix);
}

void Sign_In::on_signBtn_clicked()
{
    connectDatabase();

    if(myData.open()) {
//        qDebug() <<"database connect succeed"<<endl;
        getInput();
        QSqlQuery sql;
        QString checkExist = "select * from users where userName = '"+signName+"' ";

        if(signName.isEmpty() || signPassword.isEmpty() ||
                signEmail.isEmpty() || signPhone.isEmpty())
        {
            QMessageBox::about(this, "sign up failed", "Please Please fill in all the information");
        }
        else if(sql.exec(checkExist))
        {
            if(sql.next() == true)
            {
                QMessageBox::information(this, "Not Inserted", "This user name already exist");
            }
            else if(sql.next() == false)
            {
                insertData();
                cleanLineEdit();
            }
        }

    }else {
        QMessageBox::information(this, "Not connected", "database is not conntected");
    }
}

void Sign_In::connectDatabase()
{
    //prevent errors due to called repeatly
    if(QSqlDatabase::contains("qt_sql_default_connection")) {

        myData = QSqlDatabase::database("qt_sql_default_connection");
    }
    else {
        myData = QSqlDatabase::addDatabase("QSQLITE");
    }

    myData.setHostName("localhost");
    myData.setUserName("Root");
    myData.setPassword("");
    //database path needs to be integral
    myData.setDatabaseName("/Users/a233/Desktop/Car pool/dataBase/usersData.db");
}

void Sign_In::insertData()
{
    getInput();
    QSqlQuery sql2;
     //retreive data from database
    sql2.prepare("INSERT INTO users (userName, password, email, phoneNumber)"
                "VALUES (:userName, :password, :email, :phoneNumber)");
    sql2.bindValue(":userName", signName);
    sql2.bindValue(":password", signPassword);
    sql2.bindValue(":email", signEmail);
    sql2.bindValue(":phoneNumber", signPhone);
    if (sql2.exec())
    {
        QMessageBox::about(this, "Successful", "Sign Up successful, please back to Log in");
    }
    else {
        QMessageBox::about(this, "failed", "Sign Up failed, please check if connect database");
    }
}

void Sign_In::getInput()
{
    signName = ui->fullNameBtn->text();
    signPassword = ui->passwordBtn->text();
    signEmail = ui->emailBtn->text();
    signPhone = ui->phoneBtn->text();
}

void Sign_In::cleanLineEdit()
{
   ui->fullNameBtn->clear();
   ui->passwordBtn->clear();
   ui->emailBtn->clear();
   ui->phoneBtn->clear();

}

Sign_In::~Sign_In()
{
    delete ui;
}
