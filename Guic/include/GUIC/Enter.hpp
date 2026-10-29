#ifndef ENTER_HPP
#define ENTER_HPP

#include "Trigger.hpp"
#include "Title.hpp"

#ifndef GUIC_BASE_ENTER_INTERVAL
#define GUIC_BASE_ENTER_INTERVAL 5
#endif

namespace guic

{

class DLLIMPORT Enter : public Trigger
{
private:

	String str; // Реальная строка
	String visiblestr; // Видимая строка

	int leftOutChars; // Количество символов, выходящих за пределы влево
	int rightOutChars; // Количество символов, выходящих за пределы вправо
	int topOutChars; // Количество символов, выходящих за пределы влево
	int bottomOutChars; // Количество символов, выходящих за пределы вправо
	int visiblestrChars; // Количество символов, которые видно в строке
	int MaxVisStrChars; // Константа максимального количества видимых символов
	int chars; // Общее количество символов
	bool shift; // Текст выходит за пределы

    int upOutLines;
	int downOutLines; // Количество символов, выходящих за пределы вправо
	int visiblestrLines; // Количество символов, которые видно в строке
	int MaxVisStrLines; // Константа максимального количества видимых символов
	int lines; // Количество строк
	bool lshift;

	Vector2f leftpos; // Позиция слева в пикселях
	Vector2f defpos; // Начальная позиция в пикселях

	void control(Modal modal) override;

protected:

    class EnterCursor
    {
    private:
        int leftCharPosition; // Символьная позиция в строке
        int topCharPosition; // Строчная позиция в тексте

        Enter* enter; // Объект поля ввода

        Vector2f position; // Позиция курсора в пикселях
    protected:

    public:
        EnterCursor();
        EnterCursor(Enter* e);

        Interface textCursor;
        Image textCursorImage;

        int getLeftCharPosition();
        int getTopCharPosition();

        void setCharPosition(Vector2i pos);
        void setLeftCharPosition(int pos);
        void setTopCharPosition(int pos);

        void nextLeftCharPos(int Plus);
        void nextTopcharPos(int Plus);

        void show();
        void hide();
        void click(Vector2f pos);
        void draw(RenderWindow* window);
    };

public:

    EnterCursor textCursor;

	bool isEditMode;

	Title title;

	Enter();

	Enter(IntRect enterRect);

	Enter(IntRect enterRect, Image* enterImage);

	Enter(IntRect enterRect, String file);

	String getValue();

	void setRect(IntRect enterRect) override;

	void setValue(std::string enterStr);

	void draw(RenderWindow* window);

};

}

#endif
