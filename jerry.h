#ifndef JERRY_H
#define JERRY_H

#include <QGraphicsPixmapItem>

class Jerry : public QGraphicsPixmapItem // Jerry responds to events via the gamemanager
{
private:
    int data[22][22];
    int row, column;

    bool power_mode;
    bool jerryWithCheese;

public:
    Jerry(int BoardData[22][22]);

    bool home(); // Function to check whether Jerry is at home
    void set_row_col(int r, int c);
    void get_row_col(int &r, int &c);

    void set_with_cheese(bool x);
    bool get_with_cheese();

    void set_power_mode(bool b);
    bool get_power_mode();

};
#endif // JERRY_H
