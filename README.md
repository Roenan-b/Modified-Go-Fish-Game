# Go Fish Card Game

## Overview
Welcome to the Go Fish card game implementation! This project focuses on a modified version of Go Fish, utilizing a deck of 36 cards with only faces A and 2-9. The game involves two players: a user (Wilma) and a computer (PC). The objective is to collect books (sets of four cards with the same face), and the player with the most books at the end wins.

## Implementation Details
### Card Deck
- The 36-card deck is implemented using a linked list with the following struct:
    ```c
    typedef struct card_s {
        char suit;
        int face;
        struct card_s *next;
    } card;
    ```
- The `ShuffleCard()` function is implemented using a shuffling algorithm to randomize the deck.

### Game Rules
1. Each player starts with 6 cards drawn from the shuffled deck.
2. Players take turns asking for cards of a particular rank.
3. If the opponent has the requested card(s), they must be given, and the player gets another turn.
4. If the opponent doesn't have the requested card, the player says "Go Fish" and draws a card from the center pile.
5. If the drawn card matches the requested rank, the player gets another turn.
6. The game continues until all 9 books (A, 2-9) are found.

### Winning
The player with the most books at the end is declared the winner.

## Usage
1. Compile the code using an appropriate compiler.
2. Run the executable.
3. Follow on-screen instructions to play the game.
4. Enjoy the strategic challenge of Go Fish!

Feel free to explore the code to understand the implementation details. If you have any questions or suggestions, please feel free to reach out.

Happy gaming! 🃏
