#pragma once

#include <QGraphicsSvgItem>
#include <QString>

class PeBSvgItem : public QGraphicsSvgItem {
public:
    PeBSvgItem(QSvgRenderer *renderer, const char* ID, double x, double y, QGraphicsItem* parent = nullptr);
    PeBSvgItem(QSvgRenderer *renderer, const char* ID, QGraphicsItem* parent = nullptr);


    void setPeB_ID(const char* ID);
    const char* getPeB_ID() const;

private:
    const char* PeB_ID;
    QPointF position;

    QPointF getSvgElementStartPosition(const QString& filePath, const QString& elementId);
};
