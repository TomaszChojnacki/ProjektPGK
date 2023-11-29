#include "menu.h"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

Menu::Menu(ALLEGRO_DISPLAY* display, ALLEGRO_FONT* font) /// Konstruktor Menu, inicjalizuje obiekt menu przy uzyciu podanego display i font
    : display(display), font(font) {
    background = al_load_bitmap("tlo.png"); /// ustawienie tlo.png jako tlo menu
}

Menu::~Menu(void) /// Destruktor Menu, zwalnia zaalokowana pamiec dla obrazu tla
{
    al_destroy_bitmap(background); /// Zwalnianie pamieci obrazu tla
    
}

void Menu::draw(void) /// Metoda rysujaca menu na ekranie
{
    int screenWidth = al_get_display_width(display); /// zmienna do ktorej jest przypisana szerokosc ekranu
    int screenHeight = al_get_display_height(display); /// zmienna do ktorej jest przypisana przechowujaca wysokosc ekranu

    al_draw_bitmap(background, 0, 0, 0); /// Rysowanie obrazu tla
    drawText("Silnik", screenWidth / 2 - 35, screenHeight / 2 - 50); /// Wypisanie na ekranie tekstu Silnik
    drawText("Wyjscie", screenWidth / 2 - 50, screenHeight / 2 + 50); /// Wypisanie na ekranie tekstu Wyjscie
    al_flip_display(); /// Wyswietlenie na ekranie
}

void Menu::drawText(const char* text, int x, int y) /// metoda rysujaca tekst na ekranie w podanej pozycji (x, y)
{
    al_draw_text(font, al_map_rgb(255, 255, 255), x, y, 0, text);
}

int Menu::handleInput(ALLEGRO_EVENT_QUEUE* eventQueue) /// Metoda przechowujaca zdarzenia myszy w menu
{
    ALLEGRO_EVENT event;
    while (al_get_next_event(eventQueue, &event)) /// Przekierowanie zdarzen do kolejki
    {
        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            int screenWidth = al_get_display_width(display); /// zmienna do ktorej jest przypisana szerokosc ekranu
            int screenHeight = al_get_display_height(display); /// zmienna do ktorej jest przypisana przechowujaca wysokosc ekranu

            if (event.mouse.x > screenWidth / 2 - 50 && event.mouse.x < screenWidth / 2 + 50) {
                if (event.mouse.y > screenHeight / 2 - 50 && event.mouse.y < screenHeight / 2) {
                    return 1; // Wybor opcji silnik
                }
                else if (event.mouse.y > screenHeight / 2 + 50 && event.mouse.y < screenHeight / 2 + 100) {
                    return 2; // Wybor opcji wyjscie
                }
            }
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            return 2; // Zamkniecie okna przyciskiem 'x'
        }
    }

    return 0; // Zwrocenie 0 po poprawnym zakonczeniu petli 
}
