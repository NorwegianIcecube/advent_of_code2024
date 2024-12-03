#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;

int main() {
    ifstream infile("puzzle_input");
    string line;
    string puzzle_input;
    while (getline(infile, line)) {
        puzzle_input += line + "\n";
    }

    int sum = 0;
    regex re("mul\\((\\d{1,3}),(\\d{1,3})\\)");
    for (sregex_iterator i = sregex_iterator(puzzle_input.begin(), puzzle_input.end(), re); i != sregex_iterator(); i++) {
        smatch match = *i;
        int num1 = stoi(match[1]);
        int num2 = stoi(match[2]);
        sum += num1 * num2;
    }

    cout << sum << endl;
}