#include "GUIC/Title.hpp"

namespace guic

{

Title::Title(){
	charheight = 0;
	charwidth = 0;

	title.setFont(BaseFont);
	title.setCharacterSize(GUIC_BASE_CHAR_SIZE);
	title.setFillColor(BaseTextColor);
	size = GUIC_BASE_CHAR_SIZE-GUIC_BASE_CHAR_SIZE/3;
	charheight = GUIC_BASE_CHAR_SIZE-GUIC_BASE_CHAR_SIZE/3;
	charwidth = GUIC_BASE_CHAR_SIZE/2+GUIC_BASE_CHAR_SIZE%2;

	rect.width = charwidth;
	rect.height = charheight;
	rect.top = 0;
	rect.left = 0;

	setLayer(GUIC_BASE_TITLE_LAYER);
};

Title::Title(IntRect titleRect, String titleString) :Interface(titleRect){
	strtitle = titleString;
	charheight = 0;
	charwidth = 0;

	rect = titleRect;
	size = GUIC_BASE_CHAR_SIZE;

	charheight = GUIC_BASE_CHAR_SIZE-GUIC_BASE_CHAR_SIZE/3;
	charwidth = GUIC_BASE_CHAR_SIZE/2+GUIC_BASE_CHAR_SIZE%2;

	title.setFont(BaseFont);
	title.setCharacterSize(GUIC_BASE_CHAR_SIZE);

	setLayer(GUIC_BASE_TITLE_LAYER);

	title.setString(strtitle);
	title.setPosition(titleRect.left, titleRect.top);
	title.setFillColor(BaseTextColor);

	createMaskFromColor(Color::White);

	rect.width = getTitleWidth();
	rect.height = getTitleHeight();

	setLayer(GUIC_BASE_TITLE_LAYER);
};

Title::Title(IntRect titleRect, String titleString, int charSize) :Interface(titleRect){
	strtitle = titleString;
	charheight = 0;
	charwidth = 0;

	rect = titleRect;

	title.setString(strtitle);
	title.setFont(BaseFont);
	title.setPosition(titleRect.left, titleRect.top);
	title.setCharacterSize(charSize);
	title.setFillColor(BaseTextColor);

	createMaskFromColor(Color::White);

	charwidth = charSize/2+charSize%2;
	charheight = charSize-charSize/3;

	rect.width = getTitleWidth();
	rect.height = getTitleHeight();

	setLayer(GUIC_BASE_TITLE_LAYER);
};

String Title::getString(){ return strtitle; }

Vector2f Title::getPosition(){ return title.getPosition(); }

IntRect Title::getTitleRect(){ return rect; }

int Title::getLenght(){ return strtitle.getSize(); }

float Title::getTitleWidth(){ return charwidth*strtitle.getSize(); }

float Title::getTitleHeight(){ return charheight*!strtitle.isEmpty();  }

float Title::getCharWidth(){ return charwidth; }

float Title::getCharHeight(){ return charheight; }

int Title::getCharacterSize(){ return title.getCharacterSize(); }

void Title::setTitleRect(IntRect titleRect){ rect = titleRect; changed = true; }

void Title::setBackground(Color color){
	IntRect rect = getTitleRect();

	Image image;
	image.create(rect.width, rect.height, color);
	setRectImage(&image, rect);

	createMaskFromColor(Color::White, rect);

	changed = true;
}

void Title::setString(String str){
	title.setString(str);
	strtitle = str;
	rect.width = getTitleWidth();

	changed = true;
}

void Title::setCharacterSize(unsigned int charSize){
	title.setCharacterSize(charSize);
	charwidth = charSize/2+charSize%2;
	charheight = charSize-charSize/3;;

	rect.height = getTitleHeight();
	rect.width = getTitleWidth();

	changed = true;
}

void Title::setFont(Font Font){
	title.setFont(Font);
	changed = true;
}

void Title::setColor(Color Color){
	title.setFillColor(Color);
	changed = true;
}

void Title::setPosition(float x, float y){
	int newX = ParentRect.left + x; int newY = ParentRect.top + y;
	title.setPosition(newX, newY);
	rect.left = newX;
	rect.top = newY;
	changed = true;
}

void Title::setRect(IntRect titleRect) {
	Addable::setRect(titleRect);
	title.setPosition(titleRect.left + ParentRect.left, titleRect.top + ParentRect.top);
	changed = true;
}

void Title::setPosition(Vector2f pos){
	Vector2f newPos = Vector2f(ParentRect.left + pos.x, ParentRect.top + pos.y);
	title.setPosition(newPos);
	rect.left = newPos.x;
	rect.top = newPos.y;
	changed = true;
}

void Title::draw(RenderWindow* window) {
	window->draw(getSprite());
	window->draw(title);
}

}
