#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Menu.h"

#include "DataInputMenu.h"
#include "DataInput.h"

#include "ChooseMenu.h"
#include "Choose.h"

#include "SpellMenu.h"
#include "Spell.h"

#include "LearnMenu.h"
#include "Learn.h"

#include "SelfMenu.h"
#include "Self.h"

#include "Search.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void ShowMenu();

    void ShowDataInputMenu();
    void ShowDataInput(QString path,QString name,int num);

    void ShowChooseMenu(ModeEnum::Mode mode);
    void ShowChoose(ModeEnum::Mode mode,OrderEnum::Order order,QStringList testFilePath,QStringList confuseFilePath,QList<int> select);

    void ShowSpellMenu();
    void ShowSpell(OrderEnum::Order order,QStringList testFilePath,QList<int> select,AudioSourceEnum::AudioSource source);

    void ShowLearnMenu();
    void ShowLearn(QStringList learnFilePath,bool showC,bool showE,AudioSourceEnum::AudioSource source);

    void ShowSelfMenu(ModeEnum::Mode mode);
    void ShowSelf(ModeEnum::Mode mode,OrderEnum::Order order,QStringList testFilePath,QList<int> select,AudioSourceEnum::AudioSource source);

    void ShowSearch(QStringList offerFilePath);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    Ui::MainWindow* ui;

    Menu* menu;

    DataInputMenu* dataInputMenu;
    DataInput* dataInput;

    ChooseMenu* chooseMenu;
    Choose* choose;

    SpellMenu* spellMenu;
    Spell* spell;

    LearnMenu* learnMenu;
    Learn* learn;

    SelfMenu* selfMenu;
    Self* self;

    Search* search;

    void HideAllFrame();
};

#endif // MAINWINDOW_H
