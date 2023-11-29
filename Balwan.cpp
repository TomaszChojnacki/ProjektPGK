#include "balwan.h"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

Balwan::Balwan(ALLEGRO_DISPLAY* display) /// Konstruktor klasy Balwan inicjalizacja zmiennych
    : display(display), isVisible(false), x(al_get_display_width(display) / 2), y(al_get_display_height(display) / 2),
    balwan_left(nullptr), balwan_right(nullptr), balwan_up(nullptr), balwan_down(nullptr), currentBalwan(nullptr) {
    balwan_left = al_load_bitmap("balwan2.png"); /// Dodanie bitmapy
    balwan_right = al_load_bitmap("balwan1.png"); /// Dodanie bitmapy
    balwan_up = al_load_bitmap("balwan3.png"); /// Dodanie bitmapy
    balwan_down = al_load_bitmap("balwan4.png"); /// Dodanie bitmapy

    width = al_get_display_width(display); /// Przypisanie szerowkosci
    height = al_get_display_height(display); /// Przypisanie wysokosci

    currentBalwan = balwan_right; /// Ustawienie pozycji startowej wyswietlania na obrudony w prawo

}

Balwan::~Balwan() /// Destruktor klasy Balwan zwalnianie zaalokowanej pamieci
{
    al_destroy_bitmap(balwan_left);
    al_destroy_bitmap(balwan_right);
    al_destroy_bitmap(balwan_up);
    al_destroy_bitmap(balwan_down);
}

void Balwan::draw(void) /// Funkcja rysujaca obiekt Balwan na ekranie 
{
    if (isVisible) {
        al_draw_bitmap(currentBalwan, x - al_get_bitmap_width(currentBalwan) / 2, y - al_get_bitmap_height(currentBalwan) / 2, 0);
    }
}

void Balwan::toggleVisibility(void) /// Funkcja przelaczajaca widok obiektu Balwan
{
    isVisible = !isVisible;
}

/// Funkcja zmieniajaca kierunek obiektu Balwan na podstawie podanych kierunkow
void Balwan::changeDirection(int horizontalDirection, int verticalDirection) {
    if (horizontalDirection == 1) {
        currentBalwan = balwan_right;       /// Ustawienie obrazka dla ruchu w prawo
    }
    else if (horizontalDirection == -1) {
        currentBalwan = balwan_left;        /// Ustawienie obrazka dla ruchu w lewo
    }

    if (verticalDirection == 1) {
        currentBalwan = balwan_down;        /// Ustawienie obrazka dla ruchu w dol
    }
    else if (verticalDirection == -1) {
        currentBalwan = balwan_up;          /// Ustawienie obrazka dla ruchu w gore
    }
}

/// Funkcja obslugujaca ruch Balwana zgodnie z wcisnietym klawiszem
void Balwan::move(void) {
    ALLEGRO_KEYBOARD_STATE keyState;
    al_get_keyboard_state(&keyState);

    int direction = 0;
    int verticalDirection = 0;

    if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) {
        x += 5;
        direction = 1;
    }
    else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) {
        x -= 5;
        direction = -1;
    }

    if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)) {
        y += 5;
        verticalDirection = 1;
    }
    if (al_key_down(&keyState, ALLEGRO_KEY_UP)) {
        y -= 5;
        verticalDirection = -1;
    }

    /// Sprawdzenie granic ekranu i dostosowanie pozycji obiektu Balwan
    if (x > (width - al_get_bitmap_width(currentBalwan)))
        x = (width - al_get_bitmap_width(currentBalwan));

    if (x < 0)
        x = 0;

    if (y > (height - al_get_bitmap_height(currentBalwan)))
        y = (height - al_get_bitmap_height(currentBalwan));

    if (y < 0)
        y = 0;

    
}

