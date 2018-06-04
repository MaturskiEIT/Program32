#include "glavniprozor.h"
#include "ui_glavniprozor.h"
#include "konekcija.h"
#include "boja.h"
#include "pomodelu.h"

GlavniProzor::GlavniProzor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GlavniProzor)
{
    ui->setupUi(this);
}

GlavniProzor::~GlavniProzor()
{
    delete ui;
}

void GlavniProzor::on_actionIzlaz_triggered()
{
    this->close();
}

void GlavniProzor::on_actionBoja_triggered()
{
    Boja *b = new Boja(this);
    b->setModal(true);
    b->show();
}

void GlavniProzor::on_actionPo_modelu_triggered()
{
    PoModelu *pm = new PoModelu(this);
    pm->setModal(true);
    pm->show();
}
