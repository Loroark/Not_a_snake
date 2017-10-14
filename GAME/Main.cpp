#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

const int SZER = 640;
const int WYS = 480;

int main() {
    srand(time(NULL));
    al_init(); ///inicjalizacja biblioteki
    if(!al_init()){
        al_show_native_message_box(NULL, "ALLEGRO", "Allegro", "Nie uda�o si� zainicjalizowa� allegro!", NULL, NULL);
        fprintf(stderr, "Nie uda�o si� zainicjalizowa� allegro!");
        return -1;
    }
    al_init_primitives_addon(); /// inicjalizacja modu�u primitives (kszta�ty geometryczne)
    if(!al_init_primitives_addon()){
        al_show_native_message_box(NULL, "PRIMITIVES", "Primitives", "Nie uda�o si� zainicjalizowa� modu�u primitives!", NULL, NULL);
        fprintf(stderr, "Nie uda�o si� zainicjalizowa� modu�u primitives!");
        return -1;
    }
    al_init_font_addon(); /// inicjalizacja modu�u czcionek (font�w)
    al_init_ttf_addon(); /// inicjalizacja modu�u ttf (True Type Font)
    if(!al_init_ttf_addon()){
        al_show_native_message_box(NULL, "TTF", "Ttf", "Nie uda�o si� zainicjalizowa� modu�u ttf!", NULL, NULL);
        fprintf(stderr, "Nie uda�o si� zainicjalizowa� modu�u ttf!");
        return -1;
    }
    al_install_keyboard(); ///inicjalizacja klawiatury (potrzebne by jej u�y�)
    if(!al_install_keyboard()){
        al_show_native_message_box(NULL, "KLAWIATURA", "Klawiatura", "Nie uda�o si� zainicjalizowa� klawiatury!", NULL, NULL);
        fprintf(stderr, "Nie uda�o si� zainicjalizowa� klawiatury!");
        return -1;
    }
    ALLEGRO_DISPLAY *okno = al_create_display(SZER, WYS); ///wy�wietlanie okna !!wska�nik!!
    if(!okno){
        al_show_native_message_box(NULL, "OKNO", "Okno", "Nie uda�o si� zainicjalizowa� okna!", NULL, NULL);
        fprintf(stderr, "Nie uda�o si� zainicjalizowa� okna!");
        return -1;
    }
    ALLEGRO_FONT *czcionka = al_load_ttf_font("D:/CPP/GAME/bin/Debug/pirulen.ttf", 20, 0 );
    if(!czcionka){
        al_show_native_message_box(NULL, "FONT", "Font", "Nie uda�o si� za�adowa� czcionki", NULL, NULL);
        fprintf(stderr, "Nie uda�o si� za�adowa� czcionki");
        return -1;
    }
    ALLEGRO_KEYBOARD_STATE klawiatura; /// zmienna trzymaj�ca stan klawiatury
    int player_x = SZER / 2; /// �rodek k�ka
    int player_y = WYS / 2; /// �rodek k�ka
    int player_r = 15; /// promie� k�ka
    int points = 0;
    int best_points = 0;
    int dot_r = 5;
    int dot_x = dot_r + rand()%(SZER-dot_r-dot_r+1);
    int dot_y = dot_r + rand()%(WYS-dot_r-dot_r+1);
    /** k�ko odbija si� jak pi�eczka
    int dx = 1;
    int dy = 1;
    */

    do {
        al_clear_to_color(al_map_rgb_f(0.0, 1.0, 0.0)); /// malowanie t�a na kolor RGB
        al_draw_filled_circle(player_x, player_y, player_r, al_map_rgb_f(0.0, 0.0, 1.0)); ///rysowanie k�ka
        al_draw_filled_circle(dot_x, dot_y, dot_r, al_map_rgb_f(1.0, 0.0, 0.0));
        al_draw_textf(czcionka, al_map_rgb_f(0.0, 0.0, 0.0), 0, 0, NULL, "Points: %d", points);
        if(points > best_points){
            al_draw_textf(czcionka, al_map_rgb_f(0.0, 0.0, 0.0), 0, 20, NULL, "Best this run: %d", points);
        }else{
            al_draw_textf(czcionka, al_map_rgb_f(0.0, 0.0, 0.0), 0, 20, NULL, "Best this run: %d", best_points);
        }

        al_flip_display(); ///wy�wietlenie narysowanych do tej pory rzeczy

        if(((dot_x-player_x)*(dot_x-player_x) + (dot_y-player_y)*(dot_y-player_y)) <= (player_r*player_r)){
            points++;
            dot_x = dot_r + rand()%(SZER-dot_r-dot_r+1);
            dot_y = dot_r + rand()%(WYS-dot_r-dot_r+1);
        }

        al_get_keyboard_state(&klawiatura); ///sprawdzenie stanu klawiatury
        if(al_key_down(&klawiatura, ALLEGRO_KEY_RIGHT) && player_x + player_r < SZER){
            player_x++;
        }
        if(al_key_down(&klawiatura, ALLEGRO_KEY_LEFT) && player_x - player_r > 0){
            player_x--;
        }
        if(al_key_down(&klawiatura, ALLEGRO_KEY_DOWN) && player_y + player_r < WYS){
            player_y++;
        }
        if(al_key_down(&klawiatura, ALLEGRO_KEY_UP) && player_y - player_r > 0){
            player_y--;
        }
        if(al_key_down(&klawiatura, ALLEGRO_KEY_R)){
            player_x = SZER / 2;
            player_y = WYS / 2;
            dot_x = dot_r + rand()%(SZER-dot_r-dot_r+1);
            dot_y = dot_r + rand()%(WYS-dot_r-dot_r+1);
            if(points > best_points){
                best_points = points;
            }
            points = 0;
        }
        /** k�ko odbija si� jak pi�eczka cd
        player_x += dx;
        player_y += dy;
        if(player_x + player_r == SZER){
            dx = -1;
        }
        if(player_x - player_r == 0){
            dx = 1;
        }
        if(player_y + player_r == WYS){
            dy = -1;
        }
        if(player_y - player_r == 0){
            dy = 1;
        }
        */
        al_rest(0.001);
    } while (!al_key_down(&klawiatura, ALLEGRO_KEY_ESCAPE)); ///czy wci�ni�to ESC

    al_destroy_display(okno); ///zamykanie okna
}

