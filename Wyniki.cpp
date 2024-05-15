

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Wyniki.h"


Wyniki::Wyniki(int punktyRed, int punktyBlue) : punktyRED(punktyRed), punktyBLUE(punktyBlue) {};

int Wyniki::zapiszWynik(){
    std::ofstream outputFile("/Users/zuziagwiazda/CLionProjects/hexprojektfinal/wszystkieWyniki", std::ios::app);

    if (outputFile.is_open()) {
        outputFile << "punkty RED: " << punktyRED << ", punkty BLUE: " << punktyBLUE << std::endl;
        outputFile.close();
        std::cout << "Zapisano dane do pliku1." << std::endl;
    } else {
        std::cout << "Nie można otworzyć pliku." << std::endl;
    }
    return 0;

}
bool Wyniki::porownajWyniki(const std::pair<int, int>& wynik1, const std::pair<int, int>& wynik2) {
    return std::abs(wynik1.first - wynik1.second) > std::abs(wynik2.first - wynik2.second);
}

int Wyniki:: zapiszNajlepszeWyniki() {
    std::ifstream inputFile("/Users/zuziagwiazda/CLionProjects/hexprojektfinal/wszystkieWyniki");
    std::vector<std::pair<int, int>> wyniki;

    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            if (line.find("punkty RED: ") != std::string::npos && line.find(", punkty BLUE: ") != std::string::npos) {
                size_t redPos = line.find("punkty RED: ") + 12;
                size_t bluePos = line.find(", punkty BLUE: ") + 15;
                int punktyR = std::stoi(line.substr(redPos));
                int punktyB = std::stoi(line.substr(bluePos));

                wyniki.push_back(std::make_pair(punktyR, punktyB));
            }
        }

        inputFile.close();

        std::sort(wyniki.begin(), wyniki.end(), porownajWyniki);

        std::ofstream outputFile("/Users/zuziagwiazda/CLionProjects/hexprojektfinal/najlepszeWyniki");
        if (outputFile.is_open()) {
            int liczbaNajlepszych = std::min(5, static_cast<int>(wyniki.size()));
            for (int i = 0; i < liczbaNajlepszych; i++) {
                outputFile << "punkty RED: " << wyniki[i].first << ", punkty BLUE: " << wyniki[i].second << std::endl;
            }

            outputFile.close();
            std::cout << "Zapisano najlepsze wyniki do pliku." << std::endl;
        } else {
            std::cout << "Nie można otworzyć pliku najlepszeWyniki.txt." << std::endl;
        }
    } else {
        std::cout << "Nie można otworzyć pliku wszystkieWyniki.txt." << std::endl;
    }
    return 0;
}


