#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>


namespace Ui {
class ConnectDialog;
}

class ESLconnection;
class ESLevent;
class QSocketNotifier;

class ConnectDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ConnectDialog(QWidget *parent = 0);
    ~ConnectDialog();
    
protected:
    void accept();

signals:
    void eventReceived(QSharedPointer<ESLevent>);

private slots:
    void readyRead();

private:
    Ui::ConnectDialog *ui;
    ESLconnection *m_con;
    QSocketNotifier *m_snotifier;
};

#endif // CONNECTDIALOG_H
