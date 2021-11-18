/*
Caleb Hemmestad
C++ 2021
Due: 12/08/21
Lab 7 Battleship

Description: Make a simple battleship game in C++
*/


#include <iostream>
#include <iomanip>

using namespace std ;

typedef char ARRAY [ 10 ] [ 10 ] [ 6 ] ; //Defining 3D array

//precondition : Program moves too fast
//postcondition : Pausing in spots so you can read
void pause ( ) ;

//precondition : Don't know what youre playing are if you want to
//postcondition : Shows you what your playing and asks if you want
void header ( bool &again ) ;

//precondition : Array isnt storing any chars to display yet
//postcondition : Fills array with '~'
void setGrids ( ARRAY ocean ) ;

//precondition : Cant see whats happening 
//postcondition : Shows you the grid so you can see whats going on and where to place stuff
void display ( ARRAY ocean , int player ) ;

//precondition : Dont know if you want to play again
//postcondition : Asks you if you want to play again if won,lost, or surrendered and adds to wons or losses
void playAgain ( bool &again , int &player , bool &game ) ;

//precondition : Cant place ships and dont know if theyre valid positions
//postcondition : Checks if placement is valid and places the ship
void shipPlacement ( ARRAY ocean ) ;

//precondition : Computer cant place any ships yet
//postcondition : Allows computer to randomly place ships in valid spots
void shipPlacementCom ( ARRAY ocean ) ;

//precondition : Cant guess where to go yet
//postcondition : Allows you to guess a spot to fire and shows if hit or miss also lets you surrender
void guess ( ARRAY ocean , int &player , bool &game , int &losses ) ;

//precondition : Computer cant guess spots to fire
//postcondition : Allows computer to make a random spot to fire and shows if hit or miss
void guessCom ( ARRAY ocean ) ;

//precondition : Cant see how many times you won or lost
//postcondition : Displays the amount of times you won or lost at end of game
void win_loss ( int wins , int losses ) ;

//precondition : Dont know what ships have been destroyed
//postcondition : Shows you what ships have been destroyed
void gameStatus ( ARRAY ocean ) ;

//precondition : Dont know if anyone has won or lost yet
//postcondition : Checks to see if all ships have been destroyed and tells you if you won or lost
void gameOver ( ARRAY ocean , bool &game , int &losses , int &wins ) ;

/*
					=============================================
												 BEGINNING OF MAIN
					=============================================
*/
int main(int argc, char **argv)
{
	ARRAY ocean ; //3D array for keeping track of ships and everything ( 6 10x10 grids )
	bool again = true ; //Only continuing loop if player says yes
	bool game = true ; //Only continuing loop if game isnt over
	int player = 0 ; //Used for the amount of grids displayed ( 0 for user , 2 for user & com , 4 for user & com & shiptypes )
	int wins = 0 ; //For counting wins
	int losses = 0 ; //For counting losses
	
	header ( again ) ; //Displaying header for game
	do {
		if ( !again ) {
			break ;
		}
		setGrids ( ocean ) ; //Setting all of the grids to '~' for starting the game and playing again
		shipPlacement ( ocean ) ; //Allowing you to choose where to place ships
		shipPlacementCom ( ocean ) ; //Allowing computer to randomly place their ships
		do {
			gameStatus ( ocean ) ; //Check what and whos ships have been destroyed
			guess ( ocean , player , game , losses ) ; //Allowing you to guess or surrender
			gameOver ( ocean , game , losses , wins ) ; //Checking to see if anyone has lost yet
			pause ( ) ; //Pausing so you can read results of guess
			if ( !game ) {
				break ;
			}
			guessCom ( ocean ) ; //Allowing computer to guess randomly
			gameOver ( ocean , game , losses , wins ) ; //Checking to see if anyone has lost yet
			pause ( ) ; //Pausing for dramatic affect
			if ( !game ) {
				break ;
			}
		} while ( game ) ;
		playAgain ( again , player , game ) ; //Asking user if they want to play again
	} while ( again ) ;
	win_loss ( wins , losses ) ; //Displaying wins and losses if they quit the game
	
	return 0;
}
/*
					=============================================
														   END OF MAIN
					=============================================
*/

void gameOver ( ARRAY ocean , bool &game , int &losses , int &wins ) {
	
	int carrier = 0 ; 
	int battleship = 0 ;
	int cruiser = 0 ;
	int submarine = 0 ;
	int destroyer = 0 ;
	
	int comcarrier = 0 ; 
	int combattleship = 0 ;
	int comcruiser = 0 ;
	int comsubmarine = 0 ;
	int comdestroyer = 0 ;
	
	for ( int y = 0 ; y < 10 ; y++ ) {
		for ( int x = 0 ; x < 10 ; x++ ) {
			if ( ocean [ y ] [ x ] [ 4 ] == '5' ) {
				carrier++ ;
			} else if ( ocean [ y ] [ x ] [ 4 ] == '4' ) {
				battleship++ ;
			} else if ( ocean [ y ] [ x ] [ 4 ] == '3' ) {
				cruiser++ ;
			} else if ( ocean [ y ] [ x ] [ 4 ] == '2' ) {
				submarine++ ;
			} else if ( ocean [ y ] [ x ] [ 4 ] == '1' ) {
				destroyer++ ;
			}
		}
	}
	for ( int y = 0 ; y < 10 ; y++ ) {
		for ( int x = 0 ; x < 10 ; x++ ) {
			if ( ocean [ y ] [ x ] [ 5 ] == '5' ) {
				comcarrier++ ;
			} else if ( ocean [ y ] [ x ] [ 5 ] == '4' ) {
				combattleship++ ;
			} else if ( ocean [ y ] [ x ] [ 5 ] == '3' ) {
				comcruiser++ ;
			} else if ( ocean [ y ] [ x ] [ 5 ] == '2' ) {
				comsubmarine++ ;
			} else if ( ocean [ y ] [ x ] [ 5 ] == '1' ) {
				comdestroyer++ ;
			}
		}
	}
	if ( carrier == 0 && battleship == 0 && cruiser == 0
		&& submarine == 0 && destroyer == 0 ) {
		system ( "clear" ) ;
		cout << "All ships destroyed. You lost!" << endl ;
		losses++ ;
		game = false ;
	}
	if ( comcarrier == 0 && combattleship == 0 && comcruiser == 0
		&& comsubmarine == 0 && comdestroyer == 0 ) {
		system ( "clear" ) ;
		cout << "You destroyed all their ships. You win!" << endl ;
		wins++ ;
		game = false ;
	}
}

void gameStatus ( ARRAY ocean ) {
		
	int carrier = 0 ; 
	int battleship = 0 ;
	int cruiser = 0 ;
	int submarine = 0 ;
	int destroyer = 0 ;
	
	int comcarrier = 0 ; 
	int combattleship = 0 ;
	int comcruiser = 0 ;
	int comsubmarine = 0 ;
	int comdestroyer = 0 ;
	
	for ( int y = 0 ; y < 10 ; y++ ) {
		for ( int x = 0 ; x < 10 ; x++ ) {
			if ( ocean [ y ] [ x ] [ 4 ] == '5' ) {
				carrier++ ;
			} else if ( ocean [ y ] [ x ] [ 4 ] == '4' ) {
				battleship++ ;
			} else if ( ocean [ y ] [ x ] [ 4 ] == '3' ) {
				cruiser++ ;
			} else if ( ocean [ y ] [ x ] [ 4 ] == '2' ) {
				submarine++ ;
			} else if ( ocean [ y ] [ x ] [ 4 ] == '1' ) {
				destroyer++ ;
			}
		}
	}
	for ( int y = 0 ; y < 10 ; y++ ) {
		for ( int x = 0 ; x < 10 ; x++ ) {
			if ( ocean [ y ] [ x ] [ 5 ] == '5' ) {
				comcarrier++ ;
			} else if ( ocean [ y ] [ x ] [ 5 ] == '4' ) {
				combattleship++ ;
			} else if ( ocean [ y ] [ x ] [ 5 ] == '3' ) {
				comcruiser++ ;
			} else if ( ocean [ y ] [ x ] [ 5 ] == '2' ) {
				comsubmarine++ ;
			} else if ( ocean [ y ] [ x ] [ 5 ] == '1' ) {
				comdestroyer++ ;
			}
		}
	}
	if ( carrier == 0 ) {
		cout << "Carrier destroyed!" << endl ;
	}
	if ( battleship == 0 ) {
		cout << "Battleship destroyed!" << endl ;
	}
	if ( cruiser == 0 ) {
		cout << "Cruiser destroyed!" << endl ;
	}
	if ( submarine == 0 ) {
		cout << "Submarine destroyed!" << endl ;
	}
	if ( destroyer == 0 ) {
		cout << "Destroyer destroyed!" << endl ;
	}
	cout << endl ;
	if ( comcarrier == 0 ) {
		cout << "Computer carrier destroyed!" << endl ;
	}
	if ( combattleship == 0 ) {
		cout << "Computer battleship destroyed!" << endl ;
	}
	if ( comcruiser == 0 ) {
		cout << "Computer cruiser destroyed!" << endl ;
	}
	if ( comsubmarine == 0 ) {
		cout << "Computer submarine destroyed!" << endl ;
	}
	if ( comdestroyer == 0 ) {
		cout << "Computer destroyer destroyed!" << endl ;
	}
}

void win_loss ( int wins , int losses ) {
	system ( "clear" ) ;
	cout << endl ;
	cout << "You won " << wins << " times." << endl ;
	cout << "You lost " << losses << " times." << endl ;
}

void guessCom ( ARRAY ocean ) {
	int guessy ;
	int guessx ; 
	bool valid = false ;
	system ( "clear" ) ;
	srand(time(NULL)) ; 
	do {
		do {
			guessx = rand() %10+1 ;
			if ( guessx <= 10 && guessx > 0 ) {
				valid = true ;
				guessx -= 1 ;
			} 
		} while ( !valid ) ;
		valid = false ;
		do {
			guessy = rand() %10+1 ;
			if ( guessy <= 10 && guessy > 0 ) {
				valid = true ;
				guessy -= 1 ;
			} 
		} while ( !valid ) ;
		valid = false ;
		if ( ( ocean [ guessy ] [ guessx ] [ 2 ] == 'M' ) || ( ocean [ guessy ] [ guessx ] [ 2 ] == 'H' ) ) {
			valid = false ;
		} else {
			valid = true ;
		}
	} while ( !valid ) ;
	cout << "Computer : " << "X - " << guessx+1 << " Y - " << guessy+1 << endl ;
	if ( ocean [ guessy ] [ guessx ] [ 1 ] == '#' ) {
		ocean [ guessy ] [ guessx ] [ 2 ] = 'H' ;
		ocean [ guessy ] [ guessx ] [ 1 ] = 'H' ;
		cout << "Hit!" << endl << endl ;
	} else {
		ocean [ guessy ] [ guessx ] [ 2 ] = 'M' ;
		ocean [ guessy ] [ guessx ] [ 1 ] = 'M' ;
		cout << "Miss!" << endl << endl ;
	}
	ocean [ guessy ] [ guessx ] [ 4 ] = 'X' ;
}

void guess ( ARRAY ocean , int &player , bool &game , int &losses ) {
	int guessy ;
	int guessx ; 
	bool valid = false ;
	
	display ( ocean , player ) ;
	
	cout << endl << "Your turn" << endl ;
	cout << "Enter 9999 to surrender." << endl ;
	do {
		do {
			cout << "User X axis : " ;
			cin >> guessx ;
			if ( guessx == 1234 ) {
				player = 2 ;
			} else if ( guessx == 4321 ) {
				player = 0 ;
			} else if ( guessx == 9999 || !cin ) {
				game = false ;
				cout << "Surrendered!" << endl ;
				losses++ ;
				valid = true ;
			}
			if ( guessx <= 10 && guessx > 0 ) {
				valid = true ;
				guessx -= 1 ;
			} else if ( guessx != 9999 ) {
				cout << "Invalid" << endl ;
			}
		} while ( !valid ) ;
		valid = false ;
		do {
			if ( guessx != 9999 ) {
				cout << "User Y axis : " ;
				cin >> guessy ;
			} else {
				valid = true ;
			}
			if ( guessy <= 10 && guessy > 0 ) {
				valid = true ;
				guessy -= 1 ;
			} else {
				cout << "Invalid" << endl ;
			}
		} while ( !valid ) ;
		valid = false ;
		if ( guessx == 9999 ) {
			valid = true ;
		} else if ( ( ocean [ guessy ] [ guessx ] [ 0 ] == 'M' ) || ( ocean [ guessy ] [ guessx ] [ 0 ] == 'H' ) ) {
			cout << "Invalid" << endl ;
		} else {
			valid = true ;
		} 
	} while ( !valid ) ;
	if ( guessx != 9999 ) {
		if ( ocean [ guessy ] [ guessx ] [ 3 ] == '#' ) {
			ocean [ guessy ] [ guessx ] [ 0 ] = 'H' ;
			ocean [ guessy ] [ guessx ] [ 3 ] = 'H' ;
			cout << "Hit!" << endl << endl ;
		} else {
			ocean [ guessy ] [ guessx ] [ 0 ] = 'M' ;
			ocean [ guessy ] [ guessx ] [ 3 ] = 'M' ;
			cout << "Miss!" << endl << endl ;
		}
	}
	if ( guessx == 9999 ) {
		guessx = 1 ;
		guessy = 1 ;
	}
	ocean [ guessy ] [ guessx ] [ 5 ] = 'X' ;
}

void shipPlacementCom ( ARRAY ocean ) {
	char shipType ;
	int shipSize ;
	int yPlacement ;
	int xPlacement ;
	int direction ;
	
	cout << "Computer is placing their ships now..." << endl ;
	
	for ( int c = 0 ; c < 5 ; c++ ) {
		bool print = true ;
		switch ( c ) {
			case 0 :
			shipSize = 5 ;
			shipType = '5' ;
			break ;
			case 1 :
			shipSize = 4 ;
			shipType = '4' ;
			break ;
			case 2 :
			shipSize = 3 ;
			shipType = '3' ;
			break ;
			case 3 :
			shipSize = 3 ;
			shipType = '2' ;
			break ;
			case 4 :
			shipSize = 2 ;
			shipType = '1' ;
			break ;
		}
		srand(time(NULL)) ;
		
		xPlacement = rand() %10+1 ;
		if ( xPlacement > 10 || xPlacement <= 0 ) {
			c-- ;
			continue ;
		}
		yPlacement = rand() %10+1 ;
		if ( yPlacement > 10 || yPlacement <= 0 ) {
			c-- ;
			continue ;
		}
		direction = rand() %4+1 ;
		for ( int x = 0 ; x < shipSize ; x++ ) {
			if ( direction == 1 ) {
				if ( ocean [ yPlacement-1 ] [ xPlacement-1-x ] [ 3 ] == '#' ) {
					c-- ;
					print = false ;
				}
			} else if ( direction == 2 ) {
				if ( ocean [ yPlacement-1 ] [ xPlacement-1+x ] [ 3 ] == '#' ) {
					c-- ;
					print = false ;
				}
			} else if ( direction == 3 ) {
				if ( ocean [ yPlacement-1+x ] [ xPlacement-1 ] [ 3 ] == '#' ) {
					c-- ;
					print = false ;
				}
			} else if ( direction == 4 ) {
				if ( ocean [ yPlacement-1-x ] [ xPlacement-1 ] [ 3 ] == '#' ) {
					c-- ;
					print = false ;
				}
			} else {
				if ( ocean [ yPlacement-1 ] [ xPlacement-1+x ] [ 3 ] == '#' ) {
					c-- ;
					print = false ;
				}
			}
			if ( !print ) {
				break ;
			}
		}
		for ( int x = 0 ; x < shipSize ; x++ ) {
			if ( direction == 1 ) {
				if ( xPlacement-1-x < 0 ) {
					c-- ;
					print = false ;
				}
			} else if ( direction == 2 ) {
				if ( xPlacement-1+x > 9 ) {
					c-- ;
					print = false ;
				}
			} else if ( direction == 3 ) {
				if ( yPlacement-1+x > 9 ) {
					c-- ;
					print = false ;
				}
			} else if ( direction == 4 ) {
				if ( yPlacement-1-x < 0 ) {
					c-- ;
					print = false ;
				}
			} else {
				if ( xPlacement-1+x > 9 ) {
					c-- ;
					print = false ;
					break ;
				}
			}
			if ( !print ) {
				break ;
			}
		}
		if ( print ) {
			for ( int x = 0 ; x < shipSize ; x++ ) {
				if ( direction == 1 ) {
					ocean [ yPlacement-1 ] [ xPlacement-1-x ] [ 3 ] = '#' ;
					ocean [ yPlacement-1 ] [ xPlacement-1-x ] [ 5 ] = shipType ;
				} else if ( direction == 2 ) {
					ocean [ yPlacement-1 ] [ xPlacement-1+x ] [ 3 ] = '#' ;
					ocean [ yPlacement-1 ] [ xPlacement-1+x ] [ 5 ] = shipType ;
				} else if ( direction == 3 ) {
					ocean [ yPlacement-1+x ] [ xPlacement-1 ] [ 3 ] = '#' ;
					ocean [ yPlacement-1+x ] [ xPlacement-1 ] [ 5 ] = shipType ;
				} else if ( direction == 4 ) {
					ocean [ yPlacement-1-x ] [ xPlacement-1 ] [ 3 ] = '#' ;
					ocean [ yPlacement-1-x ] [ xPlacement-1 ] [ 5 ] = shipType ;
				} else {
					ocean [ yPlacement-1 ] [ xPlacement-1+x ] [ 3 ] = '#' ;
					ocean [ yPlacement-1 ] [ xPlacement-1+x ] [ 5 ] = shipType ;
				}
			}
		}		
	}
	system ( "clear" ) ;
}

void shipPlacement ( ARRAY ocean ) {
	
	char shipType ;
	int shipSize ;
	int yPlacement ;
	int xPlacement ;
	int direction ;
	
	for ( int c = 0 ; c < 5 ; c++ ) {
		bool print = true ;
		display ( ocean , 0 ) ;
		switch ( c ) {
			case 0 :
			shipSize = 5 ;
			shipType = '5' ;
			cout << endl << "Place carrier ( 5 spaces ) " << endl ;
			break ;
			case 1 :
			shipSize = 4 ;
			shipType = '4' ;
			cout << endl << "Place battleship ( 4 spaces ) " << endl ;
			break ;
			case 2 :
			shipSize = 3 ;
			shipType = '3' ;
			cout << endl << "Place cruiser ( 3 spaces ) " << endl ;
			break ;
			case 3 :
			shipSize = 3 ;
			shipType = '2' ;
			cout << endl << "Place submarine ( 3 spaces ) " << endl ;
			break ;
			case 4 :
			shipSize = 2 ;
			shipType = '1' ;
			cout << endl << "Place destroyer ( 2 spaces ) " << endl ;
			break ;
		}
		cout << "X axis : " ;
		cin >> xPlacement ;
		if ( !cin ){
			cout << "\n\n\n\t!!!!!!! PROGRAM FAILING !!!!!!!\n\n\n\n" ;
			break ;
		}
		if ( xPlacement > 10 || xPlacement <= 0 ) {
			system ( "clear" ) ;
			cout << "Invalid" << endl ;
			c-- ;
			continue ;
		}
		cout << "Y axis : " ; 
		cin >> yPlacement ;
		if ( !cin ) {
			cout << "\n\n\n\t!!!!!!! PROGRAM FAILING !!!!!!!\n\n\n\n" ;
			break ;
		}
		if ( yPlacement > 10 || yPlacement <= 0 ) {
			system ( "clear" ) ;
			cout << "Invalid" << endl ;
			c-- ;
			continue ;
		}
		cout << "Direction , Left 1 , Right 2 , Down 3 , Up 4 : " ;
		cin >> direction ;
		for ( int x = 0 ; x < shipSize ; x++ ) {
			if ( direction == 1 ) {
				if ( ocean [ yPlacement-1 ] [ xPlacement-1-x ] [ 1 ] == '#' ) {
					system ( "clear" ) ;
					cout << "Invalid" << endl ;
					c-- ;
					print = false ;
				}
			} else if ( direction == 2 ) {
				if ( ocean [ yPlacement-1 ] [ xPlacement-1+x ] [ 1 ] == '#' ) {
					system ( "clear" ) ;
					cout << "Invalid" << endl ;
					c-- ;
					print = false ;
				}
			} else if ( direction == 3 ) {
				if ( ocean [ yPlacement-1+x ] [ xPlacement-1 ] [ 1 ] == '#' ) {
					system ( "clear" ) ;
					cout << "Invalid" << endl ;
					c-- ;
					print = false ;
				}
			} else if ( direction == 4 ) {
				if ( ocean [ yPlacement-1-x ] [ xPlacement-1 ] [ 1 ] == '#' ) {
					system ( "clear" ) ;
					cout << "Invalid" << endl ;
					c-- ;
					print = false ;
				}
			} else {
				if ( ocean [ yPlacement-1 ] [ xPlacement-1+x ] [ 1 ] == '#' ) {
					system ( "clear" ) ;
					cout << "Invalid" << endl ;
					c-- ;
					print = false ;
				}
			}
			if ( !print ) {
				break ;
			}
		}
		for ( int x = 0 ; x < shipSize ; x++ ) {
			if ( direction == 1 ) {
				if ( xPlacement-1-x < 0 ) {
					system ( "clear" ) ;
					cout << "Invalid" << endl ;
					c-- ;
					print = false ;
				}
			} else if ( direction == 2 ) {
				if ( xPlacement-1+x > 9 ) {
					system ( "clear" ) ;
					cout << "Invalid" << endl ;
					c-- ;
					print = false ;
				}
			} else if ( direction == 3 ) { 
				if ( yPlacement-1+x > 9 ) {
					system ( "clear" ) ;
					cout << "Invalid" << endl ;
					c-- ;
					print = false ;
				} 
			} else if ( direction == 4 ) {
				if ( yPlacement-1-x < 0 ) {
					system ( "clear" ) ;
					cout << "Invalid" << endl ;
					c-- ;
					print = false ;
				}
			} else {
				if ( xPlacement-1+x > 9 ) {
					system ( "clear" ) ;
					cout << "Invalid" << endl ;
					c-- ;
					print = false ;
				}
			}
			if ( !print ) {
				break ;
			}
		}
		if ( print ) {
			for ( int x = 0 ; x < shipSize ; x++ ) {
				if ( direction == 1 ) {
					ocean [ yPlacement-1 ] [ xPlacement-1-x ] [ 1 ] = '#' ;
					ocean [ yPlacement-1 ] [ xPlacement-1-x ] [ 4 ] = shipType ;
				} else if ( direction == 2 ) {
					ocean [ yPlacement-1 ] [ xPlacement-1+x ] [ 1 ] = '#' ;
					ocean [ yPlacement-1 ] [ xPlacement-1+x ] [ 4 ] = shipType ;
				} else if ( direction == 3 ) {
					ocean [ yPlacement-1+x ] [ xPlacement-1 ] [ 1 ] = '#' ;
					ocean [ yPlacement-1+x ] [ xPlacement-1 ] [ 4 ] = shipType ;
				} else if ( direction == 4 ) {
					ocean [ yPlacement-1-x ] [ xPlacement-1 ] [ 1 ] = '#' ;
					ocean [ yPlacement-1-x ] [ xPlacement-1 ] [ 4 ] = shipType ;
				} else {
					ocean [ yPlacement-1 ] [ xPlacement-1+x ] [ 1 ] = '#' ;
					ocean [ yPlacement-1 ] [ xPlacement-1+x ] [ 4 ] = shipType ;
				}
			}
			system ( "clear" ) ;
		}		
	}
}

void playAgain ( bool &again , int &player , bool &game ) {
	char play ; 
	system ( "clear" ) ;
	cout << "Do you want to play again? Y/N : " ;
	cin >> play ;
	if ( play != 'Y' && play != 'y' ) {
		again = false ;
	} else {
		player = 0 ;
		game = true ;
		system ( "clear" ) ;
	}
}

void header ( bool &again ) {
	char play ;
	
	system ( "clear" ) ;
		
	char welcomeMessage [9] [80] ;

	// Simple variables for counting and filtering through array
	int v ; // v for vertical
	int h ; // h for horizontal
	// Variables for changing the way it looks
	int s = 9 ; // s for shift because it shifts the word left or right to center it
	char c = 'O' ; // c for character to change the character used to form the letters for the banner
	char e = ' ' ; // e for empty to change the character used to fill in the empty spaces
	char b = '=' ; // b for border to change the border
	
	// Making welcome banner
	
	for ( v = 0 ; v < 8 ; v++ ) {
		for ( h = 0 ; h < 80 ; h++) {
			if (( v > 0 && v < 6 ) && ( h == 0+s || h == 4+s || h == 8+s )) { 
				welcomeMessage [ v ] [ h ] = c ;
			} else if (( v == 6 ) && (( h > 0+s && h < 4+s ) || ( h > 4+s && h < 8+s ))) { // Makes the W
				welcomeMessage [ v ] [ h ] = c ;
			} else if ((( v > 0 && v < 7 ) && ( h == 11+s )) || (( v == 1 || v == 6 || v == 4 ) && ( h > 11+s && h < 17+s ))) { // Makes the E
				welcomeMessage [ v ] [ h ] = c ;
			} else if (( v > 0 && v < 7 && h == 19+s ) || ( v == 6 && h > 19+s && h < 25+s )) { // Makes the L
				welcomeMessage [ v ] [ h ] = c ;
			} else if (( v > 1 && v < 6 && h == 27+s ) || (( v == 2 || v == 5 ) && ( h == 33+s )) || (( v == 1 || v == 6 ) && ( h > 27+s && h < 33+s ))) { // Makes the C
				welcomeMessage [ v ] [ h ] = c ;
			} else if ((( v > 1 && v < 6 ) && ( h == 36+s || h == 42+s )) || (( v == 1 || v == 6 ) && ( h > 36+s && h < 42+s ))) { // Makes the O
				welcomeMessage [ v ] [ h ] = c ;
			} else if ((( v > 0 && v < 7 ) && ( h == 45+s || h == 53+s )) || (( v == 2 ) && ( h == 46+s || h == 52+s )) || (( v == 3 ) && // Makes the M
			( h == 47+s || h == 51+s )) || (( v == 4 ) && ( h == 48+s || h == 50+s )) || (( v == 5 ) && ( h == 49+s ))) { 
				welcomeMessage [ v ] [ h ] = c ;
			} else if ((( v > 0 && v < 7 ) && ( h == 56+s )) || (( v == 1 || v == 6 || v == 4 ) && ( h > 56+s && h < 62+s ))) { // Makes the E
				welcomeMessage [ v ] [ h ] = c ;
			} else if ( v == 0 || v == 7 ) {
				welcomeMessage [ v ] [ h ] = b ;
			}
			else {
				welcomeMessage [ v ] [ h ] = e ;
			}
		}
	}
	
	// Displaying banner
	cout << "\n\n\n\n\n\n" ;
	for ( v = 0 ; v < 8 ; v++ ) {
		for ( h = 0 ; h < 80 ; h++) {
			cout << welcomeMessage [ v ] [ h ] ;
		}
	}
	cout << "\n" ;
	
	cout << "This is BATTLESHIP! Do you want to play? Y/N : " << endl ;
	cin >> play ;
	if ( play != 'Y' && play != 'y' ) {
		again = false ;
	}
	system ( "clear" ) ;
}

void setGrids ( ARRAY ocean ) {
	for ( int y = 0 ; y < 10 ; y++ ) {
		for ( int x = 0 ; x < 10 ; x++ ) {
			for ( int z = 0 ; z < 6 ; z ++ ) {
				ocean [ y ] [ x ] [ z ] = '~' ;
			}
		}
	}
}

void display ( ARRAY ocean , int player ) {
	for ( int z = 0 ; z < player+2 ; z++ ) {
		cout << endl ;
		cout << "   1 2 3 4 5 6 7 8 9 10 X" << endl ;
		for ( int y = 0 ; y < 10 ; y++ ) {
			cout << setw(2) << y +1 ;
			cout << ' ' ;
			for ( int x = 0 ; x < 10 ; x++ ) {
				cout << ocean [ y ] [ x ] [ z ] << ' ' ;
			}
			cout << endl ;
		}
	}
}

void pause ( ) {
	for ( long x = 0 ; x < 1000000000 ; x ++ ) {
		continue ;
	}
}


