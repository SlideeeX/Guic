#include "GUIC/Addable.hpp"

namespace guic

{

Addable::Addable()
{
	Rect = IntRect(0, 0, 0, 0);
	ParentRect = IntRect(0, 0, 0, 0);
	added = false;
	forshow = false;
	layer = GUIC_BASE_HIGH_LAYER;
	_sprite = new Sprite;
	_image = new Image;
	_texture = new Texture;
	changed = true;
}

Addable::Addable(IntRect rect){
	Rect = rect;
	ParentRect = IntRect(0, 0, 0, 0);
	added = false;
	forshow = false;
	layer = GUIC_BASE_HIGH_LAYER;
	_sprite = new Sprite;
	_image = new Image;
	_texture = new Texture;
	changed = true;
};

Addable::Addable(IntRect rect, Image* image){
	Rect = rect;
	ParentRect = IntRect(0, 0, 0, 0);
	added = false;
	forshow = false;
	layer = GUIC_BASE_HIGH_LAYER;
	_sprite = new Sprite;
	_image = image;
	_texture = new Texture;

	setImage(image);
	changed = true;
}

Image Addable::getImage() { return *_image; }

Image* Addable::getImagePointer() { return _image; }

Texture Addable::getTexture() { return *_texture; }

Texture* Addable::getTexturePointer() { return _texture; }

Sprite Addable::getSprite() { return *_sprite; }

Sprite* Addable::getSpritePointer() { return _sprite; }

IntRect Addable::getRect() { return Rect; }

IntRect Addable::getTextureRect() { return _sprite->getTextureRect(); }

int Addable::getLayer() { return layer; }

bool Addable::isAdded() { return added; }

bool Addable::isShow() { return forshow; }

bool Addable::isChanged() { return changed; }

void Addable::show() {
	if(forshow) return;
	forshow = true; changed = true;
}

void Addable::hide() {
	if(!forshow) return;
	forshow = false; changed = true;
}

void Addable::_add() { added = true; changed = true; }

void Addable::_remove() { added = false; changed = true; }

void Addable::_unchange() { changed = false; }

void Addable::update() { changed = true; }

void Addable::setTextureRect(IntRect rect) { _sprite->setTextureRect(rect); changed = true; }

void Addable::setPosition(int X, int Y){
	int newX = ParentRect.left + X; int newY = ParentRect.top + Y;

	_sprite->setPosition(newX, newY);
	Rect.left = newX;
	Rect.top = newY;
	changed = true;
}

void Addable::setRectImage(Image* image, IntRect rect){
	Rect = rect;
	_image = image;
	_texture->loadFromImage(*_image);

	_sprite->setTexture(*_texture);
	_sprite->setTextureRect(IntRect(0, 0, rect.width, rect.height));
	_sprite->setPosition(Vector2f(rect.left, rect.top));

	changed = true;
}

void Addable::setImage(String path) {
	_image->loadFromFile(path);
	_texture->loadFromImage(*_image);

	_sprite->setTexture(*_texture);
	_sprite->setTextureRect(IntRect(0, 0, Rect.width, Rect.height));
	_sprite->setPosition(Rect.left, Rect.top);

	changed = true;
}

void Addable::setImage(Image* image) {
	_image = image;
	_texture->loadFromImage(*_image);

	_sprite->setTexture(*_texture);
	_sprite->setTextureRect(IntRect(0, 0, Rect.width, Rect.height));
	_sprite->setPosition(Rect.left, Rect.top);

	changed = true;
}

void Addable::setRect(IntRect rect) {
	Rect = IntRect(rect.left + ParentRect.left, rect.top + ParentRect.top, rect.width, rect.height);
	_sprite->setTextureRect(IntRect(0, 0, rect.width, rect.height));
	_sprite->setPosition(Rect.left, Rect.top);
	changed = true;
}

void Addable::setParentRect(IntRect rect) {
	ParentRect = rect;
	setRect(Rect);
}

void Addable::setLayer(unsigned int Layer) { layer = Layer; changed = true; }

void Addable::createMaskFromColor(Color color, IntRect rect){
	if(rect.height && rect.width && _image->getSize().x && _image->getSize().y){
		_image->createMaskFromColor(color);
		_texture->loadFromImage(*_image);
		_sprite->setTextureRect(rect);
		_sprite->setTexture(*_texture);
		changed = true;
	}
}

void Addable::createMaskFromColor(Color color){
	if(Rect.height && Rect.width && _image->getSize().x && _image->getSize().y){
		_image->createMaskFromColor(color);
		_texture->loadFromImage(*_image);
		_sprite->setTextureRect(Rect);
		_sprite->setTexture(*_texture);
		changed = true;
	}
}

void Addable::control(Modal modal){};

void Addable::draw(RenderWindow* window){};

}
