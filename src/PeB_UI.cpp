#include "PeB_UI.h"
#include "PeBSvgItem.h"
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsPathItem>
#include <QSvgRenderer>
#include <QGraphicsSvgItem>
#include <QGraphicsColorizeEffect>

#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QDebug>
#include <QRegularExpression>
#include <QMap>
#include <QStack>

#include <iostream>
#include <map>
#include <typeinfo>


QMap<QGraphicsItem*, QGraphicsColorizeEffect*> effectMap;

PeB_UI::PeB_UI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // TOP SCENE 
    //  Initialization
    
    topGraphicsScene = new QGraphicsScene();
    topGraphicsScene->setBackgroundBrush(QColor("#000000"));
    
    ui->topGraphicsView->scale(2, 2);
    ui->topGraphicsView->setScene(topGraphicsScene);

    // RIGHT SCENE
    
    rightGraphicsScene = new QGraphicsScene();
    rightGraphicsScene->setBackgroundBrush(QColor("#000000"));

    ui->rightGraphicsView->setScene(rightGraphicsScene);
    
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &PeB_UI::onTimerTick);
    timer->start(2000); // 1000 ms = 1 second

}

PeB_UI::~PeB_UI()
{
    delete ui;
}

// Function to apply red effect
void applyEffect(QGraphicsItem* item) {
    QGraphicsColorizeEffect* effect = new QGraphicsColorizeEffect;
    effect->setColor(QColor("#ffffff"));
    effect->setStrength(0.75);
    item->setGraphicsEffect(effect);
}

// Function to remove effect
void removeEffect(QGraphicsItem* item) {
    item->setGraphicsEffect(nullptr);
}

// Toggle function
void toggleEffect(QGraphicsItem* item) {
    if (item->graphicsEffect()) {
        removeEffect(item);
    } else {
        applyEffect(item);
    }
}

/**
 * @brief Pulls PeB items out of SVG file and adds the items to the renderer
 * 
 * @param filePath Path to SVG file
 * @param renderer Shared renderer for use with PeBSvgItems
 * @param mapping Dictionary of PeBSvgItems (QGraphicsSvgItem)
 */
void PeB_UI::loadSvgToRenderer(const QString& filePath, QSvgRenderer *renderer, std::map<std::string, PeBSvgItem*> *mapping) {
    QFile file(filePath);           // QFile is a SVG
    QDomDocument doc;               

    // Load document
    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file)) {
        qWarning() << "Failed to open or parse SVG file.";
        return;
    }

    file.close();

    QDomNode root = doc.documentElement();
    QStack<QDomNode> stack;         // Creating a QStack to keep track of traversal
    stack.push(root);

    while (!stack.isEmpty()) {
        QDomNode node = stack.pop();
        QDomNode current = node.firstChild();
        
        while (!current.isNull()) {
            if (current.isElement()) {
                QDomElement el = current.toElement();
                if (el.attribute("PeB_enable") == "1") {
                    QString elementId = el.attribute("id");
                    QString x_fromSVG = el.attribute("PeB_x");
                    QString y_fromSVG = el.attribute("PeB_y");
                    if (!x_fromSVG.isEmpty() & !y_fromSVG.isEmpty()) {
                        
                        double x = x_fromSVG.toDouble();
                        double y = y_fromSVG.toDouble();
                        PeBSvgItem *myPeBSvgItem = new PeBSvgItem(renderer, elementId.toUtf8().constData(), x, y);
                        std::string elementIdString = elementId.toStdString();
                        qDebug() << "Element:" << elementId;

                        mapping->emplace(elementIdString, myPeBSvgItem);
                        // return;
                    }

                }
            }

            // Push children first
            if (current.hasChildNodes()) {
                stack.push(current);
            }
            current = current.nextSibling();
        }
    }
    return;
}

/**
 * @brief 
 * 
 * @param graphicsScene 
 * @param mapping 
 */
void PeB_UI::loadImagesToScene(QGraphicsScene *graphicsScene, std::map<std::string, PeBSvgItem*> *mapping){
    for (std::map<std::string, PeBSvgItem*>::iterator it = mapping->begin(); it != mapping->end(); ++it) 
        graphicsScene->addItem(it->second);
    return;
}


// Given a SVG render and ID this returns a SVG Item that can be
// rendered on the Graphics screen 
QGraphicsSvgItem *PeB_UI::getSvgItemByID(QSvgRenderer *renderer, const char* ID) {
    QGraphicsSvgItem *SvgItem = new QGraphicsSvgItem();
    SvgItem->setSharedRenderer(renderer);
    SvgItem->setElementId(QLatin1String(ID));
    return SvgItem;
}

/**
 * @brief 
 * 
 * @param filePath Path to SVG file
 */
void PeB_UI::loadSvgToTop(std::string filePath) {
    // This loads the SVG to the renderer
    topRenderer = new QSvgRenderer(QString::fromStdString(filePath));

    // Loads specifically enabled DOMS to into the renderer
    loadSvgToRenderer(QString::fromStdString(filePath), topRenderer, topGraphicsImages);
    loadImagesToScene(topGraphicsScene, topGraphicsImages);
    
    topGraphicsScene->update();
    ui->topGraphicsView->setScene(topGraphicsScene);
    ui->topGraphicsView->viewport()->update();
}



void PeB_UI::onTimerTick() {
    toggleEffect(topGraphicsImages->at("rect111"));
}

