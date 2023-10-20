#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int BUTTON_WIDTH = 100;
const int BUTTON_HEIGHT = 50;
const int BUTTON_X = SCREEN_WIDTH - BUTTON_WIDTH - 10;
const int BUTTON_Y = SCREEN_HEIGHT - BUTTON_HEIGHT - 10;

bool isMouseOverButton(int mouseX, int mouseY) {
    return (mouseX >= BUTTON_X && mouseX <= (BUTTON_X + BUTTON_WIDTH) &&
        mouseY >= BUTTON_Y && mouseY <= (BUTTON_Y + BUTTON_HEIGHT));
}
int main() {
    ALLEGRO_DISPLAY* display = nullptr;
    ALLEGRO_EVENT_QUEUE* eventQueue = nullptr;
    ALLEGRO_FONT* font = nullptr;
    ALLEGRO_COLOR backgroundColor = al_map_rgb(0, 0, 0);
    ALLEGRO_COLOR textColor = al_map_rgb(255, 255, 255);
    ALLEGRO_COLOR buttonColor = al_map_rgb(100, 100, 100);
    if (!al_init()) {
        cout << "ERROR ALLEGRO";
        return 1;
    }

    display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        cout << "ERROR DISPLAYA";
        return 1;
    }

    al_install_mouse();
    al_install_keyboard();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    font = al_load_ttf_font("arial.ttf", 30, 0);
    if (!font) {
        cout << "ERROR FONTA";
        return  1;
    }

    eventQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_mouse_event_source());
    al_register_event_source(eventQueue, al_get_keyboard_event_source());

    bool running = true;

    int mouseX = 0;
    int mouseY = 0;

    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
            mouseX = event.mouse.x;
            mouseY = event.mouse.y;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode >= ALLEGRO_KEY_1 && event.keyboard.keycode <= ALLEGRO_KEY_9 || event.keyboard.keycode == ALLEGRO_KEY_0) {
                
                switch (event.keyboard.keycode) {
                
                case ALLEGRO_KEY_1:
                    backgroundColor = al_map_rgb(0, 255, 0);  // Zielony
                    break;
                case ALLEGRO_KEY_2:
                    backgroundColor = al_map_rgb(0, 0, 255); // Niebieski
                    break;
                case ALLEGRO_KEY_3:
                    backgroundColor = al_map_rgb(255, 0, 255); // Rozowy
                    break;
                case ALLEGRO_KEY_4:
                    backgroundColor = al_map_rgb(255, 255, 0); //zolty
                    break;
                case ALLEGRO_KEY_5:
                    backgroundColor = al_map_rgb(255, 0, 0);  // Czerwony
                    break;
                case ALLEGRO_KEY_6:
                    backgroundColor = al_map_rgb(255, 150, 0); //Pomaranczowy
                    break;
                case ALLEGRO_KEY_7:
                    backgroundColor = al_map_rgb(0, 150, 255); //turkusowy
                    break;
                case ALLEGRO_KEY_8:
                    backgroundColor = al_map_rgb(150, 150, 150); // szary
                    break;
                case ALLEGRO_KEY_9:
                    backgroundColor = al_map_rgb(60, 60, 60); // ciemno szary
                    break;
                case ALLEGRO_KEY_0:
                    backgroundColor = al_map_rgb(0, 0, 0); //czarny
                    break;
                }
            }
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if (event.mouse.button & 1) {  // Obsługuje lewy przycisk myszy
                if (isMouseOverButton(mouseX, mouseY)) {
                    running = false;
                }
            }
        }
        al_clear_to_color(backgroundColor);
        al_draw_textf(font, textColor, 10, 10, 0, "Pozycja myszki: X=%d, Y=%d", mouseX, mouseY);
        al_draw_textf(font, textColor, 10, 40, 0, "Klawiszami od 0-9 mozna wybierac kolory tla");
        al_draw_filled_rounded_rectangle(BUTTON_X, BUTTON_Y, BUTTON_X + BUTTON_WIDTH, BUTTON_Y + BUTTON_HEIGHT, 5, 5, buttonColor);
        al_draw_text(font, textColor, BUTTON_X + 10, BUTTON_Y + 10, 0, "Exit");
        al_flip_display();
    }

    al_destroy_font(font);
    al_destroy_event_queue(eventQueue);
    al_destroy_display(display);

    return 0;
}
