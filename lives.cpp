#include "lives.h"

Lives::Lives(int id)
{
    QPixmap image("heart.jpg");

    image = image.scaledToWidth(30);
    image = image.scaledToHeight(30);

    // Setting heart image
    setPixmap(image);
    setPos(130 + (30 * id), 6);
}
