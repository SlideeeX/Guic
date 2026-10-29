#include "GUIC/Container.hpp"

namespace guic

{

Container::Container(){ setLayer(GUIC_BASE_CONTAINER_LAYER); changed = true;}

Container::Container(IntRect containerRect) :Interface(containerRect){ setLayer(GUIC_BASE_CONTAINER_LAYER); changed = true; };

void Container::add(Addable &item){
	item.setParentRect(getRect());
	items.item[items.size]=&item;
	items.item[items.size]->_add();
	items.size++;

	changed = true;
}

void Container::remove(Addable &item){
	for(int i=0; i!=items.size; i++){
		if(items.item[i]==&item){
			items.item[i]->_remove();
			changed = true;
			break;
		}
	}
}

void Container::clear(){
	items.size = 0;
	changed = true;
}

void Container::setRect(IntRect rect){
	Addable::setRect(rect);
	for(int i=0; i<items.size; i++){
		items.item[i]->setParentRect(rect);
	}
}

void Container::control(Modal modal){
	for(int i=0; i<items.size; i++){
		if(items.item[i]->isShow()) {
			items.item[i]->control(modal);
			if(items.item[i]->isChanged()){
				changed = true;
				break;
			}
		}
	}
}

void Container::draw(RenderWindow* window){
	if(items.size<1 || changed == false) return;

	for(int j=1; j<=GUIC_MAX_LAYER; j++){
		for(int i=0; i<items.size; i++){
			if(items.item[i]->isShow() && items.item[i]->getLayer()==j) {
				items.item[i]->update();
				items.item[i]->draw(window);
				items.item[i]->_unchange();
			}
		}
	}

	for(int i=0; i<items.size; i++){
		if(items.item[i]->isShow() && items.item[i]->getLayer()==0){
			items.item[i]->update();
			items.item[i]->draw(window);
			items.item[i]->_unchange();
		}
	}

	changed = false;
}

};

