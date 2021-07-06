#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>


int main()
{
    char *tirets = "+------------+";
    char *prenoms[] = {  "Béatrice","Annie", "Gédéon"};

    setlocale(LC_CTYPE, getenv("LANG"));
    wprintf(L"%s\n", tirets);
    for (int i = 0; i < 3; i++) {
        wprintf(L"| %-10s |\n", prenoms[i]);
    }
    wprintf(L"%s\n", tirets);

    return 0;
}

