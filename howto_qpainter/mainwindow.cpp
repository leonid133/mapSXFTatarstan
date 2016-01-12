#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    wgt = new WMap(this);
    ui->verticalLayout->addWidget(wgt);
    connect( ui->OpenFileButton , SIGNAL( triggered() ), wgt, SLOT(SetFileNameSlot()) );
    connect( ui->checkBox , SIGNAL( clicked() ), wgt, SLOT(SlotSetBox1()) );
    connect( ui->checkBox_2 , SIGNAL( clicked() ), wgt, SLOT(SlotSetBox2()) );
    connect( ui->checkBox_3 , SIGNAL( clicked() ), wgt, SLOT(SlotSetBox3()) );
    connect( ui->checkBox_4 , SIGNAL( clicked() ), wgt, SLOT(SlotSetBox4()) );
    connect( ui->checkBox_5 , SIGNAL( clicked() ), wgt, SLOT(SlotSetBox5()) );
    connect( ui->checkBox_6 , SIGNAL( clicked() ), wgt, SLOT(SlotSetBox6()) );
    connect( ui->checkBox_7 , SIGNAL( clicked() ), wgt, SLOT(SlotSetBox7()) );
    connect( ui->checkBox_8 , SIGNAL( clicked() ), wgt, SLOT(SlotSetBox8()) );
    connect( ui->checkBox_9 , SIGNAL( clicked() ), wgt, SLOT(SlotSetBox9()) );
    connect( ui->checkBox_10 , SIGNAL( clicked() ), wgt, SLOT(SlotSetBox10()) );
    connect( ui->checkBox_11 , SIGNAL( clicked() ), wgt, SLOT(SlotSetBox11()) );
    connect( ui->checkBox_12 , SIGNAL( clicked() ), wgt, SLOT(SlotSetBox12()) );
    connect( ui->checkBox_13 , SIGNAL( clicked() ), wgt, SLOT(SlotSetBox13()) );
    connect( ui->checkBox_14 , SIGNAL( clicked() ), wgt, SLOT(SlotSetBox14()) );
    connect( ui->checkBox_15 , SIGNAL( clicked() ), wgt, SLOT(SlotSetBox15()) );
    connect( ui->checkBox_16 , SIGNAL( clicked() ), wgt, SLOT(SlotSetBox16()) );
}

MainWindow::~MainWindow()
{
    wgt->deleteLater();
    delete ui;
}


void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
