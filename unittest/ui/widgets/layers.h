#pragma once

#include <QTest>
#include <widgets/layers.cpp>

class LayersTest : public Layers {
    public:
        LayersTest(lc::Document_SPtr document = nullptr, QWidget* parent = 0) :
                Layers(document, parent)
        {}

        unsigned int nbLayers() {
            QAbstractItemModel* model = ui->layerList->model();
            return model->rowCount();
        }

        void selectLayer(unsigned int row) {
            ui->layerList->selectRow(row);
        }

        void cellClick(unsigned int col, unsigned int row) {
            int xPos = ui->layerList->columnViewportPosition(col) + 2;
            int yPos = ui->layerList->rowViewportPosition(row) + 2;

            QWidget* viewport = ui->layerList->viewport();

            QTest::mouseClick(viewport, Qt::LeftButton, NULL, QPoint(xPos, yPos));
        }

        void addLayer(lc::Layer_CSPtr layer) {
            createLayer(layer);
        }

        void remove() {
            QTest::mouseClick(ui->deleteButton, Qt::LeftButton, Qt::NoModifier, QPoint(5, 5), 100);
        }
};