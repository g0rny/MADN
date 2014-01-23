#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include "Netzwerkverbindung.h"

class Client : public Netzwerkverbindung {
    Q_OBJECT
private:
    QTcpSocket *socket;
private slots:
    void nachrichtEmpfangen();
public:
    Client(QObject *parent);
    bool verbinden(QHostAddress adresse);
public slots:
    void sendeChat(QString name, QString nachricht);
    void sendeWurfeln(int augenzahl);
    void sendeZug(int zug);
signals:
    void verbindungVerloren();
};

#endif // CLIENT_H
