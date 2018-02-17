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

  // ALLEGRO_DISPLAY       *display = NULL;
  // ALLEGRO_DISPLAY_MODE   disp_data;
  //
  // al_get_display_mode(al_get_num_display_modes() -1, &disp_data);
  //
  // al_set_new_display_flags(ALLEGRO_FULLSCREEN);
  //
  // display=al_create_display(disp_data.width, disp_data.height);
  //
  // //cout<<endl<<disp_data.width<<" "<<disp_data.height<<endl;
  // al_clear_to_color(al_map_rgb(255,0,0));
  // al_flip_display();
  // // al_rest(1);
  // al_rest(3);
  // al_destroy_display(display);




  return 0;
}

void init()
{
  al_init();
  al_init_image_addon();
  al_init_primitives_addon();
}
