#include "mainwindow.h"
#include "ui_mainwindow.h" 

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QDate currentDate = QDate::currentDate();
    int currentMonth = currentDate.month();
    int currentYear = currentDate.year();

    ui->spinBox_mj->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinBox_mj->setReadOnly(true);
    ui->spinBox_mj->setValue(currentMonth);
    ui->spinBox_god->setReadOnly(true);
    ui->spinBox_god->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->spinBox_god->setValue(currentYear);

    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Users/MAGARAC/Desktop/ClickChargeET.db");

    if(!mydb.open())
        ui->label->setText("Failed to open the database!");
    else
        ui->label_db->setText("Conected...");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_dodaj_clicked()
{
    QString serijskiBroj, inventurniBroj, model, lokacija, osoba, rb, psb, tsb;
    serijskiBroj=ui->lineEdit_sb->text();
    inventurniBroj=ui->lineEdit_ib->text();
    model=ui->lineEdit_mp->text();
    lokacija=ui->lineEdit_l->text();
    osoba=ui->lineEdit_zo->text();
    rb=ui->lineEdit_rb->text();
    psb=ui->lineEdit_psb->text();
    tsb=ui->lineEdit_tsb->text();


    QSqlQuery qry;

    QString query = "insert into Printeri (redniBroj, serijskiBroj, inventurniBroj, model, lokacija, osoba, prethodnoStanjeBrojaca, trenutnoStanjeBrojaca)"
                    "values ('"+rb+"', '"+serijskiBroj+"', '"+inventurniBroj+"', '"+model+"', '"+lokacija+"', '"+osoba+"','"+psb+"', '"+tsb+"');";

    QString query_2 = "CREATE TABLE '"+serijskiBroj+"' ("
                                                    "godina INT,"
                                                    "mjesec INT,"
                                                    "prethodno INT,"
                                                    "trenutno INT,"
                                                    "potrosnja INT,"
                                                    "cijena REAL"
                                                    ")";

    int godina = ui->spinBox_god->value();
    int mjesec = ui->spinBox_mj->value();
    int prethodno = psb.toInt();
    int trenutno = tsb.toInt();
    int potrosnja = (trenutno - prethodno);
    int cijena = (potrosnja * 0.019);

    QString query_3 = QString("INSERT INTO %1 (godina, mjesec, prethodno, trenutno, potrosnja, cijena) "
                              "VALUES (%2, %3, %4, %5, %6, %7)")
                      .arg(serijskiBroj)
                      .arg(godina)
                      .arg(mjesec)
                      .arg(prethodno)
                      .arg(trenutno)
                      .arg(potrosnja)
                      .arg(cijena);

    if(qry.exec(query)) {
        QMessageBox::information(this, tr("Save"), tr("Saved"));
            if(qry.exec(query_2)) {
                QMessageBox::information(this, tr("Save"), tr("Saved"));
                    if(qry.exec(query_3)) {
                        QMessageBox::information(this, tr("Save"), tr("Saved"));
                    } else {
                        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
                    }
             } else {
                QMessageBox::critical(this, tr("error::"), qry.lastError().text());
             }
    } else {
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }
}

void MainWindow::on_pushButton_update_clicked()
{
   QString query = "CREATE TABLE testtable (test varchar(20));";

   QSqlQuery qry;

   if(!qry.exec(query)) {
     QMessageBox::critical(this, tr("error::"), qry.lastError().text());
   }
}

void MainWindow::on_pushButton_obrisi_clicked()
{
   QMessageBox::information(this, tr("Save"), tr("Saved"));
}

void MainWindow::on_pushButton_m_clicked()
{
    int currentValue = ui->spinBox_mj->value();
    int newValue = currentValue + 1;
    if(newValue == 13) {
        newValue = 1;
        int god = ui->spinBox_god->value();
        ui->spinBox_god->setValue(god + 1);
     }

    ui->spinBox_mj->setValue(newValue);
}
