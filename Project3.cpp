#include <allegro5/allegro5.h>
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

    ALLEGRO_FONT* font = al_load_ttf_font("Amatic-Bold.ttf", 50, 0);
    ALLEGRO_DISPLAY* display = al_create_display(1240, 640);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60);
    ALLEGRO_TIMER* timer2 = al_create_timer(0.1);
    ALLEGRO_BITMAP* bitmap = NULL;
    ALLEGRO_BITMAP* bitmap2 = NULL;
    ALLEGRO_BITMAP* bitmap3 = NULL;
    ALLEGRO_KEYBOARD_STATE keyState;
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

    al_init_image_addon();
    bitmap = al_load_bitmap("luki.jpg");
    bitmap2 = al_load_bitmap("NOWAY.png");
    bitmap3 = al_load_bitmap("ufolud.png");
    assert(bitmap != NULL);

    int points[4] = { 180, 140, 90 ,50 };
    float x = 0, y = 0, c = 50.0, d[4] = { 120.0,120.0,120.0,120.0 }, M[4] = { 2.0, 2.0 ,2.0 ,2.0 };
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

        if (menu) {
            if (event.type == ALLEGRO_EVENT_TIMER) {
                al_clear_to_color(al_map_rgb(21, 33, 233));
                al_draw_text(font, al_map_rgb(0, 0, 0), 250, 0, 0, "Murzyn");
                al_draw_text(font, al_map_rgb(0, 0, 0), 270, 200, 0, "GRAJ");
                al_draw_text(font, al_map_rgb(0, 0, 0), 60, 300, 0, "POZIOM TRUDNOSCI");
                al_draw_text(font, al_map_rgb(0, 0, 0), 220, 400, 0, "WYJSCIE");
                al_draw_bitmap(bitmap2, 820, 320, 0);
                al_flip_display();
            }

            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                return false;
            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP &&
                event.mouse.x >= 270 && event.mouse.x <= 270 + (al_get_text_width(font, "GRAJ")) &&
                event.mouse.y >= 200 && event.mouse.y <= 200 + al_get_font_line_height(font))
            {

                graj = true;
                menu = false;
            }
            else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP &&
                event.mouse.x >= 220 && event.mouse.x <= 320 &&
                event.mouse.y >= 400 && event.mouse.y <= 460)
            {
                return false;
            }
        }




        /*if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
         {
             x = event.mouse.x;
             y = event.mouse.y;
         }

         if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
         {
             x = y = 0;
             al_set_mouse_xy(display, 0, 0);
         }*/


         // keyboard

        if (graj) {
            al_start_timer(timer2);
            al_get_keyboard_state(&keyState);
            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                return false;
            if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
                if (al_key_down(&keyState, ALLEGRO_KEY_LCTRL))
                    x += 10;
                else
                {
                    x += 1;
                }

            if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
                if (al_key_down(&keyState, ALLEGRO_KEY_LCTRL))
                    x += -10;
                else
                {
                    x += -1;
                }
            if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))
                if (al_key_down(&keyState, ALLEGRO_KEY_LCTRL))
                    y += 10;
                else
                    y += 1;

            if (al_key_down(&keyState, ALLEGRO_KEY_UP))
                if (al_key_down(&keyState, ALLEGRO_KEY_LCTRL))
                    y += -10;
                else
                    y += -1;

            if (al_key_down(&keyState, ALLEGRO_KEY_SPACE))
            {

            }
                if (x > (al_get_display_width(display)) - (al_get_bitmap_width(bitmap)))
                x = (al_get_display_width(display)) - (al_get_bitmap_width(bitmap));
            if (x < 0)
                x = 0;

            if (y > (al_get_display_height(display)) - (al_get_bitmap_height(bitmap)))
                y = (al_get_display_height(display)) - (al_get_bitmap_height(bitmap));
            if (y < 0)
                y = 0;
            if (a - al_get_text_width(font, "KACPERUKUU NIE DENERWUJ SIE") >= al_get_display_width(display))
            {
                a = 0 - al_get_text_width(font, "KACPERUKUU NIE DENERWUJ SIE");
                b += 30;
            }





            if (event.type == ALLEGRO_EVENT_TIMER)
            {

                al_clear_to_color(al_map_rgba_f(1, 1, 1, 1));
                al_draw_text(font, al_map_rgb_f(255, 0, 0), a += 3, b, 0, "TOMECZKU NIE DENERWUJ SIE");

                for (int i = 0; i <= 3; i++)
                {

                    al_draw_bitmap(bitmap3, points[i] += M[i], d[i], 0);
                    if (points[i] + al_get_bitmap_width(bitmap3) >= al_get_display_width(display))
                    {
                        d[i] += 10;
                        M[i] += -2;
                    }

                    if (points[i] <= 0)
                    {
                        d[i] += 10;
                        M[i] += 2;
                    }

                }

                al_draw_bitmap(bitmap, x, y, 0);


                al_draw_bitmap(button, 170, 390, 0);
                al_draw_text(font, al_map_rgb(0, 0, 0), 220, 395, 0, "WYJSCIE");


                al_flip_display();


            }

            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP &&
                event.mouse.x >= 170 && event.mouse.x <= 170 + 200 &&
                event.mouse.y >= 390 && event.mouse.y <= 390 + 70)
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
    al_destroy_bitmap(bitmap);
    al_destroy_bitmap(bitmap3);

    return 0;
}