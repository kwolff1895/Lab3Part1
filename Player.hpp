/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.hpp
 * Author: Kimberly
 *
 * Created on March 12, 2017, 3:26 PM
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <cstring>
#include <iostream>
#include "cell.hpp"
//#include "moveslist.hpp" // for extra credit only
using namespace std;
class Player {
 string name; // the player's name
 char c; // the player's character that they're placing on the board each turn
 int score; // keeps track of the player's score (number of completed squares
 bool isComputer; // indicates whether this player is a computer or a human


public:
 friend class Game; // so Game has access to all private fields and methods
 Player();
 // constructor that uses cin to ask user for player's name and character. Initializes
 // score to 0, isComputer to false.
 Player(string n, char ic, bool x);
 //constructor that initializes name to n, c to ic, and bool to x. Initializes score
 // to 0.
};





#endif /* PLAYER_HPP */

