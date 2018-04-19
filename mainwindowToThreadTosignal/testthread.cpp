#include "testthread.h"
#include <QString>

testThread::testThread()
{
    m_isCanRun = true;
}

testThread::~testThread()
{

}

void testThread::run()
{
    while (1) {
            msleep(1000);
            doSomething();
            QMutexLocker locker(&m_lock);
            if(!m_isCanRun)//在每次循环判断是否可以运行，如果不行就退出循环
            {
                return;
            }
    }
}

void testThread::doSomething()
{
    qDebug()<<"----------------thread  doSomething--------------------";
    emit message(QString("-------------emit message--------"));
}

void testThread::stopthread()
{
        QMutexLocker locker(&m_lock);
        m_isCanRun = false;
}
