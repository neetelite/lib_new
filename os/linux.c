#include <unistd.h> /* readlink */

#include "./linux.h"
#include "../graphics/opengl.h"

#include "../scalar.h"
#include "../cstring.h"
#include "../memory.h"

#include "../debug.h"
#include "../../lib/graphics.h"

struct OS_Display os_display;
struct OS_State os_state;
struct OS_Input os_input;

void
os_path_build()
{
	/* path_exe */
	readlink("/proc/self/exe", os_state.path_exe, PATH_MAX);

	/* path_run */
	cstr_path_parent(os_state.path_run, os_state.path_exe);

	/* path_data */
	cstr_cat(os_state.path_data, os_state.path_run, "data/");

	/* path */
	cstr_path_parent(os_state.path, os_state.path_run);

	/* path_src */
	cstr_cat(os_state.path_src, os_state.path, "src/");
}

void
os_init(n32 fps)
{
	/* Path */
	os_path_build();

	/* X11 */
	os_display.handle = XOpenDisplay(NULL);
	os_display.window_root.handle = RootWindow(os_display.handle, DefaultScreen(os_display.handle));

	XGetWindowAttributes(os_display.handle, os_display.window_root.handle, &os_display.window_root.attributes);
	os_display.window_root.dim.width = os_display.window_root.attributes.width;
	os_display.window_root.dim.height = os_display.window_root.attributes.height;
}

/* Graphics */
void
os_graphics_init(void)
{
	opengl_init();
}

void
os_graphics_draw(void)
{
	glXSwapBuffers(os_display.handle, os_display.window_main.handle);
}

/* Window */
Window
x11_window_find(Window window_current, CString window_name)
{
    /* Check if this window has the name we seek */
    CString window_name_tmp = NULL;
	i32 ret = XFetchName(os_display.handle, window_current, &window_name_tmp);
    if(ret > 0)
	{
		ret = cstr_eql(window_name_tmp, window_name);
		XFree(window_name_tmp);
		if(ret == TRUE)
		{
			return(window_current);
		}
    }

    /* If it does not: check all subwindows recursively. */
    Window result = 0;

	Window window_root, window_parent, *window_children;
    n32 child_count;
	ret = XQueryTree(os_display.handle, window_current,
					 &window_root, &window_parent, &window_children, &child_count);
    if(ret != 0)
	{
        for(i32 i = 0; i < child_count; ++i)
		{
            Window window_tmp = x11_window_find(window_children[i], window_name);
			if(window_tmp != 0)
			{
				result = window_tmp;
				break;
			}
        }
        XFree(window_children);
    }

    return(result);
}

struct OS_Window
os_window_find(CString window_name)
{
	/* TODO: Error checking */
	struct OS_Window result = {};
	result.handle = x11_window_find(os_display.window_root.handle, window_name);

	if(result.handle != 0)
	{
		XGetWindowAttributes(os_display.handle, result.handle, &result.attributes);
		result.dim.width = result.attributes.width;
		result.dim.height = result.attributes.height;
	}

	return(result);
}

struct OS_Window
os_screen_find(CString screen_name)
{
	/* TODO: Error checking */
	struct OS_Window result = {};
	i32 screen_id = ScreenCount(os_display.handle);
	printf("SCREEN: %d\n", screen_id);
	result.handle = RootWindow(os_display.handle, 1);

	if(result.handle != 0)
	{
		XGetWindowAttributes(os_display.handle, result.handle, &result.attributes);
		result.dim.width = result.attributes.width;
		result.dim.height = result.attributes.height;
	}

	return(result);
}

void
os_window_capture_image(struct OS_Window *window, struct Image *image)
{
	XImage *ximage = XGetImage(os_display.handle, window->handle,
							   window->pos.x, window->pos.y,
							   window->dim.x, window->dim.y,
							   AllPlanes, ZPixmap);

	image->format = IMG_FORMAT_BGRA;
	image->separation = IMG_SEPARATION_PIXEL;
	image->representation = IMG_REPRESENTATION_R32;
	image->colorspace = IMG_COLORSPACE_RGB;

	image->width = ximage->width;
	image->height = ximage->height;
	image->channel_count = 3;
	image->channel_padding = 1;
	img_extra_set(image);

	switch(image->representation)
	{
	case IMG_REPRESENTATION_N8: mem_cpy(image->data, ximage->data, image->size); break;
	case IMG_REPRESENTATION_R32:
	{
		img_representation_r32_from_n8_out(image->data, ximage->data, image->width, image->height, image->channel_count, image->channel_padding);

		struct Image image_tmp = *image;
		image_tmp.data = mem_alloc(image->size, FALSE);
		mem_cpy(image_tmp.data, image->data, image->size);
		for(i32 y = 0; y < image->height; ++y)
		{
			for(i32 x = 0; x < image->width; ++x)
			{
				Vec4 *pixel_src = img_pixel_get(&image_tmp, x, y);
				Vec4 *pixel_dst = img_pixel_get(image, x, image->height - 1 - y);
				*pixel_dst = *pixel_src;
			}
		}
		mem_free(image_tmp.data);
	} break;
	}

	XDestroyImage(ximage);
}

void
os_window_create(n32 width, n32 height, CString window_name)
{
	GLint gl_attributes[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};
	XVisualInfo *visual_info = glXChooseVisual(os_display.handle, 0, gl_attributes);
	if(visual_info == NULL) {DBG_FATAL("glxChooseVisual.\n");}

	Colormap colormap = XCreateColormap(os_display.handle, os_display.window_root.handle,
										visual_info->visual, AllocNone);

	XSetWindowAttributes swa = {0};
	swa.colormap = colormap;
	swa.event_mask = KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask |
		EnterWindowMask | LeaveWindowMask | PointerMotionMask |
		Button1MotionMask | Button2MotionMask | Button3MotionMask | Button4MotionMask | Button5MotionMask |
		ButtonMotionMask | ExposureMask | StructureNotifyMask | ResizeRedirectMask;

	os_display.window_main.dim.width = width;
	os_display.window_main.dim.height = height;
	os_display.window_main.handle = XCreateWindow
	(
		os_display.handle, os_display.window_root.handle,
		0, 0, os_display.window_main.dim.width, os_display.window_main.dim.height, 0,
		visual_info->depth, InputOutput, visual_info->visual,
		CWColormap | CWEventMask, &swa
	);

	XMapWindow(os_display.handle, os_display.window_main.handle);
	XStoreName(os_display.handle, os_display.window_main.handle, window_name);

	os_display.graphics_context = glXCreateContext(os_display.handle, visual_info, NULL, GL_TRUE);
	glXMakeCurrent(os_display.handle, os_display.window_main.handle, os_display.graphics_context);

	/* Nothing to do with creating a window */
	os_graphics_init();

	gl_viewport_rec_set(VEC4(0, 0, width, height));
	gl_viewport_color_set(VEC4_COLOR_BLACK);
	gl.projection_2d = gl_projection_2d(width, height);

	gl_enable(GL_TEXTURE_2D);
	//gl_enable(GL_DEPTH_TEST);
	gl_enable(GL_BLEND);

	gl_func_blend(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//gl_func_depth(GL_LEQUAL);
}

void
os_input_update()
{
	struct Periph_Keyboard *keyboard = &os_input.keyboard;
	struct Periph_Mouse *mouse = &os_input.mouse;

	mem_cpy(keyboard->key_last, keyboard->key, KEY_MAX * sizeof(*keyboard->key));
	mem_cpy(mouse->button_last, mouse->button, BUTTON_MAX * sizeof(*mouse->button));
	mouse->has_moved = FALSE;

	n32 half_width = os_display.window_main.dim.width / 2;
	n32 half_height = os_display.window_main.dim.height / 2;

	/* Parse events */
	XEvent event;
	while(XPending(os_display.handle))
	{
		XNextEvent(os_display.handle, &event);
		switch(event.type)
		{
			case KeyPress:
			case KeyRelease:
			{
				keyboard->key[event.xkey.keycode] += 1;
			} break;
			case ButtonPress:
			case ButtonRelease:
			{
				mouse->button[event.xbutton.button] += 1;
			} break;
			case MotionNotify:
			{
				/* NOTE - This way is better than "mouse->d = mouse->p - new_pos" */
				mouse->has_moved = TRUE;
				Vec2 new_pos = VEC2(event.xmotion.x, (os_display.window_main.dim.height - event.xmotion.y)-1);
				mouse->pos_change = VEC2(new_pos.x - half_width, new_pos.y - half_height);
				mouse->pos_window = new_pos;
			} break;
		}
	}

	/* Execute OS Events */
	if(key_alt_is_down(keyboard) && key_is_down(keyboard, KEY_F4)) os_state.is_running = FALSE;
}
