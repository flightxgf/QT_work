#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->progressBar_heart->setRange(0,100);
    ui->progressBar_heart->setValue(0);

    connect(&m_heart,&QTimer::timeout,this,&MainWindow::heartTimeOut);
     m_heart.start(3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::heartTimeOut()
{
     m_heart.stop();
    static int s_heartCount = 0;
    ++s_heartCount;
    if(s_heartCount > 100)
    {
        s_heartCount = 0;
    }
    ui->progressBar_heart->setValue(s_heartCount);
     m_heart.start(500);
}
