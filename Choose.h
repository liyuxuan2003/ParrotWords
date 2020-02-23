#ifndef CHOOSE_H
#define CHOOSE_H

#include <algorithm>

#include <QFrame>
#include <QTime>
#include <QRadioButton>
#include <QKeyEvent>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include "ChooseReview.h"
#include "ChooseHelp.h"

#include "WordCard.h"

#include "GlobalEnum.h"

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

    void Init(ModeEnum::Mode mode,OrderEnum::Order order,QStringList testFilePath,QStringList confuseFilePath,QList<int> review);

protected:
    virtual void resizeEvent(QResizeEvent * event);

    virtual void keyPressEvent(QKeyEvent *ev);

private slots:
    void on_pushButtonNext_clicked();

    void on_pushButtonExit_clicked();

    void on_pushButtonMark_clicked();

    void on_pushButtonHelp_clicked();

    void on_pushButtonSearch_clicked();

    void on_pushButtonA_clicked();

    void on_pushButtonB_clicked();

    void on_pushButtonC_clicked();

    void on_pushButtonD_clicked();

private:
    Ui::Choose *ui;

    ChooseReview* chooseReview;

    ChooseHelp* chooseHelp;

    LiEasyLayout* l1;
    LiFixedToLayout* l2;

    ModeEnum::Mode mode;
    OrderEnum::Order order;

    QStringList testFilePath;
    QStringList confuseFilePath;

    QStringList wordChineseTest;
    QStringList wordEnglishTest;

    QStringList wordChineseConfuse;
    QStringList wordEnglishConfuse;

    QRadioButton* radioButtons[4];

    QList<int> toReview;

    QStringList wordCardChinese;
    QStringList wordCardEnglish;

    int* record;
    int* testOrder;

    int nowRightOption;

    int nowNum;
    int totalNum;

    void GeneratePage();

signals:
    void ShowMenu();

    void ShowSearch(QStringList offerFilePath);

};

#endif // CHOOSE_H
