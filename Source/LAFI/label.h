#ifndef LAFI_LABEL_INCLUDED
#define LAFI_LABEL_INCLUDED

#include <string>

#include "widget.h"

using namespace std;

class lafi_label : public lafi_widget {
public:
    ALLEGRO_BITMAP* normal_bitmap;
    int text_flags;
    
    string text;
    
    lafi_label(int x1 = 0, int y1 = 0, int x2 = 1, int y2 = 1, string text = "", int text_flags = 0, lafi_style* style = NULL, unsigned char flags = 0);
    ~lafi_label();
    
    void render();
    void draw_self();
};

#endif //ifndef LAFI_LABEL_INCLUDED