#include "pellets.h"

Pellets::Pellets(int id, int r, int c)
{
    // setting the id of the pellet
    this->id = id;

    // Reading the image
    QPixmap image("Pellet.svg");

    // Setting dimensions of the image
    image = image.scaledToWidth(30);
    image = image.scaledToHeight(30);

    // Setting pellets image
    setPixmap(image);

    // Setting Pellets position
    row = r;
    column = c;
    setPos(70 + (30 * column), 70 + (30 * row));

    on_scene = true;
}

Pellets::Pellets(const Pellets &c)
{
    id = c.id;
    row = c.row;
    column = c.column;
}

void Pellets::get_row_col(int &r, int &c)
{
    r = row;
    c = column;
}
void Pellets::set_onScene(bool x)
{
    on_scene = x;
}
bool Pellets::onScene()
{
    return on_scene;
}
