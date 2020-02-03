#include "Menu.h"
#include "ui_Menu.h"

Menu::Menu(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f);

    l2=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(ui->pushButtonLearn);
    l1->AddUnit(ui->pushButtonChooseEC);
    l1->AddUnit(ui->pushButtonChooseCE);
    l1->AddUnit(ui->pushButtonSpellCE);
    l1->AddUnit(ui->pushButtonDataInput);
    l1->AddUnit(new QWidget*[2]{ui->labelExtraInfo1,ui->labelExtraInfo2},2);

    l1->LayoutConfigDone();

    l2->AddUnit(ui->labelIcon,width(),height(),LiFixedCorner::RightTop);
    l2->AddUnit(ui->pushButtonExit,width(),height(),LiFixedCorner::RightBottom);
    l2->AddUnit(ui->pushButtonAbout,width(),height(),LiFixedCorner::RightBottom);

    about=new About();
    about->hide();
}

Menu::~Menu()
{
    delete ui;
}

void Menu::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithFixedToLayout(width(),height());
}

void Menu::on_pushButtonDataInput_clicked()
{
    emit(ShowDataInputMenu());
}

void Menu::on_pushButtonChooseEC_clicked()
{
    emit(ShowChooseMenu(ChooseMode::EC));
}

void Menu::on_pushButtonChooseCE_clicked()
{
    emit(ShowChooseMenu(ChooseMode::CE));
}

void Menu::on_pushButtonSpellCE_clicked()
{
    emit(ShowSpellMenu());
}

void Menu::on_pushButtonLearn_clicked()
{
    emit(ShowLearnMenu());
}

void Menu::on_pushButtonAbout_clicked()
{
    about->exec();
}

void Menu::on_pushButtonExit_clicked()
{
    QApplication::exit();
}
