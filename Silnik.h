#ifndef SILNIK_H
#define SILNIK_H
#include "balwan.h"
#include <allegro5/allegro.h>

class Silnik {
public:
    Silnik(ALLEGRO_DISPLAY* display);         /// Konstruktor klasy Silnik przyjmuje wskaznik do obiektu ALLEGRO_DISPLAY
    ~Silnik();                                /// Destruktor klasy Silnik
    ALLEGRO_TIMER* timer;                     /// Timer uzywany do czasu w programie
    bool isTimerRunning;                      /// Flaga okreslajaca czy timer jest uruchomiony
    void toggleTimer();                       /// Metoda do przelaczania stanu timera
    void clearScreen();                       /// Metoda do czyszczenia ekranu
    int handleInput();                        /// Metoda obsugujaca interakcje z uzytkownikiem 
    void showEndButton();                     /// Metoda do wyswietlania przycisku koncowego
    void showMousePosition();                 /// Metoda do wyswietlania pozycji myszy
    void showInstructions();                  /// Metoda do wyswietlania instrukcji
    void changeBackgroundColor(int color);    /// Metoda do zmiany koloru tla
    void toggleBalwan();                      /// Metoda do przelaczania widocznosci obiektu Balwan
    void updateBalwanPosition();              /// Metoda do aktualizacji pozycji obiektu Balwan
   

private:
    ALLEGRO_DISPLAY* display;                 /// Wskaznik do obiektu ALLEGRO_DISPLAY
    int mouseX, mouseY;;                      /// Zmienne przechowujace aktualn¹ pozycje myszy
    int  startX, startY;                      /// Poczatkowe wspolrzedne obiektu Balwan
    bool drawing;                             /// Flaga okreslajaca czy uzytkownik rysuje na ekranie
    bool isPKeyPressed;                       /// Flagi okreslajace czy klawisze P, K, T sa wcisniete
    bool isKKeyPressed;
    bool isTKeyPressed;
    Balwan balwan;                            /// Obiekt Balwan u¿ywany w programie
    bool isLeftKeyPressed;                    /// Flagi okreslajace czy klawisze strzalek sa wcisniete
    bool isRightKeyPressed;
    bool isUpKeyPressed;
    bool isDownKeyPressed;
};

#endif // SILNIK_H
