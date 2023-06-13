#ifndef PRINTERIINFO_H
#define PRINTERIINFO_H

#include <QDialog>

namespace Ui {
class PrinteriInfo;
}

class PrinteriInfo : public QDialog
{
    Q_OBJECT

public:
    explicit PrinteriInfo(QWidget *parent = 0);
    ~PrinteriInfo();

private:
    Ui::PrinteriInfo *ui;
};

#endif // PRINTERIINFO_H
