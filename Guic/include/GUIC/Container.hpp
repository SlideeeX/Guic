#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "Interface.hpp"

#ifndef GUIC_BASE_CONTAINER_LAYER
#define GUIC_BASE_CONTAINER_LAYER 1
#endif

#ifndef GUIC_MAX_LAYER
#define GUIC_MAX_LAYER 6
#endif

namespace guic

{

using namespace sf;

class DLLIMPORT Container :public Interface

{

private:

public:

	Items items;

	Container();

	Container(IntRect containerRect);

	void add(Addable &item);

	void remove(Addable &item);

	void clear();

	void setRect(IntRect rect) override;

	void control(Modal modal) override;

	void draw(RenderWindow* window) override;

};

}

#endif
