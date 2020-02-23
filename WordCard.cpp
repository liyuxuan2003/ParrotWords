#include "WordCard.h"
#include "ui_WordCard.h"

WordCard::WordCard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WordCard)
{
    ui->setupUi(this);

    tts = new QTextToSpeech(this);
    tts->setLocale(QLocale::English);
    tts->setRate(0.0);
    tts->setPitch(1.0);
    tts->setVolume(1.0);

    player = new QMediaPlayer(this);
    player->setVolume(100);
}

WordCard::~WordCard()
{
    delete ui;
}

void WordCard::Init(QString chinese,QString english)
{
    ui->labelChinese->setText(chinese);
    ui->labelEnglish->setText(english);

    this->chinese=chinese;
    this->english=english;
}

void WordCard::on_pushButtonYoudao_clicked()
{
    player->setMedia(QUrl("http://dict.youdao.com/speech?audio="+english));
    player->play();
}

void WordCard::on_pushButtonMachine_clicked()
{
    tts->say(english);
}
