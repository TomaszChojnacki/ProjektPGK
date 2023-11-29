#include "Prymitywy.h"
#include <allegro5/allegro_primitives.h>

/// Funkcja rysujaca prostokat na ekranie o zadanych wspolrzednych i kolorze
void Prymitywy::drawRectangle(ALLEGRO_DISPLAY* display, int x1, int y1, int x2, int y2) {
    al_draw_rectangle(x1, y1, x2, y2, al_map_rgb(0, 255, 0), 2);
}

/// Funkcja rysujaca wypelniony okr¹g na ekranie o zadanych wspolrzednych i kolorze
void Prymitywy::drawCircle(ALLEGRO_DISPLAY* display, int x1, int y1, int x2, int y2) {
    int radius = abs(x2 - x1) / 2;
    int centerX = (x1 + x2) / 2;
    int centerY = (y1 + y2) / 2;

    al_draw_filled_circle(centerX, centerY, radius, al_map_rgb(0, 0, 255));
}

/// Funkcja rysujaca wypelniony trojkat na ekranie o zadanych wspolrzednych i kolorze
void Prymitywy::drawTriangle(ALLEGRO_DISPLAY* display, int x1, int y1, int x2, int y2) {
    int x3 = x1 + (x2 - x1) / 2;
    int y3 = y1 - (y2 - y1);

    al_draw_filled_triangle(x1, y1, x2, y2, x3, y3, al_map_rgb(0, 255, 255));
}