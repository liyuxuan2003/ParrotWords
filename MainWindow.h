#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Menu.h"

#include "DataInputMenu.h"
#include "DataInput.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void ShowMenu();
    void ShowDataInputMenu();
    void ShowDataInput(QString path,QString name,int num);

protected:
    virtual void resizeEvent(QResizeEvent * event);

private:
    Ui::MainWindow* ui;

    Menu* menu;

    DataInputMenu* dataInputMenu;
    DataInput* dataInput;

    void HideAllFrame();
};

#endif // MAINWINDOW_H
