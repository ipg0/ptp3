#include "adddialog.h"
#include "ui_adddialog.h"

AddDialog::AddDialog(QWidget *parent, Database *_database) :
    QDialog(parent),
    ui(new Ui::AddDialog) {
    database = _database;
    ui->setupUi(this);
}

AddDialog::~AddDialog() {
    delete ui;
}

void AddDialog::on_pushButton_2_clicked() {
    database->add(DatabaseNode(ui->lineEdit->text().toLocal8Bit().data(),
                               ui->lineEdit_2->text().toLong(),
                               ui->lineEdit_3->text().toLocal8Bit().data(),
                               ui->lineEdit_4->text().toLocal8Bit().data(),
                               ui->lineEdit_5->text().toShort()
                      ));
    emit(updateCallback());
}

void AddDialog::on_pushButton_clicked() {
    close();
}
