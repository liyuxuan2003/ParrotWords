#include "Choose.h"
#include "ui_Choose.h"

Choose::Choose(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Choose)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f);
    l2=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(ui->labelLocation);
    l1->AddUnit(ui->labelQuestion);
    l1->AddUnit(new QWidget*[2]{ui->pushButtonA,ui->radioButtonA},2);
    l1->AddUnit(new QWidget*[2]{ui->pushButtonB,ui->radioButtonB},2);
    l1->AddUnit(new QWidget*[2]{ui->pushButtonC,ui->radioButtonC},2);
    l1->AddUnit(new QWidget*[2]{ui->pushButtonD,ui->radioButtonD},2);
    l1->AddUnit(new QWidget*[3]{ui->pushButtonNext,ui->pushButtonMark,ui->labelMark},3);

    l1->LayoutConfigDone();

    l2->AddUnit(ui->pushButtonExit,width(),height(),LiFixedCorner::RightBottom);
    l2->AddUnit(ui->pushButtonHelp,width(),height(),LiFixedCorner::RightTop);
    l2->AddUnit(ui->pushButtonSearch,width(),height(),LiFixedCorner::RightTop);

    radioButtons[0]=ui->radioButtonA;
    radioButtons[1]=ui->radioButtonB;
    radioButtons[2]=ui->radioButtonC;
    radioButtons[3]=ui->radioButtonD;

    chooseReview=new ChooseReview();
    chooseReview->hide();

    chooseHelp=new ChooseHelp();
    chooseHelp->hide();
}

Choose::~Choose()
{
    delete ui;
}

void Choose::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithFixedToLayout(width(),height());
}

void Choose::Init(ModeEnum::Mode mode,OrderEnum::Order order,QStringList testFilePath,QStringList confuseFilePath,QList<int> review)
{
    this->mode=mode;
    this->order=order;
    this->testFilePath=testFilePath;
    this->confuseFilePath=confuseFilePath;

    toReview.clear();

    if(mode==ModeEnum::CE)
        ui->labelTitle->setText("中译英选择练习");
    if(mode==ModeEnum::EC)
        ui->labelTitle->setText("英译中选择练习");

    wordChinese.clear();
    wordEnglish.clear();
    wordChineseConfuse.clear();
    wordEnglishConfuse.clear();

    for(int i=0;i<testFilePath.length();i++)
    {
        bool isExist=false;
        for(int j=0;j<confuseFilePath.length();j++)
        {
            if(testFilePath[i]==confuseFilePath[j])
            {
                isExist=true;
                break;
            }
        }
        if(isExist==false)
            confuseFilePath.append(testFilePath[i]);
    }

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

    for(int i=0;i<confuseFilePath.length();i++)
    {
        QFile file(confuseFilePath[i]);
        file.open(QIODevice::ReadOnly);

        QByteArray jsonData = file.readAll();
        file.close();

        QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData));
        QJsonArray jsonArray=jsonDoc.array();

        for(int i=0;i<jsonArray.size();i++)
        {
            QJsonObject jsonObject=jsonArray[i].toObject();
            wordChineseConfuse.append(jsonObject.value("wordChinese").toString());
            wordEnglishConfuse.append(jsonObject.value("wordEnglish").toString());
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

void Choose::GeneratePage()
{
    QTime time=QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);

    ui->labelMark->hide();

    for(int i=0;i<4;i++)
        radioButtons[i]->setStyleSheet("color: rgb(255, 255, 255);");

    for(int i=0;i<4;i++)
        radioButtons[i]->setAutoExclusive(false);

    for(int i=0;i<4;i++)
        radioButtons[i]->setChecked(false);

    for(int i=0;i<4;i++)
        radioButtons[i]->setAutoExclusive(true);

    wordCardChinese.clear();
    wordCardEnglish.clear();

    QList<int> wrongAns;
    wrongAns.clear();
    for(int i=0;i<4;i++)
    {
        int wa=0;
        bool isSame=false;
        do
        {
            isSame=false;
            wa=qrand()%wordChineseConfuse.length();
            if(wordChineseConfuse[wa]==wordChinese[testOrder[nowNum]] && wordEnglishConfuse[wa]==wordEnglish[testOrder[nowNum]])
                isSame=true;
            for (int j=0;j<i;j++)
            {
                if(wa==wrongAns[j])
                    isSame=true;
            }
        }
        while(isSame==true);
        wrongAns.append(wa);
        wordCardChinese.append(wordChineseConfuse[wa]);
        wordCardEnglish.append(wordEnglishConfuse[wa]);
    }

    if(mode==ModeEnum::CE)
    {
        ui->labelQuestion->setText(wordChinese[testOrder[nowNum]]);
        QString optstr[4];
        for(int i=0;i<4;i++)
            optstr[i]=wordEnglishConfuse[wrongAns[i]];
        nowRightOption=qrand()%4;
        optstr[nowRightOption]=wordEnglish[testOrder[nowNum]];
        wordCardChinese[nowRightOption]=wordChinese[testOrder[nowNum]];
        wordCardEnglish[nowRightOption]=wordEnglish[testOrder[nowNum]];
        for(int i=0;i<4;i++)
            radioButtons[i]->setText(optstr[i]);
    }

    if(mode==ModeEnum::EC)
    {
        ui->labelQuestion->setText(wordEnglish[testOrder[nowNum]]);
        QString optstr[4];
        for(int i=0;i<4;i++)
            optstr[i]=wordChineseConfuse[wrongAns[i]];
        nowRightOption=qrand()%4;
        optstr[nowRightOption]=wordChinese[testOrder[nowNum]];
        wordCardChinese[nowRightOption]=wordChinese[testOrder[nowNum]];
        wordCardEnglish[nowRightOption]=wordEnglish[testOrder[nowNum]];
        for(int i=0;i<4;i++)
            radioButtons[i]->setText(optstr[i]);
    }

    ui->labelLocation->setText("当前题目："+QString::number(nowNum+1)+"/"+QString::number(totalNum));

    this->setFocus();
}

void Choose::keyPressEvent(QKeyEvent *ev)
{
    this->setFocus();
    if(ev->key()==Qt::Key_1)
        ui->radioButtonA->click();
    if(ev->key()==Qt::Key_2)
        ui->radioButtonB->click();
    if(ev->key()==Qt::Key_3)
        ui->radioButtonC->click();
    if(ev->key()==Qt::Key_4)
        ui->radioButtonD->click();
    if(ev->key()==Qt::Key_0)
        ui->pushButtonMark->click();
    if(ev->key()==Qt::Key_Space)
        ui->pushButtonNext->click();
}

void Choose::on_pushButtonNext_clicked()
{
    int userAns=-1;
    for(int i=0;i<4;i++)
    {
        if(radioButtons[i]->isChecked()==true)
        {
            userAns=i;
            break;
        }
    }
    if(userAns==-1)
        return;
    if(nowRightOption==userAns)
    {
        nowNum++;
        for(int i=0;i<4;i++)
            radioButtons[i]->setChecked(false);
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
                    wrongNum++;
            }
            chooseReview->Init(rightNum,markNum,wrongNum,totalNum);
            chooseReview->exec();
            if(chooseReview->GetUserAns()==true)
            {
                Init(mode,order,testFilePath,confuseFilePath,toReview);
                return;
            }
            else
                emit(ShowMenu());
        }
    }
    else
    {
        if(toReview.isEmpty()==false)
        {
            if(testOrder[nowNum]!=toReview.last())
            {
                record[nowNum]=std::max(record[nowNum],2);
                toReview.append(testOrder[nowNum]);
            }
        }
        if(toReview.isEmpty()==true)
        {
            record[nowNum]=std::max(record[nowNum],2);
            toReview.append(testOrder[nowNum]);
        }
        radioButtons[nowRightOption]->setStyleSheet("color: rgb(255, 0, 0);");
    }
}

void Choose::on_pushButtonExit_clicked()
{
    emit(ShowMenu());
}

void Choose::on_pushButtonMark_clicked()
{
    ui->labelMark->show();
    record[nowNum]=std::max(record[nowNum],1);
    toReview.append(testOrder[nowNum]);
}

void Choose::on_pushButtonHelp_clicked()
{
    chooseHelp->exec();
}

void Choose::on_pushButtonSearch_clicked()
{
    ShowSearch(testFilePath);
}

void Choose::on_pushButtonA_clicked()
{
    WordCard* wordCard=new WordCard();
    wordCard->Init(wordCardChinese[0],wordCardEnglish[0]);
    wordCard->show();
}

void Choose::on_pushButtonB_clicked()
{
    WordCard* wordCard=new WordCard();
    wordCard->Init(wordCardChinese[1],wordCardEnglish[1]);
    wordCard->show();
}

void Choose::on_pushButtonC_clicked()
{
    WordCard* wordCard=new WordCard();
    wordCard->Init(wordCardChinese[2],wordCardEnglish[2]);
    wordCard->show();
}

void Choose::on_pushButtonD_clicked()
{
    WordCard* wordCard=new WordCard();
    wordCard->Init(wordCardChinese[3],wordCardEnglish[3]);
    wordCard->show();
}
