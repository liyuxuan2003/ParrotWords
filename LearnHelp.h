#ifndef LEARNHELP_H
#define LEARNHELP_H

#include <QDialog>

namespace Ui {
class LearnHelp;
}

class LearnHelp : public QDialog
{
    Q_OBJECT

public:
    explicit LearnHelp(QWidget *parent = nullptr);
    ~LearnHelp();

private:
    Ui::LearnHelp *ui;
};

#endif // LEARNHELP_H
