#ifndef CHOOSEMENU_H
#define CHOOSEMENU_H

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

namespace Ui
{
    class ChooseMenu;
}

class ChooseMode
{
public:
    enum Mode{CE,EC};
};

class ChooseOrder
{
public:
    enum Order{Ordered,Random};
};

class ChooseMenu : public QFrame
{
    Q_OBJECT

public:
    explicit ChooseMenu(QWidget *parent = nullptr);
    ~ChooseMenu();

    void Init(ChooseMode::Mode mode);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    Ui::ChooseMenu *ui;

    LiEasyLayout* l1;
    LiFixedToLayout* l2;

    ChooseMode::Mode mode;
    ChooseOrder::Order order;

    QStringList testFilePath;
    QStringList confuseFilePath;

private slots:
    void on_pushButtonExit_clicked();

    void on_pushButtonTest_clicked();

    void on_pushButtonConfuse_clicked();

    void on_pushButtonStart_clicked();

    void on_radioButtonOrdered_toggled(bool checked);

    void on_radioButtonRandom_toggled(bool checked);

    void on_radioButtonSelect_toggled(bool checked);

signals:
    void ShowMenu();
    void ShowChoose(ChooseMode::Mode mode,ChooseOrder::Order order,QStringList testFilePath,QStringList confuseFilePath,QList<int> select);
};

#endif // CHOOSEMENU_H
