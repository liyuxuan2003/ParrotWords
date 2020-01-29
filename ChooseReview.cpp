#include "ChooseReview.h"
#include "ui_ChooseReview.h"

ChooseReview::ChooseReview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseReview)
{
    ui->setupUi(this);
}

ChooseReview::~ChooseReview()
{
    delete ui;
}

void ChooseReview::Init(int rightNum,int wrongNum,int markNum,int totalNum)
{
    ui->labelRightNum->setText("正确："+QString::number(rightNum));
    ui->labelWrongNum->setText("错误："+QString::number(wrongNum));
    ui->labelMarkNum->setText("标记："+QString::number(markNum));
    ui->labelTotalNum->setText("总计："+QString::number(totalNum));
    userAns=false;
    if(wrongNum!=0)
    {
        ui->labelReview->setText("是否进入复习模式？");
        ui->pushButtonYes->show();
        ui->pushButtonNo->show();
    }
    if(wrongNum==0)
    {
        ui->labelReview->setText("关闭窗口返回首页！");
        ui->pushButtonYes->hide();
        ui->pushButtonNo->hide();
    }
}

bool ChooseReview::GetUserAns()
{
    return userAns;
}

void ChooseReview::on_pushButtonYes_clicked()
{
    userAns=true;
    this->close();
}

void ChooseReview::on_pushButtonNo_clicked()
{
    userAns=false;
    this->close();
}
