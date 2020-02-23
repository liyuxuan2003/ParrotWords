#ifndef SELF_H
#define SELF_H

#include <QFrame>
#include <QTime>
#include <QKeyEvent>
#include <QTextToSpeech>
#include <QMediaPlayer>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include "GlobalEnum.h"

#include "SelfReview.h"
#include "SelfHelp.h"

namespace Ui
{
    class Self;
}

class Self : public QFrame
{
    Q_OBJECT

public:
    explicit Self(QWidget *parent = nullptr);
    ~Self();

    void Init(ModeEnum::Mode mode,OrderEnum::Order order,QStringList testFilePath,QList<int> review,AudioSourceEnum::AudioSource source);

protected:
    virtual void resizeEvent(QResizeEvent * event);

    virtual void keyPressEvent(QKeyEvent *ev);

private slots:
    void on_pushButtonExit_clicked();

    void on_pushButtonShowAns_clicked();

    void on_pushButtonRight_clicked();

    void on_pushButtonWrong_clicked();

    void on_pushButtonRead_clicked();

    void on_pushButtonHelp_clicked();

    void on_pushButtonSearch_clicked();

private:
    Ui::Self *ui;

    LiEasyLayout* l1;
    LiFixedToLayout* l2;

    SelfReview* selfReview;

    SelfHelp* selfHelp;

    OrderEnum::Order order;

    QStringList testFilePath;

    QStringList wordChinese;
    QStringList wordEnglish;

    QTextToSpeech* tts;
    QMediaPlayer* player;

    AudioSourceEnum::AudioSource source;

    ModeEnum::Mode mode;

    QList<int> toReview;

    int* record;
    int* testOrder;

    int nowNum;
    int totalNum;

    void GeneratePage();

    void NextPage();

signals:
    void ShowMenu();

    void ShowSearch(QStringList offerFilePath);
};

#endif // SELF_H
