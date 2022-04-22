#include "./asset.h"

struct Assets assets;

struct Font *
asset_font_default(void)
{
	struct Font *result = &assets.fonts[assets.font_default];
	return(result);
}
