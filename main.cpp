/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Kimberly
 *
 * Created on March 12, 2017, 3:25 PM
 */

#include <stdlib.h>
#include "Cell.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include <iostream>

using namespace std;

/*
 * 
 */
int main() {
    Game game;
    game.makeBoard();
    game.getPlayers();
    game.printBoard();
    game.printPlayers();
    game.getWinner();
    

    return 0;
}

