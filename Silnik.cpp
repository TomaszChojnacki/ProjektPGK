#include "silnik.h"
#include "Prymitywy.h"
#include "balwan.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdbool.h>

Silnik::Silnik(ALLEGRO_DISPLAY* display) /// Konstruktor klasy Silnik 
    : display(display), mouseX(0), mouseY(0), startX(0), startY(0), drawing(false), isPKeyPressed(false), isKKeyPressed(false), 
    isTKeyPressed(false), balwan(display), isLeftKeyPressed(false), isRightKeyPressed(false), isUpKeyPressed(false), 
    isDownKeyPressed(false), isTimerRunning(false){

    timer = al_create_timer(1.0 / 60); /// ustawienie czasu w programie 60Hz
   
}

Silnik::~Silnik() /// Destruktor kalsy Silnik
{
    al_destroy_timer(timer);
}


void Silnik::toggleTimer(void) /// Metoda do przelaczania timera
{
    if (isTimerRunning) {
        al_stop_timer(timer); /// timer wlaczony
        
    }
    else {
        al_start_timer(timer); /// timer wylaczony
    }
    isTimerRunning = !isTimerRunning;
}

void Silnik::clearScreen(void) ///Metoda czyszczenia ekranu i wyswietlania
{
    al_clear_to_color(al_map_rgb(255, 0, 0)); /// czyszczenie ekranu
    showInstructions(); /// funkcja ktora wyswietla komunikat na ekranie
    showEndButton(); /// funkcja pokazujaca przycisk wyjscie
    showMousePosition(); /// funckja pokazujaca pozycje myszy
    balwan.draw(); /// funkcja rysujaca balwana
   
    if (drawing) /// funckja odpowiada z rydowanie prymitywu 
    {
        if (isPKeyPressed) /// rysowanie prymitywy jesli odpowieni przycisk jest klikniety 
        {
            Prymitywy::drawRectangle(display, startX, startY, mouseX, mouseY); /// Rysowanie prostokatu
        }
        else if (isKKeyPressed) {
            Prymitywy::drawCircle(display, startX, startY, mouseX, mouseY); /// rysowanie kola
        }
        else if (isTKeyPressed) {
            Prymitywy::drawTriangle(display, startX, startY, mouseX, mouseY); /// rysowanie trojkata
        }
    }
    al_flip_display(); /// wypisanie na ekranie
}

void Silnik::showInstructions() ///Metoda do wyswietlania informacji na ekranie
{
    al_draw_text(al_create_builtin_font(), al_map_rgb(255, 255, 255), 
        al_get_display_width(display) / 2, al_get_display_height(display) / 2, 
        ALLEGRO_ALIGN_CENTER, "Aby zmienic kolor, wcisnij od 0 do 9");
}

void Silnik::showEndButton() /// Metoda do wyswietlania przycisku wyjscia w prawym dolnym rogu ekranu
{
    al_draw_text(al_create_builtin_font(), al_map_rgb(255, 255, 255),
        al_get_display_width(display) - 80, al_get_display_height(display) - 30,
        ALLEGRO_ALIGN_CENTER, "Wyjdz");
}
void Silnik::showMousePosition() /// Metoda do wyswietlania pozycji myszy
{
    ALLEGRO_MOUSE_STATE state;
    al_get_mouse_state(&state);
   
    al_draw_textf(al_create_builtin_font(), al_map_rgb(255, 255, 255), 10, 10, ALLEGRO_ALIGN_LEFT, "Mysz: %d, %d", state.x, state.y);
    al_flip_display();

    mouseX = state.x; /// pozycja x
    mouseY = state.y; /// pozycja y

    if (drawing) /// Dodanie wyswietlania prymitywow w celu rozpoczecia rysowania w pozycji myszy 
    {
        if (isPKeyPressed) {
            Prymitywy::drawRectangle(display, startX, startY, mouseX, mouseY);
        }
        else if (isKKeyPressed) {
            Prymitywy::drawCircle(display, startX, startY, mouseX, mouseY);
        }
        else if (isTKeyPressed) {
            Prymitywy::drawTriangle(display, startX, startY, mouseX, mouseY);
        }
    }
}


void Silnik::changeBackgroundColor(int color)  /// Metoda do zmiany koloru tla
{
    int r, g, b;

    switch (color) {
    case 0:
        r = 0; g = 0; b = 255; // Niebieski
        break;
    case 1:
        r = 255; g = 0; b = 0; // Czerwony
        break;
    case 2:
        r = 128; g = 0; b = 128; // Fioletowy
        break;
    case 3:
        r = 255; g = 165; b = 0; // Pomaranczowy
        break;
    case 4:
        r = 0; g = 128; b = 0; // Zielony
        break;
    case 5:
        r = 255; g = 200; b = 0; // ¯olty
        break;
    case 6:
        r = 128; g = 128; b = 128; // Szary
        break;
    case 7:
        r = 255; g = 100; b = 0; // Bialy
        break;
    case 8:
        r = 255; g = 182; b = 193; // Rozowy
        break;
    case 9:
        r = 165; g = 42; b = 42; // Brazowy
        break;
    default:
        r = 255; g = 0; b = 0; // Domyslnie czerwony
        break;
    }
    clearScreen(); /// wyczyszczenie ekranu
    al_clear_to_color(al_map_rgb(r, g, b)); /// wyswietlenie koloru
    showInstructions(); /// wyswietlenie instrukcji
    showEndButton(); /// Wyswietlenie przycisku konca 
    showMousePosition(); /// Wyswietlenie pozycji myszki
    balwan.draw(); /// rysowanie balwana
    al_flip_display(); /// wypisanie wszystkiego na ekran 
}

void Silnik::toggleBalwan(void) /// Metoda do przelaczania widocznosci balwana
{
    balwan.toggleVisibility();
}

void Silnik::updateBalwanPosition(void) /// metoda do okreslenia pozycji balwana
{
    int horizontalDirection = 0;
    int verticalDirection = 0;

    ALLEGRO_KEYBOARD_STATE keyState;
    al_get_keyboard_state(&keyState);

    if (isLeftKeyPressed) {
        horizontalDirection = -1;
    }
    else if (isRightKeyPressed) {
        horizontalDirection = 1;
    }

    if (isUpKeyPressed) {
        verticalDirection = -1;
    }
    else if (isDownKeyPressed) {
        verticalDirection = 1;
    }

    balwan.changeDirection(horizontalDirection, verticalDirection); /// przeslanie informacji o zmianie pozycji 
    balwan.move(); /// funkcja zwiazana z ruchem balwana
}


int Silnik::handleInput(void) /// Metoda obsugujaca interakcje z uzytkownikiem 
{
    ALLEGRO_EVENT_QUEUE* eventQueue = al_create_event_queue(); /// Tworzenie kolejki 
    al_register_event_source(eventQueue, al_get_display_event_source(display)); /// Przkierowanie ekranu do kolejki
    al_register_event_source(eventQueue, al_get_mouse_event_source()); /// Przekierwanie myszki do kolejki
    al_register_event_source(eventQueue, al_get_keyboard_event_source());  /// Przekierownaie klawiatury do kolejki
    al_register_event_source(eventQueue, al_get_timer_event_source(timer)); /// Przekierowanie czasu do kolejki

    while (true) /// Petla odpowiadajaca za dzialanie programu silnika
    {
        ALLEGRO_EVENT event; /// Tworzenie nowego eventu w celu przekierowania do kolejki 
        al_wait_for_event(eventQueue, &event); /// czekanie na kolejke 

        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) /// Odpowiada za zamkniecie petli silnika przez klikniecie w wyjscie
        {
            if (event.mouse.x > al_get_display_width(display) - 100 && event.mouse.y > al_get_display_height(display) - 50) {
                al_destroy_event_queue(eventQueue);
                return 0; 
            }
        }
        else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) /// Odpowiada za zamkniecie okna przyciskiem 'x'
        {
            al_destroy_event_queue(eventQueue);
            return 0;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) /// Odpowiada za uruchamianie funkcji po wcisnieciu przycisku
        {
            if (event.keyboard.keycode == ALLEGRO_KEY_P) {
                isPKeyPressed = true;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_K) {
                isKKeyPressed = true;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_T) {
                isTKeyPressed = true;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_B) {
                toggleBalwan(); /// uruchomienie funkcji balwana
                toggleTimer(); /// uruchomienie czasu w programie
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                isLeftKeyPressed = true; /// Dodanie poruszania sie strzalka w lewo 
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                isRightKeyPressed = true; /// Dodanie poruszania sie strzalka w prawo
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
                isUpKeyPressed = true; /// Dodanie poruszania sie strzalka w gore
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                isDownKeyPressed = true; /// Dodanie poruszania sie strzalka w dol
            }
        }


        else if (event.type == ALLEGRO_EVENT_KEY_UP) /// sprawdza czy przycisk zostal puszczony jesli tak anuluje dzialanie wybranej funkcji
        {
            if (event.keyboard.keycode == ALLEGRO_KEY_P) {
                isPKeyPressed = false;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_K) {
                isKKeyPressed = false;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_T) {
                isTKeyPressed = false;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                isLeftKeyPressed = false; 
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                isRightKeyPressed = false;
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_UP) {
                isUpKeyPressed = false; 
            }
            else if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) {
                isDownKeyPressed = false; 
            }
        }


        else if (event.type == ALLEGRO_EVENT_KEY_CHAR) /// Obsluguje zdarzenia klawiatury zwiazanie z cyframie od 0 do 9
        {
            if (event.keyboard.unichar >= '0' && event.keyboard.unichar <= '9') {
                changeBackgroundColor(event.keyboard.unichar - '0');
            }
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) /// Odpowiada za koordynaty myszy
        {
                showMousePosition();
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) /// Sprawdza czy przcisk myszy zostal wcisniety 
        {
            if (event.mouse.x < al_get_display_width(display) - 100 && event.mouse.y < al_get_display_height(display) - 50) {
                // Pocz¹tek rysowania prostok¹ta
                startX = event.mouse.x;
                startY = event.mouse.y;
                drawing = true;
            }
        }
        else if (event.type == ALLEGRO_EVENT_TIMER) /// Odpowiada za czas w programie
        {
            updateBalwanPosition();
            clearScreen();
        }
        al_flip_display(); /// Wypiszanie na ekran
        
    }
}
