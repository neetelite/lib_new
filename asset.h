#ifndef _asset_h
#define _asset_h

#include "./font.h"
#include "./scalar/natural.h"

struct Assets
{
	n32 font_default;
	struct Font ARR_D fonts;
};

extern struct Assets assets;

/* Functions */
struct Font * asset_font_default(void);

#endif /* _asset_h */
