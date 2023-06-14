#include "mainwindow.h"
#include "ui_mainwindow.h" 

void displayDataInTableView(QTableView* tableView);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTableView* tableView = ui->tableView;

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
        ui->label_db->setText("Failed to open the database!");
    else
        ui->label_db->setText("Conected...");
    displayDataInTableView();

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
    QString serijskiBroj, inventurniBroj, model, lokacija, osoba, rb, psb, tsb;
    serijskiBroj=ui->lineEdit_sb->text();
    inventurniBroj=ui->lineEdit_ib->text();
    model=ui->lineEdit_mp->text();
    lokacija=ui->lineEdit_l->text();
    osoba=ui->lineEdit_zo->text();
    rb=ui->lineEdit_rb->text();
    psb=ui->lineEdit_psb->text();
    tsb=ui->lineEdit_tsb->text();


    int mjesec = ui->spinBox_mj->value();
    int godina = ui->spinBox_god->value();
    int prethodno = psb.toInt();
    int trenutno = tsb.toInt();
    int potrosnja = (trenutno - prethodno);
    int cijena = (potrosnja * 0.019);

        // Check if a row with the same month and year already exists
        QSqlQuery query;
        query.prepare("SELECT * FROM "+serijskiBroj+" WHERE mjesec = :mjesec AND godina = :godina");
        query.bindValue(":mjesec", mjesec);
        query.bindValue(":godina", godina);
        if (query.exec() && query.next()) {
            // Row with the same month and year already exists, update the row
            query.prepare("UPDATE "+serijskiBroj+" SET prethodno = :prethodno, trenutno = :trenutno, potrosnja = :potrosnja, cijena = :cijena WHERE mjesec = :mjesec AND godina = :godina");
            query.bindValue(":prethodno", prethodno);
            query.bindValue(":trenutno", trenutno);
            query.bindValue(":potrosnja", potrosnja);
            query.bindValue(":cijena", cijena);
            query.bindValue(":mjesec", mjesec);
            query.bindValue(":godina", godina);
            if (query.exec()) {
                qDebug() << "Row updated successfully";
                // Perform any additional actions after updating the row
            } else {
                qDebug() << "Failed to update row:" << query.lastError().text();
                // Handle the error
            }
        } else {
            // Row with the same month and year doesn't exist, add a new row
            query.prepare("INSERT INTO "+serijskiBroj+" (godina, mjesec, prethodno, trenutno, potrosnja, cijena) "
                          "VALUES (:godina, :mjesec, :prethodno, :trenutno, :potrosnja, :cijena)");
            query.bindValue(":godina", godina);
            query.bindValue(":mjesec", mjesec);
            query.bindValue(":prethodno", prethodno);
            query.bindValue(":trenutno", trenutno);
            query.bindValue(":potrosnja", potrosnja);
            query.bindValue(":cijena", cijena);
            if (query.exec()) {
                qDebug() << "New row added successfully";
                // Perform any additional actions after adding the new row
            } else {
                qDebug() << "Failed to add new row:" << query.lastError().text();
                // Handle the error
            }
        }
}

void MainWindow::on_pushButton_obrisi_clicked()
{
    // Get the value needed to identify the row to delete
    QString serijskiBroj = ui->lineEdit_sb->text();

    // Prepare the delete query
    QSqlQuery query;
    query.prepare("DELETE FROM Printeri WHERE serijskiBroj = :serijskiBroj");
    query.bindValue(":serijskiBroj", serijskiBroj);

    // Execute the delete query
    if (query.exec()) {
        qDebug() << "Row deleted successfully";
        // Perform any additional actions after deleting the row
    } else {
        qDebug() << "Failed to delete row:" << query.lastError().text();
        // Handle the error
    }
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

void MainWindow::displayDataInTableView()
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT * FROM Printeri");

    QTableView *tableView = findChild<QTableView*>("tableView");
    tableView->setModel(model);
}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QString val = ui->tableView->model()->data(index).toString();
        int columnIndex = index.column();
        QSqlQuery query;

        QString serijskiBroj, inventurniBroj, model, lokacija, osoba, rb, psb, tsb;
        //int mjesec, godina, prethodno, trenutno, potrosnja, cijena;

        if (columnIndex == 1) {
            query.prepare("SELECT redniBroj, serijskiBroj, inventurniBroj, model, lokacija, osoba, prethodnoStanjeBrojaca, trenutnoStanjeBrojaca FROM Printeri WHERE serijskiBroj = :val");
            query.bindValue(":val", val);

            // Execute the query
            if (query.exec()) {
                // Check if there is a row of data
                if (query.next()) {
                    // Fetch the data from the current row and assign it to the variables
                    serijskiBroj = query.value("serijskiBroj").toString();
                    inventurniBroj = query.value("inventurniBroj").toString();
                    model = query.value("model").toString();
                    lokacija = query.value("lokacija").toString();
                    osoba = query.value("osoba").toString();
                    rb = query.value("redniBroj").toString();
                    psb = query.value("prethodnoStanjeBrojaca").toString();
                    tsb = query.value("trenutnoStanjeBrojaca").toString();

                    ui->label_sb->setText(serijskiBroj);
                    ui->lineEdit_rb->setText(rb);
                    ui->lineEdit_sb->setText(serijskiBroj);
                    ui->lineEdit_ib->setText(inventurniBroj);
                    ui->lineEdit_mp->setText(model);
                    ui->lineEdit_l->setText(lokacija);
                    ui->lineEdit_zo->setText(osoba);
                    ui->lineEdit_psb->setText(psb);
                    ui->lineEdit_tsb->setText(tsb);

                    //Dio koda za prikaz podataka u drugi tableView
                    QSqlQueryModel *model = new QSqlQueryModel(this);
                    model->setQuery("SELECT * FROM " + val);

                    QTableView *tableView = findChild<QTableView*>("tableView_2");
                    tableView->setModel(model);



                } else {
                    // Handle the case when no rows are returned
                    qDebug() << "No data found";
                }
            } else {
                // Handle the case when the query execution fails
                qDebug() << "Failed to execute query:" << query.lastError().text();
            }
        }
}





