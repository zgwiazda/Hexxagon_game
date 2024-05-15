
/**
 * Obiekt klasy przechowuje informacje o aktualnych dostępnych do ruchu polach dla wybranego przez użytkownika pola
 */
#ifndef HEXPROJEKTFINAL_DOSTEPNEPOLA_H
#define HEXPROJEKTFINAL_DOSTEPNEPOLA_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>

class DostepnePola {
public:

/**
 * Zapisuje w wektorze numery pól o kolorze zielonym
 */
    std::vector<int> pola_green;
    /**
 * Zapisuje w wektorze numery pól o kolorze żółtym
 */
    std::vector<int> pola_yellow;
    /**
 * Zapisuje w numer pola wyjściowego
 */
    int nr_pole_wyjsciowe;

    DostepnePola(int nr);

    virtual ~DostepnePola() {

    }
};


#endif //HEXPROJEKTFINAL_DOSTEPNEPOLA_H
