#include <SFML/Audio.hpp>

#include "Structures.h"
#include "GameEngine.h"

using namespace sf;

void startGamemodeMenu(RenderWindow *gamemodeWindow, Font *font, Sprite *background, Sprite *logo, SoundBuffer *buffer, SoundBuffer *dejavuBuffer)
{
	float text_soloWidth, text_multiWidth, backWidth;
	float mouseX = 0, mouseY = 0;

	gamemodeWindow->clear();

	//Draw logo and background
	gamemodeWindow->draw(*background);
	gamemodeWindow->draw(*logo);

	RectangleShape box_solo(Vector2f(MENU_BOX_WIDTH, MENU_BOX_HEIGHT));
	RectangleShape box_multi(Vector2f(MENU_BOX_WIDTH, MENU_BOX_HEIGHT));
	box_solo.setPosition(200, 400);
	box_multi.setPosition(200, 525);

	box_solo.setFillColor(Color::Blue);
	box_solo.setOutlineThickness(MENU_OUTLINE);
	box_multi.setFillColor(Color::Blue);
	box_multi.setOutlineThickness(MENU_OUTLINE);

	RectangleShape box_back_menu(Vector2f(SETTINGS_BOX_WIDTH, SETTINGS_BOX_HEIGHT));
	box_back_menu.setFillColor(Color::Blue);
	box_back_menu.setOutlineThickness(OUTLINE_SETTINGS_BOX);
	box_back_menu.setPosition(850, 650);

	Text text_solo;
	text_solo.setFont(*font);
	text_solo.setString("Solo");
	text_solo.setCharacterSize(MENU_FONT_SIZE);
	text_soloWidth = text_solo.getLocalBounds().width;
	text_solo.setPosition((WINDOW_WIDTH - text_soloWidth) / 2, 400);

	Text text_multi;
	text_multi.setFont(*font);
	text_multi.setString("Multijoueur");
	text_multi.setCharacterSize(MENU_FONT_SIZE);
	text_multiWidth = text_multi.getLocalBounds().width;
	text_multi.setPosition((WINDOW_WIDTH - text_multiWidth) / 2, 525);

	Text back;
	back.setFont(*font);
	back.setString("Retour");
	back.setCharacterSize(70);
	backWidth = back.getLocalBounds().width;
	back.setPosition(850 + (SETTINGS_BOX_WIDTH - backWidth) / 2, 650);

	gamemodeWindow->draw(box_solo);
	gamemodeWindow->draw(box_multi);
	gamemodeWindow->draw(box_back_menu);
	gamemodeWindow->draw(text_solo);
	gamemodeWindow->draw(text_multi);
	gamemodeWindow->draw(back);
	gamemodeWindow->display();

	//Detect interaction
	while (gamemodeWindow->isOpen())
	{
		mouseX = Mouse::getPosition(*gamemodeWindow).x;
		mouseY = Mouse::getPosition(*gamemodeWindow).y;
		Event event;
		while (gamemodeWindow->pollEvent(event))
		{
			if (event.type == Event::Closed)
				gamemodeWindow->close();
			if (box_solo.getGlobalBounds().contains(Vector2f(mouseX, mouseY))) {
				if (Mouse::isButtonPressed(Mouse::Left)) {
					startGame(*gamemodeWindow, background, false, buffer, dejavuBuffer);
				}
			}
			if (box_multi.getGlobalBounds().contains(Vector2f(mouseX, mouseY))) {
				if (Mouse::isButtonPressed(Mouse::Left)) {
					startGame(*gamemodeWindow, background, true, buffer, dejavuBuffer);
				}
			}
			if (box_back_menu.getGlobalBounds().contains(Vector2f(mouseX, mouseY)))
				if (Mouse::isButtonPressed(Mouse::Left)) {
					while (Mouse::isButtonPressed(Mouse::Left)) {
					}
					return;
				}
		}

	}
}