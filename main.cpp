#include <iostream>
#include <string>

void runTests();

int main(int argc, char *argv[]) {
    // FIXME: if you want to run test uncomment the next line
    runTests();


    // if arg count is less than 3 -> no input and output files specified
    if (argc < 3) {
        throw std::invalid_argument("You have to specify input and output files");
    }

    // get input and output files from args
    std::string input_file = argv[1], output_file = argv[2];

    std::cout << input_file << ' ' << output_file << '\n';

    return EXIT_SUCCESS;
}
