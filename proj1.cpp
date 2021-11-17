//Title: proj1.cpp
//Author: Kirtan Thakkar
//Date: 9/23/2021
//Description: UMBC word search game
//Class/section: CMSC 202, sec 20 (Fall21)
//E-mail: k238@umbc.edu

// ***********************************************************


#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//****** prototypes ******

void LoadFile(char arr[][15], string words[]);
void Display(char letter[][15], string words[]);
string BuildWord(char letter [][15], int stX, int stY, int edX, int edY);
bool check(string wrd, string words[]); 
string GetName();

//****** global constants ******

const int XSIZE = 15;
const int YSIZE = 15;
const int WORDS = 10;
const int BACK2BASE = -1;
//******* Main function ******

int main (){

  
  char letter[YSIZE][XSIZE];
  string words[WORDS];

  
  LoadFile(letter, words);


  return 0; 
}

//****** Other functions ******

void LoadFile (char letter[][XSIZE], string words[]){ // Loads the file and intializes 2D and 1D arrays 
  
  ifstream inputFile;

  int sx, sy, ex, ey, input = -1, count = 0;
  int lettersCount = 0, wordsCount = 0;
  string data, wordMade;
  char ch;


  inputFile.open(GetName());
  
  if(inputFile.is_open())// this segment reads the file and puts all the letters into a 2D array
    {

      for(int y = 0; y < YSIZE; y++)
	{

	  for(int x = 0; x < XSIZE; x++)
	    {
		  
	      inputFile >> ch;

	      if(ch != ' ') 
		{		      
		   letter[y][x] = ch;
		   lettersCount++;
		 }

	    }
	}


      for(int w = 0; w < WORDS; w++) // intializes words array
	 {
	    inputFile >> data;
	    words[w] = data;
	    wordsCount++;
	  }
	  

	  inputFile.close();
	
          
    }else{

    cout <<"Error: Failed to load the file, please input a file to run the program.." << endl;
    
  }


  cout << lettersCount << " letters imported." << endl;
  cout << wordsCount << " words imported." << endl;



  do{ // takes user input

   Display(letter, words);
     
     while (input > 14 || input < 0)
       {
	 cout << "What is the starting X Y (separated by space)? " << endl;
	 cin >> input;

	 if (input > 14 || input < 0)
	   {
	     cout << "Error: invalid input. Try again (interger between 0 - 14)" << endl;
	   }

       }

     sy = input;

     cin >> input;

     sx = input;

     input = BACK2BASE;

     while(input > 14 || input < 0)
       {
	 cout << "What is the ending X Y (separated by space)? " << endl;
	 cin >> input;

	 if (input > 14 || input < 0)
	   {
	     cout << "Error: invalid input. Try again (interger between 0 - 14)" << endl;
	   }
       }
     
     ey = input;

     cin >> input;

     ex = input;

     input = BACK2BASE;
     
     wordMade = BuildWord(letter, sx, sy, ex, ey);

     
     if(check(wordMade, words)) // checks if the word built is one of the words from word bank
       {
	 
	 cout << "You found the word " << wordMade << "!" << endl;
	 
       }else{

       cout << "No such a word, as \"" << wordMade << "\" exist in word bank! " << endl;

     }

     count++;

   }while(count < WORDS);

 cout << "Thank you for playing UMBC Word Search!" << endl;
   
}


void Display(char letter[][XSIZE], string words[]){ //Displays the letter grid and word list

 int num = 0;
    
  while(num != XSIZE)
    {
      if(num > 1)
	{
	  cout << num << "   ";
	}else{	
	cout << num << "   ";
      }
      num++;

    }
  
  cout << endl;
    
  for(int y = 0; y < YSIZE; y++ )
    {
      if(y < 10)
	{
	  cout << y << "   ";
	}else{
	cout << y << "  ";
      }

      
      for(int x = 0; x < XSIZE; x++)
	{

	  cout << letter[y][x] << "   ";

	}
      
      cout << endl;      
    }

  cout <<endl;
  
  cout << "************** REMAINING WORDS***************" << endl;
  
 for(int w = 0; w < WORDS; w++)
    {
      if(words[w] != " ")
	{
	  cout << words[w] << endl;
	}
    }

 cout << endl;
  
}

string BuildWord(char letter [][XSIZE], int stX, int stY, int edX, int edY) {

  // builds a word, based on the indexes user requested
  
  int xAxis = stX, yAxis = stY, at = 0, checkCondition = 0;
  bool up = false, down = false, right = false, left = false;
  string wordBuilt;

  // Checks for the directions, (up, down, left, right, or diagnal)
  
  if(stY > edY) // ^ (+) 0 (-) v
    {      
      up = true; // (-)
      checkCondition++;
      
    }else if (stY < edY){ // ^ (+) 0 (-) v
    
    down = true; // (+)
    checkCondition++;
  }

  if(stX > edX)// <-- (-) 0 (+) -->
    {
      
      left = true; // (-)
      checkCondition++;
      
    }else if(stX < edX){ // <-- (-) 0 (+) -->

    right = true; // (+)
    checkCondition++;
    
  }

 // builds a word for the directions - up, down, left, and right (No diagnals)
  //************ X ************
  
  if(checkCondition == 1)
    {
      if(up)
	{
	  
	  for(int y = stY; y >= edY; y--) // UP
	    {
	      wordBuilt += letter[y][xAxis];
	      at++;
	    }

	 
	}else if(down){ 

	for(int y = stY; y <= edY; y++) // Down
	  {
	    wordBuilt += letter[y][xAxis];
	    at++;
	  }
    
      }else if(left){
    
	for(int x = stX; x >= edX; x--) // Left
	  {  
	    wordBuilt += letter[yAxis][x];
	    at++;
	  }

      }else if(right){
    
	for(int x = stX; x <= edX; x++) // Right
	  {
	    wordBuilt += letter[yAxis][x];
	    at++;
	  }
    
      }
    }

  // builds the words that are diagnals
  
  if(checkCondition == 2)
    {
      if(up && right){

	while(yAxis >= edY && xAxis <= edX) // Up-right
	  {
	    wordBuilt += letter[yAxis][xAxis];
	    yAxis--;
	    xAxis++;
	    at++;
	  }

    
      }else if(up && left){

	while(yAxis >= edY && xAxis >= edX) // Up-left
	  {
	    wordBuilt += letter[yAxis][xAxis];
	    yAxis--;
	    xAxis--;
	    at++;
	  }



      }else if(down && left){

	while(yAxis <= edY && xAxis >= edX) // Down-left
	  {
	    wordBuilt += letter[yAxis][xAxis];
	    yAxis++;
	    xAxis--;
	    at++;
	  }




      }else if(down && right){

	while(yAxis <= edY && xAxis <= edX) // Down-right
	  {
	    wordBuilt += letter[yAxis][xAxis];
	    yAxis++;
	    xAxis++;
	    at++;
	  }


      }
    }
  
      return wordBuilt;
}


bool check(string wrd, string words[])
{

  // checks the word in the word list
  
  bool matched = false;
  string reverse;

  
  for(int w = 0; w < WORDS; w++)
    {
       if(words[w] != " ")
	 {
	   if(wrd == words[w]) // replaces the word with space
	     {
	       words[w] = " ";
	       return true;
	     }else{
		  
	     matched = false;
	   }
	   
	 }
    }
   
  return matched;
}


string GetName(){

  // lets user set a name
  
  string fileName;
  cout << "Welcome to UMBC Word Search" << endl;
  cout << "What is the name of then file you would like to load?" << endl;
  cin >> fileName;
  
  return fileName;
}
