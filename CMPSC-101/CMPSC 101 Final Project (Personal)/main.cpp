// Zachary Newman
// Works cited:
/*
- Game map drawing and array code based on:
  https://replit.com/@cminich/101-Spring-2021-Maze-1#main.cpp

- Emoji values found using Unicode.org in:
  https://unicode.org/emoji/charts-13.0/full-emoji-list.html

- Decimal precision code written by Professor Minich adapted from:
  https://replit.com/@cminich/101-setf-rounding

- Colored Text code written by Professor Minich adapted from:
  https://replit.com/@cminich/101-colorful-text
*/
#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <fstream>
using namespace std;

// ---- GLOBAL CONSTANTS ----
const int ROWS = 10; // Number of rows in the map
const int COLUMNS = 20; // Number of coloumns in the map
const int MAP_AMOUNT = 12; // Number of different maps that can be generated.
const double STAT_INCREASE = 0.05; // Amount that stats increase in the shop.
const int SHOP_PRICE = 5; // XP cost of items in shop
const string T = "\U0001F332"; // "\U0001F332" Tree
const string P = "\U00000D9E "; // "\U0001F920" Cowboy hat face (Player) (Among Us currently)
const string F = "  "; // Floor
const string E = "\U0001F573 "; // "\U0001F573" Hole (Ending)
const string A = "\U0001F400"; // "\U0001F400" Rat (Monster 1)
const string B = "\U0001F426"; // "\U0001F426" Bird (Monster 2)
const string C = "\U0001F422"; // "\U0001F422" Turtle (Monster 3)
const string S = "\U0001F3D5"; // "\U0001F3D5" Campsite (Shop)
const string L = "\U0001F4B0"; // "\U0001F4B0" Money Bag(XP loot)
const string RED = "\33[31m"; // Sets the color of the text to red.
const string BLUE = "\33[34m"; // Sets the color of the text to blue.
const string YELLOW = "\33[33m"; // Sets the color of the text to yellow.
const string GREEN = "\33[32m"; // Sets the color of the text to green.
const string RESET_COLOR = "\33[0m"; //Reset the color to the default

const bool DEBUG_MODE = false; // Changes whether the console clears after one interation of the main game loop.
const bool TEST_MAP_MODE = false; //Changes where the map that gets generated is a random one from a list or TestMap.map

// ---- GLOBAL VARIABLES ----
bool isValidMovement = false; // True when the input movement command is valid 
bool isLastMoveValid = true; // True if the last input movement command was valid.
string gameMap[ROWS][COLUMNS]; // Stores the game map
int mapLocations[MAP_AMOUNT][4][2]
// Entity locations:       
// Player Mon1  Mon2  Mon3 | Map Name:
{
  {{1,1},{4,5},{2,6},{6,16}},   // Map0
  {{1,1},{8,1},{1,10},{4,18}},  // Map1
  {{8,1},{1,4},{1,10},{8,17}},  // Map2
  {{8,1},{1,1},{8,18},{5,4}},   // Map3
  {{1,1},{7,3},{2,9},{5,18}},   // Map4
  {{1,1},{7,5},{4,9},{8,18}},   // Map5
  {{2,2},{7,8},{3,17},{7,12}},  // Map6
  {{5,9},{2,3},{1,16},{5,18}},  // Map7
  {{7,9},{7,2},{3,17},{1,10}},  // Map8
  {{1,3},{7,3},{8,18},{1,18}},  // Map9
  {{4,6},{0,0},{0,0},{0,0}},    // MapShop
  {{1,2},{2,6},{2,10},{2,14}},  // TestMap
};

// ---- FUNCTION DECLARATIONS ----

void displayMap();
  // outputs the data in gameMap.

int determineMoveType(int endRow, int endCol); 
  // determines what the type of move the attempted action is.

void movePlayer(int startRow, int startCol, int endRow, int endCol, int moveType); 
  // uses the move type to either move the player character or do something else (FIX_ME reimplement as multiple functions based on moveType)

void clearConsole(); 
  //Removes all outputs and inputs from the console

int generateMap(int floor, int lastMap); 
  // Inputs the values for the 2d array gameMap[][] from a file and outputs the map number.

void displayStats(double health, double maxHealth, double strength, double dexterity, double intelligence, double experience); 
  // Displays all of the players stats in the same line.

void displayShopMenu(); // Displays the shop menu

bool hitCheck(double attackDex, double targetDex); 
  // Determines if an attack made against a target is successful

double calculateDamage(int dieSize, double strength); 
  // Determines how much damage is dealt to the target.

double generateXP(int range, int lower);
  // Determines how much XP is gained from an action.

void displayTitleScreen(); // displays the opening title and the opening monologue

double selectDifficulty(); // used to determine the difficulty mod

// ---- MAIN PROGRAM ----
int main() 
{
  // -- LOCAL VARIABLES --
  bool isGameOver = false; // True when the game is over.
  int floorNum = 1; // Current Floor Number.
  int mapNum = 0; // Current Numeric Map reference.
  bool hasReachedEnd = false; // True when player reaches the ending tile.
  string specialOutput = ""; // Used for xp gain and damage numbers.
  double lootNum = 0.0; // Temporarily stores the XP gained.
  double tempDamage = 0.0; // Temporarily stores the damage dealt.
  double difficultyMod = 0; // Difficulty modifier to multiple monster stats.

  // - Player Variables -
  string playerMove = ""; // Movement Key Pressed.
  int playerRow = 0; // Current Player Row.
  int playerEndingRow = 0; // Row the player the is moving to.
  int playerCol = 0; // Current Player Column.
  int playerEndingCol = 0; // Column the player is moving to.
  int moveType = 0; // Whether the direction of movement is free or occupied.
  double playerMaxHP = 15.0; // Player's Max Health.
  double playerHP = playerMaxHP; // Player's Current Health.
  double playerStr = 1.0; // Player's Strength Modifier.
  double playerDex = 1.0; // Player's Dexterity Modifier.
  double playerInt = 1.0; // Player's Intelligence Modifier.
  double playerXP = 0.0; // Player's Current Experience.
  int playerDiceSize = 6; // Number of "faces" on the player's damage dice.

  // - Monster Variables -
  int monsterDice = 4; // Monster's Damage Dice.
  // Monster A/1 :
  int monOneRow = 0; // Current Monster 1 Row.
  int monOneCol = 0; // Current Monster 1 Column.
  double monOneMaxHP = 5.0; // Maximum Monster 1 HP.
  double monOneHP = monOneMaxHP; // Current Monster 1 HP.
  double monOneStr = 0.9; // Monster 1's Strength Modifier.
  double monOneDex = 0.8; // Monster 1's Dexterity Modifier.
  // Monster B/2 :
  int monTwoRow = 0; // Current Monster 2 Row.
  int monTwoCol = 0; // Current Monster 2 Column.
  double monTwoMaxHP = 5.0; // Maximum Monster 2 HP.
  double monTwoHP = monTwoMaxHP; // Current Monster 2 HP.
  double monTwoStr = 0.8; // Monster 2's Strength Modifier.
  double monTwoDex = 0.9; // Monster 2's Dexterity Modifier.
  // Monster C/3 :
  int monThreeRow = 0; // Current Monster 3 Row.
  int monThreeCol = 0; // Current Monster 3 Column.
  double monThreeMaxHP = 6.0; // Maximum Monster 3 HP.
  double monThreeHP = monThreeMaxHP; // Current Monster 3 HP.
  double monThreeStr = 0.8; // Monster 3's Strength Modifier.
  double monThreeDex = 0.8; // Monster 3's Dexterity Modifier.

  // -- INITIAL SETUP -- 
  srand(time(0));
  displayTitleScreen(); // Displays title screen
  cout << "Enter anything to continue: ";
  cin >> playerMove;
  difficultyMod = selectDifficulty(); // Difficulty selection
  clearConsole();
  mapNum = generateMap(floorNum, mapNum); // Initial map generation
  // Player Position:
  playerRow = mapLocations[mapNum][0][0];
  playerCol = mapLocations[mapNum][0][1];
  // Monster 1 Position:
  monOneRow = mapLocations[mapNum][1][0];
  monOneCol = mapLocations[mapNum][1][1];
  // Monster 2 Position:
  monTwoRow = mapLocations[mapNum][2][0];
  monTwoCol = mapLocations[mapNum][2][1];
  // Monster 3 Position:
  monThreeRow = mapLocations[mapNum][3][0];
  monThreeCol = mapLocations[mapNum][3][1];

  clearConsole(); //Clears the console of all outputs/inputs.
  cout << "Floor: " << floorNum << endl; // Displays floor number
  displayMap(); // Outputs the map to the console.

  // ---- MAIN GAME LOOP ----
  while(!isGameOver)
  {
    if(hasReachedEnd) //If the player reaches the end of the floor, it generates a new mape and keeps going.
    {
      clearConsole(); //Clears the console of all outputs/inputs.
      cout << "New Floor Reached." << endl;
      floorNum++;
      mapNum = generateMap(floorNum, mapNum); // Initial map generation
      // Player Position:
      playerRow = mapLocations[mapNum][0][0];
      playerCol = mapLocations[mapNum][0][1];
      playerHP = playerMaxHP;
      // Monster 1 Position:
      monOneRow = mapLocations[mapNum][1][0];
      monOneCol = mapLocations[mapNum][1][1];
      // Monster 2 Position:
      monTwoRow = mapLocations[mapNum][2][0];
      monTwoCol = mapLocations[mapNum][2][1];
      // Monster 3 Position:
      monThreeRow = mapLocations[mapNum][3][0];
      monThreeCol = mapLocations[mapNum][3][1];
      // Resetting Monster Health
      monOneHP = monOneMaxHP;
      monTwoHP = monTwoMaxHP;
      monThreeHP = monThreeMaxHP;
      if ((floorNum % 5) == 0)
      {
        // Monster 1 stat increase:
        monOneMaxHP = monOneMaxHP * difficultyMod;
        monOneStr = monOneStr * difficultyMod;
        monOneDex = monOneDex * difficultyMod;
        // Monster 2 stat increase:
        monTwoMaxHP = monTwoMaxHP * difficultyMod;
        monTwoStr = monTwoStr * difficultyMod;
        monTwoDex = monTwoDex * difficultyMod;
        // Monster 3 stat increase:
        monThreeMaxHP = monThreeMaxHP * difficultyMod;
        monThreeStr = monThreeStr * difficultyMod;
        monThreeDex = monThreeDex * difficultyMod;
        if (!TEST_MAP_MODE)
        {
          // Health set to zero for shop
          monOneHP = 0;
          monTwoHP = 0;
          monThreeHP = 0;
        }
      }
      cout << "Floor: " << floorNum << endl;
      displayMap(); // Outputs the map to the console.
      hasReachedEnd = false;
    }
    displayStats(playerHP, playerMaxHP, playerStr, playerDex, playerInt, playerXP);
    cout << "w - Up | a - Left | s - Down | d - Right | q - Quit" << endl;
    cout << "Input a movement direction: ";
    cin >> playerMove;
    
    while(!isValidMovement) //Player Input Handler
    {
      if(!isLastMoveValid)
      {
        clearConsole(); //Clears the console of all outputs/inputs.
        cout << "Floor: " << floorNum << endl;
        displayMap();
        displayStats(playerHP, playerMaxHP, playerStr, playerDex, playerInt, playerXP);
        cout << "w - Up | a - Left | s - Down | d - Right | q - Quit" << endl;
        cout << "Input a " << RED << "VALID" << RESET_COLOR << " movement direction: ";
        cin >> playerMove;
      }
      if (playerMove == "q")
      {
        moveType = -1;
        isGameOver = true;
      }
      else if (playerMove == "w")
      {
        playerEndingRow = playerRow - 1;
        playerEndingCol = playerCol;
        moveType = determineMoveType(playerEndingRow, playerEndingCol);
      }
      else if (playerMove == "a")
      {
        playerEndingRow = playerRow;
        playerEndingCol = playerCol - 1;
        moveType = determineMoveType(playerEndingRow, playerEndingCol);
      }
      else if (playerMove == "s")
      {
        playerEndingRow = playerRow + 1;
        playerEndingCol = playerCol;
        moveType = determineMoveType(playerEndingRow, playerEndingCol);
      }
      else if (playerMove == "d")
      {
        playerEndingRow = playerRow;
        playerEndingCol = playerCol + 1;
        moveType = determineMoveType(playerEndingRow, playerEndingCol);
      }
      else // player enters an invalid input
      {
        isLastMoveValid = false;
        continue;
      }
      movePlayer(playerRow, playerCol, playerEndingRow, playerEndingCol, moveType); // Moves player if targeting floor
    } //End of Player Input Handler
    isValidMovement = false; 
    
    if (moveType == 2) // Moves player position if targeting floor
    {
      playerRow = playerEndingRow;
      playerCol = playerEndingCol;
    }
    else if (moveType == 1 && (monOneHP <= 0 && monTwoHP <= 0 && monThreeHP <= 0))
    {
      // If the player reaches the end of the floor, and the monsters are dead, restart the main game loop so you can continue on a new floor.
      hasReachedEnd = true;
      continue;
    }
    else if (moveType == 8) // Loot Handler
    {
      lootNum = (generateXP(10,5) * playerInt);
      playerXP += lootNum;
      gameMap[playerEndingRow][playerEndingCol] = F;
      specialOutput = "You have gained " + GREEN + to_string(lootNum) + RESET_COLOR + " Experience. \n";
    }
    else if (moveType == 7) // Shop System
    {
      while (playerMove != "q")
      {
        clearConsole();
        displayShopMenu();
        cout << "Current Player Stats:" << endl;
        displayStats(playerHP, playerMaxHP, playerStr, playerDex, playerInt, playerXP);
        cout << RED << specialOutput << RESET_COLOR;
        specialOutput = "";
        cout << "Input the stat name to upgrade it, or type \"q\" to exit:";
        cin >> playerMove;
        if (playerMove == "Health" || playerMove == "health" || playerMove == "HP" || playerMove == "hp" || playerMove == "h")
        {
          if (playerXP >= (2 * SHOP_PRICE))
          {
            playerMaxHP += 1;
            playerHP += 1;
            playerXP -= (2 * SHOP_PRICE);
          }
          else
          {
            specialOutput = "Insufficient Funds.\n";
          }
        }
        else if (playerMove == "Strength" || playerMove == "strength" || playerMove == "Str" || playerMove == "str" || playerMove == "s")
        {
          if (playerXP >= SHOP_PRICE)
          {
            playerStr += STAT_INCREASE;
            playerXP -= SHOP_PRICE;
          }
          else
          {
            specialOutput = "Insufficient Funds.\n";
          }
        }
        else if (playerMove == "Dexterity" || playerMove == "dexterity" || playerMove == "Dex" || playerMove == "dex" || playerMove == "d")
        {
          if (playerXP >= SHOP_PRICE)
          {
            playerDex += STAT_INCREASE;
            playerXP -= SHOP_PRICE;
          }
          else
          {
            specialOutput = "Insufficient Funds.\n";
          }
        }
        else if (playerMove == "Intelligence" || playerMove == "intelligence" || playerMove == "Int" || playerMove == "int" || playerMove == "i")
        {
          if (playerXP >= SHOP_PRICE)
          {
            playerInt += STAT_INCREASE;
            playerXP -= SHOP_PRICE;
          }
          else
          {
            specialOutput = "Insufficient Funds.\n";
          }
        }
        else
        {
          specialOutput = "Invalid Input.\n";
        }
      }
      specialOutput = "";
    } // end of shop system
    else if (moveType == 3) // Attack monster 1
    {
      if (hitCheck(playerDex, monOneDex))
      {
        tempDamage = calculateDamage(playerDiceSize, playerStr);
        monOneHP -= tempDamage;
        specialOutput = "You have dealt " + RED + to_string((tempDamage)) + RESET_COLOR + " damage.\n";
      }
      else {
        specialOutput = "You missed.\n";
      }
      if (monOneHP <= 0)
      {
        lootNum = (generateXP(10,5) * playerInt);
        playerXP += lootNum;
        gameMap[monOneRow][monOneCol] = F;
        specialOutput += "You have gained " + GREEN + to_string(lootNum) + RESET_COLOR + " Experience. \n";
      }
    } // End of attack monster 1
    else if (moveType == 4) // Attack monster 2
    {
      if (hitCheck(playerDex, monTwoDex))
      {
        tempDamage = calculateDamage(playerDiceSize, playerStr);
        monTwoHP -= tempDamage;
        specialOutput = "You have dealt " + RED + to_string((tempDamage)) + RESET_COLOR + " damage.\n";
      }
      else {
        specialOutput = "You missed.\n";
      }
      if (monTwoHP <= 0)
      {
        lootNum = (generateXP(10,5) * playerInt);
        playerXP += lootNum;
        gameMap[monTwoRow][monTwoCol] = F;
        specialOutput += "You have gained " + GREEN + to_string(lootNum) + RESET_COLOR + " Experience. \n";
      }
    } // End of attack monster 2
    else if (moveType == 5) // Attack monster 3
    {
      if (hitCheck(playerDex, monThreeDex))
      {
        tempDamage = calculateDamage(playerDiceSize, playerStr);
        monThreeHP -= tempDamage;
        specialOutput = "You have dealt " + RED + to_string((tempDamage)) + RESET_COLOR + " damage.\n";
      }
      else {
        specialOutput = "You missed.\n";
      }
      if (monThreeHP <= 0)
      {
        lootNum = (generateXP(10,5) * playerInt);
        playerXP += lootNum;
        gameMap[monThreeRow][monThreeCol] = F;
        specialOutput += "You have gained " + GREEN + to_string(lootNum) + RESET_COLOR + " Experience. \n";
      }
    } // End of attack monster 3

    // monster 1 AI:
    if (monOneHP > 0)
    {
      if (gameMap[monOneRow-1][monOneCol] == P) // attack up
      {
        if (hitCheck(monOneDex, playerDex))
        {
          tempDamage = calculateDamage(monsterDice, monOneStr);
          playerHP -= tempDamage;
          specialOutput += "Monster 1 dealt " + RED + to_string((tempDamage)) + RESET_COLOR + " damage.\n";
        }
        else {
          specialOutput += "Monster 1 missed.\n";
        }
      }
      else if (gameMap[monOneRow][monOneCol-1] == P) // attack left
      {
        if (hitCheck(monOneDex, playerDex))
        {
          tempDamage = calculateDamage(monsterDice, monOneStr);
          playerHP -= tempDamage;
          specialOutput += "Monster 1 dealt " + RED + to_string((tempDamage)) + RESET_COLOR + " damage.\n";
        }
        else {
          specialOutput += "Monster 1 missed.\n";
        }
      }
      else if (gameMap[monOneRow+1][monOneCol] == P) // attack down
      {
        if (hitCheck(monOneDex, playerDex))
        {
          tempDamage = calculateDamage(monsterDice, monOneStr);
          playerHP -= tempDamage;
          specialOutput += "Monster 1 dealt " + RED + to_string((tempDamage)) + RESET_COLOR + " damage.\n";
        }
        else {
          specialOutput += "Monster 1 missed.\n";
        }
      }
      else if (gameMap[monOneRow][monOneCol+1] == P) // attack right
      {
        if (hitCheck(monOneDex, playerDex))
        {
          tempDamage = calculateDamage(monsterDice, monOneStr);
          playerHP -= tempDamage;
          specialOutput += "Monster 1 dealt " + RED + to_string((tempDamage)) + RESET_COLOR + " damage.\n";
        }
        else {
          specialOutput += "Monster 1 missed.\n";
        }
      }
      else if (playerRow < monOneRow && gameMap[monOneRow-1][monOneCol] == F) // move up
      {
        gameMap[monOneRow-1][monOneCol] = A;
        gameMap[monOneRow][monOneCol] = F;
        monOneRow -= 1;
      }
      else if (playerCol < monOneCol && gameMap[monOneRow][monOneCol-1] == F) // move left
      {
        gameMap[monOneRow][monOneCol-1] = A;
        gameMap[monOneRow][monOneCol] = F;
        monOneCol -= 1;
      }
      else if (playerRow > monOneRow && gameMap[monOneRow+1][monOneCol] == F) // move down
      {
        gameMap[monOneRow+1][monOneCol] = A;
        gameMap[monOneRow][monOneCol] = F;
        monOneRow += 1;
      }
      else if (playerCol > monOneCol && gameMap[monOneRow][monOneCol+1] == F) // move right
      {
        gameMap[monOneRow][monOneCol+1] = A;
        gameMap[monOneRow][monOneCol] = F;
        monOneCol += 1;
      }
    } // end of monster 1 AI.
    
    // monster 2 AI:
    if (monTwoHP > 0)
    {
      if (gameMap[monTwoRow-1][monTwoCol] == P) // attack up
      {
        if (hitCheck(monTwoDex, playerDex))
        {
          tempDamage = calculateDamage(monsterDice, monTwoStr);
          playerHP -= tempDamage;
          specialOutput += "Monster 2 dealt " + RED + to_string((tempDamage)) + RESET_COLOR + " damage.\n";
        }
        else {
          specialOutput += "Monster 2 missed.\n";
        }
      }
      else if (gameMap[monTwoRow][monTwoCol-1] == P) // attack left
      {
        if (hitCheck(monTwoDex, playerDex))
        {
          tempDamage = calculateDamage(monsterDice, monTwoStr);
          playerHP -= tempDamage;
          specialOutput += "Monster 2 dealt " + RED + to_string((tempDamage)) + RESET_COLOR + " damage.\n";
        }
        else {
          specialOutput += "Monster 2 missed.\n";
        }
      }
      else if (gameMap[monTwoRow+1][monTwoCol] == P) // attack down
      {
        if (hitCheck(monTwoDex, playerDex))
        {
          tempDamage = calculateDamage(monsterDice, monTwoStr);
          playerHP -= tempDamage;
          specialOutput += "Monster 2 dealt " + RED + to_string((tempDamage)) + RESET_COLOR + " damage.\n";
        }
        else {
          specialOutput += "Monster 2 missed.\n";
        }
      }
      else if (gameMap[monTwoRow][monTwoCol+1] == P) // attack right
      {
        if (hitCheck(monTwoDex, playerDex))
        {
          tempDamage = calculateDamage(monsterDice, monTwoStr);
          playerHP -= tempDamage;
          specialOutput += "Monster 2 dealt " + RED + to_string((tempDamage)) + RESET_COLOR + " damage.\n";
        }
        else {
          specialOutput += "Monster 2 missed.\n";
        }
      }
      else if (playerRow < monTwoRow && gameMap[monTwoRow-1][monTwoCol] == F) // move up
      {
        gameMap[monTwoRow-1][monTwoCol] = B;
        gameMap[monTwoRow][monTwoCol] = F;
        monTwoRow -= 1;
      }
      else if (playerCol < monTwoCol && gameMap[monTwoRow][monTwoCol-1] == F) // move left
      {
        gameMap[monTwoRow][monTwoCol-1] = B;
        gameMap[monTwoRow][monTwoCol] = F;
        monTwoCol -= 1;
      }
      else if (playerRow > monTwoRow && gameMap[monTwoRow+1][monTwoCol] == F) // move down
      {
        gameMap[monTwoRow+1][monTwoCol] = B;
        gameMap[monTwoRow][monTwoCol] = F;
        monTwoRow += 1;
      }
      else if (playerCol > monTwoCol && gameMap[monTwoRow][monTwoCol+1] == F) // move right
      {
        gameMap[monTwoRow][monTwoCol+1] = B;
        gameMap[monTwoRow][monTwoCol] = F;
        monTwoCol += 1;
      }
    } // end of monster 2 AI.
    
    // monster 3 AI:
    if (monThreeHP > 0)
    {
      if (gameMap[monThreeRow-1][monThreeCol] == P) // attack up
      {
        if (hitCheck(monThreeDex, playerDex))
        {
          tempDamage = calculateDamage(monsterDice, monThreeStr);
          playerHP -= tempDamage;
          specialOutput += "Monster 3 dealt " + RED + to_string((tempDamage)) + RESET_COLOR + " damage.\n";
        }
        else {
          specialOutput += "Monster 3 missed.\n";
        }
      }
      else if (gameMap[monThreeRow][monThreeCol-1] == P) // attack left
      {
        if (hitCheck(monThreeDex, playerDex))
        {
          tempDamage = calculateDamage(monsterDice, monThreeStr);
          playerHP -= tempDamage;
          specialOutput += "Monster 3 dealt " + RED + to_string((tempDamage)) + RESET_COLOR + " damage.\n";
        }
        else {
          specialOutput += "Monster 3 missed.\n";
        }
      }
      else if (gameMap[monThreeRow+1][monThreeCol] == P) // attack down
      {
        if (hitCheck(monThreeDex, playerDex))
        {
          tempDamage = calculateDamage(monsterDice, monThreeStr);
          playerHP -= tempDamage;
          specialOutput += "Monster 3 dealt " + RED + to_string((tempDamage)) + RESET_COLOR + " damage.\n";
        }
        else {
          specialOutput += "Monster 3 missed.\n";
        }
      }
      else if (gameMap[monThreeRow][monThreeCol+1] == P) // attack right
      {
        if (hitCheck(monThreeDex, playerDex))
        {
          tempDamage = calculateDamage(monsterDice, monThreeStr);
          playerHP -= tempDamage;
          specialOutput += "Monster 3 dealt " + RED + to_string((tempDamage)) + RESET_COLOR + " damage.\n";
        }
        else {
          specialOutput += "Monster 3 missed.\n";
        }
      }
      else if (playerRow < monThreeRow && gameMap[monThreeRow-1][monThreeCol] == F) // move up
      {
        gameMap[monThreeRow-1][monThreeCol] = C;
        gameMap[monThreeRow][monThreeCol] = F;
        monThreeRow -= 1;
      }
      else if (playerCol < monThreeCol && gameMap[monThreeRow][monThreeCol-1] == F) // move left
      {
        gameMap[monThreeRow][monThreeCol-1] = C;
        gameMap[monThreeRow][monThreeCol] = F;
        monThreeCol -= 1;
      }
      else if (playerRow > monThreeRow && gameMap[monThreeRow+1][monThreeCol] == F) // move down
      {
        gameMap[monThreeRow+1][monThreeCol] = C;
        gameMap[monThreeRow][monThreeCol] = F;
        monThreeRow += 1;
      }
      else if (playerCol > monThreeCol && gameMap[monThreeRow][monThreeCol+1] == F) // move right
      {
        gameMap[monThreeRow][monThreeCol+1] = C;
        gameMap[monThreeRow][monThreeCol] = F;
        monThreeCol += 1;
      }
    } // end of monster 3 AI.

    if (playerHP <= 0) // Checks if player is dead.
    {
      isGameOver = true;
    }

    clearConsole(); //Clears the console of all outputs/inputs.
    cout << "Floor: " << floorNum << endl;
    displayMap(); // Outputs the map to the console.
    cout << specialOutput;
    specialOutput = "";
  } // End of Main Game Loop

  clearConsole(); //Clears the console of all outputs/inputs.
  cout << "Floor: " << floorNum << endl;
  displayMap();
  displayStats(playerHP, playerMaxHP, playerStr, playerDex, playerInt, playerXP);
} // end of main

// ---- FUNCTION DEFINITIONS ----

// Displays the current game map
void displayMap()
{
  for (int row = 0; row < ROWS; row++)
  {
    for (int col = 0; col < COLUMNS; col++)
    {
      cout << gameMap[row][col] << " ";
    }
    cout << endl;
  }
} // end of displayMap

// determines the type of action the player is trying to do based on where the player is trying to go.
int determineMoveType(int endRow, int endCol) 
{
/*
  moveType = -1 :           game over
  moveType = 0 : trees      blocking movement
  moveType = 1 : endpoint   blocking movement
  moveType = 2 : floor      allowing movement
  moveType = 3 : monster A  allowing attack
  moveType = 4 : monster B  allowing attack
  moveType = 5 : monster C  allowing attack
  moveType = 6 : player     allowing attack
  moveType = 7 : shop       allowing shopping
  moteType = 8 : loot       increasing a stat
*/
  int moveType = 0;
  if(gameMap[endRow][endCol] == T)
  {
    moveType = 0;
  }
  else if (gameMap[endRow][endCol] == E)
  {
    moveType = 1;
  }
  else if (gameMap[endRow][endCol] == F)
  {
    moveType = 2;
  }
  else if (gameMap[endRow][endCol] == A)
  {
    moveType = 3;
  }
  else if (gameMap[endRow][endCol] == B)
  {
    moveType = 4;
  }
  else if (gameMap[endRow][endCol] == C)
  {
    moveType = 5;
  }
  else if (gameMap[endRow][endCol] == P)
  {
    moveType = 6;
  }
  else if (gameMap[endRow][endCol] == S)
  {
    moveType = 7;
  }
  else if (gameMap[endRow][endCol] == L)
  {
    moveType = 8;
  }
  return moveType;
} // end of determineMoveType

// Moves the location of the player or takes another action
void movePlayer(int startRow, int startCol, int endRow, int endCol, int moveType)
{
  if (moveType == 0)
  {
    cout << "Invalid Move." << endl;
    isValidMovement = false;
    isLastMoveValid = false;
  }
  else if (moveType == 1)
  {
    cout << "Moving to next floor." << endl;
    isValidMovement = true;
    isLastMoveValid = true;
  }
  else if (moveType == 2)
  {
    gameMap[endRow][endCol] = P;
    gameMap[startRow][startCol] = F;
    isValidMovement = true;
    isLastMoveValid = true;
  }
  else if (moveType == -1)
  {
    cout << "Game over." << endl;
    isValidMovement = true;
    isLastMoveValid = true;
  }
  else if (moveType == 7)
  {
    cout << "Opening Shop." << endl;
    isValidMovement = true;
    isLastMoveValid = true;
  }
  else if (moveType == 8)
  {
    cout << "Opening Loot." << endl;
    isValidMovement = true;
    isLastMoveValid = true;
  }
  else if (moveType == 3 || moveType == 4 || moveType == 5)
  {
    cout << "Attacking enemy." << endl;
    isValidMovement = true;
    isLastMoveValid = true;
  }
  else // Current way the monsters, shop, and player moveTypes are being handled (pretending they're trees)
  {
    cout << "Invalid Move" << endl;
    isValidMovement = false;
    isLastMoveValid = false;
  }
} // end of moveAction

// Clears the console if not in Debug mode
void clearConsole()
{
  if (!DEBUG_MODE)
    {
      system("clear");
    }
} // end of clearConsole

// Imports a map from a file into the 2d array gameMap[][] and outputs the map number.
int generateMap(int floor, int lastMap)
{
  string letter = "";
  int row = 0;
  int col = 0;
  int mapVal = 0;
  string fileName = "";
  ifstream infile;
  if (TEST_MAP_MODE)
  {
    infile.open("Maps/TestMap.map");
    mapVal = 11;
  }
  else
  {
    if ((floor % 5) == 0 && floor != 0)
    {
      infile.open("Maps/MapShop.map");
      mapVal = 10;
    }
    else
    {
      mapVal = rand() % 10;
      fileName = "Maps/Map" + to_string(mapVal) + ".map";
      infile.open(fileName);
    }
  }
  for (row = 0; row < ROWS; row++)
  {
    for (col = 0; col < COLUMNS; col++)
    {
      infile >> letter;
      if (letter == "T")
      {
        gameMap[row][col] = T;
      }
      else if (letter == "P")
      {
        gameMap[row][col] = P;
      }
      else if (letter == "E")
      {
        gameMap[row][col] = E;
      }
      else if (letter == "F")
      {
        gameMap[row][col] = F;
      }
      else if (letter == "A")
      {
        gameMap[row][col] = A;
      }
      else if (letter == "B")
      {
        gameMap[row][col] = B;
      }
      else if (letter == "C")
      {
        gameMap[row][col] = C;
      }
      else if (letter == "S")
      {
        gameMap[row][col] = S;
      }
      else if (letter == "L")
      {
        gameMap[row][col] = L;
      }
    }
  }
  infile.close();
  return mapVal;
} // end of generateMap

//Outputs all of the players starts in the same line.
void displayStats(double health, double maxHealth, double strength, double dexterity, double intelligence, double experience) 
{
  cout.setf(ios::fixed); 
	cout.precision(2);
  cout << "HP: ";
  if (health >= maxHealth)
  {
    cout << GREEN;
  } 
  else if (health < maxHealth)
  {
    cout << YELLOW;
  }
  cout << health << RESET_COLOR << "/";
  cout << GREEN << maxHealth << RESET_COLOR << " | ";
  cout << "Str: " << GREEN << strength << RESET_COLOR << " | ";
  cout << "Dex: " << GREEN << dexterity << RESET_COLOR << " | ";
  cout << "Int: " << GREEN << intelligence << RESET_COLOR << " | ";
  cout << "XP: " << GREEN << experience << RESET_COLOR << endl;
  cout.setf(ios::fixed); 
	cout.precision(0);
} // end of displayStats

// Displays all of the necessary shop info
void displayShopMenu()
{
  cout << BLUE << "Stat Upgrade Shop: " << RESET_COLOR <<endl;
  cout << "Health        (+1)  | Cost: " << GREEN << (2 * SHOP_PRICE) << RESET_COLOR << " XP." << endl;
  cout << "Strength     (+0.05) | Cost: " << GREEN << SHOP_PRICE << RESET_COLOR << " XP." << endl;
  cout << "Dexterity    (+0.05) | Cost: " << GREEN << SHOP_PRICE << RESET_COLOR << " XP." << endl;
  cout << "Intelligence (+0.05) | Cost: " << GREEN << SHOP_PRICE << RESET_COLOR << " XP." << endl;
} // end of displayShopMenu

// Determines if an attack hits its target
bool hitCheck(double attackDex, double targetDex)
{
  double attackResult = 0;
  double targetResult = 0;
  attackResult = (rand() % 10) + 1;
  attackResult = attackResult * attackDex;
  targetResult = (rand() % 10) + 1;
  targetResult = targetResult * targetDex;
  return (attackResult > targetResult); // returns true if the attacker's result is greater than the target's result.
} // end of hitCheck

// randomly generates the damage to be dealt to the target
double calculateDamage(int dieSize, double strength)
{
  double damage;
  damage = (rand() % dieSize) + 1;
  damage = damage * strength;
  return damage;
} // end of calculateDamage

// randomly generates the xp to be given to the player
double generateXP(int range, int lower)
{
  return ((rand() % range) + lower);
} // end of generateXP

// Displays the title and opening monologue
void displayTitleScreen()
{
  cout << "Welcome to:" << endl << endl;
  cout << BLUE << "ZACH'S FOREST OF DREAMS" << RESET_COLOR << endl << endl;
  cout << "A game made by Zachary Newman for CMPSC 101." << endl;
  cout << "(Make sure you have read README.md before continuing.)" << endl << endl;
  cout << "You awaken in the middle of a dense forest with nothing but your clothing and a crude weapon. \nA quick glance around reveals that the forest goes on as far as you can see, which isn't that far as everything is obscured by a faint white fog. \nThe only way to leave is to travel through the clearings within the forest. \nAs you do so, you begin to realise that you are not alone." << endl;
} // end of displayTitleScreen

// Allows the player to select a difficulty modifier
double selectDifficulty()
{
  bool validDiff = false;
  bool lastDiffValid = true;
  string input = "";
  while (!validDiff)
  {
    clearConsole();
    cout << "Choose your difficulty from among the following:" << endl;
    cout << "Easy: " << GREEN << "1.1x" << RESET_COLOR << endl;
    cout << "Medium: " << GREEN << "1.2x" << RESET_COLOR << endl;
    cout << "Hard: " << GREEN << "1.5x" << RESET_COLOR << endl;
    cout << "Impossible: " << GREEN << "2.0x" << RESET_COLOR << endl;
    if (lastDiffValid)
    {
      cout << "Input the name of the difficulty to select it: ";
    }
    else
    {
      cout << "Input the " << RED << "VALID" << RESET_COLOR << " name of the difficulty to select it: ";
    }
    cin >> input;
    if (input == "Easy" || input == "easy" || input == "e")
    {
      return 1.1;
    }
    else if (input == "Medium" || input == "medium" || input == "m")
    {
      return 1.2;
    }
    else if (input == "Hard" || input == "hard" || input == "h")
    {
      return 1.5;
    }
    else if (input == "Impossible" || input == "impossible" || input == "i")
    {
      return 2.0;
    }
    else
    {
      lastDiffValid = false;
      validDiff = false;
    }
