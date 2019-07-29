#include "rmas6219.h"
#include <SFML/Graphics.hpp>

using namespace rmas;
void define_robot(Robot &robot, bool advanced = false);
void define_blocks(std::vector<Block> &blocks, bool advanced = false);
void define_obstacles(std::vector<Obstacle> &obstacles, bool advanced = false);
void define_map(Rectangle &map, bool advanced = false);
void define_mothership(Mothership &mothership, bool advanced = false);


int main() {
	Robot robot(true);
	Rectangle map;
	std::vector<Block> blocks{};
	std::vector<Obstacle> obstacles{};
	Mothership mothership;

	bool test_mode = false;

	for (;;) {
		std::cout << "1)\tRun Simulation\n" << "2)\tChange Settings\n"
			<< "3)\tChange Advanced Settings\n" << "4)\tRun in Developer Mode\n"
			<< "\nSelection: ";
		int choice;
		std::cin >> choice;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << ERROR_INVALID_INPUT << std::endl;
			continue;
		}
		switch (choice) {
		case 1:
			break;
		case 2:
			define_robot(robot);
			define_map(map);
			define_mothership(mothership);
			define_blocks(blocks);
			define_obstacles(obstacles);
		case 3:
			define_robot(robot, true);
			define_map(map, true);
			define_mothership(mothership, true);
			define_blocks(blocks, true);
			define_obstacles(obstacles, true);
		case 4:
			test_mode = true;
			break;
		default:
			std::cerr << ERROR_INVALID_INPUT << std::endl;
			continue;
		}
		break;
	}

	//Define blocks (in environment if random)
	//Define obstacles (in environment if random)
	//Define Mothership
	sf::RenderWindow window(sf::VideoMode(700, 600), "Simulation", sf::Style::Close);

	//Define environment
	Environment environment(robot, map, 6, 0, true, true);
	


	//run algorithm

	//show results
	//environment.move_log.print_log();

	//Animate Robot Motion
	/*
		Graphics Function:
		takes the logs. Each event has a number assigned by the order it occured in the simulation
		Graphics copies each log to a throw away vector
		as it used the events to animate, it remembers where it was, so that it isn't scanning through whole vectors.
	*/

	int scale = 5;
	sf::RectangleShape robot_shape(sf::Vector2f(round(robot.return_length() * scale), round(robot.return_width() * scale)));
	robot_shape.setFillColor(sf::Color::Blue);
	robot_shape.setOrigin(robot.return_length() * scale / 2, robot.return_width() * scale/ 2);
	
	sf::RectangleShape map_shape(sf::Vector2f(96 * scale, 96 * scale));
	map_shape.setFillColor(sf::Color(183, 65, 14));

	//sf::RectangleShape mothership(sf::Vector2f())

	std::vector<sf::Vector2f> block_positions;
	for (int i = 0; i < 6; i++) {
		block_positions.push_back(sf::Vector2f(round(environment.return_block(i).return_width() * scale), round(environment.return_block(i).return_width() * scale)));
	}
	std::vector<sf::RectangleShape> block_shapes;
	for (int i = 0; i < 6; i++) {
		block_shapes.push_back(sf::RectangleShape(block_positions[i]));
		block_shapes[i].setFillColor(sf::Color(169, 169, 169));
	}

	std::vector<sf::CircleShape> obstacle_shapes;

	

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

		if (test_mode) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
				environment.rotate_ccw(1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
				environment.rotate_cw(1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
				//Should eventually be forward
				environment.backward(1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
				//Should eventually be backward
				environment.forward(1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
				environment.left(1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
				environment.right(1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
				environment.diagonal_left_up(1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
				environment.diagonal_right_up(1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
				environment.diagonal_left_down(1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
				environment.diagonal_right_down(1);
			}
		}
		
		Event::Move temp_event = environment.move_log.return_event(count);
		std::vector<double> position = environment.move_log.return_event(count).return_atts();
		robot_shape.setPosition(position[0] * scale + 20, position[1] * scale + 20);
		robot_shape.setRotation(position[2]);		
		window.draw(robot_shape);
		for (int i = 0; i < 6; i++) {
			block_shapes[i].setPosition(environment.return_block(i).return_x()* scale + 20, environment.return_block(i).return_y() * scale + 20);
			block_shapes[i].setRotation(environment.return_block(i).return_orientation());
			window.draw(block_shapes[i]);
		}

		window.display();
		while (count < environment.move_log.return_size()) {
			count++;
		}
	}
	return 0;
}