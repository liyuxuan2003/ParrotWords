#ifndef CHOOSE_H
#define CHOOSE_H

#include <QFrame>
#include <QTime>
#include <QRadioButton>
#include <QButtonGroup>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include "ChooseMenu.h"

namespace Ui
{
    class Choose;
}

class Choose : public QFrame
{
    Q_OBJECT

public:
    explicit Choose(QWidget *parent = nullptr);
    ~Choose();

    void Init(ChooseMode::Mode mode,ChooseOrder::Order order,QStringList testFilePath,QStringList confuseFilePath,QList<int> review);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private slots:
    void on_pushButtonNext_clicked();

    void on_pushButtonExit_clicked();

private:
    Ui::Choose *ui;

    LiEasyLayout* l1;
    LiFixedToLayout* l2;

    ChooseMode::Mode mode;
    ChooseOrder::Order order;

    QStringList testFilePath;
    QStringList confuseFilePath;

    QStringList wordChineseTest;
    QStringList wordEnglishTest;

    QStringList wordChineseConfuse;
    QStringList wordEnglishConfuse;

    QRadioButton* radioButtons[4];

    QList<int> toReview;

    int* testOrder;

    int nowRightOption;

    int nowNum;
    int totalNum;

    void GeneratePage();

signals:
    void ShowMenu();

};

#endif // CHOOSE_H
