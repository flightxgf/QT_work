#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include <QMutexLocker>
#include <QThread>
#include <QDebug>

class testThread : public QThread
{
    Q_OBJECT

public:
    testThread();
   ~testThread();
    void run();
    void doSomething();

signals:
    void message(const QString& info);

public:
    void stopthread();

private:
    QMutex m_lock;
    bool m_isCanRun;
    int m_runCount;
};

#endif // TESTTHREAD_H
