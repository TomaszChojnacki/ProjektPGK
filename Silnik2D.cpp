#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "menu.h"
#include "silnik.h"

int main(void) {
    /// Inicjalizacja zmiennych dla obslugi grafiki, klawiatury, myszy, czcionek i obrazow
    ALLEGRO_DISPLAY* display = nullptr;
    ALLEGRO_FONT* font = nullptr;
    ALLEGRO_EVENT_QUEUE* eventQueue = nullptr;

    al_init(); /// inicjalizacja allegro
    al_install_mouse(); /// instalacja myszki
    al_install_keyboard(); /// Instalacja klawiaury
    al_init_image_addon(); /// Inicjalizacja funkcji zdjec
    al_init_font_addon(); /// Inicjalizacja czcionki 
    al_init_ttf_addon(); /// Inicjalizacja rodziaju czcionki 
    al_init_primitives_addon(); /// Inicjalizacja prymitywow 

    display = al_create_display(800, 600);/// Tworzenie okna graficznego o rozmiarach 800x600 pikseli
    font = al_load_ttf_font("Arial.ttf", 30, 0); ///Dodanie rodzaju czcioski 
    eventQueue = al_create_event_queue(); /// Tworzenie kolejki zdarzen

    al_register_event_source(eventQueue, al_get_mouse_event_source()); ///Dodanie zdarzenia myszki do kolejki
    al_register_event_source(eventQueue, al_get_display_event_source(display)); ///Dodanie zdarzenia obrazu do kolejki
    

    Menu menu(display, font); /// Inicjalizacja obiktow menu
    Silnik silnik(display); ///Inicjalizacja obiktow silnika

    bool running = true; ///Zmienna bool potrzebna do petli while w celu okreselenia czy program ma sie zakonczyc czy ma dzialac 
    while (running) {
        menu.draw(); /// Wyswietlenia menu
        int action = menu.handleInput(eventQueue); /// Przekierowanie zdarzen z menu do kolejki 

        switch (action) {
        case 1:
            silnik.clearScreen(); /// Wyczyszczenie ekranu
            running = silnik.handleInput(); // Przejscie do silnika
            break; /// zakonczenie case 1
        case 2:
            running = false; /// Wyjscie z petli powoduje zakonczenie programu
            break; /// zakonczenie case 2
        }
    }

    al_destroy_event_queue(eventQueue); /// Zwolnienie zaalokowanej pamieci kolejki
    al_destroy_display(display); /// Zwolnienie zaalokowanej pamieci okna
    al_destroy_font(font); /// Zwolnienei zaalokowanej pamieci czcionki

    return 0; /// zwrocenie 0 po poprawnym zamknieciu programu
}



/// Tworcy: Tomasz Chojnacki, Przemyslaw Palka, Maciej Bernatek