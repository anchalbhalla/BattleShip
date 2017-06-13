/* Name - Anchal Bhalla  
   Id - 5261211 
*/
#include <iostream>  
#include <cstdlib> 
#include <ctime>  // used for generating different numbers each time 
#include <cctype> // used for toupper 
#include <iomanip> // libaray used for setw and setfill 
using namespace std ;  

//global variables  
int a,b,c,d,e ;                      // variables used as counters in the sankship function to increment with each hit  
int countervar=0 ;                  // a counter used for calling out coordinates to hit user's grid   
int plays ;                        // a counter used in the computer moves function to keep track of where to call out for a hit next 
int storedarr[2] ;                  // Array to store the row and column which will be used globally when the computers call it out randomly  
int rowup, columnup, rowdown, columndown,  rowright, columnright, rowleft, columnleft;  // used in the go up go down etc program to set rows and columns  
int goingup, goingdown, goingright, goingleft = 0;   // used in the go up go down etc as counters 
int computerpoints =0 ;                             // to keep track of the computers hits on the user's grid
int playerpoints =0 ;                              // to keep track of user's hits on the computer's grid 

// Global arrays, that is the separate grids to keep track of 
char DisplayArray[20][20] ;        //Displays to the user the where there is a hit or miss 
char UserArray [20][20] ;         //Array for the computer to keep track of hits and miss on user grid 
char ShipPlArray [20][20] ;      //Array for placing the ships 
char TrackerArray [20][20] ; 	//Array for the computer to keep track of its ships, hits and miss 
char Shipsunkarr [20][20] ;    //This grid will keep track of different battleships with differnt letters and will be used to check whether the ship has sank 	
char shipname [5] = {'A', 'B', 'C', 'D', 'E'} ; // Array to hold the ships named as A, B, C, D - carrier, battleship, cruiser, submarine, destroyer
	
//Function prototypes
void IntialAssignment (char a[20][20], char emty) ; //function to assign a particular array to 'X' that is empty 
void DisplayGrid (char a[20][20]) ;                // display the grid function 
void ShipPlacer () ;                              // this function places the battleship accordingly on the ShipPlArray array 
int spacechecker (int row, int column, int ship[], int i , int direction) ;  //used in the ShipPlacer to check if there is enough space for a ship to be placed
void PlayUser () ;                                //function for the user's turn to play 
bool calledcor (char a[20][20],int ro, int col) ; // to check whether the coodinates called havent been called before 
int SankShip (int ro, int col) ;  // to check if the ship has sunk or not 
void computercall () ;           // computer's turn to play 
void computermoves () ;         // function for dertermining where the computer should go next up, down, right, left to hit the user's grid 
void GoUp () ;                 // function for going up for the computer to hit user's grid 
void Godown () ;              // function for going down for the computer to hit user's grid 
void Goright () ;            // function for going right for the computer to hit user's grid 
void Goleft () ;            // function for going left for the computer to hit user's grid 
void DisplayScores () ;    // Display the scores at the end of the game 


int main () 
{ 
	char emty = 'X' ;  
	
	IntialAssignment (DisplayArray, emty) ;  
	IntialAssignment (UserArray, emty) ; 
	IntialAssignment (ShipPlArray, emty) ; 
	IntialAssignment (TrackerArray, emty) ;  
	IntialAssignment (Shipsunkarr, emty) ; // Assigning all the arrays to 'X' that is empty  
	ShipPlacer () ;    // placing all the battleships for the computer 


	cout << "***************************Welcome to the BattleShip Game*************************** " << endl <<endl ;
	DisplayGrid(DisplayArray) ;  
	cout << endl << endl ;  
	
	
	while (computerpoints<17 && playerpoints<17) // play until either one of them reaches 17 hits that is all ships sank 
			{
			PlayUser () ;    
			computercall ()  ;  
			system("cls");                 // to clear the screen 
			DisplayGrid(DisplayArray) ;
	  		}   
	  		
	  	 DisplayScores (); 
	system ("pause") ;
	return 0 ; 

}  

void IntialAssignment (char a[20][20], char emty) 
{ 

	for (int i=0; i<20; i++) 
	{
		for (int j=0 ; j<20; j++) 
		
		{
		  a[i][j] = emty ;         // assigning all the 20x20 grid elements to empty that is 'X' 
		
		} 
	
	}
}

void DisplayGrid (char a[20][20]) 
{ 
	char letter = 'A' ;                   // column starting from 'A' 
	cout << "   | "<< letter << " | "; 
	for (int k = 1 ; k<20; k++)          // till 20 letters that is 'T' 
	{
		char r = letter+k ; 
		cout << r << " | " ;   
	}
	cout << endl; 
	for (int i=0; i<20; i++) 
	{
		cout << "------------------------------------------------------------------------------------ " <<endl;   
		cout <<setw(2) << setfill(' ')<< i+1 << " | "; // used for setting the width properly and all single numbers a space before them 
		 
		for (int j=0 ; j<20; j++) 
		
		{
			cout << a[i][j] << " | " ;   // printing the grid elements 
		} 
		cout << endl ; 
	}
} 


void ShipPlacer () 
{ 
	int ship[5] = {5,4,3,3,2} ;   // array for storing the ship sizes 

	srand (time(NULL)) ;
	int row ; 
	int column ; 
	int direction;  
	for (int i=0; i<5; i++)    // for loop will go through all the  5 size sizes in the ship array  
	{ 
		row = rand() %20 ;    
		column = rand() %20 ;  
		direction = rand() %2 ;  // generates a row, column, and direcion (to go vertically(0) or horizontally(1)) for each ship 
		
		while (!spacechecker (row,column, ship,i, direction ) ) // checks if there is enough space for a ship to be placed a certain row and column   
		{ 
			row = rand() %20 ;  
			column = rand() %20 ;  
		} 
		
		for (int j =0; j<ship[i] ; j++)  //goes through each position once and places a 'B' there checking for how much space each ship occupies and goes those many times  
		{
			ShipPlArray[row][column] = 'B' ;  
			TrackerArray[row][column] = 'B' ;   
			Shipsunkarr[row][column] = shipname[i] ; // also it places different names for the ships each time accordingly to check if a whole ship is sunk at a later stage 
			
			if (direction ==0) 
				row++ ; // if going vertically increment the row to go down 
			else 
				column++ ; // else increment column to go right 
		}
	}
} 


int spacechecker (int row, int column, int ship[], int i, int direction ) 
{   
	if (direction ==1) // if the direction is horizontal 
	{ 	
		for (int k=0; k<ship[i]; k++)  // from the beginning to the amount of space for the ship 
		{
			if(column >= 20)        // check if there are enough columns in the row to put the entire ship 
				return 0;
			
			if (ShipPlArray[row][column] =='X')  // check if all of them are empty and no battleship is there from before 
				column++ ;                          // increment column to check the next column 
			
			if(ShipPlArray[row][column]=='B')
				return 0;
		}
		
		return 1 ;  
	}
 
	else     // else if the direction is vertical 
	{  
		
		for (int k=0; k<ship[i]; k++) 
		{
			if(row >= 20) // check if there is enough space to put the ship more down 
			return 0;
			
			if (ShipPlArray[row][column] =='X')    // check if all of them are empty and no battleship is there from before 
				row++ ; 
			
			if(ShipPlArray[row][column]=='B')   // increment column to check the next column 
				return 0;
		}
		return 1 ;  

	}
}  


void PlayUser () 
{ 
	char x ; // for entering the x coordinate that is the column 
	int y ;   // for entering the y coordinate that is the row 
	int col ; 
	int ro ; // converting them to rows and columns in integer form 
	
	cout << "Users turn to play " <<endl;
    int turn = 0 ;  // counter for going for the first time 
	do 
	{ 
		if (turn!= 0) // if it is the first turn dont display invalid 
			cout << "Invalid coordinates \nEnter the coordinates again " << endl ; 
		cout << "Enter coordinates (x y) and enter X to exit game   "  ;
		cin >> x ;   
		x= toupper(x) ;   
		if (x== 'X') // if user enters 'X' then exit from the game and show the points till now  
		 { 
			 system("cls");
			 cout<< "This game is now exiting..."<<endl; 
			 DisplayScores () ;
			 exit(0) ;	// used for ending the entire program
		 } 
		 	  
		cin >> y ; // enter y coordinate 
		while(cin.fail()) // if not appropriately entered then  
		{ 
			cout <<"Invalid coordinates \nEnter the coordinates again " <<endl;
			cin.clear() ; // clear what all has been entered for the y coordinate 
			cin.ignore(256, '\n');  // ignore a certain number of characters entered 
			cin>> x;               // and enter all the coordinates again 
			while(isdigit(x))     //if x is not a character enter again 
			{ 
				cout<<" Invalid coordinates \nEnter the coordinates again " <<endl; 
				cin.clear(); 
				cin.ignore(256, '\n'); 
				cin>>x ;
			} 
			cin>>y ;  
			x= toupper(x) ;   // chanage x to upper case 
		if (x== 'X') 
		 { 
			 system("cls");
			 cout<< "This game is now existing..."<<endl; 
			 DisplayScores () ;
			 exit(0) ;	
		 } 
	
		} 
		
		 
		col= static_cast<int>(x) ; // typecasting x to interger   
		col -=65 ;                // and -65 to make a number 
		
		ro = y-1 ;    
		turn++ ;                // increment the turn at the end
		while(x>'T' || y > 20 || y<1 ) // if the coordinates entered are in the range else you enter them again 
			{
				cout << "Invalid coordinates \nEnter the coordinates again " << endl ; 
				cout << "Enter coordinates  "  ;
			cin >> x ;   
			cin >> y ;   
			x= toupper(x) ;   
		 
		col= static_cast<int>(x) ;  
		col -=65 ;   
		
		ro = y-1 ; 
			
		}
 	} while (calledcor(TrackerArray, ro, col)) ; // and also check whether the coodinates were called before or not 
	
	
	if (TrackerArray[ro][col]=='B')  // if there is a 'B' in the grid from before says its a hit 
	 {
	 	DisplayArray[ro][col]= 'H' ; 
	 	TrackerArray[ro][col]= 'H' ;  
	 	cout << "HIT! " << endl ; 
		 playerpoints++ ;  // and increment player's points 
	 }
	 
	else 
	{ 
		DisplayArray[ro][col]= 'M' ;  // if its a miss then say a miss and update the tracker array 
	 	TrackerArray[ro][col]= 'M' ; 
	 	cout << "MISS! " << endl ; 
	} 

	if (TrackerArray[ro][col]== 'H' ) // if it was a hit you also check whether it was a sunk ship or not 
	{
		if (SankShip (ro, col)) 
			{	cout << "Ship has sunk" <<endl  ;  
				if (a==5) 
					cout <<"Carrier sank "<<endl ; // a is carrier - space 5
				else if (b==4) 
					cout << "Battleship sank "<<endl ;  //b is battleship - space 4 
				else if (c==3) 
					cout<< "Cruiser sank "<<endl ;  // c is cruiser - space 3 
				else if (d==3) 
					cout << "Submarine sank "<<endl ; //d is submarine - space 3 
				else if (e==2) 
					cout << "Destroyer sank" <<endl;  // e is destroyer - space 2 
				
			} 
} 
}


bool calledcor (char a[20][20],int ro, int col) 
{ 
	if (a[ro][col]=='H' ||a[ro][col]=='M' ) // to check whether the coordinate is already a hit or miss if yes then true else false 
	return true ;  
	else 
	return false ; 
}  


int SankShip (int ro, int col) 
{ 

	if (Shipsunkarr[ro][col]=='A') // if ship is a 'A' that is carrier then increment the counter for it 
		{ 
			a++ ; 
			if (a==5)  //if already all its spaces have been hit then return true that is it has been sunk 
			{
				
				return 1 ; 
				a==0 ;   // and set it to 0 ; 
			} 
			else 
				return 0 ;
		}	  
	else if (Shipsunkarr[ro][col]=='B') // if ship is a 'B' that is battleship then increment the counter for it 
		{ 
			b++ ; 
			if (b==4)  // if hit 4 times then sunk 
			{ 
			
				return 1 ; 
					b==0 ;  	
			} 
			else  
				return 0 ; 
		}	  
	else if (Shipsunkarr[ro][col]=='C') // if ship is a 'C' that is crusier then increment the counter for it 
		{ 
			c++ ; 
			if (c==3)  
			{ 
			
				return 1 ; 	 
					c==0 ;
			} 
			else  
				return 0 ; 
		}	   
	else if (Shipsunkarr[ro][col]=='D') // if ship is a 'C' that is submarine then increment the counter for it 
		{ 
			d++ ; 
			if (d==3)  
			{ 
			
				return 1 ; 	 
					d==0 ; 
			} 
			else  
				return 0 ; 
		}	   
	else if (Shipsunkarr[ro][col]=='E') // if ship is a 'E' that is destroyer then increment the counter for it 
		{ 
			e++ ; 
			if (e==2)  
			{ 
			
				return 1 ; 	  
					e==0 ;
			} 
			else  
				return 0 ; 
		}	   
	
}  


void computercall () 
{ 
	int row, col ;
	char option ;     // this for taking in the hit miss or sunk option from the user 
	char coldisplay ; // used to for displaying the character column 	
	if (countervar==1) // if countervar is equal to 1 that is if there was a hit before then move on to the computermoves function 
	{ 
		computermoves() ;	  
	} 
	else if (countervar==0) // if there was no hit before then generate a row and column to hit 
	{ 
		row = rand()%20 ; 
		col= rand()%20 ;  
		
		while (row==0 || col ==0) // this condition is set so that 0 that is an invalid row and column is not called out 
		{ 
			row = rand()%20 ; 
			col= rand()%20 ;
		} while (calledcor(TrackerArray, row, col)) ; // and it is not a called out coordinated before 
	
		storedarr[0]=col;  // first element is a column 
		storedarr[1]=row;  
		coldisplay = 65+storedarr[0] ; // to display the alphabetical column we add 65 to (ASCII code for 'A') 
		cout << "Computer calls out : "<< coldisplay <<	 storedarr[1] << endl ; 
		cout << "Enter option (H - Hit, M - Miss, S - Hit and Sunk) " <<endl ; 
		cin>> option ; 
		option = toupper(option) ;   // convert the option entered to a upper case letter  
	
		while(option!='M'&& option!='H'&&option!='S') // to check whether the letter entered was a h m or s, else u ask again until correct letter entered 
	{ 
		cout << "Invalid " <<endl; 
		cout << "Enter option (H - Hit, M - Miss, S - Hit and Sunk) " <<endl;
		cin >> option ;  
		option = toupper(option) ; 
	} 
	
		if(option=='H') 					//if randomly generated coodinate was a hit then
			{
				plays=0;  					// set plays to 0 that is first go to the goup function  
				countervar=1 ;   			// and set the global variable to 1 that is everytime it comes it to this function it can start directly where it left 
				UserArray[row-1][col]='H';  // place a hit on the user grid 
				computerpoints++ ; 			// increment computer's points 
			} 
		if(option=='M') 
		{ 
			UserArray[row-1][col]='M';  	// if it was a miss then place a miss on the user grid and start over next time when reaches this function 
		}
		
	}
} 

void computermoves () 
{ 
	if (plays==0) 		//0 for the goup function 
		GoUp () ; 
	else if (plays==1) // 1 for the godown function 
		Godown () ;  
	else if (plays==2) // 2 for the goright function 
		Goright () ; 
	else if (plays==3) // 3 for the goleft function 
		Goleft () ;	
}


void GoUp () 
{  
	char displaycol2 ;  // display alphabetical letter 
	char option ;      // user enters hit miss or sunk (h, m, s) 
	
	if (goingup==0)   // a counter set if going up for the first time (0) 
{ 
		columnup = storedarr[0] ; // then it stores the array in columns and rows 
		rowup = storedarr[1] ;  
		goingup = 1 ;            // and sets going up to 1 that is next time will not be the first time 
}
	 
	rowup-- ;     // decrement the rows as its going up 
	if (rowup<1)  // a check to see if it doesnt cross the limit that is 1 
	{ 
		plays = 1 ;  
		goingup=0;  
		Godown () ; 
		return ;	// if it does then it sets plays to 1 that is it will go down call calls out the godown function and exists the function, reseting variables for this function that is goingup
	}
	displaycol2 = 65+columnup ;  
	cout << "Computer calls out : "<< displaycol2 << rowup <<endl ;  
	cout << "Enter option (H - Hit, M - Miss, S - Hit and Sunk) " <<endl;
	cin >> option ;  
	option = toupper(option) ;   
	
	while(option!='M'&& option!='H'&&option!='S') 
	{ 
		cout << "Invalid " <<endl; 
		cout << "Enter option (H - Hit, M - Miss, S - Hit and Sunk) " <<endl;
		cin >> option ; 
		option = toupper(option) ; 
	} 
	
		
	if (option=='M') 
	{
		plays = 1 ;   
		UserArray[rowup-1][columnup]='M'; // if it is a miss then it has to start hitting from down the next time so plays =1 to go down 
	}	
	if (option=='S') 
	{
		countervar = 0 ;  
		plays=0;  
		goingup=0 ; 
		goingdown=0 ;  
		goingleft=0;  
		goingright=0 ;  
		UserArray[rowup-1][columnup]='H';  
		computerpoints++ ;   
		return;   // if the ship is sunk then reset all the counters for calling outcoordinates so we can start over and increment the computers points and exist out of the function and move forward
	}
	if(option=='H')
	{
		plays= 0 ; 
		UserArray[rowup-1][columnup]='H';  
		computerpoints++ ; // if it is hit you still have to keep going up 
	}


 }

void Godown () 
{  
	char displaycol2 ;  
	char option ;  

	if (goingdown==0)  // a counter set if going down for the first time (0)
{ 
		columndown = storedarr[0] ; 
		rowdown = storedarr[1] ;  // set the arrays to row and column 
		
}
	 
	rowdown++ ;   //increment the rows as rows are going down 
	if(rowdown>20) // check to see if the rows doesnt cross its limit that is 20 
	{ 
		plays = 0 ;  
		goingdown=0;
		GoUp () ; // if yes then go to the goup function 
		return ;	
	}
	displaycol2 = 65+columndown ;  
	cout << "Computer calls out : "<< displaycol2 << rowdown<<endl ; 
	cout << "Enter option (H - Hit, M - Miss, S - Hit and Sunk) "<<endl ; 
	cin >> option ;  
	option = toupper(option) ;  
		
	while(option!='M'&& option!='H'&&option!='S') 
	{ 
		cout << "Invalid " <<endl; 
		cout << "Enter option (H - Hit, M - Miss, S - Hit and Sunk) " <<endl;
		cin >> option ;  
		option = toupper(option) ; 
	} 

	if (goingdown==0) 
	{ 
		if (option=='M') 
			{
				plays=2 ;  
				UserArray[rowdown-1][columndown]='M'; 
			}
	}
	if (option=='S') 
	{
		countervar = 0 ;  
		plays=0 ;  
		goingup=0 ; 
		goingdown=0 ;  
		goingleft=0;  
		goingright=0 ;  
		UserArray[rowdown-1][columndown]='H';   
		computerpoints++ ;  
		return;    // resetting all the variables and starting from the beginning 
	}
	if(option=='H') 
	{
		plays= 1 ; 
		UserArray[rowdown-1][columndown]='H'; 
		computerpoints++ ;  
	}
	

goingdown = 1 ; // you set a 1 after this indicating it has been here once and no need to set the array of row and column again
 } 
 

void Goright () 
{  
	char displaycol2 ;  
	char option ; 	  

		if (goingright==0)
{ 
		columnright = storedarr[0] ; 
		rowright = storedarr[1] ;  
		goingright = 1 ; 
}
	 
	columnright++ ;      // as it moves to the right the column increases 
	if (columnright>19) // the limit here is 19 
	{ 
		plays = 3 ; 
		Goleft() ;  
		goingright=0;  	 // if it crosses u start moving backwards that is go the left 
		return ;
	}
	displaycol2 = 65+columnright ;  
	cout << "Computer calls out : "<< displaycol2 << rowright<<endl ;  
		cout << "Enter option (H - Hit, M - Miss, S - Hit and Sunk) "<<endl ;
	cin >> option ;  
	option = toupper(option) ;   
	
	while(option!='M'&& option!='H'&&option!='S') 
	{ 
		cout << "Invalid " <<endl; 
		cout << "Enter option (H - Hit, M - Miss, S - Hit and Sunk) " <<endl;
		cin >> option ;  
		option = toupper(option) ; 
	} 
	
	if (option=='M') 
	{
		plays = 3 ;   
		UserArray[rowright-1][columnright]='M';  // if a miss go the left function 
	}
	if (option=='S') 
	{ 
		countervar = 0 ;   
		plays=0;  
		goingup=0 ; 
		goingdown=0 ;  
		goingleft=0;  
		goingright=0 ;  
		UserArray[rowright-1][columnright]='H'; 
		computerpoints++ ;  
		return;
	}
	if(option=='H')
	{
		plays= 2  ;
 		UserArray[rowright-1][columnright]='H';   
 		computerpoints++ ;
	}

}
 
 void Goleft () 
{  
	char displaycol2 ;  
	char option ;  
	
	if (goingleft==0)
{ 
		columnleft = storedarr[0] ; 
		rowleft = storedarr[1] ;  
		
}
	 
	columnleft-- ;  // here the columns keep going backward so decrement the columns 
	if(columnleft<0)  // the limit here is 0 as 0 is the least that is 'A' = 0+65 
	{ 
		plays = 2 ; // start going to the right then eventhough it will a miss but we can go the next available one 
		Goright () ;  
		goingleft=0;  
		return; 
	}
	displaycol2 = 65+columnleft ;  
	cout << "Computer calls out : "<< displaycol2 << rowleft <<endl;
		cout << "Enter option (H - Hit, M - Miss, S - Hit and Sunk) " ;  
	cin >> option ;  
	option = toupper(option) ;  
	
	while(option!='M'&& option!='H'&&option!='S') 
	{ 
		cout << "Invalid " <<endl; 
		cout << "Enter option (H - Hit, M - Miss, S - Hit and Sunk) " <<endl;
		cin >> option ;  
		option = toupper(option) ; 
	}  
	
	if (option=='S') 
	{ 
		countervar = 0 ;   
		plays=0; 
		goingup=0 ; 
		goingdown=0 ;  
		goingleft=0;  
		goingright=0 ;  
		UserArray[rowleft-1][columnleft]='H'; 
		computerpoints++ ; 
		return;
	}
	if(option=='H') 
	{
		plays= 3 ; 
		UserArray[rowleft-1][columnleft]='H';  
		computerpoints++ ;  
	}
	
goingleft = 1 ;  // showing that it has been here in the function once 
 }


void DisplayScores () 
{ 
	if (playerpoints>computerpoints) 
	cout << " You won\nCongratulations"<<endl ; 
	else if (playerpoints<computerpoints) 
	cout << "Sorry you lost\nComputer has won "<<endl;  
	else if (playerpoints==computerpoints) 
	cout << "It was a tie between you and the computer "<<endl ; // comparing the user and computer points 
	
	
	cout << "Player scores are as follows : " << playerpoints << endl ;  
	cout << "      User Grid as follow     " << endl; 
	DisplayGrid (UserArray) ;  
	
	cout << "Computer scores are as follows : " << computerpoints << endl ;  
	cout << "      Battleship Placement Grid as follow     " << endl; 
	DisplayGrid (ShipPlArray) ;   // and displaying the battleship placement grid and user hit and miss grid for a comparsion 
	
	cout<< "This is the end of the game ..." << endl; 	
}
