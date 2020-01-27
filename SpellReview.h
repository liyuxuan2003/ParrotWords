#ifndef SPELLREVIEW_H
#define SPELLREVIEW_H

#include <QDialog>

namespace Ui {
class SpellReview;
}

class SpellReview : public QDialog
{
    Q_OBJECT

public:
    explicit SpellReview(QWidget *parent = nullptr);
    ~SpellReview();

    void Init(int rightNum,int tipNum,int wrongNum,int totalNum);
    bool GetUserAns();

private slots:
    void on_pushButtonYes_clicked();

    void on_pushButtonNo_clicked();

private:
    Ui::SpellReview* ui;

    bool userAns;
};

#endif // SPELLREVIEW_H
