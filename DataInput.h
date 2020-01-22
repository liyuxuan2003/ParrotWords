#ifndef DATAINPUT_H
#define DATAINPUT_H

#include <QFrame>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTime>

#include <LiLibrary/LiEasyLayout.h>
#include <LiLibrary/LiFixedToLayout.h>

namespace Ui
{
    class DataInput;
}

class DataInput : public QFrame
{
    Q_OBJECT

public:
    explicit DataInput(QWidget *parent = nullptr);
    ~DataInput();

    void Init(QString path,QString name,int num);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private slots:
    void on_pushButtonPrev_clicked();

    void on_pushButtonNext_clicked();

    void on_pushButtonSave_clicked();

    void on_pushButtonExit_clicked();

private:
    Ui::DataInput* ui;

    LiEasyLayout* l1;
    LiFixedToLayout* l2;

    QString path;
    QString name;
    int num;

    int nowNum;
    QString* wordChinese;
    QString* wordEnglish;

    void OnLocationChange(int offset);

signals:
    void ShowMenu();

};

#endif // DATAINPUT_H
