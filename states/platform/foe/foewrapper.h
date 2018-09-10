#define _SCL_SECURE_NO_WARNINGS
#pragma once
#include "treedefinitions.h"
#include "foe.h"
#include "sprite.h"
#include <SFML/Graphics/RenderWindow.hpp>

class FoeWrapper
{
	RTree* tree;
	std::vector<Foe*> foes;

	std::vector<std::vector<cmm::Sprite*>> sprites;

	// Process ------------------------
	sf::RenderWindow* window;
	double elapsedTime;
	Rect* screen;
	Rect* character;
	Rect* characterAttack;	// attack box
	bool characterHasAttacked;
	float characterDamage;
	float characterHP;
	float characterArmour;
	// --------------------------------

public:
	FoeWrapper();
	~FoeWrapper();
	void free();
	void clean();
	void incinerate();

	void insert(Foe* foe);
	void load(std::vector<std::string>&, std::vector<int>&, std::vector<int>&);

	void update(sf::RenderWindow* &,
				double &,
				Rect* &,
				Rect* &,
				Rect* &,
				bool &,
				float &,
				float &,
				float &);

	void process();
};