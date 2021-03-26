#include <iostream>
#include <time.h>
#include "utils/COLORS!.hpp"
#ifdef _WIN32
#include <conio.h>
#endif
#ifdef linux
#include "utils/conio.h"
#endif
using namespace std;

struct Node
{
    Node *next = NULL;
    int x;
    int y;
};

class Snake
{
private:
    Node *head;
    const int dimensions[2] = {30, 20};
    int food[2] = {15, 5};
    bool running = true;
    char DEFAULT = 'd';
    int score = 0;

public:
    Snake()
    {
        head = NULL;
        int index = 3;
        int baseCoords[3][2] = {{4, 9}, {5, 9}, {6, 9}};
        for (int i = 0; i < index; i++)
        {
            Node *temp = new Node;
            temp->x = baseCoords[i][0];
            temp->y = baseCoords[i][1];
            if (head == NULL)
                head = temp;
            else
            {
                Node *t = head;
                while (t->next != NULL)
                    t = t->next;
                t->next = temp;
            }
        }
        draw();
        cout << "Score: " << score << endl;
    }
    void clearScreen()
    {
#ifdef _WIN32
        system("cls");
#endif
#ifdef linux
        system("clear");
#endif
    }
    bool isPresent(int a, int b)
    {
        Node *t = head;
        while (t != NULL)
        {
            if (t->x == a && t->y == b)
                return true;
            t = t->next;
        }
        return false;
    }
    bool collided(int a, int b)
    {
        int index = 0;
        Node *t = head;
        while (t != NULL)
        {
            if (t->x == a && t->y == b && index > 2)
                return true;
            index++;
            t = t->next;
        }
        return false;
    }
    void sleep(int milliseconds)
    {
        clock_t time_end;
        time_end = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
        while (clock() < time_end)
        {
        }
    }
    void draw()
    {
        while (running)
        {
            bool ate = false;
            if (head->x >= dimensions[0] || head->x < 0 || head->y < 0 || head->y >= dimensions[1])
            {
                running = false;
                return;
            }
            if (collided(head->x, head->y))
            {
                running = false;
                return;
            }
            if (head->x == food[0] && head->y == food[1])
            {
                spawnFood();
                ate = true;
                score++;
            }
            for (int i = 0; i < dimensions[1]; i++)
            {
                for (int j = 0; j < dimensions[0]; j++)
                {
                    if ((j == dimensions[0] - 1 || j == 0) && i != 0)
                        cout << "|";
                    else if (isPresent(j, i))
                    {
                        if (head->x == j && head->y == i)
                        {
                            cout << GREEN_NO_FLASH << "*" << NC;
                        }
                        else
                            cout << RED_NO_FLASH << "*" << NC;
                    }
                    else if (j == food[0] && i == food[1])
                        cout << ORANGE_NO_FLASH << "#" << NC;
                    else if (i == dimensions[1] - 1 || i == 0)
                        cout << "_";
                    else
                        cout << " ";
                }
                cout << "\n";
            }
            cout << "Score : " << score << endl;
            processInput(ate);
            sleep(90);
            clearScreen();
        }
    }
    void spawnFood()
    {
        while (isPresent(food[0], food[1]))
        {
            srand(time(0));
            food[0] = rand() % (dimensions[0] - 2) + 1;
            food[1] = rand() % (dimensions[1] - 2) + 1;
        }
    }
    char getInput()
    {
        if (kbhit())
        {
            char a = getch();
            if (a == 'w' || a == 'a' || a == 's' || a == 'd')
            {
                DEFAULT = a;
                return a;
            }
            else
                return DEFAULT;
        }
        return DEFAULT;
    }
    void insert(int a, int b)
    {
        Node *temp = new Node;
        temp->x = a;
        temp->y = b;
        temp->next = head;
        head = temp;
    }
    void pop()
    {
        Node *t = head;
        while (t->next->next != NULL)
            t = t->next;
        t->next = NULL;
    }
    void processInput(bool eaten = false)
    {
        char inp = getInput();
        int x = head->x;
        int y = head->y;
        if (inp == 'a')
            x -= 1;
        else if (inp == 'd')
            x += 1;
        else if (inp == 'w')
            y -= 1;
        else if (inp == 's')
            y += 1;
        insert(x, y);
        if (!eaten)
            pop();
    }
};

int main()
{
    Snake s;
    return 0;
}
