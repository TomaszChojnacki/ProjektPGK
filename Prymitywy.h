#pragma once
#include <allegro5/allegro_primitives.h>

class Prymitywy {
public:
    /// Funkcja rysuj¹ca prostokat 
    static void drawRectangle(ALLEGRO_DISPLAY* display, int x1, int y1, int x2, int y2);

    /// Funkcja rysujaca kolo 
    static void drawCircle(ALLEGRO_DISPLAY* display, int x1, int y1, int x2, int y2);

    /// Funkcja rysujaca trojkat
    static void drawTriangle(ALLEGRO_DISPLAY* display, int x1, int y1, int x2, int y2);
};
