#ifndef TIMEOUT_H
#define TIMEOUT_H

#include <QObject>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>
#include <iostream>
#include <QTimer>

class Timeout : public QObject
{
    Q_OBJECT
private:
    int sekunden;
    int aktSek;
    //void timer();

public:
    explicit Timeout(QObject *parent = 0);
    void setSekunden(int _sekunden){ sekunden=_sekunden;}
    QTimer *timer;

signals:
    void sekundeVorbei(int);
    void zeitAbgelaufen();

public slots:
    void starte();
    void update();
};

#endif // TIMEOUT_H
