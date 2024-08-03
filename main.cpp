#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

class Sandbox {
	static const int width = 160;
	static const int height = 160;

private:
	int first[height][width];
	int second[height][width];

public:
	static const int pixelSize = 5;

	Sandbox() {
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				first[i][j] = 0;
				second[i][j] = 0;
			}
		}
	}

	void place(int x, int y) {
		first[y][x] = 1;
	}

	void update() {
		for (int i = height-1; i > -1; --i) {
			for (int j = 0; j < width; ++j) {
				if (first[i][j] == 1 && i+1 < height && first[i+1][j] == 0) {
					first[i + 1][j] = 1;
					first[i][j] = 0;
				}
			}
		}
	}

	void reset() {
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				first[i][j] = 0;
			}
		}
	}

	void draw(RenderWindow& window) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (first[i][j] == 1) {
					RectangleShape rec = RectangleShape();

					rec.setSize(Vector2f(pixelSize, pixelSize));
					rec.setFillColor(Color::White);
					rec.setPosition(j * pixelSize, i * pixelSize);

					window.draw(rec);
				}
			}
		}
	}
};

int main() {
	RenderWindow window(VideoMode(800, 800), "Sand");
	window.setFramerateLimit(60);

	Sandbox sandbox;

	while (window.isOpen()) {

		window.clear();

		sf::Event event;

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (Keyboard::isKeyPressed(Keyboard::R)) {
				sandbox.reset();
			}
			else if (Mouse::isButtonPressed(Mouse::Left))
			{
				auto pos = Mouse::getPosition(window);

				int x = floor(pos.x / sandbox.pixelSize);
				int y = floor(pos.y / sandbox.pixelSize);

				sandbox.place(x, y);
			}
		}

		sandbox.update();
		sandbox.draw(window);
		window.display();

	}

	return 0;
}