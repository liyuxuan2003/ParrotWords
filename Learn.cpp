#include "Learn.h"
#include "ui_Learn.h"

Learn::Learn(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Learn)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f);
    l2=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(ui->labelLocation);
    l1->AddUnit(new QWidget*[2]{ui->labelChineseTitle,ui->labelChinese},2);
    l1->AddUnit(new QWidget*[2]{ui->labelEnglishTitle,ui->labelEnglish},2);
    l1->AddUnit(new QWidget*[3]{ui->pushButtonShowChinese,ui->pushButtonShowEnglish,ui->pushButtonRead},3);
    l1->AddUnit(new QWidget*[2]{ui->pushButtonPrev,ui->pushButtonNext},2);

    l1->LayoutConfigDone();

    l2->AddUnit(ui->pushButtonExit,width(),height(),LiFixedCorner::RightBottom);

    tts=new QTextToSpeech(this);
    tts->setLocale(QLocale::English);
    tts->setRate(0.0);
    tts->setPitch(1.0);
    tts->setVolume(1.0);
}

Learn::~Learn()
{
    delete ui;
}

void Learn::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithFixedToLayout(width(),height());
}

void Learn::Init(QStringList learnFilePath)
{
    this->learnFilePath=learnFilePath;

    ui->pushButtonPrev->setDisabled(true);
    ui->pushButtonPrev->setEnabled(true);

    wordChineseLearn.clear();
    wordEnglishLearn.clear();

    for(int i=0;i<learnFilePath.length();i++)
    {
        QFile file(learnFilePath[i]);
        file.open(QIODevice::ReadOnly);

        QByteArray jsonData = file.readAll();
        file.close();

        QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData));
        QJsonArray jsonArray=jsonDoc.array();

        for(int i=0;i<jsonArray.size();i++)
        {
            QJsonObject jsonObject=jsonArray[i].toObject();
            wordChineseLearn.append(jsonObject.value("wordChinese").toString());
            wordEnglishLearn.append(jsonObject.value("wordEnglish").toString());
        }
    }

    nowNum=0;
    totalNum=wordChineseLearn.length();

    isShowChinese=new bool[totalNum];
    isShowEnglish=new bool[totalNum];

    for(int i=0;i<totalNum;i++)
    {
        isShowChinese[i]=true;
        isShowEnglish[i]=true;
    }

    GeneratePage();
}

void Learn::GeneratePage()
{
    ui->labelLocation->setText("当前题目："+QString::number(nowNum+1)+"/"+QString::number(totalNum));
    this->setFocus();

    ChangeShowMode();
}

void Learn::keyPressEvent(QKeyEvent *ev)
{
    this->setFocus();
    if(ev->key()==Qt::Key_1)
        ui->pushButtonShowChinese->click();
    if(ev->key()==Qt::Key_2)
        ui->pushButtonShowEnglish->click();
    if(ev->key()==Qt::Key_3)
        ui->pushButtonRead->click();
    if(ev->key()==Qt::Key_Left)
        ui->pushButtonPrev->click();
    if(ev->key()==Qt::Key_Right)
        ui->pushButtonNext->click();
}

void Learn::ChangeShowMode()
{
    if(isShowChinese[nowNum]==true)
    {
        ui->labelChinese->setText(wordChineseLearn[nowNum]);
        ui->pushButtonShowChinese->setText("隐藏中文释义");
    }
    else
    {
        ui->labelChinese->setText("");
        ui->pushButtonShowChinese->setText("显示中文释义");
    }

    if(isShowEnglish[nowNum]==true)
    {
        ui->labelEnglish->setText(wordEnglishLearn[nowNum]);
        ui->pushButtonShowEnglish->setText("隐藏英文拼写");
    }
    else
    {
        ui->labelEnglish->setText("");
        ui->pushButtonShowEnglish->setText("显示英文拼写");
    }
}

void Learn::on_pushButtonShowChinese_clicked()
{
    isShowChinese[nowNum]=!isShowChinese[nowNum];
    ChangeShowMode();
}

void Learn::on_pushButtonShowEnglish_clicked()
{
    isShowEnglish[nowNum]=!isShowEnglish[nowNum];
    ChangeShowMode();
}

void Learn::on_pushButtonRead_clicked()
{
    tts->say(wordEnglishLearn[nowNum]);
}

void Learn::OnLocationChange(int offset)
{
    nowNum=nowNum+offset;
    if(nowNum>0 && nowNum<totalNum-1)
    {
        ui->pushButtonPrev->setEnabled(true);
        ui->pushButtonNext->setEnabled(true);
    }
    else if(nowNum==0)
    {
        ui->pushButtonPrev->setDisabled(true);
        ui->pushButtonNext->setEnabled(true);
    }
    else if(nowNum==totalNum-1)
    {
        ui->pushButtonPrev->setEnabled(true);
        ui->pushButtonNext->setDisabled(true);
    }
    GeneratePage();
}

void Learn::on_pushButtonPrev_clicked()
{
    OnLocationChange(-1);
}

void Learn::on_pushButtonNext_clicked()
{
    OnLocationChange(1);
}

void Learn::on_pushButtonExit_clicked()
{
    emit(ShowMenu());
}
