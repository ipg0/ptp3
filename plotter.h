#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include "database.h"


namespace Ui {
class Plotter;
}

class Plotter : public QWidget
{
    Q_OBJECT

public:
    explicit Plotter(QWidget *parent = nullptr);
    void showGraph(DatabaseNode *nodes, size_t quantity);
    ~Plotter();

private:
    Ui::Plotter *ui;
    size_t structureData(DatabaseNode *nodes, size_t quantity, size_t &startYear, size_t &endYear, size_t &min, size_t &max, size_t *&graphableData);
};

#endif // PLOTTER_H
