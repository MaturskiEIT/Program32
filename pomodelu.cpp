#include "pomodelu.h"
#include "ui_pomodelu.h"
#include "konekcija.h"
#include <QMessageBox>

PoModelu::PoModelu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PoModelu)
{
    ui->setupUi(this);

    Konekcija baza;
    if(!baza.dbOpen())
    {
        QMessageBox::critical(this, "Kriticno!!!", "Nismo povezani sa bazom podataka!!!");
    }
    else
    {
        QSqlQuery upit;

        upit.prepare("SELECT Naziv FROM Model ORDER BY Naziv;");
        if(!upit.exec())
        {
            QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
        }
        else
        {
            QSqlQueryModel *model;
            model = new QSqlQueryModel();
            model->setQuery(upit);
            ui->comboBoxModel->setModel(model);
        }

        upit.prepare("SELECT Naziv FROM Boja ORDER BY Naziv;");
        if(!upit.exec())
        {
            QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
        }
        else
        {
            QSqlQueryModel *model;
            model = new QSqlQueryModel();
            model->setQuery(upit);
            ui->comboBoxBoja->setModel(model);
        }

        upit.prepare("SELECT Naziv FROM Gorivo ORDER BY Naziv;");
        if(!upit.exec())
        {
            QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
        }
        else
        {
            QSqlQueryModel *model;
            model = new QSqlQueryModel();
            model->setQuery(upit);
            ui->comboBoxGorivo->setModel(model);
        }
    }
    baza.dbClose();
}

PoModelu::~PoModelu()
{
    delete ui;
}

void PoModelu::on_pushButtonIzadji_clicked()
{
    this->close();
}

void PoModelu::on_pushButtonPrikazi_clicked()
{
    QString model  = ui->comboBoxModel->currentText();
    QString boja   = ui->comboBoxBoja->currentText();
    QString gorivo = ui->comboBoxGorivo->currentText();
    QString godisteOd, godisteDo;

    switch (ui->comboBoxGodinaProizvodnje->currentIndex()) {
        case 0: godisteOd = "2015"; godisteDo = "2100"; break;
        case 1: godisteOd = "2010"; godisteDo = "2014"; break;
        case 2: godisteOd = "2005"; godisteDo = "2009"; break;
        case 3: godisteOd = "2000"; godisteDo = "2004"; break;
        case 4: godisteOd = "1995"; godisteDo = "1999"; break;
        case 5: godisteOd = "1990"; godisteDo = "1994"; break;
        case 6: godisteOd = "1900"; godisteDo = "1989";
    }

    Konekcija baza;
    if(!baza.dbOpen())
    {
        QMessageBox::critical(this, "Kriticno!!!", "Nismo povezani sa bazom podataka!!!");
    }
    else
    {
        QSqlQuery upit;

        upit.prepare("SELECT Vozilo.Registracija, Vozilo.PredjenoKM AS Kilometraza FROM Vozilo INNER JOIN Model ON Vozilo.ModelID = Model.ModelID INNER JOIN Boja ON Vozilo.BojaID = Boja.BojaID INNER JOIN Gorivo ON Vozilo.GorivoID = Gorivo.GorivoID WHERE Model.Naziv = :model AND Boja.Naziv = :boja AND Gorivo.Naziv = :gorivo AND (Vozilo.GodinaProizvodnje BETWEEN :godisteOd AND :godisteDo) ORDER BY Vozilo.PredjenoKM ASC, Vozilo.Registracija DESC;");
        upit.bindValue(":model", model);
        upit.bindValue(":boja", boja);
        upit.bindValue(":gorivo", gorivo);
        upit.bindValue(":godisteOd", godisteOd);
        upit.bindValue(":godisteDo", godisteDo);
        if(!upit.exec())
        {
            QMessageBox::critical(this, "Kriticno!!!", "SQL naredba nije izvrsena!!!");
        }
        else
        {
            QSqlQueryModel *model;
            model = new QSqlQueryModel();
            model->setQuery(upit);
            ui->tableView->setModel(model);
        }
    }
    baza.dbClose();
}
