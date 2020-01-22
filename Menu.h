#ifndef MENU_H
#define MENU_H

#include <QFrame>
#include <LiLibrary/LiEasyLayout.h>

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

private:
    Ui::Menu* ui;

    LiEasyLayout* l1;

signals:
    void ShowDataInputMenu();

};

#endif // MENU_H
