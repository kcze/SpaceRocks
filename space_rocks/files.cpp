#include "files.h"

// Loads controls from a file
void Files::loadControls() {
	std::ifstream file;
	file.open("controls.dat");

	// If file doesn't exist, save default controls
	if (!file.good())
	{
		file.close();
		saveControls();
		return;
	}

	// Loading data
	while (!file.eof())
	{
		int i;
		file >> i;
		Input::KeyCode keyCode = (Input::KeyCode)i;

		// Loading key number
		bool keyboardKey;
		if (file >> keyboardKey)
		{
			file >> i;
			Input::keys[keyCode].first = (Keyboard::Key)i;
		}
		else
		{
			file >> i;
			Input::keys[keyCode].first = (unsigned int)i;
		}

		// Loading key name
		file >> Input::keys[keyCode].second;
	}

	file.close();
}

// Saves controls to a file
void Files::saveControls() {
	std::ofstream file;
	file.open("controls.dat");

	for (auto pair : Input::keys)
	{
		// Saving KeyCode
		file << (int)pair.first << " ";
		// Saving true if variant is a Keyboard::Key and false if it's a unsigned int
		if (std::holds_alternative<Keyboard::Key>(pair.second.first))
			file << true << " " << (int)std::get<Keyboard::Key>(pair.second.first) << " ";
		else
			file << false << " " << (int)std::get<unsigned int>(pair.second.first) << " ";
		// Saving name string
		file << pair.second.second << std::endl;
	}

	file.close();
}

// Load settings
bool Files::loadSettings() {
	std::ifstream file;
	file.open("settings.dat");

	// If file doesn't exist, return
	if (!file.good())
	{
		file.close();
		return true;
	}

	// Loading data
	bool windowed = false;
	file >> windowed;

	sf::Vector2u resolution;

	file >> resolution.x;
	file >> resolution.y;

	// Fullscreen or change resolution
	if (windowed)
		Engine::getWindow().setSize(resolution);

	file.close();

	return windowed;
}


// Save settings
void Files::saveSettings() {
	std::ofstream file;
	file.open("settings.dat");

	// Saving fullscreen state
	if (Engine::isWindowed())
		file << true << " ";
	else
		file << false << " ";

	// Saving resolution
	file << Engine::getWindowSize().x << " " << Engine::getWindowSize().y;

	file.close();
}

// Loads highscores from a file
std::multimap<unsigned int, std::string> Files::loadHighscores() {
	std::multimap<unsigned int, std::string> highscores;

	std::ifstream file;
	file.open("highscores.dat");

	// If file doesn't exist, return
	if (!file.good())
	{
		file.close();
		return highscores;
	}

	// Loading data
	while (!file.eof())
	{
		// Loading score
		unsigned int score = 0;
		file >> score;

		// Reached the last line
		if (score == 0)
			return highscores;

		// Loading name
		std::string name;
		file >> name;
		highscores.emplace(score, name);
	}

	file.close();

	return highscores;
}

// Saves highscores to a file
void Files::saveHighscores(std::multimap<unsigned int, std::string> highscores) {

	std::ofstream file;
	file.open("highscores.dat");

	for (auto pair : highscores)
	{
		// Saving score
		file << pair.first << " ";
		// Saving name string
		file << pair.second << std::endl;
	}

	file.close();
}