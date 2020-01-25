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

    chooseMenu=new ChooseMenu(this);
    chooseMenu->move(0,0);

    choose=new Choose(this);
    choose->move(0,0);

    HideAllFrame();
    menu->show();

    //DataInput
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

    //Choose
    connect(
        menu,SIGNAL(ShowChooseMenu(ChooseMode::Mode)),
        this,SLOT(ShowChooseMenu(ChooseMode::Mode)));

    connect(
        chooseMenu,SIGNAL(ShowMenu()),
        this,SLOT(ShowMenu()));

    connect(
        chooseMenu,SIGNAL(ShowChoose(ChooseMode::Mode,ChooseOrder::Order,QStringList,QStringList)),
        this,SLOT(ShowChoose(ChooseMode::Mode,ChooseOrder::Order,QStringList,QStringList)));

    connect(
        choose,SIGNAL(ShowMenu()),
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
    chooseMenu->resize(width(),height());
    choose->resize(width(),height());
}

void MainWindow::HideAllFrame()
{
    menu->hide();
    dataInputMenu->hide();
    dataInput->hide();
    chooseMenu->hide();
    choose->hide();
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

void MainWindow::ShowChooseMenu(ChooseMode::Mode mode)
{
    HideAllFrame();
    chooseMenu->show();
    chooseMenu->Init(mode);
}

void MainWindow::ShowChoose(ChooseMode::Mode mode,ChooseOrder::Order order,QStringList testFilePath,QStringList confuseFilePath)
{
    HideAllFrame();
    QList<int> emptyList;
    emptyList.clear();
    choose->show();
    choose->Init(mode,order,testFilePath,confuseFilePath,emptyList);
}
