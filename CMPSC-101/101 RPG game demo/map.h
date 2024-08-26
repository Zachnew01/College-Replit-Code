#include <iostream>
using namespace std;

void ShowMap(int location) // show map
{
  char green[] = { 0x1b, '[', '0', ';', '3', '2', 'm', 0 }; // make it green
  char normal[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };// make it white

  if (location == 1)
  {
    cout << normal << " _________________________________________________________" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                 /¯ † ¯\\       /¯ ∩ ¯\\                   |" << endl;
    cout << "|                /       \\     /       \\                  |" << endl;
    cout << "|           "<< green << "o" << normal << " - = -- = ------ x -- = ---- = - ?           |" << endl; // center
    cout << "|                \\       /     \\       /                  |" << endl;
    cout << "|                 \\_ ∩ _/       \\_ † _/                   |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                                                         |" << endl;
    cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
    cout << "|                         Legend                          |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|    o → You Are Here        x → Town         ∩ → Cave    |" << endl;
    cout << "|      † → Forest          / or - → Path      = → Road    |" << endl;
    cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
  }

  if (location == 2)
  {
    cout << normal << " _________________________________________________________" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                 /¯ † ¯\\       /¯ ∩ ¯\\                   |" << endl;
    cout << "|                /       \\     /       \\                  |" << endl;
    cout << "|           = - " << green << "o" << normal << " -- = ------ x -- = ---- = - ?           |" << endl; // center
    cout << "|                \\       /     \\       /                  |" << endl;
    cout << "|                 \\_ ∩ _/       \\_ † _/                   |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                                                         |" << endl;
    cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
    cout << "|                         Legend                          |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|    o → You Are Here        x → Town         ∩ → Cave    |" << endl;
    cout << "|      † → Forest          / or - → Path      = → Road    |" << endl;
    cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
  }

  if (location == 3)
  {
    cout << normal << " _________________________________________________________" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                 /¯ " << green << "o" << normal << " ¯\\       /¯ ∩ ¯\\                   |" << endl;
    cout << "|                /       \\     /       \\                  |" << endl;
    cout << "|           = - = -- = ------ x -- = ---- = - ?           |" << endl; // center
    cout << "|                \\       /     \\       /                  |" << endl;
    cout << "|                 \\_ ∩ _/       \\_ † _/                   |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                                                         |" << endl;
    cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
    cout << "|                         Legend                          |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|    o → You Are Here        x → Town         ∩ → Cave    |" << endl;
    cout << "|      † → Forest          / or - → Path      = → Road    |" << endl;
    cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
  }

  if (location == 4)
  {
    cout << normal << " _________________________________________________________" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                 /¯ † ¯\\       /¯ ∩ ¯\\                   |" << endl;
    cout << "|                /       \\     /       \\                  |" << endl;
    cout << "|           = - = -- " << green << "o" << normal << " ------ x -- = ---- = - ?           |" << endl; // center
    cout << "|                \\       /     \\       /                  |" << endl;
    cout << "|                 \\_ ∩ _/       \\_ † _/                   |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                                                         |" << endl;
    cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
    cout << "|                         Legend                          |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|    o → You Are Here        x → Town         ∩ → Cave    |" << endl;
    cout << "|      † → Forest          / or - → Path      = → Road    |" << endl;
    cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
  }

  if (location == 5)
  {
    cout << normal << " _________________________________________________________" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                 /¯ † ¯\\       /¯ ∩ ¯\\                   |" << endl;
    cout << "|                /       \\     /       \\                  |" << endl;
    cout << "|           = - = -- = ------ x -- = ---- = - ?           |" << endl; // center
    cout << "|                \\       /     \\       /                  |" << endl;
    cout << "|                 \\_ " << green << "o" << normal << " _/       \\_ † _/                   |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                                                         |" << endl;
    cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
    cout << "|                         Legend                          |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|    o → You Are Here        x → Town         ∩ → Cave    |" << endl;
    cout << "|      † → Forest          / or - → Path      = → Road    |" << endl;
    cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
  }

  if (location == 6)
  {
    cout << normal << " _________________________________________________________" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                 /¯ † ¯\\       /¯ ∩ ¯\\                   |" << endl;
    cout << "|                /       \\     /       \\                  |" << endl;
    cout << "|           = - = -- = ------ " << green << "o" << normal << " -- = ---- = - ?           |" << endl; // center
    cout << "|                \\       /     \\       /                  |" << endl;
    cout << "|                 \\_ ∩ _/       \\_ † _/                   |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                                                         |" << endl;
    cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
    cout << "|                         Legend                          |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|    o → You Are Here        x → Town         ∩ → Cave    |" << endl;
    cout << "|      † → Forest          / or - → Path      = → Road    |" << endl;
    cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
  }

  if (location == 7)
  {
    cout << normal << " _________________________________________________________" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                 /¯ † ¯\\       /¯ " << green << "o" << normal << " ¯\\                   |" << endl;
    cout << "|                /       \\     /       \\                  |" << endl;
    cout << "|           = - = -- = ------ x -- = ---- = - ?           |" << endl; // center
    cout << "|                \\       /     \\       /                  |" << endl;
    cout << "|                 \\_ ∩ _/       \\_ † _/                   |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                                                         |" << endl;
    cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
    cout << "|                         Legend                          |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|    o → You Are Here        x → Town         ∩ → Cave    |" << endl;
    cout << "|      † → Forest          / or - → Path      = → Road    |" << endl;
    cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
  }

  if (location == 8)
  {
    cout << normal << " _________________________________________________________" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                 /¯ † ¯\\       /¯ ∩ ¯\\                   |" << endl;
    cout << "|                /       \\     /       \\                  |" << endl;
    cout << "|           = - = -- = ------ x -- " << green << "o" << normal << " ---- = - ?           |" << endl; // center
    cout << "|                \\       /     \\       /                  |" << endl;
    cout << "|                 \\_ ∩ _/       \\_ † _/                   |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                                                         |" << endl;
    cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
    cout << "|                         Legend                          |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|    o → You Are Here        x → Town         ∩ → Cave    |" << endl;
    cout << "|      † → Forest          / or - → Path      = → Road    |" << endl;
    cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
  }

  if (location == 9)
  {
    cout << normal << " _________________________________________________________" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                 /¯ † ¯\\       /¯ ∩ ¯\\                   |" << endl;
    cout << "|                /       \\     /       \\                  |" << endl;
    cout << "|           = - = -- = ------ x -- = ---- = - ?           |" << endl; // center
    cout << "|                \\       /     \\       /                  |" << endl;
    cout << "|                 \\_ ∩ _/       \\_ " << green << "o" << normal << " _/                   |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                                                         |" << endl;
    cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
    cout << "|                         Legend                          |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|    o → You Are Here        x → Town         ∩ → Cave    |" << endl;
    cout << "|      † → Forest          / or - → Path      = → Road    |" << endl;
    cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
  }

  if (location == 10)
  {
    cout << normal << " _________________________________________________________" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                 /¯ † ¯\\       /¯ ∩ ¯\\                   |" << endl;
    cout << "|                /       \\     /       \\                  |" << endl;
    cout << "|           = - = -- = ------ x -- = ---- " << green << "o" << normal << " - ?           |" << endl; // center
    cout << "|                \\       /     \\       /                  |" << endl;
    cout << "|                 \\_ ∩ _/       \\_ † _/                   |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|                                                         |" << endl;
    cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
    cout << "|                         Legend                          |" << endl;
    cout << "|                                                         |" << endl;
    cout << "|    o → You Are Here        x → Town         ∩ → Cave    |" << endl;
    cout << "|      † → Forest          / or - → Path      = → Road    |" << endl;
    cout << " ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << endl;
  }
}
