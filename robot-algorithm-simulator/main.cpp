#include "rmas6219.h"
#include <SFML/Graphics.hpp>

using namespace rmas;

int main() {
	/*
		Graphics Function:
		takes the logs. Each event has a number assigned by the order it occured in the simulation
		Graphics copies each log to a throw away vector
		as it used the events to animate, it remebers where it was, so that it isn't scanning through whole vectors.
	*/

	//define robot
	Robot robot;
	//define blocks/obstacles if applicable

	//build environment
	Environment environment(robot);

	//run algorithm

	//show results
	environment.move_log.print_log();

	//Animate Robot Motion
	sf::RectangleShape robot_shape(sf::Vector2f(robot.return_length() * 12, robot.return_width() * 12));
	robot_shape.setFillColor(sf::Color::Blue);

	sf::RenderWindow window(sf::VideoMode(600, 600), "Simulation", sf::Style::Close);

	window.setVerticalSyncEnabled(true);

	int count = 0;
	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear(sf::Color::Black);
		//draw here
		Event::Move temp_event = environment.move_log.return_event();
		robot_shape.setPosition(temp_event.return_x() * 12, temp_event.return_y() * 12);
		robot_shape.setRotation(temp_event.return_orientation());
		window.draw(robot_shape);

		window.display();
		count++;
	}

	return 0;
}