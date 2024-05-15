//
// Created by Zuzia Gwiazda on 01/06/2023.
//
/**
 * Klasa obsługująca zapis wyników oraz wybranie 5ciu najlepszych
 */
#ifndef HEXPROJEKTFINAL_WYNIKI_H
#define HEXPROJEKTFINAL_WYNIKI_H


class Wyniki {
public:
    /**
     * Zmienne z ilością punktów RED i BLUE danej rozgrywki
     */
    int punktyRED;
    int punktyBLUE;

    Wyniki(int punktyRed, int punktyBlue);
    /**
     * Metoda zapisująca wynik danej rozgrywki do pliku
     */

    int zapiszWynik();


   /**
    * Metoda do porównania dwóch wyników
    * (porównuje względem tego, w której rozgrywce była większa różnica między punktamiRED a punktamiBLUE)
    * @param wynik1
    * @param wynik2
    * @return zwraca, który wynik jest większy
    */

    static bool porownajWyniki(const std::pair<int, int>& wynik1, const std::pair<int, int>& wynik2);

    /**
     * Metoda po wybraniu 5ciu najlepszych wyników zapisuje je do pliku
     * @return
     */

    static int zapiszNajlepszeWyniki();
};


#endif //HEXPROJEKTFINAL_WYNIKI_H
