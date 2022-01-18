#include "cheese.h"

Cheese::Cheese(int id, int r, int c)
{
    // Setting the id of the cheese
    this->id = id;

    // Reading the image
    QPixmap image("Cheese.svg");

    // Setting dimensions of the image
    image = image.scaledToWidth(30);
    image = image.scaledToHeight(30);

    // Setting Cheese image
    setPixmap(image);

    // Setting Cheese position
    row = r;
    column = c;
    setPos(70 + (30 * column), 70 + (30 * row));

    caught = false;
    home = false;
}

Cheese::Cheese(const Cheese &c)
{
    id = c.id;
    row = c.row;
    column = c.column;
}

void Cheese::set_row_col(int r, int c)
{
    row = r;
    column = c;
    setPos(70 + (30 * column), 70 + (30 * row));
}
void Cheese::get_row_col(int &r, int &c)
{
    r = row;
    c = column;
}
void Cheese::set_caught(bool b)
{
    caught = b;
}
bool Cheese::get_caught()
{
    return (caught);
}
void Cheese::set_home(bool b)
{
    home = b;
}
bool Cheese::get_home()
{
    return (home);
}
int Cheese::get_id()
{
    return (id);
}
