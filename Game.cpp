/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Game.hpp"
#include "Cell.hpp"

#include <stdlib.h>
#include <iostream>
#include <valarray>
using namespace std;
Game::Game() {
    cout<<"Please enter board size: "<<endl;
    cin>>size;;
    cout<<"Please enter total number of players: "<<endl;
    cin>>numPlayers;
    cout<<"Please enter number of computer players: "<<endl;
    cin>>compplayers;
    turn = 0;
    won = false;
    boardFull=false;
    makeBoard();
    getPlayers();
    printPlayers();
    printBoard();
    playGame();
    
    
// for non-automatized version – asks for board size, num players, num of computer players, and then initializes
// everything
// your code goes here
}
Game::Game(bool b) {
    if (b == true){
        size = rand() % 11 +3;
        numPlayers = 2;
        compplayers = 2;
        boardFull=false;
        turn = 0;
        won = false;
        
    }
    else{
        makeBoard();
        printBoard();
        getPlayers();
        printPlayers();
        playGame();
    }
    
//for the automated version – if b is true, randomly generate the size of the board, set the num of players and the
//num of compplayers to 2, and the, of course initialize everything
// your code goes here
}
void Game::makeBoard(){
    //dynamically create board to be size x size
    board = new char*[size];
    for (int i = 0; i < size; i++) {
        board[i] = new char[size];
        for (int j = 0; j < size; j++) {
            board[i][j] = '.';
        }
    }
}
void Game::printBoard() {
//Note: I’m giving you this one
 for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
        cout << board[i][j]<<"\t";
    }
    cout << endl;
 }
}
void Game::getPlayers() {
//This method dynamically generates an array of players, and then, for each element in the array, creates a new
//player object with a name and a character. For the number of players that are computers, I used an array of names
// and an array of characters, and then just selected the next name and character in the list for my player object.
// for humans I called the Player constructor with no input parameters (that one asked the user for their name and
// their preferred character.
// your code goes here
    //create string array for names of computer players
    
    string compNames[] = {"George", "Sally", "Bob","Kelly", "Ryan"};
    char compCharacters[]={'a','b','c','d','e'};
    int NumCompPlayers = compplayers;
    players = NULL;
    players = new Player*[numPlayers];
    for (int i = 0; i< numPlayers;i++){
        if (NumCompPlayers>0){
            players[i] = new Player (compNames[i], compCharacters[i], true);
            NumCompPlayers--;
        }
        else{
            players[i] = new Player();
        }
    }
}
void Game::printPlayers() {
// this method is optional – I wrote it so I could test my getPlayers() method to make sure it generated all my Players
// correctly. If you choose not to include this method, that is fine.
    for (int i = 0; i<numPlayers;i++){
        cout<<"Players"<<(*players[i]).name<<endl;
    }
}
void Game::playGame() {
// This is the heart of the game. I called this method directly from my Game constructor(s) as the very last thing.
//This method loops until the board is full.
// In each loop, the next player either chooses where to place their character (if human) or the x,y coordinates are
// randomly generated (and checked to make sure the player isn’t overwriting a piece already on the board).
//It checks to see if the new piece completes a square, and, if so, that player’s score goes up by 1 and that player
// takes another turn. At the end of each round, the board is printed out and each player’s name and score is printed.
//Your code goes here
    int numIterations = 0;//number of iterations or loops per game
    int x;
    int y;
    bool continuePlaying = true;//variable to tell if game should continue or not
    bool initial = true;//variable for initial move for a player
    
    while(numIterations < size*size){
        if ((*players[turn]).isComputer == true){//if player is computer
            while (continuePlaying == true){
                if (findMoves((*players[turn]).c == true)){//if a player can move
                    numIterations++;
                
                    if(numIterations == size*size){//if board full, stop playing
                        continuePlaying = false;
                    }
                }
            
                else{//if player cannot move
                    numIterations += 1;
                    continuePlaying = false;
                    printPlayers();
                }
        }
    }
        else{//get coordinates from human players
            while (continuePlaying == true){
                while(initial == true || x >= size || y >= size || x < 0 || y < 0 || board[x][y] != ','){
                    cout<< (*players[turn]).name << "Please enter a x coordinate";
                    cin>> x;
                    cout<<"Please enter a y coordinate";
                    cin>>y;
                    initial == false;
                }
                    board[x][y]= (*players[turn]).c;//place players character
                    if(checkFour(y,x) == true){//if forms a square, increase players score
                        (*players[turn]).score++;
                        printBoard();
                        printPlayers();
                        numIterations += 1;
                        
                        if (numIterations == size*size){//if board full
                            continuePlaying==false;
                        }
                    }
                    else{
                        turn += 1;
                        if (turn == numPlayers){
                            turn = 0;
                        }
                        numIterations +=1;
                        continuePlaying = false;
                        printBoard();
                        printPlayers();
                    }
                }
            }
            continuePlaying = true;
    }
        getWinner();
        boardFull = true;
}

bool Game::findMoves(char v){
    int index; //index of player who's turn it currently is
    bool placed = false;
    for (int i; i<numPlayers; i++){
        if ((*players[i]).c = v){
            index = i;//sets index to the index of current player
        }
    }
    int x = rand()%size;
    int y = rand()%size;
    for (int i; i <size*size; i++){
        if (board[x][y]== '.'){//if spot empty, add character
            board[x][y]=(*players[turn]).c;
            placed=true;
            if (checkFour(x,y)==true){//if they made a square, add 1 to score
                (*players[index]).score++;
                printBoard();
                printPlayers();
                return true;
            }
            else{
                turn++;
                if(turn == numPlayers){//reset turn to 0 if number of turns is going to exceed number of players
                    turn = 0;
                }
                printBoard();
                return false;
            }
        }
        x = rand()%size;
        y = rand()%size;
        return false;

}
    
    
    
    
// Regular version, this method continues to generate random x,y values until that cell on the
// board is empty, then places the player's character v on the board, and checks to see if a
// square is completed using checkFour. If so, true is returned and that player’s score goes up by 1 in the
// playGame method, and that player gets to take another turn (so turn does not increase by 1).
// This method uses checkFour() method to determine whether a move is good, checkThree to determine if a move is
// bad, and if neither of those is true, then the move is considered neutral.
// This method returns the list of three movesList objects.
}
bool Game::checkFour(int x, int y) {
    for (int i = 0; i<size; i++){
        for (int j = 0; j<size; j++){
            if (board[x+1][y] != '.' && board[x][y-1] != '.' && board[x+1][y-1] != '.'){
                return true;
            }
            
            else if(board[x+1][y] != '.' && board[x][y+1] != '.' && board[x+1][y+1] != '.'){
                return true;
            }
            else if(board[x-1][y] != '.' && board[x][y+1]!= '.' && board[x-1][y+1] != '.'){
                return true;
            }
            else if(board[x-1][y] != '.' && board[x][y-1] != '.' && board[x-1][y-1] != '.'){
                return true;
            }
        //makes a square if character on board at following locations:
        //(x+1,y)(x,y-1)(x+1,y-1)
        //OR
        //(x+1,y)(x,y+1)(x+1,y+1)
        //OR
        //(x-1,y)(x,y+1)(x-1,y-1)
        //OR
        //(x-1,y)(x,y-1)(x-1,y-1)
          
    
            else{
                return false;
            }
// this method checks to see if placing a piece at x and y on the board will complete a square, and, if so, it
// returns true. Otherwise it returns false.
        }
    }
}
void Game::getWinner() {
// This method determines which of the players in the array of Players has the highest score, and prints out 
// that player’s name and their score.
    int BestScore = -1;
    string winner;
    for (int i = 0; i<numPlayers; i++){
        if ((*players[i]).score>BestScore){
            BestScore = (*players[i]).score;
            winner = (*players[i]).name;
        }
    }
    cout<<"Winner = "<<winner<<"Best Score is: "<<BestScore<<endl;
}
//bool Game::checkThree(int x, int y) {
//// Only needed for Extra Credit
//// This method determines whether placing a piece on the board at x and y will complete ¾ of a square and, if so, it
//// returns true. Otherwise it returns false.
//}