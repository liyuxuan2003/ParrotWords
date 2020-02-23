#ifndef SELFREVIEW_H
#define SELFREVIEW_H

#include <QDialog>

namespace Ui
{
    class SelfReview;
}

class SelfReview : public QDialog
{
    Q_OBJECT

public:
    explicit SelfReview(QWidget *parent = nullptr);
    ~SelfReview();

    void Init(int rightNum,int wrongNum,int totalNum);
    bool GetUserAns();

private slots:
    void on_pushButtonYes_clicked();

    void on_pushButtonNo_clicked();

private:
    Ui::SelfReview *ui;

    bool userAns;
};

#endif // SELFREVIEW_H
