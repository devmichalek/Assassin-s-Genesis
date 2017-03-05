#pragma once

#include "04_platform/enemy/coins/coin.h"
#include "04_platform/enemy/expletive/slab.h"
#include "drawable/sprite.h"
#include <vector>

class Coins
{
	int width;
	int screen_w;
	int money;
	
	MySprite coin;
	vector <Coin*> coins;
	vector <Slab*> dropped_coins;
	vector <Slab*> jumped_coins;
	
public:
	
	Coins();
	~Coins();
	void free();
	void reset();
	
	void load( int width, int screen_w, int type );
	void setChance( int chance );
	void draw( sf::RenderWindow* &window );
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	void setCoin( Rect* rect );
	void playDropped_coin();
	void playJumped_coin();
	
	// In action.
	void moveX( sf::Uint8 direction, float vel );
	void undoFall( sf::Uint8 add );
	void mechanics();
	void setColor( sf::Color color );
	
	int strToInt( string s );
	int getMoney();
	bool upliftMoney( Rect* rect );
};