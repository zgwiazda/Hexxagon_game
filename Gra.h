/**
 * Klasa jednej, aktualnej rozgrywki
 */
#ifndef HEXPROJEKTFINAL_GRA_H
#define HEXPROJEKTFINAL_GRA_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <unistd.h>
#include "Hex.h"
#include "DostepnePola.h"

class Gra {
public:


    std::string graczR;
    std::string graczB;

    int punktyR;
    int punktyB;
    /**
     * zmienna przechowująca wartość bool, mówiąca o stanie gry, a konkretniej o jej końcu
     */
    bool koniecGry=false;


    Gra();
/**
 *Metoda wykonywująca ruch czerwonym pionkiem- po nacisnieciu w wybrane pole, "podswietla" możliwe do ruchu pola na odpowiednie kolory
 * Po wybraniu pola do ruchu, zmienia jego kolor oraz "farbuje" sąsiadujące pola przeciwnika
 * @param window okno gry
 * @param wszystkiePola tablica zawierająca wszystkie pola planszy
 * @param firstClick parametr zapamietujacy, czy kliknięcie myszki jest pierwszym kliknięciem
 * @param wszystkieDostepnePola wektor zawierający wszystkie obiekty DostępnePola (pola dostępne do ruchu)
 * @param zmianaRuchu parametr określający zmiane ruchu z RED na BLUE
 * @return
 */
    int ruchRED(sf::RenderWindow& window,
             std::vector<Hex>& wszystkiePola,
             int &firstClick,std::vector<DostepnePola>& wszystkieDostepnePola,
             int &zmianaRuchu);

    /**
     * Metoda wykonywująca ruch niebieskim pionkiem- po nacisnieciu w wybrane pole, "podswietla" możliwe do ruchu pola na odpowiednie kolory
     * Po wybraniu pola do ruchu, zmienia jego kolor oraz "farbuje" sąsiadujące pola przeciwnika
     * @param window okno gry
     * @param wszystkiePola tablica zawierająca wszystkie pola planszy
     * @param firstClick  parametr zapamietujacy, czy kliknięcie myszki jest pierwszym kliknięciem
     * @param wszystkieDostepnePola wektor zawierający wszystkie obiekty DostępnePola (pola dostępne do ruchu)
     * @param zmianaRuchu parametr określający zmiane ruchu z BLUE na RED
     * @return
     */
    int ruchBLUE(sf::RenderWindow& window,
             std::vector<Hex>& wszystkiePola,
             int &firstClick,std::vector<DostepnePola>& wszystkieDostepnePola,
             int &zmianaRuchu);

    /**
     * Metoda, która na bieżąco sprawdza stan planszy- liczy ilość białych (wolnych) pól i sprawdza, czy gracze mają możliwość ruchu
     * Ustawia koniecGry na true, jeśli któryś z graczy nie ma już żadnej możliwości ruchu
     * @param wszystkiePola tablica zawierająca wszystkie pola planszy
     * @param window okno gry
     * @return
     */
    int sprawdzStanGry(std::vector<Hex> &wszystkiePola,sf::RenderWindow& window);


/**
 * Metoda zapisująca stan aktualnej gry do pliku, który później można odtworzyć
 * @param wszystkiePola tablica zawierająca wszystkie pola planszy
 * @return
 */
    int zapiszStanGry(std::vector<Hex> &wszystkiePola);
};


#endif //HEXPROJEKTFINAL_GRA_H
