#include "Self.h"
#include "ui_Self.h"

Self::Self(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Self)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f);
    l2=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(ui->labelLocation);

    l1->AddUnit(new QWidget*[3]{ui->labelQTitle,ui->labelQC,ui->labelQE},3);
    l1->AddUnit(new QWidget*[3]{ui->labelATitle,ui->labelAC,ui->labelAE},3);
    l1->AddUnit(new QWidget*[4]{ui->pushButtonShowAns,ui->pushButtonRight,ui->pushButtonWrong,ui->pushButtonRead},4);
    l1->AddUnit(new QWidget*[2]{ui->labelNote,ui->lineEditNote},2);

    l1->LayoutConfigDone();

    l2->AddUnit(ui->pushButtonExit,width(),height(),LiFixedCorner::RightBottom);
    l2->AddUnit(ui->pushButtonHelp,width(),height(),LiFixedCorner::RightTop);
    l2->AddUnit(ui->pushButtonSearch,width(),height(),LiFixedCorner::RightTop);

    selfReview=new SelfReview();
    selfReview->hide();

    selfHelp=new SelfHelp();
    selfHelp->hide();

    tts = new QTextToSpeech(this);
    tts->setLocale(QLocale::English);
    tts->setRate(0.0);
    tts->setPitch(1.0);
    tts->setVolume(1.0);

    player = new QMediaPlayer(this);
    player->setVolume(100);
}

Self::~Self()
{
    delete ui;
}

void Self::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithFixedToLayout(width(),height());
}

void Self::keyPressEvent(QKeyEvent *ev)
{
    this->setFocus();

    if(ev->key()==Qt::Key_Space)
        ui->pushButtonShowAns->click();
    else if(ev->key()==Qt::Key_1 && ui->pushButtonRight->isVisible()==true)
        ui->pushButtonRight->click();
    else if(ev->key()==Qt::Key_2 && ui->pushButtonWrong->isVisible()==true)
        ui->pushButtonWrong->click();
    else if(ev->key()==Qt::Key_3 && ui->pushButtonRead->isVisible()==true)
        ui->pushButtonRead->click();
}

void Self::on_pushButtonExit_clicked()
{
    emit(ShowMenu());
}

void Self::Init(ModeEnum::Mode mode,OrderEnum::Order order,QStringList testFilePath,QList<int> review,AudioSourceEnum::AudioSource source)
{
    this->mode=mode;
    if(mode==ModeEnum::CE)
    {
        ui->labelTitle->setText("中译英自测练习");
        ui->labelQC->show();
        ui->labelQE->hide();
        ui->labelAE->show();
        ui->labelAC->hide();
        ui->labelQTitle->setText("单词中文：");
        ui->labelATitle->setText("单词英文：");
    }
    if(mode==ModeEnum::EC)
    {
        ui->labelTitle->setText("英译中自测练习");
        ui->labelQC->hide();
        ui->labelQE->show();
        ui->labelAE->hide();
        ui->labelAC->show();
        ui->labelQTitle->setText("单词英文：");
        ui->labelATitle->setText("单词中文：");
    }

    this->testFilePath=testFilePath;
    this->order=order;

    this->source=source;

    wordChinese.clear();
    wordEnglish.clear();
    toReview.clear();

    for(int i=0;i<testFilePath.length();i++)
    {
        QFile file(testFilePath[i]);
        file.open(QIODevice::ReadOnly);

        QByteArray jsonData = file.readAll();
        file.close();

        QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData));
        QJsonArray jsonArray=jsonDoc.array();

        for(int i=0;i<jsonArray.size();i++)
        {
            QJsonObject jsonObject=jsonArray[i].toObject();
            wordChinese.append(jsonObject.value("wordChinese").toString());
            wordEnglish.append(jsonObject.value("wordEnglish").toString());
        }
    }

    nowNum=0;
    if(review.length()==0)
    {
        totalNum=wordChinese.length();
        testOrder=new int[totalNum];
        for(int i=0;i<totalNum;i++)
            testOrder[i]=i;
    }
    if(review.length()!=0)
    {
        totalNum=review.length();
        testOrder=new int[totalNum];
        for(int i=0;i<totalNum;i++)
            testOrder[i]=review[i];
    }
    record=new int[totalNum]{0};

    QTime time=QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    if(order==OrderEnum::Random)
    {
        for(int i=0;i<4*totalNum;i++)
        {
            int n1=qrand()%totalNum;
            int n2=qrand()%totalNum;
            qSwap(testOrder[n1],testOrder[n2]);
        }
    }

    GeneratePage();
}

void Self::GeneratePage()
{
    ui->labelLocation->setText("当前题目："+QString::number(nowNum+1)+"/"+QString::number(totalNum));
    if(mode==ModeEnum::CE)
    {
        ui->labelQC->setText(wordChinese[testOrder[nowNum]]);
        ui->labelAE->setText(wordEnglish[testOrder[nowNum]]);
        ui->labelAE->hide();
    }
    if(mode==ModeEnum::EC)
    {
        ui->labelQE->setText(wordEnglish[testOrder[nowNum]]);
        ui->labelAC->setText(wordChinese[testOrder[nowNum]]);
        ui->labelAC->hide();
    }
    ui->pushButtonRight->hide();
    ui->pushButtonWrong->hide();
    ui->pushButtonRead->hide();
    ui->lineEditNote->setText("");
    this->setFocus();
}

void Self::on_pushButtonShowAns_clicked()
{
    if(mode==ModeEnum::CE)
        ui->labelAE->show();
    if(mode==ModeEnum::EC)
        ui->labelAC->show();
    ui->pushButtonRight->show();
    ui->pushButtonWrong->show();
    ui->pushButtonRead->show();
}

void Self::on_pushButtonRight_clicked()
{
    record[nowNum]=0;
    NextPage();
}

void Self::on_pushButtonWrong_clicked()
{
    record[nowNum]=1;
    NextPage();
}

void Self::NextPage()
{
    if(record[nowNum]>0)
        toReview.append(testOrder[nowNum]);
    nowNum++;
    if(nowNum<totalNum)
        GeneratePage();
    else
    {
        int rightNum=0;
        int wrongNum=0;
        for(int i=0;i<totalNum;i++)
        {
            if(record[i]==0)
                rightNum++;
            if(record[i]==1)
                wrongNum++;
        }
        selfReview->Init(rightNum,wrongNum,totalNum);
        selfReview->exec();
        if(selfReview->GetUserAns()==true)
        {
            Init(mode,order,testFilePath,toReview,source);
            return;
        }
        else
            emit(ShowMenu());
    }
}

void Self::on_pushButtonRead_clicked()
{
    if(source==AudioSourceEnum::Youdao)
    {
        player->setMedia(QUrl("http://dict.youdao.com/speech?audio="+wordEnglish[testOrder[nowNum]]));
        player->play();
    }

    if(source==AudioSourceEnum::Machine)
    {
        tts->say(wordEnglish[testOrder[nowNum]]);
    }
}

void Self::on_pushButtonHelp_clicked()
{
    selfHelp->exec();
}

void Self::on_pushButtonSearch_clicked()
{
    ShowSearch(testFilePath);
}
