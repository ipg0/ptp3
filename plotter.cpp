#include "plotter.h"
#include "ui_plotter.h"
#include <QGraphicsTextItem>

Plotter::Plotter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Plotter)
{
    ui->setupUi(this);
}

size_t Plotter::structureData(DatabaseNode *nodes, size_t quantity, size_t &startYear, size_t &endYear, size_t &min, size_t &max, size_t *&graphableData) {
    if(quantity < 2)
        throw;
    startYear = nodes[0].year;
    endYear = nodes[0].year;
    for(size_t i = 0; i < quantity; i++) {
        if(nodes[i].rating < 8) continue;
        if(nodes[i].year < startYear)
              startYear = nodes[i].year;
        if(nodes[i].year > endYear)
              endYear = nodes[i].year;
    }
    graphableData = new size_t[endYear - startYear + 1];
    for(size_t i = 0; i < endYear - startYear + 1; i++)
        graphableData[i] = 0;
    for(size_t i = 0; i < quantity; i++)
        if(nodes[i].rating >= 8)
            ++graphableData[nodes[i].year - startYear];
    max = graphableData[0];
    min = graphableData[0];
    for(size_t i = 0; i < endYear - startYear + 1; i++) {
        if(graphableData[i] > max)
            max = graphableData[i];
        if(graphableData[i] < min)
            min = graphableData[i];
    }
    return endYear - startYear + 1;
}

void Plotter::showGraph(DatabaseNode *nodes, size_t quantity) {
    size_t xmax, xmin, ymax, ymin;
    size_t *data = nullptr;
    size_t span = structureData(nodes, quantity, xmin, xmax, ymin, ymax, data);
    if(quantity < 2)
        throw;
    QGraphicsScene *scene = new QGraphicsScene(0, 0, 700, 400, this);
    ui->graphicsView->setScene(scene);
    scene->clear();
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(0, 0, 0));
    // axis
    scene->addLine(40, 0, 45, 10, pen);
    scene->addLine(40, 0, 35, 10, pen);
    QGraphicsTextItem *text = scene->addText("Number of popular films (rated 8+)");
    text->setX(20);
    text->setY(-30);
    scene->addLine(40, 0, 40, 310, pen);
    scene->addLine(40, 310, 610, 310, pen);
    scene->addLine(610, 310, 600, 305, pen);
    scene->addLine(610, 310, 600, 315, pen);
    text = scene->addText("Year");
    text->setX(630);
    text->setY(300);
    // actual data
    pen.setColor(QColor(0, 115, 207));
    pen.setWidth(3);
    for(size_t i = 1; i < span; i++)
        scene->addLine(40 + ((static_cast<double>(i) - 1) / (xmax - xmin)) * 560,
                       310 - ((static_cast<double>(data[i - 1]) - ymin) / (ymax - ymin)) * 300,
                       40 + (static_cast<double>(i) / (xmax - xmin)) * 560,
                       310 - ((static_cast<double>(data[i]) - ymin) / (ymax - ymin)) * 300, pen);
    // x aux lines and caps
    pen.setColor(QColor(200, 200, 200));
    pen.setWidth(1);
    for(size_t i = 0; i < span; i++) {
        scene->addLine(40 + (static_cast<double>(i) / (xmax - xmin)) * 560, 310,
                       40 + (static_cast<double>(i) / (xmax - xmin)) * 560, 10, pen);
        QGraphicsTextItem *text = scene->addText(QString::number(i + xmin));
        text->setX(35 + (static_cast<double>(i) / (xmax - xmin)) * 560);
        text->setY(320);
    }
    // y aux lines and caps
    for(size_t i = ymin; i < ymax; i++) {
        scene->addLine(600, 310 - ((static_cast<double>(i) - ymin) / (ymax - ymin)) * 300,
                       40, 310 - ((static_cast<double>(i) - ymin) / (ymax - ymin)) * 300, pen);
        QGraphicsTextItem *text = scene->addText(QString::number(i));
        text->setX(20);
        text->setY(305 - ((static_cast<double>(i) - ymin) / (ymax - ymin)) * 300);
    }
    delete[] data;
    this->show();
}

Plotter::~Plotter()
{
    delete ui;
}
