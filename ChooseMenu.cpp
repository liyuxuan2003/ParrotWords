#include "ChooseMenu.h"
#include "ui_ChooseMenu.h"

ChooseMenu::ChooseMenu(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ChooseMenu)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f);
    l2=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(new QWidget*[3]{ui->labelTest,ui->pushButtonTest,ui->labelTestInfo},3);
    l1->AddUnit(new QWidget*[3]{ui->labelConfuse,ui->pushButtonConfuse,ui->labelConfuseInfo},3);
    l1->AddUnit(new QWidget*[5]{ui->labelOrder,ui->radioButtonOrdered,ui->radioButtonRandom,ui->radioButtonSelect,ui->spinBoxSelect},5);
    l1->AddUnit(ui->pushButtonStart);
    l1->AddUnit(ui->labelFailed);

    l1->LayoutConfigDone();

    l2->AddUnit(ui->pushButtonExit,width(),height(),LiFixedCorner::RightBottom);
}

ChooseMenu::~ChooseMenu()
{
    delete ui;
}

void ChooseMenu::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithFixedToLayout(width(),height());
}

void ChooseMenu::Init(ModeEnum::Mode mode)
{
    this->mode=mode;
    if(mode==ModeEnum::CE)
        ui->labelTitle->setText("中译英选择练习-配置页面");
    if(mode==ModeEnum::EC)
        ui->labelTitle->setText("英译中选择练习-配置页面");
    ui->labelTestInfo->setText("未选择测试单词库");
    ui->labelConfuseInfo->setText("未选择混淆单词库");
    testFilePath.clear();
    confuseFilePath.clear();
    ui->labelFailed->hide();
    ui->spinBoxSelect->hide();
    ui->spinBoxSelect->setValue(10);
    ui->radioButtonOrdered->setChecked(true);
}

void ChooseMenu::on_pushButtonExit_clicked()
{
    emit(ShowMenu());
}

void ChooseMenu::on_pushButtonTest_clicked()
{
    QStringList files=QFileDialog::getOpenFileNames(this,"请选择测试单词库","D:/","JSON File (*.json)");
    if(files.length()==0)
        return;
    testFilePath=files;
    ui->labelTestInfo->setText("已选择测试单词库："+QString::number(testFilePath.length())+"个");
}

void ChooseMenu::on_pushButtonConfuse_clicked()
{
    QStringList files=QFileDialog::getOpenFileNames(this,"请选择混淆单词库","D:/","JSON File (*.json)");
    if(files.length()==0)
        return;
    confuseFilePath=files;
    ui->labelConfuseInfo->setText("已选择混淆单词库："+QString::number(confuseFilePath.length())+"个");
}

void ChooseMenu::on_pushButtonStart_clicked()
{
    if(testFilePath.length()==0)
    {
        ui->labelFailed->show();
        ui->labelFailed->setText("请选择测试单词库！");
        return;
    }

    bool testFileCheck=true;
    bool confuseFileCheck=true;

    int wordCounter=0;

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

        QJsonArray jsonArray=jsonDoc.array();
        wordCounter+=jsonArray.size();
    }

    for(int i=0;i<confuseFilePath.length();i++)
    {
        QFile file(confuseFilePath[i]);
        file.open(QIODevice::ReadOnly);

        QByteArray jsonData = file.readAll();
        file.close();

        QJsonParseError jsonError;
        QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData,&jsonError));

        if(jsonError.error!=QJsonParseError::NoError)
        {
            confuseFileCheck=false;
            break;
        }
    }

    if(testFileCheck==false && confuseFileCheck==false)
    {
        ui->labelFailed->show();
        ui->labelFailed->setText("选中的测试单词库和混淆单词库中存在损坏文件！");
        return;
    }
    else if(testFileCheck==false)
    {
        ui->labelFailed->show();
        ui->labelFailed->setText("选中的测试单词库中存在损坏文件！");
        return;
    }
    else if(confuseFileCheck==false)
    {
        ui->labelFailed->show();
        ui->labelFailed->setText("选中的混淆单词库中存在损坏文件！");
        return;
    }

    QList<int> select;
    select.clear();
    if(ui->radioButtonSelect->isChecked()==true)
    {
        int needWord=ui->spinBoxSelect->value();
        if(needWord>wordCounter)
            needWord=wordCounter;
        QList<int> selectList;
        selectList.clear();
        for(int i=0;i<wordCounter;i++)
            selectList.append(i);

        QTime time=QTime::currentTime();
        qsrand(time.msec()+time.second()*1000);
        for(int i=0;i<4*wordCounter;i++)
        {
            int n1=qrand()%wordCounter;
            int n2=qrand()%wordCounter;
            qSwap(selectList[n1],selectList[n2]);
        }

        for(int i=0;i<needWord;i++)
            select.append(selectList[i]);
    }

    ui->labelFailed->hide();
    emit(ShowChoose(mode,order,testFilePath,confuseFilePath,select));
}

void ChooseMenu::on_radioButtonOrdered_toggled(bool checked)
{
    if(checked==true)
        order=OrderEnum::Ordered;
}

void ChooseMenu::on_radioButtonRandom_toggled(bool checked)
{
    if(checked==true)
        order=OrderEnum::Random;
}

void ChooseMenu::on_radioButtonSelect_toggled(bool checked)
{
    if(checked==true)
    {
        order=OrderEnum::Random;
        ui->spinBoxSelect->show();
    }
    if(checked==false)
        ui->spinBoxSelect->hide();
}
