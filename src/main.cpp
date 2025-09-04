#include <QApplication>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>

// Horizontal Box 
#include <QHBoxLayout>
#include "PeB_UI.h"

#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QDebug>

#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>
#include <QDomNamedNodeMap>
#include <QDomAttr>
#include <QDebug>
#include <QStack>



int main(int argc, char **argv)
{
  qDebug() << "Testing Output";

  QApplication app (argc, argv);
  PeB_UI window;
  window.loadSvgToTop("/home/pigeonlord9000/Documents/Code/C++/PeB_Emulator/Test_Drawing.svg");

  window.show();
  return app.exec();
}

// window.setGeometry(0, 0, 1600, 1000);

// // This is creating a graphical Scene

// QGraphicsScene *rightScreen = new QGraphicsScene();
// rightScreen->setBackgroundBrush(Qt::black);

// // QGraphicsRectItem *rect = topScreen->addRect(QRectF(0, 0, 100, 100));

// // This is attaching my graphical Scene to a Graphical View
// // this is useful as a Graphical view acts as a widget in the window
// // where as the Scene does not
// QGraphicsView *viewTop = new QGraphicsView(topScreen);
// viewTop->setGeometry(0, 0, 800, 500);  // Set view size/position inside parent widget
// viewTop->setFixedSize(800, 500);

// QGraphicsView *viewRight = new QGraphicsView(topScreen);
// viewRight->setGeometry(0, 0, 500, 800);  // Set view size/position inside parent widget
// viewRight->setFixedSize(500, 800);

// QHBoxLayout *layoutH = new QHBoxLayout();  
// layoutH->addWidget(viewTop);
// layoutH->addSpacing(20);
// layoutH->addWidget(viewRight);
// // layout->addWidget(button2);

// QVBoxLayout *layoutV = new QVBoxLayout(&window);
// layoutV->addLayout(layoutH);




// void traverseDom(const QDomNode& node) {
//   QDomNode current = node.firstChild();
//   while (!current.isNull()) {
//         if (current.isElement()) {
//             QDomElement elem = current.toElement();
//             QString tagName = elem.tagName();
//             qDebug() << "Element:" << tagName;

//             // Example: Check for type="wire"
//             if (elem.hasAttribute("type") && elem.attribute("type") == "wire") {
//                 qDebug() << "  -> Found wire element with id:" << elem.attribute("id");
//             }

//             // Print all attributes
//             QDomNamedNodeMap attributes = elem.attributes();
//             for (int i = 0; i < attributes.count(); ++i) {
//                 QDomAttr attr = attributes.item(i).toAttr();
//                 qDebug() << "     " << attr.name() << "=" << attr.value();
//             }
//         }

//         // Recurse into children
//         traverseDom(current);
//         current = current.nextSibling();
//     }
// }


// void traverseDomIterative(const QDomNode& root) {
//     QStack<QDomNode> stack;
//     stack.push(root);

//     while (!stack.isEmpty()) {
//         QDomNode node = stack.pop();

//         QDomNode current = node.firstChild();
//         while (!current.isNull()) {
//             if (current.isElement()) {
//                 QDomElement elem = current.toElement();
//                 QString tagName = elem.tagName();
//                 qDebug() << "Element:" << tagName;

//                 if (elem.hasAttribute("type") && elem.attribute("type") == "wire") {
//                     qDebug() << "  -> Found wire element with id:" << elem.attribute("id");
//                 }

//                 QDomNamedNodeMap attributes = elem.attributes();
//                 for (int i = 0; i < attributes.count(); ++i) {
//                     QDomAttr attr = attributes.item(i).toAttr();
//                     qDebug() << "     " << attr.name() << "=" << attr.value();
//                 }
//             }

//             // Push children first
//             if (current.hasChildNodes()) {
//                 stack.push(current);
//             }

//             current = current.nextSibling();
//         }
//     }
// }


// void parseCustomAttributes(const QString& filePath) {
//     QFile file(filePath);
//     if (!file.open(QIODevice::ReadOnly)) {
//         qWarning() << "Failed to open SVG file";
//         return;
//     }

//     QDomDocument doc;
//     if (!doc.setContent(&file)) {
//         qWarning() << "Failed to parse SVG file";
//         file.close();
//         return;
//     }
//     file.close();

//     QDomNode current = doc.firstChild();
//     traverseDomIterative(doc.documentElement());
// }
