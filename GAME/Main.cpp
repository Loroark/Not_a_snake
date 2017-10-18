#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

const int SZER = 1280;
const int WYS = 720;
const string VERSION = "BETA 1.4";

int main() {
    srand(time(NULL));
    al_init(); ///inicjalizacja biblioteki
    if(!al_init()){
        al_show_native_message_box(NULL, "ALLEGRO", "Allegro", "Nie udalo sie zainicjalizowac allegro!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        fprintf(stderr, "Nie udalo sie zainicjalizowac allegro!");
        return -1;
    }
    al_init_primitives_addon(); /// inicjalizacja modu³u primitives (kszta³ty geometryczne)
    if(!al_init_primitives_addon()){
        al_show_native_message_box(NULL, "PRIMITIVES", "Primitives", "Nie udalo sie zainicjalizowac modulu primitives!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        fprintf(stderr, "Nie udalo sie zainicjalizowac modulu primitives!");
        return -1;
    }
    al_init_font_addon(); /// inicjalizacja modu³u czcionek (fontów)
    ///nie mogê sprawdziæ czy siê poprawnie doda³ modu³ font :(
    al_init_ttf_addon(); /// inicjalizacja modu³u ttf (True Type Font)
    if(!al_init_ttf_addon()){
        al_show_native_message_box(NULL, "TTF", "Ttf", "Nie udalo sie zainicjalizowac modulu ttf!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        fprintf(stderr, "Nie udalo sie zainicjalizowac modulu ttf!");
        return -1;
    }
    al_install_keyboard(); ///inicjalizacja klawiatury (potrzebne by jej u¿yæ)
    if(!al_install_keyboard()){
        al_show_native_message_box(NULL, "KLAWIATURA", "Klawiatura", "Nie udalo sie zainicjalizowac klawiatury!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        fprintf(stderr, "Nie udalo sie zainicjalizowac klawiatury!");
        return -1;
    }
    al_init_image_addon();
    if(!al_init_image_addon()){
        al_show_native_message_box(NULL, "IMAGE", "Image", "Nie udalo sie zainicjalizowac modulu image!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        fprintf(stderr, "Nie udalo sie zainicjalizowac modulu image!");
        return -1;
    }
    ALLEGRO_DISPLAY *okno = al_create_display(SZER, WYS); ///wyœwietlanie okna !!wskaŸnik!!
    if(!okno){
        al_show_native_message_box(NULL, "OKNO", "Okno", "Nie udalo sie zainicjalizowac okna!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        fprintf(stderr, "Nie udalo sie zainicjalizowac okna!");
        return -1;
    }
    ALLEGRO_FONT *czcionka = al_load_ttf_font("D:/CPP/GAME/bin/Debug/pirulen.ttf", 20, 0 );
    if(!czcionka){
        al_show_native_message_box(NULL, "FONT", "Font", "Nie udalo sie zaladowac czcionki!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        fprintf(stderr, "Nie udalo sie zaladowac czcionki!");
        return -1;
    }
    ALLEGRO_KEYBOARD_STATE klawiatura; /// zmienna trzymaj¹ca stan klawiatury
    ALLEGRO_BITMAP *icon = al_load_bitmap("D:/CPP/GAME/bin/Debug/ikona.bmp");
    if(!icon){
        al_show_native_message_box(NULL, "IKONA", "Cos nie tak", "Nie udalo sie zaladowac ikony!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        fprintf(stderr, "Nie udalo sie zaladowac ikony!");
        return -1;
    }
    al_init_acodec_addon();
    if(!al_init_acodec_addon()){
        al_show_native_message_box(NULL, "ACODEC", "Acodec", "Nie udalo sie zainicjalizowac modulu acodec!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        fprintf(stderr, "Nie udalo sie zainicjalizowac modulu acodec!");
        return -1;
    }
    al_install_audio();
    if(!al_install_audio()){
        al_show_native_message_box(NULL, "AUDIO", "Audio", "Nie udalo sie zainstalowac audio!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        fprintf(stderr, "Nie udalo sie zainstalowac audio!");
        return -1;
    }
    ALLEGRO_SAMPLE *sample = al_load_sample("D:/CPP/GAME/bin/Debug/Not_a_snake.wav");
    al_reserve_samples(1);
    if (!al_reserve_samples(1)){
        al_show_native_message_box(NULL, "RESERVE", "Reserve", "Nie udalo sie zarezerwowac sample'a!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        fprintf(stderr, "Nie udalo sie zarezerwowac sample'a!");
        return -1;
   }
   if(!sample){
        al_show_native_message_box(NULL, "SAMPLE", "sample", "Nie udalo sie zaladowac sample'a!", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        fprintf(stderr, "Nie udalo sie zaladowac sample'a!");
        return -1;
   }
    al_play_sample(sample, 0.8, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);



    al_set_window_title(okno, "Not a snake");
    al_set_display_icon(okno, icon);
    int player_x = SZER / 2; /// œrodek kó³ka
    int player_y = WYS / 2; /// œrodek kó³ka
    int player_r = 50; /// promieñ kó³ka
    int points = 0;
    int best_points = 0;
    int dot_r = 10;
    int dot_x = dot_r + rand()%(SZER-dot_r-dot_r+1);
    int dot_y = (dot_r+60) + rand()%((WYS-dot_r-40)-(dot_r+60)+1);
    int bad_dot_r = 10;
    int bad_dot_x = bad_dot_r + rand()%(SZER-bad_dot_r-bad_dot_r+1);
    int bad_dot_y = (bad_dot_r+60) + rand()%((WYS-bad_dot_r-40)-(bad_dot_r+60)+1);
    int bad_dot2_x = bad_dot_r + rand()%(SZER-bad_dot_r-bad_dot_r+1);
    int bad_dot2_y = (bad_dot_r+60) + rand()%((WYS-bad_dot_r-40)-(bad_dot_r+60)+1);
    int multiplier = 1;
    bool language = 0;
    double wait = 0.0015;

    do {
        al_clear_to_color(al_map_rgb_f(0.4, 0.7, 0.7)); /// malowanie t³a na kolor RGB
        al_draw_filled_circle(player_x, player_y, player_r+1, al_map_rgb_f(0.0, 0.0, 1.0)); ///rysowanie kó³ka
        al_draw_filled_circle(player_x, player_y, player_r, al_map_rgb_f(0.0, 0.0, 1.0)); ///rysowanie kó³ka
        al_draw_filled_circle(dot_x, dot_y, dot_r+1, al_map_rgb_f(0.0, 0.0, 0.0));
        al_draw_filled_circle(dot_x, dot_y, dot_r, al_map_rgb_f(0.0, 1.0, 0.0));
        al_draw_filled_circle(bad_dot_x, bad_dot_y, bad_dot_r+1, al_map_rgb_f(0.0, 0.0, 0.0));
        al_draw_filled_circle(bad_dot2_x, bad_dot2_y, bad_dot_r+1, al_map_rgb_f(0.0, 0.0, 0.0));
        al_draw_filled_circle(bad_dot_x, bad_dot_y, bad_dot_r, al_map_rgb_f(1.0, 0.0, 0.0));
        al_draw_filled_circle(bad_dot2_x, bad_dot2_y, bad_dot_r, al_map_rgb_f(1.0, 0.0, 0.0));
        al_draw_line(0, 60, SZER, 60, al_map_rgb_f(0.0, 0.0, 0.0), 1.0);
        al_draw_line(0, WYS-40, SZER, WYS-40, al_map_rgb_f(0.0, 0.0, 0.0), 1.0);
        al_draw_filled_rectangle(0, 0, SZER, 60, al_map_rgb_f(0.0, 0.0, 0.0));
        al_draw_filled_rectangle(0, WYS, SZER, WYS-40, al_map_rgb_f(0.0, 0.0, 0.0));
        if(language == 0){
            al_draw_textf(czcionka, al_map_rgb_f(1.0, 1.0, .0), 0, 0, NULL, "Points: %d", points);
            al_draw_textf(czcionka, al_map_rgb_f(1.0, 1.0, 0.0), 0, 40, NULL, "Best this run: %d", best_points);
            al_draw_textf(czcionka, al_map_rgb_f(1.0, 1.0, 0.0), 0, WYS-40, NULL, "Press \"R\" to restart");
            al_draw_textf(czcionka, al_map_rgb_f(1.0, 1.0, 0.0), 0, WYS-20, NULL, "Press \"ESC\" to quit");
            al_draw_textf(czcionka, al_map_rgb_f(1.0, 1.0, 0.0), SZER-282, 0, NULL, "Press \"1\" for easy");
            al_draw_textf(czcionka, al_map_rgb_f(1.0, 1.0, 0.0), SZER-293, 20, NULL, "Press \"2\" for hard");
            al_draw_textf(czcionka, al_map_rgb_f(1.0, 1.0, 0.0), SZER-442, 40, NULL, "WARNING! Game will restart");
        }else if(language == 1){
            al_draw_textf(czcionka, al_map_rgb_f(1.0, 1.0, 0.0), 0, 0, NULL, "Punkty: %d", points);
            al_draw_textf(czcionka, al_map_rgb_f(1.0, 1.0, 0.0), 0, 40, NULL, "Najwiecej punktow: %d", best_points);
            al_draw_textf(czcionka, al_map_rgb_f(1.0, 1.0, 0.0), 0, WYS-40, NULL, "Wcisnij \"R\" by zrestartowac");
            al_draw_textf(czcionka, al_map_rgb_f(1.0, 1.0, 0.0), 0, WYS-20, NULL, "Wcisnij \"ESC\" by zakonczyc gre");
            al_draw_textf(czcionka, al_map_rgb_f(1.0, 1.0, 0.0), SZER-664, 0, NULL, "Wcisnij \"1\" dla latwego poziomu trudnosci");
            al_draw_textf(czcionka, al_map_rgb_f(1.0, 1.0, 0.0), SZER-693, 20, NULL, "Wcisnij \"2\" dla trudnego poziomu trudnosci");
            al_draw_textf(czcionka, al_map_rgb_f(1.0, 1.0, 0.0), SZER-607, 40, NULL, "UWAGA! Gra zostanie zrestartowana");
        }
        al_draw_textf(czcionka, al_map_rgb_f(1.0, 1.0, 0.0), SZER-497, WYS-40, NULL, "Wcisnij \"P\" dla jezyka Polskiego");
        al_draw_textf(czcionka, al_map_rgb_f(1.0, 1.0, 0.0), SZER-330, WYS-20, NULL, "Press \"E\" for English");



        if(((dot_x-player_x)*(dot_x-player_x) + (dot_y-player_y)*(dot_y-player_y)) <= (player_r*player_r)){
            points += multiplier;
            if(points > best_points){
                best_points = points;
            }
            dot_x = dot_r + rand()%(SZER-dot_r-dot_r+1);
            dot_y = (dot_r+60) + rand()%((WYS-dot_r-40)-(dot_r+60)+1);
        }
        if(((bad_dot_x-player_x)*(bad_dot_x-player_x) + (bad_dot_y-player_y)*(bad_dot_y-player_y)) <= (player_r*player_r)){
            points -= 2*multiplier;
            if(points > best_points){
                best_points = points;
            }
            bad_dot_x = bad_dot_r + rand()%(SZER-bad_dot_r-bad_dot_r+1);
            bad_dot_y = (bad_dot_r+60) + rand()%((WYS-bad_dot_r-40)-(bad_dot_r+60)+1);
            bad_dot2_x = bad_dot_r + rand()%(SZER-bad_dot_r-bad_dot_r+1);
            bad_dot2_y = (bad_dot_r+60) + rand()%((WYS-bad_dot_r-40)-(bad_dot_r+60)+1);
        }
        if(((bad_dot2_x-player_x)*(bad_dot2_x-player_x) + (bad_dot2_y-player_y)*(bad_dot2_y-player_y)) <= (player_r*player_r)){
            points -= 2*multiplier;
            if(points > best_points){
                best_points = points;
            }
            bad_dot_x = bad_dot_r + rand()%(SZER-bad_dot_r-bad_dot_r+1);
            bad_dot_y = (bad_dot_r+60) + rand()%((WYS-bad_dot_r-40)-(bad_dot_r+60)+1);
            bad_dot2_x = bad_dot_r + rand()%(SZER-bad_dot_r-bad_dot_r+1);
            bad_dot2_y = (bad_dot_r+60) + rand()%((WYS-bad_dot_r-40)-(bad_dot_r+60)+1);
        }

        al_get_keyboard_state(&klawiatura); ///sprawdzenie stanu klawiatury
        if(al_key_down(&klawiatura, ALLEGRO_KEY_RIGHT) && player_x + player_r < SZER){
            player_x++;
        }
        if(al_key_down(&klawiatura, ALLEGRO_KEY_LEFT) && player_x - player_r > 0){
            player_x--;
        }
        if(al_key_down(&klawiatura, ALLEGRO_KEY_DOWN) && player_y + player_r < WYS-40){
            player_y++;
        }
        if(al_key_down(&klawiatura, ALLEGRO_KEY_UP) && player_y - player_r > 60){
            player_y--;
        }
        if(al_key_down(&klawiatura, ALLEGRO_KEY_R)){
            player_x = SZER / 2;
            player_y = WYS / 2;
            dot_x = dot_r + rand()%(SZER-dot_r-dot_r+1);
            dot_y = (dot_r+60) + rand()%((WYS-dot_r-40)-(dot_r+60)+1);
            bad_dot_x = bad_dot_r + rand()%(SZER-bad_dot_r-bad_dot_r+1);
            bad_dot_y = (bad_dot_r+60) + rand()%((WYS-bad_dot_r-40)-(bad_dot_r+60)+1);
            bad_dot2_x = bad_dot_r + rand()%(SZER-bad_dot_r-bad_dot_r+1);
            bad_dot2_y = (bad_dot_r+60) + rand()%((WYS-bad_dot_r-40)-(bad_dot_r+60)+1);
            points = 0;
            al_rest(0.2);
        }
        if(al_key_down(&klawiatura, ALLEGRO_KEY_1)){
            player_x = SZER / 2;
            player_y = WYS / 2;
            dot_x = dot_r + rand()%(SZER-dot_r-dot_r+1);
            dot_y = (dot_r+60) + rand()%((WYS-dot_r-40)-(dot_r+60)+1);
            bad_dot_x = bad_dot_r + rand()%(SZER-bad_dot_r-bad_dot_r+1);
            bad_dot_y = (bad_dot_r+60) + rand()%((WYS-bad_dot_r-40)-(bad_dot_r+60)+1);
            bad_dot2_x = bad_dot_r + rand()%(SZER-bad_dot_r-bad_dot_r+1);
            bad_dot2_y = (bad_dot_r+60) + rand()%((WYS-bad_dot_r-40)-(bad_dot_r+60)+1);
            points = 0;
            player_r = 50;
            wait = 0.0015;
            multiplier = 1;
            dot_r = 10;
            bad_dot_r = 10;
            al_rest(0.2);
        }
        if(al_key_down(&klawiatura, ALLEGRO_KEY_2)){
            player_x = SZER / 2;
            player_y = WYS / 2;
            dot_x = dot_r + rand()%(SZER-dot_r-dot_r+1);
            dot_y = (dot_r+60) + rand()%((WYS-dot_r-40)-(dot_r+60)+1);
            bad_dot_x = bad_dot_r + rand()%(SZER-bad_dot_r-bad_dot_r+1);
            bad_dot_y = (bad_dot_r+60) + rand()%((WYS-bad_dot_r-40)-(bad_dot_r+60)+1);
            bad_dot2_x = bad_dot_r + rand()%(SZER-bad_dot_r-bad_dot_r+1);
            bad_dot2_y = (bad_dot_r+60) + rand()%((WYS-bad_dot_r-40)-(bad_dot_r+60)+1);
            points = 0;
            player_r = 15;
            wait = 0.001;
            multiplier = 3;
            dot_r = 5;
            al_rest(0.2);
        }
        if(al_key_down(&klawiatura, ALLEGRO_KEY_P)){
            language = 1;
        }
        if(al_key_down(&klawiatura, ALLEGRO_KEY_E)){
            language = 0;
        }
        al_flip_display(); ///wyœwietlenie narysowanych do tej pory rzeczy
        al_rest(wait);
    } while (!al_key_down(&klawiatura, ALLEGRO_KEY_ESCAPE)); ///czy wciœniêto ESC

    al_destroy_display(okno); ///zamykanie okna
}
