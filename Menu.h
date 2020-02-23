#ifndef MENU_H
#define MENU_H

#include <QFrame>
#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

#include "About.h"

#include "GlobalEnum.h"

namespace Ui
{
    class Menu;
}

class Menu : public QFrame
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

protected:
    virtual void resizeEvent(QResizeEvent * event);

private slots:
    void on_pushButtonDataInput_clicked();

    void on_pushButtonChooseEC_clicked();

    void on_pushButtonChooseCE_clicked();

    void on_pushButtonSpellCE_clicked();

    void on_pushButtonLearn_clicked();

    void on_pushButtonSelfEC_clicked();

    void on_pushButtonSelfCE_clicked();

    void on_pushButtonAbout_clicked();

    void on_pushButtonExit_clicked();

    void on_pushButtonSearch_clicked();

private:
    Ui::Menu* ui;

    About* about;

    LiEasyLayout* l1;

    LiFixedToLayout* l2;

signals:
    void ShowDataInputMenu();
    void ShowChooseMenu(ModeEnum::Mode mode);
    void ShowSelfMenu(ModeEnum::Mode mode);
    void ShowSpellMenu();
    void ShowLearnMenu();
    void ShowSearch(QStringList offerFilePath);
};

#endif // MENU_H
