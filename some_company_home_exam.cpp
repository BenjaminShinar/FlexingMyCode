#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <bitset>

// basically cracking the code interview 8.2
// take vector<string> that represents a path (right,down) and determine if a path to end exists in the required amount of steps.

/*
* created a convient representation of the string.
* depending on the range of input sizes, maybe std::bitset<> with an upper bound N is better than std::vector<bool>?
*Hints: #331, #360, #388 
* option 1: recursive function
* use max steps to optimize
* use std::bitset<> instead of vector - requires advance knowledge about input size, might actually cost more memory
* option 2: turn recursion into iterative solution
* BFS (Breadth First Search) DFS (depth first search) - graph traversal?
* bfs - use a queue?
* at each node/edge, take all paths and push to the back of the queue, now take the front of the queue, and do the same, each time we use we a node, we remove it from the queue.
* in our case, we construct positions struct instead of using edges from a tree
* how will this work if we have a loop inside the graph?
* dfs - use a stack?
* we take take one path and run with it to the end, similiar to recursive function,
* we push two values to the stack each time, with the top one being the one we want to visit first
* option 3: dynamic programming
* create a mirror of the data, keep track of what we know.
* each position can be marked as "not visited", "has valid path","no valid path".
* i think it's best to start the scan from the end? sta
* use enum
* can we do an early exit? - yes
* maybe we can drop the new data strucute and use the original? yes.
* do we have to scan all elements? can we skip dead branches somehow?
* 
* THINK ABOUT BENCHMARKING THE OPTIONS 
*/
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

// might be better with std::bitset<>
struct FormattedGridVector
{
    explicit FormattedGridVector(std::vector<std::string> stringGrid) : Destination{stringGrid.size() - 1, stringGrid.front().size() - 1}, StepsRequired{Destination.Column + Destination.Row}
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

private:
    std::vector<std::vector<bool>> boolean_Grid;

public:
    const Position Destination;
    const std::size_t StepsRequired;
};

struct FormattedGridBitset512
{
    explicit FormattedGridBitset512(std::vector<std::string> stringGrid) : Destination{stringGrid.size() - 1, stringGrid.front().size() - 1}, StepsRequired{Destination.Column + Destination.Row}
    {
        boolean_Grid.reserve(Destination.Row + 1);
        for (const auto &str : stringGrid)
        {
            std::bitset<512> b{0};
            //use pointer arithmetic for better results, i don't care;
            for (int i = 0; i < Destination.Column + 1; ++i)
            {
                // is there a better way to initilize it?
                b.set(i, str.at(i) == '.');
            }
            boolean_Grid.push_back(b);
        }
    }
    bool isPositionFree(const Position &position) const
    {
        if (isOutOfBounds(Destination, position))
        {
            return false;
        }
        return boolean_Grid[position.Row].test(position.Column);
    }

private:
    std::vector<std::bitset<512>> boolean_Grid;

public:
    const Position Destination;
    const std::size_t StepsRequired;
};
//T is formatted grid of some kind
template <typename T>
bool doesPathExistRec(const T &formatted_grid, Position currentPosition)
{
    //base cases
    //path is blocked
    if (!formatted_grid.isPositionFree(currentPosition))
    {
        return false;
    }
    //success
    if (formatted_grid.Destination == currentPosition)
    {
        return true;
    }

    //same row so that maybe we will get some short circuting if the first is true; up to the cpu to skip the execution
    return doesPathExistRec(formatted_grid, {currentPosition.Row, currentPosition.Column + 1}) || doesPathExistRec(formatted_grid, {currentPosition.Row + 1, currentPosition.Column});
}

//T is formatted grid of some kind
template <typename T>
std::string doesPathExist(const std::vector<std::string> &stringGrid, int maxSteps)
{
    T formatted_Grid(stringGrid);
    //check this once,
    // we know that the distance is fixed, so no need to check this each step
    if (formatted_Grid.StepsRequired > maxSteps)
    {
        return "no - early exit";
    }

    auto match = doesPathExistRec(formatted_Grid, {0, 0});
    if (match)
    {
        return "yes";
    }
    else
    {
        return "no";
    }
}

template <typename T>
std::string doesPathExistIterBFS(const std::vector<std::string> &stringGrid, int maxSteps)
{
    T formatted_Grid(stringGrid);

    if (formatted_Grid.StepsRequired > maxSteps)
    {
        return "no - early exit";
    }
    std::queue<Position> paths_Queue;
    paths_Queue.push({0, 0});

    //doesn't work for some stupid reason
    //paths_Queue.emplace(0, 0);

    while (!paths_Queue.empty())
    {
        auto current_position = paths_Queue.front();
        paths_Queue.pop();

        if (formatted_Grid.isPositionFree(current_position))
        {
            if (formatted_Grid.Destination == current_position)
            {
                return "yes";
            }
            paths_Queue.push({current_position.Row, current_position.Column + 1});
            paths_Queue.push({current_position.Row + 1, current_position.Column});
        }
    }
    return "no";
}

template <typename T>
std::string doesPathExistIterDFS(const std::vector<std::string> &stringGrid, int maxSteps)
{

    T formatted_Grid(stringGrid);

    if (formatted_Grid.StepsRequired > maxSteps)
    {
        return "no - early exit";
    }
    std::stack<Position> paths_Stack;
    paths_Stack.push({0, 0});

    while (!paths_Stack.empty())
    {
        auto current_position = paths_Stack.top();
        paths_Stack.pop();
        if (formatted_Grid.isPositionFree(current_position))
        {
            if (formatted_Grid.Destination == current_position)
            {
                return "yes";
            }
            //reverse order the DFS, becuase FIFO
            paths_Stack.push({current_position.Row + 1, current_position.Column}); //this will be second
            paths_Stack.push({current_position.Row, current_position.Column + 1}); //this will be first
        }
    }
    return "no";
}

enum class DynamicVisit
{
    NOT_VISITED,
    NO_VALID_PATHS,
    HAS_VALID_PATHS
};

std::string doesPathExistDynamicBackwards(const std::vector<std::string> &stringGrid, int maxSteps)
{

    auto n_rows = static_cast<int>(stringGrid.size());
    auto n_cols = static_cast<int>(stringGrid.front().size());
    if ((n_rows + n_cols - 2) > maxSteps)
    {
        return "no - early exit";
    }

    std::vector<std::vector<DynamicVisit>> visited_table{n_rows, std::vector<DynamicVisit>{n_cols, DynamicVisit::NOT_VISITED}};
    //destination must be ok
    visited_table[n_rows - 1][n_cols - 1] = DynamicVisit::HAS_VALID_PATHS;

    //this isn't good enough
    for (auto row = n_rows - 1; row >= 0; --row)
    {
        for (auto col = n_cols - 1; col >= 0; --col)
        {
            if (visited_table[row][col] == DynamicVisit::NOT_VISITED)
            {
                bool match{stringGrid[row][col] == '.'};
                //hope for compiler to shortCircut and not compute these
                match |= (col < (n_cols - 1)) && visited_table[row][col + 1] == DynamicVisit::HAS_VALID_PATHS;
                match |= (row < (n_rows - 1)) && visited_table[row + 1][col] == DynamicVisit::HAS_VALID_PATHS;

                if (match)
                {
                    visited_table[row][col] = DynamicVisit::HAS_VALID_PATHS;
                }
                else
                {
                    visited_table[row][col] = DynamicVisit::NO_VALID_PATHS;
                }
            }
        }
    }
    if (visited_table.front().front() == DynamicVisit::HAS_VALID_PATHS)
    {
        return "yes";
    }
    return "no";
}

std::string doesPathExistDynamicForwards(const std::vector<std::string> &stringGrid, int maxSteps)
{

    auto n_rows = static_cast<int>(stringGrid.size());
    auto n_cols = static_cast<int>(stringGrid.front().size());
    if ((n_rows + n_cols - 2) > maxSteps)
    {
        return "no - early exit";
    }

    std::vector<std::vector<DynamicVisit>> visited_table{n_rows, std::vector<DynamicVisit>{n_cols, DynamicVisit::NOT_VISITED}};
    //destination must be ok
    visited_table[n_rows - 1][n_cols - 1] = DynamicVisit::HAS_VALID_PATHS;

    //this isn't good enough
    for (auto row = n_rows - 1; row >= 0; --row)
    {
        for (auto col = n_cols - 1; col >= 0; --col)
        {
            if (visited_table[row][col] == DynamicVisit::NOT_VISITED)
            {
                bool match{stringGrid[row][col] == '.'};
                //hope for compiler to shortCircut and not compute these
                match |= (col < (n_cols - 1)) && visited_table[row][col + 1] == DynamicVisit::HAS_VALID_PATHS;
                match |= (row < (n_rows - 1)) && visited_table[row + 1][col] == DynamicVisit::HAS_VALID_PATHS;

                if (match)
                {
                    visited_table[row][col] = DynamicVisit::HAS_VALID_PATHS;
                }
                else
                {
                    visited_table[row][col] = DynamicVisit::NO_VALID_PATHS;
                }
            }
        }
    }
    if (visited_table.front().front() == DynamicVisit::HAS_VALID_PATHS)
    {
        return "yes";
    }
    return "no";
}

int main()
{
    std::vector<std::string> simple_case{".#.",
                                         "..#",
                                         "#.#",
                                         "#.."};
    std::vector<std::string> advance_case{".#.#",
                                          ".#.#",
                                          "..##",
                                          "#...",
                                          "###."};
    std::vector<std::string> advance_case_step{".#.#",
                                               ".#.#",
                                               "..##",
                                               "#...",
                                               "###."};
    std::vector<std::string> blocked_case{".#..",
                                          ".##.",
                                          "..#.",
                                          "#.#.",
                                          "###."};

    std::cout << "using vector version" << '\n';
    {
        std::cout << "simple case: " << doesPathExist<FormattedGridVector>(simple_case, 5) << '\n';
        std::cout << "advanced case: " << doesPathExist<FormattedGridVector>(advance_case, 7) << '\n';
        std::cout << "advance insufficent steps case: " << doesPathExist<FormattedGridVector>(advance_case_step, 6) << '\n';
        std::cout << "blocked case: " << doesPathExist<FormattedGridVector>(blocked_case, 10) << '\n';
        std::cout << '\n';
    }
    std::cout << "bitset<512> version" << '\n';
    {
        std::cout << "simple case: " << doesPathExist<FormattedGridBitset512>(simple_case, 5) << '\n';
        std::cout << "advanced case: " << doesPathExist<FormattedGridBitset512>(advance_case, 7) << '\n';
        std::cout << "advance insufficent steps case: " << doesPathExist<FormattedGridBitset512>(advance_case_step, 6) << '\n';
        std::cout << "blocked case: " << doesPathExist<FormattedGridBitset512>(blocked_case, 10) << '\n';
        std::cout << '\n';
    }
    std::cout << "Iterrative BFS version" << '\n';
    {
        std::cout << "simple case: " << doesPathExistIterBFS<FormattedGridBitset512>(simple_case, 5) << '\n';
        std::cout << "advanced case: " << doesPathExistIterBFS<FormattedGridBitset512>(advance_case, 7) << '\n';
        std::cout << "advance insufficent steps case: " << doesPathExistIterBFS<FormattedGridBitset512>(advance_case_step, 6) << '\n';
        std::cout << "blocked case: " << doesPathExistIterBFS<FormattedGridBitset512>(blocked_case, 10) << '\n';
        std::cout << '\n';
    }
    std::cout << "Iterrative DFS version" << '\n';
    {
        std::cout << "simple case: " << doesPathExistIterDFS<FormattedGridVector>(simple_case, 5) << '\n';
        std::cout << "advanced case: " << doesPathExistIterDFS<FormattedGridVector>(advance_case, 7) << '\n';
        std::cout << "advance insufficent steps case: " << doesPathExistIterDFS<FormattedGridVector>(advance_case_step, 6) << '\n';
        std::cout << "blocked case: " << doesPathExistIterDFS<FormattedGridVector>(blocked_case, 10) << '\n';
        std::cout << '\n';
    }

    std::cout << "Dynamic Programming backwards version" << '\n';
    {
        std::cout << "simple case: " << doesPathExistDynamicBackwards(simple_case, 5) << '\n';
        std::cout << "advanced case: " << doesPathExistDynamicBackwards(advance_case, 7) << '\n';
        std::cout << "advance insufficent steps case: " << doesPathExistDynamicBackwards(advance_case_step, 6) << '\n';
        std::cout << "blocked case: " << doesPathExistDynamicBackwards(blocked_case, 10) << '\n';
        std::cout << '\n';
    }

    std::cout << "Dynamic Programming forewards version" << '\n';
    {
        std::cout << "simple case: " << doesPathExistDynamicForwards(simple_case, 5) << '\n';
        std::cout << "advanced case: " << doesPathExistDynamicForwards(advance_case, 7) << '\n';
        std::cout << "advance insufficent steps case: " << doesPathExistDynamicForwards(advance_case_step, 6) << '\n';
        std::cout << "blocked case: " << doesPathExistDynamicForwards(blocked_case, 10) << '\n';
        std::cout << '\n';
    }
    return 0;
}