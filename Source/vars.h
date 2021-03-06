#ifndef VARS_INCLUDED
#define VARS_INCLUDED

#include <vector>
#include <map>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>

#include "animation.h"
#include "const.h"
#include "controls.h"
#include "hitbox.h"
#include "LAFI/gui.h"
#include "LAFI/label.h"
#include "leader.h"
#include "misc_structs.h"
#include "particle.h"
#include "pikmin.h"
#include "pikmin_type.h"
#include "spray_type.h"
#include "spec_objs/info_spot.h"
#include "spec_objs/nectar.h"
#include "spec_objs/onion.h"
#include "spec_objs/pellet.h"
#include "spec_objs/ship.h"
#include "status.h"
#include "treasure.h"
#include "weather.h"

using namespace std;

//Bitmaps.
extern ALLEGRO_BITMAP* bmp_blue[3];
extern ALLEGRO_BITMAP* bmp_blue_buried[3];
extern ALLEGRO_BITMAP* bmp_blue_idle[3];
extern ALLEGRO_BITMAP* bmp_blue_onion;
extern ALLEGRO_BITMAP* bmp_bubble;
extern ALLEGRO_BITMAP* bmp_cloaking_burrow_nit;
extern ALLEGRO_BITMAP* bmp_cursor;
extern ALLEGRO_BITMAP* bmp_day_bubble;
extern ALLEGRO_BITMAP* bmp_enemy_spirit;
extern ALLEGRO_BITMAP* bmp_hard_bubble;
extern ALLEGRO_BITMAP* bmp_icon;
extern ALLEGRO_BITMAP* bmp_idle_glow;
extern ALLEGRO_BITMAP* bmp_louie;
extern ALLEGRO_BITMAP* bmp_louie_lying;
extern ALLEGRO_BITMAP* bmp_message_box;
extern ALLEGRO_BITMAP* bmp_mouse_cursor;
extern ALLEGRO_BITMAP* bmp_mouse_cursor_invalid;
extern ALLEGRO_BITMAP* bmp_move_group_arrow;
extern ALLEGRO_BITMAP* bmp_nectar;
extern ALLEGRO_BITMAP* bmp_number_bubble;
extern ALLEGRO_BITMAP* bmp_olimar;
extern ALLEGRO_BITMAP* bmp_olimar_lying;
extern ALLEGRO_BITMAP* bmp_pikmin_spirit;
extern ALLEGRO_BITMAP* bmp_president;
extern ALLEGRO_BITMAP* bmp_president_lying;
extern ALLEGRO_BITMAP* bmp_purple[3];
extern ALLEGRO_BITMAP* bmp_red[3];
extern ALLEGRO_BITMAP* bmp_red_buried[3];
extern ALLEGRO_BITMAP* bmp_red_idle[3];
extern ALLEGRO_BITMAP* bmp_red_onion;
extern ALLEGRO_BITMAP* bmp_red_pellet[4];
extern ALLEGRO_BITMAP* bmp_shadow;
extern ALLEGRO_BITMAP* bmp_ship;
extern ALLEGRO_BITMAP* bmp_smoke;
extern ALLEGRO_BITMAP* bmp_sparkle;
extern ALLEGRO_BITMAP* bmp_sun;
extern ALLEGRO_BITMAP* bmp_sun_bubble;
extern ALLEGRO_BITMAP* bmp_tp;
extern ALLEGRO_BITMAP* bmp_ub_spray;
extern ALLEGRO_BITMAP* bmp_us_spray;
extern ALLEGRO_BITMAP* bmp_white[3];
extern ALLEGRO_BITMAP* bmp_yellow[3];
extern ALLEGRO_BITMAP* bmp_yellow_buried[3];
extern ALLEGRO_BITMAP* bmp_yellow_idle[3];
extern ALLEGRO_BITMAP* bmp_yellow_onion;

//Test things, temporary.
extern ALLEGRO_BITMAP* bmp_test;
extern sector test_sector;
extern vector<linedef> test_linedefs;

//Sound effects.
extern sample_struct sfx_attack;
extern sample_struct sfx_camera;
extern sample_struct sfx_dismiss;
extern sample_struct sfx_louie_whistle;
extern sample_struct sfx_louie_name_call;
extern sample_struct sfx_president_name_call;
extern sample_struct sfx_olimar_whistle;
extern sample_struct sfx_olimar_name_call;
extern sample_struct sfx_president_whistle;
extern sample_struct sfx_president_name_call;
extern sample_struct sfx_pikmin_attack;
extern sample_struct sfx_pikmin_called;
extern sample_struct sfx_pikmin_carrying;
extern sample_struct sfx_pikmin_carrying_grab;
extern sample_struct sfx_pikmin_dying;
extern sample_struct sfx_pikmin_held;
extern sample_struct sfx_pikmin_idle;
extern sample_struct sfx_pikmin_pluck;
extern sample_struct sfx_pikmin_plucked;
extern sample_struct sfx_pikmin_thrown;
extern sample_struct sfx_switch_pikmin;
extern sample_struct sfx_throw;

//General globals.
extern vector<vector<ALLEGRO_BITMAP*> >
area_images;
extern float                 area_x1;               //Top-left corner of the area, in world coordinates.
extern float                 area_y1;
extern float                 auto_pluck_input_time; //Time left until the player can press the pluck button again, to make the captain auto-pluck.
extern vector<unsigned int>  berries;
extern ALLEGRO_BITMAP*       bmp_error;
extern float                 cam_trans_pan_final_x;
extern float                 cam_trans_pan_final_y;
extern float                 cam_trans_pan_initial_x;
extern float                 cam_trans_pan_initial_y;
extern float                 cam_trans_pan_time_left;
extern float                 cam_trans_zoom_final_level;
extern float                 cam_trans_zoom_initial_level;
extern float                 cam_trans_zoom_time_left;
extern float                 cam_x;
extern float                 cam_y;
extern float                 cam_zoom;
extern vector<control_info>  controls;
extern mob*                  closest_party_member;
extern size_t                cur_leader_nr;
extern string                cur_message;
extern size_t                cur_message_char;
extern float                 cur_message_char_time;
extern size_t                cur_message_section;
extern ALLEGRO_BITMAP*       cur_message_speaker;
extern vector<size_t>        cur_message_stopping_chars; //The message stops scrolling when it reaches one of these characters.
extern unsigned char         cur_screen;
extern weather               cur_weather;              //Current weather.
extern float                 cursor_angle;
extern float                 cursor_save_time;         //Time left until the position of the cursor is saved on the vector.
extern float                 cursor_spin_angle;
extern vector<point>         cursor_spots;             //Spots the cursor has been through. Used for the faint trail left behind it.
extern float                 cursor_x;                 //Leader's cursor.
extern float                 cursor_y;
extern unsigned int          day;
extern float                 day_minutes;
extern float                 day_minutes_end;          //The day ends when the in-game minutes reach this value.
extern float                 day_minutes_per_irl_sec;  //Every real-life second, these many in-game minutes pass.
extern float                 day_minutes_start;        //The in-game minutes start with this value every day.
extern bool                  daylight_effect;
extern ALLEGRO_DISPLAY*      display;
extern map<string, animation> ed_anims;
extern animation*            ed_anim;
extern string                ed_anim_name;
extern bool                  ed_anim_playing;
extern size_t                ed_cur_frame_nr;
extern float                 ed_cur_frame_time;
extern float                 ed_cur_hitbox_angle;  //Angle of rotation of the current hitbox' outline.
extern size_t                ed_cur_hitbox_nr;     //string::npos = none.
extern size_t                ed_grabbing_hitbox;   //Hitbox being grabbed by the mouse cursor. string::npos = none.
extern bool                  ed_grabbing_hitbox_edge;
extern float                 ed_grabbing_hitbox_x; //X world coordinate of the point we're grabbing, or the anchor, when in resize mode.
extern float                 ed_grabbing_hitbox_y;
extern lafi_gui*             ed_gui;
extern lafi_label*           ed_gui_status_bar;
extern bool                  ed_hitboxes_visible;
extern bool                  ed_holding_m2;
extern unsigned char         ed_mode;
extern float                 ed_new_hitbox_corner_x; //FLT_MAX = none.
extern float                 ed_new_hitbox_corner_y;
extern map<string, enemy_type*>
enemy_types;
extern vector<enemy*>        enemies;
extern ALLEGRO_FONT*         font;
extern ALLEGRO_FONT*         font_area_name;
extern ALLEGRO_FONT*         font_counter;
extern unsigned int          font_counter_h;
extern unsigned int          font_h;
extern ALLEGRO_FONT*         font_value;             //Font for the carrying / money values.
extern unsigned char         game_fps;
extern vector<vector<float> >
group_spots_x;
extern vector<vector<float> >
group_spots_y;
extern float                 idle_glow_angle;
extern mob_type*             info_spot_mob_type;
extern vector<info_spot*>    info_spots;
extern map<ALLEGRO_JOYSTICK*, int>
joystick_numbers;
extern vector<leader*>       leaders;
extern float                 leader_move_x;              //How hard the joystick is pressed in the X axis ([-1, 1]).
extern float                 leader_move_y;
extern map<string, leader_type*>
leader_types;
extern unsigned              max_pikmin_in_field;
extern ALLEGRO_MIXER*        mixer;
extern vector<mob*>          mobs;
extern float                 mouse_cursor_x;             //The physical mouse's cursor.
extern float                 mouse_cursor_y;
extern float                 mouse_cursor_speed_x;
extern float                 mouse_cursor_speed_y;
extern bool                  mouse_cursor_valid;
extern bool                  mouse_moves_cursor[4];
extern vector<float>         move_group_arrows;          //Distance of the arrows that appear when the "move group to cursor" button is held.
extern float                 move_group_next_arrow_time; //Time remaining until the next arrow on the "move group arrows" appears.
extern float                 moving_group_angle;
extern float                 moving_group_intensity;     //General intensity of the group move in the specified angle.
extern float                 moving_group_pos_x;         //Intensity on the X coordinate, used for analog stick movement. Basically, position of the analog stick.
extern float                 moving_group_pos_y;
extern bool                  moving_group_to_cursor;     //Is the "move group to cursor" button being pressed?
extern mob_type*             nectar_mob_type;
extern vector<nectar*>       nectars;
extern map<string, onion_type*>
onion_types;
extern vector<onion*>        onions;
extern unsigned char         particle_quality;
extern vector<particle>      particles;
extern bool                  paused;
extern map<string, pellet_type*>
pellet_types;
extern vector<pellet*>       pellets;
extern vector<point>         percipitation;
extern float                 percipitation_time_left;
extern map<pikmin_type*, unsigned long>
pikmin_in_onions;
extern vector<pikmin*>       pikmin_list;
extern map<string, pikmin_type*>
pikmin_types;
extern bool                  pretty_whistle;              //If true, the whistle radius is merely drawn as a circle. Used to improve performance.
extern float                 prev_moving_group_intensity; //The group move intensity on the previous frame. Used to figure out if, on 0-intensity, we should put the group's center near the leader or let it go there by itself.
extern bool                  running;
extern unsigned short        scr_h;
extern unsigned short        scr_w;
extern vector<sector>        sectors;
extern unsigned int          selected_spray;
extern unsigned char         ship_beam_ring_color[3];
extern bool                  ship_beam_ring_color_up[3];
extern mob_type*             ship_mob_type;
extern vector<ship*>         ships;
extern bool                  smooth_scaling;     //If false, images that are scaled up and down will look pixelated.
extern vector<unsigned long> spray_amounts;      //How many of each spray the player has.
extern vector<spray_type>    spray_types;
extern vector<status>        statuses;
extern float                 sun_meter_sun_angle;
extern float                 throw_particle_timer;
extern string                total_error_log;
extern map<string, treasure_type*>
treasure_types;
extern vector<treasure*>     treasures;
extern ALLEGRO_VOICE*        voice;  //Voice from which the sound effects play.
extern map<string, weather>  weather_conditions;
extern float                 whistle_dot_offset;    //How much each dot of the whistle should spin.
extern float                 whistle_dot_radius[6]; //Radius of every 6th dot.
extern float                 whistle_fade_radius;   //Radius the whistle was at pre-fade.
extern float                 whistle_fade_time;     //Time left for the whistle's fading animations.
extern float                 whistle_max_hold;      //The whistle area is at max size. Hold the whistle for these many seconds.
extern float                 whistle_next_dot_time;
extern float                 whistle_next_ring_time;
extern float                 whistle_radius;
extern vector<unsigned char> whistle_ring_colors;
extern unsigned char         whistle_ring_prev_color;
extern vector<float>         whistle_rings;
extern bool                  whistling;             //Is the whistle currently being blown?

#endif //ifndef VARS_INCLUDED