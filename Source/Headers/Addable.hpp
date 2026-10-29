#ifndef ADDABLE_HPP
#define ADDABLE_HPP

#include <GUIC/Variables.hpp>

#ifndef GUIC_MAX_ITEMS
#define GUIC_MAX_ITEMS 10000
#endif

#ifndef GUIC_BASE_HIGH_LAYER
#define GUIC_BASE_HIGH_LAYER 0
#endif

#ifdef __cplusplus
extern "C"
{
#endif

namespace guic

{

using namespace sf;

struct DLLIMPORT Modal
{
	Event event;
	Vector2f pos;
};

class DLLIMPORT Addable

{

public:
	bool changed;

	Image getImage();

	Image* getImagePointer();

	Texture getTexture();

	Texture* getTexturePointer();

	Sprite getSprite();

	Sprite* getSpritePointer();

	IntRect getRect();

	IntRect getParentRect();

	IntRect getTextureRect();

	int getLayer();

	bool isAdded();

	bool isShow();

	bool isChanged();

	void show();

	void hide();

	void _add();

	void _remove();

	void _unchange();

	void update();

	void setTextureRect(IntRect rect);

	void setPosition(int X, int Y);

	void setRectImage(Image* image, IntRect rect);

	void setImage(Image* image);

	void setImage(String path);

	virtual void setRect(IntRect rect);

	void setParentRect(IntRect rect);

	void setLayer(unsigned int Layer);

	void createMaskFromColor(Color color, IntRect rect);

	void createMaskFromColor(Color color);

	virtual void control(Modal modal);

	virtual void draw(RenderWindow* window);

protected:

	bool added;
	bool forshow;
	unsigned int layer;
	IntRect Rect;
	IntRect ParentRect;

	Addable();

	Addable(IntRect Rect);

	Addable(IntRect Rect, Image* Image);

private:

	Sprite* _sprite;
	Image* _image;
	Texture* _texture;

};

struct DLLIMPORT Items
{
	Addable* item[GUIC_MAX_ITEMS];
	int size = 0;
};

}

#ifdef __cplusplus
}
#endif

#endif
