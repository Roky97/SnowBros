#include <iostream>
using namespace std;
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

void init();

int main(int argc, char **argv){
  init();
  int w,h;
  ALLEGRO_DISPLAY       *display = NULL;
  //ALLEGRO_DISPLAY_MODE   disp_data;
//  ALLEGRO_MONITOR_INFO info;
  // al_get_monitor_info(0, &info);
  // w = info.x2 - info.x1; /* Assume this is 1366 */
  // h = info.y2 - info.y1; /* Assume this is 768 */
  al_create_display(256, 224);

  //cout<<endl<<w<<" "<<h<<endl;
  // al_get_display_mode(al_get_num_display_modes() -1, &disp_data);

  al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
  display=al_create_display(w, h);

  //cout<<endl<<disp_data.width<<" "<<disp_data.height<<endl;
  al_clear_to_color(al_map_rgb(255,0,0));
  al_set_window_title(display, "SnowBros");



  al_destroy_display(display);




  return 0;
}

void init()
{
  al_init();
  al_init_image_addon();
  al_init_primitives_addon();
}
