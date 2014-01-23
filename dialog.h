#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include "Netzwerkverbindung.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;

private slots:
    void on_pushButton_clicked();

signals:
    void verbindungHergestellt(Netzwerkverbindung *verbindung);
    void sendeName(QString name);
};

#endif // DIALOG_H
