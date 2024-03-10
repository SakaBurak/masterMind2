#include <iostream>
#include <string>
#include <limits> // numeric_limits için gerekli baþlýk dosyasý

using namespace std;

string getInput(const string &prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

//Kontrol
bool isValidCode(const string &code) {
    if (code.length() != 4) return false;

    string validColors = "RGBPYM";
    for (int i = 0; i < 4; ++i) {
        if (validColors.find(code[i]) == string::npos) {
            return false;
        }
        for (int j = i + 1; j < 4; ++j) {
            if (code[i] == code[j]) {
                return false; // Kod içinde ayný karakterlerin tekrarý, geçersiz kod
            }
        }
    }

    return true;
}

//Geri Bildirim
string calculateFeedback(const string &secretCode, const string &guessCode) {
    string feedback;
    for (int i = 0; i < 4; ++i) {
        if (secretCode[i] == guessCode[i]) {
            feedback += 'R';
        } else if (secretCode.find(guessCode[i]) != string::npos) {//var ama yeri yanlýþ olduðu için
            feedback += 'W';
        }
    }
    return feedback;
}

int main() {
    string player1, player2;
    int totalRuns;
    cout << "Please enter the names of the players: ";
    cin>>player1>>player2;
    cout << "Welcome " << player1 << " and " << player2 << endl;
    cout<<endl;
    cout<<endl;

    do {
        cout << "Please enter the number of runs: ";
        if(!(cin >> totalRuns) || totalRuns <= 0 || totalRuns % 2 != 0){
        	cout << "Invalid number of runs!" << endl;
        	 cin.clear();
        	 cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
    } while (totalRuns <= 0 || totalRuns % 2 != 0);

    int player1Score = 0, player2Score = 0;

    for (int run = 1; run <= totalRuns; ++run) {
        string secretCode, guessCode;
        string currentCodeMaker = (run % 2 != 0) ? player1 : player2;
        string currentCodeBreaker = (run % 2 != 0) ? player2 : player1;

        cout << currentCodeMaker << ", it is your turn to select the secret!" << endl;
        do {
            secretCode = getInput("Valid colors: R - Red, G - Green, B - Blue, P - Purple, Y - Yellow, M - Magenta \n"
                                  + currentCodeMaker + ", please enter your secret: ");
            if (!isValidCode(secretCode)){
            	//cout << "Invalid secret!" << endl;
			}
        } while (!isValidCode(secretCode));

        for (int chance = 1; chance <= 6; ++chance) {
            cout << currentCodeBreaker << ", please enter your guess: ";
            do {
                guessCode = getInput("");
                if(!isValidCode(guessCode)){
                	cout<<"Invalid guess!"<<endl;
				}
            } while (!isValidCode(guessCode));

            if (secretCode == guessCode) {
                cout << currentCodeBreaker << ", you won this run!" << endl;
                (currentCodeBreaker == player1) ? ++player1Score : ++player2Score;
                break;
            } else {
                string feedback = calculateFeedback(secretCode, guessCode);
                cout << feedback << endl;
                if (chance == 6) {
                    cout << currentCodeBreaker << ",  you're out of chances, you lost this run!" << endl;
                    (currentCodeMaker == player1) ? ++player1Score : ++player2Score;
                }
            }
        }
    }

    cout << "The game has ended!" << endl;
    cout << player1 << ": " << player1Score << " - " << player2 << ": " << player2Score << endl;

    if (player1Score == player2Score) {
        cout << player1 << " and " << player2 << ", there is a tie!" << endl;
    } else {
        cout <<"Congrats " <<((player1Score > player2Score) ? player1 : player2) << ", you have won the game!" << endl;
    }

    return 0;
}

