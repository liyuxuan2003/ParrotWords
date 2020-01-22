#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    menu=new Menu(this);
    menu->move(0,0);

    dataInputMenu=new DataInputMenu(this);
    dataInputMenu->move(0,0);

    dataInput=new DataInput(this);
    dataInput->move(0,0);

    HideAllFrame();
    menu->show();

    connect(
        menu,SIGNAL(ShowDataInputMenu()),
        this,SLOT(ShowDataInputMenu()));

    connect(
        dataInputMenu,SIGNAL(ShowDataInput(QString,QString,int)),
        this,SLOT(ShowDataInput(QString,QString,int)));

    connect(
        dataInputMenu,SIGNAL(ShowMenu()),
        this,SLOT(ShowMenu()));

    connect(
        dataInput,SIGNAL(ShowMenu()),
        this,SLOT(ShowMenu()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    menu->resize(width(),height());
    dataInputMenu->resize(width(),height());
    dataInput->resize(width(),height());
}

void MainWindow::HideAllFrame()
{
    menu->hide();
    dataInputMenu->hide();
    dataInput->hide();
}

void MainWindow::ShowMenu()
{
    HideAllFrame();
    menu->show();
}

void MainWindow::ShowDataInputMenu()
{
    HideAllFrame();
    dataInputMenu->show();
    dataInputMenu->Init();
}

void MainWindow::ShowDataInput(QString path,QString name,int num)
{
    HideAllFrame();
    dataInput->show();
    dataInput->Init(path,name,num);
}
