#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

//This creates a pokemon node for use later in the linked list for pokemon, it contains variables for the pokemons name, its type, and it's main ability. It also contains a pointer of type struct called next, which will be used in the list to point to the next PokemonNode in the list.
struct PokemonNode {

    char name[50];
    char ability[50];
    char type[50];

    struct PokemonNode* next;

};

//this just makes it so i can say "PokemonNode" instead of "struct PokemonNode" every single time I have to use it.
typedef struct PokemonNode PokemonNode;


//Same as PokemonNode, this is for use later in the players linked list. it contains variables for the players name of a char array (c doesnt have strings, just arrays of characters), a struct for the array of pokemon it will contain, as pointers, and an integer value just for how many pokemon the player owns. Like PokemonNode it also contains a pointer for use in the list for the next playernode.
struct PlayerNode {

    char playerName[50];
    struct PokemonNode* PokemonArray[20];
    int pokemonOwned;

    struct PlayerNode* playerNext;
};

//same reason as the pokemonnode typedef.
typedef struct PlayerNode PlayerNode;


//This is a pokedex struct that contains two structs of type pokemonnode and playernode, for us in the linked list to find the head pokemon and the head player respectively.
struct Pokedex{

    struct PokemonNode *headPoke;
    struct PlayerNode *headPlayer;

};

//same reason as pokemonnode and playernode.
typedef struct Pokedex Pokedex;






//Creating a new struct of type PokemonNode called NewPokemonNode, this contains the values that need to be added to the PokemonNode, using pointers, as strings (character arrays) can't be written to directly and must use pointers.
PokemonNode *NewPokemonNode(char *name, char *ability, char *type){
        // this also allocates memory to the size of one pokemonnode , so when a new pokemonnode is created later, it allocates the proper amount of memory. It also acts as a temporary name for the new pokemon node so that the name, ability, and type can be copied into it as the new values.
        PokemonNode *result = malloc(sizeof(PokemonNode));
        strcpy(result->name, name);
        strcpy(result->ability, ability);
        strcpy(result->type, type);
        //result->next is a pointer from result(the pokemon node) to next, and makes it NULL which means it points to the end of the list(for now).
        result->next = NULL;
        //returning the result brings the result out into the program so that values can be put in and different values can come out.
        return result;
}
//this is basically the same as the new pokemon node.
PlayerNode *NewPlayerNode(char *playerName){
       PlayerNode *result = malloc(sizeof(PlayerNode));
       strcpy(result->playerName, playerName);
       result->playerNext = NULL;
       return result;
};



PokemonNode *FindPokemon(Pokedex *pokedex, char *name){
 //This creates a temp value of type pokemonnode, and sets it's value as a pointer through pokedex to the head pokemon.
  PokemonNode *temp=NULL;
  temp=pokedex->headPoke;

  //while the headpokemon is not equal to null, it checks if "ismatch" is equal to 0 or not, as if it is 0 it is an exact match through strcmp (string compare), it then returns it's value to main. if it isn't 0 it returns null and the loop starts again, so it goes onto the next headpokemon.
  while (temp!=NULL){
    int isMatch = strcmp(temp->name,name);
    if(isMatch == 0){
      return temp;
    }
  }
  return NULL;
}

//this works in the same way as finding the pokemon.
PlayerNode *FindPlayer(Pokedex *pokedex, char *playerName){
  PlayerNode *temp=NULL;
  temp=pokedex->headPlayer;

  while (temp!=NULL){
    int isMatch = strcmp(temp->playerName,playerName);
    if(isMatch ==0){
      return temp;
    }
  }
  return NULL;
}



void AddPokemonToList(Pokedex *pokedex, char *name, char *ability, char *type) {
    //this declares a pointer of type pokemonnode called new pokemon, which points to newpokemonnode and takes its values, these values are already called in the function so they don't need to be defined.
    PokemonNode *newPokemon = NewPokemonNode(name, ability, type);

    //this sets the temp value of pokemonnode to null for safety, and then points it at the head of the pokemon list through the pokedex.
    PokemonNode *temp=NULL;
    temp=pokedex->headPoke;


    //if the headpokemon doesnt exist yet e.g it's an empty list, a new pokemon is created there.
    if (temp==NULL){
        pokedex->headPoke=newPokemon;
        return;
        }

    // while the next value in the list isn't null, temp moves onto the next pokemon in the list until it does, using dupeCheck to check for duplicates on the way there, using strcmp to compare the pokemon name that is already in the list to the one that's trying to be added, all the way through.
    while (temp->next!=NULL){
        temp = temp->next;
        int dupeCheck = strcmp(temp->name,name);
        if (dupeCheck == 0 ){
            printf("\n\nA Pokemon already in list, pokemon has not been duplicated.\n\n");
            return;
            }

        }

    //temp then makes the "next" pointer to a new pokemon, as it has reached the end of the list.
    temp->next = newPokemon;

    return;
    }

// this is a function to add a new player to the linked list of players, it works in the same way as the pokemon one, minus a dupecheck for the same name, as player names don't have to be unique as you can have multiple people with the same name.
void AddPlayerToList(Pokedex *pokedex, char *playerName) {
  PlayerNode *newPlayer = NewPlayerNode(playerName);

  PlayerNode *temp=NULL;
  temp=pokedex->headPlayer;

  if (temp==NULL){
    pokedex->headPlayer=newPlayer;
    return;
  }

  while (temp->playerNext!=NULL){
    temp = temp->playerNext;
  }

  temp->playerNext = newPlayer;

  return;

}


// this function adds pokemon into the players array of pokemon, and also increments their pokemon owned integer by one.
void AddPokemonToPlayer(Pokedex *pokedex,char *playerName,char *name){

  PlayerNode *playerFound = FindPlayer(pokedex, playerName);

    PokemonNode *pokeFound = FindPokemon(pokedex, name);
    if (playerFound!=NULL && pokeFound!=NULL){
      for (int loop = 0; loop < 20; loop++){
       if (playerFound ->PokemonArray[loop] == NULL){
          playerFound->PokemonArray[loop] = pokeFound;
          playerFound->pokemonOwned = playerFound->pokemonOwned+1;
          return;
        }
      }
    }

   return;
}

void printPoke(PokemonNode *head) {
    PokemonNode *hPointer = head;

    while (hPointer != NULL) {
        printf("Pokemon Name: %s\n", hPointer->name);
        printf("Ability: %s\n", hPointer->ability);
        printf("Type: %s\n", hPointer->type);
        hPointer = hPointer->next;
        printf("\n\n");
    }

}

void printPlayers(PlayerNode *headP) {
    PlayerNode *hpPointer = headP;

    while (hpPointer != NULL){
        printf("Player Name: %s\n", hpPointer->playerName);
        printf("Pokemon Player Owns: %d\n", hpPointer->pokemonOwned);
        hpPointer = hpPointer->playerNext;
        printf("\n\n");
    }

};


int main(void){
  Pokedex *pokedex = NULL;
  pokedex = (Pokedex*)malloc(sizeof(Pokedex));

  AddPokemonToList(pokedex,"Pikachu","Lightning_Bolt","Lightning");
  AddPokemonToList(pokedex,"Charizard","Flamethrower","Dragon");
  AddPokemonToList(pokedex,"Squirtle","Bubblegun","Water");
  AddPokemonToList(pokedex,"Piplup","Bubblegun","Water");
  AddPokemonToList(pokedex,"Squirtle","Bubblegun","Water");

  AddPlayerToList(pokedex, "Jordan");



  AddPokemonToPlayer(pokedex,"Jordan" ,"Pikachu");






  printPoke(pokedex->headPoke);


}
