/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) Project
/******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[52]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables. You 
 */
 // ♥, ♠, ♦, ♣
const char* suit[4] = {"\U00002665","\U00002660","\U00002666","\U00002663"}; // H, S, D, C
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[52])
{
  /******** You complete ****************/

  for (int i=0; i<NUM_CARDS; i++) { // intializing 0-51 in deck
    cards[i] = i;
  }

  // randomizing 0-51 deck. n=52
  // for i from n−1 downto 1 do
  // j ← random integer such that 0 ≤ j ≤ i
  //     (i.e. use a modulus operation on the random number)
  // exchange a[j] and a[i]
  for (int i=NUM_CARDS-1; i > 0; i--) {
    int j = rand() % (i + 1);
    int tmp = cards[j];
    cards[j] = cards[i];
    cards[i] = tmp;
  }
  
}
/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 *
 *  Must use the suit and type arrays to lookup
 *   the appropriate characters to print.
 */
void printCard(int id)
{
  /******** You complete ****************/
  
  int suit_index = id / 13; // function gets card suit index
  const char* card_suit = suit[suit_index]; 

  int type_index = id % 13; // function gets card type index
  const char* card_type = type[type_index];

  cout << card_type << card_suit;

}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 *
 * Must use the values array to lookup the appropriate
 *  card return value.
 */
int cardValue(int id)
{
  /******** You complete ****************/
  int value_index = id % 13; // determines value of card (2-11)
  const int card_value = value[value_index];
  
  return card_value;
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
 //input phand[9], phandsize
void printHand(int hand[], int numCards)
{
  /******** You complete ****************/
  // loops through hand[] and calls printCard on each card ID within hand[]
  for (int i=0; i<numCards; i++) {
    printCard(hand[i]);
    cout << " ";
  }
  cout << endl;

}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
  /******** You complete ****************/
  int sum = 0;
  int ace_counter = 0;
  bool contains_ace = false;
  // loops through hand[], converting ID's to appropriate value with cardValue function
  // and adding it to sum
  for (int i=0; i<numCards; i++) {
    sum += cardValue(hand[i]);
    
    if (cardValue(hand[i]) == 11) { // check to see if there is an ace, and if so, how many
      contains_ace = true;
      ace_counter++;
    }
  }
  
  if (sum <= 21) {
    return sum;
  }
  if (sum > 21 && contains_ace == false) { 
    return sum;
  }
  if (sum > 21 && contains_ace == true) { 
    // for every ace within the deck, simply subtract -10 (equivalent to changing 11 to 1)
    // and check if sum <= 21.
    for (int i=0; i<ace_counter; i++) {
      sum -= 10;
      if (sum <= 21) {
        return sum;
      }
    }
    return sum;
  }
  return sum;
}


/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  // //---------------------------------------
  // // Do not change this code -- Begin
  // //---------------------------------------
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------
  
  int phandsize = 0;
  int dhandsize = 0;
  int topcard = 0;
  /******** You complete ****************/

  bool play_again = true;
  bool exit_game = false;
  while (play_again == true) {
    shuffle(cards);

    for (int i=0; i<9; i++) { // setting dhand values to 0
      dhand[i] = 0;
    }
    for (int i=0; i<9; i++) { // setting phand values to 0
      phand[i] = 0;
    }

    //giving two cards *alternatingly... (i think thats a word)* to dealer and player
    for (int i=0; i<4; i++) { 
      if (i % 2 == 0) {
        phand[phandsize] = cards[i];
        phandsize++;
      } else {
        dhand[dhandsize] = cards[i];
        dhandsize++;
      }
      topcard++;
    }
    // call display function to print hands of the player and dealer
    cout << "Dealer: ? ";
    printCard(dhand[1]);
    cout << endl;
    cout << "Player: ";
    printHand(phand, phandsize);

    // gets player and dealer sum after initial alternating cards get dealt
    int playersum = getBestScore(phand, phandsize);
    int dealersum = getBestScore(dhand, dhandsize);

    bool player_bust = false;
    bool player_blackjack = false;
    // START OF PLAYERS TURN
    while (player_bust == false) {
      if (playersum == 21) { // if player hits blackjack, just break out of loop
        player_blackjack = true;
        break;
      }
      char user_input;
      cout << "Type 'h' to hit and 's' to stay:" << endl;
      cin >> user_input;
      if (user_input == 'h') { //if h, draw a card
        phand[phandsize] = cards[topcard];
        phandsize++;
        topcard++;
        cout << "Player: ";
        printHand(phand, phandsize);
      } else if (user_input == 's') { // if s, break out of inner loop
        break;
      } else {
        exit_game = true; 
        break;
      }
      playersum = getBestScore(phand, phandsize);
      if (playersum > 21) {
        player_bust = true;
        break;
      }
    }
    
    // check if user inputted anything other than 'y' or 'y', if so, will break out of loop
    if (exit_game) {
      break;
    } 

    //START OF DEALERS TURN
    bool dealer_bust = false;
    bool dealer_blackjack = false;;

    if (player_bust == false) { // only let dealer draw if player has not gone over 21
      while (dealersum <= 16) { // while dealer sum is <= 16, keep drawing cards
        dhand[dhandsize] = cards[topcard];
        dealersum = getBestScore(dhand, dhandsize); 
        if (dealersum > 21) { 
          dealer_bust = true;
          break;
        } else if (dealersum >= 17) {
          break;
        }
        if (dealersum == 21) {
          dealer_blackjack = true;
          break;
        }
        dhandsize++;
        topcard++;
      }
      cout << "Dealer: ";
      printHand(dhand, dhandsize);
    }   

    /** 
      code below checks conditions of variables and determines the appropriate winner,
      and appropriate output message. **i'm sure there is a much more effecient way to
      code for these cases, but this is the best I have so far**
    */
    if (player_bust) {
      cout << "Player busts" << endl;
      cout << "Lose " << playersum << " " << dealersum << endl; 
    } else if (dealer_bust) {
      cout << "Dealer busts" << endl;
      cout << "Win " << playersum << " " << dealersum << endl;
    } else if (player_blackjack) {
      if (dealer_blackjack) { // if player gets blackjack and then dealer gets blackjack after
        cout << "Tie " << playersum << " " << dealersum << endl; 
      }
      cout << "Win " << playersum << " " << dealersum << endl;
    } else if (dealer_blackjack) {
      cout << "Lose " << playersum << " " << dealersum << endl; 
    } else if ((21-playersum) > (21-dealersum)) {
      cout << "Lose " << playersum << " " << dealersum << endl;
    } else if ((21-playersum) < (21-dealersum)) {
      cout << "Win " << playersum << " " << dealersum << endl;
    } else if (playersum == dealersum) {
      cout << "Tie " << playersum << " " << dealersum << endl;
    } else {
      cout << "-_- error occurred sry" << endl; // ideally this line should never be run
    }

    //AFTER either player wins or loses a game...
    cout << endl;
    char play_again_input;
    cout << "Play again? [y/n]" << endl;
    cin >> play_again_input;
    if (play_again_input == 'y') { // if player wants to play again, reset phandsize, dhandsize and topcard to 0
        phandsize = 0;
        dhandsize = 0;
        topcard = 0;
        continue;
    } else if (play_again_input == 'n') { // else if player doesn't want to play again, exit outermost loop
        play_again = false;
        break;
    } else {
        break;
    }
  }
  return 0;
}

