/*fichier d'implementation des fontions 
pour Set implementé avec les ABR */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "tree.h" /*pour utiliser les fontions des arbres */
#include "Set.h"

struct set_t{
	int nb_elts;
	tree  arbre;
};

/**************************************************************/
Set* createEmptySet(void){
	
	Set * res= (Set*)malloc(sizeof(Set));
	
	if(res ==NULL){
		printf("ERREUR ALLOCATION MEMOIRE!\n");
		exit(EXIT_FAILURE);
	}
	
	res->arbre =createEmptyTree(); 
	
	if(res->arbre==NULL)
		printf("erreur alloc pour arbre\n");
		
	res->nb_elts=0;
	return res;
}
/**************************************************************/
void freeSet(Set* set){
	if(set==NULL)
		return;
	freeTree(set->arbre);
	free(set);
	set=NULL;
}
/**************************************************************/

size_t sizeOfSet(const Set* set){
	return set->nb_elts;
}
/**************************************************************/
insert_t insertInSet(Set* set, char* element){
	
	if(contains(set,element)){
		return OLD;
	}
	if(set==NULL){
		Set*n=createEmptySet();
		printf("set is null\n");
		if(n==NULL)
			return ALLOC_ERROR;
	}
	
	insert_iter(element,&(set->arbre));
	 
	set->nb_elts++;	
	return NEW;
}
/**************************************************************/
bool contains(const Set* set, const char* element){
	if(set==NULL)
		return false;
	if(  strcmp(element, set->arbre->key)==0  )
		return true;
	if(  strcmp(element, set->arbre->key)>0  )
		return search(element,set->arbre->right);
	else 
		return search(element,set->arbre->left);
}	
/**************************************************************/

StringArray* setIntersection(const Set* set1, const Set* set2){
	StringArray* array = createEmptyArray();
	return set_intersection_tree(array,set1->arbre, set2->arbre);
}
/***********************************************************************************/
/* les fonctions pour les arbres binaires de recherche */
tree createEmptyTree(void){
	tree res= malloc(sizeof(node));
	res->key= malloc(10*sizeof(char));
	res->left=NULL;
	res->right=NULL;
	res->h=0;
	return res;
}
/**************************************************************/
void freeTree(tree a){
	if(a==NULL)
		return;
	freeTree(a->left);
	freeTree(a->right);
	free(a->key);
	free(a);
}
/**************************************************************/
/*intersection de deux arbres binaires*/
StringArray * set_intersection_tree(StringArray * arr,tree t1, tree t2){
	if(t1==NULL || t2==NULL){
		return arr;
	}
	if(search(t1->key,t2)){
		if(!insertInArray(arr,t1->key))
			printf("error\n");
	}
	set_intersection_tree(arr,t1->left, t2);
	set_intersection_tree(arr,t1->right, t2);
	return arr;
}
/**************************************************************/

/*recherche recursive*/
bool search (const char* v,node*A){
	if(A == NULL)
		return false;
	if(strcmp(A->key,v) == 0)
		return true;
	if(strcmp(A->key,v) < 0)
		return search(v,A->right);
	return search(v,A->left);
}
/**************************************************************/
/*insertion iterative que l'on a utilisé dans le programme*/
void insert_iter(char* v, node** A){
	/*creation d'un noeud pour v */
	node* m= createEmptyTree();
	m->key=v;
	
	if((*A)==NULL)
		(*A)=m;
		
	node* y=NULL;
	node* x=(*A);
	while(x!=NULL){
		y=x;
		if(strcmp(m->key,x->key) < 0)
			x=x->left;
		else
			x=x->right;
	}
	if(strcmp(m->key,y->key) < 0)
		y->left=m;
	else
		y->right=m;
}
/**************************************************************/
/*insertion recursive*/
void insert (char* v,node** A){
	if((*A)==NULL){
		node * m = createEmptyTree();
		m->key=v;
		(*A)=m;
	}
	else{
		if( strcmp((*A)->key,v) <0 )
			insert(v, &((*A)->right) );
		
		else if (strcmp((*A)->key,v) >0)
			insert(v,&(*A)->left);
	}
}
/**************************************************************/		
char* delet (char* v, tree *a){
	char*c;
	if((*a ==NULL)) return 0;
	else {
		if(strcmp(v,(*a)->key) <0)
			return delet(v,&((*a)->left));
		else {
			if(strcmp(v,(*a)->key) >0)
				return delet(v,&((*a)->right));
			else{
				if(((*a)->left)==NULL){
					c=(*a)->key;
					node *p =*a;
					*a=(*a)->right;
					free(p);
					return c;
				}
				else{
					if((*a)->right==NULL){
						c=(*a)->key;
						node *p=*a;
						*a=(*a)->left;
						free(p);
						return c;
					}
					else {
						char* m=minimum((*a)->right);//successeur
						(*a)->key=m;
						return delet (m,&((*a)->right));
					}
				}
			}
		}
	}
}
/**************************************************************/

void print_inorder (node*A) { 
	if(A != NULL){
		print_inorder(A->left);
		printf("%s ", A->key);
		print_inorder(A->right);
	}
}
/**************************************************************/	
char* minimum (node*A){
	if(A == NULL){
		printf(" arbre vide \n");
		return "pas de min";
	}
	while(A->left !=NULL){
		A=A->left;
	}
	return A->key ;
}
/**************************************************************/				
				
int height (node*A) {
	if( A == NULL )
		return -1;
	int h1=height(A->left);
	int h2= height(A->right);
	if(h1 > h2){
		return 1+ h1;
	}else{
		return 1+ h2;
	}
}

