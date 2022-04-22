#ifndef _linux_h
#define _linux_h

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
/* IMPORTANT NOTE: The retards at X11 defined Status, Bool, True, False */
#undef Status
#undef Bool
#undef True
#undef False

#include <linux/limits.h>

#include "../vector.h"
#include "../scalar/boolean.h"
#include "../scalar/natural.h"
#include "../cstring.h"
#include "../image.h"
#include "../peripheral.h"

struct OS_Window
{
	Window handle;
	XWindowAttributes attributes;

	/* TODO: Change to box */
	//struct Box2 box;
	Vec2 pos;
	Vec2 dim;

	r32 aspect_ratio;
	Bool is_fullscreen;
};

struct OS_Display
{
	Display *handle;
	struct OS_Window window_root;
	struct OS_Window window_main;

	GLXContext graphics_context;
};

struct OS_State
{
	char path[PATH_MAX];
	char path_exe[PATH_MAX];
	char path_run[PATH_MAX];
	char path_src[PATH_MAX];
	char path_data[PATH_MAX];

	n32 fps;
	n32 fps_max;
	n32 frame;

	r32 dt;

	Bool is_running;
};

struct OS_Input
{
	struct Periph_Keyboard keyboard;
	struct Periph_Mouse mouse;
};

extern struct OS_Display os_display;
extern struct OS_State os_state;
extern struct OS_Input os_input;

/* Functions */
void os_init(n32 fps);
void os_graphics_init(void);
void os_graphics_draw(void);
struct OS_Window os_window_find(CString window_name);
void os_window_create(n32 width, n32 height, CString name);
void os_window_capture_image(struct OS_Window *window, struct Image *image);
struct OS_Window os_screen_find(CString screen_name);

void os_input_update(void);

#endif /* _linux_h */
