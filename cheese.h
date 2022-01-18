#ifndef CHEESE_H
#define CHEESE_H
#include <QGraphicsPixmapItem>

class Cheese : public QGraphicsPixmapItem
{
private:
    int id; // id is the cheese number
    int row, column;
    bool caught;
    bool home;

public:
    Cheese();                     // deafault constructor
    Cheese(int id, int r, int c); // parametrized constructor
    Cheese(const Cheese &c);      // copy constructor
    void set_row_col(int r, int c);
    void get_row_col(int &r, int &c);
    bool get_caught();
    void set_caught(bool);
    bool get_home();
    void set_home(bool);
    int get_id();
};

#endif // CHEESE_H
