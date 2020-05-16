#include "Server.h"

Server::Server(MainWindow* pHelloServer,QObject *parent):QTcpServer(parent)
{
   m_pHelloWindow = pHelloServer;
}

void Server::incomingConnection(int socketfd)
{
    QTcpSocket *client = new QTcpSocket(this);
    client->setSocketDescriptor(socketfd);
    clients.insert(client);

    m_pHelloWindow->addMessage("New Client from : "+client->peerAddress().toString());

    connect(client,SIGNAL(readyRead()),this,SLOT(readyRead()));
    connect(client,SIGNAL(disconnected()),this,SLOT(disconnected()));
}

void Server::readyRead()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    while(client->canReadLine())
    {
        QString line = QString::fromUtf8(client->readLine()).trimmed();
        m_pHelloWindow->addMessage(line);
    }
}

void Server::disconnected()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    qDebug() << "Client disconnected: "<< client->peerAddress().toString();

    clients.remove(client);
}
