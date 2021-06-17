#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    database = new Database("data.bin");
    addDialog = new AddDialog(this, database);
    tableOutput = new TableOutput(this);
    connect(addDialog, &AddDialog::updateCallback, this, &MainWindow::onUpdateCallback);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("Name"));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem("Year"));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem("Genre"));
    ui->tableWidget->setItem(0, 3, new QTableWidgetItem("Main Actor"));
    ui->tableWidget->setItem(0, 4, new QTableWidgetItem("Rating"));
    ui->lineEdit->setValidator(new QIntValidator(this));
    plotter = new Plotter;
    redrawTable();
}

MainWindow::~MainWindow() {
    delete ui;
    delete database;
    delete addDialog;
}

void MainWindow::on_pushButton_clicked() {
    addDialog->open();
}

void MainWindow::on_pushButton_2_clicked() {
    database->remove(ui->tableWidget->selectedItems().back()->row() - 1);
    redrawTable();
}

void MainWindow::onUpdateCallback() {
    redrawTable();
}

void MainWindow::redrawTable() {
    for(size_t i = 0; i < ui->tableWidget->rowCount(); i++) {
        delete ui->tableWidget->item(i + 1, 0);
        delete ui->tableWidget->item(i + 1, 1);
        delete ui->tableWidget->item(i + 1, 2);
        delete ui->tableWidget->item(i + 1, 3);
        delete ui->tableWidget->item(i + 1, 4);
    }
    DatabaseNode *nodes = nullptr;
    DatabaseNode leastRated(const_cast<char *>(""), 0, const_cast<char *>("Unavailable"), const_cast<char *>(""), 127);
    size_t quantity = database->update(nodes);
    ui->tableWidget->setRowCount(quantity + 1);
    for(size_t i = 0; i < quantity; i++) {
        ui->tableWidget->setItem(i + 1, 0,
                                 new QTableWidgetItem(QString::fromLocal8Bit(nodes[i].name, strlen(nodes[i].name))));
        ui->tableWidget->setItem(i + 1, 1,
                                 new QTableWidgetItem(QString::number(nodes[i].year)));
        ui->tableWidget->setItem(i + 1, 2,
                                 new QTableWidgetItem(QString::fromLocal8Bit(nodes[i].genre, strlen(nodes[i].genre))));
        ui->tableWidget->setItem(i + 1, 3,
                                 new QTableWidgetItem(QString::fromLocal8Bit(nodes[i].mainActor, strlen(nodes[i].mainActor))));
        ui->tableWidget->setItem(i + 1, 4,
                                 new QTableWidgetItem(QString::number(nodes[i].rating)));
        if(leastRated.rating > nodes[i].rating)
            leastRated = nodes[i];
    }
    ui->lineEdit_5->setText(QString::fromLocal8Bit(leastRated.genre, strlen(leastRated.genre)));
}

void MainWindow::on_pushButton_3_clicked() {
    DatabaseNode *nodes = nullptr;
    size_t quantity = database->filter(nodes, ui->lineEdit_2->text().toLocal8Bit().data(), ui->lineEdit->text().toInt(), FilterOption::genreFilter);
    tableOutput->showTable(nodes, quantity);
}

void MainWindow::on_pushButton_10_clicked() {
    DatabaseNode *nodes = nullptr;
    size_t quantity = database->filter(nodes, ui->lineEdit_4->text().toLocal8Bit().data());
    tableOutput->showTable(nodes, quantity);
}

void MainWindow::on_pushButton_4_clicked() {
    DatabaseNode *nodes = nullptr;
    plotter->showGraph(nodes, database->update(nodes));
}

