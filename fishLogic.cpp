#include <sstream>
#include <SFML/Graphics.hpp>
#include <string> //add to GDD
#include <cstdlib> //add to GDD
#include <iostream> // add to GDD
#include <ctime> //add to GDD

using namespace std;

/*
	How the logic foe determining what fish will be caught works like this:
	while there is no hit, the algorithm will do cascading rolls to decide the rarity.
	it starts with rolling for legendary and if that fails it rolls again for ultra rare and so on until one hits.
	once a rarity hits, it then chooses a random fish from that rarites array and then returns chosenFish
*/

int fishID = 0; // Value used to get the fish from the array
int fishRarity = 0; // Get a number between 1 and 100 to determine what rarity the fish is from

/*
	Variables for the fish rarity chances

	The rarites go (base odds):

	1% ( == 100): Legendary
	5% ( < 100 AND >= 95): Ultra Rare
	14% ( < 95 AND >= 81): Rare
	35% (< 81 OR >= 46): Uncommon
	45% ( < 46 ): Common
*/

//1%
int legendaryChance = 100;

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

// the value of the fish
int value = 0;

//the rarity of the fish 0 = common, 1 = uncommon, 2 = rare, 3 = ultra rare, 4 = legendary
int rarity = 0;

//the chosen fish
std::string chosenFish = "";

//all values are placeholders and will be changed

//List of all legendary fish
std::string legendaryFish[2][3] = { 
									{ "Blue Crayfish", "Koi",   "Vampire Crab" },
								    { "9600",		   "15000", "12500" } 
								  };

int legendaryFishArraySize = sizeof(legendaryFish[0]) / sizeof(legendaryFish[0][0]);

//List of all ultra rare fish
std::string ultraRareFish[2][6] = {
									{ "Neon Tetra", "Zebra Pleco", "Lamprey", "Piranha", "Archerfish", "Sturgeon"},
									{ "2350",		"3200",		   "2670",	  "3800",    "2980",       "3150"}
								  };

int ultraRareFishArraySize = sizeof(ultraRareFish[0]) / sizeof(ultraRareFish[0][0]);

//List of all rare fish
std::string rareFish[2][8] = {
								{ "Steelhead Trout", "Catfish", "Char", "American Eel", "Gar", "White Bass", "Pike", "Arowana"},
								{ "186",			 "170",		"210",	"190",			"215", "122",		 "298",  "240"}
							 };

int rareFishArraySize = sizeof(rareFish[0]) / sizeof(rareFish[0][0]);

//List of all uncommon fish
std::string uncommonFish[2][6] = {
									{ "Bluegill", "Crab", "Salmon", "Rainbow Trout", "Bass", "Shad"},
									{ "28",		  "26",	  "40",		"30",			 "35",	 "25"}
								 };

int uncommonFishArraySize = sizeof(uncommonFish[0]) / sizeof(uncommonFish[0][0]);

//List of all common fish
std::string commonFish[2][6] = {
									{ "Goldfish", "Perch", "Minnow", "Crayfish", "Brwon Trout", "Carp"},
									{ "10",		  "13",	   "9",		 "15",		 "18",			"12"}
							   };

int commonFishArraySize = sizeof(commonFish[0]) / sizeof(commonFish[0][0]);


//get a unique random number each time from 1 to 100
int randomise() {
	
	//fishRarity = 0;
	fishRarity = rand() % 101;

	return fishRarity;

}

//determine which fish is to be caught
void getFish() {

	//continue utill a rarity hits
	while (hit == false) {
		randomise();

		//roll for legendary
		if (fishRarity == legendaryChance) {

			rarity = 4; //Legendary

			fishID = rand() % legendaryFishArraySize; //get a random number used to pick a fish from

			chosenFish = legendaryFish[0][fishID];

			value = stoi(legendaryFish[1][fishID]);

			hit = true;

		}
		else if (fishRarity < ultraRareChanceMax && fishRarity >= ultraRareChanceMin) {

			rarity = 3; //Ultra rare

			fishID = rand() % ultraRareFishArraySize; //get a random number used to pick a fish from

			chosenFish = ultraRareFish[0][fishID];

			value = stoi(ultraRareFish[1][fishID]);

			hit = true;
		}

		else if (fishRarity < rareChanceMax && fishRarity >= rareChanceMin) {

			rarity = 2; //rare

			fishID = rand() % rareFishArraySize; //get a random number used to pick a fish from

			chosenFish = rareFish[0][fishID];

			value = stoi(rareFish[1][fishID]);

			hit = true;
		}

		else if (fishRarity < uncommonChanceMax && fishRarity >= uncommonChanceMin) {

			rarity = 1; //uncommon

			fishID = rand() % uncommonFishArraySize; //get a random number used to pick a fish from

			chosenFish = uncommonFish[0][fishID];

			value = stoi(uncommonFish[1][fishID]);

			hit = true;
		}

		//since uncommon failed, it must be common
		else {

			rarity = 0; //common

			fishID = rand() % commonFishArraySize; //get a random number used to pick a fish from

			chosenFish = commonFish[0][fishID];

			value = stoi(commonFish[1][fishID]);

			hit = true;

		}
	}
}

int main() {

	//seed the random number on program start
	srand(static_cast<unsigned int>(time(0)));


	//testing
	string input;
	
	while (true) {

		cout << "enter r to roll, e to exit: ";
		cin >> input;
		cout << "\n";

		if (input == "e") {
			break;
		}

		if (input == "r") {
			getFish();

			//testing values
			std::cout << "Fish ID: " << fishID << "\n";
			std::cout << "Fish rarity: " << fishRarity << "\n";
			std::cout << "chosen fish: " << chosenFish << "\n";
			std::cout << "Value: " << value << "g" << "\n";
			cout << "\n";

			hit = false;

		}
	}
	return 0;
} 