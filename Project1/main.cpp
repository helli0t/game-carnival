#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <thread>   // For std::this_thread::sleep_for
#include <chrono>   // For std::chrono::milliseconds
#include <conio.h>  // For _getch()
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class City {
public:
    string name;
    vector<string> resources;
    vector<int> prices;

    City(string cityName, vector<string> cityResources) : name(cityName), resources(cityResources) {
        for (int i = 0; i < cityResources.size(); ++i) {
            prices.push_back(rand() % 50 + 10); // Randomize prices
        }
    }
};

class Trader {
public:
    string name;
    int capital;
    vector<string> inventory;

    Trader(string traderName, int startingCapital) : name(traderName), capital(startingCapital) {}

    void buyResource(string resource, int price) {
        if (capital >= price) {
            capital -= price;
            inventory.push_back(resource);
            cout << "Bought: " << resource << " (Remaining capital: " << capital << ")" << endl;
        }
        else {
            cout << "Insufficient funds!" << endl;
        }
    }

    void sellResource(string resource, int price) {
        auto it = find(inventory.begin(), inventory.end(), resource);
        if (it != inventory.end()) {
            capital += price;
            inventory.erase(it);
            cout << "Sold: " << resource << " (Remaining capital: " << capital << ")" << endl;
        }
        else {
            cout << "Item not in inventory!" << endl;
        }
    }

    bool scam(int initialPrice) {
        cout << "Do you want to try a scam? (Y/N): ";
        char choice;
        cin >> choice;

        if (choice == 'Y' || choice == 'y') {
            int chance = rand() % 100;
            if (chance > 70) {
                cout << "Scam successful! You gained " << initialPrice << " coins." << endl;
                capital += initialPrice;
                return true;
            }
            else {
                cout << "Scam failed! You lost " << initialPrice / 2 << " coins." << endl;
                capital -= initialPrice / 2;
                return true;
            }
        }

        return false;
    }
};

void playGame7() {
    srand(time(nullptr));

    City city1("City 1", { "Wheat", "Fruit", "Stone" });
    City city2("City 2", { "Axe", "Salt", "Fabric" });
    City tradingPost("Trading Post", { "Goods", "Gems", "Metals", "Spices", "Tools", "Jewelry", "Paintings", "Books", "Clothing", "Electronics" });

    Trader player("Player", 100);

    cout << "Welcome to the Trading Route Game!" << endl;

    while (true) {
        cout << "\n--- " << player.name << " ---" << endl;
        cout << "Capital: " << player.capital << endl;
        cout << "Inventory: ";
        for (const string& item : player.inventory) {
            cout << item << endl;
        }
        cout << endl;

        cout << "\nLocations: 1 - " << city1.name << ", 2 - " << city2.name << ", 3 - " << tradingPost.name << endl;
        int choice;
        cout << "Which location would you like to visit? (1/2/3, 0 to quit): ";
        cin >> choice;

        if (choice == 0) {
            cout << "Exiting the game." << endl;
            break;
        }
        else if (choice == 1) {
            cout << "--- " << city1.name << " ---" << endl;
        }
        else if (choice == 2) {
            cout << "--- " << city2.name << " ---" << endl;
        }
        else if (choice == 3) {
            cout << "--- " << tradingPost.name << " ---" << endl;
        }
        else {
            cout << "Invalid choice!" << endl;
            continue;
        }

        if (choice != 3) {
            cout << "Available resources: ";
            const City& selectedCity = (choice == 1) ? city1 : city2;
            for (int i = 0; i < selectedCity.resources.size(); ++i) {
                cout << i + 1 << " - " << selectedCity.resources[i] << " (" << selectedCity.prices[i] << " coins)" << endl;
            }
            cout << endl;

            int tradeChoice;
            cout << "Which resource would you like to buy or sell? (1-" << selectedCity.resources.size() << ", 0 to cancel): ";
            cin >> tradeChoice;

            if (tradeChoice == 0) {
                continue;
            }
            else if (tradeChoice >= 1 && tradeChoice <= selectedCity.resources.size()) {
                const string& selectedResource = selectedCity.resources[tradeChoice - 1];
                int selectedPrice = selectedCity.prices[tradeChoice - 1];

                cout << "Action: 1 - Buy, 2 - Sell: ";
                int action;
                cin >> action;

                if (action == 1) {
                    player.buyResource(selectedResource, selectedPrice);
                }
                else if (action == 2) {
                    player.sellResource(selectedResource, selectedPrice);
                }
                else {
                    cout << "Invalid action!" << endl;
                }
            }
            else {
                cout << "Invalid choice!" << endl;
            }
        }
        else {
            cout << "Available resources for trade: ";
            for (int i = 0; i < tradingPost.resources.size(); ++i) {
                cout << i + 1 << " - " << tradingPost.resources[i] << " (" << tradingPost.prices[i] << " coins)" << endl;
            }
            cout << endl;

            int tradeChoice;
            cout << "Which resource would you like to buy or sell? (1-" << tradingPost.resources.size() << ", 0 to cancel): ";
            cin >> tradeChoice;

            if (tradeChoice == 0) {
                continue;
            }
            else if (tradeChoice >= 1 && tradeChoice <= tradingPost.resources.size()) {
                const string& selectedResource = tradingPost.resources[tradeChoice - 1];
                int selectedPrice = tradingPost.prices[tradeChoice - 1];

                cout << "Action: 1 - Buy, 2 - Sell: ";
                int action;
                cin >> action;

                if (action == 1) {
                    bool scamSuccessful = player.scam(selectedPrice);
                    if (!scamSuccessful) {
                        player.buyResource(selectedResource, selectedPrice);
                    }
                }
                else if (action == 2) {
                    bool scamSuccessful = player.scam(selectedPrice);
                    if (!scamSuccessful) {
                        player.sellResource(selectedResource, selectedPrice);
                    }
                }
                else {
                    cout << "Invalid action!" << endl;
                }
            }
            else {
                cout << "Invalid choice!" << endl;
            }
        }
    }
}

class Drink {
public:
    Drink(int id, const string& name, double price)
        : id(id), name(name), price(price) {}

    int getID() const {
        return id;
    }

    string getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

private:
    int id;
    string name;
    double price;
};
class Bartender {
public:
    Bartender() : freeDrinksLeft(2) {}

    void showMenu(const vector<Drink>& menu) const {
        cout << "Menu:" << endl;
        for (const Drink& drink : menu) {
            cout << drink.getName() << " - $" << drink.getPrice() << endl;
        }
    }

    void serveDrink(const Drink& drink) const {
        cout << "Serving a " << drink.getName() << "." << endl;
    }

    void chat() const {
        cout << "Bartender: Hello! How can I help you today?" << endl;
        cout << "Bartender: Here are some things we can talk about:" << endl;
        cout << "Bartender: 1. Today's specials" << endl;
        cout << "Bartender: 2. Tell me a joke" << endl;
        cout << "Bartender: 3. Ask for a free drink" << endl;
    }

    void discount() const {
        vector<string> discountResponses = {
            "Bartender: I can offer you a 10% discount on any drink. Just let me know!",
            "Bartender: Looking for a special deal? How about a 10% discount on your next drink?"
        };
        int randomIndex = rand() % discountResponses.size();
        cout << discountResponses[randomIndex] << endl;
    }

    void talkAboutSpecials() const {
        vector<string> specialsResponses = {
            "Bartender: Today's specials are: 20% off on Mojito and Margarita!",
            "Bartender: Looking for something exciting? Our specials today include 20% off on Mojito and Margarita!"
        };
        int randomIndex = rand() % specialsResponses.size();
        cout << specialsResponses[randomIndex] << endl;
    }

    void tellJoke() const {
        vector<string> jokes = {
            "Bartender: Why don't scientists trust atoms? Because they make up everything!",
            "Bartender: Parallel lines have so much in common. It's a shame they'll never meet.",
            "Bartender: How does a penguin build its house? Igloos it together!"
        };
        int randomIndex = rand() % jokes.size();
        cout << jokes[randomIndex] << endl;
    }

    void begForDrink() {
        if (freeDrinksLeft > 0) {
            vector<string> begResponses = {
                "Bartender: Oh, you seem really thirsty! How about a free drink from the house?",
                "Bartender: Well, I guess I can't say no to a thirsty customer. Enjoy your free drink!",
                "Bartender: Alright, I'll make an exception this time. Here's a drink on the house!"
            };
            int randomIndex = rand() % begResponses.size();
            cout << begResponses[randomIndex] << endl;
            freeDrinksLeft--;
        }
        else {
            cout << "Bartender: Sorry, I've already given away my daily limit of free drinks." << endl;
        }
    }

private:
    int freeDrinksLeft;
};


void playGame6() {
    srand(static_cast<unsigned int>(time(0)));

    vector<Drink> menu;
    menu.push_back(Drink(1, "{1}, Mojito", 8.0));
    menu.push_back(Drink(2, "{2}, Cosmopolitan", 10.0));
    menu.push_back(Drink(3, "{3}, Old Fashioned", 12.0));
    menu.push_back(Drink(4, "{4}, Martini", 9.0));
    menu.push_back(Drink(5, "{5}, Margarita", 9.0));

    Bartender bartender;

    while (true) {
        cout << "Welcome to the Bar!" << endl;
        cout << "Here's our menu:" << endl;
        bartender.showMenu(menu);

        char choice;
        do {
            cout << "Enter the number of the drink you want, 'Chat' to talk to the bartender, or 'Discount' for a discount: ";
            string input;
            cin.ignore();
            getline(cin, input);

            transform(input.begin(), input.end(), input.begin(), ::tolower);

            if (input == "chat") {
                bartender.chat();
                cout << "Bartender: What would you like to talk about? (1/2/3): ";
                int chatChoice;
                cin >> chatChoice;

                if (chatChoice == 1) {
                    bartender.talkAboutSpecials();
                }
                else if (chatChoice == 2) {
                    bartender.tellJoke();
                }
                else if (chatChoice == 3) {
                    bartender.begForDrink();
                }
                else {
                    cout << "Bartender: I'm sorry, I didn't understand that." << endl;
                }
            }
            else if (input == "discount") {
                bartender.discount();
            }
            else {
                bool isSpecialInput = (input == "chat" || input == "discount");
                bool drinkFound = false;

                if (!isSpecialInput) {
                    for (const Drink& drink : menu) {
                        if (to_string(drink.getID()) == input) {
                            bartender.serveDrink(drink);
                            drinkFound = true;
                            break;
                        }
                    }
                }

                if (!drinkFound && !isSpecialInput) {
                    cout << "Sorry, we don't have that drink on the menu." << endl;
                }
            }

            cout << "Do you want another drink or action? (y/n): ";
            cin >> choice;
            if (choice == 'n' || choice == 'N') {
                cout << "Thank you for visiting the Bar! Cheers!" << endl;
                return;
            }
        } while (choice == 'y' || choice == 'Y');
    }
}


enum Rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES };

struct Card {
    Rank rank;
    Suit suit;
};

class Deck {
private:
    vector<Card> cards;

public:
    Deck() {
        for (int suit = CLUBS; suit <= SPADES; suit++) {
            for (int rank = ACE; rank <= KING; rank++) {
                cards.push_back({ static_cast<Rank>(rank), static_cast<Suit>(suit) });
            }
        }
    }

    void shuffle() {
        srand(static_cast<unsigned int>(time(0)));
        for (int i = 0; i < cards.size(); i++) {
            int j = rand() % cards.size();
            swap(cards[i], cards[j]);
        }
    }

    Card draw() {
        if (!cards.empty()) {
            Card card = cards.back();
            cards.pop_back();
            return card;
        }
        return { ACE, CLUBS }; // Default card (not used)
    }
};

int getCardValue(const Card& card) {
    switch (card.rank) {
    case JACK:
    case QUEEN:
    case KING:
        return 10;
    default:
        return static_cast<int>(card.rank);
    }
}

void displayCard(const Card& card) {
    string rankString;
    switch (card.rank) {
    case ACE:
        rankString = "A";
        break;
    case JACK:
        rankString = "J";
        break;
    case QUEEN:
        rankString = "Q";
        break;
    case KING:
        rankString = "K";
        break;
    default:
        rankString = to_string(static_cast<int>(card.rank));
    }

    string suitString;
    switch (card.suit) {
    case CLUBS:
        suitString = "\u2663"; // Club
        break;
    case DIAMONDS:
        suitString = "\u2666"; // Diamond
        break;
    case HEARTS:
        suitString = "\u2665"; // Heart
        break;
    case SPADES:
        suitString = "\u2660"; // Spade
        break;
    }

    cout << "┌─────────┐\n";
    cout << "│ " << rankString << "       │\n";
    cout << "│         │\n";
    cout << "│    " << suitString << "    │\n";
    cout << "│         │\n";
    cout << "│       " << rankString << " │\n";
    cout << "└─────────┘\n";
}

void playGame5() {
    Deck deck;
    deck.shuffle();

    int playerScore = 0;
    int dealerScore = 0;

    Card playerHand[10]; // Max 10 cards per hand
    Card dealerHand[10];

    // Initial deal
    playerHand[0] = deck.draw();
    dealerHand[0] = deck.draw();
    playerHand[1] = deck.draw();
    dealerHand[1] = deck.draw();

    playerScore = getCardValue(playerHand[0]) + getCardValue(playerHand[1]);
    dealerScore = getCardValue(dealerHand[0]) + getCardValue(dealerHand[1]);

    cout << "Your cards: \n";
    displayCard(playerHand[0]);
    displayCard(playerHand[1]);
    cout << endl;

    cout << "Dealer's card: \n";
    displayCard(dealerHand[0]);
    cout << endl;

    char choice;
    cout << "Do you want to hit? (y/n): ";
    cin >> choice;

    int playerHandSize = 2;

    while (choice == 'y' || choice == 'Y') {
        playerHand[playerHandSize] = deck.draw();
        playerScore += getCardValue(playerHand[playerHandSize]);
        cout << "Your card: \n";
        displayCard(playerHand[playerHandSize]);
        cout << endl;

        if (playerScore > 21) {
            cout << "Bust! Your score is over 21." << endl;
            break;
        }

        cout << "Do you want to hit? (y/n): ";
        cin >> choice;
        playerHandSize++;
    }

    // Dealer's turn
    while (dealerScore < 17) {
        dealerHand[playerHandSize] = deck.draw();
        dealerScore += getCardValue(dealerHand[playerHandSize]);
        cout << "Dealer's card: \n";
        displayCard(dealerHand[playerHandSize]);
        cout << endl;
        playerHandSize++;
    }

    // Determine winner
    cout << "Your score: " << playerScore << endl;
    cout << "Dealer's score: " << dealerScore << endl;

    if (playerScore > 21) {
        cout << "Dealer wins!" << endl;
    }
    else if (dealerScore > 21) {
        cout << "You win!" << endl;
    }
    else if (playerScore > dealerScore) {
        cout << "You win!" << endl;
    }
    else if (dealerScore > playerScore) {
        cout << "Dealer wins!" << endl;
    }
    else {
        cout << "It's a tie!" << endl;
    }
    char playAgainChoice;
    cout << "Do you want to play again? (y/n): ";
    cin >> playAgainChoice;

    if (playAgainChoice == 'y' || playAgainChoice == 'Y') {
        playGame5(); // Restart the game
    }
    else {
        cout << "Thank you for playing Blackjack!" << endl;
    }
}

enum Choice { ROCK, PAPER, SCISSORS };

Choice getPlayerChoice() {
    int choice;
    cout << "Enter your choice (0 for Rock, 1 for Paper, 2 for Scissors): ";
    cin >> choice;
    return static_cast<Choice>(choice);
}

Choice getComputerChoice() {
    return static_cast<Choice>(rand() % 3);
}

string choiceToString(Choice choice) {
    if (choice == ROCK) return "Rock";
    if (choice == PAPER) return "Paper";
    if (choice == SCISSORS) return "Scissors";
    return "";
}

int determineWinner(Choice playerChoice, Choice computerChoice) {
    if (playerChoice == computerChoice) return 0;
    if ((playerChoice == ROCK && computerChoice == SCISSORS) ||
        (playerChoice == PAPER && computerChoice == ROCK) ||
        (playerChoice == SCISSORS && computerChoice == PAPER)) {
        return 1;
    }
    return -1;
}

void playGame4() {
    srand(static_cast<unsigned int>(time(0)));

    cout << "Let's play Rock-Paper-Scissors!" << endl;

    char playAgain = 'y';

    while (playAgain == 'y' || playAgain == 'Y') {
        Choice playerChoice = getPlayerChoice();
        Choice computerChoice = getComputerChoice();

        cout << "You chose: " << choiceToString(playerChoice) << endl;
        cout << "Computer chose: " << choiceToString(computerChoice) << endl;

        int result = determineWinner(playerChoice, computerChoice);

        if (result == 0) {
            cout << "It's a tie!" << endl;
        }
        else if (result == 1) {
            cout << "Congratulations! You win!" << endl;
        }
        else {
            cout << "Sorry, computer wins!" << endl;
        }

        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
    }

    cout << "Thank you for playing Rock-Paper-Scissors!" << endl;
}

const int width = 20;
const int height = 15;

bool gameOver;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

void playGame1() {
    srand(time(0));

    int choice;
    cout << "Select the difficulty level:" << endl;
    cout << "1. Easy (1 to 10)" << endl;
    cout << "2. Medium (1 to 50)" << endl;
    cout << "3. Hard (1 to 100)" << endl;
    cout << "Enter your choice (1/2/3): ";
    cin >> choice;

    int difficulty;
    if (choice == 1) {
        difficulty = 10;
    }
    else if (choice == 2) {
        difficulty = 50;
    }
    else if (choice == 3) {
        difficulty = 100;
    }
    else {
        cout << "Invalid choice. Exiting." << endl;
        return;
    }

    bool playAgain = true;

    while (playAgain) {
        int targetNumber = rand() % difficulty + 1;

        int guess;
        int attempts = 0;

        cout << "Guess a number between 1 and " << difficulty << "." << endl;

        do {
            cout << "Enter your guess: ";
            cin >> guess;
            attempts++;

            if (guess < targetNumber) {
                cout << "Enter a larger number." << endl;
            }
            else if (guess > targetNumber) {
                cout << "Enter a smaller number." << endl;
            }
            else {
                cout << "Congratulations! You guessed correctly in " << attempts << " attempts." << endl;
            }
        } while (guess != targetNumber);

        char playAgainChoice;
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgainChoice;

        if (playAgainChoice != 'y' && playAgainChoice != 'Y') {
            playAgain = false;
        }
        else {
            system("cls"); // Clear console on Windows
        }
    }

    cout << "Thank you for playing Game 1. Goodbye!" << endl;
}

void playGame2() {
    srand(time(0));

    bool playAgain = true;

    while (playAgain) {
        int choice;
        cout << "Heads (1) or Tails (2)? ";
        cin >> choice;

        int coinFlip = rand() % 2 + 1; // 1 for heads, 2 for tails

        if (coinFlip == choice) {
            cout << "Congratulations! You guessed correctly!" << endl;
        }
        else {
            cout << "Sorry, you guessed wrong." << endl;
        }

        char playAgainChoice;
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgainChoice;

        if (playAgainChoice != 'y' && playAgainChoice != 'Y') {
            playAgain = false;
        }
        else {
            system("cls"); // Clear console on Windows
        }
    }

    cout << "Thank you for playing Game 2. Goodbye!" << endl;
}


void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw() {
    system("cls");

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else {
                bool printTail = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        printTail = true;
                    }
                }
                if (!printTail)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    cout << "Score:" << score << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

void playGame3() {
    srand(static_cast<unsigned int>(time(0)));

    char playAgain = 'y';

    while (playAgain == 'y' || playAgain == 'Y') {
        Setup();

        nTail = 0; // Reset tail length

        while (!gameOver) {
            Draw();
            Input();
            Logic();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        cout << "Game Over!" << endl;
        cout << "Your score: " << score << endl;

        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;

        if (playAgain == 'y' || playAgain == 'Y') {
            system("cls");
        }
    }

    cout << "Thank you for playing!" << endl;
}

int main() {
    int choice;

    do {
        system("cls");
        cout << "Select a game to play:" << endl;
        cout << "{1}. Guess the Number" << endl;
        cout << "{2}. Heads or Tails" << endl;
        cout << "{3}. Snake" << endl;
        cout << "{4}. Rock-Paper-Scissors" << endl;
        cout << "{5}. Blackjack" << endl;
        cout << "{6}. Bartender Simulator" << endl;
        cout << "{7}. Trading Simulator" << endl;
        cout << "{0}. Exit" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            system("cls");
            playGame1();
            break;
        case 2:
            system("cls");
            playGame2();
            break;
        case 3:
            system("cls");
            playGame3();
            break;
        case 4:
            system("cls");
            playGame4();
            break;
        case 5:
            system("cls");
            playGame5();
            break;
        case 6:
            system("cls");
            playGame6();
            break;
        case 7:
            system("cls");
            playGame7();
            break;
        case 0:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 0);

    return 0;
}