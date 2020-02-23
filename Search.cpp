#include "Search.h"
#include "ui_Search.h"

Search::Search(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Search)
{
    ui->setupUi(this);

    ui->labelSearchInfo->show();

    pushButtonResult[0]=ui->pushButtonResult0;
    pushButtonResult[1]=ui->pushButtonResult1;
    pushButtonResult[2]=ui->pushButtonResult2;
    pushButtonResult[3]=ui->pushButtonResult3;
    pushButtonResult[4]=ui->pushButtonResult4;

    for(int i=0;i<5;i++)
        pushButtonResult[i]->hide();

    ui->lineEditSearch->setAttribute(Qt::WA_InputMethodEnabled,false);

    totalNum=0;
}

Search::~Search()
{
    delete ui;
}

void Search::Init(QStringList offerFilePath)
{
    this->offerFilePath=offerFilePath;
    if(offerFilePath.length()==0)
        ui->pushButtonApply->setDisabled(true);
    ui->lineEditSearch->setFocus();
}

void Search::on_pushButtonSet_clicked()
{
    QStringList files=QFileDialog::getOpenFileNames(this,"请选择搜索单词库","D:/","JSON File (*.json)");
    if(files.length()==0)
        return;
    searchFilePath=files;
    ChangeSource();
}

void Search::on_pushButtonApply_clicked()
{
    searchFilePath=offerFilePath;
    ChangeSource();
}

void Search::ChangeSource()
{
    wordChinese.clear();
    wordEnglish.clear();

    bool learnFileCheck=true;

    for(int i=0;i<searchFilePath.length();i++)
    {
        QFile file(searchFilePath[i]);
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

        QJsonArray jsonArray=jsonDoc.array();
        for(int i=0;i<jsonArray.size();i++)
        {
            QJsonObject jsonObject=jsonArray[i].toObject();
            wordChinese.append(jsonObject.value("wordChinese").toString());
            wordEnglish.append(jsonObject.value("wordEnglish").toString());
        }
    }

    if(learnFileCheck==false)
    {
        wordChinese.clear();
        wordEnglish.clear();
        ui->labelWordBaseInfo->setText("选中的搜索单词库中存在损坏文件！");
    }
    else
    {
        ui->labelWordBaseInfo->setText("已选择搜索单词库："+QString::number(searchFilePath.length())+"个");
    }

    totalNum=wordChinese.size();
    on_lineEditSearch_textChanged(ui->lineEditSearch->text());
}

void Search::on_lineEditSearch_textChanged(const QString &arg1)
{
    if(arg1=="")
    {
        for(int i=0;i<5;i++)
            pushButtonResult[i]->hide();
        ui->labelSearchInfo->show();
        return;
    }

    fillList.clear();

    for(int i=0;i<totalNum;i++)
    {
        if(wordEnglish[i].startsWith(arg1))
            fillList.append(i);
        if(fillList.size()==5)
            break;
    }

    for(int i=0;i<5;i++)
    {
        if(i<fillList.size())
        {
            pushButtonResult[i]->setText(wordEnglish[fillList[i]]);
            pushButtonResult[i]->show();
        }
        else
            pushButtonResult[i]->hide();
    }

    if(fillList.size()==0)
        ui->labelSearchInfo->show();
    if(fillList.size()!=0)
        ui->labelSearchInfo->hide();
}

void Search::on_pushButtonResult0_clicked()
{
    OpenWordCard(0);
}

void Search::on_pushButtonResult1_clicked()
{
    OpenWordCard(1);
}

void Search::on_pushButtonResult2_clicked()
{
    OpenWordCard(2);
}

void Search::on_pushButtonResult3_clicked()
{
    OpenWordCard(3);
}

void Search::on_pushButtonResult4_clicked()
{
    OpenWordCard(4);
}

void Search::OpenWordCard(int buttonId)
{
    WordCard* wordCard=new WordCard();
    wordCard->Init(wordChinese[fillList[buttonId]],wordEnglish[fillList[buttonId]]);
    wordCard->show();
}
