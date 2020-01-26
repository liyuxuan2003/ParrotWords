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
    l1->AddUnit(ui->radioButtonA);
    l1->AddUnit(ui->radioButtonB);
    l1->AddUnit(ui->radioButtonC);
    l1->AddUnit(ui->radioButtonD);
    l1->AddUnit(ui->pushButtonNext);

    l1->LayoutConfigDone();

    l2->AddUnit(ui->pushButtonExit,width(),height(),LiFixedCorner::RightBottom);

    radioButtons[0]=ui->radioButtonA;
    radioButtons[1]=ui->radioButtonB;
    radioButtons[2]=ui->radioButtonC;
    radioButtons[3]=ui->radioButtonD;
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

void Choose::Init(ChooseMode::Mode mode,ChooseOrder::Order order,QStringList testFilePath,QStringList confuseFilePath,QList<int> review)
{
    this->mode=mode;
    this->order=order;
    this->testFilePath=testFilePath;
    this->confuseFilePath=confuseFilePath;

    toReview.clear();

    if(mode==ChooseMode::CE)
        ui->labelTitle->setText("中译英选择练习");
    if(mode==ChooseMode::EC)
        ui->labelTitle->setText("英译中选择练习");

    for(int i=0;i<4;i++)
        radioButtons[i]->setAutoExclusive(false);

    for(int i=0;i<4;i++)
        radioButtons[i]->setChecked(false);

    for(int i=0;i<4;i++)
        radioButtons[i]->setAutoExclusive(true);

    wordChineseTest.clear();
    wordEnglishTest.clear();
    wordChineseConfuse.clear();
    wordEnglishConfuse.clear();

    for(int i=0;i<testFilePath.length();i++)
    {
        bool isExist=false;
        for(int j=0;j<confuseFilePath.length();i++)
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
            wordChineseTest.append(jsonObject.value("wordChinese").toString());
            wordEnglishTest.append(jsonObject.value("wordEnglish").toString());
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
        totalNum=wordChineseTest.length();
    if(review.length()!=0)
        totalNum=review.length();

    testOrder=new int[totalNum];
    if(review.length()==0)
        for(int i=0;i<totalNum;i++)
            testOrder[i]=i;
    if(review.length()!=0)
        for(int i=0;i<totalNum;i++)
            testOrder[i]=review[i];

    QTime time=QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    if(order==ChooseOrder::Random)
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

    for(int i=0;i<4;i++)
        radioButtons[i]->setAutoExclusive(false);

    for(int i=0;i<4;i++)
        radioButtons[i]->setChecked(false);

    for(int i=0;i<4;i++)
        radioButtons[i]->setAutoExclusive(true);

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
            if(wordChineseConfuse[wa]==wordChineseTest[testOrder[nowNum]] && wordEnglishConfuse[wa]==wordEnglishTest[testOrder[nowNum]])
                isSame=true;
            for (int j=0;j<i;j++)
            {
                if(wa==wrongAns[j])
                    isSame=true;
            }
        }
        while(isSame==true);
        wrongAns.append(wa);
    }

    if(mode==ChooseMode::CE)
    {
        ui->labelQuestion->setText(wordChineseTest[testOrder[nowNum]]);
        QString optstr[4];
        for(int i=0;i<4;i++)
            optstr[i]=wordEnglishConfuse[wrongAns[i]];
        nowRightOption=qrand()%4;
        optstr[nowRightOption]=wordEnglishTest[testOrder[nowNum]];
        for(int i=0;i<4;i++)
            radioButtons[i]->setText(optstr[i]);
    }

    if(mode==ChooseMode::EC)
    {
        ui->labelQuestion->setText(wordEnglishTest[testOrder[nowNum]]);
        QString optstr[4];
        for(int i=0;i<4;i++)
            optstr[i]=wordChineseTest[wrongAns[i]];
        nowRightOption=qrand()%4;
        optstr[nowRightOption]=wordChineseTest[testOrder[nowNum]];
        for(int i=0;i<4;i++)
            radioButtons[i]->setText(optstr[i]);
    }

    ui->labelLocation->setText("当前题目："+QString::number(nowNum+1)+"/"+QString::number(totalNum));
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
    if(nowRightOption==userAns)
    {
        nowNum++;
        for(int i=0;i<4;i++)
            radioButtons[i]->setChecked(false);
        if(nowNum<totalNum)
            GeneratePage();
        else
            emit(ShowMenu());
    }
    else
    {
        qDebug() << nowRightOption;
        toReview.append(testOrder[nowNum]);
    }
}

void Choose::on_pushButtonExit_clicked()
{
    emit(ShowMenu());
}
