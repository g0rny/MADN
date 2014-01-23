#include "timeout.h"


Timeout::Timeout(QObject *parent) :
    QObject(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    aktSek=sekunden;
}

void Timeout::starte()
{
    aktSek=sekunden;
    timer->start(1000);

   /* int i=0;
    while(i<sekunden){
        //timer->start(1000);
        i++;
        std::cout << sekunden-i << std::endl;
        emit(sekundeVorbei(sekunden-i));
    }
    emit zeitAbgelaufen();*/
}

void Timeout::update()
{
    aktSek--;

    if(aktSek){
        std::cout << aktSek << std::endl;
        emit(sekundeVorbei(aktSek));
     }
    if(!aktSek){
        aktSek=sekunden;
        timer->stop();
        emit zeitAbgelaufen();
        return;
    }
}

/*void Timeout::timer()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}*/
