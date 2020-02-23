#ifndef SEARCH_H
#define SEARCH_H

#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QDebug>

#include <LiLibrary/LiFileName.h>

#include "WordCard.h"

namespace Ui
{
    class Search;
}

class Search : public QMainWindow
{
    Q_OBJECT

public:
    explicit Search(QWidget *parent = nullptr);
    ~Search();

    void Init(QStringList offerFilePath);

    QStringList offerFilePath;
    QStringList searchFilePath;

    QStringList wordChinese;
    QStringList wordEnglish;

    QList<int> fillList;

    int totalNum;

    QPushButton* pushButtonResult[5];

private slots:
    void on_pushButtonSet_clicked();

    void on_pushButtonApply_clicked();

    void on_lineEditSearch_textChanged(const QString &arg1);

    void on_pushButtonResult0_clicked();

    void on_pushButtonResult1_clicked();

    void on_pushButtonResult2_clicked();

    void on_pushButtonResult3_clicked();

    void on_pushButtonResult4_clicked();

private:
    Ui::Search *ui;

    void ChangeSource();

    void OpenWordCard(int buttonId);
};

#endif // SEARCH_H
