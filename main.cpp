/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iomanip>
#include <cstring>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <fstream>
#include <iostream>

using namespace std;

struct KirtasiyeUrun {
    char ad[80];
    float fiyat;
    int stok;  
};

void KirtasiyeUrunuEkle();
void KirtasiyeUrunListele();
void KirtasiyeUrunAra();
void KirtasiyeUrunSil();
void KirtasiyeUrunDuzelt();
void KirtasiyeUrunStokGuncelle();

int main() {
    char anamenu;
    do {
        system("cls"); 
        
        cout << "|------- Kırtasiye Otomasyonu ------|" << endl ;
        cout << "|         Ana Menü Seçim Yapınız    |" << endl ;
        cout << "|   1- Kırtasiye Ürünü Ekleme      |" << endl ;
        cout << "|   2- Kırtasiye Ürünlerini Listele |" << endl ;
        cout << "|   3- Kırtasiye Ürün Arama        |" << endl;
        cout << "|   4- Kırtasiye Ürün Silme        |" << endl;
        cout << "|   5- Kırtasiye Ürün Düzenle      |" << endl;
        cout << "|   6- Kırtasiye Ürün Stok Güncelle|" << endl;
        cout << "|-----------------------------------|" << endl ;

        char secim;
        cin >> secim;

        switch (secim) {
            case '1': 
                KirtasiyeUrunuEkle();
                break;
            case '2': 
                KirtasiyeUrunListele();
                break;
            case '3': 
                KirtasiyeUrunAra();
                break;
            case '4': 
                KirtasiyeUrunSil();
                break;
            case '5': 
                KirtasiyeUrunDuzelt();
                break;
            case '6': 
                KirtasiyeUrunStokGuncelle();
                break;
            default:
                cout << "Geçersiz seçim!" << endl;
        }

        cout << "Ana Menüye dönmek için: 'a', çıkmak için: 'c' basın." << endl; 
        anamenu = getch();

    } while (anamenu == 'a');
    
    return 0;
}

KirtasiyeUrun urun;

void KirtasiyeUrunuEkle() {
    ofstream yaz("kirtasiye.dat", ios::binary | ios::app);
    char secim;
    int adet = 0;

    do {
        cout << "Ürün Adı Giriniz: ";
        cin >> urun.ad;
        cout << "Ürün Fiyatı Giriniz: ";
        cin >> urun.fiyat;
        cout << "Ürün Stok Miktarı Giriniz: ";
        cin >> urun.stok;

        yaz.write((char*)&urun, sizeof(urun)); 
        adet++;    

        cout << "Başka ürün eklemek ister misiniz? (E/H): ";
        secim = getch();
        cout << endl;
    } while (secim == 'e' || secim == 'E');

    cout << adet << " adet ürün eklendi..." << endl;
    yaz.close();
}

void KirtasiyeUrunListele() {
    ifstream oku("kirtasiye.dat", ios::binary | ios::in);
    
    oku.seekg(0, ios::end);
    int kayitsayisi = oku.tellg() / sizeof(urun);
    cout << "Toplam Kırtasiye Ürün Sayısı: " << kayitsayisi << endl;

    if (kayitsayisi > 0) {
        oku.seekg(0, ios::beg);
        for (int i = 0; i < kayitsayisi; i++) {
            oku.read((char*)&urun, sizeof(urun));

            cout << i + 1 << ". Ürünün Bilgileri" << endl;
            cout << "Ürün Adı: " << urun.ad << endl;
            cout << "Ürün Fiyatı: " << urun.fiyat << endl;
            cout << "Ürün Stok Miktarı: " << urun.stok << endl;
        }
    } else {
        cout << "Kayıt Bulunamadı..." << endl;
    }

    oku.close();
}

void KirtasiyeUrunAra() {
    ifstream oku("kirtasiye.dat", ios::binary | ios::in);
    
    oku.seekg(0, ios::end);
    int kayitsayisi = oku.tellg() / sizeof(urun);

    cout << "Aramak istediğiniz ürün adını giriniz: ";
    char urun_ad[80];
    cin >> urun_ad;

    if (kayitsayisi > 0) {
        oku.seekg(0, ios::beg);
        bool found = false;
        for (int i = 0; i < kayitsayisi; i++) {
            oku.read((char*)&urun, sizeof(urun));

            if (strcmp(urun.ad, urun_ad) == 0) {
                cout << "Bulunan Ürünün Bilgileri" << endl;
                cout << "Ürün Adı: " << urun.ad << endl;
                cout << "Ürün Fiyatı: " << urun.fiyat << endl;
                cout << "Ürün Stok Miktarı: " << urun.stok << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Ürün bulunamadı." << endl;
        }
    } else {
        cout << "Kayıt Bulunamadı..." << endl;
    }

    oku.close();
}

void KirtasiyeUrunSil() {
    char urun_ad[80];
    char secim = ' ';
    bool var = false;

    ifstream oku("kirtasiye.dat", ios::binary | ios::in);
    ofstream yaz("temp.dat", ios::binary | ios::out);
    
    oku.seekg(0, ios::end);
    int kayitsayisi = oku.tellg() / sizeof(urun);

    cout << "Silmek istediğiniz ürün adını giriniz: ";
    cin >> urun_ad;

    oku.seekg(0, ios::beg);
    for (int i = 0; i < kayitsayisi; i++) {
        oku.read((char*)&urun, sizeof(urun));

        if (strcmp(urun.ad, urun_ad) == 0) {
            cout << "Silmek istediğiniz ürün: " << urun.ad << endl;
            cout << "Fiyat: " << urun.fiyat << ", Stok: " << urun.stok << endl;
            cout << "Silmek istediğinizden emin misiniz? (E/H): ";
            secim = getch();
            if (secim == 'E' || secim == 'e') {
                var = true;
            } else {
                yaz.write((char*)&urun, sizeof(urun));
            }
        } else {
            yaz.write((char*)&urun, sizeof(urun));
        }
    }
    
    oku.close();
    yaz.close();

    if (var) {
        remove("kirtasiye.dat");
        rename("temp.dat", "kirtasiye.dat");
        cout << "Ürün başarıyla silindi." << endl;
    } else {
        cout << "Ürün bulunamadı." << endl;
    }
}

void KirtasiyeUrunDuzelt() {
    char urun_ad[80];
    bool var = false;

    ifstream oku("kirtasiye.dat", ios::binary | ios::in);
    ofstream yaz("temp.dat", ios::binary | ios::out);
    
    oku.seekg(0, ios::end);
    int kayitsayisi = oku.tellg() / sizeof(urun);

    cout << "Düzenlemek istediğiniz ürün adını giriniz: ";
    cin >> urun_ad;

    oku.seekg(0, ios::beg);
    for (int i = 0; i < kayitsayisi; i++) {
        oku.read((char*)&urun, sizeof(urun));

        if (strcmp(urun.ad, urun_ad) == 0) {
            cout << "Düzenlemek istediğiniz ürün: " << urun.ad << endl;
            cout << "Yeni ürün fiyatını giriniz: ";
            cin >> urun.fiyat;
            cout << "Yeni stok miktarını giriniz: ";
            cin >> urun.stok;

            var = true;
        }
        yaz.write((char*)&urun, sizeof(urun));
    }

    oku.close();
    yaz.close();

    if (var) {
        remove("kirtasiye.dat");
        rename("temp.dat", "kirtasiye.dat");
        cout << "Ürün başarıyla düzenlendi." << endl;
    } else {
        cout << "Ürün bulunamadı." << endl;
    }
}

void KirtasiyeUrunStokGuncelle() {
    char urun_ad[80];
    bool var = false;

    ifstream oku("kirtasiye.dat", ios::binary | ios::in);
    ofstream yaz("temp.dat", ios::binary | ios::out);
    
    oku.seekg(0, ios::end);
    int kayitsayisi = oku.tellg() / sizeof(urun);

    cout << "Stok miktarını güncellemek istediğiniz ürün adını giriniz: ";
    cin >> urun_ad;

    oku.seekg(0, ios::beg);
    for (int i = 0; i < kayitsayisi; i++) {
        oku.read((char*)&urun, sizeof(urun));

        if (strcmp(urun.ad, urun_ad) == 0) {
            cout << "Güncellemek istediğiniz ürün: " << urun.ad << endl;
            cout << "Yeni stok miktarını giriniz: ";
            cin >> urun.stok;

            var = true;
        }
        yaz.write((char*)&urun, sizeof(urun));
    }

    oku.close();
    yaz.close();

    if (var) {
        remove("kirtasiye.dat");
        rename("temp.dat", "kirtasiye.dat");
        cout << "Stok başarıyla güncellendi." << endl;
    } else {
        cout << "Ürün bulunamadı." << endl;
    }
}