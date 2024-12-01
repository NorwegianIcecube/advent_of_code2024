#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


int main() 
{
    // Create vector for a and vector for b
    std::vector<int> a_s;
    std::vector<int> b_s;

    // Getting all numbers from lists and storing them in vectors
    std::ifstream infile("puzzle_input");
    int a, b;
    while (infile >> a >> b)
    {
        a_s.push_back(a);
        b_s.push_back(b);
    }

    // Sorting the vectors in ascending order
    sort(a_s.begin(), a_s.end());
    sort(b_s.begin(), b_s.end());

    // For each number in vector a, count the number of occurences in vector b, multiply the number in a with the count and add this product to the sum
    int sum = 0;
    for (int i = 0; i < a_s.size(); i++)
    {
        sum += a_s[i] * count(b_s.begin(), b_s.end(), a_s[i]);
    }

    std::cout << sum << std::endl;
}