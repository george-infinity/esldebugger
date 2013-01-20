#include "connectdialog.h"
#include "ui_connectdialog.h"
#include "esl_oop.h"
#include <QSocketNotifier>
#include <QDebug>
#include <QSharedPointer>

ConnectDialog::ConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);
    m_con = 0;
    m_snotifier = 0;
    qRegisterMetaType<QSharedPointer<ESLevent> >("QSharedPointer<ESLevent>");
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

void ConnectDialog::accept()
{
    m_con = new ESLconnection(ui->lineHost->text().toAscii().constData(),
                          QString::number(ui->spinPort->value()).toAscii().constData(),
                          ui->linePass->text().toAscii().constData());
    m_snotifier = new QSocketNotifier(m_con->socketDescriptor(), QSocketNotifier::Read, this);
    connect(m_snotifier, SIGNAL(activated(int)), this, SLOT(readyRead()));
    m_con->events("plain", "all");
    QDialog::accept();
}

void ConnectDialog::readyRead() {
    ESLevent *e = m_con->recvEvent();
    emit eventReceived(QSharedPointer<ESLevent>(e));
}
