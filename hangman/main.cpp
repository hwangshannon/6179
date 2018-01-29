//wow hangman very original

#include <iostream>
#include <string>
#include <vector>

typedef std::string string;

string answer;
string guessWord;
string usedLetters;
int wrong;
int ok_wrongs;
bool notDone;

bool replay(){
    std::cout << "Play again? Y/N: \n";
    char ans;
    std::cin >> ans;
    return std::tolower(ans) == 'y';
}

void updateGuessed(string guess){ //updates known/guessed word
    char charGuess; //make a char
    std::strcpy(&charGuess,guess.c_str());
    for (int i = 0; i<answer.length(); i++){
        if (answer[i] == charGuess){
            guessWord[i] = charGuess;
        }
    }
}

string lowercase(string input){
    for (int i =0; i<input.length(); i++){
        input[i] = tolower(input[i]);
    }
    return input;
}

int main(){
    notDone = true;
    while (notDone){ //loop taking care of multiple games (replay)
        int ok_wrongs;
        std::cout << "Yay Hangman! \n P1: Enter the word you want the other player to guess \n";
        std::cin >> answer;
        answer = lowercase(answer);
        std::cout << "P1: How many mistakes will you allow the other person to make? \n";
        std::cin >> ok_wrongs;
        wrong = 0;
        guessWord = string(answer.length(), '-'); //initial guess: -'s that are length of word
        usedLetters = "";
        
        while (wrong <= ok_wrongs && guessWord != answer){ //loop taking care of individual games
            string guessLetter;
            std::sort(usedLetters.begin(), usedLetters.end());
            std::cout << "P2: You know the word looks like: " << guessWord << "\n" << "So far, you have guessed the letters <" << usedLetters << "> and made " << wrong << "/" << ok_wrongs << " mistakes. \n" ;
            std::cout << "P2: Guess next letter (or the word) pls: \n";
            std::cin >> guessLetter;
            guessLetter = lowercase(guessLetter);
            if (guessLetter.length() > 1){ //guessed a word
                if (guessLetter == answer){ //guessed right word
                    std::cout << "WOW!!! You got it!!!!!!!!!1! \n The word was " << answer << "\n";
                    break;
                }
                //guessed wrong word
                else{
                    std::cout << "you're wrong \n";
                    wrong++;
                }
            }
            else{ //guessed a letter
                if (guessWord.find(guessLetter) != string::npos){ //if already guessed
                    std::cout << "Wow you already guessed that before! sad \n";
                    wrong++;
                }
                else{
                    //if in word
                    if (answer.find(guessLetter) != string::npos){
                        std::cout << "WOW you got one! :^) \n";
                        usedLetters = usedLetters + guessLetter;
                        updateGuessed(guessLetter);
                        //if correctly guessed the last letter in the word
                        if (guessWord.find("-") == string::npos){
                            std::cout << "WOW!!! You got it!!!!!!!!!1! \n The word was " << answer <<"\n";
                            break;
                        }
                    }
                    //else
                    else{
                        std::cout << "W o w you are wrong \n";
                        usedLetters = usedLetters + guessLetter;
                        wrong++;
                    }
                }
            }
            //make disparaging remarks if wrong
            if (wrong > ok_wrongs){
                std::cout << "You died (RIP) \n";
                std::cout << "You failed to guess that the correct word was" << answer << ";-; \n";
                break;
            }
        }
        
        notDone = replay();
    }
    return 0;
}

