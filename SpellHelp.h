#ifndef SPELLHELP_H
#define SPELLHELP_H

#include <QDialog>

namespace Ui {
class SpellHelp;
}

class SpellHelp : public QDialog
{
    Q_OBJECT

public:
    explicit SpellHelp(QWidget *parent = nullptr);
    ~SpellHelp();

private:
    Ui::SpellHelp *ui;
};

#endif // SPELLHELP_H
