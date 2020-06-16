#ifndef DATAINPUTTEXT_H
#define DATAINPUTTEXT_H

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
    class DataInputText;
}

class DataInputText : public QFrame
{
    Q_OBJECT

public:
    explicit DataInputText(QWidget *parent = nullptr);
    ~DataInputText();

    void Init(QString path,QString name);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private slots:
    void on_pushButtonSave_clicked();

    void on_pushButtonExit_clicked();

private:
    Ui::DataInputText *ui;

    LiEasyLayout* l1;
    LiFixedToLayout* l2;

    QString path;
    QString name;

signals:
    void ShowMenu();
};

#endif // DATAINPUTTEXT_H
