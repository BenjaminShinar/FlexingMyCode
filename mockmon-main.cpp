#include "mockmon\include\game_driver\main.h"
//#include <boost/uuid/uuid.hpp>

#include <string>
#include <iostream>
//#include <fmt\format.h>

int main(int argc, char *argv[])
{
    std::string mockmonName{"nameless!"};
    int maxFloor(10);

    if (argc < 3)
    {

        std::cout << "how will you call your mockmon?" << '\n';
        std::cin >> mockmonName;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else
    {
        mockmonName = (argv[1]);
        std::string arg = argv[2];
        try
        {
            std::size_t pos;
            int x = std::stoi(arg, &pos);
            if (x > 0)
                maxFloor = x;
            if (pos < arg.size())
            {
                std::cerr << "Trailing characters after number: " << arg << '\n';
            }
        }
        catch (std::invalid_argument const &ex)
        {
            std::cerr << "Invalid number: " << arg << '\n';
        }
        catch (std::out_of_range const &ex)
        {
            std::cerr << "Number out of range: " << arg << '\n';
        }
    }
    //fmt::print("starting! {}\n", mockmonName);
    StartGame(mockmonName, maxFloor);
}