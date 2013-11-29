//ToDo there are a lot of times where I do, for instance, leaders[cur_leader_nr]->, replace this with a pointer for perfomance.

#pragma warning(disable : 4996) //Disables warning about localtime being deprecated.

#include <fstream>
#include <math.h>
#include <string>
#include <typeinfo>

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "const.h"
#include "controls.h"
#include "drawing.h"
#include "functions.h"
#include "logic.h"
#include "vars.h"

using namespace std;

int main() {
    //Install Allegro and initialize modules.
    al_init();
    al_install_mouse();
    al_install_keyboard();
    al_install_audio();
    al_install_joystick();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_acodec_addon();
    
    //Options and default controls.
    controls.push_back(control_info(BUTTON_PUNCH, 0, "mb_1"));
    controls.push_back(control_info(BUTTON_WHISTLE, 0, "mb_2"));
    controls.push_back(control_info(BUTTON_MOVE_RIGHT, 0, "k_4"));
    controls.push_back(control_info(BUTTON_MOVE_UP, 0, "k_23"));
    controls.push_back(control_info(BUTTON_MOVE_LEFT, 0, "k_1"));
    controls.push_back(control_info(BUTTON_MOVE_DOWN, 0, "k_19"));
    controls.push_back(control_info(BUTTON_MOVE_GROUP_TO_CURSOR, 0, "k_75"));
    controls.push_back(control_info(BUTTON_SWITCH_CAPTAIN_RIGHT, 0, "k_64"));
    controls.push_back(control_info(BUTTON_DISMISS, 0, "k_217"));
    controls.push_back(control_info(BUTTON_USE_SPRAY_1, 0, "k_18"));
    controls.push_back(control_info(BUTTON_USE_SPRAY_2, 0, "k_6"));
    controls.push_back(control_info(BUTTON_USE_SPRAY, 0, "k_18"));
    controls.push_back(control_info(BUTTON_SWITCH_SPRAY_RIGHT, 0, "k_5"));
    controls.push_back(control_info(BUTTON_SWITCH_SPRAY_LEFT, 0, "k_17"));
    controls.push_back(control_info(BUTTON_SWITCH_TYPE_RIGHT, 0, "mb_2"));
    controls.push_back(control_info(BUTTON_SWITCH_ZOOM, 0, "k_3"));
    controls.push_back(control_info(BUTTON_ZOOM_IN, 0, "mwu"));
    controls.push_back(control_info(BUTTON_ZOOM_OUT, 0, "mwd"));
    controls.push_back(control_info(BUTTON_LIE_DOWN, 0, "k_26"));
    controls.push_back(control_info(BUTTON_PAUSE, 0, "k_59"));
    load_options();
    save_options();
    
    //Event stuff.
    ALLEGRO_DISPLAY* display = al_create_display(scr_w, scr_h);
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / game_fps);
    
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_joystick_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    ALLEGRO_EVENT ev;
    
    //Other initial things.
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);
    al_set_window_title(display, "Pikmin fangame engine");
    al_hide_mouse_cursor(display);
    if(smooth_scaling) al_set_new_bitmap_flags(ALLEGRO_MAG_LINEAR | ALLEGRO_MIN_LINEAR | ALLEGRO_MIPMAP);
    al_reserve_samples(16);
    srand(time(NULL));
    
    //Error bitmap.
    //ToDo move this somewhere else, maybe?
    int bmp_error_w, bmp_error_h;
    al_get_text_dimensions(al_create_builtin_font(), "ERROR", NULL, NULL, &bmp_error_w, &bmp_error_h);
    bmp_error = al_create_bitmap(bmp_error_w, bmp_error_h);
    al_set_target_bitmap(bmp_error); {
        al_draw_text(al_create_builtin_font(), al_map_rgb(255, 0, 0), 0, 0, 0, "ERROR");
    } al_set_target_backbuffer(display);
    
    //Graphics.
    bmp_olimar = load_bmp("Olimar.png");
    bmp_louie = load_bmp("Louie.png");
    bmp_president = load_bmp("President.png");
    for(unsigned char m = 0; m < 3; m++) {
        string maturity_str;
        if(m == 0) maturity_str = "leaf";
        else if(m == 1) maturity_str = "bud";
        else maturity_str = "flower";
        bmp_red[m] = load_bmp(("Red_" + maturity_str + ".png").c_str());
        bmp_yellow[m] = load_bmp(("Yellow_" + maturity_str + ".png").c_str());
        bmp_blue[m] = load_bmp(("Blue_" + maturity_str + ".png").c_str());
        bmp_red_burrowed[m] = load_bmp(("Red_burrowed_" + maturity_str + ".png").c_str());
        bmp_yellow_burrowed[m] = load_bmp(("Yellow_burrowed_" + maturity_str + ".png").c_str());
        bmp_blue_burrowed[m] = load_bmp(("Blue_burrowed_" + maturity_str + ".png").c_str());
        bmp_red_idle[m] = load_bmp(("Red_idle_" + maturity_str + ".png").c_str());
        bmp_yellow_idle[m] = load_bmp(("Yellow_idle_" + maturity_str + ".png").c_str());
        bmp_blue_idle[m] = load_bmp(("Blue_idle_" + maturity_str + ".png").c_str());
    }
    bmp_red_onion = load_bmp("Red_onion.png");
    bmp_yellow_onion = load_bmp("Yellow_onion.png");
    bmp_blue_onion = load_bmp("Blue_onion.png");
    bmp_cursor = load_bmp("Cursor.png");
    bmp_mouse_cursor = load_bmp("Mouse_cursor.png");
    bmp_background = load_bmp("Background.png");
    bmp_bubble = load_bmp("Bubble.png");
    bmp_day_bubble = load_bmp("Day_bubble.png");
    bmp_health_bubble = load_bmp("Health_bubble.png");
    bmp_sun = load_bmp("Sun.png");
    bmp_shadow = load_bmp("Shadow.png");
    bmp_ship = load_bmp("Ship.png");
    bmp_idle_glow = load_bmp("Idle_glow.png");
    bmp_ub_spray = load_bmp("Ultra-bitter_spray.png");
    bmp_us_spray = load_bmp("Ultra-spicy_spray.png");
    bmp_move_group_arrow = load_bmp("Move_group_arrow.png");
    bmp_test = load_bmp("Test.png");
    bmp_nectar = load_bmp("Nectar.png");
    bmp_icon = load_bmp("Icon.png");
    bmp_red_pellet[0] = load_bmp("Red_1_pellet.png");
    bmp_red_pellet[1] = load_bmp("Red_5_pellet.png");
    bmp_red_pellet[2] = load_bmp("Red_10_pellet.png");
    bmp_red_pellet[3] = load_bmp("Red_20_pellet.png");
    bmp_olimar_lying = load_bmp("Olimar_lying.png");
    bmp_louie_lying = load_bmp("Louie_lying.png");
    bmp_president_lying = load_bmp("President_lying.png");
    
    int font_ranges[] = {
        0x0020, 0x007F, //ASCII
    };
    
    ALLEGRO_BITMAP* temp_font_bitmap = load_bmp("Font.png");  //We can't load the font directly because we want to set the ranges.
    if(temp_font_bitmap) font = al_grab_font_from_bitmap(temp_font_bitmap, 1, font_ranges);
    temp_font_bitmap = load_bmp("Area_name_font.png");
    if(temp_font_bitmap) font_area_name = al_grab_font_from_bitmap(temp_font_bitmap, 1, font_ranges);
    al_destroy_bitmap(temp_font_bitmap);
    font_h = al_get_font_line_height(font);
    
    //Sound effects.
    sfx_pikmin_held = load_sample("Pikmin_held.ogg");
    sfx_pikmin_thrown = load_sample("Pikmin_thrown.ogg");
    sfx_pikmin_plucked = load_sample("Pikmin_plucked.ogg");
    sfx_pikmin_called = load_sample("Pikmin_called.ogg");
    sfx_dismiss = load_sample("Dismiss.ogg");
    sfx_olimar_whistle = load_sample("Olimar_whistle.ogg");
    sfx_louie_whistle = load_sample("Louie_whistle.ogg");
    sfx_president_whistle = load_sample("President_whistle.ogg");
    sfx_olimar_name_call = load_sample("Olimar_name_call.ogg");
    sfx_louie_name_call = load_sample("Louie_name_call.ogg");
    sfx_president_name_call = load_sample("President_name_call.ogg");
    sfx_throw = load_sample("Throw.ogg");
    sfx_camera = load_sample("Camera.ogg");
    
    //Game content.
    load_game_content();
    
    //Initializing game things.
    sprays.clear();
    size_t n_spray_types = spray_types.size();
    for(size_t s = 0; s < n_spray_types; s++) { sprays.push_back(0); }
    pikmin_in_onions.clear();
    size_t n_total_types = pikmin_types.size();
    for(size_t t = 0; t < n_total_types; t++) { pikmin_in_onions[&pikmin_types[t]] = 0; }
    
    //Some temp variables.
    sector s = sector();
    /*test_sector = sector();
    test_sector.floors[0].z = 100;
    test_sector.floors[0].texture = bmp_test;
    
    test_linedefs.push_back(linedef(0, 0, 0, 0, 0, 0));
    test_linedefs.push_back(linedef(100, 0, 0, 0, 0, 0));
    test_linedefs.push_back(linedef(100, 100, 0, 0, 0, 0));
    test_linedefs.push_back(linedef(50, 150, 0, 0, 0, 0));
    test_linedefs.push_back(linedef(0, 100, 0, 0, 0, 0));*/
    
    load_area("test");
    generate_area_images();
    
    create_mob(new leader(0, 0, &s));
    leaders.back()->main_color = al_map_rgb(255, 0, 0);
    leaders.back()->health = 10;
    leaders.back()->sfx_dismiss = sfx_dismiss;
    leaders.back()->sfx_whistle = sfx_olimar_whistle;
    leaders.back()->sfx_name_call = sfx_olimar_name_call;
    create_mob(new leader(300, 250, &s));
    leaders.back()->main_color = al_map_rgb(0, 0, 255);
    leaders.back()->health = 8;
    leaders.back()->sfx_dismiss = sfx_dismiss;
    leaders.back()->sfx_whistle = sfx_louie_whistle;
    leaders.back()->sfx_name_call = sfx_louie_name_call;
    create_mob(new leader(350, 200, &s));
    leaders.back()->main_color = al_map_rgb(0, 0, 255);
    leaders.back()->health = 6;
    leaders.back()->sfx_dismiss = sfx_dismiss;
    leaders.back()->sfx_whistle = sfx_president_whistle;
    leaders.back()->sfx_name_call = sfx_president_name_call;
    create_mob(new treasure(300, 150, 80, &s, 30, 50));
    create_mob(new pikmin(&pikmin_types[0], 30, 30, &s));
    pikmin_list.back()->maturity = 1;
    create_mob(new pikmin(&pikmin_types[0], 40, 30, &s));
    pikmin_list.back()->maturity = 2;
    create_mob(new pikmin(&pikmin_types[1], 50, 30, &s));
    pikmin_list.back()->maturity = 1;
    create_mob(new pikmin(&pikmin_types[1], 60, 30, &s));
    pikmin_list.back()->maturity = 2;
    create_mob(new pikmin(&pikmin_types[2], 70, 30, &s));
    pikmin_list.back()->maturity = 1;
    create_mob(new pikmin(&pikmin_types[2], 80, 30, &s));
    pikmin_list.back()->maturity = 2;
    create_mob(new pikmin(&pikmin_types[0], 30, 200, &s));
    pikmin_list.back()->burrowed = true;
    create_mob(new pikmin(&pikmin_types[1], 50, 200, &s));
    pikmin_list.back()->burrowed = true;
    create_mob(new pikmin(&pikmin_types[2], 70, 200, &s));
    pikmin_list.back()->burrowed = true;
    for(unsigned char p = 0; p < 10; p++) {
        for(unsigned char t = 0; t < 3; t++) {
            create_mob(new pikmin(&pikmin_types[t], 100 + 10 * p + 3 * t, 30, &s));
        }
    }
    //create_mob(new pikmin(&pikmin_types[3], -50, -50, &s));
    //create_mob(new pikmin(&pikmin_types[4], -50, -70, &s));
    create_mob(new onion(400, 100, &s, &pikmin_types[0]));
    create_mob(new onion(400, 200, &s, &pikmin_types[1]));
    create_mob(new onion(400, 300, &s, &pikmin_types[2]));
    create_mob(new info_spot(300, 0, &s, "Treasure.", false, font));
    create_mob(new info_spot(400, 0, &s, "Onions.", false, font));
    create_mob(new nectar(0, 400, &s));
    sprays[0] = sprays[1] = 10;
    spray_types[0].bmp_spray = bmp_ub_spray;
    spray_types[1].bmp_spray = bmp_us_spray;
    pikmin_in_onions[&pikmin_types[0]] = 200;
    pikmin_in_onions[&pikmin_types[1]] = 180;
    pikmin_in_onions[&pikmin_types[2]] = 160;
    create_mob(new ship(-100, 100, &s));
    create_mob(new pellet(320, -100, &s, &pellet_types[0], &pikmin_types[0]));
    create_mob(new pellet(250, -100, &s, &pellet_types[1], &pikmin_types[0]));
    create_mob(new pellet(150, -100, &s, &pellet_types[2], &pikmin_types[0]));
    create_mob(new pellet(0, -100, &s, &pellet_types[3], &pikmin_types[0]));
    
    al_set_display_icon(display, bmp_icon);
    
    //Main loop.
    al_start_timer(timer);
    while(running) {
    
        /*  ************************************************
          *** | _ |                                  | _ | ***
        *****  \_/           EVENT HANDLING           \_/  *****
          *** +---+                                  +---+ ***
            ************************************************/
        
        al_wait_for_event(queue, &ev);
        
        handle_controls(ev);
        
        if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
            
        } else if(ev.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
            //scr_w = ev.display.width;
            //scr_h = ev.display.height;
            
        } else if(ev.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(queue)) {
        
            do_logic();
            do_drawing();
        }
    }
    
    //Quit.
    if(total_error_log.size()) {
        time_t tt;
        time(&tt);
        struct tm t = *localtime(&tt);
        total_error_log =
            to_string((long long) t.tm_year + 1900) + "/" +
            to_string((long long) t.tm_mon + 1) + "/" +
            to_string((long long) t.tm_mday) + " " +
            to_string((long long) t.tm_hour) + ":" +
            to_string((long long) t.tm_min) + ":" +
            to_string((long long) t.tm_sec) +
            "\n" + total_error_log;
            
        string prev_error_log;
        string line;
        
        ifstream error_log_file_i("Error_log.txt");
        if(error_log_file_i.is_open()) {
            while(!error_log_file_i.eof()) {
                getline(error_log_file_i, line);
                prev_error_log += line + "\n";
            }
            prev_error_log.erase(prev_error_log.size() - 1);
            error_log_file_i.close();
        }
        
        ofstream error_log_file_o("Error_log.txt");
        if(error_log_file_o.is_open()) {
            error_log_file_o << total_error_log << "\n" << prev_error_log;
            error_log_file_o.close();
        }
        
    }
}
