class Background
{
public:
	// variables
	float x;
	float y;
	ALLEGRO_BITMAP *sprite;
	std::string background;

	// Fuciones
	Background(std::string background);
	void action();
};

Background::Background(std::string background)
{
	sprite = al_load_bitmap(background.c_str());
	this->background = background;
	this->x = 0;
	this->y = 0;
}

void Background::action()
{

	const int spriteH = al_get_bitmap_height(sprite);
	const int spriteW = al_get_bitmap_width(sprite);

	al_draw_bitmap(sprite, x, spriteH * -1 + y, 0);
	al_draw_bitmap(sprite, x, spriteH * -2 + y, 0);
	al_draw_bitmap(sprite, x, y, 0);
	al_draw_bitmap(sprite, x, spriteH + y, 0);
	al_draw_bitmap(sprite, x, spriteH * 2 + y, 0);
	y += 1;

	if (y <= spriteH * -1 or y >= spriteH)
	{
		y = 0;
	}
}
