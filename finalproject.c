#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Define the card structure
typedef struct card_s {
    char suit;
    int face;
    struct card_s *next;
} card;

// Function prototypes
void initializeDeck(card **deck);
void shuffleDeck(card **deck, int deckSize);
void dealCards(card **deck, card **playerHand, card **computerHand);
void displayHand(card *hand, char playerName[]);
int pullFromHand(card **player1hand, card **player2hand, card **deck, char player1Name[], char player2Name[], int target_face, char userResponse, card **drawnCard);
void checkBooks(card **hand, char playerName[], int *books, int faces[]);
card *createCard(char suit, int faces);
card *getNodeAtIndex(card *deck, int index);
int cardCount(card *hand);
void getUserInput(int *userCard_Choice, card **drawnCard, card **deck);
int goFish(card **hand, card **deck, char playerName[], int target_face);
void drawNewHand(card **playerHand, card **deck);
void printIntro();
void displayBooks(int faces[]);
char getCompUserChoice(int compCard_Choice);
void freeDeck(card **deck) {
    card *current = *deck;
    while (current != NULL) {
        card *temp = current;
        current = current->next;
        free(temp);
    }
    *deck = NULL;
}

int main() {
    char userName[20];

    // Initialize deck, player's hand, and computer's hand
    card *deck = NULL;
    card *playerHand = NULL;
    card *computerHand = NULL;
    int extraTurn = 0;
    card *drawnCard = NULL;
    int playerBooks_num = 0;
    int playerBooks_face[10] = {0};
    int playerCards_num = 0;
    int computerBooks_num = 0;
    int computerBooks_face[10] = {0};
    int computerCard_num = 0;
    int terminate = 0;
    printIntro();
    int flag = 0;

    printf("\n\nEnter your name:");
    scanf("%s", userName);

    initializeDeck(&deck);      //DONE
    shuffleDeck(&deck, cardCount(deck));
    dealCards(&deck, &playerHand, &computerHand);
    int tempVar = cardCount(deck);
    int tempVar2 = cardCount(playerHand);
    int tempVar3 = cardCount(computerHand);
    int totalBooksFound = 0;
    srand(time(NULL));
    printf("\n");

    // Game loop
    char playerInput;
    do {
        int userCard_Choice;
        int compCard_Choice;
        char userChoice = 'i';
        playerCards_num = cardCount(playerHand);
        computerCard_num = cardCount(computerHand);
        if (flag != 0)
        {
            printf("=^..^=   =^..^=   =^..^=    =^..^=    =^..^=    =^..^=    =^..^=\n\n");
        }
        flag++;
        //printf("Deck card count: %d\n", cardCount(deck));
        //printf("=^..^=   =^..^=   =^..^=    =^..^=    =^..^=    =^..^=    =^..^=\n\n");
        // Player's turn
        if (playerCards_num == 0)
        {
            drawNewHand(&playerHand, &deck);
            printf("Getting %s a new hand...\n\n", userName);
            printf("Deck has %d cards remaining\n\n", cardCount(deck));
        }
        else if (computerCard_num == 0)
        {
            drawNewHand(&computerHand, &deck);
            printf("Getting the computer a new hand...\n\n");
            printf("Deck has %d cards remaining\n\n", cardCount(deck));
        }
        //printf("Deck card count: %d\n", cardCount(deck));
        checkBooks(&playerHand, userName, &playerBooks_num, playerBooks_face);
        checkBooks(&computerHand, "Computer", &computerBooks_num, computerBooks_face);
        playerCards_num = cardCount(playerHand);
        computerCard_num = cardCount(computerHand);
        //printf("Deck card count: %d\n", cardCount(deck));
        //INFO DISPLAY
        displayHand(playerHand, userName);
        printf("%s's number of cards: %d\n", userName, cardCount(playerHand));
        printf("%s's number of books: %d\n", userName, playerBooks_num);
        displayBooks(playerBooks_face);
        //printf("Deck card count: %d\n", cardCount(deck));
        //displayHand(computerHand, "Computer");      //DEBUGGING PURPOSES
        printf("Computers number of cards: %d\n", cardCount(computerHand));
        printf("Computers number of books: %d\n", computerBooks_num);
        displayBooks(computerBooks_face);
        //printf("Deck card count: %d\n", cardCount(deck));
        //displayHand(computerHand, "Computer");
        //USERS TURN
        getUserInput(&userCard_Choice, &drawnCard, &deck);
        extraTurn = pullFromHand(&computerHand, &playerHand, &deck, "Computer", userName, userCard_Choice, 'i', &drawnCard);
        //printf("Deck card count: %d\n", cardCount(deck));
        //displayHand(deck, "main");
        //printf("Computer card count: %d\n", cardCount(computerHand));
        while (extraTurn != 0) {
            if ((playerBooks_num + computerBooks_num) == 9) {
                break;
            }

            checkBooks(&playerHand, userName, &playerBooks_num, playerBooks_face);
            printf("Extra Turn!\n\n");
            if (cardCount(computerHand) == 0) {
                drawNewHand(&computerHand, &deck);
                printf("Getting the computer a new hand...\n\n");
                printf("Deck has %d cards remaining\n\n", cardCount(deck));
            }
            extraTurn = 0;
            displayHand(playerHand, userName);
            printf("%s's number of cards: %d\n", userName, cardCount(playerHand));
            printf("%s's number of books: %d\n", userName, playerBooks_num);
            displayBooks(playerBooks_face);
            getUserInput(&userCard_Choice, &drawnCard, &deck);
            extraTurn = pullFromHand(&computerHand, &playerHand, &deck, "Computer", userName, userCard_Choice, 'i',
                                     &drawnCard);
            checkBooks(&playerHand, userName, &playerBooks_num, playerBooks_face);

        }
        if ((playerBooks_num + computerBooks_num) == 9) {
            break;
        }
        //printf("Deck card count: %d\n", cardCount(deck));
        checkBooks(&playerHand, userName, &playerBooks_num, playerBooks_face);

        printf("=^..^=   =^..^=   =^..^=    =^..^=    =^..^=    =^..^=    =^..^=\n\n");
        displayHand(playerHand, userName);
        //printf("Deck card count: %d\n", cardCount(deck));
        printf("%s's number of cards: %d\n", userName, cardCount(playerHand));
        printf("%s's number of books: %d\n", userName, playerBooks_num);
        displayBooks(playerBooks_face);
        printf("\n");
        playerCards_num = cardCount(playerHand);
        computerCard_num = cardCount(computerHand);
        //displayHand(computerHand, "Computer");
        if (playerCards_num == 0)
        {
            drawNewHand(&playerHand, &deck);
            printf("Getting %s a new hand...\n\n", userName);
            printf("Deck has %d cards remaining\n\n", cardCount(deck));
            //printf("Deck card count: %d\n", cardCount(deck));
        }
        else if (computerCard_num == 0)
        {
            drawNewHand(&computerHand, &deck);
            printf("Getting the computer a new hand...\n\n");
            printf("Deck has %d cards remaining\n\n", cardCount(deck));
            //printf("Deck card count: %d\n", cardCount(deck));
        }

        //COMPUTERS TURN
        compCard_Choice = 1 + ((rand() % 9));
        char compUserChoice = 'i';  // New variable for computer's turn
        checkBooks(&computerHand, "Computer", &computerBooks_num, computerBooks_face);
        compUserChoice = getCompUserChoice(compCard_Choice);
        //printf("Deck card count: %d\n", cardCount(deck));

        if (compUserChoice == 'y') {
            extraTurn = pullFromHand(&playerHand, &computerHand, &deck, userName, "Computer", compCard_Choice, compUserChoice, &drawnCard);
            while ((extraTurn != 0) && (terminate == 0)) {
                if ((playerBooks_num + computerBooks_num) == 9) {
                    terminate++;
                    break;
                }
                if (terminate != 0)
                {
                    break;
                }
                printf("Extra Turn!\n\n");
                extraTurn = 0;
                compCard_Choice = 1 + ((rand() % 9));
                compUserChoice = getCompUserChoice(compCard_Choice);
                    if(compUserChoice == 'y')
                    {
                        extraTurn = pullFromHand(&playerHand, &computerHand, &deck, userName, "Computer", compCard_Choice, compUserChoice, &drawnCard);
                    }
                    else
                    {
                        extraTurn = goFish(&computerHand, &deck, "Computer", compCard_Choice);
                    }


                checkBooks(&computerHand, "Computer", &computerBooks_num, computerBooks_face);
            }
        } else {
            if ((playerBooks_num + computerBooks_num) == 9) {
                break;
            }
            extraTurn = goFish(&computerHand, &deck, "Computer", compCard_Choice);
            checkBooks(&computerHand, "Computer", &computerBooks_num, computerBooks_face);
            if (extraTurn != 0) {
                if ((playerBooks_num + computerBooks_num) == 9) {
                    break;
                }
                compCard_Choice = 1 + ((rand() % 9));
                while ((compUserChoice != 'y') && (compUserChoice != 'n')) {
                    if (compCard_Choice == 1) {
                        printf("\nDo you have a(n) A in your hand?\nEnter 'y' for yes or 'n' for \"Go Fish\":");
                    } else {
                        printf("\nDo you have a(n) %d in your hand?\nEnter 'y' for yes or 'n' for \"Go Fish\":", compCard_Choice);
                    }
                    scanf(" %c", &compUserChoice);
                    if (drawnCard != NULL && drawnCard->face == compCard_Choice)
                    {
                        extraTurn++;
                    }
                }
            }
        }

        checkBooks(&computerHand, "Computer", &computerBooks_num, computerBooks_face);
        if (cardCount(computerHand) == 0)
        {
            drawNewHand(&computerHand, &deck);
            //printf("Deck card count: %d\n", cardCount(deck));
        }
        //printf("Deck card count before: %d", cardCount(deck));
        shuffleDeck(&deck, cardCount(deck));        //Shuffles deck after each round
        //printf("Deck card count after: %d", cardCount(deck));
        totalBooksFound = playerBooks_num + computerBooks_num;
        //printf("Total books found spo far: %d\n\n", totalBooksFound);
    } while (totalBooksFound < 9);
    if (playerBooks_num > computerBooks_num) {
        printf("YOU WIN!!!!!!\n\nThank you for playing");
    } else {
        printf("YOU LOST!\n\n");
    }

    // Display the winner and free allocated memory
//    freeDeck(&playerHand);
//    freeDeck(&computerHand);
//    freeDeck(&deck);
    free(playerHand);
    free(computerHand);
    free(deck);

    return 0;
}




/**********************************************************************************************************************************/
void initializeDeck(card **deck) {
    char suits[] = {'C', 'D', 'H', 'S'};
    int face[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 9; j++) {
            card *newCard = createCard(suits[i], face[j]);
            if (newCard != NULL) {
                newCard->next = *deck;
                *deck = newCard;
            }
        }
    }

}
void shuffleDeck(card **deck, int deckSize) {
    card *temp1;
    card *temp2;
    int randNum;
    srand(time(NULL));

    for (int i = 0; i < 200; i++) {
        for (int j = 0; j < deckSize; j++) {
            randNum = rand() % deckSize;
            if (randNum != j) {
                temp1 = getNodeAtIndex(*deck, j);
                temp2 = getNodeAtIndex(*deck, randNum);

                // Swap face and suit
                int tempNum = temp1->face;
                char tempSuit = temp1->suit;
                temp1->face = temp2->face;
                temp1->suit = temp2->suit;
                temp2->face = tempNum;
                temp2->suit = tempSuit;
            }
        }
    }
}

void dealCards(card **deck, card **playerHand, card **computerHand) {
    for (int i = 0; i < 6; i++)
    {
        card *playerCard = *deck;
        *deck = (*deck)->next;
        playerCard->next = *playerHand;
        *playerHand = playerCard;

        card *computerCard = *deck;
        *deck = (*deck)->next;
        computerCard->next = *computerHand;
        *computerHand = computerCard;


    }

}
void displayHand(card *hand, char playerName[]) {
    card *temp = hand;
    printf("%s's hand:\n", playerName);
    while (temp != NULL)
    {
        if (temp->face == 1)
        {
            printf("A%c ", temp->suit);
        }
        else {
            printf("%d%c ", temp->face, temp->suit);
        }
        temp = temp->next;
    }
    printf("\n");
}
int pullFromHand(card **player1hand, card **player2hand, card **deck, char player1Name[], char player2Name[], int target_face, char userResponse, card **drawnCard) {
    card *current = *player1hand;
    card *prev = NULL;
    int flag = 0;
    int test = 0;

    while (current != NULL) {
        test++;
        if (current->face == target_face) {
            flag++;
            card *temp = current->next;  // Save the next card

            if (prev == NULL) {
                *player1hand = temp;
            } else {
                prev->next = temp;
            }

            current->next = *player2hand;
            *player2hand = current;
            current = temp;

            // Do not update current here
        } else {
            prev = current;
            current = current->next;  // Update current to the next card
        }
    }

    if (*drawnCard != NULL && (*drawnCard)->face == target_face) {
        printf("Extra Turn!\n\n");
        card *temp = *drawnCard;  // Save the drawn card
        *drawnCard = NULL;  // Reset the drawn card pointer
        temp->next = *player1hand;  // Add the drawn card to player1's hand
        *player1hand = temp;
        flag++;  // Increment extra turns
    }

    if (userResponse == 'y') {
        if (flag == 0) {
            if (target_face == 1) {
                printf("\nA is NOT in the hand\n\n");
            } else {
                printf("\n%d is NOT in the hand\n\n", target_face);
            }
            flag = goFish(player2hand, deck, player2Name, target_face);
        } else {
            if (target_face == 1) {
                printf("\nPulling the A's from the hand...\n\n");
            } else {
                printf("\nPulling the %d's from the hand...\n\n", target_face);
            }
        }
    } else {
        if (flag == 0) {
            flag = goFish(player2hand, deck, player2Name, target_face);
        } else {
            if (target_face == 1) {
                printf("\nPulling the A's from the hand...\n\n");
            } else {
                printf("\nPulling the %d's from the hand...\n\n", target_face);
            }
        }
    }

    return flag;  // Return the number of extra turns
}


int goFish(card **hand, card **deck, char playerName[], int target_face) {
    int extraTurns = 0;
    printf("\n><(((('> ><(((('> ><(((('>\n");
    printf("~~~ ~~~ Go Fish ~~~ ~~~\n");
    printf("><(((('> ><(((('> ><(((('>\n\n\n");

    if (*deck != NULL) {
        card *cardDrawn = *deck;
        *deck = (*deck)->next;
        cardDrawn->next = NULL;  // Ensure the new card's next is set to NULL
        if(cardDrawn->face == target_face)
        {
            extraTurns++;
        }

        // If the hand is empty, set *hand to the new card
        if (*hand == NULL) {
            *hand = cardDrawn;
        } else {
            card *lastCard = *hand;

            // Find the last card in the hand
            while (lastCard->next != NULL) {
                lastCard = lastCard->next;
            }

            // Insert the new card at the end of the hand
            lastCard->next = cardDrawn;
        }
            printf("%s drew from the deck\n\n", playerName);
        // Update deck card count

    } else {
        printf("Deck is empty\n\n");
        // Update deck card count

    }
    return extraTurns;
}

void checkBooks(card **hand, char playerName[], int *books, int faces[]){
    card *current = *hand;

    int facesCount[10] = {0};
    while (current != NULL)
    {
        facesCount[current->face]++;
        current = current->next;
    }
    for (int i=1;i<=9;i++)
    {
        if (facesCount[i] == 4)
        {
            if (i == 1){
                printf("%s found a book of A!!!!!!!!\n\n", playerName);
            }
            else {
                printf("%s found a book of %d!!!!!!!!\n\n", playerName, i);
            }
           // faces[*books]=i+1;
            (*books)++;
            faces[i]++;
            card *current = *hand;
            card *prev = NULL;

            while (current != NULL)
            {
                if ((current->face) == i) {
                    card *temp = current->next;  // Store the next node
                    if (prev == NULL) {
                        *hand = temp;
                    } else {
                        prev->next = temp;
                    }
                    free(current);
                    current = temp;  // Update current
                }else {
                    prev = current;
                    current = current->next;
                }
            }
        }
    }


}
card *createCard(char suit, int face) {
    card *newCard = (card *) malloc(sizeof(card));
    if (newCard != NULL) {
        newCard->face = face;
        newCard->suit = suit;
        newCard->next = NULL;
    }
    return newCard;
}
card *getNodeAtIndex(card *deck, int index)
{
    card *current = deck;
    for (int i = 0; i < index && current != NULL; i++)
    {
        current = current->next;
    }
    return current;
}
int cardCount(card *hand) {
    card *current = hand;
    int num_cards = 0;
    while (current != NULL) {
        current = current->next;
        num_cards += 1;
    }
    return num_cards;

}
void getUserInput(int *userCard_Choice, card **drawnCard, card **deck) {
    int faceValue = 0;
    char faceVal[2] = {'q'};
    while (1) {
        printf("Which card (A, 2 - 9) do you want to ask for?");
        scanf(" %s", faceVal);

        if (faceVal[0] == 'A') {
            faceValue = 1;
            *userCard_Choice = faceValue;
            break;
        } else {
            faceValue = atoi(faceVal);
            if ((faceValue >= 2) && (faceValue <= 9)) {
                *userCard_Choice = faceValue;
                break;
            }
        }
    }

    // Draw a card from the deck and set it to *drawnCard
}

void drawNewHand(card **playerHand, card **deck) {
    int count = 0;

    // Traverse the deck and add cards to the player's hand
    while (*deck != NULL && count < 6) {
        count++;

        // Save the current card and move to the next card in the deck
        card *current = *deck;
        *deck = (*deck)->next;

        // Set the next pointer of the current card to NULL (disconnect it from the deck)
        current->next = NULL;

        // Add the current card to the player's hand
        if (*playerHand == NULL) {
            *playerHand = current;
        } else {
            card *lastCard = *playerHand;
            while (lastCard->next != NULL) {
                lastCard = lastCard->next;
            }
            lastCard->next = current;
        }
    }
}


void printIntro()
{
    int halfWay = 50;
    printf(
            "    ,%%&& %%&& %%\n"
            "   ,%%&%% %% &%% %%&\n"
            "  %%& %%&%% &%% &%% %&%\n"
            " %%&%& &%% %&% &%% %&%&,\n"
            " &%&% &%% %& %%& %& &%%%\n"
            "%%& %&%& %&%&% %&% %&%&%&\n"
            "&%&% %&% %%&%& %& &% %%&%&\n"
            "&& %&% %&%& %&% %&%%&%&'%&\n"
            " '%&% %&% %&%& %&&% &%%%\n"
            "  % %& %& &%% %&% &%%%\n"
            "    `\\%%.'  /`%&'\n"
            "      |    |            /`-._           _\\\\/\n"
            "      |,   |_          /     `-._ ..--~`_\n"
            "      |;   |_`\\_      /  ,\\\\.~`  `-.\\ _  ^\n"
            "      |;:  |/^}__..-, @   .~`    ~    `o ~\n"
            "      |;:  |(____.-'     '.   ~   -    `    ~\n"
            "      |;:  |  \\ / `\\       //.  -    ^   ~\n"
            "      |;:  |\\ /' /\\_\\_        ~. _ ~   -   //- \n"
            "     / ;:   \\ '--' `---`           `\\\\//-\\\\///\n\n"
    );


    printf(
            " GGG           FFFF        h     !!!\n"
            "G              F   ii      h     !!!\n"
            "G  GG  ooo     FFF     sss hhh   !!!\n"
            "G   G  o o     F   ii  s   h  h    \n"
            " GGG   ooo     F   ii sss  h  h  !!!\n"
    );
    printf("\n>>>>>>>>>>>>>>>>>>>>>>Welcome!<<<<<<<<<<<<<<<<<<<<<<\n\nThis a modified version of the classic card game 'Go Fish' created by Roenan Bingle\n");
    printf("This game uses only 36 cards (Aces and 2-9) and each player gets only 6 cards to start.\n");
    printf("NOTES:\nIf the player requests a card and it is found in the other players deck, that player gets another turn\nIf the requested card is drawn from the main deck after 'Go Fish' then that player also gets another turn\n");
    printf("\n****GAME KEY****\nS = Spades\nC = Clubs\nD = Diamonds\nH = Hearts\nA = Ace\n");

}
void displayBooks(int faces[]) {
    int flag = 0;
    printf("Books:");

    for (int i = 1; i < 10; i++) {
        if (faces[i] >= 1) {
            flag++;
            if (i == 1)
            {
                printf(" A");
            }else {
                printf(" %d", i);
            }
        }
    }

    if (flag == 0) {
        printf(" None");
    }

    printf("\n\n");
}
char getCompUserChoice(int compCard_Choice) {
    char compUserChoice = 'i';

    while ((compUserChoice != 'y') && (compUserChoice != 'n')) {
        if (compCard_Choice == 1) {
            printf("\nDo you have a(n) A in your hand?\nEnter 'y' for yes or 'n' for \"Go Fish\":");
        } else {
            printf("\nDo you have a(n) %d in your hand?\nEnter 'y' for yes or 'n' for \"Go Fish\":", compCard_Choice);
        }
        scanf(" %c", &compUserChoice);
    }
}