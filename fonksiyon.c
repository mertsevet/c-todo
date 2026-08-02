#include <stdio.h>

void hepsiniIkiyeKatla(int dizi[], int boyut){
    for(int i = 0; i<boyut;i++){
        dizi[i] = dizi[i] * 2;
    }
}

int main(){
    int sayilar[5] = {1, 2, 3, 4, 5};
    int boyut = 5;
    hepsiniIkiyeKatla(sayilar, 5); 
    printf("Sayilarin 2'ye katlanmis hali: \n");
    for (int i = 0; i < boyut; i++)
    {
        printf("%d\n",sayilar[i]);
    }
    return 0;
}


