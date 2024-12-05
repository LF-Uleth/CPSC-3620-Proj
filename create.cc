#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

int main() {
    int n;

std::srand(std::time(nullptr));
std::string filename = "output" + std::to_string(n) + ".txt";
std::ofstream outfile(filename);

for (int i = 0; i < n; ++i) {
        int x = std::rand() % 20001 - 10000; // Generate x in range [-10000, 10000]
        int y = std::rand() % 20001 - 10000; // Generate y in range [-10000, 10000]
        outfile << "(" << x << "," << y << ")" << std::endl;
    }

outfile.close();

return 0;
}
