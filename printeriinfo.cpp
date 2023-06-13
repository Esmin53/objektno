#include "printeriinfo.h"
#include "ui_printeriinfo.h"

PrinteriInfo::PrinteriInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrinteriInfo)
{
    ui->setupUi(this);
}

PrinteriInfo::~PrinteriInfo()
{
    delete ui;
}
