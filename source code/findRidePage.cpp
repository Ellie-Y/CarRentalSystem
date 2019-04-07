#include "findRidePage.h"
#include "ui_findRidePage.h"

findRidePage::findRidePage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::findRidePage)
{
    ui->setupUi(this);
    this->setFixedSize(800, 600);
    this->setWindowTitle("Find Ride");
    connect(ui->searchArea, SIGNAL(textChanged(QString)),this, SLOT(searchFunc()));
    connectData();
    appendData();
    refreshData();
}

findRidePage::~findRidePage()
{
    database.close();
    delete ui;
}

void findRidePage::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/images/Mystic.png");
    painter.drawPixmap(0,0,pix);
}

void findRidePage::appendData()
{
    ui->tableView->verticalHeader()->setVisible(false);   //hide header
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setModel(sqlModel);
}


QStringList findRidePage::getCurrentData()
{
    QStringList rowData;
    //get current row data
    int row = ui->tableView->currentIndex().row();
    QAbstractItemModel *model = ui->tableView->model();
    //QModelIndex index0 = model->index(row, 0);  //two ways to get index

    if(row != -1)
    {
        //get the value of the whole row that user chosed
        rowData << model->index(row, 0).data().toString();
        rowData << model->index(row, 1).data().toString();
        rowData << model->index(row, 2).data().toString();
        rowData << model->index(row, 3).data().toString();
        rowData << model->index(row, 4).data().toString();
        rowData << model->index(row, 5).data().toString();
       //rowData << model->data(index0).toString(); as another way
    }
    return rowData;
}


void findRidePage::on_backBtn_clicked()
{
    emit this->backToMainPage();

}

void findRidePage::on_reserveBtn_clicked()
{
    reservePage = new reserveCar;
    //use input name to match database
    reservePage->inputName = inputName;
    QStringList rowData;
    rowData = this->getCurrentData();

    if(rowData.isEmpty()) {
        QMessageBox::information(this, tr("Alert") , tr("Please choose a car!"));
        return;
    }
    else {
        reservePage->setReserveData(rowData);
    }

    qDebug() << getCurrentData();
    reservePage->activateWindow();
    reservePage->exec();
}

void findRidePage::searchFunc()
{
    QSqlQueryModel *model=new QSqlQueryModel;
    QString search,
            data;
    search = ui->searchArea->text();
    data = "select carName as carName ,carModel as carModel,carCapacity as carCapacity, colour as "
           "colour, carOwner as carOwner from vehicles where carName LIKE '%"+search+"%'";
    model->setQuery(data);
    ui->tableView->setModel(model);
}

void findRidePage::connectData()
{
    if(QSqlDatabase::contains("qt_sql_default_connection")) {

        database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else {
        database = QSqlDatabase::addDatabase("QSQLITE");
    }

    database.setHostName("localhost");
    database.setUserName("Root");
    database.setPassword("");
    database.setDatabaseName("/Users/a233/Desktop/Car pool/dataBase/usersData.db");
    if(database.open()) {
        sqlModel = new QSqlQueryModel();
        sqlModel->setQuery("select carName, carModel, carCapacity, engineCapacity, colour, "
                           "carOwner from vehicles");
    }
    else {
        QMessageBox::information(this, "fail", "open failed");
    }
}

void findRidePage::refreshData()
{
    //remove row by row
    QAbstractItemModel *model = ui->tableView->model();
    int rowCount = model->rowCount();
    for(int r = rowCount - 1; r >= 0; r--) {
        model->removeRow(r);
    }

    appendData();

}
