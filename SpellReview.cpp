#include "SpellReview.h"
#include "ui_SpellReview.h"

SpellReview::SpellReview(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpellReview)
{
    ui->setupUi(this);
}

SpellReview::~SpellReview()
{
    delete ui;
}

void SpellReview::Init(int rightNum,int markNum,int tipNum,int wrongNum,int totalNum)
{
    ui->labelRightNum->setText("正确："+QString::number(rightNum));
    ui->labelMarkNum->setText("标记："+QString::number(markNum));
    ui->labelTipNum->setText("提示："+QString::number(tipNum));
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

bool SpellReview::GetUserAns()
{
    return userAns;
}

void SpellReview::on_pushButtonYes_clicked()
{
    userAns=true;
    this->close();
}

void SpellReview::on_pushButtonNo_clicked()
{
    userAns=false;
    this->close();
}
