#ifndef TESTTHREAD_H
#define TESTTHREAD_H

#include <QMutexLocker>
#include <QThread>
#include <QDebug>
#include <QObject>
#include <QTimer>
class testThread : public QObject
{
    Q_OBJECT

public:
    testThread();
   ~testThread();
    void doSomething();
    void doSomething1();

signals:
    void message(const QString& info);

public:
    void stopthread();
public slots:
    void runSomeBigWork1();
private:
    QMutex m_lock;
    bool m_isCanRun;
    int m_runCount;
    int m_runCount2;
};

#endif // TESTTHREAD_H
