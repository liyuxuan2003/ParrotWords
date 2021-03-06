#include "LearnMenu.h"
#include "ui_LearnMenu.h"

LearnMenu::LearnMenu(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::LearnMenu)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f);
    l2=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(new QWidget*[3]{ui->labelLearn,ui->pushButtonTest,ui->labelLearnInfo},3);
    l1->AddUnit(new QWidget*[2]{ui->labelSource,ui->comboBoxSource},2);
    l1->AddUnit(new QWidget*[4]{ui->labelSetting,ui->radioButtonCE,ui->radioButtonC,ui->radioButtonE},4);
    l1->AddUnit(ui->pushButtonStart);
    l1->AddUnit(ui->labelFailed);

    l1->LayoutConfigDone();

    l2->AddUnit(ui->pushButtonExit,width(),height(),LiFixedCorner::RightBottom);
}

LearnMenu::~LearnMenu()
{
    delete ui;
}

void LearnMenu::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithFixedToLayout(width(),height());
}

void LearnMenu::Init()
{
    ui->labelLearnInfo->setText("未选择学习单词库");
    ui->labelFailed->hide();
    ui->radioButtonCE->setChecked(true);
    learnFilePath.clear();
    showC=true;
    showE=true;
    ui->radioButtonCE->clicked();
    ui->comboBoxSource->setCurrentIndex(0);
    source=AudioSourceEnum::Youdao;
}

void LearnMenu::on_pushButtonTest_clicked()
{
    QStringList files=QFileDialog::getOpenFileNames(this,"请选择学习单词库","D:/","JSON File (*.json)");
    if(files.length()==0)
        return;
    learnFilePath=files;
    ui->labelLearnInfo->setText("已选择学习单词库："+QString::number(learnFilePath.length())+"个");
}

void LearnMenu::on_pushButtonStart_clicked()
{
    if(learnFilePath.length()==0)
    {
        ui->labelFailed->show();
        ui->labelFailed->setText("请选择学习单词库！");
        return;
    }

    bool learnFileCheck=true;

    for(int i=0;i<learnFilePath.length();i++)
    {
        QFile file(learnFilePath[i]);
        file.open(QIODevice::ReadOnly);

        QByteArray jsonData = file.readAll();
        file.close();

        QJsonParseError jsonError;
        QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData,&jsonError));

        if(jsonError.error!=QJsonParseError::NoError)
        {
            learnFileCheck=false;
            break;
        }
    }

    if(learnFileCheck==false)
    {
        ui->labelFailed->show();
        ui->labelFailed->setText("选中的学习单词库中存在损坏文件！");
        return;
    }

    ui->labelFailed->hide();
    emit(ShowLearn(learnFilePath,showC,showE,source));
}

void LearnMenu::on_pushButtonExit_clicked()
{
    emit(ShowMenu());
}

void LearnMenu::on_radioButtonCE_toggled(bool checked)
{
    showC=true;
    showE=true;
}

void LearnMenu::on_radioButtonC_toggled(bool checked)
{
    showC=true;
    showE=false;
}

void LearnMenu::on_radioButtonE_toggled(bool checked)
{
    showC=false;
    showE=true;
}

void LearnMenu::on_comboBoxSource_activated(int index)
{
    if(index==0)
        source=AudioSourceEnum::Youdao;
    if(index==1)
        source=AudioSourceEnum::Machine;
}
