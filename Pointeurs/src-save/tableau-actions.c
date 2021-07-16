

#include <stdio.h>

void aller_au_restaurant() 
{
	printf("Miam\n");
}

void retourner_dormir()  
{
	printf("Zzzz\n");
}

void aller_au_boulot()   
{
	printf("Bof\n");
}

void (*actions[3])()                // tableau de 3 fonctions
      = { & aller_au_restaurant, 
		  & aller_au_boulot, 
		  & retourner_dormir };

int main()
{
	for(;;) {
       printf("Action entre 0 et 2 : ");
       int n;
       scanf("%d", &n);
       actions[n] ();
    }
	return 0;
}

