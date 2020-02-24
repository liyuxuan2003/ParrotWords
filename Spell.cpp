#include "Spell.h"
#include "ui_Spell.h"

Spell::Spell(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Spell)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f);
    l2=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(ui->labelLocation);
    l1->AddUnit(ui->labelQuestion);
    l1->AddUnit(new QWidget*[5]{ui->line1,ui->line2,ui->line3,ui->line4,ui->labelInput},5);
    l1->AddUnit(new QWidget*[5]{ui->pushButtonTip1,ui->pushButtonTip2,ui->pushButtonTipR,ui->pushButtonTipA,ui->pushButtonTipHide},5);
    l1->AddUnit(new QWidget*[2]{ui->labelTips,ui->labelTipsContent},2);
    l1->AddUnit(new QWidget*[3]{ui->pushButtonNext,ui->pushButtonMark,ui->labelMark},3);

    l1->LayoutConfigDone();

    l2->AddUnit(ui->pushButtonExit,width(),height(),LiFixedCorner::RightBottom);
    l2->AddUnit(ui->pushButtonHelp,width(),height(),LiFixedCorner::RightTop);
    l2->AddUnit(ui->pushButtonSearch,width(),height(),LiFixedCorner::RightTop);

    spellReview=new SpellReview();
    spellReview->hide();

    spellHelp=new SpellHelp();
    spellHelp->hide();

    tts = new QTextToSpeech(this);
    tts->setLocale(QLocale::English);
    tts->setRate(0.0);
    tts->setPitch(1.0);
    tts->setVolume(1.0);

    player = new QMediaPlayer(this);
    player->setVolume(100);
}

Spell::~Spell()
{
    delete ui;
}

void Spell::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithFixedToLayout(width(),height());
}

void Spell::on_pushButtonExit_clicked()
{
    emit(ShowMenu());
}

void Spell::Init(OrderEnum::Order order,QStringList testFilePath,QList<int> review,AudioSourceEnum::AudioSource source)
{
    ui->labelTitle->setText("中译英拼写练习");

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

    nowEnterWord="";

    GeneratePage();
}

void Spell::GeneratePage()
{
    ui->labelLocation->setText("当前题目："+QString::number(nowNum+1)+"/"+QString::number(totalNum));
    ui->labelQuestion->setText(wordChinese[testOrder[nowNum]]);

    nowEnterWord="";
    isMarkClick=false;

    QString dotString="";
    for(int i=0;i<wordEnglish[testOrder[nowNum]].length();i++)
        dotString.append(".");
    ui->labelTipsContent->setText(dotString);
    ui->labelInput->setText("<font color=\"#FFFFFF\">"+dotString+"</font>");

    ui->pushButtonNext->hide();

    ui->labelMark->hide();
    ui->pushButtonMark->hide();

    this->setFocus();
}

void Spell::keyPressEvent(QKeyEvent *ev)
{
    this->setFocus();

    bool isNeedRewrite=false;

    if(ev->key()==Qt::Key_Space && nowEnterWord==wordEnglish[testOrder[nowNum]])
        ui->pushButtonNext->click();
    else if(ev->key()==Qt::Key_1)
        ui->pushButtonTip1->click();
    else if(ev->key()==Qt::Key_2)
        ui->pushButtonTip2->click();
    else if(ev->key()==Qt::Key_3)
        ui->pushButtonTipR->click();
    else if(ev->key()==Qt::Key_4)
        ui->pushButtonTipA->click();
    else if(ev->key()==Qt::Key_5)
        ui->pushButtonTipHide->click();
    else if(ev->key()==Qt::Key_0 && nowEnterWord==wordEnglish[testOrder[nowNum]])
        ui->pushButtonMark->click();
    else if(ev->key()==Qt::Key_Backspace)
    {
        nowEnterWord.chop(1);
        isNeedRewrite=true;
    }
    else if(ev->key()>=Qt::Key_A && ev->key()<=Qt::Key_Z && nowEnterWord.length()<wordEnglish[testOrder[nowNum]].length())
    {
        char keyInput='a';
        keyInput=keyInput+(ev->key()-Qt::Key_A);
        nowEnterWord.append(keyInput);
        isNeedRewrite=true;
    }

    if(isNeedRewrite==true)
    {
        ui->labelInput->clear();
        for(int i=0;i<wordEnglish[testOrder[nowNum]].length();i++)
        {
            if(i<nowEnterWord.length())
            {
                if(wordEnglish[testOrder[nowNum]][i]==nowEnterWord[i])
                    ui->labelInput->setText(ui->labelInput->text()+"<font color=\"#FFFFFF\">"+nowEnterWord[i]+"</font>");
                if(wordEnglish[testOrder[nowNum]][i]!=nowEnterWord[i])
                    ui->labelInput->setText(ui->labelInput->text()+"<font color=\"#FF0000\">"+nowEnterWord[i]+"</font>");
            }
            else
                ui->labelInput->setText(ui->labelInput->text()+"<font color=\"#FFFFFF\">.</font>");
        }
        if(nowEnterWord==wordEnglish[testOrder[nowNum]])
        {
            ui->pushButtonNext->show();
            ui->pushButtonMark->show();
            if(isMarkClick==true)
                ui->labelMark->show();
        }

        if(nowEnterWord!=wordEnglish[testOrder[nowNum]])
        {
            ui->pushButtonNext->hide();
            ui->pushButtonMark->hide();
            ui->labelMark->hide();
        }
    }
}

void Spell::on_pushButtonNext_clicked()
{
    if(record[nowNum]>0)
        toReview.append(testOrder[nowNum]);
    nowNum++;
    if(nowNum<totalNum)
        GeneratePage();
    else
    {
        int rightNum=0;
        int markNum=0;
        int tipNum=0;
        int wrongNum=0;
        for(int i=0;i<totalNum;i++)
        {
            if(record[i]==0)
                rightNum++;
            if(record[i]==1)
                markNum++;
            if(record[i]==2)
                tipNum++;
            if(record[i]==3)
                wrongNum++;
        }
        spellReview->Init(rightNum,markNum,tipNum,wrongNum,totalNum);
        spellReview->exec();
        if(spellReview->GetUserAns()==true)
        {
            Init(order,testFilePath,toReview,source);
            return;
        }
        else
            emit(ShowMenu());
    }
}

void Spell::on_pushButtonTip1_clicked()
{
    if(wordChinese[testOrder[nowNum]].length()>=1)
    {
        ui->labelTipsContent->setText(QString(wordEnglish[testOrder[nowNum]][0]));
        for(int i=0;i<wordEnglish[testOrder[nowNum]].length()-1;i++)
            ui->labelTipsContent->setText(ui->labelTipsContent->text()+".");
        if(nowEnterWord!=wordEnglish[testOrder[nowNum]])
            record[nowNum]=std::max(record[nowNum],2);
    }
}

void Spell::on_pushButtonTip2_clicked()
{
    if(wordChinese[testOrder[nowNum]].length()>=2)
    {
        ui->labelTipsContent->setText(QString(wordEnglish[testOrder[nowNum]][0])+QString(wordEnglish[testOrder[nowNum]][1]));
        for(int i=0;i<wordEnglish[testOrder[nowNum]].length()-2;i++)
            ui->labelTipsContent->setText(ui->labelTipsContent->text()+".");
        if(nowEnterWord!=wordEnglish[testOrder[nowNum]])
            record[nowNum]=std::max(record[nowNum],2);
    }
}

void Spell::on_pushButtonTipR_clicked()
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

    if(nowEnterWord!=wordEnglish[testOrder[nowNum]])
        record[nowNum]=std::max(record[nowNum],2);
}

void Spell::on_pushButtonTipA_clicked()
{
    ui->labelTipsContent->setText(wordEnglish[testOrder[nowNum]]);
    if(nowEnterWord!=wordEnglish[testOrder[nowNum]])
        record[nowNum]=std::max(record[nowNum],3);
}

void Spell::on_pushButtonTipHide_clicked()
{
    ui->labelTipsContent->setText("");
    for(int i=0;i<wordEnglish[testOrder[nowNum]].length();i++)
        ui->labelTipsContent->setText(ui->labelTipsContent->text()+".");
}

void Spell::on_pushButtonMark_clicked()
{
    ui->labelMark->show();
    record[nowNum]=std::max(record[nowNum],1);
    isMarkClick=true;
}

void Spell::on_pushButtonHelp_clicked()
{
    spellHelp->exec();
}

void Spell::on_pushButtonSearch_clicked()
{
    ShowSearch(testFilePath);
}
