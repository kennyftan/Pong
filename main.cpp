#include <iostream>
#include <time.h> // for randomization
#include <conio.h>
#include <windows.h>

using namespace std;
enum class eDir : int {STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6}; // enumeration for directions

template <typename Enumeration>
auto as_integer(Enumeration const value)
-> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

class Ball
{
private:
    int x, y;
    int x_original, y_original;
    eDir direction;

public:
    Ball() // Overloaded constructor
    {
        x = y = x_original = y_original = 0;
        direction = eDir::STOP;
    }

    Ball(int x_position, int y_position) // Overloaded constructor
    {
        x_original = x_position;
        y_original = y_position;
        x = x_position;
        y = y_position;
        direction = eDir::STOP;
    }

    void Reset()
    {
        x = x_original; y = y_original;
        direction = eDir::STOP;
    }

    void changeDirection(eDir d)
    {
        direction = d;
    }

    void randomDirection()
    {

        direction = (eDir)((rand() % 6) + 1);
    }

    inline int getX()
    {
        return x;
    }
    inline int getY()
    {
        return y;
    }

    inline eDir getDirection()
    {
        return direction;
    }

    void Move()
    {
        switch (direction)
        {

        case eDir::STOP:
            break;
        case eDir::LEFT:
            x--;
            break;
        case eDir::RIGHT:
            x++;
            break;
        case eDir::UPLEFT:
            x--; y--;
            break;
        case eDir::DOWNLEFT:
            x--; y++;
            break;
        case eDir::UPRIGHT:
            x++; y--;
            break;
        case eDir::DOWNRIGHT:
            x++; y++;
            break;
        default:
            break;

        }
    }

    friend ostream& operator << (ostream& o, Ball c)
    {
        o << "Ball [" << c.x << "," << c.y << "][" << as_integer(c.direction) << "]" << endl;
        return o;
    }
};

class Paddle
{
private:
    int x, y;
    int x_original, y_original;

public:
    Paddle()
    {
        x = y = x_original = y_original = 0;
    }

    Paddle(int x_position, int y_position)
    {
        x_original = x_position;
        y_original = y_position;
        x = x_position;
        y = y_position;
    }

    inline void Reset()
    {
        x = x_original;
        y = y_original;
    }

    inline int getX()
    {
        return x;
    }

    inline int getY()
    {
        return y;
    }

    inline void MoveUp()
    {
        y--;
    }

    inline void MoveDown()
    {
        y++;
    }

    friend ostream& operator << (ostream& o, Paddle c)
    {
        o << "Paddle [" << c.x << "," << c.y << "]" << endl;
        return o;
    }
};

class GameManager
{
private:
    int width, height; // Size of field
    int score_p1, score_p2;
    char up1, down1, up2, down2; // Movement of paddles
    bool quit;
    Ball* ball;
    Paddle* player1;
    Paddle* player2;

public:
    GameManager()
    {
        srand(time(0));
        quit = false;
        up1 = 'w'; down1 = 's';
        up2 = 'i'; down2 = 'k';
        score_p1 = score_p2 = 0;
        width = 40; height = 20;
        ball = new Ball(width / 2, height / 2);
        player1 = new Paddle(1, height / 2);
        player2 = new Paddle(width - 2, height / 2);
    }

    GameManager(int w, int h) // width and height of court
    {
        srand(time(0));
        quit = false;
        up1 = 'w'; down1 = 's';
        up2 = 'i'; down2 = 'k';
        score_p1 = score_p2 = 0;
        width = w; height = h;
        ball = new Ball(w / 2, h / 2);
        player1 = new Paddle(1, h / 2);
        player2 = new Paddle(w - 2, h / 2);
    }

    ~GameManager()
    {
        delete ball, player1, player2;
    }
    
    void ScoreUp(Paddle* player)
    {
        if (player == player1)
            score_p1++;
        else if (player == player2)
            score_p2++;

        ball -> Reset();
        player1 -> Reset();
        player2 -> Reset();
    }

    void Draw() // Draws court, paddle and ball onto window
    {
        clearScreen();

        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;
        
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int ballx = ball->getX();
                int bally = ball->getY();
                int player1x = player1->getX();
                int player1y = player1->getY();
                int player2x = player2->getX();
                int player2y = player2->getY();

                if (j == 0)
                    cout << "#";

                if (ballx == j && bally == i)
                    cout << "0"; // ball

                else if (player1x == j && player1y == i)
                    cout << "#"; // player 1
                else if (player1x == j && player1y + 1 == i)
                    cout << "#"; // player 1
                else if (player1x == j && player1y + 2 == i)
                    cout << "#"; // player 1
                else if (player1x == j && player1y + 3 == i)
                    cout << "#"; // player 1

                else if (player2x == j && player2y == i)
                    cout << "#"; // player 2
                else if (player2x == j && player2y + 1 == i)
                    cout << "#"; // player 2
                else if (player2x == j && player2y + 2 == i)
                    cout << "#"; // player 2
                else if (player2x == j && player2y + 3 == i)
                    cout << "#"; // player 2

                else
                    cout << " ";

                if (j == width - 1)
                    cout << "#";
            }
            cout << endl;
        }
        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;

        cout << "PLAYER 1 SCORE: " << score_p1 << endl;
        cout << "PLAYER 2 SCORE: " << score_p2 << endl;
        cout << "\n";
        cout << "Player 1 controls: " << up1 << " & " << down1 << endl;
        cout << "Player 2 controls:" << up2 << " & " << down2 << endl;
        cout << "\n";
        cout << "Press q to exit" << endl;

    }

    void Input()
    {
        ball->Move();

        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player1y = player1->getY();
        int player2x = player2->getX();
        int player2y = player2->getY();

        if (_kbhit())
        {
            char current = _getch();

            if (current == up1 && player1y > 0)
            {
                    player1->MoveUp();
            }
            else if (current == up2 && player2y > 0)
            {
                    player2->MoveUp();
            }
            else if (current == down1 && player1y + 4 < height)
            {
                    player1->MoveDown();
            }
            else if (current == down2 && player2y + 4 < height)
            {
                    player2->MoveDown();
            }

            if (ball->getDirection() == eDir::STOP)
                ball->randomDirection();

            if (current == 'q')
                quit = true;
        }
    }

    void Logic()
    {
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x = player1->getX();
        int player1y = player1->getY();
        int player2x = player2->getX();
        int player2y = player2->getY();

        // Paddle collision
        for (int i = 0; i < 4; i++) // 4 represents height of paddle
        {
            if (ballx == player1x + 1 && bally == player1y + i) // Left paddle
            {
                ball->changeDirection((eDir)((rand() % 3) + 4));
            }
            else if (ballx == player2x - 1 && bally == player2y + i) // Right paddle
            {
                ball->changeDirection((eDir)((rand() % 3) + 1));
            }
        }

        if (bally == height - 1)
            ball->changeDirection(ball->getDirection() == eDir::DOWNRIGHT ? eDir::UPRIGHT : eDir::UPLEFT);
        else if (bally == 0)
            ball->changeDirection(ball->getDirection() == eDir::UPRIGHT ? eDir::DOWNRIGHT : eDir::DOWNLEFT);

        if (ballx == width - 1)
            ScoreUp(player1);
        else if (ballx == 0)
            ScoreUp(player2);
    }

    void Run()
    {
        while (!quit)
        {
            Draw();
            Input();
            Logic();
        }
    }

    void clearScreen() // Direct implementation of "cls" to remove flicker
    {
        HANDLE hOut;
        COORD Position;

        hOut = GetStdHandle(STD_OUTPUT_HANDLE);

        Position.X = 0;
        Position.Y = 0;

        SetConsoleCursorPosition(hOut, Position);
    }
};

int main()
{
    GameManager c(80, 40);
    c.Run();
    return 0;
};