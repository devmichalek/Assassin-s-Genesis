#pragma once
#include "eafactory.h"
#include "eagrid.h"

class EditorAction
{
	EAFactory factory;
	EAGrid grid;

public:
	EditorAction();
	~EditorAction();
private:
	void free();
public:
	void reset();

	void load(const float &screen_w, const float &screen_h);
	void handle(const sf::Event &event);
	void draw(sf::RenderWindow* &window);
	void mechanics(const double &elapsedTime);
};