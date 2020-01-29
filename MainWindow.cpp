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

    spellMenu=new SpellMenu(this);
    spellMenu->move(0,0);

    spell=new Spell(this);
    spell->move(0,0);

    learnMenu=new LearnMenu(this);
    learnMenu->move(0,0);

    learn=new Learn(this);
    learn->move(0,0);

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
        chooseMenu,SIGNAL(ShowChoose(ChooseMode::Mode,ChooseOrder::Order,QStringList,QStringList,QList<int>)),
        this,SLOT(ShowChoose(ChooseMode::Mode,ChooseOrder::Order,QStringList,QStringList,QList<int>)));

    connect(
        choose,SIGNAL(ShowMenu()),
        this,SLOT(ShowMenu()));

    //Spell
    connect(
        menu,SIGNAL(ShowSpellMenu()),
        this,SLOT(ShowSpellMenu()));

    connect(
        spellMenu,SIGNAL(ShowMenu()),
        this,SLOT(ShowMenu()));

    connect(
        spellMenu,SIGNAL(ShowSpell(SpellOrder::Order,QStringList,QList<int>)),
        this,SLOT(ShowSpell(SpellOrder::Order,QStringList,QList<int>)));

    connect(
        spell,SIGNAL(ShowMenu()),
        this,SLOT(ShowMenu()));

    //Learn
    connect(
        menu,SIGNAL(ShowLearnMenu()),
        this,SLOT(ShowLearnMenu()));

    connect(
        learnMenu,SIGNAL(ShowMenu()),
        this,SLOT(ShowMenu()));

    connect(
        learnMenu,SIGNAL(ShowLearn(QStringList)),
        this,SLOT(ShowLearn(QStringList)));

    connect(
        learn,SIGNAL(ShowMenu()),
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

    spellMenu->resize(width(),height());
    spell->resize(width(),height());

    learnMenu->resize(width(),height());
    learn->resize(width(),height());
}

void MainWindow::HideAllFrame()
{
    menu->hide();

    dataInputMenu->hide();
    dataInput->hide();

    chooseMenu->hide();
    choose->hide();

    spellMenu->hide();
    spell->hide();

    learnMenu->hide();
    learn->hide();
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

void MainWindow::ShowChoose(ChooseMode::Mode mode,ChooseOrder::Order order,QStringList testFilePath,QStringList confuseFilePath,QList<int> select)
{
    HideAllFrame();
    choose->show();
    choose->Init(mode,order,testFilePath,confuseFilePath,select);
}

void MainWindow::ShowSpellMenu()
{
    HideAllFrame();
    spellMenu->show();
    spellMenu->Init();
}

void MainWindow::ShowSpell(SpellOrder::Order order,QStringList testFilePath,QList<int> select)
{
    HideAllFrame();
    spell->show();
    spell->Init(order,testFilePath,select);
}

void MainWindow::ShowLearnMenu()
{
    HideAllFrame();
    learnMenu->show();
    learnMenu->Init();
}

void MainWindow::ShowLearn(QStringList learnFilePath)
{
    HideAllFrame();
    learn->show();
    learn->Init(learnFilePath);
}
