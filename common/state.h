#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

namespace cmm
{
	enum STATES
	{
		LOADING = 0,
		INIT,
		LOGIN = 2,
		MENU,
		LEVELMENU = 4,
		PLATFORM,
		TABLE = 6,
		EDITOR,
		DEFAULT
	};

	class State
	{
	protected:
		bool prev;
		bool next;
		bool exit;
		virtual bool isReady() const = 0;

	public:
		State();
		virtual ~State();

	protected:
		bool isPrev() const;
		bool isNext() const;
		bool isExit() const;
		bool isState() const;

	public:
		virtual void setState(int &state) = 0;
		virtual void load(const float& screen_w, const float &screen_h) = 0;
		virtual void handle(const sf::Event &event) = 0;
		virtual void draw(sf::RenderWindow* &window) = 0;
		virtual void mechanics(const double &elapsedTime) = 0;
	};
}