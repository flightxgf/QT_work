#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "testthread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    ,m_objThread(NULL)
    ,m_obj(NULL)
{
    ui->setupUi(this);

    ui->progressBar_heart->setRange(0,100);
    ui->progressBar_heart->setValue(0);

    connect(&m_heart,&QTimer::timeout,this,&MainWindow::heartTimeOut);

    startObjThread();

     m_heart.start(3);
}

MainWindow::~MainWindow()
{
    if(m_objThread)
    {
        m_objThread->quit();
    }
    m_objThread->wait();

    delete ui;
}

void MainWindow::startObjThread()
{
    if(m_objThread)
    {
        return;
    }
    m_objThread= new QThread();
    m_obj = new testThread();
    m_obj->moveToThread(m_objThread);

    connect(m_objThread, SIGNAL(finished()), m_objThread, SLOT(deleteLater()));//delete   QThread
    connect(m_objThread, SIGNAL(finished()), m_obj, SLOT(deleteLater()));

    connect(m_obj, SIGNAL(message(QString)), this, SLOT(receiveMessage(QString)));
    connect(this, SIGNAL(startObjThreadWork1()), m_obj, SLOT(runSomeBigWork1()));

    m_objThread->start();

    emit startObjThreadWork1();
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
    if(m_objThread)
    {
            if(m_obj)
            {
                m_obj->stopthread();
            }
    }
}
