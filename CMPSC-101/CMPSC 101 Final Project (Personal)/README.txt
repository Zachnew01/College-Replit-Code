Welcome to ZACH'S FOREST OF DREAMS

A game made by Zachary Newman for CMPSC 101.

In this game, you navigate through various clearings (floors) within the Forests of Dreams, fighting monsters until you reach the end. This game is technically infinite, so try to go as far as you can. Feel free to refer to this document whenever you are confused about something.

How to Play:

- When you start the game, you will be greeted by a simple title screen. Once you have read through the flavor text, type in whatever you want and hit enter. Every time you are asked to input something, type what you want and hit enter. Unless you see red text indicating that you need to input a valid response, then your command should've gone through.
- After reading the title screen, you will be prompted to input a difficulty. The difficulty simply just changes the modifier to the stats of the monsters. Every 5th floor, the monsters stats will be multipled by that number. I will explain stats later.
- Once the difficulty has been selected, the game will generate the first map and you can start playing.
  - Entering "w" moves your character (the emoji with the cowboy hat) up one space.
  - Entering "a" moves your character left one space.
  - Entering "s" moves your character down one space.
  - Entering "d" moves your character right one space.
  - Entering "q" quits the game.
- You can only move onto spaces that are unoccupied, but these commands can also be used to interact with things in the game.
  - Moving into a tree is an invalid move.
  - Moving into the round hole will end the floor if all enemies have been killed.
  - Moving into the money bag will grant you experience (XP).
  - Moving into one of the animals (monsters) will attack them.
- Every 5th floor you reach, you will encounter a shop (the campsite) which you can move into to interact with it. Doing so will open the shop menu to upgrade your stats.

Stats:

- In the game, you have 4 different stats: Health, Strength, Dexterity, and Intelligence. You also have 1 resourse: Experience.
- They are displayed in game like:
- HP: 15.00/15.00 | Str: 1.00 | Dex: 1.00 | Int: 1.00 | XP: 0.00
  - Health (HP) is the amount of damage you can take before you lose the game. The number on the left is your current amount of Health. The number on the right is the max amount of health you can have. You return to full health at the start of each new floor.
  - Strength (Str) modifies how much damage you deal to enemies. You damage is multiplied by your strength stat. You start off by dealing between 1 to 6 damage.
  - Dexterity (Dex) modifies your chance to hit monsters and not get hit by monsters. Everytime you go to attack a monster, or a monster tries to attack you, two random numbers are generated and compared to see if the target is hit by or dodges the attack. Your chance to successfully hit an attack, or dodge an attack against you, is multiplied by your Dexterity stat.
  - Intelligence (Int) modifies the experience (XP) you gain when killing monsters or finding loot. The amount of experience you gain is multiplied by your Intelligence stat.
  - Experience (XP) is used to pay for stat upgrades in the shop every 5th floor.

Monsters:

- There are three monsters per floor, each start off having slightly weaker stats than the player (Only health, strength, and dexterity), with each one having their own distribution of stats.
  - The rat has slighty higher strength.
  - The bird has slightly higher dexterity.
  - The turtle has slightly higher health.
- Each monster will try to move towards the player and will not stop unless it is dead.
- If the monster is adjacent to you, it will try to attack you.
- If the monster's health reaches zero, it disapears from the map and you gain XP.
