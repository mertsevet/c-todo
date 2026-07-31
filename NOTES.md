# Notlar — C'yi tekrar öğrenirken

Bu proje boyunca öğrendiklerimin özeti. Java/C# geçmişim olduğu için
notlar çoğunlukla "C'de bu neden farklı" sorusuna cevap veriyor.

---

## Zihinsel model

Program 20 satırlık bir defter tutuyor. Her satırda iki kutu var:
başlık ve tamamlandı bilgisi.

| satır | baslik | tamamlandi |
|---|---|---|
| gorevler[0] | süt al | 0 |
| gorevler[1] | C calis | 1 |
| gorevler[2] | (çöp) | (çöp) |

- `gorevler[i]` → satırı seçer
- `.baslik` → o satırdaki kutuyu seçer

---

## 1. gün — struct ve ekrana yazdırma

### #include

Java'daki `import` gibi ama derleme anında dosya içeriğini koda
**kopyalar**.

- `stdio.h` → printf, scanf, fopen
- `string.h` → strcpy, strlen, strcspn

### struct

```c
struct Gorev {
    char baslik[50];
    int tamamlandi;
};
```

Metotsuz class. Sadece veri tutar.

**Dikkat:** kapanış parantezinden sonra noktalı virgül var. Unutulunca
anlaşılmaz hatalar çıkar.

### C'de string yok

Metin = karakter dizisi + sonunda `\0` (bitiş işareti).

`char baslik[50]` → 50 karakterlik yer, ama `\0` yüzünden en fazla
**49 karakterlik** metin sığar.

`printf` metni yazarken `\0` görene kadar okur.

### bool yok

0 = false, 0 dışındaki her şey = true.

### Değişken oluşturma

```c
struct Gorev g1;
```

`new` yok, `null` yok. Değişken doğrudan bellekte.

**Kritik:** başlangıç değeri atanmaz. Java'da `int` otomatik 0 olur,
C'de o bellekte ne varsa çöp değer olarak kalır.

### Metin atama

```c
g1.baslik = "C calis";        // OLMAZ — derleyici hata verir
strcpy(g1.baslik, "C calis"); // DOĞRU
```

Sebep: `baslik` bir dizi, adresi sabit. Kendisi değişmez, sadece içi
doldurulur. `strcpy(hedef, kaynak)` — hedef önce.

### printf

| Kod | Tip |
|---|---|
| `%d` | int |
| `%s` | metin |
| `%c` | tek karakter |
| `%f` | ondalıklı |
| `%p` | adres |

`\n` koymazsan alt satıra geçmez.

---

## 2. gün — dizi, menü döngüsü, kullanıcı girdisi

### #define

```c
#define MAX_GOREV 20
```

Derleyici koddaki her `MAX_GOREV` yazısını `20` ile değiştirir.
Bellekte değişken oluşmaz — sadece metin değişimi.

### Struct dizisi

```c
struct Gorev gorevler[MAX_GOREV];
```

Java'da bu 20 boş referans yaratırdı, nesneleri ayrıca `new` ile
yaratmak gerekirdi. C'de 20 struct'ın **tamamı zaten bellekte** —
sadece içleri çöp.

### Sayaç neden gerekli

C dizinin toplam boyutunu bilir (20), ama **kaçının dolu olduğunu**
bilmez. `gorev_sayisi` ile bunu ben takip ediyorum.
Java'daki `list.size()` yerine geçiyor.

Güzel bir yan etki: sayaç aynı zamanda "sıradaki boş satır"ı gösterir.
2 görev varsa (0 ve 1 dolu), boş satır `gorevler[2]`.

### while(1) + break

`1` = true olduğu için sonsuz döngü. Menü programlarının klasik kalıbı.
`continue` → döngünün kalanını atla, başa dön.

### & işareti — en önemli konu

**`&` = "bunun adresi" demek.** Anlamı bu, başka bir şey değil.

`scanf`'te neden gerekli: C'de fonksiyonlara her şey **kopyalanarak**
gider. `scanf(secim)` yazsaydım, scanf kopyayı doldurup atardı, benim
değişkenim değişmezdi. Adresini verince değişkenime ulaşabiliyor.

Ev adresi benzetmesi: birine "evime paket bırak" diyorsan adresini
vermen lazım.

```c
scanf("%d", &secim);   // & var  — secim tek bir sayı
fgets(temp, 50, stdin); // & yok — dizi ismi zaten adres
```

### getchar() — görünmez tuzak

`scanf("%d", ...)` sadece sayıyı okur, bastığım **Enter'i giriş
tamponunda bırakır**. Sonraki `fgets` o Enter'i görür, "boş satır
girildi" sanar ve soruyu atlar.

`getchar()` o artık Enter'i okuyup çöpe atar.

### fgets vs scanf

`scanf("%s", ...)` boşluk görünce durur — "süt al" yazsam sadece "süt"
alırdı. `fgets` satırın tamamını okur.

`fgets(nereye, en_fazla_kac_karakter, nereden)` — ikinci parametre
taşmayı önlüyor, güvenlik açısından önemli.

### Enter'i temizleme

```c
temp[strcspn(temp, "\n")] = '\0';
```

`fgets` Enter'i de metne dahil eder. `strcspn(temp, "\n")` → `\n`
karakterinin kaçıncı sırada olduğunu döndürür. O konuma `\0` yazınca
metin orada biter.

Enter'i silmiyorum — **metni ondan önce bitiriyorum**. Veri hâlâ orada
ama kimse oraya kadar okumuyor.

---

## 3. gün — işaretleme ve silme

### Kullanıcı numarası vs dizi indeksi

Kullanıcıya 1, 2, 3 diye gösteriyorum ama dizi 0'dan başlıyor.
Kullanıcının "3" dediği şey `gorevler[2]`.

- Listelerken `i + 1` → ekrana 1'den başlayarak yaz
- İşlem yaparken `no - 1` → gerçek indekse çevir

İkisi birbirini dengeliyor.

### Sınır kontrolü benim işim

```c
if (no < 1 || no > gorev_sayisi) {
    printf("Gecersiz numara.\n");
    continue;
}
```

Java'da yanlış indeks exception fırlatırdı. **C'de hiçbir şey olmaz** —
sessizce başka bir değişkenin belleğini bozar, program ilerde ilgisiz
bir noktada çöker. En sinir bozucu hata türü bu.

### Struct kopyalanabilir

```c
gorevler[i] = gorevler[i + 1];  // ÇALIŞIR
```

Dizi atanamaz ama struct atanabilir. Bu satır struct'ın içindeki tüm
byte'ları (başlık dizisi dahil) kopyalar.

Kural: **parçası (dizi) olmaz, bütünü (struct) olur.**

Not: bu bir kopya, referans değil.

### Silme = kaydırma

C'de `list.remove(2)` yok. Dizide "boşluk" kavramı da yok.

Silmek demek: silinecek yerden itibaren sonraki her elemanı bir geriye
çekmek, sonra sayacı azaltmak.

```c
for (int i = no - 1; i < gorev_sayisi - 1; i++) {
    gorevler[i] = gorevler[i + 1];
}
gorev_sayisi--;
```

Son elemandaki veri fiziksel olarak silinmiyor — sayaç azaldığı için
oraya artık kimse bakmıyor. **Veri değil, sayaç yönetiliyor.**

Döngü `gorev_sayisi - 1`'e kadar: son elemanda `gorevler[i + 1]` dizinin
dışına taşardı.

---

## 4. gün — fonksiyonlar ve dosya işlemleri

### Fonksiyonlar

C'de fonksiyonlar sınıf içinde değil, dosyada serbest durur.
`void` → bir şey döndürmez, `int` → tam sayı döndürür.

### Dizi mi, sayı mı — & konusunun oturduğu yer

```c
gorev_sayisi = yukle(gorevler);   // & yok!
```

- **Dizi gönderirsen:** dizi ismi zaten adres → fonksiyon doğrudan
  benim dizimin üstüne yazar → değişiklik kalıcı
- **Sayı gönderirsen:** kopya gider → fonksiyon içindeki değişiklik
  kaybolur → `return` ile geri göndermek gerekir

Bu yüzden `yukle` diziyi doldurabiliyor ama sayacı `return` ile
döndürmek zorunda.

**Tek cümle:** dizi adres olarak gider, sayı kopya olarak gider.

### FILE * — ilk gerçek pointer

```c
FILE *dosya = fopen("gorevler.txt", "w");
```

`*` → "bu bir pointer", içinde adres tutuyor. `dosya` dosyanın kendisi
değil, ona açılmış bir **tutamak**.

Modlar:
- `"w"` → yaz. **Dosya varsa içini komple siler.**
- `"r"` → oku. Dosya yoksa açamaz.
- `"a"` → sonuna ekle.

### NULL kontrolü — atlanmaz

```c
if (dosya == NULL) { ... }
```

`fopen` başarısız olabilir (dosya yok, izin yok, disk dolu). `NULL`
döner. Kontrol etmeden kullanırsan program anında çöker.

Yükleme fonksiyonunda bu ayrıca işe yarıyor: ilk çalıştırmada dosya
henüz yoktur, `NULL` gelir, "0 görev yüklendi" deriz. Hata değil.

### fprintf

`printf` ile aynı, sadece ilk parametre hangi dosyaya yazılacağı.

```
0;süt al
1;C calis
```

`;` ayırıcı — başlıkta boşluk olabildiği için sayının nerede bitip
metnin nerede başladığını belli etmek gerekiyor.

### fscanf ile okuma döngüsü

```c
while (sayi < MAX_GOREV &&
       fscanf(dosya, "%d;", &gorevler[sayi].tamamlandi) == 1) {
```

`fscanf` okuduğu değer sayısını döndürür. Başarılıysa 1. Dosya bitince
1 dönmez, döngü durur — "dosya bitti mi" kontrolü bu.

`sayi < MAX_GOREV` → dosyada 100 satır olsa bile 20'den fazla okumaya
çalışma. Sınır kontrolü yine bende.

### fclose

Yazılan veriler bir süre bellekte bekletilir; `fclose` onları diske
kesin olarak yazar. Kapatmazsan veri kaybolabilir.

**Kural: her `fopen`'ın bir `fclose`'u olur.** İleride `malloc`/`free`
ikilisinde de aynı kalıp: açtığını kapat, aldığını geri ver.

---

## Java/C# → C özet tablosu

| Konu | Java / C# | C |
|---|---|---|
| Metin | `String` sınıfı | `char` dizisi + `\0` |
| Metin atama | `s = "x"` | `strcpy(s, "x")` |
| Nesne | `new Gorev()` | `struct Gorev g1;` |
| Boolean | `true` / `false` | `1` / `0` |
| Varsayılan değer | otomatik atanır | çöp değer kalır |
| Dizi taşması | exception fırlatır | sessizce belleği bozar |
| Eleman sayısı | `list.size()` | elle tutulan sayaç |
| Silme | `list.remove(i)` | kaydır + sayacı azalt |
| Bellek | garbage collector | kendin yönetirsin |

---

## En çok takıldığım 3 şey

1. **`scanf`'ten sonra `getchar()`** — yoksa sonraki `fgets` Enter'i
   yer ve soruyu atlar
2. **`=` ile metin atamaya çalışmak** — dizi için `strcpy` şart
3. **`no - 1` unutmak** — kullanıcı 1'den, dizi 0'dan sayıyor

---

## Sırada ne var

- Pointer'ı doğrudan çalışmak (`*`, `&`, adres yazdırma)
- Fonksiyondan değer değiştirme (`void f(int *a)`)
- Bit işlemleri (`&`, `|`, `^`, `<<`, `>>`)
- Sonra STM32 ile gömülü tarafa geçiş
