#ifndef CHOOSEREVIEW_H
#define CHOOSEREVIEW_H

#include <QDialog>

namespace Ui
{
    class ChooseReview;
}

class ChooseReview : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseReview(QWidget *parent = nullptr);
    ~ChooseReview();

    void Init(int rightNum,int markNum,int wrongNum,int totalNum);
    bool GetUserAns();

private slots:
    void on_pushButtonYes_clicked();

    void on_pushButtonNo_clicked();

private:
    Ui::ChooseReview *ui;

    bool userAns;
};

#endif // CHOOSEREVIEW_H
