#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QKeyEvent>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QList>
#include <QTimer>
#include <QFont>

// Game Classes
#include "jerry.h"
#include "tom.h"
#include "cheese.h"
#include "pellets.h"
#include "lives.h"
#include "psteps.h"
#include "music.h"

class GameManager : public QGraphicsView
{
    Q_OBJECT //to handle buttons when clicked
private:
    QGraphicsScene *scene;
    QGraphicsTextItem *powModeStatus;
    QGraphicsTextItem *lives;
    QTimer *timer;

    // Board
    int BoardData[22][22];
    QGraphicsPixmapItem **BoardItem;

    Cheese *cheese_arr[4];//static array of pointer to the objects
    Pellets *pellets_arr[2];
    PSteps *steps_arr[10];
    Lives *lives_arr[3];
    Tom *tom;
    Jerry *jerry;
    Music *sound;
    QPushButton *music;

    int power_steps;
    int lives_num;

    void addTheGameToTheScene();
    void createBoard();
    void addCheese();
    void addTom();
    void addJerry();
    void addPellets();
    void addLives();

    void check_cheese();
    void check_pellets();
    void reset_the_game();
    void check_winning();
    void caught_by_tom();
    void power_on();

public slots:
    void keyPressEvent(QKeyEvent *event);
    void move_tom(); //to be called by the timer
    void on_music_clicked();

public:
    GameManager();
    ~GameManager();
};

#endif // GAMEMANAGER_H
