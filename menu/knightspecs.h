#pragma once
#include "text.h"
#include "sound.h"
#include "thread.h"
#include "sprite.h"
#include "request.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>

class Knightspecs
{
	float screen_w;
	float screen_h;

	enum FEATURES
	{
		HEART_POINTS = 0,
		ARMOUR,
		MOVEMENT_SPEED,
		DAMAGE,
		ATTACK_SPEED,
		LUCKINESS,
		EXPERIENCE,
		LEVEL,
		AMOUNT
	};

	cmm::Sprite plank;
	cmm::Sprite topgear, botgear;

	// Animation.
	float offset;
	float max_offset;
	cmm::Sprite knight;

	cmm::Sound click;
	cmm::Thread thread;

	// View, specs
	cmm::Text categories;
	std::vector <cmm::Text*> values;

public:
	Knightspecs();
	~Knightspecs();
	void free();

	void load(const float &screen_w, const float &screen_h);
	void draw(sf::RenderWindow* &window);
	void mechanics(const double &elapsedTime);
	void fadein(const float &v, const int &max);
	void fadeout(const float &v, const int &min);

	void setThread();
	void reloadThread();
	const bool& isReady() const;	// values are loaded correctly from database
	void setVolume(const float &volume);
private:
	void setValues();
	void position();
};