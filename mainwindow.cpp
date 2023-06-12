#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Users/MAGARAC/Desktop/ClickChargeET");

    if(!mydb.open())
        ui->label->setText("Failed to open the database!");
    else
        ui->label_2->setText("Veoma dobro");

}

MainWindow::~MainWindow()
{
    delete ui;
}
