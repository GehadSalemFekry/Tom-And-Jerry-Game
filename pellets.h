#ifndef PELLETS_H
#define PELLETS_H
#include <QGraphicsPixmapItem>

class Pellets : public QGraphicsPixmapItem
{
private:
    int id; // id is the pellet number
    int row, column;
    bool on_scene;

public:
    Pellets(int id, int r, int c); // parametrized constructor
    Pellets(const Pellets &c);     // copy constructor

    void get_row_col(int &r, int &c);
    void set_onScene(bool x);
    bool onScene();
};

#endif // PELLETS_H
