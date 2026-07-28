#include <stdio.h>
#include <string.h>

#define MAX_GOREV 20
struct Gorev {
    char baslik[50];
    int tamamlandi;
};

int main(){
    struct Gorev gorevler[MAX_GOREV];
    int gorev_sayisi=0;
    int secim;
    char temp[50];

    while(1) {
        printf("\n---TO-DO---\n");
        printf("1 - Gorev ekle\n");
        printf("2 - Gorevleri Listele\n");
        printf("3 - Cikis\n");
        printf("Secim: ");

        scanf("%d",&secim);
        getchar();
        
        if(secim==1){
            if (gorev_sayisi>=MAX_GOREV)
            {
                printf("Liste dolu.\n");
                continue;
            }
            printf("Gorev basligi: ");
            fgets(temp,50,stdin);
            temp[strcspn(temp,"\n")]='\0';

            strcpy(gorevler[gorev_sayisi].baslik,temp);
            gorevler[gorev_sayisi].tamamlandi=0;
            gorev_sayisi++;
            printf("Eklendi.\n");
        }
        else if (secim==2){
            if(gorev_sayisi==0){
                printf("Henuz gorev yok.\n");
            }
            for (int i=0; i<gorev_sayisi;i++){
                printf("%d. %s (%s\n)",i+1,gorevler[1].baslik,
                    gorevler[i].tamamlandi ? "tamam":"bekliyor");
            }
        }
        else if (secim==3){
            printf("Gorusuruz.\n");
            break;
        }
        else{
            printf("Gecersiz secim.\n");
        }
    }
    return 0;
}