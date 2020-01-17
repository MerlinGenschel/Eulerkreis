#include "animationwidget.h"
#include "ui_animationwidget.h"

#include <QSignalBlocker>

animationWidget::animationWidget(vector<Edge>eulerPath,QWidget *parent)
    : QDockWidget(parent)
    , ui(new Ui::AnimationWidget)
    , _eulerPath(eulerPath)
{
    ui->setupUi(this);
    fillAnimationWidget();
}

animationWidget::~animationWidget()
{
    delete ui;
}

void animationWidget::setzeAnimationsstatus(bool v)
{
    QSignalBlocker blocker(this); // kein Signal bei Änderungen aus dem Programm heraus
    ui->pushButton->setChecked(v);
}

void animationWidget::setzeAnimationsgeschwindigkeit(int v)
{
    QSignalBlocker blocker(this); // kein Signal bei Änderungen aus dem Programm heraus
}

//Gibt nach Prüfung auf Eulerkreis entsprechenden Text in der List View aus
void animationWidget::fillAnimationWidget()
{
    string result;
    if(!_eulerPath.empty())
    {
        if(_eulerPath[0].src == _eulerPath[_eulerPath.size()-1].dest)
        {
            qDebug()<<"Kreis";
            result.append("Ja, das ist ein Eulerkreis!");
        }
        else
            result.append("Das ist leider kein Eulerkreis...");
    }

    model = new QStringListModel(this);
    QStringList eulerResult;
    eulerResult << QString::fromStdString(result);
    model->setStringList(eulerResult);
    ui->eulerResult->setModel(model);
}

void animationWidget::on_pushButton_clicked(bool checked)
{
    //Falls kein Eulerkreis vorliegt, deaktiviere PushButton
    if(_eulerPath[0].src != _eulerPath[_eulerPath.size()-1].dest)
        ui->pushButton->setCheckable(false);
    else
        ui->pushButton->setCheckable(true);
    //Ändere Name des Push Buttons, wenn Animation aktiv ist
    neuerAnimationstatus(ui->pushButton->isChecked());
    if (ui->pushButton->isChecked() == true)
        ui->pushButton->setText("Animation Ende");
    else
    {
        if (ui->pushButton->isChecked()==false)
            ui->pushButton->setText("Animation Start");
    }
}

