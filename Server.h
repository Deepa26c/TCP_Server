#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include "mainwindow.h"

class MainWindow;
class Server:public QTcpServer
{
public:
    Server();

    Q_OBJECT
public:
    Server(MainWindow* pHelloServer,QObject *parent=0);
    MainWindow* m_pHelloWindow;

private slots:
    void readyRead();
    void disconnected();
protected:

    void incomingConnection(int socketfd);
private:
    QSet<QTcpSocket*> clients;

};

#endif // SERVER_H
