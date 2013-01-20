#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
#include "esl_oop.h"

class ConnectDialog;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_btnConnect_clicked();
    void eventReceived(QSharedPointer<ESLevent>);

    void on_btnClear_clicked();

private:
    Ui::MainWindow *ui;
    ConnectDialog *m_connection_dialog;
    int m_calls;
    int m_channels;
};

#endif // MAINWINDOW_H
