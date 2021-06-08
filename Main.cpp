#include <iostream>
#include <fstream> 
#include <cstdlib>
#include<ctime>
#include <string>
#include <list>
#include <vector>
using namespace std;

//sets the number of possible incorrect guesses
int totalLives = 6;

// creates the player class that keeps track of the player's lives 
class Player {
    private:
        int lives;
    public:
    // Setter
        void setLives(int totalLives, int lostLives) {
            lives = totalLives - lostLives;
    }
    // Getter
        int getLives() {
            return lives;
    }
        // draws the hangman based on how many lives the player has left
        void drawHangman(int lives) {
            if (lives == 6) {
                cout << endl;
                cout << "-------\n";
                cout << "|     |\n";
                cout << "|\n";
                cout << "|\n";
                cout << "|\n";
                cout << "|\n";
                cout << "----";
                cout << endl; 
            }
            else if (lives == 5) {
                cout << endl;
                cout << "-------\n";
                cout << "|     |\n";
                cout << "|     O\n";
                cout << "|\n";
                cout << "|\n";
                cout << "|\n";
                cout << "----";
                cout << endl;
            }
            else if (lives == 4) {
                cout << endl;
                cout << "-------\n";
                cout << "|     |\n";
                cout << "|     O\n";
                cout << "|     |\n";
                cout << "|\n";
                cout << "|\n";
                cout << "----";
                cout << endl;
            }
            else if (lives == 3) {
                cout << endl;
                cout << "-------\n";
                cout << "|     | \n";
                cout << "|     O \n";
                cout << "|    -| \n";
                cout << "|\n";
                cout << "|\n";
                cout << "----";
                cout << endl;
            }
            else if (lives == 2) {
                cout << endl;
                cout << "-------\n";
                cout << "|     | \n";
                cout << "|     O \n";
                cout << "|    -|- \n";
                cout << "|\n";
                cout << "|\n";
                cout << "----";
                cout << endl;
            }
            else if (lives == 1) {
                cout << endl;
                cout << "-------\n";
                cout << "|     | \n";
                cout << "|     O \n";
                cout << "|    -|- \n";
                cout << "|    / \n";
                cout << "|\n";
                cout << "----";
                cout << endl;
            }
            else {
                cout << endl;
                cout << "-------\n";
                cout << "|     | \n";
                cout << "|     O \n";
                cout << "|    -|- \n";
                cout << "|    | | ";
                cout << "\n|\n";
                cout << "----";
                cout << endl;
            }
        }
};

// reads in the word file and adds the words to the words vector for reference later
void read_word_by_word(string filename, vector<string> &words) {
    fstream file;
    string word;
    file.open(filename.c_str());
    while (file >> word) { 
        words.push_back(word);
    }
    file.close();
}

// uses the guessed letter, the starting word, and the unknown string to determine if a letter has already been guessed or is in the word. If the letter is in the word, the unknown placeholder will
// show the letter instead of the placeholder underscore
int letterGuess(char letter, string word, string& unknown) {
    int i;
    int match = 0;
    int len = word.length();
    for (i = 0; i < len; i++){
        if (letter == unknown[i])
            return 1;
        
        if (letter == word[i]) {
            unknown[i] = letter;
            match+=2;
        }
     
    }
    return match;
}
int main()
{   //creates the empty words vector and calls the fuction to read in the potential words   
    vector<string> words;
    read_word_by_word("words.txt", words);

    // create the player object and sets the lives to 7, as well as creating the unassigned letter and word variable
    Player player1;
    char letter;
    int lostLives = 0;
    player1.setLives(totalLives,lostLives);
    string word;

    // randomly picks one of the 63 words in the words vector to be the unknown word
    srand(time(NULL));
    int n = rand() % 63;
    word = words[n];
    // creates a placeholder that's the length of the unknown word that will be replaced with the letters as correct letters are guessed
    string unknown(word.length(), '_');

    //Basic program beginning and shows the placeholder word
    cout << "\nWelcome to Hangman!\n\n";
    cout << "Please only guess one letter per try\n\n";
    cout << "You have " << totalLives << " tries to try and guess the word.\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

    //while loop that will run until player gets the word or runs out of lives
    while (lostLives < totalLives) {
        //draws the hangman, displays the placeholder variable and asks for the user's guess
        player1.drawHangman(player1.getLives());
        cout << "\n\n" << unknown;
        cout << "\n\nGuess a letter: ";
        cin >> letter;

        // checks if the letter is in the word and subtracts from lives if letter is not in word
        int matches = letterGuess(letter, word, unknown);
        if (matches == 0) {
            cout << "\nThis letter isn't in the word\n";
            lostLives++;
            player1.setLives(totalLives, lostLives);
            cout << "You have " << player1.getLives() << " lives left";
        } else if (matches == 1) {
            cout << "\nYou have already guessed this letter, please guess a different letter.\n";
        } else {
            cout << "\nThis letter is in the word!";
        }
        // displays the win message
        if (word == unknown)
        {   
            player1.drawHangman(player1.getLives());
            cout << "\n\n" << unknown<< "\n\n";
            cout << "Congrats! You guessed the word!\n";
            cout << "The word was : " << word << endl;
            break;
        }
    }
    //displays the lose message
    if (player1.getLives() == 0)
    {   
        player1.drawHangman(player1.getLives());
        cout << "\n";
        cout << "\nSorry, you've been hanged.\n";
        cout << "The word was : " << word << endl;
    }
    return 0;
}