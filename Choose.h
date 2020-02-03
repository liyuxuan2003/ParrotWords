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

#include "ChooseMenu.h"
#include "ChooseReview.h"
#include "ChooseHelp.h"

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

    virtual void keyPressEvent(QKeyEvent *ev);

private slots:
    void on_pushButtonNext_clicked();

    void on_pushButtonExit_clicked();

    void on_pushButtonMark_clicked();

    void on_pushButtonHelp_clicked();

private:
    Ui::Choose *ui;

    ChooseReview* chooseReview;

    ChooseHelp* chooseHelp;

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

    int* record;
    int* testOrder;

    int nowRightOption;

    int nowNum;
    int totalNum;

    void GeneratePage();

signals:
    void ShowMenu();

};

#endif // CHOOSE_H
