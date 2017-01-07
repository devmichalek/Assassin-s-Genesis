#include "wood/play_wood.h"

Play_wood::Play_wood()
{
	state = new State;
	hero = new Hero;
	bg = new Moving_bg;
	brick = new Brick;
	kunai = new Kunai;
	heart = new Heart;
	scope = new Scope;
}

Play_wood::~Play_wood()
{
	free();
}

void Play_wood::free()
{
	delete state;
	delete hero;
	delete bg;
	delete brick;
	delete kunai;
	delete heart;
	delete scope;
}

	
void Play_wood::load( int screen_w, int screen_h )
{
	bg->load( "data/sprites/play/1.png", screen_w, screen_h );
	brick->load( screen_w, screen_h, 18, 1 );
	kunai->load();
	heart->load();
}

void Play_wood::setHero( int screen_w, int screen_h, int type )
{
	if( type == 0 )
	{
		hero->load( screen_w, screen_h, "data/sprites/hero/0/" );
	}
	else
	{
		hero->load( screen_w, screen_h, "data/sprites/hero/1/" );
	}
	
	scope->set( hero->getX(), brick->getWidth(), screen_w );
	
	bg->setXY( hero->getX(), hero->getY() );
}

void Play_wood::setWorldsize( int size )
{
	brick->positioning( size );
}

void Play_wood::handle( sf::Event &event )
{
	//...
}


void Play_wood::draw( sf::RenderWindow* &window )
{
	mechanics();
	
	bg->fadein( 2 );
	brick->fadein( 2 );
	hero->fadein( 2 );
	kunai->fadein( 2 );
	heart->fadein( 2 );

	
	bg->draw( window );
	brick->drawLadders( window );
	hero->draw( window );
	kunai->draw( window );
	brick->draw( window );
	heart->draw( window );
}

	
State* Play_wood::getState()
{
	return state;
}

void Play_wood::set( State* state )
{
	this->state = state;
	state->state = 0;
	
	/*
	// Set chunks
	if( !state->cSwitch )
	{
		backtomenu->turn();
		choice->turn();
	}
	
	// Set music volume
	music->setVolume( state->mVolume );
	
	// Set chunk volume
	backtomenu->setVolume( state->cVolume );
	choice->setVolume( state->cVolume );
	*/
}

	
bool Play_wood::isQuit()
{
	if( state->state == 3 )
	{
		return true;
	}
	
	return false;
}

bool Play_wood::nextState()
{
	if( state->state == 1 )
	{
		return true;
	}
	
	return false;
}

bool Play_wood::backToLevel()
{
	if( state->state == 2 )
	{
		state->state = 0;
		// backtomenu->setState( 0 );
		return true;
	}
		
	return false;
}

	
void Play_wood::reloadMusic()
{
	// music->reload();
}

