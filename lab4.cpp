/**  
*  @file    lab4.cpp  
*  @author  Georgina Hutchins (hutcgb12)
*  @date    02/20/2014  
*  @version 1.0  
*
*  @brief CSC 112, Lab 4, Digital Signal Processing, Part 1
*
*  @section DESCRIPTION
*
*  This program performs various tasks on audio data, upon user's
*  request. After the program has loaded the audio data from the
*  user's file, the main menu will allow the user to choose 
*  from different options to perform tasks on the audio file.
*
*  @bug No known bugs
*
*/



#include <iostream>
#include "sound.h"
#include <cstdio>
#define MAX_SIZE 240000
using namespace std;



void clearScreen();


void myPause();


void displayMenu(int& option, bool& loaded);


void readFile(string fileName, short samples[], int MaxSize, int& numSamples);


void playSample(short samples [], int numSamples);


void displaySignal(int numSamples, short samples[]);


void adjustVolume(int numSamples, short samples[]);


void reverseAudio(int numSamples, short samples[]);



int main()
{
	int option;		///< Main menu options for user to select		
	bool loaded = false;	///< Boolean indicating if the file has been loaded
	string fileName;	///< Name of user input file	
	int numSamples;		///< Number of PCM samples (logical size of array)
	short samples[MAX_SIZE];///< Array of PCM samples
	int MaxSize = MAX_SIZE; ///< Maximum number of elements in samples (physical size)
	
	displayMenu(option, loaded);

	while (option != 0)
	{
		if (option == 1)
		{
			readFile(fileName, samples, MaxSize, numSamples);
			displayMenu(option, loaded);
		}
		if (option == 2 && loaded)
		{
			displaySignal(numSamples, samples);
			displayMenu(option,loaded);
		}
		if (option == 3 && loaded)
		{
			adjustVolume(numSamples, samples);
			displayMenu(option, loaded);
		}
		if (option == 4 && loaded)
		{
			reverseAudio(numSamples, samples);
			displayMenu(option, loaded);
		}
		else if (option == 5 && loaded)
		{
			playSample(samples, numSamples);
			displayMenu(option, loaded);
		}
		else if (loaded == false)
		{
			displayMenu(option, loaded);
		}

	}
	
	return 0;
}



/**
*  @brief clearScreen clears an Xterm window
*
*  @return void
*/
void clearScreen()
{
	 cout << char(27) << "[;H" << char(27) << "[2J" << '\n';
}



/**
*  @brief myPause pauses the program
*
*  @return void
*/
void myPause()
{
   cout << "Press return to continue. ";
   getchar();
   getchar();  
}



/**
*  @brief displayMenu creates a main menu for the user to select
*  from
*
*  @param option is the option (0-5) that the user enters
*  @param loaded indicates if the input file has been loaded
*
*  @return void
*/
void displayMenu(int& option, bool& loaded)
{
	clearScreen();

	cout << "      Digital Signal Processing Program" << '\n';
	cout << "      ---------------------------------" << '\n';
	cout << "1) Read audio data from file	4) Reverse audio" << '\n';
	cout << "2) Display signal		5) Play audio" << '\n';
	cout << "3) Adjust volume		0) Quit" << '\n' << endl;
	cout << " Enter option (0 - 5) - > ";
	cin >> option;
	
	if (option == 1 || option == 0)
	{
		loaded = true;
	}
}



/**
*  @brief readFile reads audio data from a file
*
*  @param fileName is the name of the file
*  @param samples is the array of PCM samples
*  @param MaxSize is the physical size of the array
*  @param numSamples is the number of PCM samples in the array (logical size)
*
*  @return void
*/
void readFile(string fileName, short samples[], int MaxSize, int& numSamples)
{
	clearScreen();
	cout << "Read PCM Data from File" << '\n';
	cout << "Enter .au file name ->  ";
	cin >> fileName;

	readAuFile(fileName, samples, MaxSize, numSamples);

	cout << "Reading the .au file: " << fileName << '\n';
	cout << numSamples << " samples read signal duration " << (numSamples / 8000.0) << '\n';
	myPause();

}



/**
*  @brief displaySignal will display a segment of the signal
*
*  @param numSamples is the logical size of the array
*  @param samples is an array of PCM samples
*
*  @return void
*/
void displaySignal(int numSamples, short samples[])
{
	clearScreen();
	int startIndex;		///< First index of segment to be displayed
	int stopIndex;		///< Last index of segment to be displayed
	int numSymbol;		///< Number of symbols which represent sample value
	short temp;		///< Temporary variable to interchange start and stop indexes
	
	cout << "Signal Display" << '\n';
	cout << "Enter the start and stop index for the segment" << '\n';
	cout << "values range from 1 to " << numSamples << '\n' << '\n';
	cout << "Enter the start index -> ";
	cin >> startIndex;
	cout << "Enter the stop index -> ";
	cin >> stopIndex;
	cout << '\n';
	
	if (startIndex > stopIndex)
	{
		temp = startIndex;
		startIndex = stopIndex;
		stopIndex = temp;
	}

	for  (int i= startIndex; i < stopIndex; i++)
	{
		cout << i << '(' << samples[i] << ") : ";
		numSymbol = (samples[i] / 100);

		if (numSymbol > 0)
		{
			for (int j = 0; j < numSymbol; j++)
				cout << '>';
		}
		else if (numSymbol < 0)
		{
			numSymbol = (numSymbol * -1);
			for (int p = 0; p < numSymbol; p++)
				cout << '<';
		}
		else if (numSymbol == 0)
		{
			cout << ' ';
		}
		cout << '\n';
	}

	myPause();
}



/**
*  @brief adjustVolume is a function that prompts the user for 
*  a value to adjust the audio volume
*  @param numSamples is the logical size of the array
*  @param samples is an array of PCM samples
*
*  @return void
*/
void adjustVolume(int numSamples, short samples[])
{
	clearScreen();
	float input;		///< Value entered by the user to adjust volume

	cout << "Adjust Volume" << '\n';
	cout << "Anything less than 1.0 decreases the volume, anything greater increases the volume" << '\n';
	cout << "Enter any value between 0 and 10 to adjust the volume: ";
	cin >> input;

	if (input > 10.0 || input < 0.0)
	{
		cout << "Error" << '\n';
		cout << "Enter a valid value between 0 and 10 to adjust the volume: ";
		cin >> input;
	}

		if (input < 1.0 && input > 0.0)
		{
			for(int i = 0; i < numSamples; i++)
			{
				samples[i] = (samples[i] * input);
			}
		cout << "The volume has been decreased" << '\n';
		}

		else if (input >= 1.0 && input <= 10.0)
		{
			for(int j = 0; j <= numSamples; j++)
			{
				samples[j] = (samples[j] * input);
			}
		cout << "The volume has been increased" << '\n';
		}

	myPause();
}



/**
*  @brief reverseAudio reverses the PCM samples in the array
*
*  @param numSamples is the logical size of the array
*  @param samples is an array of PCM samples
*
*  @return void
*/
void reverseAudio(int numSamples, short samples[])
{
	short temp;			 ///< Temporary variable to reverse values
	int lastIndex = (numSamples - 1);///< Last index of the array

	for(int i = 0; i < (lastIndex/ 2); i++)
	{
		temp = samples[i];
		samples[i] = samples[lastIndex - i];
		samples[lastIndex - i] = temp;
	}

	cout << "Total numer of samples in the signal: " << numSamples << '\n';
	cout << "Signal duration: " << (numSamples / 8000.0) << '\n';

	myPause();
}



/**
*  @brief playSample plays the PCM audio data in the array
*
*  @param samples is an array of PCM samples
*  @param numSamples is the logical size of the array
*
*  @return void
*/
void playSample(short samples[], int numSamples)
{
	playPCMsamples(samples, numSamples);
	myPause();
}













