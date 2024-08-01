#ifndef FOOD_H
#define FOOD_H

#include <windows.h>
#include <cstdlib>

#define WIDTH 50
#define HEIGHT 25

class Food
{
    COORD position;

public:
    void gen_food();
    COORD get_food();
};

void Food::gen_food()
{
   position.X = rand() % (WIDTH - 2) + 1; // Avoid left wall
    position.Y = rand() % (HEIGHT - 2) + 1; // Avoid top wall

    // Ensure food is not placed directly adjacent to the walls
    while (position.X <= 1 || position.X >= WIDTH - 2 || position.Y <= 1 || position.Y >= HEIGHT - 2)
    {
        position.X = rand() % (WIDTH - 2) + 1;
        position.Y = rand() % (HEIGHT - 2) + 1;
    }
}

COORD Food::get_food()
{
    return this->position;
}

#endif // FOOD_H
