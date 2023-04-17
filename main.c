#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



/*Declaring below variables as global since they are needed and used in most functions */
  char menu1[]=
    "1. Start the game\n0. Exit the game\n";
    char menu2[]=
    "1. Choose the length of the word\n2. Modify the difficulty level(Number of misses allowed)\n0. Exit the game \n";
    int miss=10;


//A function To display the First menu and get the desired input:
int menuloop1(void)
{
    int flag=0,choice;
     do
  {
      fflush(stdin);
      if(flag)
        printf("\nWrong input. Please refer to the menu...\n");
    printf("%s",menu1);
    scanf("%d", &choice);
      printf(" \n");
        flag=1;       //For the Next cycle of the loop as the input will be wrong.
  }while(choice!=1 && choice !=0);

  return choice;
}

void setNumberOfMisses(void)
{
            /*The loop below deals with getting the number of misses allowed and comes back to the second menu*/
                do
            {

                if(miss<1)
                    printf("\nWrong input. Number of misses allowed starts from 1...");
            printf("\nPlease set the number of allowed misses: \n");
             fflush(stdin);
             miss=-1;
            scanf("%d",&miss);

            }while(miss<1);
}

//A function To display the second menu and get the desired input:
int menuLoop2(void)
{
    int flag=0,choice;

    do
    {
        fflush(stdin);
        if (flag)
           printf("\nWrong input. Please refer to the menu...\n");
        printf("%s\n",menu2);
        choice=-1;
        scanf("%d", &choice);
       printf("\n");
       if (choice==0 || choice==1 || choice ==2)
           flag=0;            //For the Next cycle of the loop as the input will be wrong.
           else flag=1;
        if (choice==2)
          {
                setNumberOfMisses();
            printf("\nBack to the menu. Choose below...\n");
          }

    }while (choice !=0 && choice!=1);

    return choice;
}



// A function to read the file that contains the words and selects a random word of a given length
void getRandomWord(char *word, int length) {
  FILE *wordList = fopen("words.txt", "r");
  if (wordList == NULL) {
    printf("\n\n\n      Could not open the file :(");
    return;
  }
  // A structure to represent a node in the linked list
struct Node {
  char *word;
  struct Node *next;
};

  // Create the head of the linked list
  struct Node *head = NULL;
  struct Node *tail = NULL;

  // Read the file and add words of the desired length to the linked list
  char buff[17];
  while (fscanf(wordList, "%s", buff) == 1) {
    if (strlen(buff) == length) {
      // Allocate memory for a new node and initialize its fields
      struct Node *node = malloc(sizeof(struct Node));
      node->word = strdup(buff);
      node->next = NULL;

      // Add the node to the linked list
      if (head == NULL) {
        head = node;
      } else {
        tail->next = node;
      }
      tail = node;
    }
  }
  fclose(wordList);

  // Select a random word from the linked list
  srand((unsigned)time(NULL));
  int count = 0;
  struct Node *current = head;
  while (current != NULL) {
    count++;
    if (rand() % count == 0) {
      strcpy(word, current->word);
    }
    current = current->next;
  }

  // Free the memory used by the linked list
  while (head != NULL) {
    struct Node *temp = head;
    head = head->next;
    free(temp->word);
    free(temp);
  }
}


//this is an alternate function to retrieve the word
/*A function to read the file that contains the words and selects a random word of a given length*/
/* void getRandomWord(char *word,int length)
{

 FILE *wordList;
int cnt=0;
char buff[17];  //to temporarily store a word maximum length of which might be 16.
wordList=fopen("words.txt","r");

if(wordList==NULL)
{
    printf("\n\n\n      Could not open the file :(");
    return;
}
/*The loop below counts number of words of a length given by User in the file*/
/*while(fscanf(wordList,"%s",buff)==1)
{
   if(strlen(buff)==length)
    cnt++;
}
// Double pointer memory allocation to store the words of a length given by User
char **wordSelect=(char**)malloc(cnt*sizeof(char*));
for(int k=0;k<cnt;k++)
    wordSelect[k]=(char*)malloc(length*sizeof(char));
int i=0;  //To index string in "wordSelect".
rewind(wordList);
//Below the loop checks words in the file for the length and in case satisfied stores them in "wordSelect".
while(fscanf(wordList,"%s",buff)==1)
{
    if(strlen(buff)==length)
    {
        wordSelect[i]=strdup(buff);
        i++;
    }
}

  fclose(wordList);

  srand((unsigned)time(NULL));
int random=rand()%cnt+1;    // To get a random number from 1 to "cnt"

for(int k=0;k<length;k++)
  {
      //Storing the word stored in index "random-1" to "word"
      word[k]=wordSelect[random-1][k];
      word[k+1]='\0';
  }
//Freeing the double pointer which stored words number of which is "cnt"
for(int k=0;k<cnt;k++)
    free(wordSelect[k]);
  free(wordSelect);
} */





//A function to get length from User for the word that is to be guessed
int getLength(void)
{
    int length=0;
    //Below the loop gets "length" from User making sure it is in correct range.
       do
   {
         fflush(stdin);
           printf("\nHow many letters would you like a word to contain? (Range is from 1 to 16)\n");
               scanf("%d", &length);
       if(length<1 || length>16)
        printf("\n\nOut of range or incorrect input.\nPlease, choose the length of the word from the range\n");

   }while(length<1 || length>16);
   return length;
}


//A function to get a letter when User start guessing the word
char getGuess(void)
{
    char guess;
    //The loop below runs as long as newline character is not inserted
    do
    {
   scanf("%c", & guess);
   fflush(stdin);   //flushes after one input
   if(guess=='0')
  {
      break;
  }
    }while(guess=='\n');  //As the key Enter can be stored in "guess". We don't want this

return guess;
}
int main()
{
    int length,choice;
    char guess;



    printf("\n\n\n");

     printf("    **      **   **********   **     **   ********    **          **   **********   **     **\n");
     printf("    **      **   **********   ***    **   ********    ***        ***   **********   ***    **\n");
     printf("    **      **   **      **   ****   **   **          ****      ****   **      **   ****   **\n");
     printf("    **********   **********   ** **  **   **          ** **    ** **   **********   ** **  **\n");
     printf("    **********   **********   **  ** **   **   ****   **  **  **  **   **********   **  ** **\n");
     printf("    **      **   **      **   **   ****   **     **   **   ****   **   **      **   **   ****\n");
     printf("    **      **   **      **   **    ***   *********   **          **   **      **   **    ***\n");
     printf("    **      **   **      **   **     **   *********   **          **   **      **   **     **\n");

    printf("\n\n\n");
    printf("                Hello, are you ready to play? Keep in mind, you can be hanged. Choose below...");
    printf("\n\n\n");

    //Getting choice of a User for the first menu.
choice=menuloop1();

  if(choice==0)   //In case User enters zero.
  {
        printf("\n                  The game is terminated!\n\n\n");
        return 0;
  }

   printf("\n");
   //getting choice of a User for the second menu.
choice=menuLoop2();

  if(choice==0)   //In case User enters zero.
  {
      printf("\n                  The game is terminated!\n\n\n");
    return 0;
  }

//Getting a length for word that user wants to guess
length=getLength();

char *word=(char*)malloc((length+1)*sizeof(char));
word[0]='\0';
//Getting a word randomly according to the length
getRandomWord(word,length);
if (word[0]=='\0')
{
    printf("\n\nThe game, unfortunately, terminates here... Please try again.\n\n\n");
    return 0;
}

char *dashes=(char*)malloc((length+1)*sizeof(char));  //To represent the word in dashes and reveal them
char *misses=(char*)malloc((miss+1)*sizeof(char));    //To display the letters the user missed
char *repeatGuess=(char*)malloc((miss+length)*sizeof(char));      //To warn The User of an already guessed letter

for(int k=0;k<length;k++)
{
    dashes[k]='-';
    dashes[k+1]='\0';
}
misses[0]='\0';   //"misses" initially contains nothing.
printf("\n\n\n            Please, start guessing letter by letter\n");
printf("Bear in mind, the word might contain Upper or Lower case lettes\n");
       printf("\n\n\n%s",dashes);
       printf("                   misses: %s (%d left.)\n\n",misses,miss);

int misscount=0;               //To index a string in "misses"
int repeatcnt=0;              //To index a string in "repeatGuess"
int repeatFlag=0;            //To be inactivated for the first cycle of the loop

do
{
    int missFlag=1;   //It is assumed it will be a miss
//getting a guess fro the User.
    guess=getGuess();

   if(guess=='0')
  {
      printf("\n                  The game is terminated!\n\n\n");
      break;
  }
        if(repeatFlag)   //It is inactive in the first cycle. from the second it checks for repeats
       {
            //If it is repeated it continues to the next cycle meaning no need to check for correct or wrong
           if(strchr(repeatGuess,guess)!=NULL)
        {
            printf("\n      You have already guessed \"%c\". Please, try another letter.\n",guess);
            printf("\n%s",dashes);
            printf("                   misses: %s (%d left.)\n\n",misses,miss);
            continue;
        }
       }
        repeatFlag=1;
   for(int k=0;word[k]!='\0';k++)
   {
      if(word[k]==guess)  //In case the guess is correct
        {
            dashes[k]=word[k];  //Stores the letter indexed at "k" from "word" into "dashes"
            missFlag=0;  //Sets missFlag to zero as the guess this time is correct
            length--;  //As it is correct, length is decremented to indicate number of letters to be guessed
        }
   }


   if(missFlag) //if miss
   {
       miss--;    //decrementing number of allowed "miss"
       misses[misscount]=guess;    //storing the guess into "misses".
       misscount++;
       misses[misscount]='\0';  //terminating

   }
       //No matter the guess is correct or wrong "repeatGuess" will store it for further use of warning
       repeatGuess[repeatcnt]=guess;
       repeatcnt++;
       repeatGuess[repeatcnt]='\0';
       //Revealing the guessed letters in word with modified "dashes"
       printf("\n\n\n%s",dashes);
       printf("                   misses: %s (%d left.)\n\n",misses,miss);   //Displaying missed letters

        if(!length)  //In case number of letters to be guessed is 0 then the User wins
       {
           printf("Congratulations! You win and saved your life from this horrible death. Happy living! :)\n");
           break;
       }

       if(!miss)   //In case number of allowed misses reached 0 then the user loses
       {
        printf("\n                 YOU LOST! Say goodbye to your close ones:( YOU are going to be HANGED!\n");
        printf("\n                               The word was \"%s\".\n\n\n",word);
       }

}while(miss);

//Freeing all allocated memories
free(repeatGuess);
free(dashes);
free(misses);
free(word);

    return 0;
}
