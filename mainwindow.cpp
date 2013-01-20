#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectdialog.h"
#include <QDebug>
#include "esl.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_connection_dialog = 0;
    m_calls = m_channels = 0;
    connect(ui->btnQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnConnect_clicked()
{
    if (!m_connection_dialog) {
        m_connection_dialog = new ConnectDialog(this);
        connect(m_connection_dialog, SIGNAL(eventReceived(QSharedPointer<ESLevent>)), this, SLOT(eventReceived(QSharedPointer<ESLevent>)));
    }
    m_connection_dialog->show();
}

void MainWindow::eventReceived(QSharedPointer<ESLevent> e) {
    switch(e.data()->event->event_id) {
    case ESL_EVENT_CHANNEL_BRIDGE:
        m_calls++;
        break;
    case ESL_EVENT_CHANNEL_UNBRIDGE:
        m_calls--;
        break;
    default:
        break;
    }
    ui->lblCallCount->setText(QString("%1 active calls").arg(m_calls));
    if (QString(e.data()->getHeader("Unique-ID")).isEmpty())
        return;
    QList<QTreeWidgetItem *> list_items = ui->treeChannels->findItems(e.data()->getHeader("Unique-ID"), Qt::MatchExactly, 0);
    QTreeWidgetItem *curr_parent = 0;
    if (list_items.isEmpty()) {
        curr_parent = new QTreeWidgetItem(QStringList(e.data()->getHeader("Unique-ID")));
        ui->treeChannels->insertTopLevelItem(ui->treeChannels->topLevelItemCount(), curr_parent);
    } else {
        if (list_items.size() > 1) {
            qDebug() << "Error! We have more than one UUID on tree!!!";
            return;
        }
        curr_parent = list_items.first();
    }
    QTreeWidgetItem *event = new QTreeWidgetItem(QStringList(e.data()->getType()));
    curr_parent->addChild(event);
    const char* header = e.data()->firstHeader();
    do {
        QStringList l;
        l << QString(header) << e.data()->getHeader(header);
        event->addChild(new QTreeWidgetItem(l));
        header = e.data()->nextHeader();
    } while(header != NULL);
}

void MainWindow::on_btnClear_clicked()
{
    ui->treeChannels->clear();
}
