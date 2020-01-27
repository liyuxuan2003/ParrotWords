#ifndef SPELLMENU_H
#define SPELLMENU_H

#include <QFrame>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>
#include <LiLibrary/LiFileName.h>

class SpellOrder
{
public:
    enum Order{Ordered,Random};
};

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

    SpellOrder::Order order;

    QStringList testFilePath;

private slots:
    void on_pushButtonExit_clicked();

    void on_pushButtonTest_clicked();

    void on_pushButtonStart_clicked();

    void on_radioButtonOrdered_toggled(bool checked);

    void on_radioButtonRandom_toggled(bool checked);

signals:
    void ShowMenu();
    void ShowSpell(SpellOrder::Order order,QStringList testFilePath);
};

#endif // SPELLMENU_H
