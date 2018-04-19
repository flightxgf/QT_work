#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "testthread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->progressBar_heart->setRange(0,100);
    ui->progressBar_heart->setValue(0);

    connect(&m_heart,&QTimer::timeout,this,&MainWindow::heartTimeOut);

    //全局线程的创建
    m_thread = new testThread();
    connect(m_thread, SIGNAL(message(QString)), this, SLOT(receiveMessage(QString)));
     m_heart.start(3);

     if(m_thread->isRunning())
     {
         return;
     }
     m_thread->start();
}

MainWindow::~MainWindow()
{
    m_thread->stopthread();
    m_thread->wait();

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

void MainWindow::receiveMessage(const QString &str)
{
    qDebug() << "-----------------main receiveMessage---------------------"<<str;
}

void MainWindow::on_pushButton_clicked()
{
    m_thread->stopthread();
}
