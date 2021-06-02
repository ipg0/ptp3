#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include "database.h"

namespace Ui {
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = nullptr, Database *_database = nullptr);
    ~AddDialog();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

signals:
    void updateCallback();

private:
    Database *database;
    Ui::AddDialog *ui;
};

#endif // ADDDIALOG_H
