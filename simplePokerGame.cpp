//Names: Nue Lopez, Alexander R., Dylan Hamilton
//Date: 1/21/2025
//Assignment: Reviewing Procedural Programming 

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Card suits and values are declared
const string SUITS[] = {"Spades ♠", "Hearts ♥", "Diamonds ♦", "Clubs ♣"}; //Added code
const string RANKS[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
int DECK[52]; // Make sure deck has 52 cards
int currentCardIndex = 0;

//NEW CODE:
int counterPlayer = 0;
int counterDealer = 0;


// Starts game with zero cards drawn, and makes sure all 52 cards are in play
void initializeDeck() { 
    for (int i = 0; i < 52; i++) {
        DECK[i] = i;
    }
    currentCardIndex = 0; // Reset the current card index
}

void shuffleDeck() {
    srand(time(0)); // Use srand to randomize cards pulled
    for (int i = 0; i < 52; i++) {
        int index = rand() % 52;
        int temp = DECK[i];
        DECK[i] = DECK[index];
        DECK[index] = temp;
    }
}

int dealCard() {
    return DECK[currentCardIndex++];
}

// getSuit function to get the suit of the card
int getSuit(int cardIndex) {
    return (cardIndex / 13);
}

// cardValue function to get the value of the card
int cardValue(int card) {
    card = card % 13;
    return (card < 9) ? (card + 2) : 10;
}

// Function to deal players cards
int dealInitialPlayerCards() {
    int card1 = dealCard();
    int card2 = dealCard();
    cout << "Your cards: " << RANKS[card1 % 13] << " of " << SUITS[getSuit(card1)] << " and " << RANKS[card2 % 13] << " of " << SUITS[getSuit(card2)] << endl;
    return cardValue(card1) + cardValue(card2);
}

// Function to deal the dealer's cards
int dealInitialDealerCards() {
    int card1 = dealCard();
    cout << "Dealer's card: " << RANKS[card1 % 13] << " of " << SUITS[getSuit(card1)] << endl;
    return cardValue(card1);
}

// Function to get the player's move
int playerTurn(int playerTotal) {
    while (true) {
        cout << "Your total is " << playerTotal << ". Do you want to hit or stand?" << endl;
        string action;
        getline(cin, action);
        if (action == "hit") {
            int newCard = dealCard();
            playerTotal += cardValue(newCard);
            cout << "You drew a " << RANKS[newCard % 13] << " of " << SUITS[getSuit(newCard)] << endl;
            if (playerTotal > 21) {
                //NEW OUTPUT: ADDED EMOJIS
                cout << "BUST! Dealer wins. 😰" << endl;
                counterDealer++; //Added dealer counter.
                return playerTotal;
            }

        } else if (action == "stand") {
            break;
        } else {
            cout << "Invalid action. Please type 'hit' or 'stand'." << endl; // case sensitive, make sure to type in lowercase
        }
    }
    return playerTotal;
}

// Function to get the dealer's move
int dealerTurn(int dealerTotal) {
    while (dealerTotal < 17) {
        int newCard = dealCard();
        dealerTotal += cardValue(newCard);
        cout << "Dealer drew " << RANKS[newCard % 13] << " of " << SUITS[getSuit(newCard)] << endl;
    }
    cout << "Dealer's total is " << dealerTotal << endl;
    return dealerTotal;
}

// Function to report the results and winner of the game
void determineWinner(int playerTotal, int dealerTotal) {
    //ADDED CODE: Emojis
    if (dealerTotal > 21 || playerTotal > dealerTotal) {
        cout << "You win! 😃" << endl; 
        counterPlayer++; //added counter to the player.
    } else if (dealerTotal == playerTotal) {
        cout << "Tie! 🗿" << endl; 
    } else {
        cout << "Dealer wins!" << endl;
    }

}

int main() {
    bool turn = true;
    string playerDecision;

    // Player turn loop
    while (turn) {
        initializeDeck();
        shuffleDeck();

        int playerTotal = dealInitialPlayerCards();
        int dealerTotal = dealInitialDealerCards();

        // Keep game running as long as player doesn't go over 21
        playerTotal = playerTurn(playerTotal);
    
        if (playerTotal > 21) {
            continue;
        }

        dealerTotal = dealerTurn(dealerTotal);
        determineWinner(playerTotal, dealerTotal);

        // Allow player to play again
        cout << "Play Again? (yes or no)" << endl;
        getline(cin, playerDecision);
        transform(playerDecision.begin(), playerDecision.end(), playerDecision.begin(), ::tolower);

        // While player says yes, continue loop and keep playing 
        while (!(playerDecision == "no" || playerDecision == "yes")) {
            cout << "Invalid action. Please type 'yes' or 'no'." << endl;
            getline(cin, playerDecision);
            transform(playerDecision.begin(), playerDecision.end(), playerDecision.begin(), ::tolower);
        }

        // If they say no, end loop and end game
        if (playerDecision == "no") {
            turn = false;
        }
    }

    // Goodbye message, end of game 
    //NEW CODE: ADDED counter.
    cout << "Player Wins: " << counterPlayer << " Dealer Wins: " << counterDealer << endl; 
    cout << "Thanks for playing!" << endl;
    return 0;
}
