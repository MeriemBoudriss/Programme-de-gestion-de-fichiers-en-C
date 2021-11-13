#include <stdio.h>
#include <stdlib.h>
#include "Set.h"
#include <time.h>

/* l'algorithme generique d'intersection */
StringArray* getIntersection(const StringArray* array1, const StringArray* array2){
	
	Set* set1 = createEmptySet();
	Set* set2 = createEmptySet();
	
	
	for(unsigned int i=0; i<arrayLength(array1); i++){
		insertInSet(set1, getElementInArray(array1, i));
	}
	
	for(unsigned int i=0; i<arrayLength(array2); i++){
		insertInSet(set2, getElementInArray(array2, i));
	}
	
	StringArray* result= createEmptyArray();
	
	result= setIntersection(set1,set2);
	
	return result;
}
