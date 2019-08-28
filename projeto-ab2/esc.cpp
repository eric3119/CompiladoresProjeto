#include <iostream>
#include <fstream>
#include "src/Parser.h"

using namespace std;

int main(int argc, const char **argv) {
    if (argc != 2){

        cout << "use: " << argv[0] << " prog.esc" << endl;

        exit(0);
    }

    string s(argv[1]);

    ifstream fileTest(s);
    if (!fileTest.is_open()){
        cout << "File not found" << endl;
        exit(0);
    }
    fileTest.close();

    Parser parser(argv[1]);

    parser.parse();

    return 0;
}