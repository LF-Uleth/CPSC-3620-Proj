#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <chrono>

struct Point {
    int x, y;
};

// Function to calculate the Euclidean distance between two points
double calculateDistance(const Point& p1, const Point& p2) {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Brute-force closest-pair algorithm
void findClosestPair(const std::vector<Point>& points, Point& p1, Point& p2, double& minDistance) {
    minDistance = std::numeric_limits<double>::max();
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            double distance = calculateDistance(points[i], points[j]);
            if (distance < minDistance) {
                minDistance = distance;
                p1 = points[i];
                p2 = points[j];
            }
        }
    }
}

int main() {
    std::string filename;
    std::cout << "Enter the input file name: ";
    std::cin >> filename;

    // Read points from the file
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return 1;
    }

    std::vector<Point> points;
    int x, y;
    char delim1, delim2, delim3;
    while (infile >> delim1 >> x >> delim2 >> y >> delim3) {
        points.push_back({x, y});
    }
    infile.close();

    if (points.size() < 2) {
        std::cerr << "Not enough points to find the closest pair." << std::endl;
        return 1;
    }

    // Measure time and find the closest pair
    Point p1, p2;
    double minDistance;
    auto start = std::chrono::high_resolution_clock::now();
    findClosestPair(points, p1, p2, minDistance);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Output the result
    std::cout << "Closest pair of points: (" << p1.x << "," << p1.y << ") and ("
              << p2.x << "," << p2.y << ")" << std::endl;
    std::cout << "Minimum distance: " << minDistance << std::endl;
    std::cout << "Time taken: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}
