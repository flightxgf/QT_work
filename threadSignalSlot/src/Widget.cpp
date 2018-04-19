#include "Widget.h"
#include "ui_Widget.h"
#include <QDebug>

//在Qt多线程中使用信号槽传递变量是非常安全的，不需要对变量进行加锁保护
//Qt经常用信号和槽传递变量，为了降低拷贝的消耗，传递变量时经常使用常引用(const &)作为变量的传递方式

TestThread::TestThread(QObject *par):QThread(par)
  ,m_abort(false)
{

}

TestThread::~TestThread()
{
    m_abort = true;
}

void TestThread::run()
{
    while(!m_abort)
    {
        if(1)
        {
            int a = 1;
            unsigned int add = (unsigned int)&a;
            emit signalData(a,add);
        }
        sleep(1);
       // m_abort = true;
    }
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_thread = new TestThread(this);
    connect(this,SIGNAL(signalData(int,unsigned int))
            ,SLOT(recDataQueuedConnection(int,unsigned int))
            ,Qt::QueuedConnection
            );
    connect(this,SIGNAL(signalData(int,unsigned int))
            ,SLOT(recDataDirectConnection(int,unsigned int))
            ,Qt::DirectConnection
            );
    connect(m_thread,SIGNAL(signalData(int,unsigned int))
            ,SLOT(recThreadData(int,unsigned int))
            );
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_test_clicked()
{
    if(!m_thread->isRunning())
    {
        m_thread->start();
    }
    int a = 1;
    unsigned int add = (unsigned int)&a;
    ui->textBrowser->append("start emit local signal");
    qDebug() <<"start emit";
    emit signalData(a,add);
    ui->textBrowser->append("after emit local signal");
    qDebug() <<"after emit";
}

void Widget::recDataDirectConnection(const int &a, unsigned int aAddress)
{
    if(a != 1)
    {
        ui->textBrowser->append("a != 1");
    }
    if(aAddress != (unsigned int)&a)
    {
        ui->textBrowser->append(QString("DirectConnection addr not same,rec a:%1,thread a:%2").arg((unsigned int)&a).arg(aAddress));
        qDebug() <<"start recDataDirectConnection";
    }
    else
    {
        ui->textBrowser->append(QString("DirectConnection addr is same,rec a:%1,thread a:%2").arg((unsigned int)&a).arg(aAddress));
        qDebug() <<"recDataDirectConnection";
    }
}

void Widget::recThreadData(const int &a, unsigned int aAddress)
{
    if(a != 1)
    {
        ui->textBrowser->append("a != 1");
    }
    if(aAddress != (unsigned int)&a)
    {
        ui->textBrowser->append(QString("[Thread]addr not same,rec a:%1,thread a:%2").arg((unsigned int)&a).arg(aAddress));
        qDebug() <<"recThreadData";
    }
    else
    {
        ui->textBrowser->append(QString("[Thread]addr is same,rec a:%1,thread a:%2").arg((unsigned int)&a).arg(aAddress));
        qDebug() <<"read emit";
    }

}

void Widget::recDataQueuedConnection(const int &a, unsigned int aAddress)
{
    if(a != 1)
    {
        ui->textBrowser->append("a != 1");
    }
    if(aAddress != (unsigned int)&a)
    {
         qDebug() <<"recDataQueuedConnection";
        ui->textBrowser->append(QString("QueuedConnection addr not same,rec a:%1,thread a:%2").arg((unsigned int)&a).arg(aAddress));
    }
    else
    {
        qDebug() <<"else recDataQueuedConnection";
        ui->textBrowser->append(QString("QueuedConnection addr is same,rec a:%1,thread a:%2").arg((unsigned int)&a).arg(aAddress));
    }
}


