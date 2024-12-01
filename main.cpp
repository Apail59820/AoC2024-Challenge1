#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>

bool LoadListFromFile(std::vector<std::pair<int, int>>& vec) {
    std::ifstream inputFile("../day1Input.txt");
    if (!inputFile) {
        std::cerr << "Error while opening input file." << std::endl;
        return false;
    }

    int left, right;
    while (inputFile >> left >> right) {
        vec.emplace_back(left, right);
    }

    inputFile.close();
    return true;
}

int main() {
    std::vector<std::pair<int, int>> lists;
    const auto start = std::chrono::high_resolution_clock::now();

    if (!LoadListFromFile(lists)) {
        std::cerr << "Error while loading lists." << std::endl;
        return 1;
    }

    std::unordered_map<int, int> leftFreq, rightFreq;

    for (const auto& [left, right] : lists) {
        ++leftFreq[left];
        ++rightFreq[right];
    }

    int totalDist = 0;
    int similarityScore = 0;

    for (const auto& [leftValue, leftCount] : leftFreq) {
        if (rightFreq.find(leftValue) != rightFreq.end()) {
            similarityScore += leftValue * leftCount * rightFreq[leftValue];
        }
    }

    for (const auto& [left, right] : lists) {
        totalDist += right - left;
    }

    std::cout << "Total distance : " << totalDist << std::endl;
    std::cout << "Similarity score : " << similarityScore << std::endl;

    const auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Finished in: " << elapsed.count() << " ms" << std::endl;

    return 0;
}