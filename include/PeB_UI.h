#ifndef PEB_UI_H
#define PEB_UI_H

#include <QMainWindow>
#include <QGraphicsSvgItem>
#include "ui_mainwindow.h"
#include "PeBSvgItem.h"
#include <string>
#include <QTimer>
#include <map>
#include <string>
#include <QSvgRenderer>



class PeB_UI : public QMainWindow
{
    Q_OBJECT

    public:
        PeB_UI(QWidget *parent = nullptr);
        ~PeB_UI();

        
        void loadSvgToTop(std::string filePath);
        
    private:
        Ui::MainWindow *ui;

        QGraphicsScene *topGraphicsScene;
        QGraphicsScene *rightGraphicsScene;
        QSvgRenderer *topRenderer;

        QTimer* timer;
        std::map<std::string, PeBSvgItem*> *topGraphicsImages = new std::map<std::string, PeBSvgItem*>();

        void loadSvgToRenderer(const QString& filePath, QSvgRenderer *renderer, std::map<std::string, PeBSvgItem*> *mapping);
        void loadImagesToScene(QGraphicsScene *graphicsScene, std::map<std::string, PeBSvgItem*> *mapping);


        QGraphicsSvgItem *getSvgItemByID(QSvgRenderer *renderer, const char* ID);
        void onTimerTick();

};
#endif // PEB_UI_H
