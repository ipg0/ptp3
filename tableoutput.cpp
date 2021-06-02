#include "tableoutput.h"
#include "ui_tableoutput.h"

TableOutput::TableOutput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableOutput) {
    ui->setupUi(this);
}

void TableOutput::showTable(DatabaseNode *nodes, size_t quantity) {
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("Name"));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem("Year"));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem("Genre"));
    ui->tableWidget->setItem(0, 3, new QTableWidgetItem("Main Actor"));
    ui->tableWidget->setItem(0, 4, new QTableWidgetItem("Rating"));
    ui->tableWidget->setRowCount(quantity + 1);
    for(size_t i = 0; i < quantity; i++) {
        ui->tableWidget->setItem(i + 1, 0,
                                 new QTableWidgetItem(QString::fromLocal8Bit(nodes[i].name, strlen(nodes[i].name))));
        ui->tableWidget->setItem(i + 1, 1,
                                 new QTableWidgetItem(QString::number(nodes[i].year)));
        ui->tableWidget->setItem(i + 1, 2,
                                 new QTableWidgetItem(QString::fromLocal8Bit(nodes[i].genre, strlen(nodes[i].genre))));
        ui->tableWidget->setItem(i + 1, 3,
                                 new QTableWidgetItem(QString::fromLocal8Bit(nodes[i].mainCharacter, strlen(nodes[i].mainCharacter))));
        ui->tableWidget->setItem(i + 1, 4,
                                 new QTableWidgetItem(QString::number(nodes[i].rating)));
    }
    show();
}

TableOutput::~TableOutput() {
    delete ui;
}
