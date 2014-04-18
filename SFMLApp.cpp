#include "SFMLApp.h"
#include "SFML/Window/VideoMode.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Graphics/Color.hpp"

SFMLApp::SFMLApp() {
	MapGenerator generator;
	this->currentMap = generator.GenerateMap(60, 60, 3);

	BSPNode* startRoom = generator.getRooms()[0];
	int row = (startRoom->row + (startRoom->height / 2));
	int col = (startRoom->column + (startRoom->width / 2));
	this->player = new Entity(row, col, (this->currentMap->GetTile(row, col)->GetCenter()), true);
	this->moved = false;
}

SFMLApp::~SFMLApp() {
	delete this->window;
	delete this->currentMap;
}

bool SFMLApp::Init(const char * title) {
	this->window = new sf::RenderWindow(sf::VideoMode(SFMLApp::WINDOW_WIDTH, SFMLApp::WINDOW_HEIGHT, 32), title);
	this->viewport = new sf::View(sf::Vector2f((SFMLApp::WINDOW_WIDTH / 2), (SFMLApp::WINDOW_HEIGHT / 2)), sf::Vector2f(SFMLApp::WINDOW_WIDTH, SFMLApp::WINDOW_HEIGHT));
	this->viewport->setCenter(this->player->GetCenter());

	return (this->window != NULL);
}

void SFMLApp::HandleEvent(sf::Event* event) {
	if(event->type == sf::Event::Closed) this->running = false;

	if(event->type == sf::Event::KeyPressed) {
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) this->running = false;

		// Viewport Keys
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) this->viewKeys[0] = true;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) this->viewKeys[1] = true;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) this->viewKeys[2] = true;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) this->viewKeys[3] = true;

		// Movement Keys
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) this->moveKeys[0] = true;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) this->moveKeys[1] = true;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) this->moveKeys[2] = true;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) this->moveKeys[3] = true;
	}

	if(event->type == sf::Event::KeyReleased) {
		// Viewport Keys
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && this->viewKeys[0]) this->viewKeys[0] = false;
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && this->viewKeys[1]) this->viewKeys[1] = false;
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && this->viewKeys[2]) this->viewKeys[2] = false;
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && this->viewKeys[3]) this->viewKeys[3] = false;

		// Movement Keys
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && this->moveKeys[0]) this->moveKeys[0] = false;
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && this->moveKeys[1]) this->moveKeys[1] = false;
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && this->moveKeys[2]) this->moveKeys[2] = false;
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && this->moveKeys[3]) this->moveKeys[3] = false;

		if(this->moved) {
			bool moveKeysDown = false;
			for(int i = 0; i < 4; i++) {
				if(this->moveKeys[i]) {
					moveKeysDown = true;
					break;
				}
			}
			this->moved = moveKeysDown;
		}
	}

	if(event->type == sf::Event::MouseWheelMoved) {
		// Set the zoom level according to the direction the mouse wheel moves.
		if(event->mouseWheel.delta > 0) this->SetViewportZoom(0.5);
		else if(event->mouseWheel.delta < 0) this->SetViewportZoom(2); 
	}
}

void SFMLApp::Update(sf::Time elapsedTime) {
	if(this->viewKeys[0]) this->viewport->move(sf::Vector2f(0.0f, 2.0f));
	if(this->viewKeys[1]) this->viewport->move(sf::Vector2f(-2.0f, 0.0f));
	if(this->viewKeys[2]) this->viewport->move(sf::Vector2f(0.0f, -2.0f));
	if(this->viewKeys[3]) this->viewport->move(sf::Vector2f(2.0f, 0.0f));

	if(!this->moved) {
		if(this->moveKeys[0] && this->CheckValidMove(-1, 0)) {
			this->player->Move(-1, 0, this->viewport);
			this->moved = true;
		} else if(this->moveKeys[1] && this->CheckValidMove(0, 1)) {
			this->player->Move(0, 1, this->viewport);
			this->moved = true;
		} else if(this->moveKeys[2] && this->CheckValidMove(1, 0)) {
			this->player->Move(1, 0, this->viewport);
			this->moved = true;
		} else if(this->moveKeys[3] && this->CheckValidMove(0, -1)) {
			this->player->Move(0, -1, this->viewport);
			this->moved = true;
		}
	}
}

void SFMLApp::Render() {
	this->window->clear(sf::Color::Black);

	this->window->setView(*(this->viewport));
	this->currentMap->DrawTiles(this->window);
	this->player->Draw(this->window);
	this->window->setView(this->window->getDefaultView());

	this->window->display();
}

void SFMLApp::Cleanup() {

}

void SFMLApp::LoadTextures() {

}

void SFMLApp::SetViewportFocus(sf::Vector2f center) {
	this->viewport->setCenter(center);
}

void SFMLApp::SetViewportZoom(float factor) {
	this->viewport->zoom(factor);
}

bool SFMLApp::CheckValidMove(int rOff, int cOff) {
	int newRow = this->player->GetRow() + rOff;
	int newCol = this->player->GetColumn() + cOff;
	return (((newRow >= 0) && (newRow < this->currentMap->GetHeight())) && ((newCol >= 0)&& (newCol < this->currentMap->GetWidth()))) && 
		   (this->currentMap->GetTile(newRow, newCol)->IsTraversable());
}