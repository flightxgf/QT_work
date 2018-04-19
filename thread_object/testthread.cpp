#include "testthread.h"
#include <QString>

testThread::testThread()
{
        m_isCanRun = true;
        m_runCount = 10;
        m_runCount2 = 20;
}

testThread::~testThread()
{

}

void testThread::runSomeBigWork1()
{
    while (1) {
            usleep(1000*1000);
            doSomething1();
//            QMutexLocker locker(&m_lock);
//            if(!m_isCanRun)//在每次循环判断是否可以运行，如果不行就退出循环
//            {
//                return;
//            }
    }
}

void testThread::doSomething()
{
    qDebug()<<"----------------thread  doSomething2--------------------"<<m_runCount;
    emit message(QString("-------------emit message2--------"));
}
void testThread::doSomething1()
{
    qDebug()<<"----------------thread  doSomething1--------------------"<<m_runCount2;
    emit message(QString("-------------emit message1--------"));
}

void testThread::stopthread()
{
        QMutexLocker locker(&m_lock);
        m_isCanRun = false;
}
