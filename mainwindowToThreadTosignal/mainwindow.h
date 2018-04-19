#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

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

private:
    QTimer m_heart;
    testThread* m_thread;

};

#endif // MAINWINDOW_H
