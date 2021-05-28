#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_video.h>
#include <math.h>

#define LOG_ENABLED

/* Constants */
const int FPS = 60;
const int SCREEN_W = 800;
const int SCREEN_H = 600;
const int RESERVE_SAMPLES = 10;   // At most 10 audios can be played at a time.
enum {
	SCENE_MENU = 1,
	SCENE_SETTINGS = 2,
	SCENE_START = 3,
	SCENE_TRANS1 = 4,
	SCENE_TRANS2 = 5,
	SCENE_BOSS = 6,
	SCENE_ENDING = 7,
	SCENE_TEMP = 10
};

/* Input states */
int active_scene;   // The active scene id.
bool key_state[ALLEGRO_KEY_MAX];
bool *mouse_state;
int mouse_x, mouse_y;
// TODO: More variables to store input states such as joysticks, ...

/* Variables for allegro basic routines. */
ALLEGRO_DISPLAY* game_display;
ALLEGRO_EVENT_QUEUE* game_event_queue;
ALLEGRO_TIMER* game_update_timer;

/* Shared resources*/
ALLEGRO_FONT* font_aot_64;
ALLEGRO_FONT* font_aot_32;
ALLEGRO_FONT* font_aot_20;
ALLEGRO_FONT* font_normal;

/* Menu Scene resources*/
ALLEGRO_BITMAP* menu_img_background;
ALLEGRO_SAMPLE* menu_bgm;
ALLEGRO_SAMPLE_ID menu_bgm_id;

ALLEGRO_BITMAP* img_setting_icon;
ALLEGRO_BITMAP* img_setting_icon_on;
ALLEGRO_BITMAP* img_setting_background;

/* setting scene resourses*/
ALLEGRO_BITMAP *setting_img_background;
ALLEGRO_BITMAP *setting_img_eren;
ALLEGRO_BITMAP *setting_img_eren_on;
ALLEGRO_BITMAP *setting_img_levi;
ALLEGRO_BITMAP *setting_img_levi_on;

/* Start Scene resources*/
ALLEGRO_BITMAP* start_img_background;
ALLEGRO_BITMAP* start_img_eren;
ALLEGRO_BITMAP* start_img_levi;
ALLEGRO_BITMAP* start_img_enemy;
ALLEGRO_SAMPLE* start_bgm;
ALLEGRO_SAMPLE_ID start_bgm_id;

ALLEGRO_BITMAP* img_punch;
ALLEGRO_BITMAP* img_armorFist;
ALLEGRO_BITMAP* img_ult;

/* Trans Scene resourses */
ALLEGRO_BITMAP* trans_victory_img_background;
ALLEGRO_BITMAP* trans_victory_img_background2;
ALLEGRO_SAMPLE* trans_victory_bgm;
ALLEGRO_SAMPLE_ID trans_victory_bgm_id;
ALLEGRO_BITMAP* trans_defeat_img_background;
ALLEGRO_SAMPLE* trans_defeat_bgm;
ALLEGRO_SAMPLE_ID trans_defeat_bgm_id;

/* Boss Scene resourses */
ALLEGRO_BITMAP* boss_img_background;
ALLEGRO_BITMAP* boss_img_boss;
ALLEGRO_BITMAP* boss_img_fire;
ALLEGRO_SAMPLE* boss_bgm;
ALLEGRO_SAMPLE_ID boss_bgm_id;

/* End scene resourses*/
ALLEGRO_BITMAP* end_eren_img_background;
ALLEGRO_BITMAP* end_armin_img_background;
ALLEGRO_BITMAP* end_reiner_img_background;

typedef struct {
	float x, y;
	float w, h;
	float vx, vy;
	bool hidden;	// Should we draw this object on the screen.
	ALLEGRO_BITMAP* img; // The pointer to the objects image.
} MovableObject;


#define MAX_ENEMY 10
#define MAX_PUNCH 5
#define MAX_FIRE 20
#define MAX_BOSSHP 99999
MovableObject character;
MovableObject punches[MAX_PUNCH];
MovableObject reiner[MAX_ENEMY];
MovableObject armorFists[MAX_ENEMY];
MovableObject boss;
MovableObject fire[MAX_FIRE];
MovableObject armin;

int character_id = 1;
int score;
int heart = 5;
int bossHP = MAX_BOSSHP;
const float CD_PUNCH = 0.2f;
const float CD_ARMORFIST = 0.5;
const float CD_FIRE = 0.5;
const float CD_ULT = 2;
double last_punch;
double last_armorFist;
double last_fire;
double last_ult;


/* Declare function prototypes. */
void allegro5_init(void);
// Initialize variables and resources.
// Allows the game to perform any initialization it needs before starting to run.
void game_init(void);
// Process events inside the event queue using an infinity loop.
void game_start_event_loop(void);
// Run game logic such as updating the world, checking for collision, switching scenes and so on.
// This is called when the game should update its logic.
void game_update(void);
// Draw to display.
// This is called when the game should draw itself.
void game_draw(void);
// Release resources.
// Free the pointers we allocated.
void game_destroy(void);
// Function to change from one scene to another.
void game_change_scene(int next_scene);


// Load resized bitmap and check if failed.
ALLEGRO_BITMAP *load_bitmap_resized(const char *filename, int w, int h);
void draw_movable_object(MovableObject obj);
// Collision detect
bool pnt_in_rect(int x, int y, int pic_x, int pic_y, int pic_w, int pic_h);
bool obj_collision(MovableObject obj1, MovableObject obj2);
// Event callbacks.
void on_key_down(int keycode);
void on_mouse_down(int btn, int x, int y);


/* Declare function prototypes for debugging. */

// Display error message and exit the program, used like 'printf'.
// Write formatted output to stdout and file from the format string.
// If the program crashes unexpectedly, you can inspect "log.txt" for
// further information.
void game_abort(const char* format, ...);
// Log events for later debugging, used like 'printf'.
// Write formatted output to stdout and file from the format string.
// You can inspect "log.txt" for logs in the last run.
void game_log(const char* format, ...);
// Log using va_list.
void game_vlog(const char* format, va_list arg);

int main(int argc, char** argv) {
	// Set random seed for better random outcome.
	srand(time(NULL));
	allegro5_init();
	game_log("Allegro5 initialized");
	game_log("Game begin");
	// Initialize game variables.
	game_init();
	game_log("Game initialized");
	// Draw the first frame.
	game_draw();
	game_log("Game start event loop");
	// This call blocks until the game is finished.
	game_start_event_loop();
	game_log("Game end");
	game_destroy();
	return 0;
}

void allegro5_init(void) {
	if (!al_init())
		game_abort("failed to initialize allegro");

	// Initialize add-ons.
	if (!al_init_primitives_addon())
		game_abort("failed to initialize primitives add-on");
	if (!al_init_font_addon())
		game_abort("failed to initialize font add-on");
	if (!al_init_ttf_addon())
		game_abort("failed to initialize ttf add-on");
	if (!al_init_image_addon())
		game_abort("failed to initialize image add-on");
	if (!al_install_audio())
		game_abort("failed to initialize audio add-on");
	if (!al_init_acodec_addon())
		game_abort("failed to initialize audio codec add-on");
	if (!al_reserve_samples(RESERVE_SAMPLES))
		game_abort("failed to reserve samples");
	if (!al_install_keyboard())
		game_abort("failed to install keyboard");
	if (!al_install_mouse())
		game_abort("failed to install mouse");
	// TODO: Initialize other addons such as video, ...
	if (!al_init_video_addon)
		game_abort("failed to initialize video add-on");

	// Setup game display.
	game_display = al_create_display(SCREEN_W, SCREEN_H);
	if (!game_display)
		game_abort("failed to create display");
	al_set_window_title(game_display, "Punch on Reiner! <108062174>");

	// Setup update timer.
	game_update_timer = al_create_timer(1.0f / FPS);
	if (!game_update_timer)
		game_abort("failed to create timer");

	// Setup event queue.
	game_event_queue = al_create_event_queue();
	if (!game_event_queue)
		game_abort("failed to create event queue");

	// Malloc mouse buttons state according to button counts.
	const unsigned m_buttons = al_get_mouse_num_buttons();
	game_log("There are total %u supported mouse buttons", m_buttons);
	// mouse_state[0] will not be used.
	mouse_state = malloc((m_buttons + 1) * sizeof(bool));
	memset(mouse_state, false, (m_buttons + 1) * sizeof(bool));

	// Register display, timer, keyboard, mouse events to the event queue.
	al_register_event_source(game_event_queue, al_get_display_event_source(game_display));
	al_register_event_source(game_event_queue, al_get_timer_event_source(game_update_timer));
	al_register_event_source(game_event_queue, al_get_keyboard_event_source());
	al_register_event_source(game_event_queue, al_get_mouse_event_source());
	// TODO: Register other event sources such as timer, video, ...

	// Start the timer to update and draw the game.
	al_start_timer(game_update_timer);
}

void game_init(void) {
	/* Shared resources: mostly fonts*/
	font_aot_64 = al_load_font("lintxt.ttf", 64, 0);
	if (!font_aot_64)
		game_abort("failed to load font: lintxt.ttf with size 64");

	font_aot_32 = al_load_font("lintxt.ttf", 32, 0);
	if (!font_aot_32)
		game_abort("failed to load font: lintxt.ttf with size 32");

	font_aot_20 = al_load_font("lintxt.ttf", 20, 0);
	if (!font_aot_20)
		game_abort("failed to load font: lintxt.ttf with size 20");

	font_normal = al_load_font("MISTRAL.ttf", 55, 0);
	if (!font_normal)
		game_abort("failed to load font: MISTRAL.ttf with size 55");

	/* Menu Scene resources*/
	menu_img_background = load_bitmap_resized("menu_bg.jpg", SCREEN_W, SCREEN_H);
	if (!menu_img_background)
		game_abort("failed to load image: menu_bg.jpg");

	menu_bgm = al_load_sample("K2.mp3");
	if (!menu_bgm)
		game_abort("failed to load audio: K2.mp3");

	img_setting_icon = al_load_bitmap("settings.png");
	if (!img_setting_icon)
		game_abort("failed to load image: settings.png");
	img_setting_icon_on = al_load_bitmap("settings2.png");
	if (!img_setting_icon_on)
		game_abort("failed to load image: settings2.png");

	/* Setting Scene resourses*/
	setting_img_background = load_bitmap_resized("setting_bg.jpg", SCREEN_W, SCREEN_H);
	if (!setting_img_background)
		game_abort("failed to load image: setting_bg.jpg");

	setting_img_eren = load_bitmap_resized("setting_eren.jpg", 200, 250);
	if (!setting_img_eren)
		game_abort("failed to load image: setting_eren.jpg");

	setting_img_eren_on = load_bitmap_resized("setting_eren_on.jpg", 200, 250);
	if (!setting_img_eren_on)
		game_abort("failed to load image: setting_eren_on.jpg");

	setting_img_levi = load_bitmap_resized("setting_levi.jpg", 200, 250);
	if (!setting_img_levi)
		game_abort("failed to load image: setting_levi.jpg");

	setting_img_levi_on = load_bitmap_resized("setting_levi_on.jpg", 200, 250);
	if (!setting_img_levi_on)
		game_abort("failed to load image: setting_levi_on.jpg");

	/* Start Scene resources*/
	start_img_background = load_bitmap_resized("start_bg.jpg", SCREEN_W, SCREEN_H);
	if (!start_img_background)
		game_abort("failed to load image: start_bg.png");

	start_img_eren = al_load_bitmap("eren.png");
	if (!start_img_eren)
		game_abort("failed to load image: eren.png");

	start_img_levi = load_bitmap_resized("levi.png", 50, 50);
	if (!start_img_levi)
		game_abort("failed to load image: levi.png");

	start_img_enemy = al_load_bitmap("reiner.png");
	if (!start_img_enemy)
		game_abort("failed to load image: reiner.png");

	start_bgm = al_load_sample("AttackOnTitan.mp3");
	if (!start_bgm)
		game_abort("failed to load audio: AttackOnTitan.mp3");

	img_punch = load_bitmap_resized("punch.png", 30, 50);   // Costumed loadin & resizing function
	if (!img_punch)
		game_abort("failed to load image: punch.png");

	img_armorFist = load_bitmap_resized("armorfist.png", 30, 50);
	if (!img_armorFist)
		game_abort("failed to load image: armorfist.png");

	img_ult = load_bitmap_resized("armin.png", 50, 60);
	if (!img_ult)
		game_abort("failed to load image: armin.png");

	/* Trans scene resourses */
	trans_victory_img_background = load_bitmap_resized("trans_victory.png", SCREEN_W, SCREEN_H);
	if (!trans_victory_img_background)
		game_abort("failed to load image: trans_victory.png");

	trans_victory_img_background2 = load_bitmap_resized("trans_victory2.png", SCREEN_W, SCREEN_H);
	if (!trans_victory_img_background2)
		game_abort("failed to load image: trans_victory2.png");

	trans_victory_bgm = al_load_sample("win_bgm.mp3");
	if (!trans_victory_bgm)
		game_abort("failed to load audio: win_bgm.mp3");

	trans_defeat_img_background = load_bitmap_resized("trans_fail.png", SCREEN_W, SCREEN_H);
	if (!trans_defeat_img_background)
		game_abort("failed to load image: trans_fail.png");
	trans_defeat_bgm = al_load_sample("fail_bgm.mp3");
	if (!trans_defeat_bgm)
		game_abort("failed to load audio: fail_bgm.mp3");

	/* Boss scene resourses*/
	boss_img_background = load_bitmap_resized("start_bg.jpg", SCREEN_W, SCREEN_H);
	if (!boss_img_background)
		game_abort("failed to load image: start_bg.jpg");

	boss_img_boss = al_load_bitmap("boss.png");
	if (!boss_img_boss)
		game_abort("failed to load image: boss.png");

	boss_img_fire = load_bitmap_resized("fire.png", 40, 50);
	if (!boss_img_fire)
		game_abort("failed to load image: fire.png");

	boss_bgm = al_load_sample("AppleSeed.mp3");
	if (!boss_bgm)
		game_abort("failed to load audio: AppleSeed.mp3");

	/* end scene resourses*/
	end_eren_img_background = load_bitmap_resized("end_eren.png", SCREEN_W, SCREEN_H);
	if (!end_eren_img_background)
		game_abort("failed to load image: end_eren.png");

	end_armin_img_background = load_bitmap_resized("end_armin.png", SCREEN_W, SCREEN_H);
	if (!end_armin_img_background)
		game_abort("failed to load image: end_armin.png");

	end_reiner_img_background = load_bitmap_resized("end_reiner.jpg", SCREEN_W, SCREEN_H);
	if (!end_reiner_img_background)
		game_abort("failed to load image: end_reiner.jpg");
	
	// Change to first scene.
	game_change_scene(SCENE_MENU);
}

void game_start_event_loop(void) {
	bool done = false;
	ALLEGRO_EVENT event;
	int redraws = 0;
	while (!done) {
		al_wait_for_event(game_event_queue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			// Event for clicking the window close button.
			game_log("Window close button clicked");
			done = true;
		}
		else if (event.type == ALLEGRO_EVENT_TIMER) {
			// Event for redrawing the display.
			if (event.timer.source == game_update_timer)
				// The redraw timer has ticked.
				redraws++;
		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			game_log("Key with keycode %d (name: %s) down", event.keyboard.keycode, al_keycode_to_name(event.keyboard.keycode));
			key_state[event.keyboard.keycode] = true;
			on_key_down(event.keyboard.keycode);
		}
		else if (event.type == ALLEGRO_EVENT_KEY_UP) {
			game_log("Key with keycode %d (name: %s) up", event.keyboard.keycode, al_keycode_to_name(event.keyboard.keycode));
			key_state[event.keyboard.keycode] = false;
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			game_log("Mouse button %d down at (%d, %d)", event.mouse.button, event.mouse.x, event.mouse.y);
			mouse_state[event.mouse.button] = true;
			on_mouse_down(event.mouse.button, event.mouse.x, event.mouse.y);
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			game_log("Mouse button %d up at (%d, %d)", event.mouse.button, event.mouse.x, event.mouse.y);
			mouse_state[event.mouse.button] = false;
		}
		else if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
			if (event.mouse.dx || event.mouse.dy) {
				// Event for mouse move.
				// game_log("Mouse move to (%d, %d)", event.mouse.x, event.mouse.y);
				mouse_x = event.mouse.x;
				mouse_y = event.mouse.y;
			} else if (event.mouse.dz) {
				// Event for mouse scroll.
				game_log("Mouse scroll at (%d, %d) with delta %d", event.mouse.x, event.mouse.y, event.mouse.dz);
			}
		}
		// TODO: Process more events and call callbacks by adding more entries inside Scene.

		// Redraw
		if (redraws > 0 && al_is_event_queue_empty(game_event_queue)) {
			if (redraws > 1)
			     game_log("%d frame(s) dropped", redraws - 1);
			// Update and draw the next frame.
			game_update();
			game_draw();
			redraws = 0;
		}
	}
}

void game_update(void) {
	if (active_scene == SCENE_START || active_scene == SCENE_BOSS) {
		/* Character */
		// move
		character.vx = character.vy = 0;
		if (key_state[ALLEGRO_KEY_UP] || key_state[ALLEGRO_KEY_W])
			character.vy -= 1;
		if (key_state[ALLEGRO_KEY_DOWN] || key_state[ALLEGRO_KEY_S])
			character.vy += 1;
		if (key_state[ALLEGRO_KEY_LEFT] || key_state[ALLEGRO_KEY_A])
			character.vx -= 1;
		if (key_state[ALLEGRO_KEY_RIGHT] || key_state[ALLEGRO_KEY_D])
			character.vx += 1;
		// 0.71 is (1/sqrt(2)).
		character.y += character.vy * 4 * (character.vx ? 0.71f : 1);
		character.x += character.vx * 4 * (character.vy ? 0.71f : 1);
		//  boundary
		if (character.x < character.w / 1.5)
			character.x = character.w / 1.5;
		else if (character.x > SCREEN_W - character.w / 1.5)
			character.x = SCREEN_W - character.w / 1.5;
		if (character.y < character.h / 1.5)
			character.y = character.h / 1.5;
		else if (character.y > SCREEN_H - character.h / 1.5)
			character.y = SCREEN_H - character.h / 1.5;

		/* Bullets */
		double now_punch = al_get_time();	  // Shoot if key is down and cool-down is over.
		if (key_state[ALLEGRO_KEY_SPACE] && now_punch - last_punch >= CD_PUNCH) {
			for (int i = 0; i < MAX_PUNCH; i++) {
				if (punches[i].hidden) {
					last_punch = now_punch;
					punches[i].hidden = false;
					punches[i].x = character.x;
					punches[i].y = character.y - character.h / 3;
					break;
				}
			}
		}
		for (int i = 0; i < MAX_PUNCH; i++) {
			if (!punches[i].hidden)	  // move
				punches[i].y += punches[i].vy;
			if (punches[i].y < 0)     // boundary
				punches[i].hidden = true;
		}
		
		/* specific operations on BASIC level*/
		if (active_scene == SCENE_START) {
			/* Enemies */
			bool noReiner = true;
			for (int i = 0; i < MAX_ENEMY; i++) {
				if (!reiner[i].hidden) {
					noReiner = false;
					if (reiner[i].x < 10)
						reiner[i].vx = 3;
					if (reiner[i].x > SCREEN_W - 10)
						reiner[i].vx = -3;
					reiner[i].x += reiner[i].vx;   // left-right move
					// collision detection (bullet to enemy)
					for (int j = 0; j < MAX_PUNCH; j++) {
						if (!punches[j].hidden && obj_collision(reiner[i], punches[j])) {
							score++;
							punches[j].hidden = true;
							reiner[i].hidden = true;
						}
					}
				}	// all Reiner GG ~
			} if (noReiner) game_change_scene(SCENE_TRANS1);

			/* Enemies' armor fists*/
			double now_fist = al_get_time();	// Shoot if cool-down is over.
			if (now_fist - last_armorFist >= CD_ARMORFIST) {
				for (int i = 0; i < MAX_ENEMY; i++) {
					if (!reiner[i].hidden)
						if (armorFists[i].hidden) {
							last_armorFist = now_fist;
							armorFists[i].hidden = false;
							armorFists[i].x = reiner[i].x;
							armorFists[i].y = reiner[i].y + reiner[i].h;
							break;
						}
				}
			}
			for (int i = 0; i < MAX_ENEMY; i++) {
				if (!armorFists[i].hidden) {
					armorFists[i].y += armorFists[i].vy;  // move
					if (armorFists[i].y > SCREEN_H)       // boundary
						armorFists[i].hidden = true;

					// collision detection (fists to character)
					if (obj_collision(armorFists[i], character)) {
						heart--;
						armorFists[i].hidden = true;
					}
				}	// eren GG ~
			} if (!heart) game_change_scene(SCENE_TRANS1);
		}

		/* specific operations on BOSS level*/
		else if (active_scene == SCENE_BOSS) {
			/* Armin = ultie */
			double now_ult = al_get_time();   // Shoot Armin if Q is down and CD is over.
			if (key_state[ALLEGRO_KEY_Q] && now_ult - last_ult >= CD_ULT) {
				last_ult = now_ult;
				armin.hidden = false;
				armin.x = character.x;
				armin.y = character.y - character.h / 3;
			}
			// armin move and boundary
			if (!armin.hidden) {
				armin.x += armin.vx;
				armin.y += armin.vy;
				if (armin.y < 0)
					armin.hidden = true;
			}
			
			/* Enemy's random fires*/
			double now_fire = al_get_time();
			if (now_fire - last_fire >= CD_FIRE) {
				for (int i = 0; i < MAX_FIRE; i++) {
					if (fire[i].hidden) {
						last_fire = now_fire;
						fire[i].hidden = false;
						fire[i].x = (float)rand() / RAND_MAX * SCREEN_W;
						fire[i].y = 0;
						break;
					}
				}
			}
			for (int i = 0; i < MAX_FIRE; i++) {
				if (fire[i].hidden)
					continue;
				// move and boundary
				fire[i].x += fire[i].vx + i % 10;
				fire[i].y += fire[i].vy + i % 10;
				if (fire[i].y > SCREEN_H)
					fire[i].hidden = true;
				
				// collision detect
				// fire to character
				if (obj_collision(fire[i], character)) {
					heart--;
					fire[i].hidden = true;
				} // fire to armin
				if (!armin.hidden && obj_collision(fire[i], armin)) {
					heart = -999;
					fire[i].hidden = true;
				} // fire to punch
				for (int j = 0; j < MAX_PUNCH; j++) {
					if (!punches[j].hidden && obj_collision(fire[i], punches[j])) {
						score++;
						punches[j].hidden = true;
						fire[i].hidden = true;
					}
				}
			}

			/* BOSS collision detect*/
			// eren to boss
			if (obj_collision(boss, character))
				heart = 0;
			// armin to boss
			if (!armin.hidden && obj_collision(boss, armin)) {
				score += 100;
				bossHP -= 10000;
				armin.hidden = true;
			} // punch to boss
			for (int i = 0; i < MAX_PUNCH; i++) {
				if (!punches[i].hidden && obj_collision(boss, punches[i])) {
					score += 10;
					bossHP--;
					punches[i].hidden = true;
				}
			}
			// victory or defeated
			if (heart <= 0 || bossHP <= 0)
				game_change_scene(SCENE_ENDING);
		}
	}
}

void game_draw(void) {
	if (active_scene == SCENE_MENU) {
		al_draw_bitmap(menu_img_background, 0, 0, 0);
		al_draw_text(font_aot_64, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 3 + 50, ALLEGRO_ALIGN_CENTER, "Punch on Reiner");
		al_draw_text(font_normal, al_map_rgb(255, 255, 255), 20, SCREEN_H - 50, 0, "Press enter key to start");
		if (pnt_in_rect(mouse_x, mouse_y, SCREEN_W - 48, 10, 38, 38))
			al_draw_bitmap(img_setting_icon_on, SCREEN_W - 48, 10, 0);
		else
			al_draw_bitmap(img_setting_icon, SCREEN_W - 48, 10, 0);
	}
	else if (active_scene == SCENE_SETTINGS) {
		al_draw_bitmap(setting_img_background, 0, 0, 0);

		if (pnt_in_rect(mouse_x, mouse_y, SCREEN_W / 5, 150, 200, 250))
			al_draw_bitmap(setting_img_eren_on, SCREEN_W / 5, 150, 0);
		else
			al_draw_bitmap(setting_img_eren, SCREEN_W / 5, 150, 0);

		if (pnt_in_rect(mouse_x, mouse_y, SCREEN_W / 2 + 50, 150, 200, 250))
			al_draw_bitmap(setting_img_levi_on, SCREEN_W / 2 + 50, 150, 0);
		else
			al_draw_bitmap(setting_img_levi, SCREEN_W / 2 + 50, 150, 0);
	}
	else if (active_scene == SCENE_START) {
		al_draw_bitmap(start_img_background, 0, 0, 0);
		al_draw_textf(font_aot_20, al_map_rgb(0, 0, 0), 10, 10, 0, "Score: %d", score);
		al_draw_textf(font_aot_20, al_map_rgb(0, 0, 0), SCREEN_W - 80, 10, 0, "Heart: %d", heart);

		draw_movable_object(character);
		// Draw all punches in your bullet array.
		for (int i = 0; i < MAX_PUNCH; i++)
			draw_movable_object(punches[i]);
		for (int i = 0; i < MAX_ENEMY; i++) {
			draw_movable_object(reiner[i]);
			draw_movable_object(armorFists[i]);
		}
	}
	else if (active_scene == SCENE_TRANS1) {
		if (!heart) {	// defeat
			al_draw_bitmap(trans_defeat_img_background, 0, 0, 0);
			al_draw_text(font_aot_64, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H - 150, ALLEGRO_ALIGN_CENTER, "Defeat");
			al_draw_text(font_normal, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H - 80, ALLEGRO_ALIGN_CENTER, "Press Enter to revenge");
		}
		else if (score >= MAX_ENEMY) {	// vic
			al_draw_bitmap(trans_victory_img_background, 0, 0, 0);
			al_draw_text(font_normal, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H - 100, ALLEGRO_ALIGN_CENTER, "Help me! Bertoldt!");
			game_change_scene(SCENE_TRANS2);
		}
	}
	else if (active_scene == SCENE_TRANS2) {
		al_rest(11);
		al_draw_bitmap(trans_victory_img_background2, 0, 0, 0);
		game_change_scene(SCENE_TEMP);
	}
	else if (active_scene == SCENE_TEMP) {
		al_rest(3);
		game_change_scene(SCENE_BOSS);
	}
	else if (active_scene == SCENE_BOSS) {
		al_draw_bitmap(boss_img_background, 0, 0, 0);
		al_draw_bitmap(boss.img, boss.x, boss.y, 0);
		al_draw_textf(font_aot_20, al_map_rgb(0, 0, 0), 10, 10, 0, "Score: %d", score);
		al_draw_textf(font_aot_20, al_map_rgb(0, 0, 0), SCREEN_W / 2 - 50 , 10, 0, "Boss HP: %d", bossHP);
		al_draw_textf(font_aot_20, al_map_rgb(0, 0, 0), SCREEN_W - 80, 10, 0, "Heart: %d", heart);
		draw_movable_object(character);
		draw_movable_object(armin);
		for (int i = 0; i < MAX_PUNCH; i++)
			draw_movable_object(punches[i]);
		for (int i = 0; i < MAX_FIRE; i++)
			draw_movable_object(fire[i]);
	}
	al_flip_display();
}

void game_destroy(void) {
	// Destroy everything you have created.
	// Free the memories allocated by malloc or allegro functions.

	// Destroy shared resources.
	al_destroy_font(font_aot_64);
	al_destroy_font(font_aot_32);
	al_destroy_font(font_aot_20);
	al_destroy_font(font_normal);

	/* Menu Scene resources*/
	al_destroy_bitmap(menu_img_background);
	al_destroy_sample(menu_bgm);
	al_destroy_bitmap(img_setting_icon);
	al_destroy_bitmap(img_setting_icon_on);

	/* Setting Scene resourses*/
	al_destroy_bitmap(setting_img_background);
	al_destroy_bitmap(setting_img_eren);
	al_destroy_bitmap(setting_img_eren_on);
	al_destroy_bitmap(setting_img_levi);
	al_destroy_bitmap(setting_img_levi_on);

	/* Start Scene resources*/
	al_destroy_bitmap(start_img_background);
	al_destroy_bitmap(start_img_eren);
	al_destroy_bitmap(start_img_levi);
	al_destroy_bitmap(start_img_enemy);
	al_destroy_sample(start_bgm);
	al_destroy_bitmap(img_punch);
	al_destroy_bitmap(img_armorFist);
	al_destroy_bitmap(img_ult);

	/* Trans Scene resourses*/
	al_destroy_bitmap(trans_victory_img_background);
	al_destroy_bitmap(trans_victory_img_background2);
	al_destroy_bitmap(trans_defeat_img_background);
	al_destroy_sample(trans_victory_bgm);
	al_destroy_sample(trans_defeat_bgm);

	/* BOSS Scene resourses*/
	al_destroy_bitmap(boss_img_background);
	al_destroy_bitmap(boss_img_boss);
	al_destroy_bitmap(boss_img_fire);
	al_destroy_sample(boss_bgm);

	/* End scene resourses*/
	al_destroy_bitmap(end_eren_img_background);
	al_destroy_bitmap(end_armin_img_background);
	al_destroy_bitmap(end_reiner_img_background);

	al_destroy_timer(game_update_timer);
	al_destroy_event_queue(game_event_queue);
	al_destroy_display(game_display);
	free(mouse_state);
}

void game_change_scene(int next_scene) {
	game_log("Change scene from %d to %d", active_scene, next_scene);
	// Destroy resources initialized when creating scene.
	if (active_scene == SCENE_MENU) {
		al_stop_sample(&menu_bgm_id);
		game_log("stop audio (bgm)");
	}
	else if (active_scene == SCENE_START) {
		al_stop_sample(&start_bgm_id);
		game_log("stop audio (bgm)");
	}
	else if (active_scene == SCENE_TRANS1) {
		if (!heart) {	// eren defeat
			heart = 5;
			al_stop_sample(&trans_defeat_bgm_id);
			game_log("stop audio (eren defeat)");
		}
	}
	else if (active_scene == SCENE_TEMP) {
		al_stop_sample(&trans_victory_bgm_id);
		game_log("stop audio (reiner defeat)");
	}
	else if (active_scene == SCENE_BOSS) {
		al_stop_sample(&boss_bgm_id);
		game_log("stop audio (bgm)");
	}
	else if (active_scene == SCENE_ENDING) {
		if (heart <= 0) {	// if defeat in BOSS level, play again
			score = 0;
			heart = 5;
			bossHP = MAX_BOSSHP;
		}
	}
	active_scene = next_scene;

	// TODO: Allocate resources before entering scene.
	if (active_scene == SCENE_MENU) {
		if (!al_play_sample(menu_bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &menu_bgm_id))
			game_abort("failed to play audio (bgm)");
	}
	else if (active_scene == SCENE_START) {
		if (!al_play_sample(start_bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &start_bgm_id))
			game_abort("failed to play audio (bgm)");

		// Initialize character
		if (character_id == 1) character.img = start_img_eren;
		if (character_id == 2) character.img = start_img_levi;
		character.x = 400;
		character.y = 500;
		character.w = al_get_bitmap_width(character.img);
		character.h = al_get_bitmap_height(character.img);
		// Initialize punches
		for (int i = 0; i < MAX_PUNCH; i++) {
			punches[i].img = img_punch;
			punches[i].w = al_get_bitmap_width(img_punch);
			punches[i].h = al_get_bitmap_height(img_punch);
			punches[i].vx = 0;
			punches[i].vy = -3;
			punches[i].hidden = true;
		}
		// Initialize Reiner and his fists
		for (int i = 0; i < MAX_ENEMY; i++) {
			reiner[i].img = start_img_enemy;
			reiner[i].w = al_get_bitmap_width(start_img_enemy);
			reiner[i].h = al_get_bitmap_height(start_img_enemy);
			reiner[i].x = reiner[i].w / 2 + (float)rand() / RAND_MAX * (SCREEN_W - reiner[i].w);
			reiner[i].y = 80;
			reiner[i].vx = i % 2 ? 3 : -3;
			armorFists[i].img = img_armorFist;
			armorFists[i].w = al_get_bitmap_width(img_armorFist);
			armorFists[i].h = al_get_bitmap_height(img_armorFist);
			armorFists[i].vx = 0;
			armorFists[i].vy = 2;
			armorFists[i].hidden = true;
		}
	}
	else if (active_scene == SCENE_TRANS1) {
		if (!heart) {
			if (!al_play_sample(trans_defeat_bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &trans_defeat_bgm_id))
				game_abort("failed to play audio (eren defeat)");
		}
		else if (score >= MAX_ENEMY) {
			al_rest(0.5);
			if (!al_play_sample(trans_victory_bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &trans_victory_bgm_id))
				game_abort("failed to play audio (reiner defeat)");
		}
	}
	else if (active_scene == SCENE_BOSS) {
		if (!al_play_sample(boss_bgm, 1, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &boss_bgm_id))
			game_abort("failed to play audio (bgm)");

		// Character Reposition
		character.x = 400;
		character.y = 500;
		for (int i = 0; i < MAX_PUNCH; i++)
			punches[i].hidden = true;

		// Initialize BOSS
		boss.img = boss_img_boss;
		boss.w = al_get_bitmap_width(boss_img_boss);
		boss.h = al_get_bitmap_height(boss_img_boss);
		boss.x = boss.w / 3;
		boss.y = 50;
		// Initialize BOSS' fire
		for (int i = 0; i < MAX_FIRE; i++) {
			fire[i].img = boss_img_fire;
			fire[i].w = al_get_bitmap_width(boss_img_fire);
			fire[i].h = al_get_bitmap_height(boss_img_fire);
			fire[i].x = fire[i].w / 2 + (float)rand() / RAND_MAX * SCREEN_W - fire[i].w;
			fire[i].y = 0;
			fire[i].vx = i % 2 ? 3 : -3;
			fire[i].vy = 3;
			fire[i].hidden = true;
		}

		// Initialize Armin
		armin.img = img_ult;
		armin.w = al_get_bitmap_width(img_ult);
		armin.h = al_get_bitmap_height(img_ult);
		armin.vx = 0;
		armin.vy = -3;
		armin.hidden = true;
	}
	else if (active_scene == SCENE_ENDING) {
		if (bossHP <= 0) {
			al_draw_bitmap(end_reiner_img_background, 0, 0, 0);
			al_draw_text(font_normal, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H -200, ALLEGRO_ALIGN_CENTER, "VICTORY!");
		}
		else if (heart == 0) {
			al_draw_bitmap(end_eren_img_background, 0, 0, 0);
			al_draw_text(font_normal, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H - 200, ALLEGRO_ALIGN_CENTER, "DEFEAT");
		}
		else if (heart < 0) {
			al_draw_bitmap(end_armin_img_background, 0, 0, 0);
			al_draw_text(font_normal, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H -200, ALLEGRO_ALIGN_CENTER, "DEFEAT");
		}
	}
}

void on_key_down(int keycode) {
	if (active_scene == SCENE_MENU) {
		if (keycode == ALLEGRO_KEY_ENTER)
			game_change_scene(SCENE_START);
	}
	else if (active_scene == SCENE_SETTINGS) {
		if (keycode == ALLEGRO_KEY_BACKSPACE)
			game_change_scene(SCENE_MENU);
	}
	else if (active_scene == SCENE_TRANS1 && !heart) {
			if (keycode == ALLEGRO_KEY_ENTER)
				game_change_scene(SCENE_MENU);
	}
	else if (active_scene == SCENE_ENDING) {
		if (keycode == ALLEGRO_KEY_ENTER)
			game_change_scene(SCENE_BOSS);
	}
}

void on_mouse_down(int btn, int x, int y) {
	if (active_scene == SCENE_MENU) {
		if (btn == 1) {
			if (pnt_in_rect(x, y, SCREEN_W - 48, 10, 38, 38))
				game_change_scene(SCENE_SETTINGS);
		}
	}
	else if (active_scene == SCENE_SETTINGS) {
		if (btn == 1) {
			if (pnt_in_rect(x, y, SCREEN_W / 5, 150, 200, 250)) {
				character_id = 1;
				game_change_scene(SCENE_START);
			}
			else if (pnt_in_rect(x, y, SCREEN_W / 2 + 50, 150, 200, 250)) {
				character_id = 2;
				game_change_scene(SCENE_START);
			}
		}
	}
}

void draw_movable_object(MovableObject obj) {
	if (obj.hidden)
		return;
	al_draw_bitmap(obj.img, round(obj.x - obj.w / 2), round(obj.y - obj.h / 2), 0);
}

ALLEGRO_BITMAP *load_bitmap_resized(const char *filename, int w, int h) {
	ALLEGRO_BITMAP* loaded_bmp = al_load_bitmap(filename);
	if (!loaded_bmp)
		game_abort("failed to load image: %s", filename);
	ALLEGRO_BITMAP *resized_bmp = al_create_bitmap(w, h);
	ALLEGRO_BITMAP *prev_target = al_get_target_bitmap();

	if (!resized_bmp)
		game_abort("failed to create bitmap when creating resized image: %s", filename);
	al_set_target_bitmap(resized_bmp);
	al_draw_scaled_bitmap(loaded_bmp, 0, 0,
		al_get_bitmap_width(loaded_bmp),
		al_get_bitmap_height(loaded_bmp),
		0, 0, w, h, 0);
	al_set_target_bitmap(prev_target);
	al_destroy_bitmap(loaded_bmp);

	game_log("resized image: %s", filename);

	return resized_bmp;
}

bool pnt_in_rect(int x, int y, int pic_x, int pic_y, int pic_w, int pic_h) {
	return (pic_x <= x && x <= pic_x + pic_w && pic_y <= y && y <= pic_y + pic_h);
}

bool obj_collision(MovableObject obj1, MovableObject obj2) {
	if (obj1.y < obj2.y && obj2.y < obj1.y + obj1.h || obj1.y < obj2.y + obj2.h && obj2.y + obj2.h < obj1.y + obj1.h)
		if (obj1.x < obj2.x && obj2.x < obj1.x + obj1.w || obj1.x < obj2.x + obj2.w && obj2.x + obj2.w < obj1.x + obj1.w)
			return true;
	return false;
}

	// +=================================================================+
	// | Code below is for debugging purpose, it's fine to remove it.    |
	// | Deleting the code below and removing all calls to the functions |
	// | doesn't affect the game.                                        |
	// +=================================================================+

	void game_abort(const char* format, ...) {
		va_list arg;
		va_start(arg, format);
		game_vlog(format, arg);
		va_end(arg);
		fprintf(stderr, "error occured, exiting after 2 secs");
		// Wait 2 secs before exiting.
		al_rest(2);
		// Force exit program.
		exit(1);
	}

	void game_log(const char* format, ...) {
#ifdef LOG_ENABLED
		va_list arg;
		va_start(arg, format);
		game_vlog(format, arg);
		va_end(arg);
#endif
	}

	void game_vlog(const char* format, va_list arg) {
#ifdef LOG_ENABLED
		static bool clear_file = true;
		// Write log to file for later debugging.
		FILE* pFile = fopen("log.txt", clear_file ? "w" : "a");
		if (pFile) {
			va_list arg2;
			va_copy(arg2, arg);
			vfprintf(pFile, format, arg2);
			va_end(arg2);
			fprintf(pFile, "\n");
			fclose(pFile);
		}
		vprintf(format, arg);
		printf("\n");
		clear_file = false;
#endif
	}
