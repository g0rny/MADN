#include "dialog.h"
#include "ui_dialog.h"

#include <QHostAddress>
#include <iostream>

#include "Client.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    QString strAdresse = ui->lineEdit->text();
    QHostAddress adresse;
    bool gueltig = adresse.setAddress(strAdresse);
    if (!gueltig) {
        std::cerr << "Dialog::on_pushButton_clicked : ungueltige Adresse " << strAdresse.toStdString();
        return;
    }
    Client *client = new Client(this->parent());
    bool verbunden = client->verbinden(adresse);
    if (!verbunden) {
        delete client;
        return;
    }
    emit verbindungHergestellt(client);
    emit sendeName(ui->lineEdit_2->text());
    this->close();
}
