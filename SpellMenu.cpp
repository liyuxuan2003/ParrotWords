#include "SpellMenu.h"
#include "ui_SpellMenu.h"

SpellMenu::SpellMenu(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SpellMenu)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f);
    l2=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(new QWidget*[3]{ui->labelTest,ui->pushButtonTest,ui->labelTestInfo},3);
    l1->AddUnit(new QWidget*[3]{ui->labelOrder,ui->radioButtonOrdered,ui->radioButtonRandom},3);
    l1->AddUnit(ui->pushButtonStart);
    l1->AddUnit(ui->labelFailed);

    l1->LayoutConfigDone();

    l2->AddUnit(ui->pushButtonExit,width(),height(),LiFixedCorner::RightBottom);
}

SpellMenu::~SpellMenu()
{
    delete ui;
}

void SpellMenu::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithFixedToLayout(width(),height());
}

void SpellMenu::Init()
{
    ui->labelTestInfo->setText("未选择测试单词库");
    testFilePath.clear();
    ui->labelFailed->hide();
    ui->radioButtonOrdered->setChecked(true);
}

void SpellMenu::on_pushButtonExit_clicked()
{
    emit(ShowMenu());
}

void SpellMenu::on_pushButtonTest_clicked()
{
    QStringList files=QFileDialog::getOpenFileNames(this,"请选择测试单词库","D:/","JSON File (*.json)");
    if(files.length()==0)
        return;
    testFilePath=files;
    ui->labelTestInfo->setText("已选择测试单词库："+QString::number(testFilePath.length())+"个");
}

void SpellMenu::on_pushButtonStart_clicked()
{
    if(testFilePath.length()==0)
    {
        ui->labelFailed->show();
        ui->labelFailed->setText("请选择测试单词库！");
        return;
    }

    bool testFileCheck=true;

    for(int i=0;i<testFilePath.length();i++)
    {
        QFile file(testFilePath[i]);
        file.open(QIODevice::ReadOnly);

        QByteArray jsonData = file.readAll();
        file.close();

        QJsonParseError jsonError;
        QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData,&jsonError));

        if(jsonError.error!=QJsonParseError::NoError)
        {
            testFileCheck=false;
            break;
        }
    }

    if(testFileCheck==false)
    {
        ui->labelFailed->show();
        ui->labelFailed->setText("选中的测试单词库中存在损坏文件！");
        return;
    }

    ui->labelFailed->hide();
    emit(ShowSpell(order,testFilePath));
}

void SpellMenu::on_radioButtonOrdered_toggled(bool checked)
{
    if(checked==true)
        order=SpellOrder::Ordered;
}

void SpellMenu::on_radioButtonRandom_toggled(bool checked)
{
    if(checked==true)
        order=SpellOrder::Random;
}
