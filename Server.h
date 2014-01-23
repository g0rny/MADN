#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include "Netzwerkverbindung.h"

#define SPIELER_MAX 4
#define CLIENTS_MAX (SPIELER_MAX - 1)

class Server : public Netzwerkverbindung {
    Q_OBJECT
private:
    QTcpServer *server;
    QTcpSocket *clients[CLIENTS_MAX];
    int anzahlClients;
private slots:
    void neueVerbindung();
    void nachrichtEmpfangen();
public slots:
    void sendeChat(QString name, QString nachricht);
    void sendeWurfeln(int augenzahl);
    void sendeZug(int zug);
public:
    Server(QObject *parent);
};

#endif // SERVER_H
