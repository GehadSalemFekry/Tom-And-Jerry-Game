#include "jerry.h"
#include <QDebug>

Jerry::Jerry(int BoardData[22][22])
{
    // Reading the image
    QPixmap image("Jerry.png");
    // Setting dimensions of the image
    image = image.scaledToWidth(30);
    image = image.scaledToHeight(30);

    // Setting Jerry's image
    setPixmap(image);

    // Setting Jerry's position (Default at his home)
    row = 11;
    column = 11;
    setPos(70 + (30 * column), 70 + (30 * row));

    // Reading Board
    for (int i = 0; i < 22; i++)
        for (int j = 0; j < 22; j++)
            data[i][j] = BoardData[i][j];


    jerryWithCheese = false;
    power_mode = false;
}

bool Jerry::home()
{
    for (int i = 9; i < 13; i++)
        for (int j = 9; j < 13; j++)
            if ((row == i) && (column == j))
                return true;
    return false;
}
void Jerry::set_row_col(int r, int c)
{
    row = r;
    column = c;
    setPos(70 + (30 * column), 70 + (30 * row));
}
void Jerry::get_row_col(int &r, int &c)
{
    r = row;
    c = column;
}
void Jerry::set_power_mode(bool b)
{
    power_mode = b;
}
bool Jerry::get_power_mode()
{
    return (power_mode);
}
void Jerry::set_with_cheese(bool x)
{
    jerryWithCheese = x;
}
bool Jerry::get_with_cheese()
{
    return jerryWithCheese;
}
