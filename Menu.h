#ifndef MENU_H
#define MENU_H

#include <QFrame>
#include <LiLibrary/LiEasyLayout.h>

#include"ChooseMenu.h"

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

private:
    Ui::Menu* ui;

    LiEasyLayout* l1;

signals:
    void ShowDataInputMenu();
    void ShowChooseMenu(ChooseMode::Mode mode);
    void ShowSpellMenu();
};

#endif // MENU_H
