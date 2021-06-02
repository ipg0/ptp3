#ifndef TABLEOUTPUT_H
#define TABLEOUTPUT_H

#include <QDialog>
#include "database.h"

namespace Ui {
class TableOutput;
}

class TableOutput : public QDialog {
    Q_OBJECT

public:
    explicit TableOutput(QWidget *parent = nullptr);
    void showTable(DatabaseNode *nodes, size_t quantity);
    ~TableOutput();

private:
    Ui::TableOutput *ui;
};

#endif
