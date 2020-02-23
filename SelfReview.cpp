#include "SelfReview.h"
#include "ui_SelfReview.h"

SelfReview::SelfReview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelfReview)
{
    ui->setupUi(this);
}

SelfReview::~SelfReview()
{
    delete ui;
}

void SelfReview::Init(int rightNum,int wrongNum,int totalNum)
{
    ui->labelRightNum->setText("正确："+QString::number(rightNum));
    ui->labelWrongNum->setText("错误："+QString::number(wrongNum));
    ui->labelTotalNum->setText("总计："+QString::number(totalNum));
    userAns=false;
    if(rightNum==totalNum)
    {
        ui->labelReview->setText("关闭窗口返回首页！");
        ui->pushButtonYes->hide();
        ui->pushButtonNo->hide();
        ui->pushButtonYes->setDisabled(true);
        ui->pushButtonNo->setDisabled(true);
    }
    else
    {
        ui->labelReview->setText("是否进入复习模式？");
        ui->pushButtonYes->show();
        ui->pushButtonNo->show();
        ui->pushButtonYes->setEnabled(true);
        ui->pushButtonNo->setEnabled(true);
    }
}

bool SelfReview::GetUserAns()
{
    return userAns;
}

void SelfReview::on_pushButtonYes_clicked()
{
    userAns=true;
    this->close();
}

void SelfReview::on_pushButtonNo_clicked()
{
    userAns=false;
    this->close();
}
