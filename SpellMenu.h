#ifndef SPELLMENU_H
#define SPELLMENU_H

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
    class SpellMenu;
}

class SpellMenu : public QFrame
{
    Q_OBJECT

public:
    explicit SpellMenu(QWidget *parent = nullptr);
    ~SpellMenu();

    void Init();

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    Ui::SpellMenu *ui;

    LiEasyLayout* l1;
    LiFixedToLayout* l2;

    OrderEnum::Order order;
    AudioSourceEnum::AudioSource source;

    QStringList testFilePath;

private slots:
    void on_pushButtonExit_clicked();

    void on_pushButtonTest_clicked();

    void on_pushButtonStart_clicked();

    void on_radioButtonOrdered_toggled(bool checked);

    void on_radioButtonRandom_toggled(bool checked);

    void on_radioButtonSelect_toggled(bool checked);

    void on_comboBoxSource_activated(int index);

signals:
    void ShowMenu();
    void ShowSpell(OrderEnum::Order order,QStringList testFilePath,QList<int> select,AudioSourceEnum::AudioSource source);
};

#endif // SPELLMENU_H
