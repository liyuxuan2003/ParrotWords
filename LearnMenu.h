#ifndef LEARNMENU_H
#define LEARNMENU_H

#include <QFrame>
#include <QTime>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>
#include <LiLibrary/LiFileName.h>

#include "GlobalEnum.h"

namespace Ui
{
    class LearnMenu;
}

class LearnMenu : public QFrame
{
    Q_OBJECT

public:
    explicit LearnMenu(QWidget *parent = nullptr);
    ~LearnMenu();

    void Init();

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    Ui::LearnMenu *ui;

    LiEasyLayout* l1;
    LiFixedToLayout* l2;

    QStringList learnFilePath;

    bool showC;
    bool showE;

    AudioSourceEnum::AudioSource source;

signals:
    void ShowMenu();
    void ShowLearn(QStringList learnFilePath,bool showC,bool showE,AudioSourceEnum::AudioSource source);

private slots:
    void on_pushButtonTest_clicked();
    void on_pushButtonStart_clicked();
    void on_pushButtonExit_clicked();
    void on_radioButtonCE_toggled(bool checked);
    void on_radioButtonC_toggled(bool checked);
    void on_radioButtonE_toggled(bool checked);
    void on_comboBoxSource_activated(int index);
};

#endif // LEARNMENU_H
