#include "LearnHelp.h"
#include "ui_LearnHelp.h"

LearnHelp::LearnHelp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LearnHelp)
{
    ui->setupUi(this);
}

LearnHelp::~LearnHelp()
{
    delete ui;
}
