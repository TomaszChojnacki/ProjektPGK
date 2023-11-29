
#include <allegro5/allegro.h> /// Zaladowanie bibliotek Allegro
#include <allegro5/allegro_primitives.h> 
#include <allegro5/allegro_font.h> 
#include <allegro5/allegro_ttf.h> 
#include <iostream> 

using namespace std;

struct SegmentWeza { /// Definicja struktury segmentow weza
    int x, y; /// Wspolrzedne segmentu
};

enum Kierunek { /// Definicja typu wyliczeniowego okreslajacego kierunki ruchu 
    GORA,
    DOL,
    LEWO,
    PRAWO
};

class GraWeza { /// Definicja klasy reprezentującej gre 
public:
    int SZEROKOSC = 800; /// Stala okreslajaca szerokosc ekranu
    int WYSOKOSC = 600; /// Stala okreslajaca wysokosc ekranu
    int ROZMIAR_RUCHU = 20; /// Stala okreslajaca rozmiar pojedynczego ruchu weza
    GraWeza(); /// Konstruktor klasy
    void UruchomPetleGry(); /// Metoda uruchamiajaca petle gry
    void Inicjalizuj(); /// Metoda inicjalizujaca Allegro i ustawiajaca poczatkowe wartosci
    void Aktualizuj(); /// Metoda aktualizujaca stan gry
    void Renderuj(); /// Metoda renderujaca obraz gry
    void KierunekObsluga(); /// Metoda obslugujaca zmiany kierunku weza
    void GenerujJedzenie(); /// Metoda generujaca nowe polozenie jedzenia
    bool SprawdzKolizje(); /// Metoda sprawdzajaca kolizje weza
    void KoniecGry(); /// Metoda po przegraniu gry

    ALLEGRO_DISPLAY* ekran; /// Deklaracja ekran
    ALLEGRO_EVENT_QUEUE* kolejkaZdarzen; /// Deklaracja kolejki zdarzen w Allegro
    ALLEGRO_TIMER* zegar; /// Deklaracja timera w Allegro
    ALLEGRO_FONT* czcionka; /// Deklaracja czcionki

    SegmentWeza wez[100]; /// Tablica przechowująca segmenty weza (maksymalna dlugosc weza)
    Kierunek aktualnyKierunek; /// Zmienna przechowujaca aktualny kierunek ruchu weza
    int jedzenieX, jedzenieY; /// xwspolrzedne jedzenia
    int dlugoscWeza; /// Zmienna przechowujaca dlugosc weza
};

GraWeza::GraWeza() { /// Implementacja konstruktora klasy GraWeza
    Inicjalizuj(); 
}

void GraWeza::Inicjalizuj() { // Implementacja metody Inicjalizuj
    if (!al_init() || !al_install_keyboard() || !al_init_primitives_addon() || /// Inicjalizacja potrzebych dodatkow z biblioteki Allegro
        !al_init_font_addon() || !al_init_ttf_addon() || !al_install_mouse()) {
        cout << "Blad inicjalizacji Allegro!" << endl; /// Komunikat o bledzie dotyczacego wczytania dodatkow z biblioteki
        exit(EXIT_FAILURE); /// Wyjsce z programu gdy nastapi blad
    }

    ekran = al_create_display(SZEROKOSC, WYSOKOSC); /// Utworzenie obiektu reprezentujacego ekran
    if (!ekran) {
        cout << "Blad tworzenia ekranu!" << endl; /// Komunikat bledu o niepowodzeniu w tworzeniu ekranu
        exit(EXIT_FAILURE); /// Wyjsce z programu gdy nastapi blad
    }

    al_set_window_title(ekran, "Gra SNAKE"); /// Ustawienie tytulu okna gry

    kolejkaZdarzen = al_create_event_queue(); /// Utworzenie obiektu odpowiedzialnego za kolejke zdarzen
    zegar = al_create_timer(1.0 / 10); /// Utworzenie obiektu reprezentujacego timer (10 klatek na sekunde)
    czcionka = al_load_ttf_font("arial.ttf", 24, 0); /// Wczytanie czcionki 

    al_register_event_source(kolejkaZdarzen, al_get_keyboard_event_source()); /// Zarejestrowanie zrodla zdarzen
    al_register_event_source(kolejkaZdarzen, al_get_timer_event_source(zegar));
    al_register_event_source(kolejkaZdarzen, al_get_display_event_source(ekran));
    al_register_event_source(kolejkaZdarzen, al_get_mouse_event_source());
    /// Inicjalizacja weza
    wez[0].x = SZEROKOSC / 2;
    wez[0].y = WYSOKOSC / 2;
    dlugoscWeza = 1;
    aktualnyKierunek = PRAWO;

    /// Inicjalizacja pierwszego jedzenia
    GenerujJedzenie();

    al_start_timer(zegar); /// Uruchomienie timera
}

void GraWeza::UruchomPetleGry() { /// Implementacja metody UruchomPetleGry
    bool przerysuj = true; /// Flaga wskazujaca, czy trzeba przerysowac obraz
    bool zakonczGre = false; /// Flaga wskazujaca, czy gra ma byc zakonczona

    while (!zakonczGre) { /// Glowna petla gry
        ALLEGRO_EVENT zdarzenie; /// Struktura przechowujaca zdarzenie
        al_wait_for_event(kolejkaZdarzen, &zdarzenie); /// Oczekiwanie na zdarzenie

        if (zdarzenie.type == ALLEGRO_EVENT_TIMER) { /// Obsluga zdarzenia od timera
            Aktualizuj(); /// Wywolanie metody aktualizujacej stan gry
            przerysuj = true; /// Ustawienie flagi przerysowania
        }
        else if (zdarzenie.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { /// Obsluga zamkniecia okna
            zakonczGre = true; /// Ustawienie flagi zakonczenia gry
        }
        else if (zdarzenie.type == ALLEGRO_EVENT_KEY_DOWN) { /// Obsuga nacisniecia klawisza
            if (zdarzenie.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                zakonczGre = true; /// Ustawienie flagi zakonczenia gry
            }
            KierunekObsluga(); /// Wywolanie metody obslugujacej zmiany kierunku weza
        }

        if (przerysuj && al_is_event_queue_empty(kolejkaZdarzen)) {
            Renderuj(); /// Wywolanie metody renderujacej obraz gry
            przerysuj = false; /// flagi przerysowania ustawiana na false
        }
    }
}

void GraWeza::Aktualizuj() { /// Implementacja metody Aktualizuj
    /// Przesuniecie weza
    int glowaX = wez[0].x;
    int glowaY = wez[0].y;

    switch (aktualnyKierunek) { /// Zaleznie od kierunku x lub y rosna albo maleja
    case GORA:
        glowaY -= ROZMIAR_RUCHU;
        break;
    case DOL:
        glowaY += ROZMIAR_RUCHU;
        break;
    case LEWO:
        glowaX -= ROZMIAR_RUCHU;
        break;
    case PRAWO:
        glowaX += ROZMIAR_RUCHU;
        break;
    }

    /// Sprawdzenie kolizji
    if (glowaX < 0 || glowaX >= SZEROKOSC || glowaY < 0 || glowaY >= WYSOKOSC || SprawdzKolizje()) {
        KoniecGry(); /// Wywolanie metody konczacej gre
        return;
    }

    /// Sprawdzenie, czy waz zjadl jedzenie
    if (glowaX == jedzenieX && glowaY == jedzenieY) {
        GenerujJedzenie(); /// Wywolanie metody generujacej nowe jedzenie
        dlugoscWeza++; /// Zwiekszenie dlugosci weza
    }

    /// Przesuniecie segmentow weza
    for (int i = dlugoscWeza - 1; i > 0; --i) {
        wez[i].x = wez[i - 1].x;
        wez[i].y = wez[i - 1].y;
    }

    /// Ustawienie nowej pozycji glowy weza
    wez[0].x = glowaX;
    wez[0].y = glowaY;
}

void GraWeza::Renderuj() { /// Implementacja metody Renderuj
    al_clear_to_color(al_map_rgb(0, 0, 0)); /// Wyczyszczenie ekranu na czarno

    /// Narysowanie weza
    for (int i = 0; i < dlugoscWeza; ++i) {
        al_draw_filled_rectangle(wez[i].x, wez[i].y, wez[i].x + ROZMIAR_RUCHU, wez[i].y + ROZMIAR_RUCHU, al_map_rgb(0, 255, 0));
    }

    /// Narysowanie jedzenia
    al_draw_filled_rectangle(jedzenieX, jedzenieY, jedzenieX + ROZMIAR_RUCHU, jedzenieY + ROZMIAR_RUCHU, al_map_rgb(255, 0, 0));

    al_flip_display(); // Wymiana buforow, aby nowy obraz byl widoczny
}

void GraWeza::KierunekObsluga() { /// Implementacja metody KierunekObsluga
    ALLEGRO_KEYBOARD_STATE stanKlawiatury; /// Struktura przechowujaca stan klawiatury
    al_get_keyboard_state(&stanKlawiatury); /// Pobranie aktualnego stanu klawiatury

    if (al_key_down(&stanKlawiatury, ALLEGRO_KEY_UP) && aktualnyKierunek != DOL) {
        aktualnyKierunek = GORA; /// Zmiana kierunku na gore, jesli nie jest on aktualny
    }
    else if (al_key_down(&stanKlawiatury, ALLEGRO_KEY_DOWN) && aktualnyKierunek != GORA) {
        aktualnyKierunek = DOL; /// Zmiana kierunku na dol, jesli nie jest on aktualny
    }
    else if (al_key_down(&stanKlawiatury, ALLEGRO_KEY_LEFT) && aktualnyKierunek != PRAWO) {
        aktualnyKierunek = LEWO; /// Zmiana kierunku w lewo, jesli nie jest on aktualny
    }
    else if (al_key_down(&stanKlawiatury, ALLEGRO_KEY_RIGHT) && aktualnyKierunek != LEWO) {
        aktualnyKierunek = PRAWO; /// Zmiana kierunku w prawo, jesli nie jest on aktualny
    }
}

/// Metoda generujaca jedzenie w grze
void GraWeza::GenerujJedzenie() { /// Implementacja metody GenerujJedzenie
    bool poprawnePolozenie = false; /// Flaga wskazujaca, czy wygenerowane jedzenie ma poprawne polozenie

    while (!poprawnePolozenie) {
        poprawnePolozenie = true;

        jedzenieX = (rand() % (SZEROKOSC / ROZMIAR_RUCHU)) * ROZMIAR_RUCHU; // Losowanie wspolrzednej X jedzenia
        jedzenieY = (rand() % (WYSOKOSC / ROZMIAR_RUCHU)) * ROZMIAR_RUCHU; // Losowanie wspolrzednej Y jedzenia

        // Sprawdzenie, czy nowe polozenie jedzenia nie znajduje sie na ciele weza
        for (int i = 0; i < dlugoscWeza; ++i) {
            if (jedzenieX == wez[i].x && jedzenieY == wez[i].y) {
                poprawnePolozenie = false;
                break;
            }
        }
    }
}

/// Metoda sprawdzajaca kolizje w grze
bool GraWeza::SprawdzKolizje() {
    int glowaX = wez[0].x;
    int glowaY = wez[0].y;

    // Sprawdzenie kolizji z ciałem weza
    for (int i = 1; i < dlugoscWeza; ++i) {
        if (glowaX == wez[i].x && glowaY == wez[i].y) {
            return true;
        }
    }

    return false;
}

/// Metoda obslugujaca zakonczenie gry
void GraWeza::KoniecGry() {
    al_clear_to_color(al_map_rgb(0, 0, 0)); /// Ustawienie tla
    al_draw_text(czcionka, al_map_rgb(184, 3, 255), SZEROKOSC / 2, WYSOKOSC / 2-50, ALLEGRO_ALIGN_CENTER, "GAME OVER"); /// Napis Game Over
    al_draw_text(czcionka, al_map_rgb(255, 255, 255), SZEROKOSC / 2, WYSOKOSC / 2, ALLEGRO_ALIGN_CENTER, "Wyjscie"); /// Napis Wyjscie
    al_flip_display();

    bool zakonczProgram = false; /// Flaga wskazujaca, czy program ma sie zakonczyc 

    while (!zakonczProgram) {
        ALLEGRO_EVENT zdarzenie;
        al_wait_for_event(kolejkaZdarzen, &zdarzenie); /// Struktura przechowujaca zdarzenie

        if (zdarzenie.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            zakonczProgram = true; /// Zakonczenie programu przez klikniecie X w prawym rogu ekranu
        }
        else if (zdarzenie.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) { 
            int mouseX = zdarzenie.mouse.x; /// Polozenie myszki x
            int mouseY = zdarzenie.mouse.y; /// Polozenie myszki y

            /// Sprawdź, czy myszka jest nad obszarem "Wyjscie"
            if (mouseX >= SZEROKOSC / 2 - 50 && mouseX <= SZEROKOSC / 2 + 50 &&
                mouseY >= WYSOKOSC / 2 - 12 && mouseY <= WYSOKOSC / 2 + 12) { /// Przedzial w pikselach w ktorych wykrywane jest klikniecie myszki
                zakonczProgram = true; /// Zakonczenie programu
            }
        }
        else if (zdarzenie.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (zdarzenie.keyboard.keycode == ALLEGRO_KEY_ESCAPE) { 
                zakonczProgram = true; /// Zakonczenie programu poprzez przycisk ESCAPE
            }
        }
    }

    al_destroy_display(ekran); /// zwolnienie zasobow biblioteki
    al_destroy_event_queue(kolejkaZdarzen);
    al_destroy_timer(zegar);
    al_destroy_font(czcionka);

    exit(EXIT_SUCCESS);
}



int main() {
    GraWeza graWeza; 
    graWeza.UruchomPetleGry(); /// uruchomienie petli

    return 0;
}