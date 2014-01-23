#ifndef NETZWERKVERBINDUNG_H
#define NETZWERKVERBINDUNG_H

#include <QObject>

class Zug;

enum NachrichtenTyp {
//    BEGRUESSUNG, //QString magic, quint32 version
//    BEITRITT, //QString name
    CHAT, //QString nachricht
//    WURFELN, //quint8 augenzahl
//    ZUG, //quint8 feld
//    AUSTRITT, //QString name
//    VERBINDUNGSABBRUCH //QString name
};

class Netzwerkverbindung : public QObject {
    Q_OBJECT
public slots:
    virtual void sendeChat(QString name, QString nachricht) = 0;
    virtual void sendeWurfeln(int augenzahl) = 0;
    virtual void sendeZug(int zug) = 0;
signals:
    void chatEmpfangen(QString nachricht);
    void wurfelnEmpfangen(int augenzahl);
    void zugEmpfangen(quint8 zug);
    void spielerBeigetreten(QString name);
    void spielerAusgetreten(QString name);
    void verbindungAbgebrochen(QString name);
};

#endif // NETZWERKVERBINDUNG_H
