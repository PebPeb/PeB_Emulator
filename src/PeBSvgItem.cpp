#include "PeBSvgItem.h"

#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QDebug>
#include <QRegularExpression>

#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>
#include <QDomNamedNodeMap>
#include <QDomAttr>
#include <QDebug>
#include <QStack>


PeBSvgItem::PeBSvgItem(QSvgRenderer *renderer, const char* ID, double x, double y, QGraphicsItem* parent)
    : QGraphicsSvgItem(parent), PeB_ID(ID)
{
    setSharedRenderer(renderer);
    setElementId(ID);
    setPos(QPointF(x, y));
}

PeBSvgItem::PeBSvgItem(QSvgRenderer *renderer, const char* ID, QGraphicsItem* parent)
    : QGraphicsSvgItem(parent), PeB_ID(ID)
{
    setSharedRenderer(renderer);
    setElementId(ID);

    position = getSvgElementStartPosition("Test_Drawing.svg", ID);
    // qDebug() << position.x();    
    // qDebug() << position.y();
    setPos(position);
    
    // You can optionally load or log here
}





void PeBSvgItem::setPeB_ID(const char* ID) {
    PeB_ID = ID;
}

const char* PeBSvgItem::getPeB_ID() const {
    return PeB_ID;
}



QPointF PeBSvgItem::getSvgElementStartPosition(const QString& filePath, const QString& elementId) {
    QFile file(filePath);
    QDomDocument doc;

    if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file)) {
        qWarning() << "Failed to open or parse SVG file.";
        return QPointF();
    }

    file.close();

    QDomNode root = doc.documentElement();

    QStack<QDomNode> stack;
    stack.push(root);

    while (!stack.isEmpty()) {
        QDomNode node = stack.pop();
        QDomNode current = node.firstChild();

        while (!current.isNull()) {
            if (current.isElement()) {
                QDomElement el = current.toElement();
                if (el.attribute("id") == elementId) {
                    qDebug() << "Element:" << elementId;
                    QString x_fromSVG = el.attribute("PeB_x");
                    QString y_fromSVG = el.attribute("PeB_y");
                    if (!x_fromSVG.isEmpty() & !y_fromSVG.isEmpty()) {
                        double x = x_fromSVG.toDouble();
                        double y = y_fromSVG.toDouble();
                        qDebug() << "X: " << x << "Y: " << y;
                        return QPointF(x, y);
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
    return QPointF();
}
