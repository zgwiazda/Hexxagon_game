

#include "Hex.h"

Hex::Hex (sf::CircleShape pole,int numer) :
pole (pole), numer(numer) {};


int Hex::zmienKolor(sf::Color c) {
   pole.setFillColor(c);
}

int Hex::zmienOutline(sf::Color c) {
 pole.setOutlineColor(c);
}