#ifndef _peripheral_h
#define _peripheral_h

#include "./scalar/boolean.h"
#include "./scalar/natural.h"
#include "./vector.h"

#define KEY_MAX 0xFF
#define BUTTON_MAX 0xA

struct Periph_Keyboard
{
	n8 key[KEY_MAX];
	n8 key_last[KEY_MAX];
};

struct Periph_Mouse
{
	n8 button[BUTTON_MAX];
	n8 button_last[BUTTON_MAX];

	Vec2 pos_screen;
	Vec2 pos_window;
	Vec2 pos_change;

	i32 wheel;
	i32 wheel_last;

	Bool has_moved;
};

#if OS == OS_LINUX
enum Periph_KeyboardKey
{
	/* NOTE: X11 specific */

	/* Numbers */
	KEY_1 = 0x0a,
	KEY_2 = 0x0b,
	KEY_3 = 0x0c,
	KEY_4 = 0x0d,
	KEY_5 = 0x0e,
	KEY_6 = 0x0f,
	KEY_7 = 0x10,
	KEY_8 = 0x11,
	KEY_9 = 0x12,
	KEY_0 = 0x13,

	/* Letters */
	KEY_A = 0x26,
	KEY_B = 0x38,
	KEY_C = 0x36,
	KEY_D = 0x28,
	KEY_E = 0x1A,
	KEY_F = 0x29,
	KEY_G = 0x2A,
	KEY_H = 0x2B,
	KEY_I = 0x1F,
	KEY_J = 0x2C,
	KEY_K = 0x2D,
	KEY_L = 0x2E,
	KEY_M = 0x3A,
	KEY_N = 0x39,
	KEY_O = 0x20,
	KEY_P = 0x21,
	KEY_Q = 0x18,
	KEY_R = 0x1B,
	KEY_S = 0x27,
	KEY_T = 0x1C,
	KEY_U = 0x1E,
	KEY_V = 0x37,
	KEY_W = 0x19,
	KEY_X = 0x35,
	KEY_Y = 0x1D,
	KEY_Z = 0x34,

	/* Special */
	KEY_TAB = 0x17,
	KEY_ENTER = 0x24,

	KEY_SPACE = 0x41,
	KEY_TILDE = 0x31,
	KEY_MINUS = 0x14,
	KEY_PLUS = 0x15,
	KEY_COLON = 0x2F,
	KEY_QUOTE = 0x30,
	KEY_COMMA = 0x3B,
	KEY_PERIOD = 0x3C,
	KEY_BRACKET_LEFT = 0x22,
	KEY_BRACKET_RIGHT = 0x23,
	KEY_SLASH_LEFT = 0x33, /* backslash */
	KEY_SLASH_RIGHT = 0x3D, /* slash */

	/* Control */
	KEY_ESCAPE = 0x09,
	KEY_BACKSPACE = 0x16,
	KEY_CAPSLOCK = 0x42,
	KEY_ALT_LEFT = 0x40,
	KEY_ALT_RIGHT = 0x6C,
	KEY_CTRL_LEFT = 0x25,
	KEY_CTRL_RIGHT = 0x69,
	KEY_SHIFT_LEFT = 0x32,
	KEY_SHIFT_RIGHT = 0x3E,
	KEY_MOD_LEFT = 0x85,
	KEY_MOD_RIGHT = 0x86,

	KEY_PRINT_SCREEN = 0x6B,
	KEY_SCROLL_LOCK = 0x4E,
	KEY_PAUSE = 0x7F,

	KEY_INSERT = 0x76,
	KEY_DELETE = 0x77,
	KEY_END = 0x73,
	KEY_HOME = 0x6E,
	KEY_PAGE_UP = 0x70,
	KEY_PAGE_DOWN = 0x75,

	KEY_ARROW_LEFT = 0x71,
	KEY_ARROW_RIGHT = 0x72,
	KEY_ARROW_UP = 0x6F,
	KEY_ARROW_DOWN = 0x74,

	/* fUNCTION */
	KEY_F1 = 0x43,
	KEY_F2 = 0x44,
	KEY_F3 = 0x45,
	KEY_F4 = 0x46,
	KEY_F5 = 0x47,
	KEY_F6 = 0x48,
	KEY_F7 = 0x49,
	KEY_F8 = 0x4A,
	KEY_F9 = 0x4B,
	KEY_F10 = 0x4C,
	KEY_F11 = 0x5F,
	KEY_F12 = 0x60,
	KEY_F13 = 0xBF,
	KEY_F14 = 0xC0,
	KEY_F15 = 0xC1,
	KEY_F16 = 0xC2,
	KEY_F17 = 0xC3,
	KEY_F18 = 0xC4,
	KEY_F19 = 0xC5,
	KEY_F20 = 0xC6,
	KEY_F21 = 0xC7,
	KEY_F22 = 0xC8,
	KEY_F23 = 0xC9,
	KEY_F24 = 0xCA,

	/* nUMPAD */
	KEY_NUM_1 = 0x57,
	KEY_NUM_2 = 0x58,
	KEY_NUM_3 = 0x59,
	KEY_NUM_4 = 0x53,
	KEY_NUM_5 = 0x54,
	KEY_NUM_6 = 0x55,
	KEY_NUM_7 = 0x4F,
	KEY_NUM_8 = 0x50,
	KEY_NUM_9 = 0x51,
	KEY_NUM_0 = 0x5A,
	KEY_NUM_SUB = 0x52,
	KEY_NUM_ADD = 0x56,
	KEY_NUM_MUL = 0x3F,
	KEY_NUM_DIV = 0x6A,
	KEY_NUM_EQL = 0x7D,
	KEY_NUM_COMMA = 0x81,
	KEY_NUM_DECIMAL = 0x5B,

	KEY_NUM_SIGN = 0x7E,
	KEY_NUM_LOCK = 0x4D,
	KEY_NUM_ENTER = 0x68,
	KEY_NUM_PARENT_LEFT = 0xBB,
	KEY_NUM_PARENT_RIGHT = 0xBC,

	/* bROWSER */
	KEY_BROWSER_FAVORITES = 0xA4,
	KEY_BROWSER_LEFT = 0xA6,
	KEY_BROWSER_RIGHT = 0xA7,
	KEY_BROWSER_HOME = 0xB4,
	KEY_BROWSER_REFRESH = 0xB5,
	KEY_BROWSER_SEARCH = 0xE1,

	/* mEDIA */
	KEY_MEDIA_NEXT = 0xAB,
	KEY_MEDIA_PAUSE = 0xAC,
	KEY_MEDIA_PREV = 0xAD,
	KEY_MEDIA_STOP = 0xAE,
	KEY_MEDIA_PLAYER = 0xB3,

	/* vOLUEMT */
	KEY_VOL_MUTE = 0x79,
	KEY_VOL_DOWN = 0x7A,
	KEY_VOL_UP = 0x7B,

	/* uNKNOWN */
	KEY_SELECT = 0x8C,
	KEY_INTL_BCAKSLASH = 0x5E, /* todo: intl backslash */
	KEY_INTL_RO = 0x61, /* todo intl ro */
	KEY_CONVERT = 0x64,
	KEY_KANA = 0x65,
	KEY_NON_CONVER = 0x66,
	KEY_POWER = 0x7C,
	KEY_LANG_1 = 0x82,
	KEY_LANG_2 = 0x83,
	KEY_INTL_YEN = 0x84,
	KEY_CONTEXT_MENU = 0x87,
	KEY_CANCEL = 0x88,
	KEY_AGAIN = 0x89,
	KEY_PROPS = 0x8A,
	KEY_UNDO = 0x8B,
	KEY_COPY = 0x8D,
	KEY_OPEN = 0x8E,
	KEY_PASTE = 0x8F,
	KEY_FIND = 0x90,
	KEY_CUT = 0x91,
	KEY_HELP = 0x92,
	KEY_APP_2 = 0x94,
	KEY_WAKEUP = 0x97,
	KEY_APP_1 = 0x98,
	KEY_MAIL = 0xA3,
	KEY_EJECT = 0xA9,
};

enum Periph_MouseButton
{
	BUTTON_LEFT    = 1,
	BUTTON_MIDDLE  = 2,
	BUTTON_RIGHT   = 3,
	BUTTON_EXTRA_1 = 6,
	BUTTON_EXTRA_2 = 7,
};
#elif OS == OS_WINDOWS
enum Periph_KeyboardKey
{
	/* TODO: Use hex numbers for everything */
	/* nUMBERS */
	KEY_1 = 0x31,
	KEY_2 = 0x32,
	KEY_3 = 0x33,
	KEY_4 = 0x34,
	KEY_5 = 0x35,
	KEY_6 = 0x36,
	KEY_7 = 0x37,
	KEY_8 = 0x38,
	KEY_9 = 0x39,
	KEY_0 = 0x30,

	/* lETTERS */
	KEY_A = 0x41,
	KEY_B = 0x42,
	KEY_C = 0x43,
	KEY_D = 0x44,
	KEY_E = 0x45,
	KEY_F = 0x46,
	KEY_G = 0x47,
	KEY_H = 0x48,
	KEY_I = 0x49,
	KEY_J = 0x4A,
	KEY_K = 0x4B,
	KEY_L = 0x4C,
	KEY_M = 0x4D,
	KEY_N = 0x4E,
	KEY_O = 0x4F,
	KEY_P = 0x50,
	KEY_Q = 0x51,
	KEY_R = 0x52,
	KEY_S = 0x53,
	KEY_T = 0x54,
	KEY_U = 0x55,
	KEY_V = 0x56,
	KEY_W = 0x57,
	KEY_X = 0x58,
	KEY_Y = 0x59,
	KEY_Z = 0x5A,

	/* sPECIAL */
	KEY_TAB = vk_tab,
	KEY_ENTER = vk_return,

	KEY_SPACE = vk_space,
	KEY_TILDE = vk_oem_3,
	KEY_MINUS = vk_oem_minus,
	KEY_PLUS = vk_oem_plus,
	KEY_COLON = vk_oem_1,
	KEY_QUOTE = vk_oem_7,
	KEY_COMMA = vk_oem_comma,
	KEY_PERIOD = vk_oem_period,
	KEY_BRACKET_LEFT = vk_oem_4,
	KEY_BRACKET_RIGHT = vk_oem_6,
	KEY_SLASH_LEFT = vk_oem_5, /* BACKSLASH */
	KEY_SLASH_RIGHT = vk_oem_2, /* SLASH */

	/* cONTROL */
	KEY_ESCAPE = vk_escape,
	KEY_BACKSPACE = vk_back,
	KEY_CAPSLOCK = vk_capital,
	KEY_ALT_LEFT = vk_lmenu,
	KEY_ALT_RIGHT = vk_rmenu,
	KEY_CTRL_LEFT = vk_lcontrol,
	KEY_CTRL_RIGHT = vk_rcontrol,
	KEY_SHIFT_LEFT = vk_lshift,
	KEY_SHIFT_RIGHT = vk_rshift,
	KEY_MOD_LEFT = vk_lwin,
	KEY_MOD_RIGHT = vk_rwin,

	KEY_SHIFT = vk_shift,
	KEY_CTRL = vk_control,
	KEY_ALT = vk_menu,
	//KEY_MOD = vk_win,

	KEY_PRINT_SCREEN = vk_snapshot,
	KEY_SCROLL_LOCK = vk_numlock,
	KEY_PAUSE = vk_pause,

	KEY_INSERT = vk_insert,
	KEY_DELETE = vk_delete,
	KEY_END = vk_end,
	KEY_HOME = vk_home,
	KEY_PAGE_UP = vk_prior,
	KEY_PAGE_DOWN = vk_next,

	KEY_ARROW_LEFT = vk_left,
	KEY_ARROW_RIGHT = vk_right,
	KEY_ARROW_UP = vk_up,
	KEY_ARROW_DOWN = vk_down,

	/* fUNCTION */
	KEY_F1 = vk_f1,
	KEY_F2 = vk_f2,
	KEY_F3 = vk_f3,
	KEY_F4 = vk_f4,
	KEY_F5 = vk_f5,
	KEY_F6 = vk_f6,
	KEY_F7 = vk_f7,
	KEY_F8 = vk_f8,
	KEY_F9 = vk_f9,
	KEY_F10 = vk_f10,
	KEY_F11 = vk_f11,
	KEY_F12 = vk_f12,
	KEY_F13 = vk_f13,
	KEY_F14 = vk_f14,
	KEY_F15 = vk_f15,
	KEY_F16 = vk_f16,
	KEY_F17 = vk_f17,
	KEY_F18 = vk_f18,
	KEY_F19 = vk_f19,
	KEY_F20 = vk_f20,
	KEY_F21 = vk_f21,
	KEY_F22 = vk_f22,
	KEY_F23 = vk_f23,
	KEY_F24 = vk_f24,

	/* nUMPAD */
	KEY_NUMPAD_0 = 0x60,
	KEY_NUMPAD_1 = 0x61,
	KEY_NUMPAD_2 = 0x62,
	KEY_NUMPAD_3 = 0x63,
	KEY_NUMPAD_4 = 0x64,
	KEY_NUMPAD_5 = 0x65,
	KEY_NUMPAD_6 = 0x66,
	KEY_NUMPAD_7 = 0x67,
	KEY_NUMPAD_8 = 0x68,
	KEY_NUMPAD_9 = 0x69,
	KEY_NUMPAD_SUB = vk_subtract,
	KEY_NUMPAD_ADD = vk_add,
	KEY_NUMPAD_MUL = vk_multiply,
	//KEY_NUMPAD_DIV = vk_devide,
	//KEY_NUM_EQL = 0x0,
	//KEY_NUM_COMMA = 0x0,
	KEY_NUMPAD_DECIMAL= vk_decimal,
	//KEY_NUM_SIGN = 0x7E,
	//KEY_NUM_LOCK = 0x4D,
	//KEY_NUM_ENTER = 0x68,
	//KEY_NUM_PARENT_LEFT = 0xBB,
	//KEY_NUM_PARENT_RIGHT = 0xBC,

	//KEY_NUM_SIGN = 0x7E,
	KEY_NUM_LOCK = vk_numlock,
	//KEY_NUM_ENTER = 0x68,
	//KEY_NUM_PARENT_LEFT = 0xBB,
	//KEY_NUM_PARENT_RIGHT = 0xBC,

	/* bROWSER */
	KEY_BROWSER_FAVORITES = vk_browser_favorites,
	KEY_BROWSER_LEFT = vk_browser_back,
	KEY_BROWSER_RIGHT = vk_browser_forward,
	KEY_BROWSER_HOME = vk_browser_home,
	KEY_BROWSER_REFRESH = vk_browser_refresh,
	KEY_BROWSER_SEARCH = vk_browser_search,
	//KEY_BROWSER_STOP = vk_browser_stop,

	/* todo: ime kEYS? */
	/* todo: oem kEYS */

	/* mEDIA */
	KEY_MEDIA_NEXT = vk_media_next_track,
	//KEY_MEDIA_PAUSE = vk_media_pause,
	KEY_MEDIA_PREV = vk_media_prev_track,
	KEY_MEDIA_STOP = vk_media_stop,
	//KEY_MEDIA_PLAYER = 0x0,

	/* vOLUME */
	#IF 0
	KEY_VOL_MUTE = vk_vol_mute,
	KEY_VOL_DOWN = vk_vol_down,
	KEY_VOL_UP = vk_vol_up,
	#ENDIF

	/* uNKNOWN */
	KEY_CLEAR = vk_clear,
	KEY_HELP = vk_help,
	KEY_NUMPAD_SEPARATOR = vk_separator,
	KEY_SELECT = vk_select,
	KEY_PRINT = vk_print,
	//key_execute = vk_execute,
	//KEY_APP = vk_app, /* ???? */
	KEY_SLEEP = vk_sleep,

};

enum Periph_MouseButton
{
	BUTTON_LEFT    = 1,
	BUTTON_MIDDLE  = 2,
	BUTTON_RIGHT   = 3,
	BUTTON_EXTRA_1 = 6,
	BUTTON_EXTRA_2 = 7,
};

enum Periph_MouseWheel
{
	WHEEL_UP   = 4,
	WHEEL_DOWN = 5,
};
#endif

/* Functions */
Bool key_is_down(struct Periph_Keyboard *keyboard, enum Periph_KeyboardKey key);
Bool key_is_up(struct Periph_Keyboard *keyboard, enum Periph_KeyboardKey key);
Bool key_was_pressed(struct Periph_Keyboard *keyboard, enum Periph_KeyboardKey key);
Bool key_was_released(struct Periph_Keyboard *keyboard, enum Periph_KeyboardKey key);

Bool key_alt_is_down(struct Periph_Keyboard *keyboard);
Bool key_alt_is_up(struct Periph_Keyboard *keyboard);
Bool key_ctrl_is_down(struct Periph_Keyboard *keyboard);
Bool key_ctrl_is_up(struct Periph_Keyboard *keyboard);
Bool key_shift_is_down(struct Periph_Keyboard *keyboard);
Bool key_shift_is_up(struct Periph_Keyboard *keyboard);
Bool key_mod_is_down(struct Periph_Keyboard *keyboard);
Bool key_mod_is_up(struct Periph_Keyboard *keyboard);

Bool button_is_down(struct Periph_Mouse *mouse, enum Periph_MouseButton button);
Bool button_is_up(struct Periph_Mouse *mouse, enum Periph_MouseButton button);
Bool button_was_pressed(struct Periph_Mouse *mouse, enum Periph_MouseButton button);
Bool button_was_released(struct Periph_Mouse *mouse, enum Periph_MouseButton button);

char ascii_from_key(enum Periph_KeyboardKey key, Bool key_shift_is_up);

#endif /* _peripheral_h */
