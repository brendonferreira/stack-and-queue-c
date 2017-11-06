#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

bool have_parentesis( char * string ){
  for(int i = 0; i <= strlen(string) ; i++){
    if( string[i] == '(' ) {
      return true;
    }
  }
  return false;
}

char * subString(char *string, int position, int length) {
   char * pointer;
   int c;
 
   pointer = malloc(length+1);
   if (pointer == NULL){
      printf("Não foi possivel alocar a memoria necessaria.\n");
      exit(1);
   }
   for (c = 0 ; c < length ; c++){
      *(pointer+c) = *(string+position-1);      
      string++;   
   }
   *(pointer+c) = '\0';
   return pointer;
}

char * separate_parent_parentesis( char * equation ){
  int open_parentesis_position = -1 ;
  int closures_counter = 0;
  for( int count = 0; count < strlen( equation ); count++ ){
    if( equation[count] != '\040' ){
      if( equation[count] == '(' ){
        closures_counter++;
        if( open_parentesis_position < 0 ){
          open_parentesis_position = count + 2;
        }
      } else if( equation[count] == ')' ){
        closures_counter--;
        if( closures_counter == 0 && open_parentesis_position > -1 ){
          char * part = subString( equation, open_parentesis_position, (count + 1) - open_parentesis_position );
          return part;
        }
      }
    }
  }
  return equation;
}

int indexOf ( char * str, char * toFind ){
  char *result = strstr(str, toFind);
  int position = result - str;
  return position;
}

char * classify_equation ( char * equation , char * classification, int position, int * index ) {
	
  if( have_parentesis( equation ) ){
    char * separated_parentesis = separate_parent_parentesis( equation ); 
    classify_equation( separated_parentesis, classification, position + indexOf( equation, separated_parentesis ), index );
  } 
    
  // find multi/division
  for(int i = 0; i < strlen(equation); i++){	
    if( classification[ i + position] == '\040' ){
      if(equation[i] == '*'|| equation[i] == '/'){
	      *index = *index + 1;
        classification[i + position] = *index + 48;
      }
    }
  }

  // find add/sub
  for(int i = 0; i < strlen(equation) ; i++){	
    if( classification[i + position] == '\040' ){
      if(equation[i] == '-'|| equation[i] == '+'){
        *index = *index + 1;
	      classification[i + position] = *index + 48;
      }
    }
  }

}



int main(){
  int index = 0;

  char * equation;

  printf("Digite uma expreção matemática válida:\n");
  scanf("%m[^\n]", &equation);

  char * classification = (char *) malloc( strlen( equation ) * sizeof("a") );

  for(int i = 0; i < strlen( equation ) * sizeof("a") ; i++){	
      classification[i] = '\040';
  }

  classify_equation( equation , classification, 0 , &index);
  printf( "%s\n", classification );
}