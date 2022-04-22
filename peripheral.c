#include "./peripheral.h"

/* Keyboard */
inline Bool
key_is_up(struct Periph_Keyboard *keyboard, enum Periph_KeyboardKey key)
{
	return(keyboard->key[key] % 2 == 0);
}

inline Bool
key_is_down(struct Periph_Keyboard *keyboard, enum Periph_KeyboardKey key)
{
	return(keyboard->key[key] % 2 == 1);
}

inline Bool
key_was_pressed(struct Periph_Keyboard *keyboard, enum Periph_KeyboardKey key)
{
	return(keyboard->key[key] % 2 == 1 && keyboard->key_last[key] % 2 == 0);
}

inline Bool
key_was_released(struct Periph_Keyboard *keyboard, enum Periph_KeyboardKey key)
{
	return(keyboard->key[key] % 2 == 0 && keyboard->key_last[key] % 2 == 1);
}

inline Bool
key_alt_is_down(struct Periph_Keyboard *keyboard)
{
	#if OS == OS_LINUX
	return(key_is_down(keyboard, KEY_ALT_LEFT) || key_is_down(keyboard, KEY_ALT_RIGHT));
	#elif OS == OS_WINDOWS
	return(key_is_down(keyboard, KEY_ALT));
	#endif
}

inline Bool
key_alt_is_up(struct Periph_Keyboard *keyboard)
{
	return(key_alt_is_down(keyboard) == FALSE);
}

inline Bool
key_ctrl_is_down(struct Periph_Keyboard *keyboard)
{
	#if OS == OS_LINUX
	return(key_is_down(keyboard, KEY_CTRL_LEFT) || key_is_down(keyboard, KEY_CTRL_RIGHT));
	#elif OS == OS_WINDOWS
	return(key_is_down(keyboard, KEY_CTRL));
	#endif
}

inline Bool
key_ctrl_is_up(struct Periph_Keyboard *keyboard)
{
	return(key_ctrl_is_down(keyboard) == FALSE);
}

inline Bool
key_shift_is_down(struct Periph_Keyboard *keyboard)
{
	#if OS == OS_LINUX
	return(key_is_down(keyboard, KEY_SHIFT_LEFT) || key_is_down(keyboard, KEY_SHIFT_RIGHT));
	#elif OS == OS_WINDOWS
	return(key_is_down(KEY_SHIFT));
	#endif
}

inline Bool
key_shift_is_up(struct Periph_Keyboard *keyboard)
{
	return(key_shift_is_down(keyboard) == FALSE);
}

inline Bool
key_mod_is_down(struct Periph_Keyboard *keyboard)
{
	#if OS == OS_LINUX
	return(key_is_down(keyboard, KEY_MOD_LEFT) || key_is_down(keyboard, KEY_MOD_LEFT));
	#elif OS == OS_WINDOWS
	return(key_is_down(keyboard, KEY_MOD));
	#endif
}

inline Bool
key_mod_is_up(struct Periph_Keyboard *keyboard)
{
	return(key_mod_is_down(keyboard) == FALSE);
}

/* Mouse */
inline Bool
button_is_down(struct Periph_Mouse *mouse, enum Periph_MouseButton button)
{
	return(mouse->button[button] % 2 == 1);
}

inline Bool
button_is_up(struct Periph_Mouse *mouse, enum Periph_MouseButton button)
{
	return(mouse->button[button] % 2 == 0);
}

inline Bool
button_was_pressed(struct Periph_Mouse *mouse, enum Periph_MouseButton button)
{
	return(mouse->button[button] % 2 == 1 && mouse->button_last[button] % 2 == 0);
}

inline Bool
button_was_released(struct Periph_Mouse *mouse, enum Periph_MouseButton button)
{
	return(mouse->button[button] % 2 == 0 && mouse->button_last[button] % 2 == 1);
}

/* Typing */
char
ascii_from_key(enum Periph_KeyboardKey key, Bool key_shift_is_up)
{
	/* Independed if shift is pressed */
	switch(key)
	{
		case KEY_TAB: return('\t');
		case KEY_ENTER: return('\n');
		case KEY_SPACE: return(' ');
	}

	/* Dependednt on shift */
	if(key_shift_is_up)
	{
		switch(key)
		{
			/* Numbers */
			case KEY_0: return('0');
			case KEY_1: return('1');
			case KEY_2: return('2');
			case KEY_3: return('3');
			case KEY_4: return('4');
			case KEY_5: return('5');
			case KEY_6: return('6');
			case KEY_7: return('7');
			case KEY_8: return('8');
			case KEY_9: return('9');

			/* Letters */
			case KEY_A: return('a');
			case KEY_B: return('b');
			case KEY_C: return('c');
			case KEY_D: return('d');
			case KEY_E: return('e');
			case KEY_F: return('f');
			case KEY_G: return('g');
			case KEY_H: return('h');
			case KEY_I: return('i');
			case KEY_J: return('j');
			case KEY_K: return('k');
			case KEY_L: return('l');
			case KEY_M: return('m');
			case KEY_N: return('n');
			case KEY_O: return('o');
			case KEY_P: return('p');
			case KEY_Q: return('q');
			case KEY_R: return('r');
			case KEY_S: return('s');
			case KEY_T: return('t');
			case KEY_U: return('u');
			case KEY_V: return('v');
			case KEY_W: return('w');
			case KEY_X: return('x');
			case KEY_Y: return('y');
			case KEY_Z: return('z');

			/* Special */
			case KEY_TILDE:         return('`');
			case KEY_MINUS:         return('-');
			case KEY_PLUS:          return('=');
			case KEY_COLON:         return(';');
			case KEY_QUOTE:         return('\'');
			case KEY_COMMA:         return(',');
			case KEY_PERIOD:        return('.');
			case KEY_BRACKET_LEFT:  return('[');
			case KEY_BRACKET_RIGHT: return(']');
			case KEY_SLASH_LEFT:    return('\\');
			case KEY_SLASH_RIGHT:   return('/');
		};
	}
	else
	{
		switch(key)
		{
			/* Numbers */
			case KEY_0: return(')');
			case KEY_1: return('!');
			case KEY_2: return('@');
			case KEY_3: return('#');
			case KEY_4: return('$');
			case KEY_5: return('%');
			case KEY_6: return('^');
			case KEY_7: return('&');
			case KEY_8: return('*');
			case KEY_9: return('(');

			/* Letters */
			case KEY_A: return('A');
			case KEY_B: return('B');
			case KEY_C: return('C');
			case KEY_D: return('D');
			case KEY_E: return('E');
			case KEY_F: return('F');
			case KEY_G: return('G');
			case KEY_H: return('H');
			case KEY_I: return('I');
			case KEY_J: return('J');
			case KEY_K: return('K');
			case KEY_L: return('L');
			case KEY_M: return('M');
			case KEY_N: return('N');
			case KEY_O: return('O');
			case KEY_P: return('P');
			case KEY_Q: return('Q');
			case KEY_R: return('R');
			case KEY_S: return('S');
			case KEY_T: return('T');
			case KEY_U: return('U');
			case KEY_V: return('V');
			case KEY_W: return('W');
			case KEY_X: return('X');
			case KEY_Y: return('Y');
			case KEY_Z: return('Z');

			case KEY_TILDE:         return('~');
			case KEY_MINUS:         return('_');
			case KEY_PLUS:          return('+');
			case KEY_COLON:         return(':');
			case KEY_QUOTE:         return('"');
			case KEY_COMMA:         return('<');
			case KEY_PERIOD:        return('>');
			case KEY_BRACKET_LEFT:  return('{');
			case KEY_BRACKET_RIGHT: return('}');
			case KEY_SLASH_LEFT:    return('|');
			case KEY_SLASH_RIGHT:   return('?');
		};
	}

	return('\0');
}
