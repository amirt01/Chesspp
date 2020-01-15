#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <math.h>

using namespace std;

pair <char, int> gameTable[8][8] = {make_pair('R', 0), make_pair('N', 0), make_pair('B', 0), make_pair('Q', 0), make_pair('K', 0), make_pair('B', 0), make_pair('N', 0), make_pair('R', 0),    //setup chess board
                                    make_pair('P', 0), make_pair('P', 0), make_pair('P', 0), make_pair('P', 0), make_pair('P', 0), make_pair('P', 0), make_pair('P', 0), make_pair('P', 0),
                                    make_pair(' ', 1), make_pair(' ', 1), make_pair(' ', 1), make_pair(' ', 1), make_pair(' ', 1), make_pair(' ', 1), make_pair(' ', 1), make_pair(' ', 1),
                                    make_pair(' ', 1), make_pair(' ', 1), make_pair(' ', 1), make_pair(' ', 1), make_pair(' ', 1), make_pair(' ', 1), make_pair(' ', 1), make_pair(' ', 1),
                                    make_pair(' ', 1), make_pair(' ', 1), make_pair(' ', 1), make_pair(' ', 1), make_pair(' ', 1), make_pair(' ', 1), make_pair(' ', 1), make_pair(' ', 1),
                                    make_pair(' ', 1), make_pair(' ', 1), make_pair(' ', 1), make_pair(' ', 1), make_pair(' ', 1), make_pair(' ', 1), make_pair(' ', 1), make_pair(' ', 1),
                                    make_pair('P', 2), make_pair('P', 2), make_pair('P', 2), make_pair('P', 2), make_pair('P', 2), make_pair('P', 2), make_pair('P', 2), make_pair('P', 2),
                                    make_pair('R', 2), make_pair('N', 2), make_pair('B', 2), make_pair('K', 2), make_pair('Q', 2), make_pair('B', 2), make_pair('N', 2), make_pair('R', 2)};

char grid [2][8] = { '1', '2', '3', '4', '5', '6', '7', '8',
                     'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

char Char[2];

pair <int, int> fromSpace, toSpace;

int player = 0; //player X will go first

int n = 0; //number of

bool play = true;
bool loop = true;

void Draw()
{
    system("cls");  //clear the game board

    //iterate through the array in 2D
    for (int i=0;i<8;i++)
    {
        cout << grid [0][7-i] << "   ";
        for(int j=0;j<8;j++)
        {
            if (gameTable[i][j].second == 0)
                cout << "||" << gameTable [i][j].first << '|';
            else
                cout << "| " << gameTable [i][j].first << ' ';   //output table state
        }

        cout << '|';
        if (i<7)
            cout << endl << "    ---------------------------------" << endl;
        else
            cout << endl << endl;
    }

    cout << "      ";

    for (int i=0;i<8;i++)
    {
        cout << grid [1][i] << "   ";
    }
}

void TogglePlayer()
{
    if (player == 0)
        player = 2;
    else
        player = 0;
}

//function to translate player input into grid position
pair <int, int> inputToSpace()
{
    pair <int,int> chosenSpace;

    chosenSpace.first = 9 - Char[1] + '0' - 1;
    chosenSpace.second = toupper(Char[0]) - '@' - 1;

    return chosenSpace;
}

string spaceToPiece (pair <int, int> space)
{
    char piece;

    piece = gameTable[space.first][space.second].first;

    if (piece == 'R')
        return "Rook";
    else if (piece == 'N')
        return "Knight";
    else if (piece == 'B')
        return "Bishop";
    else if (piece == 'Q')
        return "Queen";
    else if (piece == 'K')
        return "King";
    else
        return "Pawn";
}

void take()
{
        gameTable[toSpace.first][toSpace.second] = gameTable[fromSpace.first][fromSpace.second];
        gameTable[fromSpace.first][fromSpace.second] = make_pair(' ', 1);
}

int distance()
{
    return sqrt(pow(toSpace.second - fromSpace.second, 2) + pow(toSpace.first - fromSpace.first, 2));
}

int direction(int dis)
{
    int as = (asin((fromSpace.first - toSpace.first) / dis) * 180) / M_PI;
    int ac = (acos((fromSpace.second - toSpace.second) / dis) * 180) / M_PI;

    if (as == 90 && ac == 90)
        return 1;
    else if (as == 90 && ac == 180)
        return 2;
    else if (as == 0 && ac == 180)
        return 3;
    else if (as == -90 && ac == 180)
        return 4;
    else if (as == -90 && ac == 90)
        return 5;
    else if (as == -90 && ac == 0)
        return 6;
    else if (as == 0 && ac == 0)
        return 7;
    else if (as == 90 && ac == 0)
        return 8;
}

bool collision(string piece, int x, int y, int dir, int dis)
{
    for (int i = 1; i < dis; i++)
    {
        if (piece == "Rook")
        {
            if (dir == 1 && gameTable[y-i][x].second != 1) // collides going up
                return true;
            else if (dir == 3 && gameTable[y][i+x].second != 1) // collides going right
                return true;
            else if (dir == 5 && gameTable[i+y][x].second != 1) // collides going down
                return true;
            else if (dir == 7 && gameTable[y][x-i].second != 1) // collides going left
                return true;
        }
        else if (piece == "Bishop")
        {
            if (dir == 2 && gameTable[y-i][x+i].second != 1) // collides going up and to the right
                return true;
            else if (dir == 4 && gameTable[y+i][x+i].second != 1) // collides going down and to the right
                return true;
            else if (dir == 6 && gameTable[y+i][x-i].second != 1) // collides going down and to the left
                return true;
            else if (dir == 8 && gameTable[y-i][x-i].second != 1) // collides going up and to the left
                return true;
        }
        else if (piece == "Queen")
        {
            if (dir == 1 && gameTable[y-i][x].second != 1) // collides going up
                return true;
            else if (dir == 3 && gameTable[y][i+x].second != 1) // collides going right
                return true;
            else if (dir == 5 && gameTable[i+y][x].second != 1) // collides going down
                return true;
            else if (dir == 7 && gameTable[y][x-i].second != 1) // collides going left
                return true;
            else if (dir == 2 && gameTable[y-i][x+i].second != 1) // collides going up and to the right
                return true;
            else if (dir == 4 && gameTable[y+i][x+i].second != 1) // collides going down and to the right
                return true;
            else if (dir == 6 && gameTable[y+i][x-i].second != 1) // collides going down and to the left
                return true;
            else if (dir == 8 && gameTable[y-i][x-i].second != 1) // collides going up and to the left
                return true;
        }
    }
    return false; // never collides
}

bool validMove(string piece, int dir, int dis)
{
    if (piece == "Knight")
    {
        if(((toSpace.first == fromSpace.first + 2 || toSpace.first == fromSpace.first - 2) && (toSpace.second == fromSpace.second + 1 || toSpace.second == fromSpace.second - 1)) || ((toSpace.first == fromSpace.first + 1 || toSpace.first == fromSpace.first - 1) && (toSpace.second == fromSpace.second + 2 || toSpace.second == fromSpace.second - 2)))
            return true;
        else
            return false;
    }
    else if (piece == "King")
    {
        if ((dir == 1 || dir == 3 || dir == 5 || dir == 7) && dis == 1)
            return true;
        else
            return false;
    }
    else if (piece == "Pawn")
    {
        if (player == 0)
        {
            if (dir == 5 && dis == 1)
                return true;
            else if (dir == 5 && dis == 2 && fromSpace.first == 1)
                return true;
            else if ((dir == 4 || dir == 6) && dis == 1 && gameTable[toSpace.first][toSpace.second].second == 2)
                return true;
            else
                return false;
        }
        else if (player == 2)
        {
            if (dir == 1 && dis == 1)
                return true;
            else if (dir == 1 && dis == 2 && fromSpace.first == 6)
                return true;
            else if ((dir == 2 || dir == 8) && dis == 1 && gameTable[toSpace.first][toSpace.second].second == 0)
                return true;
            else
                return false;
        }
    }
    else if (piece == "Rook")
    {
        if (collision(piece, fromSpace.second, fromSpace.first, dir, dis) == false && (dir == 1 || dir == 3 || dir == 5 || dir == 7))
            return true;
        else
            return false;
    }
    else if (piece == "Bishop")
    {
        if (collision(piece, fromSpace.second, fromSpace.first, dir, dis) == false && (dir == 2 || dir == 4 || dir == 6 || dir == 8))
            return true;
        else
            return false;
    }
    else if (piece == "Queen")
    {
        if (collision(piece, fromSpace.second, fromSpace.first, dir, dis) == false)
            return true;
        else
            return false;
    }
}

int main()
{
    Draw();
    while(1)
    {
        cout << "\nWhich piece would you like to move? ";
        while (loop == true)
        {
            cin.getline(Char, 3);
            fromSpace = inputToSpace();
            if (gameTable[fromSpace.first][fromSpace.second].second != player)
                cout << "Please select one of your pieces. ";
            else
                loop == false;
        }
        loop = true;
        cout << "Where would you like to move your " << spaceToPiece(fromSpace) << " to? ";
        while (loop == true)
        {
            cin.getline(Char, 3);
            toSpace = inputToSpace();
            if (gameTable[toSpace.first][toSpace.second].second == player)
                cout << "Please select a place that is not your own. ";
            else
            {
                if (validMove(spaceToPiece(fromSpace), direction(distance()), distance())==true)
                    loop = false;
                else
                    cout << "Please make a valid move. ";
            }
        }
        loop = true;
        take();
        TogglePlayer();
        Draw();
    }
    return 0;
}
