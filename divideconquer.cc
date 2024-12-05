#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <chrono>

struct Point {
    int x, y;
};

// Function to calculate the Euclidean distance between two points
double calculateDistance(const Point& p1, const Point& p2) {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Comparator for sorting points by x-coordinate
bool compareByX(const Point& p1, const Point& p2) {
    return p1.x < p2.x;
}

// Comparator for sorting points by y-coordinate
bool compareByY(const Point& p1, const Point& p2) {
    return p1.y < p2.y;
}

// Find the closest distance in the strip
double closestInStrip(std::vector<Point>& strip, double d, Point& p1, Point& p2) {
    double minDist = d;
    std::sort(strip.begin(), strip.end(), compareByY);

    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; ++j) {
            double dist = calculateDistance(strip[i], strip[j]);
            if (dist < minDist) {
                minDist = dist;
                p1 = strip[i];
                p2 = strip[j];
            }
        }
    }
    return minDist;
}

// Recursive function to find the closest pair of points
double closestPairRecursive(std::vector<Point>& points, int left, int right, Point& p1, Point& p2) {
    if (right - left <= 3) { // Use brute force for small subsets
        double minDist = std::numeric_limits<double>::max();
        for (int i = left; i < right; ++i) {
            for (int j = i + 1; j < right; ++j) {
                double dist = calculateDistance(points[i], points[j]);
                if (dist < minDist) {
                    minDist = dist;
                    p1 = points[i];
                    p2 = points[j];
                }
            }
        }
        return minDist;
    }

    int mid = left + (right - left) / 2;
    Point midPoint = points[mid];

    Point leftP1, leftP2, rightP1, rightP2;
    double dLeft = closestPairRecursive(points, left, mid, leftP1, leftP2);
    double dRight = closestPairRecursive(points, mid, right, rightP1, rightP2);

    double d = std::min(dLeft, dRight);
    if (d == dLeft) {
        p1 = leftP1;
        p2 = leftP2;
    } else {
        p1 = rightP1;
        p2 = rightP2;
    }

    // Build the strip
    std::vector<Point> strip;
    for (int i = left; i < right; ++i) {
        if (std::abs(points[i].x - midPoint.x) < d) {
            strip.push_back(points[i]);
        }
    }

    // Find the closest pair in the strip
    return std::min(d, closestInStrip(strip, d, p1, p2));
}

// Entry point for the divide-and-conquer closest-pair algorithm
double closestPair(std::vector<Point>& points, Point& p1, Point& p2) {
    std::sort(points.begin(), points.end(), compareByX);
    return closestPairRecursive(points, 0, points.size(), p1, p2);
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
    auto start = std::chrono::high_resolution_clock::now();
    double minDistance = closestPair(points, p1, p2);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    // Output the result
    std::cout << "Closest pair of points: (" << p1.x << "," << p1.y << ") and ("
              << p2.x << "," << p2.y << ")" << std::endl;
    std::cout << "Minimum distance: " << minDistance << std::endl;
    std::cout << "Time taken: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}
