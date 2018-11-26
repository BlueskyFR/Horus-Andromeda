#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "GameEngine.h"
#include "Settings.h"
#include "Shop.h"
#include "Structures.h"
#include "SaveFile.h"
#include "GamemodeMenu.h"
#include "Discord.h"
#include <Windows.h>


using namespace sf;
void menu(RenderWindow *window, Font *font, Sprite *background, Sprite *logo, SoundBuffer *buffer, SoundBuffer *dejavuBuffer);

int main() {
	// Discord init + set rich presence
	InitDiscord();
	UpdatePresence();

	SoundBuffer buffer;
	buffer.loadFromFile("res/music.wav");
	
	SoundBuffer dejavuBuffer;
	dejavuBuffer.loadFromFile("res/dejavu.wav");

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGH), "Horus : Andromeda 1.0.1");

	Texture background_texture;
	if (!background_texture.loadFromFile("res/background.png"))
		return EXIT_FAILURE;
	Sprite background(background_texture);

	Texture logo_texture;
	if (!logo_texture.loadFromFile("res/logo.png"))
		return EXIT_FAILURE;
	Sprite logo(logo_texture);

	Font font;
	if (!font.loadFromFile("res/Righteous-Regular.ttf"))
	{
		return EXIT_FAILURE;
	}

	while (window.isOpen())
	{
		menu(&window, &font, &background, &logo, &buffer, &dejavuBuffer);
		window.clear();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
	}

	return EXIT_SUCCESS;
}

void menu(RenderWindow *window, Font *font, Sprite *background, Sprite *logo, SoundBuffer *buffer, SoundBuffer *dejavuBuffer)
{
	float playWidth, shopWidth, settingsWidth, quitWidth;
	float mouseX = 0, mouseY = 0;

	//Draw logo and background
	window->draw(*background);
	(*logo).setPosition((WINDOW_WIDTH - 800) / 2, 50);
	window->draw(*logo);

	//Creation of choice box
	RectangleShape box_play(Vector2f(MENU_BOX_WIDTH, MENU_BOX_HEIGHT));
	RectangleShape box_shop(Vector2f(MENU_BOX_WIDTH, MENU_BOX_HEIGHT));
	RectangleShape box_settings(Vector2f(MENU_BOX_WIDTH_SPECIAL, MENU_BOX_HEIGHT));
	RectangleShape box_quit(Vector2f(MENU_BOX_WIDTH_SPECIAL, MENU_BOX_HEIGHT));

	box_play.setPosition(200, 400);
	box_shop.setPosition(200, 525);
	box_settings.setPosition(200, 650);
	box_quit.setPosition(200 + MENU_BOX_WIDTH_SPECIAL + 20, 650);

	//Set color of choice Box
	box_play.setFillColor(Color::Blue);
	box_play.setOutlineThickness(MENU_OUTLINE);
	box_shop.setFillColor(Color::Blue);
	box_shop.setOutlineThickness(MENU_OUTLINE);
	box_settings.setFillColor(Color::Blue);
	box_settings.setOutlineThickness(MENU_OUTLINE);
	box_quit.setFillColor(Color::Blue);
	box_quit.setOutlineThickness(MENU_OUTLINE);

	window->draw(box_play);
	window->draw(box_shop);
	window->draw(box_settings);
	window->draw(box_quit);

	//Put text into choice box
	Text play;
	play.setFont(*font);
	play.setString("Jouer");
	play.setCharacterSize(MENU_FONT_SIZE);
	playWidth = play.getLocalBounds().width;
	play.setPosition((WINDOW_WIDTH - playWidth) / 2, 400);

	Text shop;
	shop.setFont(*font);
	shop.setString("Shop");
	shop.setCharacterSize(MENU_FONT_SIZE);
	shopWidth = shop.getLocalBounds().width;
	shop.setPosition((WINDOW_WIDTH - shopWidth) / 2, 525);

	Text settings;
	settings.setFont(*font);
	settings.setString("Paramètres");
	settings.setCharacterSize(MENU_FONT_SIZE);
	settingsWidth = settings.getLocalBounds().width;
	settings.setPosition(200 + (MENU_BOX_WIDTH_SPECIAL - settingsWidth) / 2, 650);

	Text quit;
	quit.setFont(*font);
	quit.setString("Quitter");
	quit.setCharacterSize(MENU_FONT_SIZE);
	quitWidth = quit.getLocalBounds().width;
	quit.setPosition(220 + MENU_BOX_WIDTH_SPECIAL + (MENU_BOX_WIDTH_SPECIAL - quitWidth) / 2, 650);

	window->draw(play);
	window->draw(shop);
	window->draw(settings);
	window->draw(quit);
	window->display();

	Event menu_event;
	while (window->pollEvent(menu_event))
	{
		mouseX = Mouse::getPosition(*window).x;
		mouseY = Mouse::getPosition(*window).y;
		if (menu_event.type == Event::Closed)
			window->close();
		if (box_play.getGlobalBounds().contains(Vector2f(mouseX, mouseY))) {
			if (Mouse::isButtonPressed(Mouse::Left)) {
				while (Mouse::isButtonPressed(Mouse::Left)) {
				}
				// Start the game mode menu
				startGamemodeMenu(window, font, background, logo, buffer, dejavuBuffer);
			}
		}
		if (box_shop.getGlobalBounds().contains(Vector2f(mouseX, mouseY))) {
			if (Mouse::isButtonPressed(Mouse::Left)) {
				while (Mouse::isButtonPressed(Mouse::Left)) {
				}
				// Start shop menu
				startShop(window, background, font);
			}
		}
		if (box_settings.getGlobalBounds().contains(Vector2f(mouseX, mouseY))) {
			if (Mouse::isButtonPressed(Mouse::Left)) {
				// Start settings menu while mouse button is realease
				while (Mouse::isButtonPressed(Mouse::Left)) {
				}
				startSettings(window, background, font);
			}

		}
		if (box_quit.getGlobalBounds().contains(Vector2f(mouseX, mouseY))) {
			if (Mouse::isButtonPressed(Mouse::Left))
				window->close();
		}
	}
}