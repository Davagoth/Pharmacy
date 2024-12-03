#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
typedef string daneosobowe;

class Czlowiek//Klasa czlowiek, po ktorej dzidziczy Klient i Pracownik
{
    friend class Klient;//zaprzyjaznienie klas
    friend class Pracownik;
private:
protected://domyslne ustawienia
    string imie;
    string nazwisko;
    daneosobowe dane = imie + " " + nazwisko;//wlasny typ dane osobowe

public:
    virtual void WypiszInfo(){//metoda wypisujaca informacje
        cout << "Imie: " << imie << endl;
        cout << "Nazwisko: " << nazwisko << endl;
        cout << "Dane osobowe: " << dane << endl;
    }
};

class Apteka//Klasa glowna, ktora kontroluje akltualna liczbe klientow, pracownikow i stan kasy
{
private:
    string nazwa;
    int liczbaKlientow;
    int liczbaPracownikow;
    int stanKasy;
public:
    Apteka(string nazwa, int liczbaKlientow, int liczbaPracownikow, int stanKasy){//konstruktor
        this->nazwa = nazwa;
        this->liczbaKlientow = liczbaKlientow;
        this->liczbaPracownikow = liczbaPracownikow;
        this->stanKasy = stanKasy;
    }
    virtual void WypiszInfo(){//metoda wypisujaca informacje
        cout << "Nazwa: " << nazwa << endl;
        cout << "Liczba pracownikow: " << liczbaPracownikow << endl;
        cout << "Liczba klientow: " << liczbaKlientow << endl;
        cout << "Stan kasy: " << stanKasy << endl;
    }
    void UpdateInfo(int liczbaPracownikow, int liczbaKlientow, int stanKasy){//metoda aktualizujaca aktualne informacje
        this->liczbaKlientow = liczbaKlientow;
        this->liczbaPracownikow = liczbaPracownikow;
        this->stanKasy = stanKasy;
    }
};

class Lek
{
private:
    int cena;
    bool czyNaRecepte;
    string naCo;
    string nazwa;
    bool czyJestWMagazynie;

public:
    Lek(string nazwa, string naCo, int cena, bool czyNaRecepte, bool czyJestWMagazynie){//konstruktor
        this->nazwa = nazwa;
        this->naCo = naCo;
        this->cena = cena;
        this->czyNaRecepte = czyNaRecepte;
        this->czyJestWMagazynie = czyJestWMagazynie;
    }
    ~Lek(){}//destruktor

    void WypiszInfo(){//metoda wypisujaca informacje
        cout << "Nazwa: " << nazwa << endl;
        cout << "Lek na: " << naCo << endl;
        cout << "Cena: " << cena << endl;
        cout << "Czy lek na recepte:";
        if(czyNaRecepte) cout << "Tak" << endl;
        else cout << "Nie" << endl;
        if(czyJestWMagazynie==0){
            cout << "Leku nie ma w magazynie" << endl;
        }
    }

    string jakilek(){//metoda pomocnicza do wybrania nazwy leku
        return nazwa;
    }

    int jakacena(){//metoda pomocnicza do wybrania ceny leku
        return cena;
    }
    string jakachoroba(){//metoda pomocnicza do wybrania choroby na ktora jest lek
        return naCo;
    }
};

class Klient : public Czlowiek//klasa dziedziczy po klasie czlowiek
{
private:
    string leklubchoroba;
    bool czyMaRecepte;

public:
    Klient(string nazwisko, string imie, bool czyMaRecepte, string leklubchoroba){//konstruktor
        this->nazwisko = nazwisko;
        this->imie = imie;
        this->leklubchoroba = leklubchoroba;
        this->czyMaRecepte = czyMaRecepte;
    }
    ~Klient(){}

    virtual void WypiszInfo(){//metoda wirtualna wypisujaca
        cout << "Dane osobowe: " << nazwisko << " " << imie << endl;
        cout << "Jaki lek potrzebuje?/Na jaka chorobe choruje?: " << leklubchoroba << endl;
        cout << "Czy posiada recepte?:";
        if(czyMaRecepte) cout << "Posiada" << endl;
        else cout << "Nie posiada" << endl;
    }

    bool recepta(){//metoda pomocnicza do sprawdzenia czy ma recepte
        if (czyMaRecepte) return 1;
        else return 0;
    };

    string jakileklubchoroba(bool czyWie){//metoda pomocnicza do wybrania choroby lub leku
        return leklubchoroba;
    }
};

class Pracownik : public Czlowiek//klasa dziedziczy po klasie czlowiek
{
public:
    Pracownik(string nazwisko, string imie){//konstruktor
        this->nazwisko = nazwisko;
        this->imie = imie;
    }
    ~Pracownik(){}//destruktor

    virtual void WypiszInfo(){//metoda wirtualna wypisuj?ca
        cout << "Dane osobowe: " << nazwisko << imie << endl;
    }

    string daneosobowe(){//metoda pomocnicza do wybrania danych osobowych
        return dane;
    }
};

class Sprzedaz//klasa do zapisu danych sprzedazy
{
private:
    int nrParagonu;
    bool czyPlatnoscKarta;
    string lek;
    string ktoSprzedawal;
    string ktoWydalRecepte;

public:
    Sprzedaz(int nrParagonu, bool czyPlatnoscKarta, string lek, string ktoSprzedawal, string ktoWydalRecepte){//konstruktor sprzedazy
        this->nrParagonu = nrParagonu;
        this->czyPlatnoscKarta = czyPlatnoscKarta;
        this->lek = lek;
        this->ktoSprzedawal = ktoSprzedawal;
        this->ktoWydalRecepte = ktoWydalRecepte;
    }
    void WypiszInfo(){//metoda wypisujaca
        cout << "Nr paragonu: " << nrParagonu << endl;
        cout << "Lek: " << lek << endl;
        if(czyPlatnoscKarta) cout << "Platnosc Karta" << endl;
        else cout << "Platnosc gotowka" << endl;
        cout << "Recepta wydana przez: " << ktoWydalRecepte << endl;
        cout << "Lek sprzedany przez: " << ktoSprzedawal << endl;
    }
};


int main() {
    //stworzenie list lekow, aktualnych klientow, rejestru zakupow, aktualnych pracownikow oraz aktualnie obslugiwanych klientow
    vector<Lek*> ListaLekow;
    vector<Klient*> ListaKlientow;
    vector<Sprzedaz*> RejestrZakupow;
    vector<Pracownik*> ListaPracownikow;
    vector<Klient*> ObslugiwaniKlienci;

    //stworzenie apteki
    Apteka A("Apteka Codzienna", 0, 0, 0);

    //dodanie lekow domyslnych
    Lek *L1 = new Lek("Ibuprom", "Bol_glowy", 20, 0, 1);
    Lek *L2 = new Lek("Apap", "Stan_zapalny", 25, 0, 1);
    Lek *L3 = new Lek("Rutinoscorbin", "Witamina_C", 15, 0, 1);
    Lek *L4 = new Lek("Bisocar", "Beta-blocker", 30, 1, 1);

    for(int i = 0; i < 10; i++){
        ListaLekow.push_back(L1);
        ListaLekow.push_back(L2);
        ListaLekow.push_back(L3);
        ListaLekow.push_back(L4);
    }

    //zapis lekow do pliku
    fstream p1;
    p1.open(R"(C:\Users\Dawid\Desktop\TEMP\PO\ListaLekow.txt)", ios::out|ios::app);
    if (p1.good()) {
        for(int i=0;i<ListaLekow.size()/4;i++) {
            p1 << "Ibuprom, Bol_glowy, 20, nie na recepte" << endl;
            p1 << "Apap, Stan_zapalny, 25, nie na recepte"<< endl;
            p1 << "Rutinoscorbin, Witamina_C, 15, nie na recepte" << endl;
            p1 << "Bisocar, Beta-blocker, 30, na recepte" << endl;
        }
    }
    p1.close();

    int choice, liczba_pracownikow = 0, liczba_klientow = 0, stan_kasy = 0, zajeci_pracownicy = 0, obslugiwani_klienci = 0;
    int y, czyznaleziono = 0, nrParagonu = 0;

    do{//menu
        cout << "Co chcesz zrobic?" << endl;
        cout << "0. Pokaz aktualne info o aptece" << endl;
        cout << "1. Dodaj pracownika" << endl;
        cout << "2. Usun pracownika" << endl;
        cout << "3. Dodaj klienta" << endl;
        cout << "4. Popros klienta do okienka" << endl;
        cout << "5. Obsluz klienta" << endl;
        cout << "6. Pokaz kolejke klientow" << endl;
        cout << "7. Dodaj lek" << endl;
        cout << "8. Pokaz dostepne leki" << endl;
        cout << "9. Podaj informacje o wszystkich tranzakcjach" << endl;
        cout << "Wybór: ";
        cin >> choice;
        switch (choice) {
            case 0:{
                A.WypiszInfo();
                break;
            }
            case 1:{
                if(liczba_pracownikow != 4){//max liczba pracownikow to 4
                    cout << "Podaj imie" << endl;
                    string imie;
                    cin >> imie;
                    cout << "Podaj nazwisko" << endl;
                    string nazwisko;
                    cin >> nazwisko;
                    ListaPracownikow.push_back(new Pracownik(nazwisko, imie));//dodanie do listy pracownikow pracownika
                    cout << endl;
                    liczba_pracownikow++;//zwiekszenie liczby pracownikow
                    //zapis nowego pracownika do pliku
                    fstream p2;
                    p2.open(R"(C:\Users\Dawid\Desktop\TEMP\PO\ListaPracownikow.txt)", ios::out|ios::app);
                    if (p2.good()) {
                        p2 << nazwisko << " " << imie << endl;
                    }
                    p2.close();
                    //aktualizacja aktualnych danych o aptece
                    A.UpdateInfo(liczba_pracownikow, liczba_klientow, stan_kasy);
                }
                else cout << "Wszystkie okienka zajete" << endl;
                break;
            }
            case 2: {
                //usun pracownika, kory najdluzej pracuje tylko gdy jest jakis pracownik jest i gdy nie obsluguje klienta
                if(liczba_pracownikow != 0 && (zajeci_pracownicy != obslugiwani_klienci || zajeci_pracownicy == 0)){
                    ListaPracownikow.erase(ListaPracownikow.begin());//usuniecie pracownika
                    cout << "Pracownik usuniety" << endl;
                    liczba_pracownikow--;
                    //aktualizacja aktualnych danych o aptece
                    A.UpdateInfo(liczba_pracownikow, liczba_klientow, stan_kasy);
                }
                else if (liczba_pracownikow == 0) cout << "Apteka nieczynna" << endl;//gdy nie ma pracownikow
                else cout << "Wszyscy pracownicy zajeci" << endl;//gdy wszyscy pracownicy obsluguja
                break;
            }
            case 3:{
                //dodaj klienta tylko gdy jest przynajmniej jeden pracownik
                if(liczba_pracownikow != 0){
                    cout << "Podaj imie" << endl;
                    string imie;
                    cin >> imie;
                    cout << "Podaj nazwisko" << endl;
                    string nazwisko;
                    cin >> nazwisko;
                    cout << "Czy wie jaki lek chce kupic?" << endl;
                    bool czywie;
                    cin >> czywie;
                    string nazwaleku;
                    string nazwachoroby;
                    bool czyMaRecepte;
                    if(czywie == 0){
                        cout << "Podaj nazwe choroby" << endl;
                        cin >> nazwachoroby;
                        cout << "Czy ma recepte? 0/1: Nie ma" << endl;
                        czyMaRecepte = 0;
                    }
                    else{
                        cout << "Podaj nazwe leku" << endl;
                        cin >> nazwaleku;
                        cout << "Czy ma recepte? 0/1:" << endl;
                        cin >> czyMaRecepte;
                    }

                    //dodanie klienta do kolejki
                    ListaKlientow.push_back(new Klient(nazwisko, imie, czyMaRecepte, nazwaleku));
                    cout << endl;

                    //aktualizacja aktualnych danych o aptece
                    A.UpdateInfo(liczba_pracownikow, liczba_klientow, stan_kasy);
                    liczba_klientow++;
                }
                else cout << "Nie ma pracownikow, apteka nieczynna" << endl;

                break;
            }
            case 4:{
                //klient moze podejsc tylko gdy przynajmniej jeden pracownik nie jest zajety
                if(zajeci_pracownicy != liczba_pracownikow && liczba_pracownikow != 0 && liczba_klientow > 0){
                    ObslugiwaniKlienci.push_back(ListaKlientow[0]);//dodanie klienta z kolejki do okienka
                    ListaKlientow.erase(ListaKlientow.begin());//usuniecie klienta z kolejki
                    cout << "Klient podchodzi do okienka" << endl;
                    zajeci_pracownicy++;
                }
                else cout << "Wszyscy pracownicy sa zajeci" << endl;
                break;
            }
            case 5:{
                if(ObslugiwaniKlienci.empty()) cout << "Popros klienta do okienka!" << endl;//gdy nie ma klienta przy okienku
                else{//gdy przynajmniej jeden klient jest przy okienku
                    int cena = 0;
                    if(ObslugiwaniKlienci[0]->recepta() == 1){//gdy klient ma recepte
                        cout << "Klient posiada recepte" << endl;
                        for(int i = 0; i < ListaLekow.size(); i++){//szukanie leku z recepty na liscie lekow
                            if(ObslugiwaniKlienci[0]->jakileklubchoroba(1) == ListaLekow[i]->jakilek()){
                                czyznaleziono = 1;
                                cena = ListaLekow[i]->jakacena();
                                ListaLekow.erase(ListaLekow.begin() + i);//usuniecie leku z listy
                                break;
                            }
                        }
                        if(czyznaleziono == 1){//gdy znaleziono, podaj informacje o sprzedazy
                            cout << "Lek znajduje sie na stanie" << endl;
                            cout << "Sprzedajemy lek" << endl;
                            cout << "Czy platnosc karta? 0/1" << endl;
                            bool rodzajPlatnosci;
                            cin >> rodzajPlatnosci;
                            cout << "Nazwisko i imie lekarza" << endl;
                            string ktoWydalRecepte;
                            cin >> ktoWydalRecepte;
                            nrParagonu++;
                            string nazwaleku;
                            nazwaleku = ObslugiwaniKlienci[0]->jakileklubchoroba(1);
                            string pracownik;
                            pracownik = ListaPracownikow[0]->daneosobowe();
                            //zapisz info o sprzedazy w rejestrze
                            RejestrZakupow.push_back(new Sprzedaz(nrParagonu, rodzajPlatnosci, nazwaleku, pracownik, ktoWydalRecepte));
                            fstream p3;
                            p3.open(R"(C:\Users\Dawid\Desktop\TEMP\PO\RejestrZakupow.txt)", ios::out|ios::app);
                            if (p3.good()) {
                                p3 << nrParagonu;
                                if(rodzajPlatnosci) p3 << ", platnosc karta, lek:";
                                else p3 << ", platnosc gotowka, lek:";
                                p3 << nazwaleku << ", sprzedawal: " << pracownik << ", recepte wydal: " << ktoWydalRecepte << endl;
                            }
                            p3.close();
                            stan_kasy = stan_kasy + cena;

                            for(int i=0; i<ListaPracownikow.size()-1; i++)//przesun pracownika na ostatniego, ktorym mozemy obslugiwac klienta
                                swap(ListaPracownikow[i],ListaPracownikow[i+1]);
                            ObslugiwaniKlienci.erase(ObslugiwaniKlienci.begin());//usun klienta, wychodzi z apteki
                            obslugiwani_klienci--;
                            liczba_klientow--;
                            //aktualizacja aktualnych danych o aptece
                            A.UpdateInfo(liczba_pracownikow, liczba_klientow, stan_kasy);
                            czyznaleziono = 0;
                            zajeci_pracownicy--;
                        }
                        else{//Leku nie ma na stanie
                            cout << "Leku nie ma na stanie" << endl;
                            for(int i=0; i<ListaPracownikow.size()-1; i++)//przesun pracownika na ostatniego, ktorym mozemy obslugiwac klienta
                                swap(ListaPracownikow[i],ListaPracownikow[i+1]);
                            ObslugiwaniKlienci.erase(ObslugiwaniKlienci.begin());//usun klienta, wychodzi z apteki
                            obslugiwani_klienci--;
                            liczba_klientow--;
                            A.UpdateInfo(liczba_pracownikow, liczba_klientow, stan_kasy);
                            czyznaleziono = 0;
                            zajeci_pracownicy--;
                        }
                    }
                    else{//gdy klient nie ma recepty
                        cout << "Klient nie ma recepty" << endl;
                        bool czyWie;
                        cout << "Czy klient wie co chce kupic?: ";
                        cin >> czyWie;
                        if(czyWie){//gdy wie jaki lek chce kupic
                            for(int i = 0; i < ListaLekow.size(); i++){//szukanie leku na liscie lekow
                                if(ObslugiwaniKlienci[0]->jakileklubchoroba(1) == ListaLekow[i]->jakilek()){
                                    czyznaleziono = 1;
                                    cena = ListaLekow[i]->jakacena();
                                    ListaLekow.erase(ListaLekow.begin() + i);//usuniecie leku z listy lekow dostepnych
                                    break;
                                }
                            }
                            if(czyznaleziono == 1){//gdy znaleziono, podaj informacje o sprzedazy
                                cout << "Lek znajduje sie na stanie" << endl;
                                cout << "Sprzedajemy lek" << endl;
                                cout << "Czy platnosc karta? 0/1" << endl;
                                bool rodzajPlatnosci;
                                cin >> rodzajPlatnosci;
                                nrParagonu++;
                                string nazwaleku;
                                nazwaleku = ObslugiwaniKlienci[0]->jakileklubchoroba(1);
                                stan_kasy = stan_kasy + cena;

                                for(int i=0; i<ListaPracownikow.size()-1; i++)//przesun pracownika na ostatniego, ktorym mozemy obslugiwac klienta
                                    swap(ListaPracownikow[i],ListaPracownikow[i+1]);
                                ObslugiwaniKlienci.erase(ObslugiwaniKlienci.begin());//usun klienta, wychodzi z apteki
                                obslugiwani_klienci--;
                                liczba_klientow--;
                                //aktualizacja aktualnych danych o aptece
                                A.UpdateInfo(liczba_pracownikow, liczba_klientow, stan_kasy);
                                czyznaleziono = 0;
                                zajeci_pracownicy--;
                            }
                            else{//gdy nie ma leku
                                cout << "Leku nie ma na stanie" << endl;
                                for(int i=0; i<ListaPracownikow.size()-1; i++)//przesun pracownika na ostatniego, ktorym mozemy obslugiwac klienta
                                    swap(ListaPracownikow[i],ListaPracownikow[i+1]);
                                ObslugiwaniKlienci.erase(ObslugiwaniKlienci.begin());//usun klienta, wychodzi z apteki
                                obslugiwani_klienci--;
                                liczba_klientow--;
                                //aktualizacja aktualnych danych o aptece
                                A.UpdateInfo(liczba_pracownikow, liczba_klientow, stan_kasy);
                                czyznaleziono = 0;
                                zajeci_pracownicy--;
                            }
                        }
                        else{//gdy klient nie wie co chce kupic, ale wie na co
                            cout << "Podaj na co klient chce lek:" << endl;
                            string naCo;
                            cin >> naCo;
                            for(int i = 0; i < ListaLekow.size(); i++){//szukanie leku na chorobe na liscie lekow
                                if(ObslugiwaniKlienci[0]->jakileklubchoroba(0) == ListaLekow[i]->jakachoroba()){
                                    czyznaleziono = 1;
                                    string nazwaleku;
                                    nazwaleku = ListaLekow[i]->jakilek();
                                    cena = ListaLekow[i]->jakacena();
                                    ListaLekow.erase(ListaLekow.begin() + i);//usuniecie leku z listy lekow
                                    break;
                                }
                            }
                            if(czyznaleziono == 1){//podaj info o sprzedazy
                                cout << "Lek znajduje sie na stanie" << endl;
                                cout << "Sprzedajemy lek" << endl;
                                cout << "Czy platnosc karta? 0/1" << endl;
                                bool rodzajPlatnosci;
                                cin >> rodzajPlatnosci;
                                nrParagonu++;
                                stan_kasy = stan_kasy + cena;

                                for(int i=0; i<ListaPracownikow.size()-1; i++)//przesun pracownika na ostatniego, ktorym mozemy obslugiwac klienta
                                    swap(ListaPracownikow[i],ListaPracownikow[i+1]);
                                ObslugiwaniKlienci.erase(ObslugiwaniKlienci.begin());//usun klienta, wychodzi z apteki
                                obslugiwani_klienci--;
                                liczba_klientow--;
                                //aktualizacja aktualnych danych o aptece
                                A.UpdateInfo(liczba_pracownikow, liczba_klientow, stan_kasy);
                                czyznaleziono = 0;
                                zajeci_pracownicy--;
                            }
                            else{//gdy nie ma leku
                                cout << "Leku nie ma na stanie" << endl;
                                for(int i=0; i<ListaPracownikow.size()-1; i++)//przesun pracownika na ostatniego, ktorym mozemy obslugiwac klienta
                                    swap(ListaPracownikow[i],ListaPracownikow[i+1]);
                                ObslugiwaniKlienci.erase(ObslugiwaniKlienci.begin());//usun klienta, wychodzi z apteki
                                obslugiwani_klienci--;
                                liczba_klientow--;
                                //aktualizacja aktualnych danych o aptece
                                A.UpdateInfo(liczba_pracownikow, liczba_klientow, stan_kasy);
                                czyznaleziono = 0;
                                zajeci_pracownicy--;
                            }
                        }
                    }
                }
                break;
            }
            case 6:{//wypisanie kolejki
                for(int i = 0; i < ListaKlientow.size(); i++) {
                    ListaKlientow[i] -> WypiszInfo();
                }
                break;
            }
            case 7:{//dodaj lek
                cout << "Podaj nazwe: " << endl;
                string nazwa;
                cin >> nazwa;
                cout << "Podaj na co jest lek: " << endl;
                string naCo;
                cin >> naCo;
                cout << "Podaj cene: " << endl;
                int cena;
                cin >> cena;
                cout << "Podaj ilosc: " << endl;
                int ilosc;
                cin >> ilosc;
                cout << "Podaj czy jest na recepte: " << endl;
                bool czyNaRecepte;
                cin >> czyNaRecepte;
                for(int i=0;i<ilosc;i++){//dodaj ilosc lekow
                    ListaLekow.push_back(new Lek(nazwa, naCo, cena, czyNaRecepte, 1));
                }
                //zapis nowych lekow na liste dostepnych lekow
                fstream p4;
                p4.open(R"(C:\Users\Dawid\Desktop\TEMP\PO\ListaLekow.txt)", ios::out|ios::app);
                if (p4.good()) {
                    for(int i=ListaPracownikow.size();i<ListaLekow.size()+ilosc;i++) {
                        p4 << nazwa << ", " << naCo << ", " << cena << ", " << endl;
                        if (czyNaRecepte) p4 << "na recepte" << endl;
                        else p4 << "nie na recepte" << endl;

                    }
                }
                p4.close();
                cout << endl;
                break;
            }
            case 8:{//wypisz liste lekow
                for(int i = 0; i < ListaLekow.size(); i++) {
                    ListaLekow[i] -> WypiszInfo();
                }
                break;
            }
            case 9:{//wypisz rejestr zapisanych zakupow
                for(int i = 0; i < RejestrZakupow.size(); i++) {
                    RejestrZakupow[i] -> WypiszInfo();
                }
                break;
            }
            default:{
                cout << "Wybierz inna opcje" << endl;
                break;
            }
        }
        do{
            cout << "Chcesz kontynuowac? 1/0: ";
            cin >> y;
            if(y != 1 && y!= 0) cout << "Podaj inna liczbe!" << endl;
        }while(y!=1 && y!= 0);
    }while(y==1);

    return 0;
}