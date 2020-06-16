#include "DataInputText.h"
#include "ui_DataInputText.h"

DataInputText::DataInputText(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DataInputText)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f);
    l2=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(new QWidget*[2]{ui->labelMode,ui->comboBoxMode},2);
    l1->AddUnit(ui->labelWindow);
    l1->AddUnit(ui->plainTextEditWindow);
    l1->AddUnit(new QWidget*[2]{ui->pushButtonSave,ui->labelSaveInfo},2);

    l1->LayoutConfigDone();

    l2->AddUnit(ui->pushButtonExit,width(),height(),LiFixedCorner::RightBottom);
}

DataInputText::~DataInputText()
{
    delete ui;
}

void DataInputText::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithFixedToLayout(width(),height());
}

void DataInputText::Init(QString path,QString name)
{
    this->path=path;
    this->name=name;

    ui->plainTextEditWindow->clear();
    ui->labelSaveInfo->setText("");
}

void DataInputText::on_pushButtonSave_clicked()
{
    QString rawText=ui->plainTextEditWindow->toPlainText();

    QStringList splitText=rawText.split("\n");

    QStringList wordChinese;
    QStringList wordEnglish;

    if(splitText.size()%2!=0)
    {
        ui->labelSaveInfo->setText("输入的文本的行数为奇数，这是不合法的！");
        return;
    }

    for(int i=0;i<splitText.size();i+=2)
    {
        if(ui->comboBoxMode->currentIndex()==0)
        {
            wordChinese.append(splitText[i]);
            wordEnglish.append(splitText[i+1]);
        }
        if(ui->comboBoxMode->currentIndex()==1)
        {
            wordEnglish.append(splitText[i]);
            wordChinese.append(splitText[i+1]);
        }
    }

    QFile file(path+name+".json");
    file.open(QIODevice::ReadWrite);
    file.resize(0);

    QJsonArray jsonArray;
    for(int i=0;i<wordChinese.size();i++)
    {
        QJsonObject jsonObject;
        jsonObject.insert("wordChinese",wordChinese[i]);
        jsonObject.insert("wordEnglish",wordEnglish[i]);
        jsonArray.append(jsonObject);
    }

    QJsonDocument jsonDoc;
    jsonDoc.setArray(jsonArray);

    file.write(jsonDoc.toJson());
    file.close();

    ui->labelSaveInfo->show();
    ui->labelSaveInfo->setText("保存数据成功！（"+QTime::currentTime().toString()+"）");
}

void DataInputText::on_pushButtonExit_clicked()
{
    emit(ShowMenu());
}
