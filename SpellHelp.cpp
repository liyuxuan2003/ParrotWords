#include "SpellHelp.h"
#include "ui_SpellHelp.h"

SpellHelp::SpellHelp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpellHelp)
{
    ui->setupUi(this);
}

SpellHelp::~SpellHelp()
{
    delete ui;
}
