#include "log_in.h"
#include "ui_log_in.h"

/*
 * This is the Login Page
 * As the start interface allows user login
 * Also connect to sign up and Admin interfaces
 *
 */

Log_in::Log_in(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Log_in)
{
    ui->setupUi(this);
    this->setFixedSize(1100, 700);
    this->setWindowTitle("Log in");
    ui->userNameBtn->setFocus();  //set the cursor on user name area
    ui->logInSuccessful->setVisible(false);

    // operator new pages of sign in, main screen and adminstrator
    signIn = new Sign_In;
    mainPage = new MainScreen;
    admin = new adminstrator;

    /*
     * Connect to sign in page and back
     * The login page provides an interface
     * to back to login from the main and sign up pages
     *
     */
    connect(ui->SignInBtn, &clickableLabel::clicked, [=](){
        // When the user click sign up button
        // The sign up page shows
        // Log in page hide
        signIn->show();
        this->close();
    });

    connect(signIn, &Sign_In::backLogIn, [=](){
        cleanLineEdit();
        signIn->hide();
        this->show();
    });

    connect(mainPage, &MainScreen::backToLogIn, [=](){
        QTimer::singleShot(500, this, [=](){
            mainPage->hide();
            this->show();
        });
    });

    connect(admin, &adminstrator::backToLogIn, [=](){
        admin->hide();
        this->show();
    });
}

// this method is for inserting the background image
void Log_in::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/images/CoverMain.png");
    painter.drawPixmap(0,0,pix);

}

void Log_in::on_LogBtn_clicked()
{
    connectDatabase();

    //get username and password from user input areas


    if(db.open()) {
        matchDatabase();
    }else {
        QMessageBox::information(this, "database", "connection failed");
    }

    // if database close in there, then the data cannot match
}


void Log_in::connectDatabase()
{
    /*
     * The if statement is determine whether call the "QSQLITE repeatedly" while using data
     * If there's no sepecfic name, then the default one is "qt_sql_default_connection"
     *
     */
    if(QSqlDatabase::contains("qt_sql_default_connection")) {

        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else {
        db = QSqlDatabase::addDatabase("QSQLITE");
    }

    db.setHostName("localhost");
    db.setUserName("Root");
    db.setPassword("");
    db.setDatabaseName("/Users/a233/Desktop/Car pool/dataBase/usersData.db");
}

void Log_in::matchDatabase()
{
    QString userName = ui->userNameBtn->text();
    QString password = ui->passwordBtn->text();
//    qDebug <<userName + password;  //get data succeed
    qDebug()<<"connection succeed";
    QSqlQuery query(QSqlDatabase::database("QSQLITE"));
    query.prepare(QString("Select * from users Where userName = :userName "
                          "And password = :password"));
    // retrived data from database
    query.bindValue(":userName", userName);
    query.bindValue(":password", password);

    if(!query.exec()) {
        QMessageBox::information(this, "failed", "faile to execute");
    }else {
        if(query.next()) {
            //next is to determine whether the matching result is in the database
            //matching from 0
            QString userNameFromDB = query.value(0).toString();
            QString passwordFromDB = query.value(1).toString();

            if(userNameFromDB == "Ellie" && passwordFromDB == "1137") {
                qDebug() <<"Admin login"<<endl;   //testing Admin
                adminShow();
            }
            else if(userNameFromDB == userName && passwordFromDB == password)
            {
                mainScreenShow();
            }
        }
        else
        {
            QMessageBox::information(this, "failed", "Log in failed, Please check your username or "
                                                     "password");
        }
    }
}

void Log_in::adminShow()
{
    QTimer::singleShot(500, this, [=](){
        ui->logInSuccessful->setVisible(true);
        QTimer::singleShot(1000, this, [=](){
            admin->show();
            this->hide();
            ui->logInSuccessful->setVisible(false);
        });
    });
}

void Log_in::mainScreenShow()
{
    QString userName = ui->userNameBtn->text();
    //Pause 0.5 second when login successed for better user experience
    QTimer::singleShot(500, this, [=](){
        ui->logInSuccessful->setVisible(true);
    });
    QTimer::singleShot(1500, this, [=](){
        // username of main page is inherited to here
        mainPage->usersNames = userName;
        this->hide();
        mainPage->show();
        //declear in mainPage, implement in here.
        //Otherwise the obtained data will be covered
        mainPage->init();
        ui->logInSuccessful->setVisible(false);
        cleanLineEdit();
    });

}

void Log_in::cleanLineEdit()
{
    ui->userNameBtn->clear();
    ui->passwordBtn->clear();

}

Log_in::~Log_in()
{
    delete ui;
}

