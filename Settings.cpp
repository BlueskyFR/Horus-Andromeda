#include <SFML/Graphics.hpp>



#include "Structures.h";

using namespace sf;

Keyboard::Key changeKey(RenderWindow *settings, Sprite *background, Font *font);
void drawSettings(RenderWindow *settings, Sprite *background, Font *font, bool aKeyHasBeenChanged);

Keyboard::Key handleKeyBoard(Keyboard::Key keyInput, short keyNumber, char whatToDo)//whatToDo, s for set, r to return value
{
	static Keyboard::Key keyMoveUp = Keyboard::Up;//keyNumber 0
	static Keyboard::Key keyMoveDown = Keyboard::Down;//keyNumber 1
	static Keyboard::Key keyMoveLeft = Keyboard::Left;//keyNumber 2
	static Keyboard::Key keyMoveRight = Keyboard::Right;//keyNumber 3
	static Keyboard::Key keyRotationLeft = Keyboard::Q;//keyNumber 4
	static Keyboard::Key keyRotationRight = Keyboard::D;//keyNumber 5
	static Keyboard::Key keyShoot = Keyboard::Space;//keyNumber 6

	if (whatToDo == 'r')//return the value matching the right key
	{

		if (keyNumber == 0)
			return keyMoveUp;
		else if (keyNumber == 1)
			return keyMoveDown;
		else if (keyNumber == 2)
			return keyMoveLeft;
		else if (keyNumber == 3)
			return keyMoveRight;
		else if (keyNumber == 4)
			return keyRotationLeft;
		else if (keyNumber == 5)
			return keyRotationRight;
		else if (keyNumber == 6)
			return keyShoot;//if the input key doesn't match any key
		else//7
			return Keyboard::Unknown;
	}
	else if (whatToDo == 's')//set the key matching the keyNumber
	{
		if (keyNumber == 0)
			keyMoveUp = keyInput;
		else if (keyNumber == 1)
			keyMoveDown = keyInput;
		else if (keyNumber == 2)
			keyMoveLeft = keyInput;
		else if (keyNumber == 3)
			keyMoveRight = keyInput;
		else if (keyNumber == 4)
			keyRotationLeft = keyInput;
		else if (keyNumber == 5)
			keyRotationRight = keyInput;
		else//6
			keyShoot = keyInput;
		return Keyboard::Unknown;
	}
	return Keyboard::Unknown;

}


void startSettings(RenderWindow *settings, Sprite *background, Font *font)
{
	drawSettings(settings, background, font, 0);
}

void drawSettings(RenderWindow *settings, Sprite *background, Font *font, bool aKeyHasBeenChanged)
{
	float text_forwardWidth, text_backwardWidth, text_leftWidth, text_rightWidth, text_keyRotationLeftWidth, text_keyRotationRightWidth, text_shootWidth, text_backWidth;
	float mouseX, mouseY;
	settings->clear();
	settings->draw(*background);

	//Creation of all the choice box
	RectangleShape box_forward(Vector2f(SETTINGS_BOX_WIDTH, SETTINGS_BOX_HEIGHT));
	RectangleShape box_backward(Vector2f(SETTINGS_BOX_WIDTH, SETTINGS_BOX_HEIGHT));
	RectangleShape box_left(Vector2f(SETTINGS_BOX_WIDTH, SETTINGS_BOX_HEIGHT));
	RectangleShape box_right(Vector2f(SETTINGS_BOX_WIDTH, SETTINGS_BOX_HEIGHT));
	RectangleShape box_keyRotationLeft(Vector2f(SETTINGS_BOX_WIDTH, SETTINGS_BOX_HEIGHT));
	RectangleShape box_keyRotationRight(Vector2f(SETTINGS_BOX_WIDTH, SETTINGS_BOX_HEIGHT));
	RectangleShape box_shoot(Vector2f(SETTINGS_BOX_WIDTH, SETTINGS_BOX_HEIGHT));
	RectangleShape box_back_menu(Vector2f(SETTINGS_BOX_WIDTH, SETTINGS_BOX_HEIGHT));

	//Set color choice box + outline
	box_forward.setFillColor(Color::Blue);
	box_forward.setOutlineThickness(2);
	box_backward.setFillColor(Color::Blue);
	box_backward.setOutlineThickness(2);
	box_left.setFillColor(Color::Blue);
	box_left.setOutlineThickness(2);
	box_right.setFillColor(Color::Blue);
	box_right.setOutlineThickness(2);
	box_keyRotationLeft.setFillColor(Color::Blue);
	box_keyRotationLeft.setOutlineThickness(2);
	box_keyRotationRight.setFillColor(Color::Blue);
	box_keyRotationRight.setOutlineThickness(2);
	box_shoot.setFillColor(Color::Blue);
	box_shoot.setOutlineThickness(2);
	box_back_menu.setFillColor(Color::Blue);
	box_back_menu.setOutlineThickness(2);

	//Set position of choice box
	box_forward.setPosition(SETTINGS_BOX_GAP_WIDTH, SETTINGS_BOX_GAP_HEIGHT);
	box_backward.setPosition(SETTINGS_BOX_GAP_WIDTH * 2 + SETTINGS_BOX_WIDTH, SETTINGS_BOX_GAP_HEIGHT);
	box_left.setPosition(SETTINGS_BOX_GAP_WIDTH, SETTINGS_BOX_GAP_HEIGHT * 2 + SETTINGS_BOX_HEIGHT);
	box_right.setPosition(SETTINGS_BOX_GAP_WIDTH * 2 + SETTINGS_BOX_WIDTH, SETTINGS_BOX_GAP_HEIGHT * 2 + SETTINGS_BOX_HEIGHT);
	box_keyRotationLeft.setPosition(SETTINGS_BOX_GAP_WIDTH, SETTINGS_BOX_GAP_HEIGHT * 4 + SETTINGS_BOX_HEIGHT);
	box_keyRotationRight.setPosition(SETTINGS_BOX_GAP_WIDTH * 2 + SETTINGS_BOX_WIDTH, SETTINGS_BOX_GAP_HEIGHT * 4 + SETTINGS_BOX_HEIGHT);
	box_shoot.setPosition(SETTINGS_BOX_GAP_WIDTH, SETTINGS_BOX_GAP_HEIGHT * 6 + SETTINGS_BOX_HEIGHT);
	box_back_menu.setPosition(SETTINGS_BOX_GAP_WIDTH * 2 + SETTINGS_BOX_WIDTH, SETTINGS_BOX_GAP_HEIGHT * 6 + SETTINGS_BOX_HEIGHT);

	//Draw all the boxes
	settings->draw(box_forward);
	settings->draw(box_backward);
	settings->draw(box_left);
	settings->draw(box_right);
	settings->draw(box_keyRotationLeft);
	settings->draw(box_keyRotationRight);
	settings->draw(box_shoot);
	settings->draw(box_back_menu);

	//Creation of text + align in the box
	Text text_forward;
	text_forward.setFont(*font);
	text_forward.setString("Avancer");
	text_forward.setCharacterSize(SETTINGS_FONT_SIZE);
	text_forwardWidth = text_forward.getLocalBounds().width;
	text_forward.setPosition(SETTINGS_BOX_GAP_WIDTH + (SETTINGS_BOX_WIDTH - text_forwardWidth) / 2, SETTINGS_BOX_GAP_HEIGHT + 15);

	Text text_backward;
	text_backward.setFont(*font);
	text_backward.setString("Reculer");
	text_backward.setCharacterSize(SETTINGS_FONT_SIZE);
	text_backwardWidth = text_backward.getLocalBounds().width;
	text_backward.setPosition(SETTINGS_BOX_GAP_WIDTH * 2 + SETTINGS_BOX_WIDTH + (SETTINGS_BOX_WIDTH - text_backwardWidth) / 2, SETTINGS_BOX_GAP_HEIGHT + 15);

	Text text_left;
	text_left.setFont(*font);
	text_left.setString("Gauche");
	text_left.setCharacterSize(SETTINGS_FONT_SIZE);
	text_leftWidth = text_left.getLocalBounds().width;
	text_left.setPosition(SETTINGS_BOX_GAP_WIDTH + (SETTINGS_BOX_WIDTH - text_leftWidth) / 2, SETTINGS_BOX_GAP_HEIGHT * 2 + SETTINGS_BOX_HEIGHT + 15);

	Text text_right;
	text_right.setFont(*font);
	text_right.setString("Droite");
	text_right.setCharacterSize(SETTINGS_FONT_SIZE);
	text_rightWidth = text_right.getLocalBounds().width;
	text_right.setPosition(SETTINGS_BOX_GAP_WIDTH * 2 + SETTINGS_BOX_WIDTH + (SETTINGS_BOX_WIDTH - text_rightWidth) / 2, SETTINGS_BOX_GAP_HEIGHT * 2 + SETTINGS_BOX_HEIGHT + 15);

	Text text_keyRotationLeft;
	text_keyRotationLeft.setFont(*font);
	text_keyRotationLeft.setString("Rotation G");
	text_keyRotationLeft.setCharacterSize(SETTINGS_FONT_SIZE);
	text_keyRotationLeftWidth = text_keyRotationLeft.getLocalBounds().width;
	text_keyRotationLeft.setPosition(SETTINGS_BOX_GAP_WIDTH + (SETTINGS_BOX_WIDTH - text_keyRotationLeftWidth) / 2, SETTINGS_BOX_GAP_HEIGHT * 4 + SETTINGS_BOX_HEIGHT + 15);

	Text text_keyRotationRight;
	text_keyRotationRight.setFont(*font);
	text_keyRotationRight.setString("Rotation D");
	text_keyRotationRight.setCharacterSize(SETTINGS_FONT_SIZE);
	text_keyRotationRightWidth = text_keyRotationRight.getLocalBounds().width;
	text_keyRotationRight.setPosition(SETTINGS_BOX_GAP_WIDTH * 2 + SETTINGS_BOX_WIDTH + (SETTINGS_BOX_WIDTH - text_keyRotationRightWidth) / 2, SETTINGS_BOX_GAP_HEIGHT * 4 + SETTINGS_BOX_HEIGHT + 15);

	Text text_shoot;
	text_shoot.setFont(*font);
	text_shoot.setString("Tirer");
	text_shoot.setCharacterSize(SETTINGS_FONT_SIZE);
	text_shootWidth = text_shoot.getLocalBounds().width;
	text_shoot.setPosition(SETTINGS_BOX_GAP_WIDTH + (SETTINGS_BOX_WIDTH - text_shootWidth) / 2, SETTINGS_BOX_GAP_HEIGHT * 6 + SETTINGS_BOX_HEIGHT + 15);

	Text text_back;
	text_back.setFont(*font);
	text_back.setString("Retour");
	text_back.setCharacterSize(SETTINGS_FONT_SIZE);
	text_backWidth = text_back.getLocalBounds().width;
	text_back.setPosition(SETTINGS_BOX_GAP_WIDTH * 2 + SETTINGS_BOX_WIDTH + (SETTINGS_BOX_WIDTH - text_backWidth) / 2, SETTINGS_BOX_GAP_HEIGHT * 6 + SETTINGS_BOX_HEIGHT + 15);

	//Draw all the texts
	settings->draw(text_forward);
	settings->draw(text_backward);
	settings->draw(text_left);
	settings->draw(text_right);
	settings->draw(text_keyRotationLeft);
	settings->draw(text_keyRotationRight);
	settings->draw(text_shoot);
	settings->draw(text_back);

	settings->display();

	//Detection of button press
	if (aKeyHasBeenChanged == 1)
		return;
	while (settings->isOpen())
	{
		mouseX = Mouse::getPosition(*settings).x;
		mouseY = Mouse::getPosition(*settings).y;
		Event event;
		while (settings->pollEvent(event))
		{
			if (event.type == Event::Closed)//SETTING DE KEYS ICI
				settings->close();

			if (box_forward.getGlobalBounds().contains(Vector2f(mouseX, mouseY)))
			{
				if (Mouse::isButtonPressed(Mouse::Left))
					handleKeyBoard(changeKey(settings, background, font), 0, 's');//set keyMouseUp
			}
			if (box_backward.getGlobalBounds().contains(Vector2f(mouseX, mouseY)))
			{
				if (Mouse::isButtonPressed(Mouse::Left))
					handleKeyBoard(changeKey(settings, background, font), 1, 's');//set keyMouseDown
			}
			if (box_left.getGlobalBounds().contains(Vector2f(mouseX, mouseY)))
			{
				if (Mouse::isButtonPressed(Mouse::Left))
					handleKeyBoard(changeKey(settings, background, font), 2, 's');//set keyMouseLeft
			}
			if (box_right.getGlobalBounds().contains(Vector2f(mouseX, mouseY)))
			{
				if (Mouse::isButtonPressed(Mouse::Left))
					handleKeyBoard(changeKey(settings, background, font), 3, 's');//set keyMouseRight
			}
			if (box_keyRotationLeft.getGlobalBounds().contains(Vector2f(mouseX, mouseY)))
			{
				if (Mouse::isButtonPressed(Mouse::Left))
					handleKeyBoard(changeKey(settings, background, font), 4, 's');//set keyRotationLeft
			}
			if (box_keyRotationRight.getGlobalBounds().contains(Vector2f(mouseX, mouseY)))
			{
				if (Mouse::isButtonPressed(Mouse::Left))
					handleKeyBoard(changeKey(settings, background, font), 5, 's');//set keyRotationRight JENETELA
			}
			if (box_shoot.getGlobalBounds().contains(Vector2f(mouseX, mouseY)))
			{
				if (Mouse::isButtonPressed(Mouse::Left))
					handleKeyBoard(changeKey(settings, background, font), 6, 's');//set keyShoot
			}

			if ((Keyboard::isKeyPressed(Keyboard::Escape)) || ((box_back_menu.getGlobalBounds().contains(Vector2f(mouseX, mouseY))) && (Mouse::isButtonPressed(Mouse::Left)))) {
				// Return to menu while mouse button is realease
				while (Mouse::isButtonPressed(Mouse::Left)) {
				}
				return;
			}
				
		}
	}

}
Keyboard::Key changeKey(RenderWindow *settings, Sprite *background, Font *font)
{
	//Change associate key

	Keyboard::Key newKey;
	float askKeyWidth;

	settings->clear();
	settings->draw(*background);

	Text askKey;
	askKey.setFont(*font);
	askKey.setString("Appuie sur une touche !");
	askKey.setCharacterSize(ASK_KEY);
	askKeyWidth = askKey.getLocalBounds().width;
	askKey.setPosition((1200 - askKeyWidth) / 2, 350);
	settings->draw(askKey);
	settings->display();


	while (settings->isOpen())
	{
		Event event;
		while (settings->pollEvent(event))
		{
			if (event.type == event.KeyPressed)
			{
				newKey = event.key.code;
				drawSettings(settings, background, font, 1);
				return newKey;
			}
		}

	}
}
