#include "SelfHelp.h"
#include "ui_SelfHelp.h"

SelfHelp::SelfHelp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelfHelp)
{
    ui->setupUi(this);
}

SelfHelp::~SelfHelp()
{
    delete ui;
}
