//Longtin Hang
//Tic-Tic-Toe player vs. computer

#include<iostream>
#include"graph1.h"
#include<string>
#include<ctime>

using namespace std;

//constant
const int MAX = 9;

//function prototype
int* displayTicTacToe(int* tempXCoords, int* tempYCoords);
void playGame(bool& goFirst, int* tempXCoords, int* tempYCoords, int* objects, int* pScore, int* cScore);
bool determineWinner(int temp[MAX], int tie);

int main()
{
	//declarations
	int* objects = NULL;
	int tempXCoords[MAX];
	int tempYCoords[MAX];
	int pScore = 0, cScore = 0;
	bool goFirst = true;
	char repeat;

	//display graphics
	displayGraphics();

	//initialize rand
	srand(time(0));

	do
	{
		//function statements
		objects = displayTicTacToe(tempXCoords, tempYCoords);
		playGame(goFirst, tempXCoords, tempYCoords, objects, &pScore, &cScore);

		//repeat program
		cout << "Would you like to repeat the program? (y/n): ";
		cin >> repeat;

		clearGraphics();

	} while (repeat == 'Y' || repeat == 'y');

	//delete dynamic allocated
	delete[] objects;
}

//function definitions

//displays the tic-tac-toeoo
int* displayTicTacToe(int* tempXCoords, int* tempYCoords)
{
	//declarations
		//dynamic allocated array
	int* objects = NULL;
	objects = new int[MAX];
	int i, j = 0, h = 1, k = 0;
	string fn = "";

	//display the background
	displayPNG("background.png", 0, 0);

	//number the locations
	for (i = 0; i < 9; i++)
	{

		//set the condition for the numbers to display from left to right
		if (i % 3 == 0)
		{
			j++;
			k = 0;
		}

		//convert int to string
		fn = to_string(h) + ".png";

		//display the numbers
		objects[i] = displayPNG(fn, 190 + (100 * k), 0 + (100 * j));

		//store coords
		tempXCoords[i] = 190 + (100 * (k++));
		tempYCoords[i] = 0 + (100 * j);

		//increment file number
		h++;
	}

	return objects;
}

//play game!
void playGame(bool& goFirst, int* tempXCoords, int* tempYCoords, int* objects, int* pScore, int* cScore)
{
	//declarations
	int i, j, obj;
	int pTemp[MAX] = { 0 };
	int cTemp[MAX] = { 0 };
	int temp[MAX];
	int tie = 0;
	bool duplicate;
	bool winner = false;

	//get coords
	for (i = 0; i < MAX; i++)
	{
		if (goFirst)
		{
			do
			{
				//get player number
				clearText();
				gout << setPos(270, 65) << setColor(0, 0, 0) << "Your Turn!!" << endg;
				gout << setPos(225, 375) << setColor(0, 0, 0) << "Please enter a number!!!" << endg;
				gout << setPos(100, 450) << setColor(0, 0, 0) << "Player Score: " << *pScore << endg;
				gout << setPos(400, 450) << setColor(0, 0, 0) << "Computer Score: " << *cScore << endg;
				cin >> pTemp[i];
			} while (pTemp[i] < 1 || pTemp[i] > 9);

				//check for duplicates
			do
			{
				//store player temp in temp for both players
				temp[i] = pTemp[i];
				duplicate = false;
				for (j = 0; j < i; j++)
				{
					if (temp[i] == temp[j])
					{
						clearText();
						gout << setPos(200, 375) << setColor(0, 0, 0) << "Number Has Been used! Try again!" << endg;
						gout << setPos(270, 65) << setColor(0, 0, 0) << "Your Turn!!" << endg;
						gout << setPos(100, 450) << setColor(0, 0, 0) << "Player Score: " << *pScore << endg;
						gout << setPos(400, 450) << setColor(0, 0, 0) << "Computer Score: " << *cScore << endg;
						cin >> pTemp[i];
						duplicate = true;
					}
				}

			} while (duplicate);

			//draw a circle
			obj = drawCircle(20, tempXCoords[temp[i] - 1] + 27, tempYCoords[temp[i] - 1] + 27);
			setColor(obj, 0, 255, 0);

			//remove objects
			Sleep(100);
			removeObject(objects[temp[i] - 1]);

			//determine if player wins
			winner = determineWinner(pTemp, tie);

			//breaks out if player wins and let comp go first next around
			if (winner)
			{
				clearText();
				*pScore += 1;
				goFirst = false;
				gout << setPos(270, 65) << setColor(0, 0, 0) << "You won!!" << endg;
				gout << setPos(100, 450) << setColor(0, 0, 0) << "Player Score: " << *pScore << endg;
				gout << setPos(400, 450) << setColor(0, 0, 0) << "Computer Score: " << *cScore << endg;
				break;
			}

			//make goFirst to computer
			goFirst = false;
		}
		else
		{
			//Computer turns
				//display text
			clearText();
			gout << setPos(245, 65) << setColor(0, 0, 0) << "Computer's Turn!!" << endg;
			gout << setPos(250, 375) << setColor(0, 0, 0) << "Please Wait!!!" << endg;
			gout << setPos(100, 450) << setColor(0, 0, 0) << "Player Score: " << *pScore << endg;
			gout << setPos(400, 450) << setColor(0, 0, 0) << "Computer Score: " << *cScore << endg;

			//get rand number
			Sleep(1000);
			cTemp[i] = (rand() % 9) + 1;

			//check for duplicates
			do
			{
				//store computer temp in temp for both players
				temp[i] = cTemp[i];

				duplicate = false;
				for (j = 0; j < i; j++)
				{
					if (temp[i] == temp[j])
					{
						cTemp[i] = (rand() % 9) + 1;
						duplicate = true;
					}
				}

			} while (duplicate);

			//draw X
			obj = drawLine(tempXCoords[temp[i] - 1] + 18, tempYCoords[temp[i] - 1] + 10, tempXCoords[temp[i] - 1] + 40, tempYCoords[temp[i] - 1] + 40, 1);
			setColor(obj, 255, 0, 0);
			obj = drawLine(tempXCoords[temp[i] - 1] + 40, tempYCoords[temp[i] - 1] + 10, tempXCoords[temp[i] - 1] + 18, tempYCoords[temp[i] - 1] + 40, 1);
			setColor(obj, 255, 0, 0);

			//remove objects
			Sleep(100);
			removeObject(objects[temp[i] - 1]);

			//determine if computer wins
			winner = determineWinner(cTemp, tie);

			//break if computer wins and let player go first next around
			if (winner)
			{
				clearText();
				*cScore += 1;
				goFirst = true;
				gout << setPos(270, 65) << setColor(0, 0, 0) << "You lost!!" << endg;
				gout << setPos(100, 450) << setColor(0, 0, 0) << "Player Score: " << *pScore << endg;
				gout << setPos(400, 450) << setColor(0, 0, 0) << "Computer Score: " << *cScore << endg;
				break;
			}

			//make goFirst to player
			goFirst = true;
		}

		//display tie 
		tie++;
		if (tie == 9)
		{
			clearText();
			gout << setPos(295, 65) << setColor(0, 0, 0) << "Tie!!" << endg;
			gout << setPos(100, 450) << setColor(0, 0, 0) << "Player Score: " << *pScore << endg;
			gout << setPos(400, 450) << setColor(0, 0, 0) << "Computer Score: " << *cScore << endg;
		}
	}

}

//determine the winner
bool determineWinner(int temp[MAX], int tie)
{
	//declarations
	bool winner = false;

	//compare the inputs to see if there's a winner
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			for (int h = 0; h < MAX; h++)
			{
				if (temp[i] == 1 && temp[j] == 2 && temp[h] == 3)
					winner = true;
				else if (temp[i] == 1 && temp[j] == 4 && temp[h] == 7)
					winner = true;
				else if (temp[i] == 1 && temp[j] == 5 && temp[h] == 9)
					winner = true;
				else if (temp[i] == 5 && temp[j] == 4 && temp[h] == 6)
					winner = true;
				else if (temp[i] == 5 && temp[j] == 8 && temp[h] == 2)
					winner = true;
				else if (temp[i] == 5 && temp[j] == 3 && temp[h] == 7)
					winner = true;
				else if (temp[i] == 9 && temp[j] == 8 && temp[h] == 7)
					winner = true;
				else if (temp[i] == 9 && temp[j] == 3 && temp[h] == 6)
					winner = true;
			}
		}
	}

	return winner;
}
