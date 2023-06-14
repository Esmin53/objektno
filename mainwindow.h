#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtSql>
#include<QDebug>
#include<QFileInfo>
#include<QSqlQuery>
#include<QMessageBox>
#include<QSqlError>
#include<QDate>
#include<QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void displayDataInTableView();

private slots:

    void on_pushButton_dodaj_clicked();

    void on_pushButton_update_clicked();

    void on_pushButton_obrisi_clicked();

    void on_pushButton_mj_clicked();

    void on_pushButton_m_clicked();

    void on_tableView_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
