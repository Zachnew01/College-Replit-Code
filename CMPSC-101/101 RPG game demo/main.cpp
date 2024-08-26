// CMPSC 101 Final Project by Matt P 2018
// WARNING - This program does not follow the Coding Standards very closely

#include <iostream> // cause duh
#include "map.h"    // file containing map pictures
#include <string>   // for use of strings
#include <ctime>    // for true random numbers
#include <cstdlib>  // just incase it is needed
using namespace std;

// ********** function declarations
void Continue();         // press enter to continue
void Instructions();     // display instructions
int Inn(int gold);       // staying at the inn
void TownInstructions(); // display town instructions
void Forest(string& enemy, int& enemyHP, int& enemyAttack, int progress); // random forest event
void Cave(string& enemy, int& enemyHP, int& enemyAttack, int progress);   // random cave event

// *********** global variables
char red[] = { 0x1b, '[', '1', ';', '3', '1', 'm', 0 }; // red text
char normal[] = { 0x1b, '[', '1', ';', '3', '9', 'm', 0 }; // white text

int main()
{
  // ******* local variables
  int health = 50;            // player health
  int attack = 3;             // player attack
  int defense = 1;            // player defense
  string command = " ";       // player input
  int location = 1;           // current location
  int potions = 1;            // potions available
  int gold = 25;              // total gold
  bool outside = true;        // still alive?
  string armor = "Cloth(1)";  // for player to view his armor
  string weapon = "Knife(3)"; // for player to view his weapon
  int enemyHP = 0;            // enemy's hp
  string enemy = " ";         // current enemy
  bool battle = false;        // are you in a fight?
  bool town = false;          // are you in town?
  bool merchant = false;      // are you shopping?
  int enemyAttack = 0;        // how much damage enemy does
  int damage = 0;             // how much damage you recieve
  int one23 = 0;              // for choosing misc actions
  int ranNum = 0;             // random number
  int foundGold = 0;          // gold found on a corpse
  string garbage = " ";       // for storing garbage values
  
  //////////// set up
  srand(time(0));           

  // **********opening text***********
  cout << normal << "Welcome to: A short but perilous journey" << endl;
  cout << "     A text based adventure game By:" << endl;
  cout << "            Matthew Perkins" << endl << endl << endl;
  cout << "You currently live in a secluded village in the Scavi Mountains. Your village's long standing tradition is to send out the first born of every family when they reach 20 with the mission to 'destroy a great beast'. Almost none make it back alive. You plan to be one of those few.";
  Continue();
  Instructions();
  cout << "Your objective is to make it to the end of the map alive. Good Luck." << endl << endl;

// ********** main game loop

// outside combat
while (outside == true)
{
  // *******In battle*******
  while (battle == true && health > 0)
  {
    if (enemyHP > 0) // enemy still alive
    {
      cout << "In Combat" << endl;
      cout << "Please enter a command: ";
      cin >> command;
      getline(cin, garbage);
      cout << endl;
      // Check
      if (command == "check") // check enemy status
      {
        cout << "Enemy: " << enemy;
        cout << "   HP: " << enemyHP;
        cout << "   Attack: " << enemyAttack << endl << endl;
        cout << "Your current Health: " << health << endl;
        cout << "Current weapon: " << weapon;
        cout << "  Current armor: " << armor << endl << endl;
      }

      else if (command == "attack") // attack enemy
      {
        
        cout << "You swing at the " << enemy << " dealing ";
        cout << attack << " damage" << endl;
        enemyHP -= attack;

        if (enemyHP > 0)
        {
          cout << "The " << enemy << " retaliates dealing ";
          damage = enemyAttack - defense;
          if (damage < 1)
          {
            damage = 1;
            cout << damage << " damage" << endl << endl;
            health -= damage;
          }
          else
          {
            cout << damage << " damage" << endl << endl;
            health -= damage;
          }
        }
      }
      
      else if (command == "defend") // defend + attack
      {
        cout << "You take a defensive stance doubling your defense" << endl;
        defense *= 2; // double defense for defend duration
        damage = enemyAttack - defense;
        if (damage < 1) // damage can't go below 1
        {
          damage = 1;
        }
        cout << "The " << enemy << " attacks dealing ";
        cout << damage << " damage" << endl;
        health -= damage;
        cout << "You counter dealing " << attack << " damage" << endl;
        enemyHP -= attack;
        if (enemyHP > 0) // make sure enemy still alive
        {
          cout << "The " << enemy << " retaliates dealing ";
          if (damage < 1) // damage can't go below 1
          {
            damage = 1;
            cout << damage << " damage" << endl << endl;
            health -= damage;
          }

          else
          {
            cout << damage << " damage" << endl << endl;
            health -= damage;
          }
        }
        defense /= 2; // reset defense to normal
      }

      else
      {
        cout << "Invalid command" << endl << endl;
      }
    }
    else // victory
    {
      cout << endl << "You defeated the " << enemy << endl;
      if (enemy == "Goblin") // goblin reward
      {
        foundGold = (rand() % 11 + 10);
        if (location > 6)
        {
          foundGold += (rand() % 11 + 5); // more gold further in
        }
        cout << "You found " << foundGold << " gold on the body";
        gold += foundGold;
        if (rand() % 10 == 0)
        {
          cout << endl << "The goblin was carrying a potion as well! You place the potion in your bag.";
          potions++;
        }

        Continue();
      }

      if (enemy == "Thief") // thief reward
      {
        foundGold = (rand() % 11 + 15);
        if (location > 6) // more gold further in
        {
          foundGold += (rand() % 11 + 10);
        }
        cout << "You found " << foundGold << " gold on the body";
        gold += foundGold;

        if (rand() % 5 == 0)
        {
          cout << endl << "The thief was carrying a potion as well! You place the potion in your bag.";
          potions++;
        }
        
        Continue();
      }

      if (enemy == "Wolf" && !(location
       == 5 || location == 7)) // road wolf reward
      {
        foundGold = (rand() % 11 + 10);
        if (location == 8) // more gold futher in
        {
          foundGold += (rand() % 11 + 5);
        }
        gold += foundGold;
        cout << "With the wolf dead, you do the man the service of burying him. Before you do however, you find a small pouch of ";
        cout << foundGold;
        cout << " gold next to the body. You consider it payment for your good deed as he won't be needing it where he's going";
        Continue();
      }

      if (enemy == "Wolf" && (location == 5 || location == 7)) // cave wolf reward
      {
        foundGold = (rand() % 11 + 10);
        if (location == 7) // more gold further in
        {
          foundGold += (rand() % 11 + 5);
        }
        gold += foundGold;
        cout << "With the wolf slain, you turn to leave. Before you do, you see something shiny in the corner of your eye. When you get closer, you see a small sachel of gold next to some long eaten human remains. There's ";
        cout << foundGold << "gold inside.";
        Continue();
      }

      if (enemy == "Tre-ent") // tre-ent reward
      {
        foundGold = (rand() % 11 + 25);
        if (location > 6)
        {
          foundGold += (rand() % 11 + 10); // more gold further in
        }
        gold += foundGold;
        cout << "Tre-ents consume their prey to 'add their life force to the forest'. However they only consume organic material leaving the rest wedged in their trunks You find a bag of ";
        cout << foundGold << "gold in the corpse of the tre-ent." << endl;
        if (rand() % 5 == 0) // found a sword
        {
          if (location == 3) // small sword
          {
          cout << "You also found a sword stuck inside a hollow section of the tre-ent! You replace your " << weapon << " with it";
          weapon = "Sword(5)";
          attack = 5;
          }

          else if (location > 6) // longsword
          {
            cout << "You found a longsword jammed in the side of the tre-ent. It must of come from a previous victim's attempt at killing the tre-ent." << endl;
            if (attack < 8)
            {
              cout << "You equip the new sword";
              weapon = "Longsword(8)";
              attack = 8;
            }
            
            else
            {
              cout << "Your current sword is already comparable so you leave it where it lies";
            }
          }
        }
        
        Continue();
      }

      if (enemy == "Armored Goblin")
      {
        foundGold = (rand() % 11 + 25);
        if (location > 6)
        {
          foundGold += (rand() % 11 + 10); // more gold further in
        }
        gold += foundGold;
        cout << "With the long fight over you loot the goblin and find " << foundGold;
        cout << " on its body." << endl;
        if (rand() % 5 == 0)
        {
          cout << "The goblin's armor is still intact and amazingly it looks to be about your size. ";
          if (location < 6 || defense < 5)
          {
            cout << "After giving the armor a thorough cleaning, you replace it with your current armor" << endl;
            if (location < 6)
            {
              armor = "Leather(3)";
              defense = 3;
            }

            else
            {
              armor = "Chainmail(5)";
              defense = 5;
            }
          }

          else
          {
            cout << "Unfortunately your current armor is already comparable and you leave it where it lies." << endl;
          }
        }
      }

      if (enemy == "Black Drake") // final boss
      {
        cout << endl << "You've done it! The beast is slain. You take a scale from its body, a tooth from its mouth, and a horn from its head as both a trophy and proof of your glorious victory. You start the long and likely uneventful journey home, knowing the pride you have brought yourself and your family." << endl << endl;
        cout << "Thanks for playing! - This was a short text based D&D like game created by Matthew Perkins for my CMPSC101 Final Project.";
        outside = false;
        battle = false;
      }

      if (enemy != "Black Drake") // Not the end of the game
      {
        cout << endl << "You return to the path and continue your journey" << endl << endl;
        battle = false;
      }
    }
  }
  // *******Shopping********
while (merchant == true)
{

  if (location == 2) // potion menu
  {
    cout << " ___________________________________________" << endl;
    cout << "| Potions - 5g ('p' to buy)                |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl << endl;
  }

  if (location == 4) // cheap vendor menu
  {
    cout << " __________________________________________" << endl;
    cout << "| Leather(3) armor - 20g ('a' to buy)      |" << endl;
    cout << "| Sword(5) weapon - 20g ('w' to buy)       |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl << endl;
  }

  if (location == 6) // town vendor menu
  {
    cout << " __________________________________________" << endl;
    cout << "| Potions - 10g ('p' to buy)               |" << endl;
    cout << "| Leather(3) armor - 25g ('a' to buy)      |" << endl;
    cout << "| Sword(5) weapon - 25g ('w' to buy)       |" << endl;
    cout << "| Longsword(8) weapon - 40g ('l' to buy)   |" << endl;
    cout << "| Chainmail(5) armor - 40g ('c' to buy)    |" << endl;
    cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl << endl;
  }

  if (location == 10 && one23 == 1) // final expensive vendor menu
  {
    cout << " __________________________________________" << endl;
    cout << "| Potions - 12g ('p' to buy)               |" << endl;
    cout << "| Longsword(8) weapon - 50g ('l' to buy)   |" << endl;
    cout << "| Chainmail(5) armor - 50g ('c' to buy)    |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl << endl;
  }

  if (location == 10 && one23 == 2) //  final cheap vendor menu
  {
    cout << " __________________________________________" << endl;
    cout << "| Potions - 8g ('p' to buy)                |" << endl;
    cout << "| Longsword(8) weapon - 35g ('l' to buy)   |" << endl;
    cout << "| Chainmail(5) armor - 35g ('c' to buy)    |" << endl;
    cout << "|                                          |" << endl;
    cout << "|                                          |" << endl;
    cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl << endl;
  }

  cout << "Current gold: " << gold << endl;
  cout << "What would you like ('exit' to leave): ";
  cin >> command;
  getline(cin, garbage);
  cout << endl;

  if (command == "p" && !(location == 4)) // buying discount potion
  {
    if (gold > 4 && location == 2) // can afford cheap potion
    {
      potions++;
      gold -= 5;
      cout << "You bought a potion for 5 gold";
      Continue();
    }
    
    else if (gold > 9 && location == 6)
    {
      potions++;
      gold -= 10;
      cout << "You bought a potion for 10 gold";
      Continue();
    }

    else if (gold > 7 && location == 10 && one23 == 2)
    {
      potions++;
      gold -= 8;
      cout << "You bought a potion for 8 gold" << endl;
      cout << red << "(press enter to continue)" << normal << endl;
      getline(cin, garbage);
    }

    else if (gold > 11 && location == 10 && one23 == 1)
    {
      potions++;
      gold -= 12;
      cout << "You bought a potion for 12 gold";
      Continue();
    }

    else
    {
      cout << "You don't have enough gold for that";
      Continue();
    }
  }

  else if (command == "a" && (location == 4 || location == 6)) // buying leather armor
  {
    if ((gold > 19 && location == 4) || (gold > 24 && location == 6)) // do you have enough?
    {
      if (defense > 2) // alrdy had that idiot
      {
        cout << "You bought similar armor to what you are already wearing. You try to return it but the merchant says there are no refunds. You just wasted a bunch of gold (-.-)'" << endl;
        
        if (location == 4)
        {
          gold -= 20;
        }

        if (location == 6)
        {
          gold -= 25;
        }
      }

      else // equipped the armor
      {
        armor = "Leather(3)";
        defense = 3;
        cout << "You purchased leather armor for";
        
        if (location == 4) // cheaper cost at location 4
        {
          cout << " 20 gold.";
          gold -= 20;
        }

        else if (location == 6) // cheaper cost at location 6
        {
          cout << " 25 gold.";
          gold -= 25;
        }
      }

      Continue();
    }
    else
    {
      cout << "You don't have enough gold for that";
      Continue();
    }
  }

  else if (command == "w" && (location == 4 || location == 6)) // want to buy sword
  {
    if ((gold > 19 && location == 4) || (gold > 24 && location == 6)) // 
    {
      if (attack > 4) // bought it but already had one
      {
        cout << "You bought a weapon similar to what you already have. You try to return it but the merchant says there are no refunds. That's a bunch of gold wasted" << endl;
      }

      else // bought the sword
      {
        weapon = "Sword(5)";
        attack = 5;
        cout << "You purchased a sword for";
      }  
        if (location == 4) // how much did they spend
        {
          cout << " 20 gold.";
          gold -= 20;
        }

        else if (location == 6)  // how much did they spend
        {
          cout << " 25 gold.";
          gold -= 25;
        }

      Continue();
    }

    else // cant afford it
    {
      cout << "You don't have enough gold for that";
      Continue();
    }
  }

  else if (command == "l" && location == 6) // buying longsword from town
  {
    if (gold > 39) // can afford it
    {
      weapon = "Longsword(8)";
      attack = 8;
      gold -= 40;
      cout << "The shop keep looks a little worried when you point to a 4 foot long blade in a glass case. His worries go down a bit when you put 40 gold on the counter and he hands you the sword. You feel like you could take on a bear now.";
    }

    else // cant afford it
    {
      cout << "You look longingly at the a 4 foot long sword sitting inside a glass case. Unfortunately, you can't afford it so you keep browsing.";
    }

    Continue();
  }

  else if (command == "c" && location == 6) // buying chainmail armor from town
  {
    if (gold > 39) // cant afford it
    {
      armor = "Chainmail(5)";
      gold -= 40;
      defense = 5;
      cout << "The center mannequin is wearing a nice set of chainmail armor. It looks like someone could survive a dagger to the heart while wearing it. You put 40 gold on the counter and point to the mannequin and he hands over the armor.";
    }

    else // cant afford it
    {
      cout << "There is a nice set of armor being worn by a mannequin in the center of the shop. While you would love to have it, you just can't afford it and return to browsing.";
    }

    Continue();
  }

  else if (command == "l" && location == 10) // buy longsword at final merchant
  {
    if (one23 == 1) // from expensive merchant
    {
      if (gold > 49) // can afford it
      {
        cout << "You decide to buy the longsword for 50 gold" << endl;
        
        if (attack > 7) // already had one dummy
        {
          cout << "After you buy it, you realize that your sword is already just as good and try to return it. The merchant says, \"No refunds,\" You donate it to the person behind you and continue shopping." << endl;
        }

        else // got the longsword
        {
          cout << "You equip the longsword and return to shopping" << endl;
          weapon = "Longsword(8)";
          attack = 8;
        }
        gold -= 50;
      }

      else // cant afford it
      {
        cout << "You don't have enough money for that. You return to shopping." << endl;
      }
    }

    if (one23 == 2) // from discount merchant
    {
      if (gold > 34)
      {
        cout << "You decide to buy the longsword for 35 gold" << endl;

        if (attack > 7) // already had one dummy
        {
          cout << "After you buy it, you realize that your sword is already just as good and try to return it. The merchant says, \"No refunds,\" You donate it to the person behind you and continue shopping." << endl;
        }

        else // got the longsword
        {
          cout << "You equip the longsword and return to shopping" << endl;
          weapon = "Longsword(8)";
          attack = 8;
        }
        gold -= 35;
      }
    }
  }

  else if (command == "c" && location == 10) // buy chainmail at final merchant
  {
    if (one23 == 1) // from expensive merchant
    {
      if (gold > 49) // can afford it
      {
        cout << "You decide to buy the chainmail armor for 50 gold" << endl;
        
        if (defense > 4) // already had one dummy
        {
          cout << "After you buy it, you realize that your armor is already just as good and try to return it. The merchant says, \"No refunds,\" You donate it to the person behind you and continue shopping." << endl;
        }

        else // got the chainmail armor
        {
          cout << "You equip the armor and return to shopping" << endl;
          armor = "Chainmail(5)";
          defense = 5;
        }
        gold -= 50;
      }

      else // cant afford it
      {
        cout << "You don't have enough money for that. You return to shopping." << endl;
      }
    }

    if (one23 == 2) // from discount merchant
    {
      if (gold > 34)
      {
        cout << "You decide to buy the chainmail armor for 35 gold" << endl;

        if (defense > 4) // already had one dummy
        {
          cout << "After you buy it, you realize that your armor is already just as good and try to return it. The merchant says, \"No refunds,\" You donate it to the person behind you and continue shopping." << endl;
        }

        else // got the chainmail armor
        {
          cout << "You equip the chainmail armor and return to shopping" << endl;
          armor = "Chainmail(5)";
          defense = 5;
        }
        gold -= 35;
      }
    }
  }

  else if (command == "exit") // leaving merchant
  {
    cout << "You wish the merchant luck in his ventures and continue on your journey" << endl << endl;
    if (location == 6)
    {
      cout << "You leave the shop and return to the town's main road" << endl << endl;
      town = true;
    }
    
    merchant = false;
  }

  else // not a command dummy
  {
    cout << "Invalid command" << endl;
  }
}

while (town == true) // In town
{
  cout << "In town" << endl;
  cout << "Please enter a command: ";
  cin >> command;
  getline(cin, garbage);
  cout << endl;

  if (command == "c") // repeat town commands
  {
    TownInstructions();
  }

  else if (command == "v") // check Inventory
  {
    cout << "Health : " << health;
    cout << "     Gold: " << gold;
    cout << "     Potions: " << potions << endl;
    cout << "Current Weapon: " << weapon;
    cout << "  Current Armor: " << armor << endl << endl;
  }

  else if (command == "m") // show map while in town
  {
    ShowMap(location);
  }

  else if (command == "i") // visit inn
  {
    one23 = Inn(gold);

    if (one23 == 1) // slept at inn
    {
      health = 50;
      gold -= 10;
    }
  }

  else if (command == "right") // leaving town
  {
    cout << "You head towards the town's exit to return to your path";
    Continue();
    town = false;
  }

  else if (command == "s") // goin shopping
  {
    cout << "You head to the town's general store. The sign says that he sells just about everything, but you are just concerned with the weapons, armor, and potions" << endl;
    town = false;
    merchant = true;
  }

  else
  {
    cout << "Invalid command" << endl;
  }
}
  if(town == false && merchant == false && health > 0 && outside == true) // enter a command anywhere else
  {
    cout << "Please enter a command: ";
    cin >> command;
    getline(cin, garbage);
    cout << endl;
  }

    if (command == "m") // open map
    {
      ShowMap(location);
      cout << endl;
    }

    else if (command == "i") // check Instructions
    {
      Instructions();
    }
    
    else if (command == "p") // use potion
    {
      if (potions > 0)   // dumbass..
      {
        potions--;
        if (health == 50)
        {
          cout << "You wasted a potion (face palm)" << endl;
        }

        else  // using potion
        {
          health += 10;
          if (health > 50)  // health cant go above 50
          {
            health = 50;
          }
          cout << "You drink a potion. While bitter, you feel your strength return to you" << endl;
          cout << "Current Health: " << health << endl;
        }

        cout << "Potions left: " << potions << endl << endl;
      }

      else // no potions
      {
        cout << "You have no potions left" << endl << endl;
      } 
    }  

    else if (command == "v") // check Inventory
    {
      cout << "Health : " << health;
      cout << "     Gold: " << gold;
      cout << "     Potions: " << potions << endl;
      cout << "Current Armor: " << armor;
      cout << "  Current Weapon: " << weapon << endl << endl;
    }
    // Road Random Event
    else if ((command == "right" && (location == 1 
    || location == 2 || location == 6 || location == 8)) || ((command == "up" || command == "right") && location == 9) || ((command == "down" || command == "right") && location == 7))
    {
      ranNum = (rand() % 10);
      if (location == 1 || location == 2) // road 1 or 2
      {
        if (location == 1) // move to location 2
        {
          location = 2;
        }
        else // move to location 4
        {
          location = 4;
        }

        if (ranNum < 3)  // nothing happened
        {
          cout << "You walk down the main road. As you walk, you pass by a couple people but none speak to you and you reach the next path in an uneventful fashion";
          Continue();
        }

        else if (ranNum < 6) // easy thief
        {
          enemy = "Thief";
          enemyHP = 9;
          enemyAttack = 6;
          cout << "As you walk down the road, you hear some rustling from a nearby bush. You pause and look in the direction but see nothing. As you continue walking, a man wearing a hood and bandana, knife in hand, jumps out from the bush behind you. Before you can respond, he puts the knife to your throat and demands your valuables. As luck would have it, the wind causes a nearby branch to hit the ground startling the hooded man giving you time to distance yourself from him. You prepare to fight.";
          Continue();
          battle = true;
        }

        else if (ranNum < 9) // easy wolf
        {
          enemy = "Wolf";
          enemyHP = 10;
          enemyAttack = 5;
          cout << "As you are walking down the road, you hear a scream come from just off the road to your left. You decide to investiage and come to a clearing. You see a dead man with a hole in his throat. Just beside the body is a wolf guarding his recent kill. While you did not know this man, no one deserves to have their corpse mangled and you prepare to fight the wolf.";
          Continue();
          battle = true;
        }

        else if (ranNum == 9 && location == 2) // potion merchant event
        {
          cout << "As you walk down the road, a man driving a horse drawn wagon comes into view. When he gets closer, he gestures you over to the wagon. He explains that he is a merchant trying to switch from a potion selling business to a weapon selling business so he is unloading his poitons at half price." << endl;
          cout << "Would you like to shop? ('y' to shop / anything else to leave): ";
          cin >> command;
          getline(cin, garbage);

          if (command == "y") // open merchant
          {
            merchant = true;
          }

          else // back to outside
          {
            cout << "You decline and contine on your journey" << endl;
          }
        }

          else if (ranNum == 9 && location == 4) // arms merchant event
        {
          cout << "As you walk down the road, you see a wagon come up behind you. When the wagon comes along side you, the driver slows down to your walking pace. As you are walking, he explains that he is a merchant planning to open a store for 'cheap yet effective' arms and armor in the coming town and asks if you would like to see his wears." << endl;
          cout << "Would you like to shop? ('y' to shop / anything else to leave): ";
          cin >> command;
          getline(cin, garbage);

          if (command == "y") // open merchant
          {
            merchant = true;
          }

          else // back to outside
          {
            cout << "You decline and contine on your journey" << endl;
          }
        }
      }

      else if (location == 6)
      {
        location = 8;
        if (ranNum < 3) // nothing happened
        {
          cout << "You walk down the main road. As you walk, you pass by a couple people but none speak to you and you reach the next path in an uneventful fashion";
          Continue();
        }

        else if (ranNum < 6) // hard theif
        {
          enemy = "Thief";
          enemyHP = 20;
          enemyAttack = 9;
          cout << "As you walk down the road, you see a man standing on the road. His face is covered and he is wearing all black. You assume he is a thief, but any smart thief would try to jump you, not stand on the side of the road where anyone can see them. He steps in front of you and demands your valuables. You see now why he didn't bother hiding. He is very well built and weilding an expensive looking blade. He plans to use his brawn rather than surprise to take you down. He won't find you easy to take down, time to fight.";
          Continue();
          battle = true;
        }

        else if (ranNum < 9) // hard wolf
        {
          enemy = "Wolf";
          enemyHP = 25;
          enemyAttack = 8;
          cout << "You are walking peacefully down the main road. The breeze is pleasant and you feel a sense of serenity. Just as you let your mind wander, you hear a growling sound from the nearby forest. Just as you are coming to your senses a large wolf jumps out from between some trees and knocks you off your feet. You pull yourself together and look at your opponent. This is one of the largest wolves you've ever seen. You ready yourself for a fairly hard fight.";
          Continue();
          battle = true;
        }

        else // legendary sword
        {
          cout << "You are walking down the fairly well kept road, and you see an old man approach you. He claims to be a famous adventurer who has fought in many famous battles. Since you came from a secluded village, there's no way to know if he's telling the truth or not. He says that after his long career, he is looking to retire and asks if you want to buy his sword for 50 gold. He brings it out and you can tell it is of extremely high quality (12 damage)." << endl;
          cout << "Would you like to buy it? ('y' to buy / anything else to leave):";
          cin >> command;
          getline(cin, garbage);

          if (command == "y" && gold > 49) // got the best sword in the game
          {
            weapon = "Mithril Blade(12)";
            attack = 12;
            gold -= 50;
            cout << "You fork over the cash and drink in the sword's lovely blue and purple sheen. You can tell it is probably the nicest weapon in the region. Luckily you had the money to buy it. You return to your journey.";
            Continue();
          }

          else if (command == "y") // should of saved ur money
          {
            cout << "You quickly pull out your gold in excitement, only to realize you don't have that much on you. You smile awkwardly and decline his offer before resuming your journey.";
            Continue();
          }

          else // idiot didnt buy it
          {
            cout << "As beautiful as the sword looks, you decide you do not need such an item. You politely decline his offer and return to your trek.";
            Continue();
          }
        }
      }

      else if (location == 8 || location == 7 || location == 9) // final merchants
      {
        cout << "You approach a clearing that appears to be a meeting place of some kind. ";
        location = 10;
        if (ranNum < 2) // unlucky..
        {
          cout << "There is a nice looking firepit, a bunch of horse and carriage tracks, and remnats of tents and other camping equipment. However, no one is around, the firepit is not lit, and you can't sense any signs of a person's presence. I guess you are just missed the party. You continue down the road.";
          Continue();
        }

        else if (ranNum < 9) // merchants
        {
          cout << "There is a large group people, horse, carriages, and all kinds of camping equipment scattered around the area. It looks to be a meeting place for people looking to buy or sell things. ";
          if (ranNum < 6) // expensive merchant
          {
            cout << "You see a crowd of people gathering around a large tent that appears to be set up as an equipment vendor. You hear murmurings of some people complaining that his prices are a bit unreasonable, but his goods look to be of nice quality. You decide to take a look at his wears before continuing on.";
            Continue();
            one23 = 1;
          }

          else // discount merchant
          {
            cout << "A group of people have gathered by a small tent set up by a carriage that appears to be loaded with goods. You hear some conversations that the owner of the carriage seems to be having a sale, which has everyone clambering to buy something. You decide to get in line to see what he has for sale. After about 30 minutes of waiting, you finally get to the front of the line to see what's for sale.";
            Continue();
            one23 = 2;
          }

          merchant = true;
        }

        else // legendary armor
        {
          cout << "There is an old man sitting alone on a blanket near the edge of the field. A couple people are looking at him, but no one approaches. You hear a few distant conversations, \"It has to be fake\" or \"It's too ordinary looking to be real.\" You approach the man and ask what he is selling. He points to a plain looking iron chest piece and says it's magical chest armor from his adventure days. The price is 50 gold" << endl;
          cout << "Do you want to buy it? ('y' for yes / anything else to leave)";
          cin >> command;
          getline(cin, garbage);

          if (command == "y" && gold > 49) // got the best armor in the game
          {
            cout << endl << "While weary of its authenticity, you decide it's worth the risk and shell out the 50 gold for it. You put it on and return the main road.";
            armor = "Magical Iron Armor(7)";
            defense = 7;
            Continue();
          }

          else if (command == "y") // should of saved ur money
          {
            cout << endl << "You take out your gold satchel to buy it, only to realize you don't have enough for it. You smile and politely decline before returning to the main road.";
            Continue();
          }

          else // idiot didnt buy it
          {
            cout << endl << "Thinking that it must be a scam, you choose not to buy it and return to the main road.";
            Continue();
          }
        }
      }
    }

    else if (command == "right" && location == 10) // Final boss
    {
      cout << "As you walk down the road, you hear a loud roar in the distance. Curious, you start walking in that direction. You walk for 15 minutes into what seems like a barren wasteland. Disappointed, you are about to turn around when you hear the noise again. This time its much louder and is coming from a shallow looking cave. You peek inside and see what appears to be a large wingless black dragon. This is the kind of opponent that would bring you great prestige within your village. You walk into the cave and the great beast turns to face you. This is it your final battle.";
      Continue();
      enemy = "Black Drake";
      enemyHP = 50;
      enemyAttack = 13;
      battle = true;
    }

    // In Town
    else if (((command == "right" || command == "down") && location == 3)
     || (command == "right" && location == 4)
     || ((command == "right" || command == "up") && location == 5))
    {
      location = 6; // moving to town location
      cout << "You come to a fairly large town. It seems to be a peaceful place. You doubt that anything dangerous will happen here, so you relax and look around at what the town has to offer";
      TownInstructions();
      town = true;
    }
    // Forest event
    else if ((command == "up" && location == 2) || (command == "down" && location == 6))
    {
      if (location == 2) // moving to location 3
      {
        location = 3;
      }
      if (location == 6) // moving to location 9
      {
        location = 9;
      }

      Forest(enemy, enemyHP, enemyAttack, location);
      battle = true;
    }
    // Cave event
    else if ((command == "down" && location == 2) || (command == "up" && location == 6))
    {
      if (location == 2) // moving to location 5
      {
        location = 5;
      }
      if (location == 6) // moving to location 7
      {
        location = 7;
      }

      Cave(enemy, enemyHP, enemyAttack, location);
      battle = true;
    }

    else if (health > 0)// not a command dummy
    {
      cout << "Invalid direction or command" << endl;
    }

  if (health < 1) // you dead
  {
    cout << "You died and became just another one of the many in your village who never returned from their journey";
    outside = false;
  }
}

  return 0;
}

void Instructions() // Show Instructions
{
  cout << "                           Instructions" << endl << endl;
  cout << "                          Outside Combat" << endl << endl;
  cout << "                   Move on map - up, down, right" << endl;
  cout << "             Open Map - 'm'  Restate Instructions - 'i'" << endl;
  cout << "               Use Potion - 'p'  Check Inventory - 'v'" << endl << endl;
  cout << "                           Inside Combat" << endl << endl;
  cout << "                     'attack' 'check' 'defend'" << endl << endl;
  cout << "                        (potions heal 10 HP)" << endl;
  cout << "                    (check does not use a turn)" << endl;
  cout << "                   (commands must be lower case)" << endl;
  cout << "         (the number next weapon/armor is its attack/defense)";
  cout << endl << endl;
}
// ********Random forest events*********
void Forest(string& enemy, int& enemyHP, int& enemyAttack, int progress)
{
  int ranNum = 0;
  ranNum = (rand() % 10);
  cout << "You enter large forest. Even though it is daytime the trees eclipse nearly all sunlight. You follow the small dirt path as quickly as you can.";
  Continue();
  if (progress < 6) // easy forest enemy
  {
    if (ranNum < 5) // forest thief encounter
    {
      cout << "As you are walking, you run into a hooded man dressed in black. His eyes are the only thing visible in the darkness and even before he speaks, they tell you his intentions are not friendly. He pulls out a knife and demands any valuables you may be carrying. You prepare to fight.";
      Continue();
      enemy = "Thief";
      enemyHP = 9;
      enemyAttack = 6;
    }
    
    else if (ranNum < 8) // forest goblin encounter
    {
      cout << "While trying to not lose your bearings, you see a small figure ahead of you. As you sneak closer, its green skin tells you it is a goblin. You have never seen a goblin outside during the day, you figure it got lost and took refuge from the sun inside this forest. As you are attempting the sneak by the creature, you hear a loud snap as your foot steps on a branch. The startled creature charges you and you have no choice but to fight.";
      Continue();
      enemy = "Goblin";
      enemyHP = 11;
      enemyAttack = 4;
    }
    else // forest tre-ent encounter
    {
      cout << "You walk for awhile with nothing eventful happening. You look ahead and see sunlight in the distance, it seems your walk through the forest is almost over. Before you continue, you take a quick break and rest on a nearby tree. Just as you start to relax, the tree starts moving. Startled, you jump up and back away from the tree only to see that the tree is moving! You have read about trees like this in books before, tre-ents they are call, but no one you know had ever seen one. The tre-ent considers you an invader of the forest and attacks.";
      Continue();
      enemy = "Tre-ent";
      enemyHP = 20;
      enemyAttack = 7;
    }
  }
  else // hard forest enemy
  {
    if (ranNum < 5) // forest thief encounter
    {
      cout << "The darkness of the forest is a bit overbearing. You consider lighting a torch since it almost feels like you are in a cave. A torch however would just make you more of a target for anything watching. Despite your resolve in not lighting a torch, a man in black comes out from behind some trees. He doesn't even care about the element of surprise as he just walks up to you and demands everything on you. He doesn't look like your average hooligan. He is wearing solid looking armor and brandishing a well kept blade. Seems like a difficult fight is ahead.";
      Continue();
      enemy = "Thief";
      enemyHP = 20;
      enemyAttack = 9;
    }

    else if (ranNum < 8) // forest goblin encounter
    {
      cout << "As you are walking, you hear a skulking sound up ahead. You approach the sound as quietly as you can, maybe for once you will get the drop on something. You see a goblin up ahead, it is larger than usual but looks ordinary otherwise. You approach it from behind, and just when you are about to strike, you trip over a rock in the darkness. So much for surprise, the goblin lunges toward you.";
      Continue();
      enemy = "Goblin";
      enemyHP = 28;
      enemyAttack = 7;
    }

    else // Tre-ent encounter
    {
      cout << "The trees in this forest are much larger than normal. As you walk, some trees seem to move in unnatural ways. The wind blows one direction, and the branches sway the other. You ignore it, figuring your eyes are playing tricks on you in the dark. Pressing forward, you see a tree's trunk rotate a few degrees. Okay, maybe you aren't seeing things. Some tre-ents must be watching you. You continue forward, putting your guard up, but hoping they will let you pass. However, a few seconds later, a tree arm drops in front of you. A large tre-ent decides not to let you pass. You have no choice but to fight.";
      Continue();
      enemy = "Tre-ent";
      enemyHP = 35;
      enemyAttack = 11;
    }
  }
}
// *********random Cave events***********
void Cave(string& enemy, int& enemyHP, int& enemyAttack, int progress)
{
  int ranNum = 0;
  ranNum = (rand() % 10);
  cout << "You come to a dark cave. While the look of it might scare a less prepared traveller off, you know from looking at your map that the cave has an exit and you will not be deterred from your quest. You take the thickest branch you can find to use as a torch and walk inside";
  Continue();
  if (progress < 6) // easy enemy
  {
    if (ranNum < 3) // wolf encounter
    {
      cout << "The darkness of the cave makes it difficult to navigate. As you are trying to keep your bearings, you hear a snarling sound coming from your right. As you turn, you see nothing in the darkness but a pair of glowing eyes. It seems like this section of the cave was claimed by a wolf pack. Luckily, it looks like the rest of the pack isn't here. You get ready to fight.";
      Continue();
      enemy = "Wolf";
      enemyHP = 10;
      enemyAttack = 5;
    }

    else if (ranNum < 7) // goblin encounter
    {
      cout << "You walk for awhile and are surprised you havn't ran into any goblins. You read that, any time there was a secluded cave, a goblin had found a home. You look ahead and see the actual light at the end of the tunnel. As you breathe a sign of relief for making it out of the cave without any trouble, a goblin lunges at you from the darkness. You barely manage to dodge a lethal blow and prepare to defend youself.";
      Continue();
      enemy = "Goblin";
      enemyHP = 11;
      enemyAttack = 4;
    }
    
    else // armored goblin encounter
    {
      cout << "The cave gives you a slight sense of dread. You know that goblins often dwell in caves, but you feel you can handle a simple goblin or two. After all, goblins can barely use crude weapons much less modern arms and armor. As your thoughts relieve some of your fears, you see a shiny figure in the distance. You figure it's a fellow traveller and go up to greet them. When you get closer, the figure turns and you see its a goblin wearing armor! This goblin must of somehow killed a soldier and took his armor. Your in for a hard fight.";
      Continue();
      enemy = "Armored Goblin";
      enemyHP = 24;
      enemyAttack = 6;
    }
  }

  else // hard enemy
  {
    if (ranNum < 3) // wolf encounter
    {
      cout << "As you walk through the cave, you see four pairs of glowing eyes stare at you in the darkness. Six of the eyes either flee or withdraw further into the cave. The last pair slowly walks into the range of your torch's light. He is a very large wolf, clearly the leader of the pack. He stares at you and you can't tell if he sees you as food or a challenge of dominance over the cave. Either way a fight is inevitable.";
      Continue();
      enemyHP = 25;
      enemyAttack = 8;
    }

    else if (ranNum < 7) // goblin encounter
    {
      cout << "While walking through the cave, you see a few human corpses. Some of them look fairly old, others more recent. As you walk, a goblin comes into sight. Normally a single goblin isn't a match for an adult human, but this one looks different. While not much larger than most, its eyes give a feeling of bloodlust. Around its neck is a necklace of human skulls. These are probably from the corpses you saw earlier. This goblin should not be treated lightly. You prepare to fight.";
      Continue();
      enemy = "Goblin";
      enemyHP = 28;
      enemyAttack = 7;
    }

    else // armored goblin encounter
    {
      cout << "The light of your torch only illuminates an area about 5 meters around you. This cave is fairly large, with the corridor being about 15 meters wide. There could be anything near the cave walls and you wouldn't even know it. As you walk, you hear a clanging sound up ahead. The sound gets louder and louder as you walk. If it weren't for the exit being in this direction you would of ran the other way, but you are forced to move on. You finally see what is making all the noise. It is a large goblin wearing impressive looking armor. You have never seen a goblin this large. As soon as you lock eyes with the creature it charges towards you.";
      Continue();
      enemy = "Armored Goblin";
      enemyHP = 40;
      enemyAttack = 10;
    }
  }
}

void TownInstructions() // show town exclusive commands
{
  cout << endl << endl;
  cout << "              -Town Commands-" << endl << endl;
  cout << "Inn - 'i'  Check inventory - 'v'  Store - 's'" << endl;
  cout << "     Map - 'm'     Repeat commands - 'c'" << endl;
  cout << "        (Enter 'right' to leave town)" << endl << endl;
}

int Inn(int gold) // visiting inn function
{
  bool inn = true;
  string command = " ";
  string garbage = " ";
  int num = 0; // did they stay?
  while (inn == true) // still hanging out at the inn
  {
    cout << "You walk to the local Inn. After entering the door, the innkeeper greets you and asks if you would like a room (full heal). You ask him what the daily rate is and he says \"it is 10 gold per day\"." << endl;
    cout << endl << "Current gold: " << gold << endl;
    cout << "Would you like to rest here? (y / n): ";
    cin >> command;
    getline(cin, garbage);

    if (command == "n") // no they didnt
    {
      cout << "You decline and return to the town's main road";
      Continue();
      inn = false;
      num = 0;
    }

    else if (command == "y") // yes they did
    {
      if (gold > 9) // slept at inn
      {
        cout << "You pay the 10 gold and stay the night. This is the first time you have slept in a real bed or a safe place since you left on your journey. You sleep very soundly (health healed to full).";
        Continue();
        inn = false;
        num = 1;
      }

      else // cant afford it
      {
        cout << "You are about to say yes, but you realize that you don't have enough money to get a room. You politely decline and return to the town's main road";
        Continue();
        inn = false;
        num = 0;
      }
    }

    else // not a command dummy
    {
      cout << "Invalid command" << endl;
    }
  }

  return num;
}

void Continue()
{
  string garbage = " ";
  cout << endl << red << "(press enter to continue)" << normal << endl;
  getline(cin, garbage);
}
