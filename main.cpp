//
// Created by Amaury Paillard on 01/12/2024.
//

#include <fstream>
#include <iostream>


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

    if(!LoadListFromFile(lists)) {
        std::cerr << "Error while loading lists." << std::endl;
    }

    std::vector<int> leftList, rightList;
    for (const auto&[fst, snd] : lists) {
        leftList.push_back(fst);
        rightList.push_back(snd);
    }

    std::sort(leftList.begin(), leftList.end());
    std::sort(rightList.begin(), rightList.end());


    lists.clear();

    int totalDist = 0;
    int similarityScore = 0;

    if(leftList.size() == rightList.size()) {
        const int listSize = static_cast<int>(leftList.size());
        int count = 0;

        for(int i = 0; i < listSize; ++i) {

            count = static_cast<int>(std::count(rightList.begin(), rightList.end(), leftList[i]));
            similarityScore += leftList[i] * count;

            totalDist += rightList[i] - leftList[i];
        }
    }

    std::cout << "Total distance : " << totalDist << std::endl;
    std::cout << "Similarity score : " << similarityScore << std::endl;

    const auto end = std::chrono::high_resolution_clock::now();

    const std::chrono::duration<double, std::milli> elapsed = end - start;
    std::cout << "Finished in: " << elapsed.count() << " ms" << std::endl;

    return 0;
}