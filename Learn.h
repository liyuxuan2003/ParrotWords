#ifndef LEARN_H
#define LEARN_H

#include <QFrame>
#include <QTime>
#include <QKeyEvent>
#include <QTextToSpeech>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include "LearnHelp.h"

namespace Ui
{
    class Learn;
}

class Learn : public QFrame
{
    Q_OBJECT

public:
    explicit Learn(QWidget *parent = nullptr);
    ~Learn();

    void Init(QStringList learnFilePath,bool showC,bool showE);

protected:
    virtual void resizeEvent(QResizeEvent * event);

    virtual void keyPressEvent(QKeyEvent *ev);

private:
    Ui::Learn *ui;

    LearnHelp* learnHelp;

    LiEasyLayout* l1;
    LiFixedToLayout* l2;

    QStringList learnFilePath;

    QStringList wordChineseLearn;
    QStringList wordEnglishLearn;

    QTextToSpeech* tts;

    int nowNum;
    int totalNum;

    bool* isShowChinese;
    bool* isShowEnglish;

    void GeneratePage();
    void ChangeShowMode();
    void OnLocationChange(int offset);

signals:
    void ShowMenu();

private slots:
    void on_pushButtonShowChinese_clicked();
    void on_pushButtonShowEnglish_clicked();
    void on_pushButtonRead_clicked();
    void on_pushButtonPrev_clicked();
    void on_pushButtonNext_clicked();
    void on_pushButtonExit_clicked();
    void on_pushButtonHelp_clicked();
};

#endif // LEARN_H
