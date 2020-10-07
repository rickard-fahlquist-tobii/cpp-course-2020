#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <string>

#include "Blocks.h"

using namespace std::string_literals;

int main(int argc, char** argv)
{

    hw2::Text<16> block;
    const std::string imsg("Let's do some hacking!");

    block.value(imsg);

    auto omsg = block.value();

    std::cout << omsg << "\n";

    hw2::Text<16> block2;
    const std::string imsg2("Let");

    block2.value(imsg2);

    auto omsg2 = block2.value();

    std::cout << omsg2 << "\n";

    hw2::Number<4> numBk;
    numBk.value(23);
    std::cout << numBk.value() << "\n";

    hw2::Number<5> numBk2;
    numBk2.value(987654);
    std::cout << numBk2.value() << "\n";


    return 0;
}
