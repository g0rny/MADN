
#include "Server.h"
#include "QDataStream"
#include "QString"
#include <iostream>

Server::Server(QObject *parent) {
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(neueVerbindung()));

    server->listen(QHostAddress::Any, 60123);
    for (int i = 0; i < CLIENTS_MAX; ++i) {
        clients[i] = 0;
    }
    anzahlClients = 0;
}

void Server::neueVerbindung() {
    QTcpSocket *neuerClient = server->nextPendingConnection();
    if (anzahlClients >= CLIENTS_MAX) {
        neuerClient->disconnectFromHost();
    }
    clients[anzahlClients++] = neuerClient;
    connect(neuerClient, SIGNAL(readyRead()), this, SLOT(nachrichtEmpfangen()));
//    sendeBegruessung(neuerClient);
}

void Server::nachrichtEmpfangen() {
    QTcpSocket *client = dynamic_cast<QTcpSocket *>(sender());
    if (client == 0) {
        std::cerr << "Server::nachrichtEmpfangen : sender() ist nicht QTcpSocket";
    }
    while (client->canReadLine()) {
        QByteArray nachricht_bytes = client->readLine();
        QString nachricht = QString::fromUtf8(nachricht_bytes);
        QString typ = nachricht.section(QString::fromLatin1("\x1F"),0,0);
        if (typ == QString::fromLatin1("chat")) {
            for (int i = 0; i < anzahlClients; ++i) {
                if (clients[i] != client) {
                    clients[i]->write(nachricht_bytes);
                }
            }
            QString absender = nachricht.section(QString::fromLatin1("\x1F"),1,1);
            QString text = nachricht.section(QString::fromLatin1("\x1F"),2,-1);
            emit chatEmpfangen(QString::fromLatin1("<b>") + absender + QString::fromLatin1("</b>: ") + text);
        } else if (typ == QString::fromLatin1("wurf")) {
            for (int i = 0; i < anzahlClients; ++i) {
                if (clients[i] != client) {
                    clients[i]->write(nachricht_bytes);
                }
            }
            int augenzahl = nachricht.section(QString::fromLatin1("\x1F"),1,1).toInt();
            emit wurfelnEmpfangen(augenzahl);
        }
    }
}

void Server::sendeChat(QString name, QString nachricht) {
    for (int i = 0; i < anzahlClients; ++i) {
        clients[i]->write("chat");
        clients[i]->write("\x1F");
        clients[i]->write(name.toUtf8());
        clients[i]->write("\x1F");
        clients[i]->write(nachricht.toUtf8());
        clients[i]->write("\n");
    }
}

void Server::sendeWurfeln(int augenzahl) {
    for (int i = 0; i < anzahlClients; ++i) {
        clients[i]->write("wurf");
        clients[i]->write("\x1F");
        clients[i]->write(QString().setNum(augenzahl).toUtf8());
        clients[i]->write("\n");
    }
}

void Server::sendeZug(int zug) {

}
