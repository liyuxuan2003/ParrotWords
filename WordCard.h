#ifndef WORDCARD_H
#define WORDCARD_H

#include <QMainWindow>

#include <QTextToSpeech>
#include <QMediaPlayer>

namespace Ui
{
    class WordCard;
}

class WordCard : public QMainWindow
{
    Q_OBJECT

public:
    explicit WordCard(QWidget *parent = nullptr);
    ~WordCard();

    void Init(QString chinese,QString english);

    QString chinese;
    QString english;

    QTextToSpeech* tts;
    QMediaPlayer* player;

private slots:
    void on_pushButtonYoudao_clicked();

    void on_pushButtonMachine_clicked();

private:
    Ui::WordCard *ui;
};

#endif // WORDCARD_H
