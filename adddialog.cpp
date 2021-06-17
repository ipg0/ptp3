#include "adddialog.h"
#include "ui_adddialog.h"
#include "QIntValidator"

AddDialog::AddDialog(QWidget *parent, Database *_database) :
    QDialog(parent),
    ui(new Ui::AddDialog) {
    database = _database;
    ui->setupUi(this);
    ui->lineEdit_2->setValidator(new QIntValidator(this));
    ui->lineEdit_5->setValidator(new QIntValidator(this));
}

AddDialog::~AddDialog() {
    delete ui;
}

void AddDialog::on_pushButton_2_clicked() {
    database->add(DatabaseNode(ui->lineEdit->text().toLocal8Bit().data(),
                               ui->lineEdit_2->text().toLong(),
                               ui->lineEdit_4->text().toLocal8Bit().data(),
                               ui->lineEdit_3->text().toLocal8Bit().data(),
                               ui->lineEdit_5->text().toShort()
                      ));
    emit(updateCallback());
}

void AddDialog::on_pushButton_clicked() {
    close();
}
