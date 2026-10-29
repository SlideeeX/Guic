#include "GUIC/Enter.hpp"
#include <iostream>

namespace guic

{

Enter::Enter():Trigger(){
	leftOutChars = 0;
	rightOutChars = 0;
	topOutChars = 0;
	bottomOutChars = 0;

	shift = false;
	setLayer(GUIC_BASE_ENTER_LAYER);

	textCursor = EnterCursor(this);
};

Enter::Enter(IntRect enterRect):Trigger(enterRect){
	leftpos = defpos;
	leftOutChars = 0;
	rightOutChars = 0;
	topOutChars = 0;
	bottomOutChars = 0;

	shift = false;
	setLayer(GUIC_BASE_ENTER_LAYER);

	textCursor = EnterCursor(this);
};

Enter::Enter(IntRect enterRect, Image* enterImage):Trigger(enterRect, enterImage){
	leftpos = defpos;
	leftOutChars = 0;
	rightOutChars = 0;
	topOutChars = 0;
	bottomOutChars = 0;

	shift = false;
	setLayer(GUIC_BASE_ENTER_LAYER);

	textCursor = EnterCursor(this);
};

Enter::Enter(IntRect enterRect, String file):Trigger(enterRect, file){
	leftpos = defpos;
	leftOutChars = 0;
	rightOutChars = 0;
	topOutChars = 0;
	bottomOutChars = 0;

	shift = false;
	setLayer(GUIC_BASE_ENTER_LAYER);

	textCursor = EnterCursor(this);
};

void Enter::control(Modal modal){
	if (modal.event.type == Event::MouseButtonPressed){
		if (modal.event.mouseButton.button == Mouse::Left){
            leftpos.x = defpos.x-title.getCharWidth()*leftOutChars;

            if(Highlight(modal)){
                textCursor.click(modal.pos);
                isEditMode = true;
                textCursor.show();
            } else {
                visiblestr = str.substring(0, visiblestrChars);
                title.setString(visiblestr.toWideString());
                isEditMode = false;
                textCursor.hide();
            }
		}
		changed = true;
	}

	if(isEditMode && modal.event.type == sf::Event::KeyPressed){
        leftpos.x = defpos.x-title.getCharWidth()*leftOutChars;

        if(modal.event.key.code == sf::Keyboard::Right){
            textCursor.nextLeftCharPos(1); // Сдвиг на 1 позицию вправо
            changed = true;
        } else if(modal.event.key.code == sf::Keyboard::Left){
            textCursor.nextLeftCharPos(-1); // Сдвиг на 1 позицию влево
            changed = true;
        } else if(modal.event.key.code == sf::Keyboard::Up){

        } else if(modal.event.key.code == sf::Keyboard::Down){

        }
	}

	if (isEditMode && modal.event.type == sf::Event::TextEntered && modal.event.text.unicode != 0 && modal.event.text.unicode != 13){
        leftpos.x = defpos.x-title.getCharWidth()*leftOutChars;

		if(modal.event.text.unicode==8){
			if(shift){
				if(leftOutChars == 0){
					shift = false;
				}
			}
			if(textCursor.getLeftCharPosition()!=0){
                textCursor.nextLeftCharPos(-1);
				str.erase(textCursor.getLeftCharPosition());
                chars--;
			}
		} else {
		    str.insert(textCursor.getLeftCharPosition(), modal.event.text.unicode);
            chars++;
			if(!(title.getTitleWidth()<getRect().width-GUIC_BASE_ENTER_INTERVAL*3)){
				if(!shift){
                    MaxVisStrChars = chars-1;
                    shift = true;
				}
			}
			(bool)MaxVisStrChars ? visiblestrChars = MaxVisStrChars : visiblestrChars = chars;
			textCursor.nextLeftCharPos(1);
		}
		visiblestr = str.substring(leftOutChars, visiblestrChars);
		title.setString(visiblestr.toWideString());
		changed = true;
	}
}

String Enter::getValue(){ return str; }

void Enter::setRect(IntRect rect){
	Trigger::setRect(rect);
	defpos.x = Rect.left+GUIC_BASE_ENTER_INTERVAL;
	defpos.y = Rect.top+Rect.height/2-title.getCharHeight();
	title.setPosition(defpos);
	leftpos = defpos;
	changed = true;
}

void Enter::setValue(std::string enterStr){ str = enterStr; changed = true; }

void Enter::draw(RenderWindow* window){
	Trigger::draw(window);
	title.draw(window);
	textCursor.draw(window);
}

}

namespace guic

{
    Enter::EnterCursor::EnterCursor(){
        leftCharPosition = 0;
    };

    Enter::EnterCursor::EnterCursor(Enter* e){
        enter = e;
        leftCharPosition = 0;
        textCursorImage.create(1, enter->title.getCharHeight(), Color::White);
        textCursor = Interface(IntRect(0, 0, 1, enter->title.getCharHeight()), &textCursorImage);
    };

    int Enter::EnterCursor::getLeftCharPosition(){ return leftCharPosition; };
    int Enter::EnterCursor::getTopCharPosition(){ return topCharPosition; };

    void Enter::EnterCursor::setCharPosition(Vector2i pos){
        setLeftCharPosition(pos.x);
        setTopCharPosition(pos.y);
    }

    void Enter::EnterCursor::setLeftCharPosition(int pos){
        if(pos > enter->str.getSize() || pos < 0){
            return;
        }

        int charshift = (leftCharPosition-pos) * -1;

        leftCharPosition += charshift;

        int charWidth = enter->title.getCharWidth();
        Vector2f defpos = enter->defpos;

        int x_position = charWidth*leftCharPosition+enter->leftpos.x;

        if(x_position < defpos.x){
            if(enter->leftOutChars>0){
                enter->leftOutChars--;
            }
        } else if(x_position > defpos.x+charWidth*enter->visiblestrChars){
            enter->leftOutChars++;
        } else {
            position.x = x_position;
            textCursor.setPosition(position.x, position.y);
        }

        enter->visiblestr = enter->str.substring(enter->leftOutChars, enter->visiblestrChars);
        enter->title.setString(enter->visiblestr.toWideString());
    };
    void Enter::EnterCursor::setTopCharPosition(int pos){
        /*topCharPosition = pos;

        int charHeight = enter->title.getCharHeight();
        Vector2f leftpos = enter->leftpos;

        int y_position = leftpos.y+charHeight*pos+charHeight/2;

        position.y = y_position;
        textCursor.setPosition(position.x, position.y);*/

        if(pos > enter->str.getSize() || pos < 0){
            return;
        }

        int charshift = (topCharPosition-pos) * -1;

        topCharPosition += charshift;

        int charHeight = enter->title.getCharHeight();
        Vector2f defpos = enter->defpos;

        int y_position = charHeight/2 + charHeight*topCharPosition+enter->leftpos.y;

        if(y_position < defpos.y){
            if(enter->topOutChars>0){
                enter->topOutChars--;
            }
        //} else if(y_position > defpos.y+charHeight*enter->visiblestrChars){
        //    enter->topOutChars++;
        } else {
            position.y = y_position;
            textCursor.setPosition(position.x, position.y);
        }

        //enter->visiblestr = enter->str.substring(enter->leftOutChars, enter->visiblestrChars);
        //enter->title.setString(enter->visiblestr.toWideString());
    };

    void Enter::EnterCursor::nextLeftCharPos(int Plus){
        setLeftCharPosition(getLeftCharPosition()+Plus);
    };

    void Enter::EnterCursor::nextTopcharPos(int Plus){
        setLeftCharPosition(getTopCharPosition()+Plus);
    };

    void Enter::EnterCursor::show(){
        textCursor.show();
    };
    void Enter::EnterCursor::hide(){
        textCursor.hide();
    };

    void Enter::EnterCursor::click(Vector2f pos){
        /*int ssize = enter->str.getSize(); // Размер строки
        int line = enter->line; // Текущая строка
        int charWidth = enter->title.getCharWidth(); // Ширина символа
        int charHeight = enter->title.getCharHeight(); // Высота символа
        Vector2f leftpos = enter->leftpos; // Позиция текста слева
        int dif_x = pos.x - leftpos.x; // Разница между позициями в символах
        int dif_y = pos.y - leftpos.y; // Разница между позициями в строках
        float rem = dif_x % charWidth; // Отклонение
        int charPosX = dif_x/charWidth; // Позиция в символах
        int charPosY = dif_y/charHeight; // Позиция в строках

        rem>4 ? charPosX += 1 : charPosX;
        charPosX>ssize ? charPosX=ssize : charPosX;
        charPosY>line ? charPosY=line : charPosY;

        setLeftCharPosition(charPosX);
        setTopCharPosition(charPosY);*/

        if(!enter->isEditMode){
            leftCharPosition = 0;
            setLeftCharPosition(enter->str.getSize());
            setTopCharPosition(0);
            return;
        }

        int charWidth = enter->title.getCharWidth();

        Vector2f defpos = enter->defpos;
        int visChars = enter->visiblestrChars;

        int xPos = pos.x-defpos.x;
        int charPosX = xPos/enter->title.getCharWidth();

        float rem = xPos % charWidth;
        rem>charWidth/2 ? charPosX += 1 : charPosX;

        setLeftCharPosition(charPosX+enter->leftOutChars);
        setTopCharPosition(0);
    }

    void Enter::EnterCursor::draw(RenderWindow* window){
        if(textCursor.isShow()){
            textCursor.draw(window);
        }
    };
}
