
#include <QApplication>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QList>
#include <QThread>
#include <QTimer>
#include <QFont>



#include "gamemanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);








    GameManager gameManager;
    gameManager.QGraphicsView::show();



    return a.exec();
}
