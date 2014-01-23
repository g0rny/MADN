#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
void MainWindow::spielfelderInit()
{
    spielfeld[1]=ui->startposgelb;
    spielfeld[2]=ui->feld02;
    spielfeld[3]=ui->feld03;
    spielfeld[4]=ui->feld04;
    spielfeld[5]=ui->feld05;
    spielfeld[6]=ui->feld06;
    spielfeld[7]=ui->feld07;
    spielfeld[8]=ui->feld08;
    spielfeld[9]=ui->feld09;
    spielfeld[10]=ui->verzweigungsfeldgrun;
    spielfeld[11]=ui->startposgrun;
    spielfeld[12]=ui->feld12;
    spielfeld[13]=ui->feld13;
    spielfeld[14]=ui->feld14;
    spielfeld[15]=ui->feld15;
    spielfeld[16]=ui->feld16;
    spielfeld[17]=ui->feld17;
    spielfeld[18]=ui->feld18;
    spielfeld[19]=ui->feld19;
    spielfeld[20]=ui->verzweigungsfeldrot;
    spielfeld[21]=ui->startposrot;
    spielfeld[22]=ui->feld22;
    spielfeld[23]=ui->feld23;
    spielfeld[24]=ui->feld24;
    spielfeld[25]=ui->feld25;
    spielfeld[26]=ui->feld26;
    spielfeld[27]=ui->feld27;
    spielfeld[28]=ui->feld28;
    spielfeld[29]=ui->feld29;
    spielfeld[30]=ui->verzweigungsfeldblau;
    spielfeld[31]=ui->startposblau;
    spielfeld[32]=ui->feld32;
    spielfeld[33]=ui->feld33;
    spielfeld[34]=ui->feld34;
    spielfeld[35]=ui->feld35;
    spielfeld[36]=ui->feld36;
    spielfeld[37]=ui->feld37;
    spielfeld[38]=ui->feld38;
    spielfeld[39]=ui->feld39;
    spielfeld[40]=ui->verzweigungsfeldgelb;

    for(int i=1;i<41;i++)
        spielfeld[i]->setSpielfeldNr(i);
    for(int i=1;i<40;i++)
       spielfeld[i]->setNext(i+1);
    spielfeld[40]->setNext(1);
    for(int i=1;i<40;i++)
       spielfeld[i]->setZustand(nichtBelegt);
    for(int i=1;i<40;i++)
       spielfeld[i]->setalterZustand(nichtBelegt);
    for(int i=1;i<=40;i++)
       spielfeld[i]->setfeldNr(i);
// Belegung Farbe und next Feldeintrag bei den Zielfeldern für Verzweigungsfelder
    ui->verzweigungsfeldgrun->setFarbe(grun);
    ui->verzweigungsfeldgrun->setnextZielposition(5);
    ui->verzweigungsfeldrot->setFarbe(rot);
    ui->verzweigungsfeldrot->setnextZielposition(9);
    ui->verzweigungsfeldblau->setFarbe(blau);
    ui->verzweigungsfeldblau->setnextZielposition(13);
    ui->verzweigungsfeldgelb->setFarbe(gelb);
    ui->verzweigungsfeldgelb->setnextZielposition(1);
}
/**
 * @param anzahl
 * Spieleranzahl
 * @param figurArt
 * Figurart, die beim Erstellen des Spiels gewaehlt wird ( Normal, Schneemann, Smiley).
 */
void MainWindow::figurenInit(int anzahl,int figurArt)
{
    ui->animationGelb2->setPixmap(QPixmap(QString::fromUtf8("")));
    ui->animationRot2->setPixmap(QPixmap(QString::fromUtf8("")));
    ui->animationBlau2->setPixmap(QPixmap(QString::fromUtf8("")));
    ui->animationGrun2->setPixmap(QPixmap(QString::fromUtf8("")));
    for(int i=1;i<=40;i++)
    {
        spielfeld[i]->freistellen();
        spielfeld[i]->setFigurArt(figurArt);
    }
    for(int i=0;i<16;i++)
    {
        startfelder[i]->freistellen();
        startfelder[i]->setFigurArt(figurArt);
    }
    for(int i=1;i<17;i++)
    {
        zielfelder[i]->setZustand(nichtBelegt);
        zielfelder[i]->setFigurArt(figurArt);
    }
    if(anzahl>=1)
        for(int i=0;i<4;i++)
            startfelder[i]->feldBelegen(gelb);
    if(anzahl>=2)
        for(int i=4;i<8;i++)
            startfelder[i]->feldBelegen(grun);
    if(anzahl>=3)
        for(int i=8;i<12;i++)
            startfelder[i]->feldBelegen(rot);
    if(anzahl==4)
        for(int i=12;i<16;i++)
            startfelder[i]->feldBelegen(blau);

}

void MainWindow::zielfelderInit()
{
    zielfelder[1]=ui->zielfeldgelb1;
    zielfelder[2]=ui->zielfeldgelb2;
    zielfelder[3]=ui->zielfeldgelb3;
    zielfelder[4]=ui->zielfeldgelb4;
    zielfelder[5]=ui->zielfeldgrun1;
    zielfelder[6]=ui->zielfeldgrun2;
    zielfelder[7]=ui->zielfeldgrun3;
    zielfelder[8]=ui->zielfeldgrun4;
    zielfelder[9]=ui->zielfeldrot1;
    zielfelder[10]=ui->zielfeldrot2;
    zielfelder[11]=ui->zielfeldrot3;
    zielfelder[12]=ui->zielfeldrot4;
    zielfelder[13]=ui->zielfeldblau1;
    zielfelder[14]=ui->zielfeldblau2;
    zielfelder[15]=ui->zielfeldblau3;
    zielfelder[16]=ui->zielfeldblau4;

    for(int i=1;i<5;i++)
        zielfelder[i]->setNext(i+1);
    for(int i=5;i<9;i++)
        zielfelder[i]->setNext(i+1);
    for(int i=9;i<13;i++)
        zielfelder[i]->setNext(i+1);
    for(int i=13;i<17;i++)
        zielfelder[i]->setNext(i+1);
    // Die letzten 4 Zielfelder aller Farben zeigen auf NULL -> ENDE , leider hier nur '0'
    zielfelder[4]->setNext(0);
    zielfelder[8]->setNext(0);
    zielfelder[12]->setNext(0);
    zielfelder[16]->setNext(0);
    for(int i=1;i<17;i++){
        zielfelder[i]->setfeldNr(i);
        zielfelder[i]->setZustand(nichtBelegt);
    }
}

void MainWindow::startfelderInit(){
    startfelder[0]=ui->startfeldgelb1;
    startfelder[1]=ui->startfeldgelb2;
    startfelder[2]=ui->startfeldgelb3;
    startfelder[3]=ui->startfeldgelb4;
    startfelder[4]=ui->startfeldgrun1;
    startfelder[5]=ui->startfeldgrun2;
    startfelder[6]=ui->startfeldgrun3;
    startfelder[7]=ui->startfeldgrun4;
    startfelder[8]=ui->startfeldrot1;
    startfelder[9]=ui->startfeldrot2;
    startfelder[10]=ui->startfeldrot3;
    startfelder[11]=ui->startfeldrot4;
    startfelder[12]=ui->startfeldblau1;
    startfelder[13]=ui->startfeldblau2;
    startfelder[14]=ui->startfeldblau3;
    startfelder[15]=ui->startfeldblau4;
    for(int i=0;i<16;i++){
        startfelder[i]->setZustand(nichtBelegt);
    }
    for(int i=0;i<4;i++){
        startfelder[i]->setfeldNr(i);
        startfelder[i]->setNext(1);
    }
    for(int i=4;i<8;i++){
        startfelder[i]->setfeldNr(i);
        startfelder[i]->setNext(11);
    }
    for(int i=8;i<12;i++){
        startfelder[i]->setfeldNr(i);
        startfelder[i]->setNext(21);
    }
    for(int i=12;i<16;i++){
        startfelder[i]->setfeldNr(i);
        startfelder[i]->setNext(31);
    }
}
void MainWindow::wuerfelInit(){
    animationGelb[0]=ui->animationGelb1;
    animationGelb[1]=ui->animationGelb2;
    animationGelb[2]=ui->animationGelb3;
    animationGelb[3]=ui->animationGelb4;
    animationGelb[4]=ui->animationGelb5;
    animationGrun[0]=ui->animationGrun1;
    animationGrun[1]=ui->animationGrun2;
    animationGrun[2]=ui->animationGrun3;
    animationGrun[3]=ui->animationGrun4;
    animationGrun[4]=ui->animationGrun5;
    animationRot[0]=ui->animationRot1;
    animationRot[1]=ui->animationRot2;
    animationRot[2]=ui->animationRot3;
    animationRot[3]=ui->animationRot4;
    animationRot[4]=ui->animationRot5;
    animationBlau[0]=ui->animationBlau1;
    animationBlau[1]=ui->animationBlau2;
    animationBlau[2]=ui->animationBlau3;
    animationBlau[3]=ui->animationBlau4;
    animationBlau[4]=ui->animationBlau5;
}
/**
 * @param i
 * Fuer die Animationsreihenfolge ein Index.
 * @param augen
 * Aktuelle Augensumme, damit richtiges Bild gesetzt wird.
 */
void MainWindow::wuerfelAnimation(int i,int augen)
{

    if(madn->getAnDerReihe()==gelb){
           for(int i=0;i<=4;i++)
               animationGelb[i]->setPixmap(QPixmap(QString::fromUtf8("")));
           setzeBild(augen,i);
    }
    else if(madn->getAnDerReihe()==grun){
        for(int i=0;i<=4;i++)
            animationGrun[i]->setPixmap(QPixmap(QString::fromUtf8("")));
        setzeBild(augen,i);

        }
    else if(madn->getAnDerReihe()==rot){
        for(int i=0;i<=4;i++)
            animationRot[i]->setPixmap(QPixmap(QString::fromUtf8("")));
           setzeBild(augen,i);
        }
    else if(madn->getAnDerReihe()==blau){
        for(int i=0;i<=4;i++)
            animationBlau[i]->setPixmap(QPixmap(QString::fromUtf8("")));
           setzeBild(augen,i);
    }
}

/**
 * @param augen
 * Fuer die Animationsreihenfolge ein Index.
 * @param i
 * Fuer die Animationsreihenfolge ein Index.
 */
void MainWindow::setzeBild(int augen,int i)
{
    switch(augen)
    {
    case 1: switch(madn->getAnDerReihe())
        {
        case gelb:animationGelb[i]->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/gelb1.svg"))); break;
        case grun:animationGrun[i]->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/grun1.svg"))); break;
        case blau:animationBlau[i]->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/blau1.svg"))); break;
        case rot:animationRot[i]->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/rot1.svg"))); break;
        case nichtBelegt: break;
        }
        break;
    case 2: switch(madn->getAnDerReihe())
        {
        case gelb:animationGelb[i]->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/gelb2.svg"))); break;
        case grun:animationGrun[i]->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/grun2.svg"))); break;
        case blau:animationBlau[i]->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/blau2.svg"))); break;
        case rot:animationRot[i]->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/rot2.svg"))); break;
        case nichtBelegt: break;
        }
        break;
    case 3: switch(madn->getAnDerReihe())
        {
        case gelb:animationGelb[i]->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/gelb3.svg"))); break;
        case grun:animationGrun[i]->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/grun3.svg"))); break;
        case blau:animationBlau[i]->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/blau3.svg"))); break;
        case rot:animationRot[i]->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/rot3.svg"))); break;
        case nichtBelegt: break;
        }
        break;
    case 4: switch(madn->getAnDerReihe())
        {
        case gelb:animationGelb[i]->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/gelb4.svg"))); break;
        case grun:animationGrun[i]->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/grun4.svg"))); break;
        case blau:animationBlau[i]->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/blau4.svg"))); break;
        case rot:animationRot[i]->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/rot4.svg"))); break;
        case nichtBelegt: break;
        }
        break;
    case 5: switch(madn->getAnDerReihe())
        {
        case gelb:animationGelb[i]->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/gelb5.svg"))); break;
        case grun:animationGrun[i]->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/grun5.svg"))); break;
        case blau:animationBlau[i]->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/blau5.svg"))); break;
        case rot:animationRot[i]->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/rot5.svg"))); break;
        case nichtBelegt: break;
        }
        break;
    case 6: switch(madn->getAnDerReihe())
        {
        case gelb:animationGelb[i]->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/gelb6.svg"))); break;
        case grun:animationGrun[i]->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/grun6.svg"))); break;
        case blau:animationBlau[i]->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/blau6.svg"))); break;
        case rot:animationRot[i]->setPixmap(QPixmap(QString::fromUtf8(":/wurfel/grafiken/wurfel/rot6.svg"))); break;
        case nichtBelegt: break;
        }
        break;
    }
}

