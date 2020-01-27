#ifndef SPELL_H
#define SPELL_H

#include <algorithm>

#include <QFrame>
#include <QTime>
#include <QKeyEvent>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include "SpellMenu.h"
#include "SpellReview.h"

namespace Ui
{
    class Spell;
}

class Spell : public QFrame
{
    Q_OBJECT

public:
    explicit Spell(QWidget *parent = nullptr);
    ~Spell();

    void Init(SpellOrder::Order order,QStringList testFilePath,QList<int> review);

protected:
    virtual void resizeEvent(QResizeEvent * event);

    virtual void keyPressEvent(QKeyEvent *ev);

private slots:
    void on_pushButtonExit_clicked();

    void on_pushButtonNext_clicked();

    void on_pushButtonTip1_clicked();

    void on_pushButtonTip2_clicked();

    void on_pushButtonTipA_clicked();

    void on_pushButtonTipHide_clicked();

private:
    Ui::Spell *ui;

    LiEasyLayout* l1;
    LiFixedToLayout* l2;

    SpellReview* spellReview;

    SpellOrder::Order order;

    QStringList testFilePath;

    QStringList wordChineseTest;
    QStringList wordEnglishTest;

    QList<int> toReview;

    int* record;
    int* testOrder;

    int nowNum;
    int totalNum;

    QString nowEnterWord;

    void GeneratePage();

signals:
    void ShowMenu();
};

#endif // SPELL_H
