#include "GUIC/MultilineTitle.hpp"

namespace guic

{

MultilineTitle::MultilineTitle(){
	size = GUIC_BASE_CHAR_SIZE;
	linetitle.clear();
	setLayer(GUIC_BASE_MLTITLE_LAYER);
	font = BaseFont;
};

MultilineTitle::MultilineTitle(IntRect mlRect, const char* mlTitle, String file) :Interface(mlRect, file){
	linetitle = mlTitle;

	size = GUIC_BASE_CHAR_SIZE;
	font = BaseFont;

	createMaskFromColor(Color::White);
	create();

	setLayer(GUIC_BASE_MLTITLE_LAYER);
};

MultilineTitle::MultilineTitle(IntRect mlRect, const char* mlTitle, Image* mlImage) :Interface(mlRect, mlImage){
	linetitle = mlTitle;

	size = GUIC_BASE_CHAR_SIZE;
	font = BaseFont;

	createMaskFromColor(Color::White);
	create();

	setLayer(GUIC_BASE_MLTITLE_LAYER);
};

MultilineTitle::MultilineTitle(IntRect mlRect, const char* mlTitle) :Interface(mlRect){
	linetitle = mlTitle;

	size = GUIC_BASE_CHAR_SIZE;
	font = BaseFont;

	createMaskFromColor(Color::White);
	create();

	setLayer(GUIC_BASE_MLTITLE_LAYER);
};

void MultilineTitle::create() {
	charwidth=size/2+size%2;
	charheight=size-size/3;
	length=0;
	Vector2f pos;
	pos.x = Rect.left;
	pos.y = Rect.top;
	int width = Rect.width;
	String bufline="";

	for(int i=0; i<GUIC_MAX_MLTITLE_LENGHT; i++){
		words[i].clear();
	}

	for(long long unsigned int i=0, j=0; i<linetitle.getSize()+1; i++){
		words[j].operator +=(linetitle[i]);
		if(linetitle[i]==' ' || linetitle[i]=='\0'){
			j++;
		}
	}
	for(int i=0, j=0, k=0; !words[i].isEmpty() && i<GUIC_MAX_MLTITLE_ROWS; i++){
		length += words[i].getSize()*charwidth;
		bufline.operator +=(words[i]);
		if(length<width || k==0){
			lines[j].setString(bufline);
			lines[j].setPosition(pos);
			lines[j].setFont(font);
			lines[j].setCharacterSize(size);
			lines[j].setFillColor(Color::Black);
			j++;
			k++;
		} else {
			length = 0;
			pos.y += size;
			bufline="";
			i--;
			k=0;
		}
	}

	changed = true;
}

int MultilineTitle::getCharacterSize(){
	return size;
}

float MultilineTitle::getCharWidth(){ return charwidth; }

void MultilineTitle::setString(String string){
	linetitle = string;
	create();
}

void MultilineTitle::setFont(Font mlFont){
	font = mlFont;
	create();
}

void MultilineTitle::setColor(Color mlColor){
	for(int i=0; lines[i].getString()!=""; i++){
		lines[i].setFillColor(mlColor);
	}
	changed = true;
}

void MultilineTitle::setPosition(float x, float y){
	for(int i=0; lines[i].getString()!=""; i++){
		lines[i].setPosition(ParentRect.left + x, ParentRect.top + y);
	}
	changed = true;
}

void MultilineTitle::setRect(IntRect mlRect){
	Addable::setRect(mlRect);
	create();
}

void MultilineTitle::setCharacterSize(int charSize){
	size = charSize;
	create();
}

void MultilineTitle::draw(RenderWindow* window){
	window->draw(getSprite());
	for(int i=0; lines[i].getString()!=""; i++){
		window->draw(lines[i]);
	}
}

}
