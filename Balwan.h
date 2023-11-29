#pragma once
#include <allegro5/allegro.h>

class Balwan {
public:
    Balwan(ALLEGRO_DISPLAY* display);       /// Konstruktor klasy Balwan inicjalizuje obiekt przyjmujac wskaznik do obiektu ALLEGRO_DISPLAY
    ~Balwan();                              /// Destruktor klasy Balwan zwalnia zaalokowana pamiec dla obrazkow balwana
    
    void draw(void);                        /// Metoda do rysowania obecnego obrazka balwana na ekranie
    void toggleVisibility(void);            /// Metoda do przelaczania widocznoœci balwana (ukrywanie/odkrywanie)

    /// Metoda do zmiany kierunku obrazu balwana na podstawie wartosci kierunkow 
    void changeDirection(int horizontalDirection, int verticalDirection);
    
    void move(void); /// Metoda do przemieszczania balwana

private:
    ALLEGRO_DISPLAY* display;               /// Wskaznik do obiektu ALLEGRO_DISPLAY
    ALLEGRO_BITMAP* balwan_left;            /// Obrazek balwana skierowanego w lewo
    ALLEGRO_BITMAP* balwan_right;           /// Obrazek balwana skierowanego w prawo
    ALLEGRO_BITMAP* balwan_up;              /// Obrazek balwana skierowanego w gore
    ALLEGRO_BITMAP* balwan_down;            /// Obrazek balwana skierowanego w dol
    ALLEGRO_BITMAP* currentBalwan;          /// Aktualny obrazek balwana
    bool isVisible;                         /// Zmienna okreslajaca widocznosc balwana
    float x, y;                             /// Wspolrzedne polozenia balwana
    int width, height;                      /// Szerokosc i wysokosc balwana
};

