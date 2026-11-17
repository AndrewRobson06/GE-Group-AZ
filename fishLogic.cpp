#include <sstream>
#include <SFML/Graphics.hpp>
#include <string> //add to GDD
#include <cstdlib> //add to GDD
#include <iostream> // add to GDD
#include <ctime> //add to GDD

using namespace std;

/*
	How the logic foe determining what fish will be caught works like this:
	while there is no chosen fish, the algorithm will do cascading rolls to decide the rarity.
	it starts with rolling for legendary and if that fails it rolls again for ultra rare and so on until one hits.
	once a rarity hits, it then chooses a random fish from that rarites array and then returns chosenFish
*/

int fishID = 0; // value used to get the fish from the array
int fishRarity = 0; // get a number between 1 and 100 to determine what rarity the fish is from

//variables for the fish rarity chances

/*
	The rarites go (base odds):

	1% ( == 100): Legendary
	5% ( < 100 AND >= 95): Ultra Rare
	14% ( < 95 AND >= 81): Rare
	35% (< 81 OR >= 46): Uncommon
	45% ( < 46 ): Common
*/

int legendaryChance = 100; // 1%

//5%
int ultraRareChanceMax = 100;
int ultraRareChanceMin = 95;

//14%
int rareChanceMax = 95;
int rareChanceMin = 81;

//35%
int uncommonChanceMax = 81;
int uncommonChanceMin = 46;

//45% 
int commonChance = 46;

//has a rarity been hit?
bool hit = false;

// the value and size of the chosen fish
int value = 0;
int size = 0;

//the rarity of the fish 0 = common, 1 = uncommon, 2 = rare, 3 = ultra rare, 4 = legendary
int rarity = 0;

//the chosen fish
std::string chosenFish = "";

//List of all common fish
std::string commonFish[3] = { "Goldfish", "Perch", "PLACEHOLDER" };
int commonFishArraySize = sizeof(commonFish);

//List of all uncommon fish
std::string uncommonFish[3] = { "PLACEHOLDER", "PLACEHOLDER2", "PLACEHOLDER3" };
int uncommonFishArraySize = sizeof(uncommonFish);

//List of all rare fish
std::string rareFish[3] = { "PLACEHOLDER", "PLACEHOLDER2", "PLACEHOLDER3" };
int rareFishArraySize = sizeof(rareFish);

//List of all ultra rare fish
std::string ultraRareFish[3] = { "PLACEHOLDER", "PLACEHOLDER2", "PLACEHOLDER3" };
int ultraRareFishArraySize = sizeof(ultraRareFish);

//List of all legendary fish
std::string legendaryFish[3] = { "PLACEHOLDER", "PLACEHOLDER2", "PLACEHOLDER3" };
int legendaryFishArraySize = sizeof(legendaryFish);

//get a unique random number each time
void randomise() {
	srand(time(0));

	fishRarity = rand() % 101;
	//fishRarity = 100;
	//fishID = rand() % 101;
}

void getFish() {

	//continue utill a rarity hits
	while (hit = false) {

		//roll for legendary
		if (fishRarity == legendaryChance) {

			rarity = 4; //Legendary

			fishID = rand() % legendaryFishArraySize + 1; //get a random number used to pick a fish from

			chosenFish = legendaryFish[fishID];

			hit = true;

			//return chosenFish;
		}
		else {
			randomise();
		}

		//reroll for ultra rare if legendary missed
		if (fishRarity < ultraRareChanceMax && fishRarity > ultraRareChanceMin) {

			rarity = 3; //Ultra rare

			fishID = rand() % ultraRareFishArraySize + 1; //get a random number used to pick a fish from

			chosenFish = ultraRareFish[fishID];

			hit = true;
		}
		else {
			randomise();
		}

		//reroll for rare if ultra rare missed
		if (fishRarity < rareChanceMax && fishRarity > rareChanceMin) {

			rarity = 2; //rare

			fishID = rand() % rareFishArraySize + 1; //get a random number used to pick a fish from

			chosenFish = rareFish[fishID];

			hit = true;

		}
		else {
			randomise();
		}

		//reroll for uncommon if rare missed
		if (fishRarity < uncommonChanceMax && fishRarity > uncommonChanceMin) {

			rarity = 1; //uncommon

			fishID = rand() % uncommonFishArraySize + 1; //get a random number used to pick a fish from

			chosenFish = uncommonFish[1];

			hit = true;
		}
		//since uncommon failed, it must be common
		else {

			rarity = 0; //common

			fishID = rand() % commonFishArraySize + 1; //get a random number used to pick a fish from

			chosenFish = commonFish[1];

			hit = true;

		}

	}
	
}

int main() {
	randomise();
	getFish();
	
	//testing values
	std::cout << fishID << "\n";
	std::cout << fishRarity << "\n";
	//std::cout << commonFish[1] << "\n";
	//std::cout << legendaryFishArraySize << "\n";
	//std::cout << rarity;
	std::cout << chosenFish << "\n";
	printf("%s\n", chosenFish.c_str());
	
}