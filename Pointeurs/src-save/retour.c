
#include <stdio.h>

void manger() { printf("miam miam\n"); }
void dormir() { printf("rrrr zzz\n"); }

typedef void (*Action)();

// (void (*)()) que_faire(int heure)
Action que_faire(int heure)
{
	if (heure == 12 || heure == 20) {
		return manger;
	} else {
		return dormir;
	}
}
	
int main()
{
	printf("quelle heure est-il (0..24) ?");
	int heure = 12;
	scanf("%d", & heure);
	que_faire(heure)();
	return 0;
}

