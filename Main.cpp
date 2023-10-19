#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>

int main() {
    // Inicjalizacja Allegro
    al_init();

    // Inicjalizacja myszki
    al_install_mouse();

    // Inicjalizacja klawiatury
    al_install_keyboard();

    // Inicjalizacja timera
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60);  // 60 klatek na sekundê

    // Utworzenie okna o rozmiarze 800x600 pikseli
    ALLEGRO_DISPLAY* display = al_create_display(800, 600);

    // Ustawienie koloru t³a na niebieski
    al_clear_to_color(al_map_rgb(0, 0, 255));

    // Utworzenie kolejki zdarzeñ
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();

    // Rejestracja zdarzeñ myszki, klawiatury i timera
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    // Ustawienia przycisku "Wyjœcie"
    int button_width = 100;
    int button_height = 40;
    int button_x = al_get_display_width(display) - button_width;
    int button_y = al_get_display_height(display) - button_height;

    bool exit = false;
    int current_mouse_x = -1;  // Inicjalizacja aktualnego po³o¿enia myszki
    int current_mouse_y = -1;
    ALLEGRO_COLOR background_color = al_map_rgb(0, 0, 255);  // Domyœlny kolor t³a

    // Uruchomienie timera
    al_start_timer(timer);

    while (!exit) {
        ALLEGRO_EVENT ev;
        ALLEGRO_FONT* font = al_create_builtin_font();
        al_wait_for_event(event_queue, &ev);

        // Obs³uga zdarzeñ myszki
        if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            if (ev.mouse.button & 1) {  // Sprawdza czy to lewy przycisk myszy
                // Sprawdza czy myszka kliknê³a w obszar przycisku "Wyjœcie"
                if (ev.mouse.x >= button_x && ev.mouse.x <= button_x + button_width &&
                    ev.mouse.y >= button_y && ev.mouse.y <= button_y + button_height) {
                    exit = true;  // Zamkniêcie programu po klikniêciu przycisku "Wyjœcie"
                }
            }
        }

        // Obs³uga zdarzeñ zamkniêcia okna
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            exit = true;
        }

        // Sprawdzenie, czy po³o¿enie myszki siê zmieni³o
        if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
            if (ev.mouse.x != current_mouse_x || ev.mouse.y != current_mouse_y) {
                // Wyczyszczenie obszaru poprzedniego po³o¿enia myszki
                al_clear_to_color(background_color);         

                // Wyœwietlanie aktualnej pozycji myszki w lewym górnym rogu
                al_draw_textf(al_create_builtin_font(), al_map_rgb(255, 255, 255), 10, 10, ALLEGRO_ALIGN_LEFT, "Mysz: (%d, %d)", ev.mouse.x, ev.mouse.y);

                // Zapisanie aktualnego po³o¿enia myszki
                current_mouse_x = ev.mouse.x;
                current_mouse_y = ev.mouse.y;

                // Odœwie¿enie okna
               
            }
        }

        // Obs³uga zdarzeñ klawiatury
        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            // Sprawdzenie wciœniêtej klawisza
            switch (ev.keyboard.keycode) {
            case ALLEGRO_KEY_1:
                background_color = al_map_rgb(0, 255, 0);  // Zielony
                break;
            case ALLEGRO_KEY_2:
                background_color = al_map_rgb(255, 0, 0);  // Czerwony
                break;
            case ALLEGRO_KEY_3:
                background_color = al_map_rgb(0, 0, 255); // Niebieski
                break;
            case ALLEGRO_KEY_4:
                background_color = al_map_rgb(255, 0, 255); // Fioletowy
                break;
            case ALLEGRO_KEY_5:
                background_color = al_map_rgb(255, 255, 0); //zolty
                break;
            case ALLEGRO_KEY_6:
                background_color = al_map_rgb(0, 0, 0); //czarny
                break;
            case ALLEGRO_KEY_7:
                background_color = al_map_rgb(255, 150, 0); //Pomaranczowy
                break;
            case ALLEGRO_KEY_8:
                background_color = al_map_rgb(0, 150, 255); //turkusowy
                break;
            case ALLEGRO_KEY_9:
                background_color = al_map_rgb(150,150,150); // szary
                break;
            case ALLEGRO_KEY_0:
                background_color = al_map_rgb(60, 60, 60); // ciemno szary
                break;

            }
            al_clear_to_color(background_color);  // Zmiana koloru t³a po wciœniêciu klawisza
        }

        // Obs³uga zdarzeñ timera
        if (ev.type == ALLEGRO_EVENT_TIMER) {
            // Tutaj mo¿esz dodaæ kod zwi¹zany z automatyczn¹ zmian¹ koloru t³a
            // np. background_color = ...;
            // al_clear_to_color(background_color);
            al_draw_text(font, al_map_rgb(255, 255, 255),200,200, ALLEGRO_ALIGN_CENTRE, "aby zmienic kolor tla mozesz wcisnac przyciski od 0 do 9");
            al_draw_text(font, al_map_rgb(255, 0, 255), button_x + button_width / 2, button_y + button_height / 2, ALLEGRO_ALIGN_CENTRE, "Wyjscie");
            al_destroy_font(font);  // Nie zapomnij zwolniæ pamiêci!
            al_flip_display();
        }


    }


    // Zniszczenie timera
    al_destroy_timer(timer);

    // Zniszczenie kolejki zdarzeñ
    al_destroy_event_queue(event_queue);

    // Zniszczenie okna
    al_destroy_display(display);

    return 0;
}
