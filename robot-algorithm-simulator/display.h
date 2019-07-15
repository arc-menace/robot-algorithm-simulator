#pragma once
#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <SFML/Graphics.hpp>

namespace rmas {
	template<typename class_type>
	class Display {
	private:
		int width = 1920;
		int height = 1080;
		std::string name = "Untitled";
	public:
		Display() {
			sf::RenderWindow window(sf::VideoMode(width, height), name;
		}
	};
}

#endif