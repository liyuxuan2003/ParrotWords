#include "ChooseHelp.h"
#include "ui_ChooseHelp.h"

ChooseHelp::ChooseHelp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseHelp)
{
    ui->setupUi(this);
}

ChooseHelp::~ChooseHelp()
{
    delete ui;
}
