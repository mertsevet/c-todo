#include <stdio.h>
#include <string.h>

struct Gorev {
    char baslik[50];
    int tamamlandi;
};

int main(){
    struct Gorev g1;
    strcpy(g1.baslik,"C calis");
    g1.tamamlandi = 0;
    
    printf("Gorev: %s (%s)\n",g1.baslik,g1.tamamlandi ? "tamam":"bekliyor");
    return 0;

}