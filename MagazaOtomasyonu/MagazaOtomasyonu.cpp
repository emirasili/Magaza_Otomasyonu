#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;


struct node {
    int ProductId;
    string Product;                   // Urun bilgilerinin tutulduðu liste yapýsý
    int Price;
    node* next;
};



struct node* add(node*& basdugum, int ID, string product, int price) {
    if (basdugum == NULL) {
        struct node* dugum = new node();
        dugum->ProductId = ID;
        dugum->Product = product;                  // Dýþarýdan girilen hasta bilgilerini listeye ekleyen fonksiyon
        dugum->Price = price;
        dugum->next = NULL;                         // Badugum nullptr ise yeni dugumu basdugume atar
        basdugum = dugum;
    }
    else {
        struct node* dugum = new node();
        struct node* temp = basdugum;
        while (temp->next != NULL) {
            temp = temp->next;
        }                                           // Dugumleri gezerek nullptr olan dugumu yakalar ve yeni dugumu u oraya ekler
        temp->next = dugum;
        dugum->ProductId = ID;
        dugum->Product = product;
        dugum->Price = price;
    }
    return basdugum;
}


struct node* print(node* basdugum) {
    if (basdugum == NULL) {
        cout << "Magazada urun bulunmamaktadir" << endl;
    }
    node* temp = basdugum; {}                                       // Urun bilgilerini ekrana yazan fonksiyon
    while (temp != NULL) {

        cout << "Urun numarasi: " << temp->ProductId << setw(15) << "Urun Adi: " << temp->Product << setw(25) << "Urun Fiyati: " << temp->Price << endl;
        temp = temp->next;
    }
    return basdugum;
}

void printOrder() {                                              // Aranan urun bulunamayýnca siparis eden fonksiyon
    int orderId;
    string order;
    int orderPrice;                                             // Siparisýn ozelliklerini girmek icin degiskenler
    string city;
    string district;
    string storeCode;

    ofstream printOrder("SiparisListesi.txt", ios::app);         // Siparis bilgilerini dosyaya yazdýrmak icin

    cout << "Siparis etmek istediginiz urunun numarasini giriniz: "; cin >> orderId;
    cout << "Siparis etmek istediginiz urunun adini giriniz: "; cin >> order;
    cout << "Siparis etmek istediginiz urunun fiyatini giriniz: "; cin >> orderPrice;
    cout << "---------------Siparis Edilecek Magaza Bilgileri---------------" << endl;              // Degiskenlerin doldurulmasý
    cout << "Il: "; cin >> city;
    cout << "Ilce: "; cin >> district;
    cout << "Magaza Kodu: "; cin >> storeCode;

    printOrder << "Siparis Numarasi: " << orderId << " Siparis Adi: " << order << " Urun Fiyati: " << orderPrice << endl;
    printOrder << "Adres Bilgileri: " << city << "/" << district << " " << storeCode << " Magazasi" << endl;                    // Dosyaya yazan kýsým

    printOrder.close();

}


struct node* deleteProduct(node*& basdugum, int deleteID) {         // Dýþarýdan girilen ID numarasýna sahip urunu silen fonksiyon
    struct node* temp;
    struct node* iter = basdugum;
    if (basdugum->ProductId == deleteID) {
        temp = basdugum;
        basdugum = basdugum->next;                   // Silinecek urun ilk sýradaysa 2. sýradaki urunu basdugum yapar ve basdugumu siler
        delete temp;
        return basdugum;
    }
    while (iter->next->ProductId != deleteID) {
        iter = iter->next;                          // Silinecek urunu bulmak için listeyi dolaþýr
    }

    if (iter->next == NULL) {
        cout << "Bu numarada bir urun yok" << endl;     // Girilen ID ye sahip urun yoksa urunu bulamaz
    }
    temp = iter->next;
    iter->next = temp->next;
    delete temp;                            // Silinecek ID ye sahip urunu bulur ve urunu siler
    return basdugum;
}

struct node* update(node* basdugum, int ID, int newPrice) {        // Girilen ID ye sahip urunun fiyatýný guncelleyen fonksiyon
    if (basdugum == NULL) {
        cout << "Magazada urun bulunmamaktadir" << endl;            // Magazada urun yoksa urun yok yazar
    }
    else if (basdugum->ProductId == ID) {
        basdugum->Price = newPrice;                         // Guncellenecek urun ilk sýradaysa basdugumun fiyatýný gunceller
    }
    else {
        node* iterControl = basdugum;
        while (iterControl->next != NULL && iterControl->next->ProductId != ID) {     // Guncellenecek Urunu bulmak icin urunleri dolasir
            iterControl = iterControl->next;
        }
        if (iterControl->next == NULL) {
            cout << "Aranan urun bulunamadi" << endl;             // Girilen ID ye sahip urunu bulamazsa yazar
            string choice;
            cout << "Yeni Urun Siparisi Gecmek Istiyor musunuz ? (e - h)"; cin >> choice; // Magazada bulunmayan urunun siparis gecip gecilmeyeceginiz sorar
            do
            {
                if (choice == "e" || choice == "E")
                {                                           // Siparis verilecekse yukarýdaki siparis fonksiyonumuz calisir ve dosyaya siparisi yazar
                    printOrder();
                    cout << "Siparisiniz verildi, 1-7 gün icerisinde magazaya ulasacak" << endl;
                    cout << "Siparis Bilgileri Dosyaya Yazdirildi";
                    break;
                }
                else if (choice == "h" || choice == "H")
                {
                    cout << "Cikis Yapiliyor..";                // Siparis verilmeyecekse cikis yapar
                    break;
                }
                else
                {
                    cout << "Yanlis secim girdiniz. Lutfen tekrar deneyin" << endl;
                }                                                            // Yanlis secim girilmesi halinde kullanýcý doðru secime yonlendirir
            } while (choice != "e" || choice != "E" || choice != "h" || choice != "H");
        }

        node* iter = basdugum;
        while (iter->next->ProductId != ID)
        {
            iter = iter->next;
        }                                       // Guncellenecek olan urunu bulur ve fiyatini gunceller

        node* temp = iter->next;
        temp->Price = newPrice;
    }
    return basdugum;
}

struct node* find(node* basdugum, string product) {            // Aranan urunun hangi sirada oldugunu bulan fonksiyon
    if (basdugum == NULL) {
        cout << "Magazada urun bulunmamaktadir." << endl;       // Magazada urun yoksa urun yok yazar
    }
    else if (basdugum->Product == product) {
        cout << "Aranan urun bulundu ve magazada birinci sirada yer almaktadir" << endl;       // Aranan urun basdugumdeyse ilk sýrada yazar
    }
    else {
        node* iterControl = basdugum;
        while (iterControl->next != NULL && iterControl->next->Product != product) {
            iterControl = iterControl->next;                                        // Aranan urunu dolasir
        }
        if (iterControl->next == NULL) {
            cout << "Aranan urun bulunamadi" << endl;            // Girilen urunu bulunamadisa urun bulunamadi yazar
        }
        node* iter = basdugum;
        int i = 1;
        while (iter->next->Product != product)
        {
            i++;                                // Girilen urunu bulana kadar dolasir ve her dolastiginda i yi 1 arttirir
            iter = iter->next;
        }

        i++;
        node* temp = iter->next;
        cout << "Aranan urun " << i << "'nci sirada bulunmaktadir." << endl;    // Girilen urunu bulunda i degerini yazarak hangi sirada oldugunu bulur

    }

    return basdugum;
}

struct node* printFinded(node* basdugum, string product) {         // Aranan urunun ozelliklerini yazan fonksiyon
    if (basdugum == NULL) {
        cout << "Magazada urun bulunmamaktadir." << endl;           // Magazada urun yoksa urun yok yazar
    }
    else if (basdugum->Product == product) {                          // Aranan urun ilk siradaysa basdugumun ozelliklerini yazar
        cout << "Urun numarasi: " << basdugum->ProductId << setw(15) << "Urun Adi: " << basdugum->Product << setw(25) << "Urun Fiyati: " << basdugum->Price << endl;
    }
    else {
        node* iterControl = basdugum;
        while (iterControl->next != NULL && iterControl->next->Product != product) {
            iterControl = iterControl->next;                    // Aranan urunu bulmak icin dolasir
        }
        if (iterControl->next == NULL) {
            cout << "Aranan urun bulunamadi" << endl;        // Girilen urunu bulamadýysa aranan urun bulunamadi yazar
        }
        node* iter = basdugum;
        while (iter->next->Product != product)
        {
            iter = iter->next;
        }                                             // Girilen urunu dolasark bulur ve urunun bilgilerini ekrana yazar

        node* temp = iter->next;
        cout << "Urun numarasi: " << temp->ProductId << setw(15) << "Urun Adi: " << temp->Product << setw(25) << "Urun Fiyati: " << temp->Price << endl;

    }

    return basdugum;
}

struct node* printFile(node* basdugum) {           // Urunleri dosyaya yazan fonksiyon
    cout << "Dosyaya yaziliyor.." << endl;
    if (basdugum == NULL) {
        "Magazada Urun Bulunmamaktadir.";           // Urun yoksa magazada urun yok yazar
    }
    ofstream printFile("UrunListesi.txt", ios::app);     // Dosyayý UrunListesi.txt adýnda kaydeder
    struct node* iter = basdugum;
    while (iter != NULL)
    {                                                   // Urunleri dosyaya yazar
        printFile << "Urun numarasi: " << iter->ProductId << setw(15) << "Urun Adi: " << iter->Product << setw(25) << "Urun Fiyati: " << iter->Price << endl;
        iter = iter->next;
    }
    printFile.close();                  // Dosyayi kapatir

    return basdugum;
}

struct node* readFile(node* basdugum) {        // Dosyadaki urunleri okuyan fonksiyon

    ifstream readFile("UrunListesi.txt", ios::app);      // UrunListesi.txt adýndaki dosyadi urunleri okur 
    string line;
    while (getline(readFile, line))
    {
        cout << line << " " << endl;            // Okunan urunleri ekrana yazar
    }
    readFile.close();

    return basdugum;

}

void bubbleSort(node* basdugum) {                  // Urunlerin fiyatini kucukten buyugu siralayan fonksiyon
    cout << "Urunler kucukten buyuge siralaniyor" << endl;

    if (basdugum == NULL) {
        cout << "Magazada Urun Bulunmamaktadir";       // Urun yoksa magazada urun yok yazar
    }

    node* current;
    node* last = NULL;      // Gerekli degiskenler
    bool swapped;

    do {
        swapped = false;
        current = basdugum;

        while (current->next != last) {
            if (current->Price > current->next->Price) {
                int tempId = current->ProductId;            // Gecici degiskenler kullanilarak dugumlerin yerleri degistirilir
                string tempProduct = current->Product;
                int tempPrice = current->Price;

                current->ProductId = current->next->ProductId;
                current->Product = current->next->Product;
                current->Price = current->next->Price;

                current->next->ProductId = tempId;
                current->next->Product = tempProduct;
                current->next->Price = tempPrice;

                swapped = true;         // Yer degistirme gerceklestigi icin swapped true yapilir
            }
            current = current->next;
        }
        last = current;             // Bir sonraki döngüde son düðümü tekrar ele almayý önlemek için last güncellenir
    } while (swapped);          // Herhangi bir yer deðiþtirme yapýldýysa döngü tekrarlanýr
}

void calculateCosts(node* basdugum) {       // Urunlerin maliyetini hesaplayan fonksiyon
    if (basdugum == NULL) {
        cout << "Magazada urun bulunmamaktadir." << endl;     // Urun yoksa magazada urun yok yazar
        return;
    }

    node* iter = basdugum;

    while (iter != NULL)
    {
        int Cost = iter->Price * 0.60;      // Urunleri dolasir, urunlerin yuzde 60'ini alarak Cost degiskenine atar ve ekrana maliyeti yazar
        cout << "Urun numarasi " << iter->ProductId << " olan urunumuzun maliyeti " << Cost << " dir." << endl;
        iter = iter->next;
    }

}

void sameCostCount(node* basdugum, string product) {    // Ayný maliyetli kac adet urun oldugunu bulan fonksiyon
    int number{};
    int sameCost;

    if (basdugum == NULL) {
        cout << "Magazada urun bulunmamaktadir." << endl;       // Urun yoksa magazada urun yok yazar
        return;
    }

    node* temp = basdugum;

    if (product == temp->Product)
    {
        sameCost = temp->Price * 0.60;    // Disaridan girilen urun basdugumun urunune esitse ilk urunun yuzde 60'i sameCost degiskeninde tutulur
    }

    while (temp != NULL)
    {
        if (sameCost == temp->Price * 0.60)
        {
            number++;                       // Urunler dolasilir ve yuzde 60'i ayný olan urun buldukca number degiskenini 1 arttirir
        }
        temp = temp->next;
    }                                               // Ayný maliyete sahip urunlerin adetini number degiskenini kullanarak ekrana yazar

    cout << "Ayni Maliyete Sahip Toplam " << number << " adet urun vardir." << endl;

}

void maxCost(node* basdugum) {                      // En yuksek maliyete sahip urunu bulan fonksiyon
    if (basdugum == NULL) {
        cout << "Magazada urun bulunmamaktadir." << endl;     // Urun yoksa magazada urun yok yazar
        return;
    }

    node* iter = basdugum;
    int maxCost = iter->Price * 0.60;   // Basdugumun urun fiyatýnýn yuzde 60'i degiskene atanir

    while (iter != NULL)
    {
        int currentCost = iter->Price * 0.60;
        if (currentCost > maxCost)      // Urunler dolasilir ve urun fiyatinin yuzde 60'indan buyuk yeni urun bulunursa maxCost'a esitlenir
        {
            maxCost = currentCost;
        }
        iter = iter->next;
    }                                  // Maximum maliyete sahip urun maxCost degiskeni kullanilarak yazdirilir

    cout << "Maksimum Maliyete Sahip Urunun Maliyeti " << maxCost << " dir." << endl;
}

void minCost(node* basdugum) {                      // En dusuk maliyete sahip urunu bulan fonksiyon
    if (basdugum == NULL) {
        cout << "Magazada urun bulunmamaktadir." << endl;       // Urun yoksa magazada urun yok yazar
        return;
    }

    node* iter = basdugum;
    int minCost = iter->Price * 0.60;       // Basdugumun urun fiyatýnýn yuzde 60'i degiskene atanir

    while (iter != NULL)
    {
        int currentCost = iter->Price * 0.60;
        if (currentCost < minCost)     // Urunler dolasilir ve urun fiyatinin yuzde 60'indan kucuk yeni urun bulunursa minCost'a esitlenir
        {
            minCost = currentCost;
        }
        iter = iter->next;
    }                               // Minimum maliyete sahip urun minCost degiskeni kullanilarak yazdirilir

    cout << "Minimum Maliyete Sahip Urunun Maliyeti " << minCost << " dir." << endl;
}


struct node* raise(node* basdugum) {       // Listedeki urunlere yuzde 10 zam yapan fonksiyon

    node* temp = basdugum;

    while (temp != NULL) {

        temp->Price *= 1.10;     // Urunleri dolasir ve yeni urun fiyatini 10 ile carpip 100'e boler
        temp = temp->next;
    }
    return basdugum;

}


int main() {

    node* root = NULL;


    int secim;
    do {
        cout << "--------- Magaza Urun Takip Sistemine Hosgeldiniz ---------" << endl;
        cout << "1- Urun Kaydet" << endl;
        cout << "2- Urun Sil" << endl;
        cout << "3- Urun Guncelle" << endl;
        cout << "4- Listede Urun Ara" << endl;
        cout << "5- Listede Aranan Urunun Ozelliklerini Yazdir" << endl;
        cout << "6- Tum Urunleri Yazdir" << endl;
        cout << "7- Listedeki Urunlerin Fiyatini kucukten buyuge sirala" << endl;
        cout << "8- Listedeki Urunlerin Maliyetini Hesapla" << endl;
        cout << "9- Listedeki Tum Urunlere %10 Zam Yap" << endl;
        cout << "10- Minimum Maliyete Sahip Urunun Maliyetini Yazdir" << endl;
        cout << "11- Maksimum Maliyete Sahip Urunun Maliyetini Yazdir" << endl;
        cout << "12- Girdi Olarak Alinan Urune Iliskin Ayni Maliyetli Diger Urunlerin Toplam Sayisini bul" << endl;
        cout << "13- Tum Urunleri Dosyaya Yazdir" << endl;
        cout << "14- Dosyadan Urunleri Oku" << endl;
        cout << "15- Cikis" << endl;

        cout << "Secim Yapiniz: ";
        cin >> secim;

        int ID;
        string product;
        int price;
        int newPrice;
        int raiseAmount;
        int targetCost;

        switch (secim) {
        case 1:
            cout << "Urun numarasi giriniz: "; cin >> ID;
            cout << "Urun Adi giriniz: "; cin >> product;
            cout << "Urun Fiyati giriniz: "; cin >> price;
            add(root, ID, product, price);
            break;
        case 2:
            cout << "Silinecek Urunun Numarasini Giriniz: "; cin >> ID;
            deleteProduct(root, ID);
            break;
        case 3:
            cout << "Guncellenecek Urunun Numarasini Giriniz: "; cin >> ID;
            cout << "Yeni Urun Fiyatini Giriniz: "; cin >> newPrice;
            update(root, ID, newPrice);
            break;
        case 4:
            cout << "Aranacak Urunun Ismini Giriniz: "; cin >> product;
            find(root, product);
            break;
        case 5:
            cout << "Yazdirilacak Urunun Ismini Giriniz: "; cin >> product;
            printFinded(root, product);
            break;
        case 6:
            print(root);
            break;
        case 7:
            bubbleSort(root);
            cout << "Kucukten buyugu siralanmis Urun Listesi" << endl;
            print(root);
            break;
        case 8:
            calculateCosts(root);
            break;
        case 9:
            raise(root);
            cout << "Urunlerin Yeni Zamli Fiyati" << endl;
            print(root);
            break;
        case 10:
            minCost(root);
            break;
        case 11:
            maxCost(root);
            break;
        case 12:
            cout << "Kac Tane Ayni Maliyete Sahip OLdugunu Bulmak Istediginiz Urunu Giriniz: "; cin >> product;
            sameCostCount(root, product);
            break;
        case 13:
            printFile(root);
            cout << "Dosyaya yazdirildi." << endl;
            break;
        case 14:
            cout << "Dosyadan okunuyor.." << endl;
            readFile(root);
            break;
        case 15:
            system("cls");
            cout << "Cikis yapildi";
            break;
        default:
            cout << "Gecersiz secim. Lutfen tekrar deneyin." << endl;
            break;
        }
    } while (secim != 15);


}