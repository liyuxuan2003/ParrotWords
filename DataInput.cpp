#include "DataInput.h"
#include "ui_DataInput.h"

DataInput::DataInput(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::DataInput)
{
    ui->setupUi(this);

    l1=new LiEasyLayout(0,width(),height(),LiEasyLayout::left,0.6f);
    l2=new LiFixedToLayout();

    l1->AddUnit(ui->labelTitle);
    l1->AddUnit(ui->labelLocation);
    l1->AddUnit(new QWidget*[2]{ui->labelChinese,ui->lineEditChinese},2);
    l1->AddUnit(new QWidget*[2]{ui->labelEnglish,ui->lineEditEnglish},2);
    l1->AddUnit(new QWidget*[4]{ui->pushButtonPrev,ui->pushButtonNext,ui->pushButtonSave,ui->labelSaveInfo},4);

    l1->LayoutConfigDone();

    l2->AddUnit(ui->pushButtonExit,width(),height(),LiFixedCorner::RightBottom);

    ui->lineEditEnglish->setAttribute(Qt::WA_InputMethodEnabled,false);
}

DataInput::~DataInput()
{
    delete ui;
}

void DataInput::resizeEvent(QResizeEvent *event)
{
    l1->ResizeWithEasyLayout(width(),height());
    l2->ResizeWithFixedToLayout(width(),height());
}

void DataInput::Init(QString path,QString name,int num)
{
    this->path=path;
    this->name=name;
    this->num=num;

    nowNum=0;
    ui->pushButtonPrev->setDisabled(true);
    ui->pushButtonPrev->setEnabled(true);
    ui->labelLocation->setText("单词位置："+QString::number(nowNum+1)+"/"+QString::number(num));
    ui->labelSaveInfo->hide();

    ui->lineEditChinese->setText("");
    ui->lineEditEnglish->setText("");

    wordChinese.clear();
    wordEnglish.clear();

    for(int i=0;i<num;i++)
    {
        wordChinese.append("");
        wordEnglish.append("");
    }
}


void DataInput::on_pushButtonPrev_clicked()
{
    OnLocationChange(-1);
}

void DataInput::on_pushButtonNext_clicked()
{
    OnLocationChange(1);
}

void DataInput::OnLocationChange(int offset)
{
    wordChinese[nowNum]=ui->lineEditChinese->text();
    wordEnglish[nowNum]=ui->lineEditEnglish->text();

    ui->lineEditEnglish->setFocus();

    nowNum=nowNum+offset;
    if(nowNum>0 && nowNum<num-1)
    {
        ui->pushButtonPrev->setEnabled(true);
        ui->pushButtonNext->setEnabled(true);
    }
    else if(nowNum==0)
    {
        ui->pushButtonPrev->setDisabled(true);
        ui->pushButtonNext->setEnabled(true);
    }
    else if(nowNum==num-1)
    {
        ui->pushButtonPrev->setEnabled(true);
        ui->pushButtonNext->setDisabled(true);
    }
    ui->labelLocation->setText("单词位置："+QString::number(nowNum+1)+"/"+QString::number(num));
    ui->lineEditChinese->setText(wordChinese[nowNum]);
    ui->lineEditEnglish->setText(wordEnglish[nowNum]);
}

void DataInput::on_pushButtonSave_clicked()
{
    wordChinese[nowNum]=ui->lineEditChinese->text();
    wordEnglish[nowNum]=ui->lineEditEnglish->text();

    QFile file(path+name+".json");
    file.open(QIODevice::ReadWrite);
    file.resize(0);

    QJsonArray jsonArray;
    for(int i=0;i<num;i++)
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

void DataInput::on_pushButtonExit_clicked()
{
    emit(ShowMenu());
}
