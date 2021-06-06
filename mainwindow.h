#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include "adddialog.h"
#include "tableoutput.h"
#include "plotter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_4_clicked();

public slots:
    void onUpdateCallback();

private:
    Ui::MainWindow *ui;
    Database *database;
    AddDialog *addDialog;
    TableOutput *tableOutput;
    Plotter *plotter;
    void redrawTable();
};
#endif
