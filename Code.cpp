#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include "help.h"
using namespace std;
const int AlienHeight = 40;
const int AlienWidth = 40;
const int AlienSpacing = 90;
void DisplayScreen(int initialX, int initialY, int score, int livesX[], int livesY, int lives) { // function to re render screen, ship, lives and score;
	myRect(18, 38, 1403, 902, 0, 0, 255);
	drawText(30, 550, 910, 255, 215, 0, "GUJJAR TAYYARA");
	drawText(20, 1420, 140, 255, 215, 0, "Score: ", true, score); // Initial score display
	//Draw Spaceship
	myEllipse(initialX, initialY, initialX + 20, initialY + 80, 255, 0, 0, 255, 0, 0);
	myLine(initialX - 40, initialY + 20, initialX, initialY + 20, 255, 0, 0);
	myLine(initialX - 40, initialY + 20, initialX, initialY + 40, 255, 0, 0);
	myLine(initialX + 20, initialY + 20, initialX + 60, initialY + 20, 255, 0, 0);
	myLine(initialX + 20, initialY + 40, initialX + 60, initialY + 20, 255, 0, 0);
	myLine(initialX - 20, initialY + 60, initialX, initialY + 60, 255, 0, 0);
	myLine(initialX - 20, initialY + 60, initialX + 4, initialY + 70, 255, 0, 0);
	myLine(initialX + 20, initialY + 60, initialX + 40, initialY + 60, 255, 0, 0);
	myLine(initialX + 16, initialY + 70, initialX + 40, initialY + 60, 255, 0, 0);
	myLine(initialX + 10, initialY, initialX + 10, initialY - 10, 255, 0, 0);
	// Draw lives (red spheres)
	drawText(20, 1420, 40, 255, 215, 0, "Lives:");
	for (int i = 0; i < lives; i++) {
		myEllipse(livesX[i], livesY, livesX[i] + 25, livesY - 25, 255, 0, 0, 255, 0, 0);
	}
}
int main() {
	bool Game = true;

	//Continue showing menu until exit
	while (Game) {
		int whichKey;
		int high1 = 0, high2 = 0, high3 = 0, high4 = 0, high5 = 0;
		//reading score into variables from file
		ifstream HiOut("HighScore.txt");
		if (HiOut.is_open()) {
			HiOut >> high1;
			HiOut >> high2;
			HiOut >> high3;
			HiOut >> high4;
			HiOut >> high5;
			HiOut.close();
		}
		int scores[6] = { high1,high2,high3, high4,high5,0 }; //saving varibales' values into array 
		bool menu = true; // for showing menu options until key is pressed for options
		bool newGame = false; // for new game
		bool resumeGame = false; // for resuming previous game
		bool highScore = false;// for showing high score
		// Initialisation for all variables used in game every time menu button is pressed and if new game button is pressed these value will be used but if resume button is pressed the these values are overwritten from file
		float AlienX[50], AlienY[50];
		bool AlienDestroyed[50] = { false };
		float AlienGridX = 30, AlienGridY = 50;
		float initialX = 700, initialY = 820;
		float alienDirection = 1;
		int lives = 3;
		int score = 0; // Initialize score
		int livesX[3] = { 1425, 1460, 1495 }; // X-coordinates for spheres
		int livesY = 110; // Y-coordinate for spheres
		float bulletX = -1;
		float bulletY = -1;
		int alienIndex = 0;
		// the purpose of both of follwing booleans were to save score to compare for highscores
		bool bottomReach = false;
		bool livesEnd = false;

		// displaying menu
		myRect(0, 0, 1600, 1100, 12, 12, 12, 12, 12, 12);
		drawText(70, 475, 20, 255, 215, 0, "GUJJAR TAYYARA");
		drawText(70, 477, 20, 255, 215, 0, "GUJJAR TAYYARA");
		drawText(70, 473, 20, 255, 215, 0, "GUJJAR TAYYARA");
		drawText(70, 475, 18, 255, 215, 0, "GUJJAR TAYYARA");
		drawText(70, 475, 22, 255, 215, 0, "GUJJAR TAYYARA");
		myRect(240, 390, 750, 470, 255, 215, 0, 12, 12, 12);
		drawText(30, 250, 400, 255, 215, 0, "NewGame: Press N");
		myRect(1090, 390, 1570, 470, 255, 215, 0, 12, 12, 12);
		drawText(30, 1100, 400, 255, 215, 0, "Resume: Press R");
		myRect(220, 640, 820, 720, 255, 215, 0, 12, 12, 12);
		drawText(30, 230, 650, 255, 215, 0, "HighScores: Press H");
		myRect(1130, 640, 1540, 720, 255, 215, 0, 12, 12, 12);
		drawText(30, 1140, 650, 255, 215, 0, "Exit: Press E");
		while (menu) {

			bool keyPressed = isKeyPressed(whichKey);
			if (keyPressed && whichKey == 9) { // for playing newgame
				menu = false;
				newGame = true;
				myRect(0, 0, 1600, 1200, 12, 12, 12, 12, 12, 12);
			}
			else if (keyPressed && whichKey == 8) { //for resuming game
				menu = false;
				resumeGame = true;
				myRect(0, 0, 1600, 1200, 12, 12, 12, 12, 12, 12);
			}
			else if (keyPressed && whichKey == 11) { //for exiting which will end the main function
				myRect(0, 0, 1700, 1200, 12, 12, 12, 12, 12, 12);
				drawText(100, 500, 400, 255, 0, 0, "Good Bye!");
				drawText(100, 502, 400, 255, 0, 0, "Good Bye!");
				drawText(100, 498, 400, 255, 0, 0, "Good Bye!");
				drawText(100, 500, 402, 255, 0, 0, "Good Bye!");
				drawText(100, 500, 398, 255, 0, 0, "Good Bye!");
				return 0; // Exit the game
			}
			else if (keyPressed && whichKey == 10) { // for displaying highscores
				highScore = !highScore; //reverses boolean for highScore if same key pressed it will take back to menu
				myRect(0, 0, 1700, 1200, 12, 12, 12, 12, 12, 12);
				if (highScore) {
					drawText(50, 620, 38, 255, 215, 0, "High Scores");
					drawText(50, 620, 42, 255, 215, 0, "High Scores");
					drawText(50, 620, 40, 255, 215, 0, "High Scores");
					drawText(50, 622, 40, 255, 215, 0, "High Scores");
					drawText(50, 618, 40, 255, 215, 0, "High Scores");
					drawText(30, 750, 200, 255, 215, 0, "1st: ", true, high1);
					drawText(30, 750, 350, 255, 215, 0, "2nd: ", true, high2);
					drawText(30, 750, 500, 255, 215, 0, "3rd: ", true, high3);
					drawText(30, 750, 650, 255, 215, 0, "4th: ", true, high4);
					drawText(30, 750, 800, 255, 215, 0, "5th: ", true, high5);
					drawText(20, 640, 900, 255, 210, 0, "Press H to return to menu");
				}
				else {

					drawText(70, 475, 20, 255, 215, 0, "GUJJAR TAYYARA");
					drawText(70, 477, 20, 255, 215, 0, "GUJJAR TAYYARA");
					drawText(70, 473, 20, 255, 215, 0, "GUJJAR TAYYARA");
					drawText(70, 475, 18, 255, 215, 0, "GUJJAR TAYYARA");
					drawText(70, 475, 22, 255, 215, 0, "GUJJAR TAYYARA");
					myRect(240, 390, 750, 470, 255, 215, 0, 12, 12, 12);
					drawText(30, 250, 400, 255, 215, 0, "NewGame: Press N");
					myRect(1090, 390, 1570, 470, 255, 215, 0, 12, 12, 12);
					drawText(30, 1100, 400, 255, 215, 0, "Resume: Press R");
					myRect(220, 640, 820, 720, 255, 215, 0, 12, 12, 12);
					drawText(30, 230, 650, 255, 215, 0, "HighScores: Press H");
					myRect(1130, 640, 1540, 720, 255, 215, 0, 12, 12, 12);
					drawText(30, 1140, 650, 255, 215, 0, "Exit: Press E");
				}
				if (highScore) {
					continue;
				}
			}


			Sleep(2000);
		}
		if (newGame) { // for displaying aliens for newGame
			for (int row = 0; row < 5; row++) {
				for (int col = 0; col < 10; col++) {
					AlienX[alienIndex] = AlienGridX + col * AlienSpacing;
					AlienY[alienIndex] = AlienGridY + row * AlienSpacing;
					alienIndex++;
				}
			}
		}
		if (resumeGame) { //overwriting values from file for previously initialized variables to resume 
			ifstream saveOut("SaveFile.txt");
			if (saveOut.is_open()) {
				saveOut >> initialX >> initialY >> alienDirection >> lives >> score >> bulletX >> bulletY;
				saveOut >> AlienGridX;
				saveOut >> AlienGridY;
				for (int i = 0; i < 50; i++) {

					saveOut >> AlienX[i];
					saveOut >> AlienY[i];
					saveOut >> AlienDestroyed[i];

				}
			}

		}



		DisplayScreen(initialX, initialY, score, livesX, livesY, lives); // display screen, ship, lives and score for both new game and resume 


		bool movedDown = false; // for making aliens to move towards bottom once per collision with side boundaries
		bool isPaused = false; // for pausing game
		while (true) {

			bool keyPressed = isKeyPressed(whichKey);
			if (keyPressed && whichKey == 7) { //Esc to pause
				isPaused = !isPaused;
				if (isPaused) {
					myRect(0, 0, 1600, 1200, 12, 12, 12, 12, 12, 12);
					drawText(100, 600, 30, 0, 0, 255, "Paused");
					drawText(100, 602, 30, 0, 0, 255, "Paused");
					drawText(100, 598, 30, 0, 0, 255, "Paused");
					drawText(100, 600, 32, 0, 0, 255, "Paused");
					drawText(100, 600, 28, 0, 0, 255, "Paused");
					myRect(190, 390, 730, 470, 255, 215, 0, 12, 12, 12);
					drawText(30, 200, 400, 255, 215, 0, "SaveGame: Press S");
					myRect(990, 390, 1530, 470, 255, 215, 0, 12, 12, 12);
					drawText(30, 1000, 400, 255, 215, 0, "Resume: Press Esc");
					myRect(270, 640, 710, 720, 255, 215, 0, 12, 12, 12);
					drawText(30, 270, 650, 255, 215, 0, "Exit: Press E");
					myRect(1050, 640, 1490, 720, 255, 215, 0, 12, 12, 12);
					drawText(30, 1060, 650, 255, 215, 0, "Menu: Press M");
					while (isPaused) {
						bool menukeyPressed = isKeyPressed(whichKey);
						if (menukeyPressed && whichKey == 11) {
							myRect(0, 0, 1700, 1200, 12, 12, 12, 12, 12, 12);
							drawText(100, 500, 400, 255, 0, 0, "Good Bye!");
							drawText(100, 502, 400, 255, 0, 0, "Good Bye!");
							drawText(100, 498, 400, 255, 0, 0, "Good Bye!");
							drawText(100, 500, 402, 255, 0, 0, "Good Bye!");
							drawText(100, 500, 398, 255, 0, 0, "Good Bye!");
							return 0; // Exit the game
						}
						else if (menukeyPressed && whichKey == 13) { //for showing menu
							menu = true;
							break;
						}
						else if (menukeyPressed && whichKey == 12) { // for saving game
							ofstream saveIn("SaveFile.txt");
							if (saveIn.is_open()) {
								saveIn << initialX << '\n' << initialY << '\n' << alienDirection << '\n' << lives << '\n' << score << '\n' << bulletX << '\n' << bulletY << '\n';
								saveIn << AlienGridX << '\n';
								saveIn << AlienGridY << '\n';

								for (int i = 0; i < 50; i++) {

									saveIn << AlienX[i] << " ";
									saveIn << AlienY[i] << " ";
									saveIn << AlienDestroyed[i] << '\n';

								}
								saveIn.close();
								drawText(30, 600, 900, 255, 215, 0, "Game successfully saved");
								Sleep(1000);
							}
						}
						else if (menukeyPressed && whichKey == 7) { //again check for pause key to resume
							isPaused = !isPaused;
							// Erase "Paused" text
							myRect(0, 0, 1600, 1200, 12, 12, 12, 12, 12, 12);
							DisplayScreen(initialX, initialY, score, livesX, livesY, lives);
						}
					}
					if (menu == true) {
						break;
					}
				}
				else {
					// Erase "Paused" text and display blank screen
					myRect(0, 0, 1600, 1200, 12, 12, 12, 12, 12, 12);
					DisplayScreen(initialX, initialY, score, livesX, livesY, lives);
				}

			}
			if (isPaused) {
				continue;
			}
			//to checck if left or right most aliens collide with the side boundaries so direction can be changed and moved downwards
			float leftmostX = 1400, rightmostX = 0;
			for (int i = 0; i < 50; i++) {
				if (!AlienDestroyed[i]) {
					leftmostX = min(leftmostX, AlienX[i]); //to check min of both
					rightmostX = max(rightmostX, AlienX[i] + AlienWidth);//to check max of both
				}
			}
			AlienGridX += alienDirection * 0.9; // Constant speed for alien movement
			if ((rightmostX >= 1398 || leftmostX <= 22) && !movedDown) {
				alienDirection *= -1;   // Reverse direction
				AlienGridY += 30;       // Move down once
				movedDown = true;       // Set flag to prevent continuous downward movement
			}
			else if (rightmostX < 1398 && leftmostX > 22) {
				movedDown = false;      // Reset flag when not at boundaries
			}
			bool allDestroyed = true; // for setting winning condition of killing all 50 aliens
			alienIndex = 0;
			allDestroyed = true;
			for (int row = 0; row < 5; row++) {
				for (int col = 0; col < 10; col++) {
					if (!AlienDestroyed[alienIndex]) {
						allDestroyed = false;
						// Erase the alien's previous position
						myEllipse(AlienX[alienIndex], AlienY[alienIndex], AlienX[alienIndex] + 20, AlienY[alienIndex] + 20, 0, 0, 0, 0, 0, 0);
						myEllipse(AlienX[alienIndex] + 20, AlienY[alienIndex], AlienX[alienIndex] + 40, AlienY[alienIndex] + 20, 0, 0, 0, 0, 0, 0);
						myLine(AlienX[alienIndex], AlienY[alienIndex] + 20, AlienX[alienIndex] + 20, AlienY[alienIndex] + 40, 0, 0, 0);
						myLine(AlienX[alienIndex] + 40, AlienY[alienIndex] + 20, AlienX[alienIndex] + 20, AlienY[alienIndex] + 40, 0, 0, 0);

						// Update alien position
						AlienX[alienIndex] = AlienGridX + col * AlienSpacing;
						AlienY[alienIndex] = AlienGridY + row * AlienSpacing;

						// Draw the alien in its new position
						myEllipse(AlienX[alienIndex], AlienY[alienIndex], AlienX[alienIndex] + 20, AlienY[alienIndex] + 20, 0, 255, 0, 0, 255, 0);
						myEllipse(AlienX[alienIndex] + 20, AlienY[alienIndex], AlienX[alienIndex] + 40, AlienY[alienIndex] + 20, 0, 255, 0, 0, 255, 0);
						myLine(AlienX[alienIndex], AlienY[alienIndex] + 20, AlienX[alienIndex] + 20, AlienY[alienIndex] + 40, 255, 255, 255);
						myLine(AlienX[alienIndex] + 40, AlienY[alienIndex] + 20, AlienX[alienIndex] + 20, AlienY[alienIndex] + 40, 255, 255, 255);
						//If alien reaches bottom of screen
						if (AlienY[alienIndex] + 40 > 898) {
							// Game over
							myRect(0, 0, 1700, 1400, 12, 12, 12, 12, 12, 12);
							drawText(100, 500, 400, 255, 0, 0, "GAME OVER");
							drawText(100, 502, 400, 255, 0, 0, "GAME OVER");
							drawText(100, 498, 400, 255, 0, 0, "GAME OVER");
							drawText(100, 500, 402, 255, 0, 0, "GAME OVER");
							drawText(100, 500, 398, 255, 0, 0, "GAME OVER");
							Sleep(3000);
							bottomReach = true;
							break;

						}
						// Check collision with each alien
						if (bulletX >= AlienX[alienIndex] && bulletX <= AlienX[alienIndex] + AlienWidth &&
							bulletY >= AlienY[alienIndex] && bulletY <= AlienY[alienIndex] + AlienHeight) {
							// Mark the alien as destroyed
							AlienDestroyed[alienIndex] = true;
							// Update score

							drawText(20, 1420, 140, 12, 12, 12, "Score: ", true, score); // Erase old score
							score += 100;
							drawText(20, 1420, 140, 255, 215, 0, "Score: ", true, score);
							// Erase the alien
							myEllipse(AlienX[alienIndex], AlienY[alienIndex], AlienX[alienIndex] + 20, AlienY[alienIndex] + 20, 0, 0, 0, 0, 0, 0);
							myEllipse(AlienX[alienIndex] + 20, AlienY[alienIndex], AlienX[alienIndex] + 40, AlienY[alienIndex] + 20, 0, 0, 0, 0, 0, 0);
							myLine(AlienX[alienIndex], AlienY[alienIndex] + 20, AlienX[alienIndex] + 20, AlienY[alienIndex] + 40, 0, 0, 0);
							myLine(AlienX[alienIndex] + 40, AlienY[alienIndex] + 20, AlienX[alienIndex] + 20, AlienY[alienIndex] + 40, 0, 0, 0);



							myRect(bulletX, bulletY, bulletX + 4, bulletY + 15, 0, 0, 0, 0, 0, 0);
							// Reset the bullet
							bulletX = -1;
							bulletY = -1;
						}
						// Check for collision with player
						if (initialX - 40 < AlienX[alienIndex] + AlienWidth &&
							initialX + 60 > AlienX[alienIndex] &&
							initialY - 10 < AlienY[alienIndex] + AlienHeight &&
							initialY + 80 > AlienY[alienIndex]) {

							// Remove one life and mark the alien as destroyed
							AlienDestroyed[alienIndex] = true;
							// Erase the alien
							myEllipse(AlienX[alienIndex], AlienY[alienIndex], AlienX[alienIndex] + 20, AlienY[alienIndex] + 20, 0, 0, 0, 0, 0, 0);
							myEllipse(AlienX[alienIndex] + 20, AlienY[alienIndex], AlienX[alienIndex] + 40, AlienY[alienIndex] + 20, 0, 0, 0, 0, 0, 0);
							myLine(AlienX[alienIndex], AlienY[alienIndex] + 20, AlienX[alienIndex] + 20, AlienY[alienIndex] + 40, 0, 0, 0);
							myLine(AlienX[alienIndex] + 40, AlienY[alienIndex] + 20, AlienX[alienIndex] + 20, AlienY[alienIndex] + 40, 0, 0, 0);


							if (lives > 0) {
								// Erase one sphere
								myEllipse(livesX[--lives], livesY, livesX[lives] + 25, livesY - 25, 0, 0, 0, 0, 0, 0);
							}
							if (lives == 0) {
								// Game over
								myRect(0, 0, 1700, 1400, 12, 12, 12, 12, 12, 12);
								drawText(100, 500, 400, 255, 0, 0, "GAME OVER");
								drawText(100, 502, 400, 255, 0, 0, "GAME OVER");
								drawText(100, 498, 400, 255, 0, 0, "GAME OVER");
								drawText(100, 500, 402, 255, 0, 0, "GAME OVER");
								drawText(100, 500, 398, 255, 0, 0, "GAME OVER");
								Sleep(3000);
								livesEnd = true;
								break;
							}
						}
					}

					alienIndex++;
				}
				if (bottomReach == true || livesEnd) {
					break;
				}
			}
			if (bottomReach == true || livesEnd == true) {
				break;
			}
			if (allDestroyed == true) { // fulfilling winning condition of destroying all aliens
				Sleep(500);
				myRect(0, 0, 1700, 1400, 12, 12, 12, 12, 12, 12);
				drawText(70, 632, 300, 0, 0, 255, "GAME OVER!");
				drawText(70, 628, 300, 0, 0, 255, "GAME OVER!");
				drawText(70, 630, 300, 0, 0, 255, "GAME OVER!");
				drawText(70, 630, 302, 0, 0, 255, "GAME OVER!");
				drawText(70, 630, 298, 0, 0, 255, "GAME OVER!");
				drawText(70, 692, 500, 0, 0, 255, "YOU WON!");
				drawText(70, 688, 500, 0, 0, 255, "YOU WON!");
				drawText(70, 690, 502, 0, 0, 255, "YOU WON!");
				drawText(70, 690, 498, 0, 0, 255, "YOU WON!");
				drawText(70, 690, 500, 0, 0, 255, "YOU WON!");
				Sleep(3000);

				break;
			}

			// Update bullet position
			if (bulletX != -1 && bulletY != -1) {
				// Erase the previous bullet
				myRect(bulletX, bulletY, bulletX + 4, bulletY + 15, 0, 0, 0, 0, 0, 0);
				// Move bullet upwards
				bulletY -= 6;
			}
			// Check if bullet hits the top boundary
			if (bulletY < 40) {
				bulletX = -1;
				bulletY = -1; // Reset bullet
			}
			if (bulletX != -1 && bulletY != -1) {
				myRect(bulletX, bulletY, bulletX + 4, bulletY + 15, 0, 255, 255, 0, 255, 255);
			}
			if (keyPressed == true)
			{
				if (whichKey == 1) {     //For Left Move
					if (initialX - 40 > 32) {
						myEllipse(initialX, initialY, initialX + 20, initialY + 80, 0, 0, 0, 0, 0, 0);
						myLine(initialX - 40, initialY + 20, initialX, initialY + 20, 0, 0, 0);
						myLine(initialX - 40, initialY + 20, initialX, initialY + 40, 0, 0, 0);
						myLine(initialX + 20, initialY + 20, initialX + 60, initialY + 20, 0, 0, 0);
						myLine(initialX + 20, initialY + 40, initialX + 60, initialY + 20, 0, 0, 0);
						myLine(initialX - 20, initialY + 60, initialX, initialY + 60, 0, 0, 0);
						myLine(initialX - 20, initialY + 60, initialX + 4, initialY + 70, 0, 0, 0);
						myLine(initialX + 20, initialY + 60, initialX + 40, initialY + 60, 0, 0, 0);
						myLine(initialX + 16, initialY + 70, initialX + 40, initialY + 60, 0, 0, 0);
						myLine(initialX + 10, initialY, initialX + 10, initialY - 10, 0, 0, 0);
						initialX -= 20;
						myEllipse(initialX, initialY, initialX + 20, initialY + 80, 255, 0, 0, 255, 0, 0);
						myLine(initialX - 40, initialY + 20, initialX, initialY + 20, 255, 0, 0);
						myLine(initialX - 40, initialY + 20, initialX, initialY + 40, 255, 0, 0);
						myLine(initialX + 20, initialY + 20, initialX + 60, initialY + 20, 255, 0, 0);
						myLine(initialX + 20, initialY + 40, initialX + 60, initialY + 20, 255, 0, 0);
						myLine(initialX - 20, initialY + 60, initialX, initialY + 60, 255, 0, 0);
						myLine(initialX - 20, initialY + 60, initialX + 4, initialY + 70, 255, 0, 0);
						myLine(initialX + 20, initialY + 60, initialX + 40, initialY + 60, 255, 0, 0);
						myLine(initialX + 16, initialY + 70, initialX + 40, initialY + 60, 255, 0, 0);
						myLine(initialX + 10, initialY, initialX + 10, initialY - 10, 255, 0, 0);
					}
				}
				else if (whichKey == 2) { //For Moving Up
					if (initialY - 10 > 50) {
						myEllipse(initialX, initialY, initialX + 20, initialY + 80, 0, 0, 0, 0, 0, 0);
						myLine(initialX - 40, initialY + 20, initialX, initialY + 20, 0, 0, 0);
						myLine(initialX - 40, initialY + 20, initialX, initialY + 40, 0, 0, 0);
						myLine(initialX + 20, initialY + 20, initialX + 60, initialY + 20, 0, 0, 0);
						myLine(initialX + 20, initialY + 40, initialX + 60, initialY + 20, 0, 0, 0);
						myLine(initialX - 20, initialY + 60, initialX, initialY + 60, 0, 0, 0);
						myLine(initialX - 20, initialY + 60, initialX + 4, initialY + 70, 0, 0, 0);
						myLine(initialX + 20, initialY + 60, initialX + 40, initialY + 60, 0, 0, 0);
						myLine(initialX + 16, initialY + 70, initialX + 40, initialY + 60, 0, 0, 0);
						myLine(initialX + 10, initialY, initialX + 10, initialY - 10, 0, 0, 0);
						initialY -= 20;
						myEllipse(initialX, initialY, initialX + 20, initialY + 80, 255, 0, 0, 255, 0, 0);
						myLine(initialX - 40, initialY + 20, initialX, initialY + 20, 255, 0, 0);
						myLine(initialX - 40, initialY + 20, initialX, initialY + 40, 255, 0, 0);
						myLine(initialX + 20, initialY + 20, initialX + 60, initialY + 20, 255, 0, 0);
						myLine(initialX + 20, initialY + 40, initialX + 60, initialY + 20, 255, 0, 0);
						myLine(initialX - 20, initialY + 60, initialX, initialY + 60, 255, 0, 0);
						myLine(initialX - 20, initialY + 60, initialX + 4, initialY + 70, 255, 0, 0);
						myLine(initialX + 20, initialY + 60, initialX + 40, initialY + 60, 255, 0, 0);
						myLine(initialX + 16, initialY + 70, initialX + 40, initialY + 60, 255, 0, 0);
						myLine(initialX + 10, initialY, initialX + 10, initialY - 10, 255, 0, 0);
					}
				}
				else if (whichKey == 3) { //for right move
					if (initialX + 60 < 1400) {
						myEllipse(initialX, initialY, initialX + 20, initialY + 80, 0, 0, 0, 0, 0, 0);
						myLine(initialX - 40, initialY + 20, initialX, initialY + 20, 0, 0, 0);
						myLine(initialX - 40, initialY + 20, initialX, initialY + 40, 0, 0, 0);
						myLine(initialX + 20, initialY + 20, initialX + 60, initialY + 20, 0, 0, 0);
						myLine(initialX + 20, initialY + 40, initialX + 60, initialY + 20, 0, 0, 0);
						myLine(initialX - 20, initialY + 60, initialX, initialY + 60, 0, 0, 0);
						myLine(initialX - 20, initialY + 60, initialX + 4, initialY + 70, 0, 0, 0);
						myLine(initialX + 20, initialY + 60, initialX + 40, initialY + 60, 0, 0, 0);
						myLine(initialX + 16, initialY + 70, initialX + 40, initialY + 60, 0, 0, 0);
						myLine(initialX + 10, initialY, initialX + 10, initialY - 10, 0, 0, 0);
						initialX += 20;
						myEllipse(initialX, initialY, initialX + 20, initialY + 80, 255, 0, 0, 255, 0, 0);
						myLine(initialX - 40, initialY + 20, initialX, initialY + 20, 255, 0, 0);
						myLine(initialX - 40, initialY + 20, initialX, initialY + 40, 255, 0, 0);
						myLine(initialX + 20, initialY + 20, initialX + 60, initialY + 20, 255, 0, 0);
						myLine(initialX + 20, initialY + 40, initialX + 60, initialY + 20, 255, 0, 0);
						myLine(initialX - 20, initialY + 60, initialX, initialY + 60, 255, 0, 0);
						myLine(initialX - 20, initialY + 60, initialX + 4, initialY + 70, 255, 0, 0);
						myLine(initialX + 20, initialY + 60, initialX + 40, initialY + 60, 255, 0, 0);
						myLine(initialX + 16, initialY + 70, initialX + 40, initialY + 60, 255, 0, 0);
						myLine(initialX + 10, initialY, initialX + 10, initialY - 10, 255, 0, 0);
					}

				}
				else if (whichKey == 4) {//for moving up
					if (initialY + 80 < 900) {
						myEllipse(initialX, initialY, initialX + 20, initialY + 80, 0, 0, 0, 0, 0, 0);
						myLine(initialX - 40, initialY + 20, initialX, initialY + 20, 0, 0, 0);
						myLine(initialX - 40, initialY + 20, initialX, initialY + 40, 0, 0, 0);
						myLine(initialX + 20, initialY + 20, initialX + 60, initialY + 20, 0, 0, 0);
						myLine(initialX + 20, initialY + 40, initialX + 60, initialY + 20, 0, 0, 0);
						myLine(initialX - 20, initialY + 60, initialX, initialY + 60, 0, 0, 0);
						myLine(initialX - 20, initialY + 60, initialX + 4, initialY + 70, 0, 0, 0);
						myLine(initialX + 20, initialY + 60, initialX + 40, initialY + 60, 0, 0, 0);
						myLine(initialX + 16, initialY + 70, initialX + 40, initialY + 60, 0, 0, 0);
						myLine(initialX + 10, initialY, initialX + 10, initialY - 10, 0, 0, 0);
						initialY += 20;
						myEllipse(initialX, initialY, initialX + 20, initialY + 80, 255, 0, 0, 255, 0, 0);
						myLine(initialX - 40, initialY + 20, initialX, initialY + 20, 255, 0, 0);
						myLine(initialX - 40, initialY + 20, initialX, initialY + 40, 255, 0, 0);
						myLine(initialX + 20, initialY + 20, initialX + 60, initialY + 20, 255, 0, 0);
						myLine(initialX + 20, initialY + 40, initialX + 60, initialY + 20, 255, 0, 0);
						myLine(initialX - 20, initialY + 60, initialX, initialY + 60, 255, 0, 0);
						myLine(initialX - 20, initialY + 60, initialX + 4, initialY + 70, 255, 0, 0);
						myLine(initialX + 20, initialY + 60, initialX + 40, initialY + 60, 255, 0, 0);
						myLine(initialX + 16, initialY + 70, initialX + 40, initialY + 60, 255, 0, 0);
						myLine(initialX + 10, initialY, initialX + 10, initialY - 10, 255, 0, 0);
					}

				}
				else if (whichKey == 6 && bulletX == -1 && bulletY == -1) { //For launching bullet 
					bulletX = initialX + 10;
					bulletY = initialY - 30;
				}
			}
		}
		if (!menu) { // if menu button is not pressed during paused then score is not saved and redirected to menu
			int temp;
			ofstream HiIn("HighScore.txt");
			// comparing scores with all positions
			if (HiIn.is_open()) {
				if (score > high1) {
					for (int i = 5; i > 0; i--) {
						temp = scores[i - 1];
						scores[i] = scores[i - 1];
					}
					scores[0] = score;
				}
				else if (score > high2) {
					for (int i = 5; i > 1; i--) {
						temp = scores[i - 1];
						scores[i] = scores[i - 1];
					}
					scores[1] = score;
				}
				else if (score > high3) {
					for (int i = 5; i > 2; i--) {
						temp = scores[i - 1];
						scores[i] = scores[i - 1];
					}
					scores[2] = score;
				}
				else if (score > high4) {
					for (int i = 5; i > 3; i--) {
						temp = scores[i - 1];
						scores[i] = scores[i - 1];
					}
					scores[3] = score;
				}
				else if (score > high5) {
					high5 = score;
					scores[4] = score;
				}
				high1 = scores[0];
				high2 = scores[1];
				high3 = scores[2];
				high4 = scores[3];
				high5 = scores[4];
				// writing score into file
				HiIn << high1 << '\n';
				HiIn << high2 << '\n';
				HiIn << high3 << '\n';
				HiIn << high4 << '\n';
				HiIn << high5 << '\n';
				HiIn.close();
			}
		}

	}
	return 0;
}