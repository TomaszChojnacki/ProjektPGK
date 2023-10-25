#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdbool.h>

int main()
{
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();

    ALLEGRO_FONT* font = al_load_ttf_font("Amatic-Bold.ttf", 50, 0);
    ALLEGRO_DISPLAY* display = al_create_display(1240, 640);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60);
    ALLEGRO_TIMER* timer2 = al_create_timer(0.1);
    ALLEGRO_BITMAP* bitmap_left = NULL;
    ALLEGRO_BITMAP* bitmap_right = NULL;
    ALLEGRO_BITMAP* bitmap_up = NULL;
    ALLEGRO_BITMAP* bitmap_down = NULL;
    ALLEGRO_BITMAP* current_bitmap = NULL;  
    ALLEGRO_BITMAP* button = al_create_bitmap(200, 70);
    al_set_target_bitmap(button);
    al_clear_to_color(al_map_rgb(255, 0, 0));
    al_set_target_backbuffer(display);

    al_install_keyboard();
    al_install_mouse();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_timer_event_source(timer2));

    bitmap_right = al_load_bitmap("balwan1.png");
    bitmap_left = al_load_bitmap("balwan2.png");
    bitmap_up = al_load_bitmap("balwan3.png");
    bitmap_down = al_load_bitmap("balwan4.png");
    
    assert(bitmap_left != NULL && bitmap_right != NULL && bitmap_up != NULL && bitmap_down != NULL);

    int points[4] = { 180, 140, 90, 50 };
    float x = 0, y = 0;
    int width = al_get_display_width(display);
    int height = al_get_display_height(display);
    int a = 200, b = 100;
    bool menu = true;
    bool graj = false;
    al_start_timer(timer);

    while (true)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (menu)
        {
            if (event.type == ALLEGRO_EVENT_TIMER)
            {
                al_clear_to_color(al_map_rgb(21, 33, 233));

                al_draw_text(font, al_map_rgb(0, 0, 0), 270, 200, 0, "GRAJ");
                al_draw_text(font, al_map_rgb(0, 0, 0), 220, 400, 0, "WYJSCIE");
                al_flip_display();
            }

            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                return false;

            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP &&
                event.mouse.x >= 270 && event.mouse.x <= 270 + al_get_text_width(font, "GRAJ") &&
                event.mouse.y >= 200 && event.mouse.y <= 200 + al_get_font_line_height(font))
            {
                graj = true;
                menu = false;
                current_bitmap = bitmap_right;
            }
            else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP &&
                event.mouse.x >= 220 && event.mouse.x <= 320 &&
                event.mouse.y >= 400 && event.mouse.y <= 460)
            {
                return false;
            }
        }

        if (graj)
        {
            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                return false;

            int direction = 0;
            int vertical_direction = 0;

            ALLEGRO_KEYBOARD_STATE keyState;
            al_get_keyboard_state(&keyState);

            if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
            {
                x += 5;
                direction = 1;
            }
            else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
            {
                x -= 5;
                direction = -1;
            }

            if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))
            {
                y += 5;
                vertical_direction = 1;
            }
            if (al_key_down(&keyState, ALLEGRO_KEY_UP))
            {
                y -= 5;
                vertical_direction = -1;
            }

            if (x > (width - al_get_bitmap_width(current_bitmap)))

                x = (width - al_get_bitmap_width(current_bitmap));

            if (x < 0)
                x = 0;

            if (y > (height - al_get_bitmap_height(current_bitmap)))
                y = (height - al_get_bitmap_height(current_bitmap));
                if (y < 0)
                    y = 0;

                if (direction == 1)
                {
                    current_bitmap = bitmap_right;
                }
                else if (direction == -1)
                {
                    current_bitmap = bitmap_left;
                }

            if (vertical_direction == 1)
            {
                current_bitmap = bitmap_down;
            }
            else if (vertical_direction == -1)
            {
                current_bitmap = bitmap_up;
            }

            if (event.type == ALLEGRO_EVENT_TIMER)
            {
                al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));
                al_draw_bitmap(current_bitmap, x, y, 0);
                al_draw_bitmap(button, 1000, 500, 0);
                al_draw_text(font, al_map_rgb(0, 0, 0), 1055, 505, 0, "WYJSCIE");
                al_flip_display();
            }

            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP &&
                event.mouse.x >= 1000 && event.mouse.x <= 1000 + 200 &&
                event.mouse.y >= 500 && event.mouse.y <= 500 + 70)
            {
                graj = false;
                menu = true;
            }

        
    }
    }

    al_destroy_event_queue(queue);
    al_destroy_bitmap(button);
    al_uninstall_mouse();
    al_uninstall_keyboard();
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_timer(timer2);
    al_destroy_bitmap(bitmap_left);
    al_destroy_bitmap(bitmap_right);
    al_destroy_bitmap(bitmap_up);
    al_destroy_bitmap(bitmap_down);
    

    return 0;
}
