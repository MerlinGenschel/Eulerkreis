#ifndef ENDDIALOG_H
#define ENDDIALOG_H
#include <QAbstractButton>
#include <QDialog>

namespace Ui {
class endDialog;
}

class endDialog : public QDialog
{
    Q_OBJECT

public:
    explicit endDialog(QWidget *parent = nullptr);
    ~endDialog();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

private:
    Ui::endDialog *ui;
};

#endif // ENDDIALOG_H
