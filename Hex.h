//
// Created by Zuzia Gwiazda on 30/05/2023.
//
/**
 * Klasa pojedyńczego obiektu sześcian
 */
#ifndef HEXPROJEKTFINAL_HEX_H
#define HEXPROJEKTFINAL_HEX_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>

class Hex {
public:
    int numer;
    sf::CircleShape pole;
    /**
     * Każdy sześcian ma swój wektor zawierający numery pól sąsiadujących
     */
    std::vector<int> sasiedzi;

    Hex(sf::CircleShape pole,int numer) ;

/**
 * Metoda zmieniająca kolor wypełnienia
 * @param c kolor, którym zostaje wypełniony sześcian
 * @return
 */
    int zmienKolor(sf::Color c);
    /**
     * Metoda zmieniająca kolor ouline'u
     * @param c kolor, na jaki zmieniany jest outline sześcianu
     * @return
     */

    int zmienOutline(sf::Color c);
};


#endif //HEXPROJEKTFINAL_HEX_H
