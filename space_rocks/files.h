#pragma once
#include <iostream>
#include <fstream>
#include "input.h"
#include "engine.h"
#include <map>

// Static methods for loading and saving data to files
class Files {
public:

	static void loadControls();
	static void saveControls();

	static bool loadSettings();
	static void saveSettings();

	static std::multimap<unsigned int, std::string> loadHighscores();
	static void saveHighscores(std::multimap<unsigned int, std::string> highscores);

};