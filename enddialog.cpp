#include "enddialog.h"
#include "ui_enddialog.h"
#include <QMessageBox>
#include <QCloseEvent>

endDialog::endDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::endDialog)
{
    ui->setupUi(this);
}

endDialog::~endDialog()
{
    delete ui;
}


void endDialog::on_pushButton_2_clicked()
{
    //speichern
}

void endDialog::on_pushButton_3_clicked()
{
  //abbrechenQt::WA_DeleteOnClose;
}

void endDialog::on_pushButton_clicked()
{
    QApplication::quit();

}

