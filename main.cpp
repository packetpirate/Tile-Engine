#include "SFMLApp.h"
#include "SFML/System/Clock.hpp"

int SFMLApp::Execute() {
	if(!this->Init("Tile Engine")) return -1;

	this->running = true;
	for(int i = 0; i < 4; i++) {
		this->viewKeys[i] = false;
		this->moveKeys[i] = false;
	}

	sf::Event event;
	sf::Clock clock;
	while(this->running) {
		while(this->window->pollEvent(event)) this->HandleEvent(&event);

		this->Update(clock.restart());
		this->Render();
	}

	this->Cleanup();

	return 0;
}

int main(int argc, char ** argv) {
	SFMLApp app;
	return app.Execute();
}