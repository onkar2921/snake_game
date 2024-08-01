#include <iostream>
#include <cstdlib>
#include <windows.h>
#include "snake.h" // include the snake header file
#include "food.h"  // include the food header file
#include <ctime>
#include <conio.h>
#include <vector>
#define WIDTH 50
#define HEIGHT 25

using namespace std;

class Menu : protected Snake
{
    Snake snake;
    Food food;

public:
    Menu()
    {
        this->snake = Snake({WIDTH / 2, HEIGHT / 2}, 1);
        this->food = food;
    }

    // Print the board of height width including the walls
    void board(COORD food_position)
    {
        // Get the snake position
        COORD snake_position = snake.get_pos();
        vector<COORD> snake_body = snake.get_body();

        // Clear the console for every frame
        system("cls");

        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                if (i == 0 || j == WIDTH - 1 || j == 0 || i == HEIGHT - 1)
                    cout << "#"; // Printing the walls
                else if (i == food_position.Y && j == food_position.X)
                    cout << "O"; // Print the food
                else
                {
                    // Print the snake body
                    bool body_part = false;
                    for (const auto &part : snake_body)
                    {
                        if (i == part.Y && j == part.X)
                        {
                            body_part = true;
                            cout << "^"; // Snake body representation
                            break;
                        }
                    }

                    if (!body_part)
                        cout << " "; // Print space for empty areas
                }
            }
            cout << endl; // Move to the next line
        }

        // Print the score
        cout << "\nScore: " << snake.getScore() << "\n"; // Display the score with clear formatting
    }

    void play()
    {
        srand(time(NULL));
        bool game_over = false;
        food.gen_food(); // Generate the initial food

        // Debugging output
        cout << "Snake Initial Position: (" << snake.get_pos().X << ", " << snake.get_pos().Y << ")\n";
        cout << "Food Initial Position: (" << food.get_food().X << ", " << food.get_food().Y << ")\n";

        while (!game_over)
        {
            board(food.get_food());

            // Move the snake based on the current direction
            snake.move_snake();

            // Check if the snake has eaten food
            if (snake.eaten(food.get_food()))
            {
                food.gen_food(); // Generate new food
                snake.grow();    // Increase snake length
            }

            // Check for collisions
            if (snake.collide())
            {
                cout << "GAME OVER!" << endl;
                game_over = true;
                break;
            }

            // Handle user input for direction change
            if (kbhit())
            {
                switch (getch())
                {
                case 'w':
                    snake.changeDir('w');
                    break;
                case 's':
                    snake.changeDir('s');
                    break;
                case 'a':
                    snake.changeDir('a');
                    break;
                case 'd':
                    snake.changeDir('d');
                    break;
                default:
                    break;
                }
            }

            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
            Sleep(100); // Add a small delay to control the speed of the snake
        }
    }
};

int main()
{
    Menu game;
    game.play();
    return 0;
}
