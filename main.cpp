/**
 * Tutaj metoda main oraz metoda graj
 * (w plikach tekstowych zawarte są przykładowe wyniki)
 */
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <unistd.h>
#include "Hex.h"
#include "DostepnePola.h"
#include "Gra.h"
#include "Wyniki.h"




/**
 * Metoda rozgrywająca pojedynczą rozgrywkę
 * Zawiera ładowanie ekranu z planszą, rozstawienie pionków oraz przypisanie do każdego pola odpowiednich numerów pól sąsiadujących
 * @param tryb parametr określający tryb gry, gdy gra się kończy zostaje zmieniony na wyjściowe 0 aby wrócić do ekranu startowego
 * @return
 */
int graj(int &tryb){

    sf::RenderWindow window(sf::VideoMode(1800, 1400), "Hexxagon");
    Gra gra;


    static std::vector<Hex> szesciany;
    int numColumns = 9;
    float hexX = 354;
    float hexY = 310;
    int count = 8;
    int numer = 0;

    if(tryb == 4){
        std::vector<int> polaRED;
        std::vector<int> polaBLUE;
        std::ifstream inputFile("//Users/zuziagwiazda/CLionProjects/hexprojektfinal/stanOstatniejGry");
        std::string line;
        std::string section;

        if (inputFile.is_open()) {
            std::string line;
            while (std::getline(inputFile, line)) {
                if (line == "pola RED:") {
                    section = "RED";
                } else if (line == "pola BLUE:") {
                    section = "BLUE";
                } else {
                    bool isValid = true;
                    for (char c : line) {
                        if (!std::isdigit(c)) {
                            isValid = false;
                            break;
                        }
                    }
                    if (isValid) {
                        int number = std::stoi(line);
                        if (section == "RED") {
                            polaRED.push_back(number);
                        } else if (section == "BLUE") {
                            polaBLUE.push_back(number);
                        }
                    }
                }
            }

            inputFile.close();
        } else {
            std::cout << "Nie można otworzyć pliku." << std::endl;
        }
        gra.punktyR = polaRED.size();
        gra.punktyB = polaBLUE.size();

        for (int kolumna = 0; kolumna < numColumns; kolumna++) {
            if (kolumna != 0) {
                hexX = hexX + (130);
                if (kolumna < 5)
                    hexY = hexY - (45 * sqrt(3));
            }

            if (kolumna < 5) {
                for (int i = 0; i < kolumna + 5; i++) {
                    sf::CircleShape szescian(70, 6);
                    szescian.setPosition(hexX, hexY + (i * 150));
                    if (numer == 22 || numer == 29 || numer == 39) {
                        szescian.setFillColor(sf::Color::Black);
                    } else {
                        szescian.setFillColor(sf::Color::White);
                    }
                    szescian.setOutlineColor(sf::Color::Black);
                    szescian.setOutlineThickness(10);
                    szescian.rotate(30);
                    Hex nowySzescian(szescian, numer);
                    szesciany.push_back(nowySzescian);
                    numer++;
                }
            } else {
                hexY = hexY + (45 * sqrt(3));
                for (int i = 0; i < count; i++) {
                    sf::CircleShape szescian(70, 6);
                    szescian.setPosition(hexX, hexY + (i * 150));
                    if (numer == 22 || numer == 29 || numer == 39) {
                        szescian.setFillColor(sf::Color::Black);
                    } else {
                        szescian.setFillColor(sf::Color::White);
                    }
                    szescian.setOutlineColor(sf::Color::Black);
                    szescian.setOutlineThickness(10);
                    szescian.rotate(30);
                    Hex nowySzescian(szescian,numer);
                    szesciany.push_back(nowySzescian);
                    numer++;
                }
                count--;
            }
        }

        for(Hex &pole: szesciany){
            for(int nrRED: polaRED){
                if(pole.numer == nrRED){
                    pole.zmienKolor(sf::Color::Red);
                }
            }
            for(int nrBLUE: polaBLUE){
                if(pole.numer == nrBLUE){
                    pole.zmienKolor(sf::Color::Blue);
                }
            }
        }
    }
    //tworzenie i ustawianie parametrow szescianow

else{
        for (int kolumna = 0; kolumna < numColumns; kolumna++) {
            if (kolumna != 0) {
                hexX = hexX + (130);
                if (kolumna < 5)
                    hexY = hexY - (45 * sqrt(3));
            }

            if (kolumna < 5) {
                for (int i = 0; i < kolumna + 5; i++) {
                    sf::CircleShape szescian(70, 6);
                    szescian.setPosition(hexX, hexY + (i * 150));
                    if (numer == 0 || numer == 34 || numer == 56) {
                        szescian.setFillColor(sf::Color::Red);

                    } else if (numer == 4 || numer == 26 || numer == 60) {
                        szescian.setFillColor(sf::Color::Blue);
                    } else if (numer == 22 || numer == 29 || numer == 39) {
                        szescian.setFillColor(sf::Color::Black);
                    } else {
                        szescian.setFillColor(sf::Color::White);
                    }

                    szescian.setOutlineColor(sf::Color::Black);
                    szescian.setOutlineThickness(10);
                    szescian.rotate(30);
                    Hex nowySzescian(szescian, numer);
                    szesciany.push_back(nowySzescian);
                    numer++;
                }
            } else {
                hexY = hexY + (45 * sqrt(3));
                for (int i = 0; i < count; i++) {
                    sf::CircleShape szescian(70, 6);
                    szescian.setPosition(hexX, hexY + (i * 150));
                    if (numer == 0 || numer == 34 || numer == 56) {
                        szescian.setFillColor(sf::Color::Red);

                    } else if (numer == 4 || numer == 26 || numer == 60) {
                        szescian.setFillColor(sf::Color::Blue);
                    } else if (numer == 22 || numer == 29 || numer == 39) {
                        szescian.setFillColor(sf::Color::Black);
                    } else {
                        szescian.setFillColor(sf::Color::White);
                    }
                    szescian.setOutlineColor(sf::Color::Black);
                    szescian.setOutlineThickness(10);
                    szescian.rotate(30);
                    Hex nowySzescian(szescian,numer);
                    szesciany.push_back(nowySzescian);
                    numer++;
                }
                count--;
            }
        }
}


    //zapisuje recznie sasiadujace pola dla kazdego szescianu
    for (Hex &szescian: szesciany) {
        switch (szescian.numer) {
            case 0:
                szescian.sasiedzi = {5, 6, 1};
                break;
            case 1:
                szescian.sasiedzi = {0, 6, 7, 2};
                break;
            case 2:
                szescian.sasiedzi = {1, 7, 8, 3};
                break;
            case 3:
                szescian.sasiedzi = {2, 8, 9, 4};
                break;
            case 4:
                szescian.sasiedzi = {3, 9, 10};
                break;
            case 5:
                szescian.sasiedzi = {0, 6, 12, 11};
                break;
            case 6:
                szescian.sasiedzi = {5, 0, 1, 7, 13, 12};
                break;
            case 7:
                szescian.sasiedzi = {1, 2, 8, 14, 13, 6};
                break;
            case 8:
                szescian.sasiedzi = {2, 3, 9, 15, 14, 7};
                break;
            case 9:
                szescian.sasiedzi = {3, 4, 10, 16, 15, 8};
                break;
            case 10:
                szescian.sasiedzi = {4, 9, 16, 17};
                break;
            case 11:
                szescian.sasiedzi = {5, 12, 19, 18};
                break;
            case 12:
                szescian.sasiedzi = {11, 5, 6, 13, 20, 19};
                break;
            case 13:
                szescian.sasiedzi = {12, 6, 7, 14, 21, 20};
                break;
            case 14:
                szescian.sasiedzi = {13, 7, 8, 15, 21};
                break;
            case 15:
                szescian.sasiedzi = {14, 8, 9, 16, 23};
                break;
            case 16:
                szescian.sasiedzi = {15, 9, 10, 17, 24, 23};
                break;
            case 17:
                szescian.sasiedzi = {10, 16, 24, 25};
                break;
            case 18:
                szescian.sasiedzi = {11, 19, 27, 26};
                break;
            case 19:
                szescian.sasiedzi = {18, 11, 12, 20, 28, 27};
                break;
            case 20:
                szescian.sasiedzi = {19, 12, 13, 21, 28};
                break;
            case 21:
                szescian.sasiedzi = {20, 13, 14, 30};
                break;
            case 22:
                //puste pole
                break;
            case 23:
                szescian.sasiedzi = {15, 16, 24, 32, 31};
                break;
            case 24:
                szescian.sasiedzi = {23, 16, 17, 25, 33, 32};
                break;
            case 25:
                szescian.sasiedzi = {17, 24, 33, 34};
                break;
            case 26:
                szescian.sasiedzi = {18, 27, 35};
                break;
            case 27:
                szescian.sasiedzi = {26, 18, 19, 28, 36, 35};
                break;
            case 28:
                szescian.sasiedzi = {27, 19, 20, 37, 36};
                break;
            case 29:
                //puste pole
                break;
            case 30:
                szescian.sasiedzi = {21, 31, 38};
                break;
            case 31:
                szescian.sasiedzi = {30, 23, 32, 40};
                break;
            case 32:
                szescian.sasiedzi = {31, 23, 24, 33, 41, 40};
                break;
            case 33:
                szescian.sasiedzi = {32, 24, 25, 34, 42, 41};
                break;
            case 34:
                szescian.sasiedzi = {25, 33, 42};
                break;
            case 35:
                szescian.sasiedzi = {26, 27, 36, 43};
                break;
            case 36:
                szescian.sasiedzi = {35, 27, 28, 37, 44, 43};
                break;
            case 37:
                szescian.sasiedzi = {36, 28, 38, 45, 44};
                break;
            case 38:
                szescian.sasiedzi = {37, 30, 46, 45};
                break;
            case 39:
                //puste pole
                break;
            case 40:
                szescian.sasiedzi = {31, 32, 41, 48, 47};
                break;
            case 41:
                szescian.sasiedzi = {40, 32, 33, 42, 49, 48};
                break;
            case 42:
                szescian.sasiedzi = {34, 33, 41, 49};
                break;
            case 43:
                szescian.sasiedzi = {35, 36, 44, 50};
                break;
            case 44:
                szescian.sasiedzi = {43, 36, 37, 45, 51, 50};
                break;
            case 45:
                szescian.sasiedzi = {44, 37, 38, 46, 52, 51};
                break;
            case 46:
                szescian.sasiedzi = {45, 38, 47, 53, 52};
                break;
            case 47:
                szescian.sasiedzi = {46, 40, 48, 54, 53};
                break;
            case 48:
                szescian.sasiedzi = {47, 40, 41, 49, 55, 54};
                break;
            case 49:
                szescian.sasiedzi = {42, 41, 48, 55};
                break;
            case 50:
                szescian.sasiedzi = {43, 44, 51, 56};
                break;
            case 51:
                szescian.sasiedzi = {50, 44, 45, 52, 57, 56};
                break;
            case 52:
                szescian.sasiedzi = {51, 45, 46, 53, 58, 57};
                break;
            case 53:
                szescian.sasiedzi = {52, 46, 47, 54, 59, 58};
                break;
            case 54:
                szescian.sasiedzi = {53, 47, 48, 55, 60, 59};
                break;
            case 55:
                szescian.sasiedzi = {49, 48, 54, 60};
                break;
            case 56:
                szescian.sasiedzi = {50, 51, 57};
                break;
            case 57:
                szescian.sasiedzi = {56, 51, 52, 58};
                break;
            case 58:
                szescian.sasiedzi = {57, 52, 53, 59};
                break;
            case 59:
                szescian.sasiedzi = {58, 53, 54, 60};
                break;
            case 60:
                szescian.sasiedzi = {59, 54, 55};
                break;
        }
    }
    int firstClick = 0;
    std::vector<DostepnePola> wszystkieDostepnePolaRED;
    std::vector<DostepnePola> wszystkieDostepnePolaBLUE;
    DostepnePola dostepnePolaRED(-1);
    DostepnePola dostepnePolaBLUE(-1);


    sf::Font font;
    font.loadFromFile("/Users/zuziagwiazda/Library/Fonts/Arial.ttf");


    sf::Font font2;
    font2.loadFromFile("/Users/zuziagwiazda/Library/Fonts/SPACE.ttf");


    sf::Text punkty_red;
    punkty_red.setString("Punkty czerwone: "+ std::to_string(gra.punktyR));
    punkty_red.setFont(font2);
    punkty_red.setPosition(55,55);
    punkty_red.setFillColor(sf::Color::White);
    punkty_red.setCharacterSize(30);


    sf::Text punkty_blue;
    punkty_blue.setString("Punkty niebieskie: " + std::to_string(gra.punktyB));
    punkty_blue.setFont(font2);
    punkty_blue.setPosition(55,100);
    punkty_blue.setFillColor(sf::Color::White);
    punkty_blue.setCharacterSize(30);


    sf::Text zapiszStanGry;
    zapiszStanGry.setString("Zapisz stan gry");
    zapiszStanGry.setFont(font2);
    zapiszStanGry.setPosition(55,1300);
    zapiszStanGry.setFillColor(sf::Color::White);
    zapiszStanGry.setOutlineColor(sf::Color::Red);
    zapiszStanGry.setOutlineThickness(5);
    zapiszStanGry.setCharacterSize(40);

    sf::CircleShape komunikatWygrana(500, 4);
    komunikatWygrana.setFillColor(sf::Color::Cyan);
    komunikatWygrana.setOutlineColor(sf::Color::Black);
    komunikatWygrana.setOutlineThickness(20);
    komunikatWygrana.setPosition((window.getSize().x - komunikatWygrana.getRadius() * 2) / 2,
                        (window.getSize().y - komunikatWygrana.getRadius() * 2) / 2);

    sf::Text wygrana;
    wygrana.setString("Wygrana!");
    wygrana.setFont(font2);
    wygrana.setFillColor(sf::Color::Magenta);
    wygrana.setOutlineColor(sf::Color::Black);
    wygrana.setCharacterSize(50);
    wygrana.setOutlineThickness(7);
    wygrana.setPosition( (1800 - wygrana.getLocalBounds().width) / 2,(1400 - wygrana.getLocalBounds().height) / 2);

    int zmianaRuchu = 0;

    while (window.isOpen()) {


        //DOPOKI PLANSZA WOLNA MOZNA GRAC
     if(gra.punktyR+gra.punktyB < 58 && gra.koniecGry != true){
         if(zmianaRuchu==0){
             //RUCH RED
           gra.sprawdzStanGry(szesciany,window);
             gra.ruchRED(window,szesciany,firstClick,wszystkieDostepnePolaRED,zmianaRuchu);

         }
         if(zmianaRuchu==1){
             //RUCH BLUE
          gra.sprawdzStanGry(szesciany,window);
             gra.ruchBLUE(window,szesciany,firstClick,wszystkieDostepnePolaBLUE,zmianaRuchu);

         }
     }
     sleep(0.2);

        punkty_red.setString("Punkty czerwone: "+ std::to_string(gra.punktyR));
        punkty_blue.setString("Punkty niebieskie: " + std::to_string(gra.punktyB));


        window.clear(sf::Color::Black);
        sf::CircleShape plansza(700, 6);
        plansza.setFillColor(sf::Color::White);
        plansza.setPosition((window.getSize().x - plansza.getRadius() * 2) / 2,
                            (window.getSize().y - plansza.getRadius() * 2) / 2);
        window.draw(plansza);
        window.draw(punkty_red);
        window.draw(punkty_blue);
        window.draw(zapiszStanGry);


        for (Hex& pole: szesciany) {
            window.draw(pole.pole);
        }

        sf::Event e;
        if (e.type == sf::Event::MouseButtonPressed){
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                if (e.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    sf::FloatRect textBounds = zapiszStanGry.getGlobalBounds();
                    if (textBounds.contains(mousePosition.x, mousePosition.y)){
                        zapiszStanGry.setFillColor(sf::Color::Blue);
                        gra.zapiszStanGry(szesciany);
                    }
                }

            }
        }

        while (window.pollEvent(e)){
            if(e.type==sf::Event::Closed){
                window.close();
            }
        }
//zapisz stan gry
        if (e.type == sf::Event::MouseMoved) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::FloatRect zapiszStan = zapiszStanGry.getGlobalBounds();

            if (zapiszStan.contains(mousePosition.x, mousePosition.y)) {
                zapiszStanGry.setCharacterSize(45);
            }
            else {
                zapiszStanGry.setCharacterSize(40);
            }
        }



        if(gra.koniecGry || gra.punktyR+gra.punktyB == 58){
            if(gra.punktyR > gra.punktyB){
                wygrana.setString("Wygrana RED!");
            }
            else if(gra.punktyB > gra.punktyR){
                wygrana.setString("Wygrana BLUE!");
            }

          //zapisuje gre do pliku ze wszystkimi wynikami
            Wyniki wynik(gra.punktyR,gra.punktyB);
            wynik.zapiszWynik();

            wygrana.setPosition( (1800 - wygrana.getLocalBounds().width) / 2,(1400 - wygrana.getLocalBounds().height) / 2);
            sleep(0.5);
            window.draw(komunikatWygrana);
            window.draw(wygrana);
            window.display();
            sleep(5);
            wszystkieDostepnePolaBLUE.clear();
            wszystkieDostepnePolaRED.clear();
            szesciany.clear();
            window.clear();
            tryb=0;
            return 0;
        }

        window.display();


    }
    return 0;
}

/**
 * Metoda main, ładuje ekran startowy, pozwala na wybór trybu gry,załadowania poprzedniego stanu gry lub wyświetlenie 5ciu najlepszych wyników
 * @return
 */
int main(){
    sf::RenderWindow window(sf::VideoMode(1800, 1400), "Ekran startowy");
    sf::Font font;
    font.loadFromFile("/Users/zuziagwiazda/Library/Fonts/SPACE.ttf");


    sf::Text nowaGra;
    nowaGra.setString("Nowa gra: ");
    nowaGra.setFont(font);
    nowaGra.setPosition(200,400);
    nowaGra.setFillColor(sf::Color::White);
    nowaGra.setOutlineColor(sf::Color::Red);
    nowaGra.setOutlineThickness(15);
    nowaGra.setCharacterSize(60);

    sf::Text playerVsPlayer;
    playerVsPlayer.setString("tryb player RED vs player BLUE");
    playerVsPlayer.setFont(font);
    playerVsPlayer.setPosition(250,550);
    playerVsPlayer.setFillColor(sf::Color::White);
    playerVsPlayer.setOutlineColor(sf::Color::Blue);
    playerVsPlayer.setOutlineThickness(15);
    playerVsPlayer.setCharacterSize(45);

    sf::Text komputerVsPlayer;
    komputerVsPlayer.setString("tryb player RED vs komputer BLUE");
    komputerVsPlayer.setFont(font);
    komputerVsPlayer.setPosition(250,700);
    komputerVsPlayer.setFillColor(sf::Color::White);
    komputerVsPlayer.setOutlineColor(sf::Color::Blue);
    komputerVsPlayer.setOutlineThickness(15);
    komputerVsPlayer.setCharacterSize(45);


    sf::Text wczytajOstatniaGre;
    wczytajOstatniaGre.setString("Wczytaj ostatnia gre");
    wczytajOstatniaGre.setFont(font);
    wczytajOstatniaGre.setPosition(250,900);
    wczytajOstatniaGre.setFillColor(sf::Color::White);
    wczytajOstatniaGre.setOutlineColor(sf::Color::Blue);
    wczytajOstatniaGre.setOutlineThickness(15);
    wczytajOstatniaGre.setCharacterSize(45);


    sf::Text najlepszeWyniki;
    najlepszeWyniki.setString("Wyswietl najlepsze wyniki");
    najlepszeWyniki.setFont(font);
    najlepszeWyniki.setPosition(350,1200);
    najlepszeWyniki.setFillColor(sf::Color::White);
    najlepszeWyniki.setOutlineColor(sf::Color::Red);
    najlepszeWyniki.setOutlineThickness(15);
    najlepszeWyniki.setCharacterSize(50);

    sf::Text wyswietloneNWyniki;
    wyswietloneNWyniki.setFont(font);
    wyswietloneNWyniki.setPosition(200,400);
    wyswietloneNWyniki.setCharacterSize(50);
    wyswietloneNWyniki.setFillColor(sf::Color::White);
    wyswietloneNWyniki.setOutlineColor(sf::Color::Blue);
    wyswietloneNWyniki.setOutlineThickness(10);
    wyswietloneNWyniki.setLineSpacing(1.5);

    sf::RectangleShape oknoWyniki;
    oknoWyniki.setPosition(200,400);
    oknoWyniki.setFillColor(sf::Color::White);
    oknoWyniki.setOutlineColor(sf::Color::Blue);
    oknoWyniki.setOutlineThickness(15);


    //numer przypisany oznacza wybrana czynnosc:
    //1- gra player vs player; 2- gra player vs komputer; 3- wyswietl najlepsze wyniki, 4- wczytaj ostatnia gre
    int wybrane=0;

    while (window.isOpen()) {

        sf::Event e;
        while (window.pollEvent(e)){
            if(e.type==sf::Event::Closed){
                window.close();
            }
        }

      //powiekszanie tekstów po najechaniu na nie myszka
      if (e.type == sf::Event::MouseMoved) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::FloatRect PvsP = playerVsPlayer.getGlobalBounds();
            sf::FloatRect PvsK = komputerVsPlayer.getGlobalBounds();
            sf::FloatRect wyniki = najlepszeWyniki.getGlobalBounds();
            sf::FloatRect ostatniaGra = wczytajOstatniaGre.getGlobalBounds();

            if (PvsP.contains(mousePosition.x, mousePosition.y)) {
               window.clear();
                playerVsPlayer.setCharacterSize(50);
            }
            else if (PvsK.contains(mousePosition.x, mousePosition.y)) {
                window.clear();
                komputerVsPlayer.setCharacterSize(50);
            }
           else if (wyniki.contains(mousePosition.x, mousePosition.y)) {
                window.clear();
                najlepszeWyniki.setCharacterSize(55);
            }
            else if (ostatniaGra.contains(mousePosition.x, mousePosition.y)) {
                window.clear();
                wczytajOstatniaGre.setCharacterSize(50);
            }
            else{
                window.clear();
                playerVsPlayer.setCharacterSize(45);
                komputerVsPlayer.setCharacterSize(45);
                najlepszeWyniki.setCharacterSize(50);
                wczytajOstatniaGre.setCharacterSize(45);

            }
        }


      //wybranie opcji player vs player
        if (e.type == sf::Event::MouseButtonPressed){
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                if (e.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    sf::FloatRect textBounds = playerVsPlayer.getGlobalBounds();
                    if (textBounds.contains(mousePosition.x, mousePosition.y)){

                        sleep(0.5);

                        wybrane=1;
                    }
                }

            }
        }


        //wybranie opcji wyswietl najlepsze wyniki
        if (e.type == sf::Event::MouseButtonPressed){
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                if (e.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    sf::FloatRect textBounds = najlepszeWyniki.getGlobalBounds();
                    if (textBounds.contains(mousePosition.x, mousePosition.y)){

                        wybrane=3;
                    }
                }

            }
        }

        //wybranie opcji wczytaj ostatnia gre
        if (e.type == sf::Event::MouseButtonPressed){
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                if (e.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    sf::FloatRect textBounds = wczytajOstatniaGre.getGlobalBounds();
                    if (textBounds.contains(mousePosition.x, mousePosition.y)){

                        std::ifstream inputFile2("/Users/zuziagwiazda/CLionProjects/hexprojektfinal/stanOstatniejGry");

                        if (inputFile2.peek() != std::ifstream::traits_type::eof()) {
                            wybrane=4;
                        } else {
                            std::cout << "Nie ma zapisanej poprzedniej rozgrywki\n";
                        }

                        inputFile2.close();
                    }
                }

            }
        }

        window.draw(nowaGra);
        window.draw(playerVsPlayer);
        window.draw(komputerVsPlayer);
        window.draw(wczytajOstatniaGre);
        window.draw(najlepszeWyniki);

        switch (wybrane) {
            case 4:
                graj(wybrane);
                break;
            case 1:
                graj(wybrane);
                break;
            case 2:
                break;
            case 3:
                Wyniki::zapiszNajlepszeWyniki();
                std::ifstream inputFile("/Users/zuziagwiazda/CLionProjects/hexprojektfinal/najlepszeWyniki");
                if (inputFile.is_open()) {
                    std::string line;
                    std::string content="Najlepsze 5 wynikow:\n";
                    while (std::getline(inputFile, line)) {
                        content += line + "\n";
                    }
                    wyswietloneNWyniki.setString(content);
                    inputFile.close();
                } else {
                    std::cout << "Nie można otworzyć pliku najlepszeWyniki.txt." << std::endl;
                    return 1;
                }
                window.clear();
                sf::FloatRect textBounds = wyswietloneNWyniki.getGlobalBounds();
                oknoWyniki.setSize(sf::Vector2f(textBounds.width + 50, textBounds.height + 50));

                window.draw(oknoWyniki);
                window.draw(wyswietloneNWyniki);
                window.display();
                sleep(5);
                wybrane=0;
                break;


        }
        window.display();
    }
    return 0;
}