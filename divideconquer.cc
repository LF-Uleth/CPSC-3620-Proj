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

//calc distance between points
double calculateDistance(const Point& p1, const Point& p2) {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

//compares x for sorting
bool compareByX(const Point& p1, const Point& p2) {
    return p1.x < p2.x;
}

//compares y for sorting
bool compareByY(const Point& p1, const Point& p2) {
    return p1.y < p2.y;
}

//find the closest pair in strip
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

//recursive/bruteforce function to find closest pairs
double closestPairRecursive(std::vector<Point>& points, int left, int right, Point& p1, Point& p2) {
    if (right - left <= 3) { //brute force small sets
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

    //otherwise recursive check for closest pair
    
    int mid = left + (right - left) / 2; //get midpoint
    Point midPoint = points[mid];

    //get closest pair in left+right subsets
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

    //set strip
    std::vector<Point> strip;
    for (int i = left; i < right; ++i) {
        if (std::abs(points[i].x - midPoint.x) < d) {
            strip.push_back(points[i]);
        }
    }

    //get strip pair
    return std::min(d, closestInStrip(strip, d, p1, p2));
}

//prep pairs for check by ordering by x
double closestPair(std::vector<Point>& points, Point& p1, Point& p2) {
    std::sort(points.begin(), points.end(), compareByX);
    return closestPairRecursive(points, 0, points.size(), p1, p2);
}

int main() {
    //get filename
    std::string filename;
    std::cout << "Enter the input file name: ";
    std::cin >> filename;

    //read from file
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error with File: " << filename << std::endl;
        return 1;
    }

    //get points from file
    int x, y;
    char delim1, delim2, delim3;
    while (infile >> delim1 >> x >> delim2 >> y >> delim3) {
        points.push_back({x, y});
    }
    infile.close();

    //get time for pair
    Point p1, p2;
    auto start = std::chrono::high_resolution_clock::now(); //start timer
    double minDistance = closestPair(points, p1, p2);
    auto end = std::chrono::high_resolution_clock::now(); // end timer
    std::chrono::duration<double> elapsed = end - start;

    //output
    std::cout << "Closest pair of points: (" << p1.x << "," << p1.y << ") and (" << p2.x << "," << p2.y << ")" << std::endl;
    std::cout << "Minimum distance: " << minDistance << std::endl;
    std::cout << "Time taken: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}
