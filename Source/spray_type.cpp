#include "spray_type.h"

spray_type::spray_type(status* effect, bool burpable, float duration, ALLEGRO_COLOR main_color, ALLEGRO_BITMAP* bmp_spray, ALLEGRO_BITMAP* bmp_berry, bool can_drop_blobs, unsigned int berries_needed) {
    this->effect = effect;
    this->burpable = burpable;
    this->duration = duration;
    this->main_color = main_color;
    this->bmp_spray = bmp_spray;
    this->bmp_berry = bmp_berry;
    this->berries_needed = berries_needed;
    this->can_drop_blobs = can_drop_blobs;
}