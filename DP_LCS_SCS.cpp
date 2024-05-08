#include <vector>
#include <array>
#include <iostream>
#include <list>

void print_matrix(std::vector<std::vector<unsigned>> _matrix)
{
    for (const auto &row : _matrix)
    {
        for (const auto &element : row)
        {
            std::cout << element << "  ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void print_list(std::list<char> _list)
{
    for (const auto &element : _list)
    {
        std::cout << element << ' ';
    }
    std::cout << '\n';
}

std::list<char> lcs(std::vector<char> const &_x, std::vector<char> const &_y)
{
    std::vector<std::vector<unsigned>> c;
    std::vector<std::vector<unsigned>> b;

    unsigned const northWest = 1;
    unsigned const west = 2;
    unsigned const north = 3;

    c.push_back(std::vector<unsigned>(_y.size() + 1));
    b.push_back(std::vector<unsigned>(_y.size() + 1));

    for (unsigned xIndex = 0; xIndex < _x.size(); ++xIndex)
    {
        c.push_back(std::vector<unsigned>(_y.size() + 1));
        b.push_back(std::vector<unsigned>(_y.size() + 1));

        for (unsigned yIndex = 0; yIndex < _y.size(); ++yIndex)
        {
            if (_x[xIndex] == _y[yIndex])
            {
                c[xIndex + 1][yIndex + 1] = c[xIndex][yIndex] + 1;
                b[xIndex + 1][yIndex + 1] = northWest;
            }

            else if (c[xIndex][yIndex + 1] >= c[xIndex + 1][yIndex])
            {
                c[xIndex + 1][yIndex + 1] = c[xIndex][yIndex + 1];
                b[xIndex + 1][yIndex + 1] = north;
            }
            else
            {
                c[xIndex + 1][yIndex + 1] = c[xIndex + 1][yIndex];
                b[xIndex + 1][yIndex + 1] = west;
            }
        }
    }

    std::list<char> z;

    for (int xIndex = _x.size() - 1, yIndex = _y.size() - 1; xIndex >= 0 and yIndex >= 0;)
    {
        if (b[xIndex + 1][yIndex + 1] == northWest)
        {
            z.push_front(_x[xIndex--]);
            yIndex--;
        }
        else if (b[xIndex + 1][yIndex + 1] == north)
        {
            xIndex--;
        }
        else
        {
            yIndex--;
        }
    }
    return z;
}

std::list<char> scs(std::vector<char> const &_x, std::vector<char> const &_y)
{
    std::vector<std::vector<unsigned>> c;
    std::vector<std::vector<unsigned>> b;

    unsigned const northWest = 1;
    unsigned const west = 2;
    unsigned const north = 3;

    c.push_back(std::vector<unsigned>(_y.size() + 1));
    b.push_back(std::vector<unsigned>(_y.size() + 1));
    for (unsigned yIndex = 0; yIndex < _y.size(); ++yIndex)
    {
        c[0][yIndex + 1] = yIndex + 1;
    }

    for (unsigned xIndex = 0; xIndex < _x.size(); ++xIndex)
    {
        c.push_back(std::vector<unsigned>(_y.size() + 1));
        b.push_back(std::vector<unsigned>(_y.size() + 1));

        c[xIndex + 1][0] = xIndex + 1;

        for (unsigned yIndex = 0; yIndex < _y.size(); ++yIndex)
        {
            if (_x[xIndex] == _y[yIndex])
            {
                c[xIndex + 1][yIndex + 1] = c[xIndex][yIndex] + 1;
                b[xIndex + 1][yIndex + 1] = northWest;
            }

            else if (c[xIndex][yIndex + 1] <= c[xIndex + 1][yIndex])
            {
                c[xIndex + 1][yIndex + 1] = c[xIndex][yIndex + 1] + 1;
                b[xIndex + 1][yIndex + 1] = north;
            }
            else
            {
                c[xIndex + 1][yIndex + 1] = c[xIndex + 1][yIndex] + 1;
                b[xIndex + 1][yIndex + 1] = west;
            }
        }
    }

    std::list<char> z;

    int xIndex = _x.size() - 1, yIndex = _y.size() - 1;
    while (xIndex >= 0 and yIndex >= 0)
    {
        if (b[xIndex + 1][yIndex + 1] == northWest)
        {
            z.push_front(_x[xIndex--]);
            yIndex--;
        }
        else if (b[xIndex + 1][yIndex + 1] == north)
        {
            z.push_front(_x[xIndex--]);
        }
        else
        {
            z.push_front(_y[yIndex--]);
        }
    }
    while (xIndex >= 0)
    {
        z.push_front(_x[xIndex--]);
    }
    while (yIndex >= 0)
    {
        z.push_front(_y[yIndex--]);
    }

    return z;
}

int main(void)
{
    std::vector<char> x, y;
    x.push_back('A');
    x.push_back('B');
    x.push_back('C');
    x.push_back('B');
    x.push_back('D');
    x.push_back('A');
    x.push_back('B');

    y.push_back('B');
    y.push_back('D');
    y.push_back('C');
    y.push_back('A');
    y.push_back('B');
    y.push_back('A');

    const auto w = lcs(x, y);
    const auto z = scs(x, y);

    print_list(w);
    print_list(z);
    return 0;
}