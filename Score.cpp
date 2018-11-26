#include <SFML/Graphics.hpp>
#include "Constants.h"

using namespace sf;

void drawScore(RenderWindow *window, Font font, int money)
{
	char moneyChain[12];
	float text_moneyWidth;
	if (money > 999999999)
		money = 999999999;
	Text text_money;
	text_money.setFont(font);
	sprintf(moneyChain, "%i $", money);
	text_money.setString(moneyChain);
	text_money.setCharacterSize(20);
	text_money.setFillColor(Color::Yellow);
	text_moneyWidth = text_money.getLocalBounds().width;
	text_money.setPosition((WINDOW_WIDTH - 20 - text_moneyWidth), 20);
	window->draw(text_money);
}