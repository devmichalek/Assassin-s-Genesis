#include "platform.h"
#include "boost/lexical_cast.hpp"
#include <fstream>

Platform::Platform()
{
	free();
}

Platform::~Platform()
{
	free();
}

void Platform::free()
{
	prev = false;
	next = false;
	exit = false;
	loaded = false;

	homebutton.free();
	levelbutton.free();
	soundbutton.free();
	musicbutton.free();
	sound_volumebutton.free();
	music_volumebutton.free();
	// chat.free();
	pausesystem.free();
}

void Platform::set()
{
	if (!loaded)
	{
		loaded = true;

		// Set threads.
		// ...

		// Sound.
		float soundVolume = 50;
		homebutton.setVolume(soundVolume);
		levelbutton.setVolume(soundVolume);
		soundbutton.setVolume(soundVolume);
		musicbutton.setVolume(soundVolume);
		sound_volumebutton.setVolume(soundVolume);
		sound_volumebutton.setGlobalVolume(soundVolume);
		music_volumebutton.setVolume(soundVolume);
		pausesystem.setVolume(soundVolume);
		cmm::Sound::setPlayable(true);
		soundbutton.setActive(true);

		// Music.
		float musicVolume = 60;
		music.setVolume(musicVolume);
		music_volumebutton.setGlobalVolume(musicVolume);
		cmm::Music::setPlayable(true);
		musicbutton.setActive(true);
		music.play();
	}
}

bool Platform::isReady() const
{
	// return information.getBackgroundAlpha() == 0;
	return 0;
}

void Platform::reset()
{
	prev = false;
	next = false;
	exit = false;
	loaded = false;
	
	homebutton.setActive(false);
	levelbutton.setActive(false);
	// chat.reset();
	music.stop();
}



void Platform::load(float screen_w, float screen_h)
{
	free();

	float scale_x = screen_w / 2560;
	float scale_y = screen_h / 1440;

	// Circle buttons.
	homebutton.load("images/buttons/home.png");
	levelbutton.load("images/buttons/levelmenu.png");
	soundbutton.load("images/buttons/sound.png");
	musicbutton.load("images/buttons/music.png");
	soundbutton.setScale(scale_x, scale_y);
	musicbutton.setScale(scale_x, scale_y);
	soundbutton.setPosition(screen_w - screen_w / 256 - soundbutton.getWidth(), screen_h - screen_h / 144 - soundbutton.getHeight());
	musicbutton.setPosition(soundbutton.getLeft() - screen_w / 256 - musicbutton.getWidth(), soundbutton.getTop());

	// Set volume buttons.
	sound_volumebutton.load(screen_w, screen_h);
	music_volumebutton.load(screen_w, screen_h);
	sound_volumebutton.setPosition(soundbutton.getLeft(), soundbutton.getRight(), soundbutton.getBot());
	music_volumebutton.setPosition(musicbutton.getLeft(), musicbutton.getRight(), musicbutton.getBot());

	// Set chat.
	/*chat.load(screen_w, screen_h);
	chat.setCommandColor(sf::Color(0, 0, 0));
	chat.setTypicalColor(sf::Color(0x68, 0x68, 0x68));*/

	pausesystem.load(screen_w, screen_h);
	music.load("music/platform.ogg");
}

void Platform::handle(sf::Event& event)
{
	if (!isState())
	{
		if (!pausesystem.isActive() && pausesystem.getAlpha() == 0)
		{
			// chat.handle(event);

			// if (!chat.isOpen())
			{
				homebutton.handle(event);
				levelbutton.handle(event);

				if (!sound_volumebutton.handle(event))	soundbutton.handle(event);
				if (!music_volumebutton.handle(event))	musicbutton.handle(event);
			}
		}

		// if (!chat.isOpen())
		// {
		pausesystem.handle(event);
		// }
	}
}

void Platform::draw(sf::RenderWindow* &window)
{
	homebutton.draw(window);
	levelbutton.draw(window);
	soundbutton.draw(window);
	musicbutton.draw(window);
	sound_volumebutton.draw(window);
	music_volumebutton.draw(window);
	// chat.draw			(window);
	pausesystem.draw(window);
}

void Platform::mechanics(double elapsedTime)
{
	set();

	fades(elapsedTime);

	// FPS.
	/*FPS::mechanics(elapsedTime);
	if (FPS::timePassed())
	{
	printf("%d\n", FPS::getFPS());
	}*/

	// Mechanics.
	if (!pausesystem.isActive() && !isState())
	{
		//chat.mechanics(elapsedTime);
		//if (chat.isCommand())
		//{
		//	// Knight specs.
		//	if (chat.findCommand("@clear"))			knight_specs.setChosen(-1);
		//	else if (chat.findCommand("@helmet"))	knight_specs.setChosen(0);
		//	else if (chat.findCommand("@body"))		knight_specs.setChosen(1);
		//	else if (chat.findCommand("@shield"))	knight_specs.setChosen(2);
		//	else if (chat.findCommand("@sword"))		knight_specs.setChosen(3);
		//	else if (chat.findCommand("@boots"))		knight_specs.setChosen(4);

		//	// Close application.
		//	else if (chat.findCommand("@close") || chat.findCommand("@exit"))
		//	{
		//		exit.setPressed();
		//	}

		//	// Someone clicked singleplayer.
		//	else if (chat.findCommand("@start") || chat.findCommand("@play"))
		//	{
		//		if (knight_specs.isReady() && information.isReady())
		//		{
		//			singleplayer.setPressed();
		//		}
		//	}

		//	// Exsert / shovel settings.
		//	else if (chat.findCommand("@settings") || chat.findCommand("@keyboard") ||
		//		chat.findCommand("@keys") || chat.findCommand("@sets"))
		//	{
		//		settingsbutton.setActive(!settingsbutton.isActive());
		//	}

		//	// Reload data.
		//	else if (chat.findCommand("@reload") || chat.findCommand("@connect") ||
		//		chat.findCommand("@rel") || chat.findCommand("@con"))
		//	{
		//		reloadbutton.setActive(true);
		//	}

		//	// Update data.
		//	else if (chat.findCommand("@update"))
		//	{
		//		updatebutton.setActive(true);
		//	}

		//	// Turn on/off all chunks.
		//	else if (chat.findCommand("@chunk"))
		//	{
		//		chunkbutton.setChanged(true);
		//		chunkbutton.setActive(!chunkbutton.isActive());
		//	}

		//	// Turn on/off music.
		//	else if (chat.findCommand("@music"))
		//	{
		//		musicbutton.setChanged(true);
		//		musicbutton.setActive(!musicbutton.isActive());
		//	}

		//	// Turn on/off all sounds.
		//	else if (chat.findCommand("@sound"))
		//	{
		//		chunkbutton.setChanged(true);
		//		chunkbutton.setActive(!chunkbutton.isActive());
		//		musicbutton.setChanged(true);
		//		musicbutton.setActive(!musicbutton.isActive());
		//	}

		//	// Map editor.
		//	else if (chat.findCommand("@editor") || chat.findCommand("@edit"))
		//	{
		//		editor = true;
		//		chat.isOpen() = false;
		//	}

		//	// Link buttons in addition.
		//	else if (chat.findCommand("@github"))		github.openWebsite();
		//	else if (chat.findCommand("@scores"))		scores.openWebsite();
		//	else if (chat.findCommand("@website"))	website.openWebsite();

		//	// Tell that command doesn't exist.
		//	else
		//	{
		//		chat.setError();
		//	}
		//}

		if (homebutton.isActive())
		{
			prev = true;
			next = true;
		}
		
		if (levelbutton.isActive())	prev = true;

		sound_volumebutton.mechanics(elapsedTime);
		music_volumebutton.mechanics(elapsedTime);

		// Turn on/off all sounds.
		if (soundbutton.hasChanged())
		{
			cmm::Sound::setPlayable(soundbutton.isActive());
		}

		// Volume of sounds is changed.
		if (sound_volumebutton.hasChanged())
		{
			float value = sound_volumebutton.getGlobalVolume();
			homebutton.setVolume(value);
			levelbutton.setVolume(value);
			soundbutton.setVolume(value);
			musicbutton.setVolume(value);
			sound_volumebutton.setVolume(value);
			music_volumebutton.setVolume(value);
			pausesystem.setVolume(value);
		}

		// Turn on/off music.
		if (musicbutton.hasChanged())
		{
			cmm::Music::setPlayable(musicbutton.isActive());
			musicbutton.isActive() ? music.play() : music.pause();
		}

		// Volume of music is changed.
		if (music_volumebutton.hasChanged())
		{
			music.setVolume(music_volumebutton.getGlobalVolume());
		}
	}
}

void Platform::fades(double elapsedTime)
{
	if (pausesystem.isActive())
	{
		float value = elapsedTime * 0xFF * 2, min = 0xFF * 3 / 4;
		fadeout(value, min);
		pausesystem.fadein(value * 3, min);
		music.fadeout(elapsedTime * 100, music_volumebutton.getGlobalVolume() *0.2);
	}
	else if (isState())
	{
		fadeout(elapsedTime * 0xFF);
		music.fadeout(elapsedTime * 100);
	}
	else
	{
		float value = elapsedTime * 0xFF * 2;
		fadein(value);
		pausesystem.fadeout(value);
		music.fadein(elapsedTime * 100, music_volumebutton.getGlobalVolume());
	}
}

void Platform::fadein(float value, int max)
{
	homebutton.fadein(value, max);
	levelbutton.fadein(value, max);
	soundbutton.fadein(value, max);
	musicbutton.fadein(value, max);
	sound_volumebutton.fadein(value, max);
	music_volumebutton.fadein(value, max);
}

void Platform::fadeout(float value, int min)
{
	homebutton.fadeout(value, min);
	levelbutton.fadeout(value, min);
	soundbutton.fadeout(value, min);
	musicbutton.fadeout(value, min);
	sound_volumebutton.fadeout(value, min);
	music_volumebutton.fadeout(value, min);
	// chat.fadeout				(value, min);
}