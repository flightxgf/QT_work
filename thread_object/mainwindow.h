#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QThread>

class testThread;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void heartTimeOut();
    void receiveMessage(const QString& str);
    void on_pushButton_clicked();

signals:
    void startObjThreadWork1();
    void startObjThreadWork2();

private:
    QTimer m_heart;

    testThread* m_obj;
    QThread* m_objThread;

    void startObjThread();
};

#endif // MAINWINDOW_H
