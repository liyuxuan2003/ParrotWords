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

    void ShowChooseMenu(ChooseMode::Mode mode);
    void ShowChoose(ChooseMode::Mode mode,ChooseOrder::Order order,QStringList testFilePath,QStringList confuseFilePath,QList<int> select);

    void ShowSpellMenu();
    void ShowSpell(SpellOrder::Order order,QStringList testFilePath,QList<int> select);

    void ShowLearnMenu();
    void ShowLearn(QStringList learnFilePath,bool showC,bool showE);

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

    void HideAllFrame();
};

#endif // MAINWINDOW_H
