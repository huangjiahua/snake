#include <deque>
#include <ncurses.h>

struct Body {
public:
    int x;
    int y;
    Body calc_next(const int &dir);
    Body(int ix, int iy): x(ix), y(iy) { }
    Body() = delete;
};

struct Fruit {
public:
    int x = 10;
    int y = 10;
    void make(const std::deque<Body> &);
    bool exis = false;
    bool tree = false;
};

void input(int &dir);
void snake_ready(std::deque<Body> &snake, const int &dir, const Fruit&);
void move_snake(const std::deque<Body> &snake, Fruit&, WINDOW *&win);
void check_fruit(Fruit&, const std::deque<Body>&);
void logic(Fruit &f, const std::deque<Body> &snake);
bool operator==(const Body &lhs, const Body &rhs)
{
    if (lhs.x == rhs.x && lhs.y == rhs.y)
        return true;
    return false;
}
