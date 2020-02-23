#ifndef SELFHELP_H
#define SELFHELP_H

#include <QDialog>

namespace Ui {
class SelfHelp;
}

class SelfHelp : public QDialog
{
    Q_OBJECT

public:
    explicit SelfHelp(QWidget *parent = nullptr);
    ~SelfHelp();

private:
    Ui::SelfHelp *ui;
};

#endif // SELFHELP_H
