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
	std::cout << "test" << std::endl;
	//define robot
	Robot robot;
	robot.mechanum(true);
	//define blocks/obstacles if applicable

	//build environment
	Environment environment(robot);

	//run algorithm
	environment.forward(40);
	environment.right(40);

	//show results
	environment.move_log.print_log();

	//Animate Robot Motion
	int scale = 5;
	sf::RectangleShape robot_shape(sf::Vector2f(robot.return_length() * scale, robot.return_width() * scale));
	robot_shape.setFillColor(sf::Color::Blue);
	robot_shape.setOrigin(robot.return_length() * scale / 2, robot.return_width() * scale/ 2);
	
	sf::RectangleShape map_shape(sf::Vector2f(96 * scale, 96 * scale));
	map_shape.setFillColor(sf::Color(183, 65, 14));

	//sf::RectangleShape mothership(sf::Vector2f())

	std::vector<sf::RectangleShape> block_shapes;
	std::vector<sf::CircleShape> obstacle_shapes;

	sf::RenderWindow window(sf::VideoMode(700, 600), "Simulation", sf::Style::Close);

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
		map_shape.setPosition(20, 20);
		window.draw(map_shape);

		Event::Move temp_event = environment.move_log.return_event(count);
		robot_shape.setPosition(temp_event.return_x() * scale + 20, temp_event.return_y() * scale + 20);
		robot_shape.setRotation(temp_event.return_orientation());		
		window.draw(robot_shape);



		window.display();
		while (count < environment.move_log.return_size()) {
			count++;
		}
	}

	return 0;
}