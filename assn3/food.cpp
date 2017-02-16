#include <cstdlib>
#include <cstdio>
#include <string>
#include <iostream>
#include <pthread.h>
#include <set>

using 	 namespace 	std;

//  PURPOSE:  To tell the names of the foods that the baby can eat.
const char* 	FOOD_ARRAY[]=
  { "applesauce",
  "yogurt",
  "milk",
  "porridge",
  "carrots",
  "peas",
  "5 course candle-lit dinner"
};

//  PURPOSE:  To randomly choose and return a 'const char*' member from array
//'array[]' of size 'arraySize'
const char* 	obtainRandomMessage
      (size_t    	arraySize,
       const char* 	array[]
      )
{
  return(array[rand() % (arraySize / sizeof(const char*))]);
}

//  PURPOSE:  To randomly select and return the name of a food.  No parameters.
const char* 	selectFood()
{
  return( obtainRandomMessage(sizeof(FOOD_ARRAY),FOOD_ARRAY) );
}

int main ()
{
    const char* food;
//  food = selectFood();
//  printf("Food = %s \n", *food);
  food = obtainRandomMessage(sizeof(FOOD_ARRAY),FOOD_ARRAY);  
  printf("food = %s \n", food);


  return(EXIT_SUCCESS);
}
