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