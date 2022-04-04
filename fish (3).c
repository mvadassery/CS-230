#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Creator: Meghana Vadassery
// Class: 230
// Project: Hey, That's My Fish!

// A game coded in C, in which the player competes against the AI in a game called 'Hey, That's My Fish!'. 
// The player and the AI move across the game board, trying to collect as many points as possible. 
// Both the player and the AI can move in 6 directions and as many spaces as they would like. The game continues until neither the AI nor the player can move.
// The game does not make use of arrays, and instead, strictly uses pointers to create the game board and move the player's pointer and AI's pointer to various positions.

// struct Grid contains the pointers required to connect the project together. The pointers for the directions indicate which grid connects to which and how to access it.
struct Grid {
  char data;
  struct Grid * up;
  struct Grid * down;
  struct Grid * left;
  struct Grid * right;
  struct Grid * upLeft;
  struct Grid * upRight;
  struct Grid * downLeft;
  struct Grid * downRight;
};

// The function checking occurs at the end of every game round. It checks to see if either pointer passed is 'trapped'; i.e, if it surrounded by NULL values or '.'. If the pointer is, then it can not move and that player's turns are over.

int checking(struct Grid *ptr) {

  // int flag serves as a value to return. It indicates that so long as there is at least one way to move, then the pointer is not stcuk and can continue to play.
  
  int flag = 1;


  // the following if statements check all 8 directions to see if flag still equals 1, i.e, that it's still possible for the pointer to move
  
  if ((ptr->up) != NULL) {
    if((ptr->up)->data != '.')
      return flag;
  }
  if ((ptr->down) != NULL) {
    if((ptr->down)->data != '.')
      return flag;
  }
  if ((ptr->left) != NULL) {
    if((ptr->left)->data != '.')
      return flag;
  }
  if ((ptr->right) != NULL) {
    if((ptr->right)->data != '.')
      return flag;
  }
  if ((ptr->upLeft) != NULL) {
    if((ptr->upLeft)->data != '.')
      return flag;;
  }
  if ((ptr->upRight) != NULL) {
    if((ptr->upRight)->data != '.')
      return flag;
  }
  if ((ptr->downLeft) != NULL) {
    if((ptr->downLeft)->data != '.')
      return flag;
  }
  if ((ptr->downRight) != NULL) {
    if((ptr->downRight)->data != '.')
      return flag;
  }
  return 0;

}


// The function playerTurn takes care of the player's moves. First, it checks for the move's name and number. Then, it finds its corresponding if case, and then checks to see if the player can move in that direction and if there are enough spaces to move in that direction. Its arguments are the player's pointer and a pointer to the player's score.
struct Grid * playerTurn(struct Grid *ptr, int *playerScore) {
  //points to the name of the move
  char *moveName;

  //contains the number of spaces the player wishes to move
  int moveNo;

  // a copy of the original pointer passed through. this helps in checking if the pointer will go out of bounds if the inputted number of spaces is too high.
  struct Grid *origPtr = ptr;

  //this while loop is always true
  while (1) {

    //player enters their direction and number of moves
    printf("\nEnter the direction you'd like to move in and the number of spaces.\n");
    scanf("%ms %d", &moveName, &moveNo);

    //the inputted direction is compared to the name of directions: up, down, left, right, etc. If it's a match then it will enter its respective case. if not, then the player will be asked to re-enter their direction
    if (strcmp(moveName, "up") == 0) {

      //if the pointer can move up (and is not boardered by a NULL value or a '.'), then it continues. Else, the user will be prompted to re-enter their direction
      if (((ptr)->up != NULL) && (ptr->up)->data != '.') {

	//leave the current spot's data as '.'. This shows that it has been taken
	ptr->data = '.';

	// for the given number of moves, loop through the code, moving the pointer up during every iteration. Each iteration also checks to see if the pointer can still keep moving. If there is a '.' or NULL value that blocks the path, the pointer returns to its original place and the user is prompted to re-enter their direction.
	for (int k = 0; k < moveNo; k++) {
	  if((ptr->up) == NULL) {
	    ptr = origPtr;
	    break;
	  }
	  
	  if ((ptr->up)->data == '.') {
	    ptr= origPtr;
	    break;
	  }
	  
	  ptr = (ptr->up);
	}
	if (ptr == origPtr)
	  continue;

	//take the new position's data and convert it into an integer.
	*playerScore = (ptr->data) - '0';

	//replace the new position's data with the character 'P' to show where the player is
	(ptr)->data = 'P';
	break;
	
      } else {
	printf("Unavailable space. Try again.\n");
      } 
    }

    //the above comments apply for the following 7 iterations

    else if (strcmp(moveName, "down") == 0) {

      if (((ptr)->down != NULL) && (ptr->down)->data != '.') {
	ptr->data = '.';
	for (int k = 0; k < moveNo; k++) {
	  if((ptr->down) == NULL) {
	    ptr = origPtr;
	    break;
	  }
	  
	  if ((ptr->down)->data == '.') {
	    ptr= origPtr;
	    break;
	  }
	  
	  ptr = (ptr->down);
	}
	if (ptr == origPtr) continue;
	
	*playerScore = (ptr->data) - '0';
	
	(ptr)->data = 'P';
		
	break;
      } else {
	printf("Unavailable space. Try again.\n");
      }
    }
    
    
    else if (strcmp(moveName, "left") == 0) {
      if (((ptr)->left != NULL) && (ptr->left)->data != '.') {
	ptr->data = '.';
	for (int k = 0; k < moveNo; k++) {
	  if((ptr->left) == NULL) {
	    ptr = origPtr;
	    break;
	  }
	  
	  if ((ptr->left)->data == '.') {
	    ptr= origPtr;
	    break;
	  }
	  
	  ptr = (ptr->left);
	}
	if (ptr == origPtr) continue;
	
	int x = (ptr->data) - '0';
	*playerScore = x;
	
	(ptr)->data = 'P';
	break;
      } else {
	printf("Unavailable space. Try again.\n");
      }
    }
    
    else if (strcmp(moveName, "right") == 0) {
      if (((ptr)->right != NULL) && (ptr->right)->data != '.') {
	ptr->data = '.';
	
	for (int k = 0; k < moveNo; k++) {
	  if((ptr->right) == NULL) {
	    ptr = origPtr;
	    break;
	  }
	  
	  if ((ptr->right)->data == '.') {
	    ptr= origPtr;
	    break;
	  }
	  
	  ptr = (ptr->right);
	}
	if (ptr == origPtr) continue;
	
	int x = (ptr->data) - '0';
	*playerScore = x;
	
	(ptr)->data = 'P';
	break;
      } else {
	printf("Unavailable space. Try again.\n");
      }
    }
    
    else if (strcmp(moveName, "upLeft") == 0) {
      if (((ptr)->upLeft != NULL) && (ptr->upLeft)->data != '.') {
	ptr->data = '.';
	for (int k = 0; k < moveNo; k++) {
	  if((ptr->upLeft) == NULL) {
	    ptr = origPtr;
	    break;
	  }
	  
	  if ((ptr->upLeft)->data == '.') {
	    ptr= origPtr;
	    break;
	  }
	  
	  ptr = (ptr->upLeft);
	}
	if (ptr == origPtr) continue;                                                                                 
	int x = (ptr->data) - '0';
	*playerScore = x;
	
	(ptr)->data = 'P';
	break;
      } else {
	printf("Unavailable space. Try again.\n");
      }
    }
    
    else if (strcmp(moveName, "upRight") == 0) {
      if (((ptr)->upRight != NULL) && (ptr->upRight)->data != '.') {
	ptr->data = '.';
        for (int k = 0; k < moveNo; k++) {
	  if((ptr->upRight) == NULL) {
	    ptr = origPtr;
	    break;
	  }

	  if ((ptr->upRight)->data == '.') {
	    ptr= origPtr;
	    break;
	  }

	  ptr = (ptr->upRight);
	}
	if (ptr == origPtr) continue;                                                                                        
	int x = (ptr->data) - '0';
	*playerScore = x;
	(ptr)->data = 'P';
	break;
      } else {
	printf("Unavailable space. Try again.\n");
      }
    }

    else if (strcmp(moveName, "downLeft") == 0) {
      if (((ptr)->downLeft != NULL) && (ptr->downLeft)->data != '.') {
	ptr->data = '.';
	for (int k = 0; k < moveNo; k++) {
	  if((ptr->downLeft) == NULL) {
	    ptr = origPtr;
	    break;
	  }

	  if ((ptr->downLeft)->data == '.') {
	    ptr= origPtr;
	    break;
	  }

	  ptr = (ptr->downLeft);
	}
	if (ptr == origPtr) continue;                                                                               
	int x = (ptr->data) - '0';
	*playerScore = x;
	(ptr)->data = 'P';
	break;
      } else {
	printf("Unavailable space. Try again.\n");
      }
    }
    
    else if (strcmp(moveName, "downRight") == 0) {
      if (((ptr)->downRight != NULL) && (ptr->downRight)->data != '.') {
	ptr->data = '.';
	for (int k = 0; k < moveNo; k++) {
	  if((ptr->downRight) == NULL) {
	    ptr = origPtr;
	    break;
	  }
	  
	  if ((ptr->downRight)->data == '.') {
	    ptr= origPtr;
	    break;
	  }
	  
	  ptr = (ptr->downRight);
	}
	if (ptr == origPtr) continue;                                                                              
	int x = (ptr->data) - '0';
	*playerScore = x;
	(ptr)->data = 'P';
	break;
      } else {
	printf("Unavailable space. Try again.\n");
      }
    } else {
      printf("Invalid move. Try again.");
    } 
  }
  return ptr;
}

// The function AI turn focuses on the AI's movement. It uses a randomizer to obtain a direction, the number of moves, and checks to see if it is possible. If not, then it randomizes again.

struct Grid * AITurn (struct Grid *ptr, int *AIScore) {

  // both direction and move are indicated by numbers
  int direction;
  int move;
  
  while (1) {

    // the direction can be any number from 1 to 8, inclusive. they each represent a direction
    direction = 1 + (rand() % 9);

    // the move number can be any number from 1 to 6.
    move = 1 + (rand() % 6);
    
    // each number corresponds to a direction. here, 1 represents up.
    if (direction == 1) {

      // if the pointer is not boardered b a NULL value or '.' in the up direction, then it can move.
      if (((ptr->up) != NULL) && ((ptr->up)->data != '.')) {
	
	ptr->data = '.';
	for (int i = 0; i < move; i++) {
	  
	  if (ptr->up == NULL) continue;
	  if ((ptr->up)->data == '.') continue;
	  ptr = (ptr->up);
	}
	*AIScore = (ptr->data) - '0';
	(ptr)->data = 'A';
	break;
      } else {
	continue;
      }
    }
    
    if (direction == 2) {
      if (((ptr->down) != NULL) && ((ptr->down)->data != '.')) {
	ptr->data = '.';
	for (int i = 0; i < move; i++) {
	  
	  if (ptr->down == NULL) continue;
	  if ((ptr->down)->data == '.') continue;
	  ptr = (ptr->down);
	}
	*AIScore = (ptr->data) - '0';
	(ptr)->data = 'A';
	break;
      } else {
	continue;
      }
    }
    
    if (direction == 3) {
      if (((ptr->left) != NULL) && ((ptr->left)->data != '.')) {
	ptr->data = '.';
	for (int i = 0; i < move; i++) {
	  if (ptr->left == NULL) continue;
	  if ((ptr->left)->data == '.') continue;
	  ptr = (ptr->left);
	  
	}
	*AIScore = (ptr->data) - '0';
	ptr->data = 'A';
	break;
      } else {
	continue;
      }
    }
    
    if (direction == 4) {
      if (((ptr->right) != NULL) && ((ptr->right)->data != '.')) {
	ptr->data = '.';
	for (int i = 0; i < move; i++) {
	  
	  if (ptr->right == NULL) continue;
	  if ((ptr->right)->data == '.') continue;
	  ptr = (ptr->right);
	}
	*AIScore = (ptr->data) - '0';
	(ptr)->data = 'A';
	break;
      } else {
	continue;
      }
    }
    
    if (direction == 5) {
      if (((ptr->upLeft) != NULL) && ((ptr->upLeft)->data != '.')) {
	ptr->data = '.';
	for (int i = 0; i < move; i++) {
	  
	  if (ptr->upLeft == NULL) continue;
	  if ((ptr->upLeft)->data == '.') continue;
	  ptr = (ptr->upLeft);
	}
	*AIScore = (ptr->data) - '0';
	(ptr)->data = 'A';
	break;
      } else {
	continue;
      }
    }
    
    if (direction == 6) {
      if (((ptr->upRight) != NULL) && ((ptr->upRight)->data != '.')) {
	ptr->data = '.';
	for (int i = 0; i < move; i++) {
	  
	  if (ptr->upRight == NULL) continue;
	  if ((ptr->upRight)->data == '.') continue;
	  ptr = (ptr->upRight);
	}
	*AIScore = (ptr->data) - '0';
	(ptr)->data = 'A';
	break;
      } else {
	continue;
      }
    }
    
    if (direction == 7) {
      if (((ptr->downLeft) != NULL) && ((ptr->downLeft)->data != '.')) {
	ptr->data = '.';
	for (int i = 0; i < move; i++) {
	  
	  if (ptr->downLeft == NULL) continue;
	  if ((ptr->downLeft)->data == '.') continue;
	  ptr = (ptr->downLeft);
	}
	*AIScore = (ptr->data) - '0';
	(ptr)->data = 'A';
	break;
      } else {
	continue;
      }
    }
    
    if (direction == 8) {
      if (((ptr->downRight) != NULL) && ((ptr->downRight)->data != '.')) {
	ptr->data = '.';
	for (int i = 0; i < move; i++) {
	  
	  if (ptr->downRight == NULL) continue;
	  if ((ptr->downRight)->data == '.') continue;
	  ptr = (ptr->downRight);
	}
	*AIScore = (ptr->data) - '0';
	(ptr)->data = 'A';
	break;
      } else {
	continue;
      }
    }
    
  }
   return ptr;
}

// the function setup is called to set up the game. It takes in the pointers for the player and AI as arguments. The function iterates through the pointer, connecting each struct Grid to the other
void setUp (struct Grid *ptr, struct Grid *anti) {

  // counter keeps track of how many elements there are, and which one we are currently on/
  int counter = 0;

  // this for loop occurs 36 times: once for each struct Grid. If the grid is on the top row, then the up pointer points to NULL. If the grid is on the bottom row, then the down pointer points to NULL. The boarders are taken care of by pointing to NULL values
  for (int i = 0; i < 36; i++) {
    if (counter <= 5) {
      (ptr+i)->up = NULL;
    } else {
      (ptr+i)->up = (ptr+i-6);
    }
    
    if (counter >= 30) {
      (ptr+i)->down = NULL;
    } else {
      (ptr+i)->down = (ptr+i+6);
    }
    
    if (counter%6 == 0) {
      (ptr+i)->left = NULL;
    } else {
      (ptr+i)->left = (ptr+i-1);
    }
    
    if (counter%6 == 5) {
      (ptr+i)->right = NULL;
    } else {
      (ptr+i)->right = (ptr+i+1);
    }
    
    if ((counter%6 == 0) || (counter <= 5)) {
      (ptr+i)->upLeft = NULL;
    } else {
      (ptr+i)->upLeft = (ptr+i-7);
    }
    
    if ((counter%6 == 5) || (counter <= 5)) {
      (ptr+i)->upRight = NULL;
    } else {
      (ptr+i)->upRight = (ptr+i-5);
    }

    if ((counter%6 == 0) || (counter >= 30)) {
      (ptr+i)->downLeft = NULL;
    } else {
      (ptr+i)->downLeft = (ptr+i+5);
    }

    if ((counter%6 == 5) || (counter >= 30)) {
      (ptr+i)->downRight = NULL;
    } else {
      (ptr+i)->downRight = (ptr+i+7);
    }

    // assigns certain grids with the data value '1'
    if ((counter < 6) || (counter > 29) || (counter%6 == 0) || (counter%6 == 5)) {
      (ptr+i)->data = '1';
    }

    // assigns certain grids with the data value '2'
    if (((counter > 6) && (counter < 11)) || ((counter > 24) && (counter < 29)) || (counter == 13) || (counter == 19) || (counter == 16) || (counter == 22)) {
      (ptr+i)->data = '2';
    }
    
    // assigns certain grids with the data value '3'
    if ((counter == 14) || (counter == 15) || (counter == 20) || (counter == 21)) {
      (ptr+i)->data = '3';
    }
    
    counter++;
  }

  // represents both pointers with 'P' and 'A' so that the user may know where the pointers are
  (ptr)->data = 'P';
  (anti)->data = 'A';
  
  gameRound(ptr);
  
}

// the function game round prints out the gameboard by printing out the data value for each element
void gameRound (struct Grid *ptr) {
  printf(" 1 2 3 4 5 6");
  printf("\n1");
  for (int i = 0; i < 6; i++) {
    printf(" %c", ((ptr+i)->data));
  }
  printf("\n2");
  for (int i = 6; i < 12; i++) {
    printf(" %c", ((ptr+i)->data));
  }
  printf("\n3");
  for (int i = 12; i < 18; i++) {
    printf(" %c", ((ptr+i)->data));
  }
  printf("\n4");
  for (int i = 18; i < 24; i++) {
    printf(" %c", ((ptr+i)->data));
  }
  printf("\n5");
  for (int i = 24; i < 30; i++) {
    printf(" %c", ((ptr+i)->data));
  }
  printf("\n6");
  for (int i = 30; i < 36; i++) {
    printf(" %c", ((ptr+i)->data));
  }
}

// the main function, where the program begins
int main(void) {

  // the original pointer, which uses malloc to allocate enough space for 36 grids
  struct Grid *orig;
  orig = (struct Grid*) malloc (36 * (sizeof(struct Grid)));
  
  // the AI's pointer, which starts 5 positions away
  struct Grid *opp = (orig+5);

  // the initialization for the randomizer
  srand(time(NULL));

  // a pointer used to represent the player's position. it starts at the very first grid
  struct Grid *player = orig;
  
  printf("Welcome to 'Hey, That's my Fish!'.\n");
  printf("As the player, you will move first. Here is the board:\n");
  
  setUp(orig, opp);

  // AIScore contains the score for the AI for one round
  int AIScore = 1;

  // aiScore contains the score for the AI overall
  int aiScore = 0;

  int playerScore = 0;
  int curPlayerScore = 0;
  int playerCheck = 1;
  int AICheck = 1;

  // keeps track of how many rounds have been played
  int playerRunCount = 0;
  int AIRunCount = 0;

  // pointers to keep track of the indivual score obtained each round
  int *plist = (int *) malloc(36 * (sizeof(int)));
  int *olist = (int *) malloc (36 * (sizeof(int)));

  // while the player and ai can still move
  while ((playerCheck == 1) || (AICheck == 1)) {
    
    if (playerCheck == 0) {
      printf("\nNo more moves! Skipped turn.\n");
    } else {
      player = playerTurn(player, &playerScore);
      *(plist + playerRunCount) = playerScore;
      playerRunCount++;
      curPlayerScore += playerScore;
      printf("\nPlayer Score = ");
      
      // printing the sum and list of scores
      for (int i = 0; i < playerRunCount; i++) {
	printf(" %d +", *(plist + i)); 
      }
      printf(" = %d\n", curPlayerScore);  
    }

    
    if (AICheck == 0) {
      printf("\nNo more moves! Skipped turn.\n");
    } else {
      opp = AITurn(opp, &AIScore);
      *(olist + AIRunCount) = AIScore;
      AIRunCount++;
      aiScore += AIScore;
      printf("\nAI Score = ");

      for (int i = 0; i < AIRunCount; i++) {
        printf(" %d +", *(olist + i));
      }
      printf(" = %d\n", aiScore);
    }
      
    gameRound(orig);
    
       
    playerCheck = checking (player);
    AICheck = checking (opp);
    
  }
  
  
  // Game over and comparing of scores to determine the winner
  printf("\nGame over!\n");
  if (curPlayerScore > aiScore) {
    printf("You win! Congratulations!\n");
  } else if (aiScore > curPlayerScore) {
    printf("The AI wins. Better luck next time!\n");
  } else {
    printf("It's a tie! Good game\n");
  }
}
