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
    l1->AddUnit(new QWidget*[4]{ui->pushButtonTip1,ui->pushButtonTip2,ui->pushButtonTipA,ui->pushButtonTipHide},4);
    l1->AddUnit(new QWidget*[2]{ui->labelTips,ui->labelTipsContent},2);
    l1->AddUnit(ui->pushButtonNext);

    l1->LayoutConfigDone();

    l2->AddUnit(ui->pushButtonExit,width(),height(),LiFixedCorner::RightBottom);

    spellReview=new SpellReview();
    spellReview->hide();
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

void Spell::Init(SpellOrder::Order order,QStringList testFilePath,QList<int> review)
{

    ui->labelTitle->setText("中译英拼写练习");
    if(review.length()!=0)
        ui->labelTitle->setText(ui->labelTitle->text()+"-复习模式");
    this->testFilePath=testFilePath;
    this->order=order;

    wordChineseTest.clear();
    wordEnglishTest.clear();
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
            wordChineseTest.append(jsonObject.value("wordChinese").toString());
            wordEnglishTest.append(jsonObject.value("wordEnglish").toString());
        }
    }

    nowNum=0;
    if(review.length()==0)
    {
        totalNum=wordChineseTest.length();
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
    if(order==SpellOrder::Random)
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
    ui->labelQuestion->setText(wordChineseTest[testOrder[nowNum]]);

    nowEnterWord="";

    QString dotString="";
    for(int i=0;i<wordEnglishTest[testOrder[nowNum]].length();i++)
        dotString.append(".");
    ui->labelTipsContent->setText(dotString);
    ui->labelInput->setText("<font color=\"#FFFFFF\">"+dotString+"</font>");

    ui->pushButtonNext->hide();

    this->setFocus();
}

void Spell::keyPressEvent(QKeyEvent *ev)
{
    this->setFocus();
    if(ev->key()==Qt::Key_1)
        ui->pushButtonTip1->click();
    if(ev->key()==Qt::Key_2)
        ui->pushButtonTip2->click();
    if(ev->key()==Qt::Key_3)
        ui->pushButtonTipA->click();
    if(ev->key()==Qt::Key_4)
        ui->pushButtonTipHide->click();
    if(ev->key()==Qt::Key_Space && nowEnterWord==wordEnglishTest[testOrder[nowNum]])
        ui->pushButtonNext->click();
    if(ev->key()==Qt::Key_Backspace)
        nowEnterWord.chop(1);
    if(ev->key()>=Qt::Key_A && ev->key()<=Qt::Key_Z && nowEnterWord.length()<wordEnglishTest[testOrder[nowNum]].length())
    {
        char keyInput='a';
        keyInput=keyInput+(ev->key()-Qt::Key_A);
        nowEnterWord.append(keyInput);
    }
    ui->labelInput->clear();
    for(int i=0;i<wordEnglishTest[testOrder[nowNum]].length();i++)
    {
        if(i<nowEnterWord.length())
        {
            if(wordEnglishTest[testOrder[nowNum]][i]==nowEnterWord[i])
                ui->labelInput->setText(ui->labelInput->text()+"<font color=\"#FFFFFF\">"+nowEnterWord[i]+"</font>");
            if(wordEnglishTest[testOrder[nowNum]][i]!=nowEnterWord[i])
                ui->labelInput->setText(ui->labelInput->text()+"<font color=\"#FF0000\">"+nowEnterWord[i]+"</font>");
        }
        else
            ui->labelInput->setText(ui->labelInput->text()+"<font color=\"#FFFFFF\">.</font>");
    }
    if(nowEnterWord==wordEnglishTest[testOrder[nowNum]])
        ui->pushButtonNext->show();
    if(nowEnterWord!=wordEnglishTest[testOrder[nowNum]])
        ui->pushButtonNext->hide();
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
        int tipNum=0;
        int wrongNum=0;
        for(int i=0;i<totalNum;i++)
        {
            if(record[i]==0)
                rightNum++;
            if(record[i]==1 || record[i]==2)
                tipNum++;
            if(record[i]==3)
                wrongNum++;
        }
        spellReview->Init(rightNum,tipNum,wrongNum,totalNum);
        spellReview->exec();
        if(spellReview->GetUserAns()==true)
        {
            Init(order,testFilePath,toReview);
            return;
        }
        else
            emit(ShowMenu());
    }
}

void Spell::on_pushButtonTip1_clicked()
{
    if(wordChineseTest[testOrder[nowNum]].length()>=1)
    {
        ui->labelTipsContent->setText(QString(wordEnglishTest[testOrder[nowNum]][0]));
        for(int i=0;i<wordEnglishTest[testOrder[nowNum]].length()-1;i++)
            ui->labelTipsContent->setText(ui->labelTipsContent->text()+".");
        record[nowNum]=std::max(record[nowNum],1);
    }
}

void Spell::on_pushButtonTip2_clicked()
{
    if(wordChineseTest[testOrder[nowNum]].length()>=2)
    {
        ui->labelTipsContent->setText(QString(wordEnglishTest[testOrder[nowNum]][0])+QString(wordEnglishTest[testOrder[nowNum]][1]));
        for(int i=0;i<wordEnglishTest[testOrder[nowNum]].length()-2;i++)
            ui->labelTipsContent->setText(ui->labelTipsContent->text()+".");
        record[nowNum]=std::max(record[nowNum],2);
    }
}

void Spell::on_pushButtonTipA_clicked()
{
    ui->labelTipsContent->setText(wordEnglishTest[testOrder[nowNum]]);
    record[nowNum]=std::max(record[nowNum],3);
}

void Spell::on_pushButtonTipHide_clicked()
{
    ui->labelTipsContent->setText("");
    for(int i=0;i<wordEnglishTest[testOrder[nowNum]].length();i++)
        ui->labelTipsContent->setText(ui->labelTipsContent->text()+".");
}
