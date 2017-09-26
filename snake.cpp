#include <iostream>
#include <algorithm>
#include <ncurses.h>
#include <deque>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "snake_header.h"

enum direction { UP, DOWN, LEFT, RIGHT };
#define WIDTH 50
#define HEIGHT 20
int tickle = 200;



using namespace std;
vector<pair<int, int>> vp;

int main()
{
    WINDOW *map;
    int offsetx = 0, offsety = 0;
    int dir = 10;
    Fruit fruit;
    srand((unsigned)time(NULL));

    initscr();
    noecho();
    cbreak();
    timeout(tickle);
    keypad(stdscr, TRUE);
    printw("snake game, prees 'q' to left");
    refresh();

    offsetx = (COLS - WIDTH) / 2;
    offsety = (LINES - HEIGHT) / 2;
    map = newwin(HEIGHT, WIDTH, offsety, offsetx);
    wrefresh(map);
    deque<Body> snake;
    snake.push_front(Body(WIDTH / 2, HEIGHT / 2));

    while (true) {
        input(dir);
        snake_ready(snake, dir, fruit);
        check_fruit(fruit, snake);
        move_snake(snake, fruit, map);
        logic(fruit, snake);
        if (dir == 'q')
            break;
    }


    delwin(map);
    endwin();

    return 0;

}

void input(int &dir)
{
    int ch = getch();
    if (ch != ERR) {
        switch (ch) {
            case KEY_UP:
                dir = UP;
                break;
            case KEY_DOWN:
                dir = DOWN;
                break;
            case KEY_LEFT:
                dir = LEFT;
                break;
            case KEY_RIGHT:
                dir = RIGHT;
                break;
            case 'q':
                dir = 'q';
                break;
            default:
                break;
        }
    }
}

void snake_ready(deque<Body> &snake, const int &dir, const Fruit &f)
{
    snake.push_front(snake.begin()->calc_next(dir));
    if (f.exis)
        snake.pop_back();
}

void move_snake(const deque<Body> &snake, Fruit &f, WINDOW *&win)
{
    wclear(win);
    for (auto iter = snake.cbegin(); iter != snake.cend(); ++iter)
        mvwaddch(win, iter->y, iter->x, '#');
    mvwaddch(win, f.y, f.x, 'O');
    if (!f.tree) {
        int ty = f.y, tx = f.x;
        vp.resize(snake.size());
        for (int i = 0; i != snake.size(); ++i) {
            int temp = rand() % 4;
            switch (temp) {
                case 0:
                    ty == 1? ty = HEIGHT - 2 : --ty;
                    break;
                case 1:
                    ty == HEIGHT - 2? ty = 1 : ++ty;
                    break;
                case 2:
                    tx == 1? tx = WIDTH - 2 : --tx;
                    break;
                case 3:
                    tx == WIDTH - 2? tx = 1 : ++tx;
                    break;
            }
            vp[i] = {ty, tx};
        }
        f.tree = true;
    }
    for (int i = 0; i != vp.size(); ++i)
        mvwaddch(win, vp[i].first, vp[i].second, 'O');
    box(win, 0, 0);
    wrefresh(win);
}

void check_fruit(Fruit &f, const deque<Body> &snake)
{
    if (f.exis)
        return ;
    f.x = rand() % WIDTH;
    f.y = rand() % HEIGHT;
    if (f.x == 0)
        ++f.x;
    if (f.y == 0)
        ++f.y;
    if (f.x == WIDTH - 1)
        --f.x;
    if (f.y == HEIGHT - 1)
        --f.y;
}
void logic(Fruit &f, const deque<Body> &snake)
{
    if (!f.exis) {
        f.exis = true;
        f.tree = false;
    }
    if (snake[0].x == f.x && snake[0].y == f.y)
        f.exis = false;
}
Body Body::calc_next(const int &dir)
{
    int nx = 0, ny = 0;
    switch (dir) {
        case UP: {
            y == 1 ? ny = HEIGHT - 2 : ny = y - 1;
            nx = x;
            break;
        }
        case DOWN: {
            y == HEIGHT - 2? ny = 1 : ny = y + 1;
            nx = x;
            break;
        }
        case LEFT: {
            x == 1 ? nx = WIDTH - 2 : nx = x - 1;
            ny = y;
            break;
        }
        case RIGHT: {
            x == WIDTH - 2? nx = 1 : nx = x + 1;
            ny = y;
            break;
        }
        default: {
            nx = x;
            ny = y;
            break;
        }
    }
    return Body(nx, ny);
}
