#include <iostream>
#include <string>
#include <vector>

// basically cracking the code interview 8.2
// take vector<string> that represents a path (left,down) and determine if a path to end exists in the required time.
// dynamic programming question.

struct Position
{
    const unsigned int Row;
    const unsigned int Column;
};

bool operator==(const Position &lhs, const Position &rhs)
{
    return (lhs.Row == rhs.Row && lhs.Column == lhs.Column);
}
bool isOutOfBounds(const Position &destination, const Position &current)
{
    return (current.Row > destination.Row || current.Column > destination.Column);
}
struct FormattedGrid
{
    explicit FormattedGrid(std::vector<std::string> stringGrid) : Destination{stringGrid.size() - 1, stringGrid.front().size() - 1}
    {
        boolean_Grid.reserve(Destination.Row + 1);
        for (const auto &str : stringGrid)
        {
            std::vector<bool> v;
            for (auto c : str)
            {
                v.push_back(c == '.');
            }
            boolean_Grid.push_back(v);
        }
    }
    bool isPositionFree(const Position &position) const
    {
        if (isOutOfBounds(Destination, position))
        {
            return false;
        }
        return boolean_Grid[position.Row][position.Column];
    }
    std::vector<std::vector<bool>> boolean_Grid;
    const Position Destination;
};

bool doesPathExistRec(const FormattedGrid &formatted_grid, Position currentPosition, int maxSteps)
{
    //base cases
    //out of bounds
    if (maxSteps < 0)
    {
        return false;
    }

    //success
    if (formatted_grid.Destination == currentPosition)
    {
        return true;
    }

    auto go_right = formatted_grid.isPositionFree({currentPosition.Row, currentPosition.Column + 1}) && doesPathExistRec(formatted_grid, {currentPosition.Row, currentPosition.Column + 1}, maxSteps - 1);
    auto go_down = formatted_grid.isPositionFree({currentPosition.Row + 1, currentPosition.Column}) && doesPathExistRec(formatted_grid, {currentPosition.Row + 1, currentPosition.Column}, maxSteps - 1);
    return go_right || go_down;
}

std::string doesPathExist(const std::vector<std::string> &stringGrid, int maxSteps)
{
    FormattedGrid grid(stringGrid);
    auto match = doesPathExistRec(grid, {0, 0}, maxSteps);
    if (match)
    {
        return "yes";
    }
    else
    {
        return "no";
    }
}

int main()
{
    std::cout << doesPathExist({".#.",
                                "..#",
                                "#.#",
                                "#.."},
                               5)
              << '\n';
    std::cout << doesPathExist({".#.#",
                                ".#.#",
                                "..##",
                                "#...",
                                "###."},
                               8)
              << '\n';

    return 0;
}