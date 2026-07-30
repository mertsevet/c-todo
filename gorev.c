#include <stdio.h>
#include <string.h>

#define MAX_GOREV 20
#define DOSYA_ADI "gorevler.txt"

struct Gorev {
    char baslik[50];
    int tamamlandi;
};

void kaydet(struct Gorev gorevler[], int gorev_sayisi) {
    FILE *dosya = fopen(DOSYA_ADI, "w");
    if (dosya == NULL) {
        printf("Dosya kaydedilemedi.\n");
        return;
    }
    for (int i = 0; i < gorev_sayisi; i++) {
        fprintf(dosya, "%d;%s\n", gorevler[i].tamamlandi, gorevler[i].baslik);
    }
    fclose(dosya);
}

int yukle(struct Gorev gorevler[]) {
    FILE *dosya = fopen(DOSYA_ADI, "r");
    if (dosya == NULL) {
        return 0;
    }
    int sayi = 0;
    while (sayi < MAX_GOREV &&
           fscanf(dosya, "%d;", &gorevler[sayi].tamamlandi) == 1) {
        fgets(gorevler[sayi].baslik, 50, dosya);
        gorevler[sayi].baslik[strcspn(gorevler[sayi].baslik, "\n")] = '\0';
        sayi++;
    }
    fclose(dosya);
    return sayi;
}

int main() {
    struct Gorev gorevler[MAX_GOREV];
    int gorev_sayisi = yukle(gorevler);
    int secim;
    char temp[50];

    printf("%d gorev yuklendi.\n", gorev_sayisi);

    while (1) {
        printf("\n--- TO-DO ---\n");
        printf("1 - Gorev ekle\n");
        printf("2 - Gorevleri listele\n");
        printf("3 - Tamamlandi isaretle\n");
        printf("4 - Gorev sil\n");
        printf("5 - Cikis\n");
        printf("Secim: ");

        scanf("%d", &secim);
        getchar();

        if (secim == 1) {
            if (gorev_sayisi >= MAX_GOREV) {
                printf("Liste dolu.\n");
                continue;
            }
            printf("Gorev basligi: ");
            fgets(temp, 50, stdin);
            temp[strcspn(temp, "\n")] = '\0';

            strcpy(gorevler[gorev_sayisi].baslik, temp);
            gorevler[gorev_sayisi].tamamlandi = 0;
            gorev_sayisi++;
            printf("Eklendi.\n");
        }
        else if (secim == 2) {
            if (gorev_sayisi == 0) {
                printf("Henuz gorev yok.\n");
            }
            for (int i = 0; i < gorev_sayisi; i++) {
                printf("%d. %s (%s)\n", i + 1, gorevler[i].baslik,
                       gorevler[i].tamamlandi ? "tamam" : "bekliyor");
            }
        }
        else if (secim == 3) {
            int no;
            if (gorev_sayisi == 0) {
                printf("Henuz gorev yok.\n");
                continue;
            }
            printf("Hangi gorev tamamlandi (numara): ");
            scanf("%d", &no);
            getchar();

            if (no < 1 || no > gorev_sayisi) {
                printf("Gecersiz numara.\n");
                continue;
            }
            gorevler[no - 1].tamamlandi = 1;
            printf("Tamamlandi olarak isaretlendi.\n");
        }
        else if (secim == 4) {
            int no;
            if (gorev_sayisi == 0) {
                printf("Henuz gorev yok.\n");
                continue;
            }
            printf("Hangi gorev silinsin (numara): ");
            scanf("%d", &no);
            getchar();

            if (no < 1 || no > gorev_sayisi) {
                printf("Gecersiz numara.\n");
                continue;
            }
            for (int i = no - 1; i < gorev_sayisi - 1; i++) {
                gorevler[i] = gorevler[i + 1];
            }
            gorev_sayisi--;
            printf("Silindi.\n");
        }
        else if (secim == 5) {
            kaydet(gorevler, gorev_sayisi);
            printf("Kaydedildi. Gorusuruz.\n");
            break;
        }
        else {
            printf("Gecersiz secim.\n");
        }
    }

    return 0;
}