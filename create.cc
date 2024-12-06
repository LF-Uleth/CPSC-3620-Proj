#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

int main() {
    //get n
    int n;
    std::cout << "Enter the number of points (n): ";
    std::cin >> n;

//rand generate setup
std::srand(std::time(nullptr)); //rand seed for generation from time
std::string filename = "output" + std::to_string(n) + ".txt"; 
std::ofstream outfile(filename);

//create points between -10000 and 10000
for (int i = 0; i < n; ++i) {
        int x = std::rand() % 20001 - 10000;
        int y = std::rand() % 20001 - 10000;
        outfile << "(" << x << "," << y << ")" << std::endl;
    }

outfile.close();

return 0;
}
