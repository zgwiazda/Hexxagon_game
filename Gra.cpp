
#include <SFML/Graphics.hpp>
#include <cmath>
#include <fstream>
#include "Hex.h"
#include "DostepnePola.h"
#include "Gra.h"


Gra::Gra() :  graczR("Red"), graczB("Blue"), punktyR(3),punktyB(3) {}

int Gra::ruchRED(sf::RenderWindow& window,
            std::vector<Hex>& wszystkiePola,

            int &firstClick,std::vector<DostepnePola>& wszystkieDostepnePolaRED,
            int &zmianaRuchu){
        sf::Event event;
        bool zrobRuch = false;
        sf::Vector2i previousPosition;
        sf::Vector2i currentPosition;

        while (window.isOpen()) {
            if(koniecGry){
                return 0;
            }
            while (window.pollEvent(event)) {

                if(firstClick <= 0){

                    if (event.type == sf::Event::MouseButtonPressed) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            currentPosition = sf::Mouse::getPosition(window);
                            previousPosition =currentPosition;
                            firstClick =2;
                        }}
                }

                else {
                    if (event.type == sf::Event::MouseButtonPressed){
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            previousPosition = currentPosition;
                            currentPosition = sf::Mouse::getPosition(window);
                            zrobRuch= true;
                        }
                    }

                }


                //PODSWIETLANIE DOSTEPNYCH POL
                for (Hex &szescian: wszystkiePola) {
                    sf::Vector2f circlePos = szescian.pole.getPosition();
                    float circleRadius = szescian.pole.getRadius();
                    // Sprawdzenie, czy kliknięcie znajduje się w obrębie CircleShape
                    if (currentPosition.x >= circlePos.x && currentPosition.x <= circlePos.x + 2 * circleRadius &&
                        currentPosition.y >= circlePos.y && currentPosition.y <= circlePos.y + 2 * circleRadius&&
                        std::pow(currentPosition.x - circlePos.x - circleRadius, 2) +
                        std::pow(currentPosition.y - circlePos.y - circleRadius, 2) <= std::pow(circleRadius, 2)) {

                        for (Hex &s: wszystkiePola) {
                            s.zmienOutline(sf::Color::Black);
                        }
                        //jesli sie znajduje
                        //znajdz dostepne ruchy, zapisz je jako nowy obiekt DostepnePola
                        //zmien ouline'y dostepnych pol na odpowiedni kolor
                        if (szescian.pole.getFillColor() == sf::Color::Red) {
                            DostepnePola dostepnePola (szescian.numer);
                            szescian.zmienOutline(sf::Color::Yellow);
                            for (Hex &pole: wszystkiePola) {
                                for (int sasiad: szescian.sasiedzi) {
                                    if (pole.numer == sasiad && pole.pole.getFillColor() == sf::Color::White) {
                                        bool czyJest = false;
                                        for (int g: dostepnePola.pola_green) {
                                            if (g == pole.numer) {
                                                czyJest = true;
                                            }
                                        }
                                        if (!czyJest) {
                                            dostepnePola.pola_green.push_back(pole.numer);
                                        }
                                        for (Hex &pole2: wszystkiePola) {
                                            for (int sasiad2: pole.sasiedzi) {
                                                bool czyJest2 = false;
                                                if (pole2.numer == sasiad2 &&
                                                    pole2.pole.getFillColor() == sf::Color::White &&
                                                    sasiad2 != szescian.numer) {

                                                    for (int y: dostepnePola.pola_yellow) {
                                                        if (y == pole2.numer) {
                                                            czyJest2 = true;
                                                        }

                                                    }
                                                    for (int g: dostepnePola.pola_green) {
                                                        if (g == sasiad2) {
                                                            czyJest2 = true;
                                                        }
                                                    }
                                                    if (!czyJest2) {
                                                        dostepnePola.pola_yellow.push_back(pole2.numer);
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            for (int i = 0; i < dostepnePola.pola_yellow.size(); i++) {
                                int y = dostepnePola.pola_yellow[i];
                                for (int g: dostepnePola.pola_green) {
                                    if (y == g) {
                                        dostepnePola.pola_yellow[i] = -1;
                                    }
                                }
                            }

                            //zmien kolory outline
                            for (Hex &pole: wszystkiePola) {

                                for (int y: dostepnePola.pola_yellow) {
                                    if (pole.numer == y) {
                                        pole.zmienOutline(sf::Color::Yellow);
                                    }
                                }
                                for (int g: dostepnePola.pola_green) {
                                    if (pole.numer == g) {
                                        pole.zmienOutline(sf::Color::Green);
                                    }
                                }

                            }
                            zrobRuch = true;
                            firstClick++;
                            wszystkieDostepnePolaRED.push_back(dostepnePola);
                        }
                    }}

                //RUCH
                if (previousPosition != currentPosition) {
                    if (zrobRuch) {
                        DostepnePola dostepnePola = wszystkieDostepnePolaRED.back();

                        for (Hex &wybrane: wszystkiePola) {
                            sf::Vector2f circlePos = wybrane.pole.getPosition();
                            float circleRadius = wybrane.pole.getRadius();
                            if (currentPosition.x >= circlePos.x && currentPosition.x <= circlePos.x + 2 * circleRadius &&
                                currentPosition.y >= circlePos.y && currentPosition.y <= circlePos.y + 2 * circleRadius&&
                                std::pow(currentPosition.x - circlePos.x - circleRadius, 2) +
                                std::pow(currentPosition.y - circlePos.y - circleRadius, 2) <= std::pow(circleRadius, 2)) {
                                if(wybrane.pole.getFillColor() != sf::Color::Blue){
                                    sf::Color kolor = sf::Color::Red;

                                    //sprawdzam czy zielony
                                    for (int nrG: dostepnePola.pola_green) {
                                        if (wybrane.numer == nrG) {
                                            wybrane.zmienKolor(kolor);
                                            punktyR++;
                                            zmianaRuchu= 1;

                                            //FARBOWANIE SĄSIADUJACYCH PÓL PRZECIWNIKA
                                            for(Hex &przeciwnik : wszystkiePola){
                                                for(int nrSasiadaWybranego : wybrane.sasiedzi){
                                                    if(przeciwnik.numer == nrSasiadaWybranego
                                                       && przeciwnik.pole.getFillColor() != sf::Color::White
                                                       && przeciwnik.pole.getFillColor() != kolor){
                                                        przeciwnik.zmienKolor(kolor);
                                                        punktyR++;
                                                        punktyB--;
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    //sprawdzam czy zolty
                                    for (int nrY: dostepnePola.pola_yellow) {
                                        if (wybrane.numer == nrY) {
                                            wybrane.zmienKolor(kolor);
                                            for (Hex &szescian: wszystkiePola) {
                                                if (szescian.numer == dostepnePola.nr_pole_wyjsciowe) {
                                                    szescian.zmienKolor(sf::Color::White);
                                                    zmianaRuchu= 1;

                                                }
                                            }

                                            //FARBOWANIE SĄSIADUJACYCH PÓL PRZECIWNIKA
                                            for(Hex &przeciwnik : wszystkiePola){
                                                for(int nrSasiadaWybranego : wybrane.sasiedzi){
                                                    if(przeciwnik.numer == nrSasiadaWybranego
                                                       && przeciwnik.pole.getFillColor() != sf::Color::White
                                                       && przeciwnik.pole.getFillColor() != kolor){
                                                        przeciwnik.zmienKolor(kolor);
                                                        punktyR++;
                                                        punktyB--;

                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                window.display();
                return 0;
            }
            return 0;
        }
};



int Gra::ruchBLUE(sf::RenderWindow& window,
             std::vector<Hex>& wszystkiePola,

             int &firstClick,std::vector<DostepnePola>& wszystkieDostepnePolaBLUE,
             int &zmianaRuchu){

    sf::Event event;
    bool zrobRuch = false;
    sf::Vector2i previousPosition;
    sf::Vector2i currentPosition;

    while (window.isOpen()) {
        if(koniecGry){
            return 0;
        }
        while (window.pollEvent(event)) {

            if(firstClick <= 0){
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        currentPosition = sf::Mouse::getPosition(window);
                        previousPosition =currentPosition;
                        firstClick =2;
                    }}
            }

            else {
                if (event.type == sf::Event::MouseButtonPressed){
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        previousPosition = currentPosition;
                        currentPosition = sf::Mouse::getPosition(window);
                        zrobRuch = true;
                    }
                }

            }


            //PODSWIETLANIE DOSTEPNYCH POL
            for (Hex &szescian: wszystkiePola) {
                sf::Vector2f circlePos = szescian.pole.getPosition();
                float circleRadius = szescian.pole.getRadius();
                // Sprawdzenie, czy kliknięcie znajduje się w obrębie CircleShape
                if (currentPosition.x >= circlePos.x && currentPosition.x <= circlePos.x + 2 * circleRadius &&
                    currentPosition.y >= circlePos.y && currentPosition.y <= circlePos.y + 2 * circleRadius&&
                    std::pow(currentPosition.x - circlePos.x - circleRadius, 2) +
                    std::pow(currentPosition.y - circlePos.y - circleRadius, 2) <= std::pow(circleRadius, 2)) {
                    for (Hex &s: wszystkiePola) {
                        s.zmienOutline(sf::Color::Black);
                    }

                    //jesli sie znajduje
                    //znajdz dostepne ruchy, zapisz je jako nowy obiekt DostepnePola
                    //zmien ouline'y dostepnych pol na odpowiedni kolor
                    if (szescian.pole.getFillColor() == sf::Color::Blue){
                        szescian.zmienOutline(sf::Color::Yellow);
                        DostepnePola dostepnePola (szescian.numer);
                        for (Hex &pole: wszystkiePola) {
                            for (int sasiad: szescian.sasiedzi) {
                                if (pole.numer == sasiad && pole.pole.getFillColor() == sf::Color::White) {
                                    bool czyJest = false;
                                    for (int g: dostepnePola.pola_green) {
                                        if (g == pole.numer) {
                                            czyJest = true;
                                        }
                                    }
                                    if (!czyJest) {
                                        dostepnePola.pola_green.push_back(pole.numer);
                                    }
                                    for (Hex &pole2: wszystkiePola) {
                                        for (int sasiad2: pole.sasiedzi) {
                                            bool czyJest2 = false;
                                            if (pole2.numer == sasiad2 &&
                                                pole2.pole.getFillColor() == sf::Color::White &&
                                                sasiad2 != szescian.numer) {

                                                for (int y: dostepnePola.pola_yellow) {
                                                    if (y == pole2.numer) {
                                                        czyJest2 = true;
                                                    }

                                                }
                                                for (int g: dostepnePola.pola_green) {
                                                    if (g == sasiad2) {
                                                        czyJest2 = true;
                                                    }
                                                }
                                                if (!czyJest2) {
                                                    dostepnePola.pola_yellow.push_back(pole2.numer);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        for (int i = 0; i < dostepnePola.pola_yellow.size(); i++) {
                            int y = dostepnePola.pola_yellow[i];
                            for (int g: dostepnePola.pola_green) {
                                if (y == g) {
                                    dostepnePola.pola_yellow[i] = -1;
                                }
                            }
                        }

                        //zmien kolory outline
                        for (Hex &pole: wszystkiePola) {

                            for (int y: dostepnePola.pola_yellow) {
                                if (pole.numer == y) {
                                    pole.zmienOutline(sf::Color::Yellow);
                                }
                            }
                            for (int g: dostepnePola.pola_green) {
                                if (pole.numer == g) {
                                    pole.zmienOutline(sf::Color::Green);
                                }
                            }
                        }
                        zrobRuch = true;
                        firstClick++;
                        wszystkieDostepnePolaBLUE.push_back(dostepnePola);
                    }
                }}

            //RUCH
            if (previousPosition != currentPosition) {
                if (zrobRuch) {
                    DostepnePola dostepnePola = wszystkieDostepnePolaBLUE.back();
                    bool doZmianyRuchu=false;
                    for (Hex &wybrane: wszystkiePola) {
                        sf::Vector2f circlePos = wybrane.pole.getPosition();
                        float circleRadius = wybrane.pole.getRadius();
                        if (currentPosition.x >= circlePos.x && currentPosition.x <= circlePos.x + 2 * circleRadius &&
                            currentPosition.y >= circlePos.y && currentPosition.y <= circlePos.y + 2 * circleRadius&&
                            std::pow(currentPosition.x - circlePos.x - circleRadius, 2) +
                            std::pow(currentPosition.y - circlePos.y - circleRadius, 2) <= std::pow(circleRadius, 2)) {
                            if(wybrane.pole.getFillColor() != sf::Color::Red){
                                sf::Color kolor = sf::Color::Blue;
                                //sprawdzam czy zielony
                                 for (int nrG: dostepnePola.pola_green) {
                                     if (wybrane.numer == nrG) {
                                         wybrane.zmienKolor(kolor);
                                         punktyB++;
                                         zmianaRuchu= 0;

                                         //FARBOWANIE SĄSIADUJACYCH PÓL PRZECIWNIKA
                                         for(Hex &przeciwnik : wszystkiePola){
                                             for(int nrSasiadaWybranego : wybrane.sasiedzi){
                                                 if(przeciwnik.numer == nrSasiadaWybranego
                                                    && przeciwnik.pole.getFillColor() != sf::Color::White
                                                    && przeciwnik.pole.getFillColor() != kolor){
                                                     przeciwnik.zmienKolor(kolor);
                                                     punktyB++;
                                                     punktyR--;
                                                 }
                                             }
                                         }
                                     }
                                 }

                                 //sprawdzam czy zolty
                                 for (int nrY: dostepnePola.pola_yellow) {
                                     if (wybrane.numer == nrY) {

                                         wybrane.zmienKolor(kolor);
                                         for (Hex &szescian: wszystkiePola) {
                                             if (szescian.numer == dostepnePola.nr_pole_wyjsciowe) {
                                                 szescian.zmienKolor(sf::Color::White);
                                                 zmianaRuchu = 0;
                                             }
                                         }

                                         //FARBOWANIE SĄSIADUJACYCH PÓL PRZECIWNIKA
                                         for (Hex &przeciwnik: wszystkiePola) {
                                             for (int nrSasiadaWybranego: wybrane.sasiedzi) {
                                                 if (przeciwnik.numer == nrSasiadaWybranego
                                                     && przeciwnik.pole.getFillColor() != sf::Color::White
                                                     && przeciwnik.pole.getFillColor() != kolor) {
                                                     przeciwnik.zmienKolor(kolor);
                                                     punktyB++;
                                                     punktyR--;
                                                 }
                                             }
                                         }
                                     }
                                 }
                             }
                        }
                    }
                }
            }
            window.display();
            return 0;
        }
        return 0;
    }
};

int Gra::sprawdzStanGry(std::vector<Hex> &wszystkiePola, sf::RenderWindow& window){
    std::vector<int> wolnePola;
    std::vector<int> polaRed;
    std::vector<int> polaBlue;
    int wolneB= 0;
    int wolneR= 0;

    //liczenie pol bialych
    for(Hex pole: wszystkiePola){
        if(pole.pole.getFillColor()==sf::Color::White){
            wolnePola.push_back(pole.numer);
        }
    }

    //liczenie pol czerwonych i niebieskich
    for(Hex pole: wszystkiePola){
        if(pole.pole.getFillColor()==sf::Color::Red){
            polaRed.push_back(pole.numer);
        }
    }

    for(Hex pole: wszystkiePola){
        if(pole.pole.getFillColor()==sf::Color::Blue){
            polaBlue.push_back(pole.numer);
        }
    }

    for(Hex hex: wszystkiePola){
            for(int nrRed: polaRed){
                if(hex.numer == nrRed){
                    for(int sasiad : hex.sasiedzi){
                        for(int sprawdz: wolnePola){
                            if(sasiad==sprawdz){
                                wolneR++;
                            }
                        }
                    }
                }
            }
            for(int nrBlue: polaBlue){
                if(hex.numer == nrBlue){
                    for(int sasiad : hex.sasiedzi){
                        for(int sprawdz: wolnePola){
                            if(sasiad==sprawdz){
                                wolneB++;
                            }
                        }
                    }
                }
            }
    }
    if(wolneR==0 || wolneB== 0){
        koniecGry=true;
    }
    return 0;
};


int Gra::zapiszStanGry(std::vector<Hex> &wszystkiePola){
    std::ofstream outputFile("/Users/zuziagwiazda/CLionProjects/hexprojektfinal/stanOstatniejGry");

    if (outputFile.is_open()) {
        outputFile << "pola RED:" << std::endl;
        for(Hex pole: wszystkiePola){
            if(pole.pole.getFillColor() == sf::Color::Red){
                outputFile << pole.numer << std::endl;
            }
        }
        outputFile << "pola BLUE:" << std::endl;
        for(Hex pole: wszystkiePola){
            if(pole.pole.getFillColor() == sf::Color::Blue){
                outputFile << pole.numer << std::endl;
            }
        }

        outputFile.close();
    } else {
        std::cout << "Nie można otworzyć pliku." << std::endl;
    }
    return 0;
};
