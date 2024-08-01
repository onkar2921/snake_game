#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <windows.h>
#define WIDTH 50
#define HEIGHT 25

using namespace std;

class Snake
{
private:
    COORD position;
    int direction;
    int velocity;
    int len;
    vector<COORD> body;

protected:
    int score = 0;

public:
    Snake(COORD pos, int vel);
    Snake();
    void changeDir(char dir);
    void move_snake();
    COORD get_pos();
    bool eaten(COORD food_position);
    void grow(); // increase the length of the snake

    vector<COORD> get_body();
    bool collide();
    int getScore();
    ~Snake();
};

Snake::Snake()
{
    this->score = 0;
};
Snake::Snake(COORD pos, int vel)
{
    this->position = pos;
    this->velocity = vel;
    this->len = 1;
    this->direction = 'n';
    body.push_back(this->position);
}

void Snake::changeDir(char dir)
{
    // Prevent the snake from reversing direction
    if ((dir == 'w' && direction != 's') ||
        (dir == 's' && direction != 'w') ||
        (dir == 'a' && direction != 'd') ||
        (dir == 'd' && direction != 'a'))
    {
        this->direction = dir;
    }
}

int Snake::getScore()
{
    return this->score;
}

void Snake::move_snake()
{
    switch (direction)
    {
    case 'w': // Up (W key)
        position.Y -= velocity;
        break;
    case 's': // Down (S key)
        position.Y += velocity;
        break;
    case 'a': // Left (A key)
        position.X -= velocity;
        break;
    case 'd': // Right (D key)
        position.X += velocity;
        break;
    default:
        break;
    }

    body.push_back(position);
    if (body.size() > len)
        body.erase(body.begin());
}

bool Snake::eaten(COORD food_position)
{
    return (position.X == food_position.X && position.Y == food_position.Y);
}

COORD Snake::get_pos() { return position; }

void Snake::grow()
{
    this->score += 5;
    this->len++;
}

bool Snake::collide()
{
    // Wall collision check
    if (position.X <= 0 || position.X >= WIDTH - 1 || position.Y <= 0 || position.Y >= HEIGHT - 1)
    {
        return true;
    }

    // Self-collision check
    for (int i = 0; i < body.size() - 1; i++) // Check all but the last position
    {
        if (position.X == body[i].X && position.Y == body[i].Y)
        {
            return true;
        }
    }
    return false;
}

vector<COORD> Snake::get_body() { return this->body; }

Snake::~Snake() {}

#endif // SNAKE_H
