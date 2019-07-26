#include "canvas_1.h"
#include "canvas_2.h"
#include "canvas_3.h"
#include <QApplication>
#include <QLayout>
#include <QLabel>

QLabel* lblCreate(const QPainter::CompositionMode& mode){
    QLabel* lbl = new QLabel;
    lbl->setFixedSize(100, 100);

    QRect rect(lbl->contentsRect());
    QPainter painter;
    // create first image
    QImage sourceImage(rect.size(), QImage::Format_ARGB32_Premultiplied);
    sourceImage.fill(Qt::transparent);
    painter.begin(&sourceImage);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QColor(0, 255, 0));
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    // draw triangle
    painter.drawPolygon(QPolygon() << rect.bottomLeft()
                                   << QPoint(rect.center().x(), 0)
                                   << rect.bottomRight());
    painter.end();
    // create second image
    QImage resultImage(rect.size(), QImage::Format_ARGB32_Premultiplied);
    resultImage.fill(Qt::transparent);
    painter.begin(&resultImage);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(QColor(0, 255, 0), 4));
    painter.setBrush(QColor(255, 0, 0));
    // draw circle
    painter.drawEllipse(rect);
    painter.setCompositionMode(mode);
    painter.drawImage(rect, sourceImage);
    painter.end();

    lbl->setPixmap(QPixmap::fromImage(resultImage));
    return lbl;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget mainWidget;
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* innerLayout_1 = new QHBoxLayout();
    mainWidget.setLayout(mainLayout);
    mainWidget.setMinimumSize(1000, 600);
    mainLayout->addLayout(innerLayout_1);

    Canvas_1 canvasOne;
    canvas_2 canvasTwo;
    innerLayout_1->addWidget(&canvasOne);
    innerLayout_1->addWidget(&canvasTwo);

    Canvas_3 canvasThree;
    QGridLayout* innerLayout_2 = new QGridLayout();
    /*innerLayout_2->addWidget(&canvasThree);*/
    // source-mode variants
    innerLayout_2->addWidget(lblCreate(QPainter::CompositionMode_Source), 0, 0);
    innerLayout_2->addWidget(new QLabel("<CENTER>Source</CENTER>"), 1, 0);
    innerLayout_2->addWidget(lblCreate(QPainter::CompositionMode_SourceOver), 0, 1);
    innerLayout_2->addWidget(new QLabel("<CENTER>SourceOver</CENTER>"), 1, 1);
    innerLayout_2->addWidget(lblCreate(QPainter::CompositionMode_SourceIn), 0, 2);
    innerLayout_2->addWidget(new QLabel("<CENTER>SourceIn</CENTER>"), 1, 2);
    innerLayout_2->addWidget(lblCreate(QPainter::CompositionMode_SourceOut), 0, 3);
    innerLayout_2->addWidget(new QLabel("<CENTER>SourceOut</CENTER>"), 1, 3);
    innerLayout_2->addWidget(lblCreate(QPainter::CompositionMode_SourceAtop), 0, 4);
    innerLayout_2->addWidget(new QLabel("<CENTER>SourceAtop</CENTER>"), 1, 4);
    // clear-mode variant
    innerLayout_2->addWidget(lblCreate(QPainter::CompositionMode_Clear), 0, 5);
    innerLayout_2->addWidget(new QLabel("<CENTER>Clear</CENTER>"), 1, 5);
    // destination-mode variants
    innerLayout_2->addWidget(lblCreate(QPainter::CompositionMode_Destination), 2, 0);
    innerLayout_2->addWidget(new QLabel("<CENTER>Destination</CENTER>"), 3, 0);
    innerLayout_2->addWidget(lblCreate(QPainter::CompositionMode_DestinationOver), 2, 1);
    innerLayout_2->addWidget(new QLabel("<CENTER>DestinationOver</CENTER>"), 3, 1);
    innerLayout_2->addWidget(lblCreate(QPainter::CompositionMode_DestinationIn), 2, 2);
    innerLayout_2->addWidget(new QLabel("<CENTER>DestinationIn</CENTER>"), 3, 2);
    innerLayout_2->addWidget(lblCreate(QPainter::CompositionMode_DestinationOut), 2, 3);
    innerLayout_2->addWidget(new QLabel("<CENTER>DestinationOut</CENTER>"), 3, 3);
    innerLayout_2->addWidget(lblCreate(QPainter::CompositionMode_DestinationAtop), 2, 4);
    innerLayout_2->addWidget(new QLabel("<CENTER>DestinationAtop</CENTER>"), 3, 4);
    // xor-mode variant
    innerLayout_2->addWidget(lblCreate(QPainter::CompositionMode_Xor), 2, 5);
    innerLayout_2->addWidget(new QLabel("<CENTER>XOR</CENTER>"), 3, 5);

    mainLayout->addLayout(innerLayout_2);
    mainWidget.show();

    return a.exec();
}
