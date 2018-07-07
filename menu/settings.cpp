#include "settings.h"
#include <boost/lexical_cast.hpp>
#include <fstream>

Settings::Settings()
{
	free();
}

Settings::~Settings()
{
	free();
}

void Settings::free()
{
	screen_w = 0;
	screen_h = 0;

	if (!keys.empty())
	{
		keys.clear();
	}

	if (!text_collisions.empty())
	{
		text_collisions.clear();
	}

	if (!state_texts.empty())
	{
		for (auto &it : state_texts)
		{
			delete it;
			it = nullptr;
		}

		state_texts.clear();
	}
	
	if (!active_texts.empty())
	{
		for (auto &it : active_texts)
		{
			delete it;
			it = nullptr;
		}

		active_texts.clear();
	}

	if (!gears.empty())
	{
		for (auto &it : gears)
		{
			delete it;
			it = nullptr;
		}

		gears.clear();
	}

	tableMoves = 0;
	x1 = x2 = 0;

	chartMoves = 0;
	y1 = y2 = 0;

	target = -1;
}



void Settings::load(float screen_w, float screen_h)
{
	free();

	this->screen_w = screen_w;
	this->screen_h = screen_h;

	// Set font for state texts and active texts.
	const char* text_path = "fonts/jcandlestickextracond.ttf";
	for (unsigned i = 0; i < AMOUNT; i++)
	{
		state_texts.push_back(new cmm::Text);
		state_texts[i]->setFont(text_path);
		active_texts.push_back(new cmm::Text);
		active_texts[i]->setFont(text_path);
	}

	// Set text for state texts.
	state_texts[MOVE_LEFT]->setText("move left");
	state_texts[MOVE_RIGHT]->setText("move right");
	state_texts[JUMP]->setText("jump");
	state_texts[CHOP]->setText("chop");
	state_texts[SHOOT]->setText("shoot");
	state_texts[SLIDE]->setText("slide");
	state_texts[JUMP_CHOP]->setText("jump chop");
	state_texts[JUMP_SHOOT]->setText("jump shoot");
	state_texts[PAUSE]->setText("pause");
	state_texts[CHAT]->setText("chat");

	// Set active_texts text.
	std::ifstream file("txt/keys.txt");
	if (file.good())
	{
		for (unsigned i = 0; i < JUMP_CHOP; i++)
		{
			text_collisions.push_back(sf::Rect<float>());
			std::string line = "";
			file >> line;
			keys.push_back(boost::lexical_cast<int>(line));
			active_texts[i]->setText(getName(keys[i]));
		}
	}
	active_texts[JUMP_CHOP]->setText(getName(keys[JUMP]) + " + " + getName(keys[CHOP]));
	active_texts[JUMP_SHOOT]->setText(getName(keys[JUMP]) + " + " + getName(keys[SHOOT]));
	active_texts[PAUSE]->setText("p");
	active_texts[CHAT]->setText("o");

	// Set size of state texts and active texts.
	int size = screen_h / 28;
	for (unsigned i = 0; i < AMOUNT; i++)
	{
		state_texts[i]->setSize(size);
		active_texts[i]->setSize(size);
		state_texts[i]->setFillColor(sf::Color(0xDD, 0xDD, 0xDD));
		i < JUMP_CHOP ? active_texts[i]->setFillColor(sf::Color(0xFF, 0xFF, 0xFF)) : active_texts[i]->setFillColor(sf::Color(0xDD, 0xDD, 0xDD));
	}

	// Set contact me information.
	contactme.setFont(text_path);
	contactme.setText("Contact me: devmichalek@gmail.com");
	contactme.setSize(size - 4);
	contactme.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

	// Set table.
	table.load("images/other/plank.png");
	table.setScale(screen_w / 2560, screen_h / 1440);
	x1 = screen_w - screen_w / 128;
	x2 = screen_w + screen_w / 128 - table.getWidth();
	table.setPosition(x1, screen_h / 2.6);

	// Set second table.
	chart.load("images/old/menu/table_second.png");
	chart.setScale(screen_w / 2560, screen_h / 1440);
	y1 = screen_h - screen_h / 72;
	y2 = screen_h + screen_h / 72 - chart.getHeight();
	chart.setPosition(screen_w / 2.13, y1);

	// Set gears.
	for (unsigned i = 0; i < RIGHT + 1; ++i)
	{
		gears.push_back(new cmm::Sprite);
		gears[i]->load("images/other/gear.png");
		gears[i]->setOrigin(gears[i]->getWidth() * 0.5, gears[i]->getHeight() * 0.5);
		gears[i]->setScale(screen_w / 2560, screen_h / 1440);
	}
	gears[TOP]->setPosition(screen_w, table.getTop());
	gears[BOT]->setPosition(screen_w, table.getBot());
	gears[LEFT]->setPosition(chart.getLeft(), screen_h);
	gears[RIGHT]->setPosition(chart.getRight(), screen_h);

	// Set reset button.
	resetbutton.load("images/old/menu/resetbutton.png", 3);
	resetbutton.setScale(screen_w / 2560, screen_h / 1440);

	// Set info.
	info.setFont("fonts/jcandlestickextracond.ttf");
	info.setText("Press button to change\nClick anywhere to save");
	info.setSize(size);
	info.setFillColor(sf::Color(0xDD, 0xDD, 0xDD));

	// Position.
	positionTable();
	positionChart();

	// Load sounds.
	click.load("sounds/click.wav");
}

bool Settings::handle(sf::Event& event)
{
	if (chartMoves == 0 && target != -1)
	{
		// Reset.
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (resetbutton.checkCollision(event.mouseButton.x, event.mouseButton.y))
				{
					resetbutton.setOffset(1);
					reset();
					return true;
				}
			}
		}

		if (event.type == sf::Event::MouseButtonReleased)
		{
			resetbutton.setOffset(0);
		}

		// Keyboard stuff.
		if (event.type == sf::Event::KeyPressed)
		{
			bool success = true;
			for (auto &it : keys)
			{
				if (it == event.key.code)
				{
					success = false;
					break;
				}
			}

			// Set key.
			if (success)
			{
				if (isPossibleKey(event))
				{
					click.play();

					keys[target] = event.key.code;

					active_texts[target]->setText(getName(event.key.code));
					active_texts[target]->setFillColor(sf::Color(0xF2, 0x58, 0x3E));

					if (target == CHOP || target == JUMP)
					{
						active_texts[JUMP_CHOP]->setText(getName(keys[JUMP]) + " + " + getName(keys[CHOP]));
					}
					else if (target == SHOOT || target == JUMP)
					{
						active_texts[JUMP_SHOOT]->setText(getName(keys[JUMP]) + " + " + getName(keys[SHOOT]));
					}

					positionTable();
					save();
				}
			}
		}
	}

	if (tableMoves == 0 && table.getX() == x2)	// Table is fully visible.
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				// Set default color if target is set.
				if (target != -1)
				{
					active_texts[target]->setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
				}

				// Check if it is collide.
				target = -1;
				for (unsigned i = 0; i < JUMP_CHOP; i++)
				{
					if (text_collisions[i].contains(event.mouseButton.x, event.mouseButton.y))
					{
						target = i;
						click.play();
						active_texts[i]->setFillColor(sf::Color(0xF2, 0x58, 0x3E));
						break;
					}
				}

				if (target != -1)
				{
					return true;
				}
			}
		}
	}

	return false;
}

void Settings::draw(sf::RenderWindow* &window)
{
	window->draw(table.get());
	window->draw(chart.get());

	for (auto &it : state_texts)
	{
		window->draw(it->get());
	}

	for (auto &it : active_texts)
	{
		window->draw(it->get());
	}

	window->draw(contactme.get());
	window->draw(info.get());
	window->draw(resetbutton.get());

	for (auto &it : gears)
	{
		window->draw(it->get());
	}
}

void Settings::mechanics(double elapsedTime)
{
	if (tableMoves != 0)	// is moving
	{
		table.move(tableMoves, 0);

		positionTable();

		float rotation = static_cast<float>(elapsedTime) * 0xFF;

		if (tableMoves < 0)
		{
			gears[TOP]->setRotation(gears[TOP]->getRotation() + rotation);
			gears[BOT]->setRotation(gears[BOT]->getRotation() - rotation);
		}
		else
		{
			gears[TOP]->setRotation(gears[TOP]->getRotation() - rotation);
			gears[BOT]->setRotation(gears[BOT]->getRotation() + rotation);
		}
	}

	if (target != -1)
	{
		chart.getY() > y2 ? chartMoves = -elapsedTime * 0xFF : chartMoves = 0;

		if (chart.getY() < y2)
		{
			chart.setPosition(chart.getX(), y2);
		}
	}
	else
	{
		chart.getY() < y1 ? chartMoves = elapsedTime * 0xFF : chartMoves = 0;

		if (chart.getY() > y1)
		{
			chart.setPosition(chart.getX(), y1);
		}
	}

	if (chartMoves != 0) // is moving
	{
		positionChart();
		chart.move(0, chartMoves);

		float rotation = static_cast<float>(elapsedTime) * 0xFF;

		if (chartMoves < 0)
		{
			gears[LEFT]->setRotation(gears[LEFT]->getRotation() - rotation);
			gears[RIGHT]->setRotation(gears[RIGHT]->getRotation() + rotation);
		}
		else
		{
			gears[LEFT]->setRotation(gears[LEFT]->getRotation() + rotation);
			gears[RIGHT]->setRotation(gears[RIGHT]->getRotation() - rotation);
		}
	}
}



void Settings::fadein(float v, int max)
{
	for (auto &it : state_texts)
	{
		it->fadein(v, max);
	}

	for (auto &it : active_texts)
	{
		it->fadein(v, max);
	}

	for (auto &it : gears)
	{
		it->fadein(v, max);
	}

	contactme.fadein(v, max);
	table.fadein(v, max);
	chart.fadein(v, max);
	info.fadein(v, max);
	resetbutton.fadein(v, max);
}

void Settings::fadeout(float v, int min)
{
	for (auto &it : state_texts)
	{
		it->fadeout(v, min);
	}

	for (auto &it : active_texts)
	{
		it->fadeout(v, min);
	}

	for (auto &it : gears)
	{
		it->fadeout(v, min);
	}

	contactme.fadeout(v, min);
	table.fadeout(v, min);
	chart.fadeout(v, min);
	info.fadeout(v, min);
	resetbutton.fadeout(v, min);
}



void Settings::exsertTable(double elapsedTime)
{
	table.getX() > x2 ? tableMoves = -elapsedTime * 0xFF : tableMoves = 0;

	if (table.getX() < x2)
	{
		table.setPosition(x2, table.getY());
		positionTable();
	}
}

void Settings::shovelTable(double elapsedTime)
{
	table.getX() < x1 ? tableMoves = elapsedTime * 0xFF : tableMoves = 0;
	
	if (table.getX() > x1)
	{
		table.setPosition(x1, table.getY());
		positionTable();
	}
}

void Settings::reset()
{
	// Reset values.
	keys[MOVE_LEFT] = 71;
	keys[MOVE_RIGHT] = 72;
	keys[JUMP] = 73;
	keys[CHOP] = 25;
	keys[SHOOT] = 23;
	keys[SLIDE] = 74;
	for (unsigned i = 0; i < JUMP_CHOP; i++)
	{
		active_texts[i]->setText(getName(keys[i]));
		active_texts[i]->setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
	}

	// Overwrite.
	save();

	positionTable();
}

void Settings::save()
{
	std::ofstream file("txt/keys.txt");
	if (file.good())
	{
		for (unsigned i = 0; i < JUMP_CHOP; i++)
		{
			file << keys[i] << std::endl;
		}
	}
}

void Settings::positionTable()
{
	// Position state texts.
	for (unsigned i = 0; i < state_texts.size(); i++)
	{
		state_texts[i]->setPosition(table.getX() + screen_w / 80, table.getY() + (screen_h / 28 * i) + screen_h / 256);
	}

	// Position active texts.
	for (unsigned i = 0; i < active_texts.size(); i++)
	{
		active_texts[i]->setPosition(table.getX() + table.getWidth() / 2, state_texts[i]->getY());
		if (i < JUMP_CHOP)
		{
			text_collisions[i].width = table.getWidth();
			text_collisions[i].height = active_texts[i]->getHeight();
			text_collisions[i].left = table.getX();
			text_collisions[i].top = active_texts[i]->getY();
		}
	}

	// Contactme.
	contactme.setPosition(table.getX() + screen_w / 80, table.getBot() - contactme.getHeight() - screen_h / 108);
}

void Settings::positionChart()
{
	info.setPosition(chart.getX() + screen_w / 80, chart.getY() + screen_h / 54);
	resetbutton.setPosition(chart.getRight() - resetbutton.getWidth(), chart.getBot() - resetbutton.getHeight());
}

bool Settings::isPossibleKey(sf::Event &event)
{
	sf::Uint8 code = event.key.code;

	if (code == 14 || code == 15)	// pause key or chat key
	{
		return false;
	}
	if (code > -1 && code <= 35)	// a .. z and numbers
	{
		return true;
	}
	if (code >= 75 && code <= 84)	// numbers
	{
		return true;
	}
	if (code >= 71 && code <= 74)	// arrows
	{
		return true;
	}
	if (code == 57)					// space
	{
		return true;
	}

	return false;
}

std::string Settings::getName(int n)
{
	std::string name = "";

	if (n > -1 && n <= 25)			// from a to z
	{
		// in ASCII 97 is letter 'a'
		name = static_cast <char> (n + 97);
	}
	else if (n >= 26 && n <= 35)	// numbers
	{
		// 26 + 22 = 48
		// in ASCII 48 is character 0
		name = static_cast <char> (n + 22);
	}
	else if (n >= 75 && n <= 84)	// numbers cd.
	{
		// 75 - 27 = 48
		// in ASCII 48 is character 0
		name = static_cast <char> (n - 27);
	}
	else
	{
		switch (n)
		{
		case 71: name = "Left";		break;
		case 72: name = "Right";	break;
		case 73: name = "Up";		break;
		case 74: name = "Down";		break;
		case 57: name = "Space";	break;
		}
	}

	return name;
}

void Settings::reload()
{
	tableMoves = chartMoves = 0;
	table.setPosition(x1, table.getY());
	chart.setPosition(chart.getX(), y1);
	positionTable();
	positionChart();
}




void Settings::setVolume(float volume)
{
	click.setVolume(volume);
}