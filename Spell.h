#ifndef SPELL_H
#define SPELL_H

#include <algorithm>

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

#include "SpellReview.h"
#include "SpellHelp.h"

#include "GlobalEnum.h"

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

    void Init(OrderEnum::Order order,QStringList testFilePath,QList<int> review,AudioSourceEnum::AudioSource source);

protected:
    virtual void resizeEvent(QResizeEvent * event);

    virtual void keyPressEvent(QKeyEvent *ev);

private slots:
    void on_pushButtonExit_clicked();

    void on_pushButtonNext_clicked();

    void on_pushButtonTip1_clicked();

    void on_pushButtonTip2_clicked();

    void on_pushButtonTipR_clicked();

    void on_pushButtonTipA_clicked();

    void on_pushButtonTipHide_clicked();

    void on_pushButtonMark_clicked();

    void on_pushButtonHelp_clicked();

    void on_pushButtonSearch_clicked();

private:
    Ui::Spell *ui;

    LiEasyLayout* l1;
    LiFixedToLayout* l2;

    SpellReview* spellReview;

    SpellHelp* spellHelp;

    OrderEnum::Order order;

    QStringList testFilePath;

    QStringList wordChineseTest;
    QStringList wordEnglishTest;

    QTextToSpeech* tts;
    QMediaPlayer* player;

    AudioSourceEnum::AudioSource source;

    QList<int> toReview;

    int* record;
    int* testOrder;

    bool isMarkClick;

    int nowNum;
    int totalNum;

    QString nowEnterWord;

    void GeneratePage();

signals:
    void ShowMenu();

    void ShowSearch(QStringList offerFilePath);
};

#endif // SPELL_H
