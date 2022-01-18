#include "psteps.h"

PSteps::PSteps(int id)
{
    QPixmap image("feet.png");

    image = image.scaledToWidth(30);
    image = image.scaledToHeight(30);
    // Setting feet image
    setPixmap(image);
    setPos(270 + (30 * id), 35);
}
