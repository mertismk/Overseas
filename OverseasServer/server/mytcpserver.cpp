#include "mytcpserver.h"

MyTcpServer::~MyTcpServer() {
    // mTcpSocket->close();
    mTcpServer->close();
    server_status = 0;
}

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent) {
    mTcpServer = new QTcpServer(this);
    connect(mTcpServer, &QTcpServer::newConnection, this,
            &MyTcpServer::slotNewConnection);

    if (!mTcpServer->listen(QHostAddress::Any, 33333)) {
        qDebug() << "server is not started";
    } else {
        server_status = 1;
        qDebug() << "server is started";
    }
}

void MyTcpServer::slotNewConnection() {
    if (server_status == 1) {
        QTcpSocket *cur_mTcpSocket;
        cur_mTcpSocket = mTcpServer->nextPendingConnection();
        connect(cur_mTcpSocket, &QTcpSocket::readyRead, this,
                &MyTcpServer::slotServerRead);
        connect(cur_mTcpSocket, &QTcpSocket::disconnected, this,
                &MyTcpServer::slotClientDisconnected);
        mTcpSocket.insert(cur_mTcpSocket->socketDescriptor(), cur_mTcpSocket);
        qDebug() << "new connection " << cur_mTcpSocket->socketDescriptor();
    }
}

void MyTcpServer::slotServerRead() {
    // QTcpSocket *cur_mTcpSocket = mTcpSocket[mTcpServer->socketDescriptor()];
    QTcpSocket *cur_mTcpSocket = qobject_cast<QTcpSocket *>(sender());

    if (cur_mTcpSocket->canReadLine()) {
        QString string = cur_mTcpSocket->readLine().trimmed();
        qDebug() << string;
        cur_mTcpSocket->write(fparsing(string.toUtf8()).toUtf8() + "\n");
    }
}

void MyTcpServer::slotClientDisconnected() {
    QTcpSocket *cur_mTcpSocket = (QTcpSocket *)sender();
    cur_mTcpSocket->close();
    auto iter = mTcpSocket.begin();
    while (iter.value() != cur_mTcpSocket) iter++;
    mTcpSocket.erase(iter);
    qDebug() << "client disconnected. number of clients = "
             << mTcpSocket.size();

    /*QTcpSocket *cur_mTcpSocket = mTcpSocket[mTcpServer->socketDescriptor()];
    cur_mTcpSocket->close(); */
}
