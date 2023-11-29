#ifndef MENU_H
#define MENU_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class Menu{
public:
    Menu(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font);/// Konstruktor Menu, przyjmuje wskazniki na obiekty display i font
    ~Menu(); /// Destruktor Menu, zwalnia zaalokowana pamiec

    void draw(); /// Metoda do rysowania menu na ekranie
    int handleInput(ALLEGRO_EVENT_QUEUE* eventQueue); /// Metoda do obslugi wejscia, zwraca wybrana akcje

private:
    ALLEGRO_DISPLAY* display;/// Wskaznik na obiekt display
    ALLEGRO_FONT* font; /// Wskaznik na obiekt font
    ALLEGRO_BITMAP* background; /// Wskaznik na obiekt bitmapy tla menu

    void drawText(const char* text, int x, int y);/// Prywatna metoda do rysowania tekstu na ekranie
};

#endif 
