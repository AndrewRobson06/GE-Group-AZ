#include <sstream>
#include <SFML/Graphics.hpp>
#include <string> //add to GDD
#include <cstdlib> //add to GDD
#include <iostream> // add to GDD
#include <ctime> //add to GDD

/*
	How the logic foe determining what fish will be caught works like this:
	Each rarity holds a diffrent number of fish that belong to that raity. Each fish in that rarity has a range in which thier fishID represents.
	For example: a goldfish is in the common rarity and has a fishID of 35.
	Later on, the code will check the rarity, then it will check the fishID
*/
int fishID = 0; // get a number between 1 and 100 to determine what fish will be caught
int fishRarity = 0; // get a number between 1 and 100 to determine what rarity the fish is from

// the value and size of the chosen fish
int value = 0;
int size = 0;

//the rarity of the fish 0 = common, 1 = uncommon, 2 = rare, 3 = ultra rare, 4 = legendary
int rarity = 0;

//get a unique random number each time
void randomise() {
	srand(time(0));

	fishRarity = rand() % 101;
	fishID = rand() % 101;
}

int main() {
	randomise();
	std::cout << fishID;
	std::cout << fishRarity;
}