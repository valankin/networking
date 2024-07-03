/**
 * @file debug.cpp 
 */
#include <iostream>

void foo(int x) {
    int y = x + 5;
    std::cout << "In foo: " << y << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <number>" << std::endl;
        return 1;
    }

    int a = std::stoi(argv[1]);
    std::cout << "Input argument: " << a << std::endl;
    foo(a);
    return 0;
}

