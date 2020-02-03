#ifndef CHOOSEHELP_H
#define CHOOSEHELP_H

#include <QDialog>

namespace Ui {
class ChooseHelp;
}

class ChooseHelp : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseHelp(QWidget *parent = nullptr);
    ~ChooseHelp();

private:
    Ui::ChooseHelp *ui;
};

#endif // CHOOSEHELP_H
