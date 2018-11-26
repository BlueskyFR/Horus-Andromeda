#include <SFML/Graphics.hpp>
#include "SaveFile.h"


#include "Structures.h"



using namespace sf;
void drawShop(RenderWindow *shop, RectangleShape taskbar, RectangleShape box_back_menu, Font font, Sprite piece, Sprite booster1, Sprite booster2, Sprite booster3, Sprite booster1dark, Sprite booster2dark, Sprite booster3dark, float money, bool bool_booster1, bool bool_booster2, bool bool_booster3);

void startShop(RenderWindow *shop, Sprite *background, Font *font)
{
	float mouseX, mouseY;
	bool bool_booster1 = readSaveFile("bool_boost1"), bool_booster2 = readSaveFile("bool_boost2"), bool_booster3 = readSaveFile("bool_boost3");
	float money = readSaveFile("money");

	shop->clear();
	shop->draw(*background);

	//Load sprite
	Texture booster1_texture;
	if (!booster1_texture.loadFromFile("res/booster1.png"))
		printf("Error_NO_SPRITE_booster1.png");
	Sprite booster1(booster1_texture);

	Texture booster1dark_texture;
	if (!booster1dark_texture.loadFromFile("res/booster1dark.png"))
		printf("Error_NO_SPRITE_booster1dark.png");
	Sprite booster1dark(booster1dark_texture);

	Texture booster2_texture;
	if (!booster2_texture.loadFromFile("res/booster2.png"))
		printf("Error_NO_SPRITE_booster2.png");
	Sprite booster2(booster2_texture);

	Texture booster2dark_texture;
	if (!booster2dark_texture.loadFromFile("res/booster2dark.png"))
		printf("Error_NO_SPRITE_booster2dark.png");
	Sprite booster2dark(booster2dark_texture);

	Texture booster3_texture;
	if (!booster3_texture.loadFromFile("res/booster3.png"))
		printf("Error_NO_SPRITE_booster3.png");
	Sprite booster3(booster3_texture);

	Texture booster3dark_texture;
	if (!booster3dark_texture.loadFromFile("res/booster3dark.png"))
		printf("Error_NO_SPRITE_booster3dark.png");
	Sprite booster3dark(booster3dark_texture);

	Texture piece_texture;
	if (!piece_texture.loadFromFile("res/piece.png"))
		printf("Error_NO_SPRITE_piece.png");
	Sprite piece(piece_texture);

	//Draw top bar
	RectangleShape taskbar(Vector2f(WINDOW_WIDTH, 140));
	taskbar.setFillColor(Color(190, 190, 190));
	taskbar.setOutlineThickness(TASKBAR_OUTLINE_SIZE);
	taskbar.setOutlineColor(Color::Blue);

	RectangleShape box_back_menu(Vector2f(SETTINGS_BOX_WIDTH, SETTINGS_BOX_HEIGHT));
	box_back_menu.setFillColor(Color::Blue);
	box_back_menu.setOutlineThickness(OUTLINE_SETTINGS_BOX);
	box_back_menu.setPosition(850, 650);

	booster1.setPosition(50, BOOSTER_GAP_TOP);
	booster1dark.setPosition(50, BOOSTER_GAP_TOP);
	booster2.setPosition(450, BOOSTER_GAP_TOP);
	booster2dark.setPosition(450, BOOSTER_GAP_TOP);
	booster3.setPosition(850, BOOSTER_GAP_TOP);
	booster3dark.setPosition(850, BOOSTER_GAP_TOP);
	piece.setPosition(40, 35);

	drawShop(shop, taskbar, box_back_menu, *font, piece, booster1, booster2, booster3, booster1dark, booster2dark, booster3dark, money, bool_booster1, bool_booster2, bool_booster3);

	//Detect interaction
	while (shop->isOpen())
	{
		mouseX = Mouse::getPosition(*shop).x;
		mouseY = Mouse::getPosition(*shop).y;
		Event event;
		while (shop->pollEvent(event))
		{
			if (event.type == Event::Closed)
				shop->close();
			if ((booster1.getGlobalBounds().contains(Vector2f(mouseX, mouseY))) && (money >= PRICE) && (bool_booster1 == 0)) {
				if (Mouse::isButtonPressed(Mouse::Left)) {
					//Booster missile
					bool_booster1 = 1;
					money -= PRICE;
					writeToSaveFile("money", money);
					writeToSaveFile("bool_boost1", bool_booster1);
					writeToSaveFile("missileType", 1);
					shop->draw(*background);
					drawShop(shop, taskbar, box_back_menu, *font, piece, booster1, booster2, booster3, booster1dark, booster2dark, booster3dark, money, bool_booster1, bool_booster2, bool_booster3);
				}
			}
			if (booster2.getGlobalBounds().contains(Vector2f(mouseX, mouseY)) && (money >= PRICE) && (bool_booster2 == 0)) {
				if (Mouse::isButtonPressed(Mouse::Left)) {
					//Booster shield
					bool_booster2 = 1;
					money -= PRICE;
					writeToSaveFile("money", money);
					writeToSaveFile("bool_boost2", bool_booster2);
					writeToSaveFile("max_shots_before_dead", 5);
					shop->draw(*background);
					drawShop(shop, taskbar, box_back_menu, *font, piece, booster1, booster2, booster3, booster1dark, booster2dark, booster3dark, money, bool_booster1, bool_booster2, bool_booster3);
				}
			}
			if (booster3.getGlobalBounds().contains(Vector2f(mouseX, mouseY)) && (money >= PRICE) && (bool_booster3 == 0)) {
				if (Mouse::isButtonPressed(Mouse::Left)) {
					//Booster speed rotation
					bool_booster3 = 1;
					money -= PRICE;
					writeToSaveFile("money", money);
					writeToSaveFile("bool_boost3", bool_booster3);
					writeToSaveFile("spaceship_rotation", SPACESHIP_ROTATION_STRENGTH_MAX);
					shop->draw(*background);
					drawShop(shop, taskbar, box_back_menu, *font, piece, booster1, booster2, booster3, booster1dark, booster2dark, booster3dark, money, bool_booster1, bool_booster2, bool_booster3);
				}
			}
			if (box_back_menu.getGlobalBounds().contains(Vector2f(mouseX, mouseY)))
				if (Mouse::isButtonPressed(Mouse::Left)) {
					while (Mouse::isButtonPressed(Mouse::Left)){
					}
					return;
				}
		}
		
	}

}

void drawShop(RenderWindow *shop, RectangleShape taskbar, RectangleShape box_back_menu, Font font, Sprite piece, Sprite booster1, Sprite booster2, Sprite booster3, Sprite booster1dark, Sprite booster2dark, Sprite booster3dark, float money, bool bool_booster1, bool bool_booster2, bool bool_booster3)
{
	float backWidth;
		char moneyString[10];

	//Select sprite : if an object was already bought he become grey
	if (bool_booster1 == 0)
		shop->draw(booster1);
	else
		shop->draw(booster1dark);
	if (bool_booster2 == 0)
		shop->draw(booster2);
	else
		shop->draw(booster2dark);
	if (bool_booster3 == 0)
		shop->draw(booster3);
	else
		shop->draw(booster3dark);
	//Add title on the top right corner
	Text title;
	title.setFont(font);
	title.setString("Shop");
	title.setCharacterSize(100);
	title.setOutlineThickness(3);
	title.setOutlineColor(Color::Blue);
	title.setPosition(900, 0);

	Text back;
	back.setFont(font);
	back.setString("Retour");
	back.setCharacterSize(70);
	backWidth = back.getLocalBounds().width;
	back.setPosition(850 + (SETTINGS_BOX_WIDTH - backWidth) / 2, 650);

	Text text_money;
	text_money.setFont(font);
	sprintf_s(moneyString, "%.0f", money);
	text_money.setString(moneyString);
	text_money.setCharacterSize(50);
	text_money.setFillColor(Color::Yellow);
	text_money.setPosition(130, 35);

	shop->draw(taskbar);
	shop->draw(box_back_menu);
	shop->draw(back);
	shop->draw(piece);
	shop->draw(title);
	shop->draw(text_money);
	shop->display();
}