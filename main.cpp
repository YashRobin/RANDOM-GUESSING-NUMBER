#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include<Windows.h>
#include "MMSystem.h"
#include <atomic>
#include <vector>
#include <algorithm>
#include <conio.h> // For _kbhit() and _getch() on Windows
#include <thread>
#include<string>
#include <numeric>

using namespace std;


void clearScreen() {
    // Clear screen function using system("cls")
    system("cls");
}

void blinkWelcome(int numBlinks) {
    // ASCII art welcome text
    string welcomeText = R"(
  oooooo   oooooo     oooo oooooooooooo ooooo          .oooooo.     .oooooo.   ooo        ooooo oooooooooooo 
 `888.    `888.     .8'  `888'     `8 `888'         d8P'  `Y8b   d8P'  `Y8b  `88.       .888' `888'     `8 
  `888.   .8888.   .8'    888          888         888          888      888  888b     d'888   888         
   `888  .8'`888. .8'     888oooo8     888         888          888      888  8 Y88. .P  888   888oooo8    
    `888.8'  `888.8'      888    "     888         888          888      888  8  `888'   888   888    "    
     `888'    `888'       888       o  888       o `88b    ooo  `88b    d88'  8    Y     888   888       o 
      `8'      `8'       o888ooooood8 o888ooooood8  `Y8bood8P'   `Y8bood8P'  o8o        o888o o888ooooood8 
                                                                                                           
                                                                                                          
    )";

    // Print the welcome text with blinking effect
    for (int i = 0; i < numBlinks; ++i) {
        clearScreen(); // Clear screen before printing new frame
        cout << welcomeText << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Delay between blinks (500 milliseconds = 0.5 seconds)
        clearScreen(); // Clear screen before printing next blink
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Delay between blinks
    }
}



int score;
/*
void score_user(const string& filename, const string& query,int score,string username){
	
}*/

// Function to perform search query
void searchQuery(const string& filename, const string& query) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    int line_number = 0;
    while (getline(file, line)) {
        line_number++;
        size_t pos = line.find(query);
        if (pos != string::npos) {
            cout << "Found at line " << line_number << ": " << line << endl;
            // Optionally, continue searching for more occurrences
        }
    }

    file.close();
}



void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void drawBorder(bool visible) {
    int width = 90;  // Width of the border
    int height =30; // Height of the border
    char borderChar = visible ? '*' : ' ';

    // Top border
    for (int i = 1; i < width; ++i) {
        gotoxy(i, 0);
        cout << borderChar;
    }

    // Bottom border
    for (int i = 1; i < width; ++i) {
        gotoxy(i, height - 1);
        cout << borderChar;
    }

    // Left border
    for (int i = 1; i < height; ++i) {
        gotoxy(0, i);
        cout << borderChar;
    }

    // Right border
    for (int i = 1; i < height; ++i) {
        gotoxy(width - 1, i);
        cout << borderChar;
    }
}


// Function to display the intro of the advanced random guessing number game


void window_close(){
	
	//THIS WILL CLOSE THE SOUND FILE BEHIND THE ANIMATION TEXT
    const char* windowTitle = "sound";
	// const char* windowTitle1 = "C";
    // Find the window handle based on the title
    HWND hwnd = FindWindow(NULL, windowTitle);

    if (hwnd == NULL) {
        cout << "Window not found or already closed." << endl;

    }

    // Send the close message to the window
    SendMessage(hwnd, WM_CLOSE, 0, 0);
    //HWND hwnd1 = FindWindow(NULL, windowTitle1);
    //SendMessage(hwnd1, WM_CLOSE, 0, 0);
}
void window_close1(){
	
	//THIS WILL CLOSE THE SOUND FILE BEHIND THE ANIMATION TEXT
   
	 const char* windowTitle = "C";
    // Find the window handle based on the title
    HWND hwnd = FindWindow(NULL, windowTitle);

    if (hwnd == NULL) {
        cout << "Window not found or already closed." << endl;

    }

    // Send the close message to the window
  SendMessage(hwnd, WM_CLOSE, 0, 0);
}

void window_close2(){
	
	//THIS WILL CLOSE THE SOUND FILE BEHIND THE ANIMATION TEXT
   
	 const char* windowTitle = "BACKGROUNDSOUND";
    // Find the window handle based on the title
    HWND hwnd = FindWindow(NULL, windowTitle);

    if (hwnd == NULL) {
        cout << "Window not found or already closed." << endl;

    }

    // Send the close message to the window
  SendMessage(hwnd, WM_CLOSE, 0, 0);
}

atomic<bool> stopAnimation(false);

void animation_stop(){ 
if (stopAnimation) {
    	system("cls");
    	drawBorder(true);
    		COORD coord;
    coord.X = 2; // Desired X position
    coord.Y = 2;  // Desired Y position
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    	 string text = "Welcome to the Advanced Random Guessing Number Game!\n\n"
                   "* In this game, you will try to guess a number chosen by the computer.\n"
                   "* The number will be randomly selected within a specific range.\n"
                   "* After each guess, you will receive feedback on whether your guess\n"
                   "* is too high, too low, or correct.\n\n"
                   "* Let's test your luck and see how many attempts you need to find the right number!\n";
        cout << text << endl;
    } else {
        cout << endl; // Move to a new line after printing
    }
}

void animatedText(const string& text, int delay = 15) {


    for (char c : text) {
        if (stopAnimation) {
            break;
        }
        cout << c;
        cout.flush(); // Flush output to ensure immediate display
        this_thread::sleep_for(chrono::milliseconds(delay));
    }

    // If the animation was stopped, print the rest of the text
    animation_stop();
   
}

void waitForEnter() {
    while (!stopAnimation) {
        if (_kbhit() && _getch() == '\r') {
            stopAnimation = true;
            break;
        }
    }
}

void SET_CORD(int x = 2, int y = 2) {
    COORD coord;
    coord.X = x; // Use the passed value or the default
    coord.Y = y; // Use the passed value or the default
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}





void displayIntro() {
		SET_CORD();
    string intro = "Welcome to the Advanced Random Guessing Number Game!\n\n"
                   "* In this game, you will try to guess a number chosen by the computer.\n"
                   "* The number will be randomly selected within a specific range.\n"
                   "* After each guess, you will receive feedback on whether your guess\n"
                   "* is too high, too low, or correct.\n\n"
                   "* Let's test your luck and see how many attempts you need to find the right number!\n";

    thread animationThread(animatedText, ref(intro), 50); // Use ref to pass the string by reference
    thread inputThread(waitForEnter);
    animationThread.join();
    inputThread.join();
    stopAnimation = false; // Reset for next use
}


void printGameOver() {
    std::cout << R"(
  ____                       ___                 
 / ___| __ _ _ __ ___   ___  / _ \__   _____ _ __ 
| |  _ / _` | '_ ` _ \ / _ \| | | \ \ / / _ \ '__|
| |_| | (_| | | | | | |  __/| |_| |\ V /  __/ |   
 \____|\__,_|_| |_| |_|\___| \___/  \_/ \___|_|   
                                                  
    )" << std::endl;
}

void level_1() {
    std::cout << R"(
*                   __                   __   ___                   
*                  / /   ___ _   _____  / /  <  /                   
*  _ ___________  / /   / _ \ | / / _ \/ /   / /  __________________
* /_____/_____/  / /___/  __/ |/ /  __/ /   / /  /_____/_____/_____/
*               /_____/\___/|___/\___/_/   /_/                      
*                                                                                                                
   )" << std::endl;
}
void level_2() {
    std::cout << R"(
                         _                    _   ___                         
                        | |                  | | |__ \                        
  ______ ______ ______  | |     _____   _____| |    ) |  ______ ______ ______ 
 |______|______|______| | |    / _ \ \ / / _ \ |   / /  |______|______|______|
                        | |___|  __/\ V /  __/ |  / /_                        
                        |______\___| \_/ \___|_| |____|                       
                                                                              
                                                                                                                        
   )" << std::endl;
}
void level_3() {
    std::cout << R"(
                         _                    _   ____                         
                        | |                  | | |___ \                        
  ______ ______ ______  | |     _____   _____| |   __) |  ______ ______ ______ 
 |______|______|______| | |    / _ \ \ / / _ \ |  |__ <  |______|______|______|
                        | |___|  __/\ V /  __/ |  ___) |                       
                        |______\___| \_/ \___|_| |____/                        
                                                                               
                                                                               
                                                                                                                        
   )" << std::endl;
}
void level_4() {
    std::cout << R"(
                        _                    _   _  _                          
                        | |                  | | | || |                         
  ______ ______ ______  | |     _____   _____| | | || |_   ______ ______ ______ 
 |______|______|______| | |    / _ \ \ / / _ \ | |__   _| |______|______|______|
                        | |___|  __/\ V /  __/ |    | |                         
                        |______\___| \_/ \___|_|    |_|                         
                                                                                
                                                                                
                                                                                                                        
   )" << std::endl;
}

void level_5() {
    std::cout << R"(
                         _                    _   _____                        
                        | |                  | | | ____|                       
  ______ ______ ______  | |     _____   _____| | | |__    ______ ______ ______ 
 |______|______|______| | |    / _ \ \ / / _ \ | |___ \  |______|______|______|
                        | |___|  __/\ V /  __/ |  ___) |                       
                        |______\___| \_/ \___|_| |____/                        
                                                                               
                                                                               
                                                                               
                                                                                                                        
   )" << std::endl;
}
void level_6() {
    std::cout << R"(
                         _                    _     __                         
                        | |                  | |   / /                         
  ______ ______ ______  | |     _____   _____| |  / /_    ______ ______ ______ 
 |______|______|______| | |    / _ \ \ / / _ \ | | '_ \  |______|______|______|
                        | |___|  __/\ V /  __/ | | (_) |                       
                        |______\___| \_/ \___|_|  \___/                        
                                                                               
                                                                               
                                                                               
                                                                                                                        
   )" << std::endl;
}

void level_7() {
    std::cout << R"(
                          _                    _   ______                        
                        | |                  | | |____  |                       
  ______ ______ ______  | |     _____   _____| |     / /   ______ ______ ______ 
 |______|______|______| | |    / _ \ \ / / _ \ |    / /   |______|______|______|
                        | |___|  __/\ V /  __/ |   / /                          
                        |______\___| \_/ \___|_|  /_/                           
                                                                                
                                                                                                                       
   )" << std::endl;
}

void level_8() {
    std::cout << R"(
                        _                    _    _____                        
                       | |                  | |  |  _  |                       
 ______ ______ ______  | |     _____   _____| |   \ V /   ______ ______ ______ 
|______|______|______| | |    / _ \ \ / / _ \ |   / _ \  |______|______|______|
                       | |___|  __/\ V /  __/ |  | |_| |                       
                       \_____/\___| \_/ \___|_|  \_____/                       
                                                                               
                                                                               
                                                                                                                       
   )" << std::endl;
}

void Congratulation() {
    std::cout << R"(
   _____                            _         _       _   _             
   / ____|                          | |       | |     | | (_)            
  | |     ___  _ __   __ _ _ __ __ _| |_ _   _| | __ _| |_ _  ___  _ __  
  | |    / _ \| '_ \ / _` | '__/ _` | __| | | | |/ _` | __| |/ _ \| '_ \ 
  | |___| (_) | | | | (_| | | | (_| | |_| |_| | | (_| | |_| | (_) | | | |
   \_____\___/|_| |_|\__, |_|  \__,_|\__|\__,_|_|\__,_|\__|_|\___/|_| |_|
                      __/ |                                              
                     |___/                                               
                                                                                                                
   )" << std::endl;
}



void display_help(){
	cout << "316 for end during the game" << endl;
	cout << "999 for  for passing the LEVEL!" << endl;

}

void wrong_display_x(){
		cout << "*" ;
	  for (int i = 0; i < 15; i++) {
   		cout << "x" ;
    }
    cout << endl;
}

// SOUND FUNCTIONS
void sound_game_over(){
{
	
	printGameOver();
	PlaySound(TEXT("Game.wav"),NULL,SND_SYNC);
	
	 PlaySound(TEXT("AFTER-GAME-OVER.wav"), NULL, SND_SYNC  | SND_ASYNC);
}
}

void sound_game_win(){
{
	
	PlaySound(TEXT("next-level.wav"),NULL,SND_SYNC);
	system("pause");

}
}
void Level_up1(){
{
	
	PlaySound(TEXT("level-passed.wav"),NULL,SND_SYNC);
	//system("pause");

}
}


void sound_wrong(){
{
	
	PlaySound(TEXT("Wrong_sound.wav"),NULL,SND_SYNC);
//	system("pause");

}}
/*void animateLoading() {
    const std::string message = "LOADING PLEASE WAIT";
    const int numDots = 6;  // Number of dots in the animation
    const int delay = 500;  // Delay in milliseconds between each frame
    const int clearDelay = 2000;  // Delay in milliseconds before dots reappear

    while (true) {
        // Display message with dots
        std::cout << message;
        for (int i = 0; i < numDots; ++i) {
            std::cout << '.';
            std::cout.flush();
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        }

        // Clear the dots by overwriting with spaces
        std::cout << "\r" << message;
        for (int i = 0; i < numDots; ++i) {
            std::cout << ' ';
        }
        std::cout.flush();

        // Wait before starting the animation again
        std::this_thread::sleep_for(std::chrono::milliseconds(clearDelay));

        // Move cursor back to the start of the line
        std::cout << "\r";
    } 
}*/
void Design_end_line(){

for(int i=1 ; i < 90 ; i++){
   	cout << "-";
   }
}

void level_display(int level){
if (level == 1) {
    level_1();
} else if (level == 2) {
    level_2();
} else if (level == 3) {
    level_3();
} else if (level == 4) {
    level_4();
} else if (level == 5) {
    level_5();
} else if (level == 6) {
    level_6();
} else if (level == 7) {
    level_7();
} else if (level == 8) {
    level_8();
} else {
    // Optional: handle unexpected level values
    // For example, you might log an error or set a default level
}


}




// Structure to hold player information (name and score)
struct Player {
    std::string name;
    int score;

    // Constructor to initialize player with name and score
    Player(std::string n, int s) : name(n), score(s) {}
};

// Function to compare players based on score (for sorting)
bool comparePlayers(const Player& p1, const Player& p2) {
    return p1.score > p2.score; // Sort in descending order
}

// Class representing the leaderboard
class Leaderboard {
private:
    std::vector<Player> players;
    std::string filename; // File to store player records

public:
    // Constructor to initialize with filename
    Leaderboard(std::string fname) : filename(fname) {}

    // Method to add a player with their score
    void addPlayer(std::string name, int score) {
        // Check if player already exists
        bool found = false;
        for (auto& player : players) {
            if (player.name == name) {
                player.score = score; // Update existing player's score
                found = true;
                break;
            }
        }
        if (!found) {
            players.push_back(Player(name, score)); // Add new player
        }
    }

    // Method to load player records from file
    void loadFromFile() {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string name;
            int score;
            while (file >> name >> score) {
                addPlayer(name, score);
            }
            file.close();
        }
    }

    // Method to save player records to file
    void saveToFile() {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& player : players) {
                file << player.name << " " << player.score << "\n";
            }
            file.close();
        }
    }

    // Method to display the leaderboard
    void display() {
        // Sort players based on score
        std::sort(players.begin(), players.end(), comparePlayers);

        // Display leaderboard
        std::cout << "Leaderboard:\n";
        for (size_t i = 0; i < players.size(); ++i) {
            std::cout << i + 1 << ". " << players[i].name << ": " << players[i].score << "\n";
        }
    }
};

void PLAYES(string username){
	
	Leaderboard board("leaderboard.txt");
    // Load existing player records from file
    board.loadFromFile();

    // Adding sample players (or actual game scores)
   
    board.addPlayer(username, 220); // Update Player1's score

    // Displaying the leaderboard
    board.display();

    // Save updated player records to file
    board.saveToFile();
}










                                                                                            
class NumberGuessGame {
private:
    string username;
    int level;
    int max_attempts;
    int attempts_left;
    time_t timer_start;
    int timer_limit;
    vector<int> level_scores;

    bool game_running;

public:
	
	
	void Constant_User_name(string username,int level){
		if(level == 1) {
    score = 0;
}
else if (level == 2) {
    score = 10;
}
else if (level == 3) {
    score = 20;
}
else if (level == 4) {
    score = 30;
}
else if (level == 5) {
    score = 40;
}
else if (level == 6) {
    score = 50;
}
else if (level == 7) {
    score = 60;
}
else if (level == 8) {
    score = 70;
}

	SET_CORD();
   
    cout << "  Welcome, " << username << "!" <<"                          SCORE:"<<score<< endl;
	Design_end_line();
}

	
    NumberGuessGame(string uname) {
        username = uname;
        level = 1;
        max_attempts = 5;
        attempts_left = max_attempts;
        timer_start = 0;
        timer_limit = 60;  // 1 minute per level
        game_running = false;
    }

  void start_game() {
        game_running = true;
         system("start BACK.exe");
         
        //cout << "* Welcome, " << username << "!" << endl;
		
        while (level <= 8) {
        	if(level==1){
            	system("cls");
            	drawBorder(true);
         	Constant_User_name(username,level);
			}
        	
        	  if(level>=2){
            	system("cls");
            	drawBorder(true);
            	Constant_User_name(username,level);
			}
			 level_display(level);
           // cout << "\n--- Level " << level << " ---" << endl;
           
            play_level();
            if (!game_running) {
                break;
            }
            level++;
            reset_level();
        }




        
        
        
    }





private:
    void play_level() {
        timer_start = time(0);
        int target_number = rand() % get_max_range() + 1;
        cout << "* Guess the number between 1 and " << get_max_range() << "." << endl;
		
        while (attempts_left > 0 && game_running) {
            int guess = get_guess();
           
            	
            	
		
        if (guess == target_number || guess == 999 ) {
            	cout << endl;
            		system("cls");
            		drawBorder(true);
         	Constant_User_name(username,level);
            	//Design_end_line();
            	Congratulation();
            	
                cout << "* Congratulations! You guessed the correct number. " << target_number  << endl;
                
                
                //Design_end_line();
                //system("pause");
                break;
            } else if (guess < target_number) {
            	
				wrong_display_x();
				sound_wrong();
            	cout << endl;
            		system("cls");
            		drawBorder(true);
         	Constant_User_name(username,level);
         			
            //	Design_end_line();
            	level_display(level);
            	cout << "* Guess the number between 1 and " << get_max_range() << "." << endl;
            	cout << "NOT: " << guess ;
                cout << "\n Too low. Try again." << endl;
                
            } else {
            	wrong_display_x();
            	sound_wrong();
                cout << endl;
                	system("cls");
            		drawBorder(true);
         	Constant_User_name(username,level);
            //	Design_end_line();
            	level_display(level);
            	cout << "* Guess the number between 1 and " << get_max_range() << "." << endl;
            	cout << "*   NOT: " << guess ;
				cout << "\n  Too high. Try again." << endl;
                
            }
            attempts_left--;
            cout << "* Attempts left: " << attempts_left << endl;

            if (attempts_left == 0 || guess == 9989) {
			
				window_close2();
				 system("cls");
				 drawBorder(true);
         	Constant_User_name(username,level);
         			
            //	Design_end_line();
            	cout << "\n * Game over. The correct number was " << target_number << "." << endl;	
				
                Design_end_line();
                //printGameOver();
                sound_game_over();
                game_running = false;
            }
 
            time_t current_time = time(0);
            if (current_time - timer_start > timer_limit) {
                cout << "* Time's up! Game over." << endl;
                game_running = false;
            }
        }
    }

    int get_guess() {
        int guess;
        while (true) {
            cout << "* Enter your guess: ";
            
            if(guess == 9989){ // END GAME DURING PLAY IF STATMENT
            	
            		
				}
            if (!(cin >> guess)) {
            	
              
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");
                drawBorder(true);
         	Constant_User_name(username,level);
         			
            	//Design_end_line();
            	level_display(level);
            	cout << "* Invalid input. Please enter a valid number." << endl;
            	 cout << "* Guess the number between 1 and " << get_max_range() << "." << endl;
                
            } 
            else if (guess== 999) {
                break;}
                else if (guess== 9989) {
                break;}
			else if (guess < 1 || guess > get_max_range()) {
				system("cls");
                drawBorder(true);
         	Constant_User_name(username,level);
         			
            //	Design_end_line();
            	level_display(level);
                cout << "* Please enter a number between 1 and " << get_max_range() << "." << endl;
            } else {
                break;
            }
        }
        return guess;
    }

    void reset_level() {
        attempts_left = max_attempts;
        
        timer_start = 0;
        Level_up1();
        sound_game_win();
        
    }

    int get_max_range() {
        switch (level) {
            case 1:
                return 10;
            case 2:
                return 50;
            case 3:
                return 100;
            case 4:
                return 200;
            case 5:
                return 300;
            case 6:
                return 350;
            case 7:
                return 400;
            case 8:
                return 450;
            default:
                return 10;  // Default to level 1 range if level is somehow out of bounds
        }
    }
};



int main() {
	//	string filename = "leaderboard.txt";
	 //  string query = "YASH";   // Replace with your query

  //  searchQuery(filename, query);
	
 system("color 0A"); 
	 HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOWMAXIMIZED);
    
      int numBlinks = 1;
    
    // Print blinking welcome text
    blinkWelcome(numBlinks);
    
    system("start sound.exe");
    system("start C.exe");
    drawBorder(true);
    displayIntro();
    cout << "\t LOADING , PLEASE WAIT!" <<endl;

	window_close();
    window_close1();
    
    string username;
    cout << "* Enter your username: ";
  	
    getline(cin, username);
 Leaderboard board("leaderboard.txt");
    drawBorder(true);
    NumberGuessGame game(username);
    game.start_game();
	 PLAYES(username);
    return 0;
}
