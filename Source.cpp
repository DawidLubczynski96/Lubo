#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_image.h>
#include "Header.h"

//GLOBAL=============================
const int WIDTH = 500;
const int HEIGHT = 700;
enum KEYS { LEFT, RIGHT };
bool keys[2] = { false, false };


//prototypes
void InitLudek(Spadochroniarz &ludek);
void DrawLudek(Spadochroniarz &ludek);
void MoveLudekLeft(Spadochroniarz &ludek);
void MoveLudekRight(Spadochroniarz &ludek);


int main(void)
{
	//primitive variables
	bool done = false;
	bool redraw = true;
	const int FPS = 60;

	int pos_x = WIDTH / 2;
	int pos_y = HEIGHT / 2 - 175;

	//int ludWidth = 0;
	//int ludHeight = 0;

	//object variables
	Spadochroniarz ludek;

	//Allegro variables
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	//ALLEGRO_BITMAP *lud = NULL;
	

	//Initialization Functions
	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if (!display)										//test display object
		return -1;

	//if (!lud)											//sprawdzenie bitmapy
	//	return -1;

	al_init_primitives_addon();
	al_install_keyboard();
	al_init_font_addon();
	al_init_ttf_addon();
	//al_init_image_addon();

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / FPS);
	
	//lud = al_load_bitmap("spadochroniarz.bmp");

	//ludWidth = al_get_bitmap_width(lud);
	//ludHeight = al_get_bitmap_height(lud);


	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_start_timer(timer);
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			redraw = true;

			if (keys[LEFT])
				MoveLudekLeft(ludek);
			if (keys[RIGHT])
				MoveLudekRight(ludek);
		}

		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)			//zamykanie gry krzyzykiem
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = false;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			}
		}
		/*if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
		}*/

		//zmiana pozycji keys = 1 jesli mamy klawisz wcisniety (1*10=10) przesuwa o 10 pikseli
		//jesli keysup=0 wtedy 0*10 nie przesuwa 
		pos_x -= keys[LEFT] * 10;
		pos_x += keys[RIGHT] * 10;

		al_draw_filled_rectangle(pos_x, pos_y, pos_x + 30, pos_y + 30, al_map_rgb(255, 0, 255));
		//al_draw_bitmap(lud, WIDTH / 2 - ludWidth / 2, HEIGHT / 2 - ludHeight / 2, 0);

		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	
	
	//al_destroy_bitmap(lud);
	al_destroy_display(display);						//destroy our display object
	
	return 0;
}

void InitLudek(Spadochroniarz &ludek)
{
	ludek.x = WIDTH / 2;
	ludek.y = 100;
	ludek.ID = GRACZ;
	ludek.lives = 5;
	ludek.speed = 7;
	ludek.boundx = 6;
	ludek.boundy = 6;
	ludek.score = 0;
}
/*void DrawLudek(Spadochroniarz &ludek)
{
	al_draw_bitmap(lud, WIDTH / 2 - ludWidth / 2, HEIGHT / 2 - ludHeight / 2, 0);
}*/

void MoveLudekLeft(Spadochroniarz &ludek)
{
	ludek.x -= ludek.speed;
	if (ludek.x < 0)
		ludek.x = 0;
}
void MoveLudekRight(Spadochroniarz &ludek)
{
	ludek.x += ludek.speed;
	if (ludek.x > 0)
		ludek.x = 0;
}