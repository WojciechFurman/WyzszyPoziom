#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <fstream>
#include <vector>


using namespace std;

struct ksiazkaAdresowa {
    int id;
    string imie, nazwisko, telefon, email, adres;
};

bool czyNumerPoprawny(string telefon) {
    int dlugosc = telefon.length();
    int i=0;
    while(i<dlugosc) {
        if((telefon[i]>47 && 58>telefon[i]) || telefon[i]==32) {
            i++;
        } else {
            cout<< endl<<"Nieprawidłowy numer, podaj jeszcze raz: ";
            return false;
        }

    }
    return true;
}
void zapisZmianWPliku (vector <ksiazkaAdresowa> adresaci) {
    fstream plikKontaktow;
    plikKontaktow.open("Kontakty.txt", ios::out);
    for (int k=0; k < adresaci.size(); k++) {
        plikKontaktow << adresaci[k].id << "|";
        plikKontaktow << adresaci[k].imie << "|";
        plikKontaktow << adresaci[k].nazwisko << "|";
        plikKontaktow << adresaci[k].telefon << "|";
        plikKontaktow << adresaci[k].email << "|";
        plikKontaktow << adresaci[k].adres << "|";
        plikKontaktow << endl;
    }
    plikKontaktow.close();
}
int zapiszNowyKontakt(vector <ksiazkaAdresowa> &adresaci, int liczba_kontaktow) {
    ksiazkaAdresowa nowyAdresat;
    string imie, nazwisko, numerTel, adresEmail, adresZam;
    cout << "Podaj imie nowego kontaktu: ";
    cin >> imie;
    cout << "Podaj nazwisko nowego kontaktu: ";
    cin >> nazwisko;
    cout << "Podaj numer telefonu nowego kontaktu: ";
    cin.sync();
    bool pomocnicza=false;
    while (pomocnicza ==false) {
        getline(cin, numerTel);
        pomocnicza = czyNumerPoprawny(numerTel);

    }
    cin.sync();
    cout << "Podaj email nowego kontaktu: ";
    cin >> adresEmail;
    cin.sync();
    cout << "Podaj adres nowego kontaktu: ";
    getline(cin, adresZam);

    nowyAdresat.imie = imie;
    nowyAdresat.nazwisko = nazwisko;
    nowyAdresat.telefon = numerTel;
    nowyAdresat.adres = adresZam;
    nowyAdresat.email = adresEmail;
    nowyAdresat.id = liczba_kontaktow+1;
    adresaci.push_back(nowyAdresat);

    fstream plikKontaktow;
    plikKontaktow.open("Kontakty.txt", ios::out | ios:: app);

    if (plikKontaktow.good() == true) {

        plikKontaktow <<nowyAdresat.id<<"|";
        plikKontaktow <<nowyAdresat.imie<< "|";
        plikKontaktow <<nowyAdresat.nazwisko<<"|";
        plikKontaktow <<nowyAdresat.telefon<<"|";
        plikKontaktow <<nowyAdresat.email<<"|";
        plikKontaktow <<nowyAdresat.adres<<"|";
        plikKontaktow <<endl;
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system ("pause");
    }

    system("cls");
    cout << "-----Kontakt został zapisany!-----";
    Sleep(2000);
    return liczba_kontaktow+1;

}
void wyswietlWszystkieKontakty( vector <ksiazkaAdresowa> adresaci) {
    system("cls");
    for (int i=0; i < adresaci.size(); i++) {
        cout<< adresaci[i].imie << " " << adresaci[i].nazwisko << endl;
        cout<< "Nr tel: " << adresaci[i].telefon << endl;
        cout<< "@: " << adresaci[i].email << endl;
        cout<< "Adres: " << adresaci[i].adres << endl;
        cout<< "Nr. w książce adresowej: " << adresaci[i].id << endl << endl;
    }
    getch();

}

int wczytajKontakty(vector<ksiazkaAdresowa> &adresaci, int liczba_kontaktow) {

    string pobranaLinia;
    int danaDoprzypisana=1;
    fstream plikKontaktow;
    plikKontaktow.open("Kontakty.txt", ios::in);

    if (plikKontaktow.good()==false) {
        cout<<"Nie udało się załadować książki adresowej!!!";
        Sleep(3000);
        system("cls");
    } else {
        ksiazkaAdresowa nowyAdresat;
        while(getline(plikKontaktow, pobranaLinia)) {
            int dlugoscLini = pobranaLinia.length();
            string pomocnicza="";

            for(int i = 0; i < dlugoscLini ; i++ ) {

                while (pobranaLinia[i] != '|') {
                    pomocnicza += pobranaLinia[i];
                    i++;
                    switch(danaDoprzypisana) {
                    case 1:
                        nowyAdresat.id = atoi(pomocnicza.c_str());
                        liczba_kontaktow = nowyAdresat.id;
                        break;
                    case 2:
                        nowyAdresat.imie = pomocnicza;
                        break;
                    case 3:
                        nowyAdresat.nazwisko = pomocnicza;
                        break;
                    case 4:
                        nowyAdresat.telefon = pomocnicza;
                        break;
                    case 5:
                        nowyAdresat.email = pomocnicza;
                        break;
                    case 6:
                        nowyAdresat.adres = pomocnicza;
                        break;
                    }
                }
                danaDoprzypisana+=1;
                pomocnicza = "";
            }
            adresaci.push_back(nowyAdresat);
            danaDoprzypisana=1;
        }
        plikKontaktow.close();
    }
    return liczba_kontaktow;
}
void wypiszKontaktyPoImieniu(vector<ksiazkaAdresowa> adresaci) {
    system("cls");
    if (adresaci.size() == 0) {
        cout << " W książce nie ma jeszcze żadnego kontaktu!";
        Sleep(2000);
    } else {

        string imie;
        cout << "Podaj imie poszukiwanego kontaktu: ";
        cin >> imie;
        system("cls");
        for (int i=0; i < adresaci.size(); i++) {
            if (adresaci[i].imie == imie) {
                cout<< adresaci[i].imie << " " << adresaci[i].nazwisko << endl;
                cout<< "Nr tel: " << adresaci[i].telefon << endl;
                cout<< "@: " << adresaci[i].email << endl;
                cout<< "Adres: " << adresaci[i].adres << endl;
                cout<< "Nr. w książce adresowej: " << adresaci[i].id << endl << endl;
            }
        }
        cout << "Naciśnij dowolny klawisz aby powrócić do menu..."<<endl;
        getch();
    }

}
void wypiszKontaktyPoNazwisku(vector<ksiazkaAdresowa> adresaci) {
    system("cls");
    if (adresaci.size() == 0) {
        cout << " W książce nie ma jeszcze żadnego kontaktu!";
        Sleep(2000);
    } else {

        string nazwisko;
        cout << "Podaj nazwisko poszukiwanego kontaktu: ";
        cin >> nazwisko;
        system("cls");
        for (int i=0; i < adresaci.size(); i++) {
            if (adresaci[i].nazwisko == nazwisko) {
                cout<< adresaci[i].nazwisko << " " << adresaci[i].imie << endl;
                cout<< "Nr tel: " << adresaci[i].telefon << endl;
                cout<< "@: " << adresaci[i].email << endl;
                cout<< "Adres: " << adresaci[i].adres << endl;
                cout<< "Nr. w książce adresowej: " << adresaci[i].id << endl << endl;
            }
        }
        cout << "Naciśnij dowolny klawisz aby powrócić do menu..."<<endl;
        getch();
    }
}

string zmienDaneKontaktu () {
    string pomocnicza;
    cin >> pomocnicza;
    return pomocnicza;

}
string zmienNumerTelKontaktu () {
    string pomocnicza;
    cin.sync();
    bool tymczasowa;
    while (tymczasowa==false) {
        getline(cin, pomocnicza);
        tymczasowa = czyNumerPoprawny(pomocnicza);

    }
    return pomocnicza;

}
string zmienAdresKontaktu () {
    string pomocnicza;
    cin.sync();
    getline(cin, pomocnicza);
    return pomocnicza;

}

int zmienInformacjeWKontakcie(vector<ksiazkaAdresowa> &adresaci) {
    int idKontaktu;
    char wybor;
    string imie, nazwisko, numerTel, adresEmail, adresZam;
    system("cls");
    cout << "Podaj id kontaktu który chcesz zmienić: ";
    int sprawdzanyKontakt=0;
    cin >> idKontaktu;


    while (sprawdzanyKontakt < adresaci.size()) {
        if (adresaci[sprawdzanyKontakt].id == idKontaktu) {
            break;  // zatrzymuje petle jesli trafi na to id i dzialamy na kontakt[i] równym idKontaktu
        } else {
            sprawdzanyKontakt++;
            if (sprawdzanyKontakt >= adresaci.size() ) {
                system("cls");
                cout << "Nie ma w książce kontaktu o podanym id" << endl;
                cout << "Za chwilę nastąpi powrót do menu głównego" << endl;
                Sleep(2000);
                return 0;
            }
        }
    }
    while (1) {
        system("cls");
        cout<< adresaci[sprawdzanyKontakt].imie << " " << adresaci[sprawdzanyKontakt].nazwisko << endl;
        cout<< "Nr tel: " << adresaci[sprawdzanyKontakt].telefon << endl;
        cout<< "@: " << adresaci[sprawdzanyKontakt].email << endl;
        cout<< "Adres: " << adresaci[sprawdzanyKontakt].adres << endl;
        cout<< "Nr. w książce adresowej: " << adresaci[sprawdzanyKontakt].id << endl << endl;
        cout<< "1. Zmień imie." << endl;
        cout<< "2. Zmień nazwisko." << endl;
        cout<< "3. Zmień numer telefonu." << endl;
        cout<< "4. Zmień adres @." << endl;
        cout<< "5. Zmień adres zamieszkania." << endl<<endl;
        cout<< "0. Zapisz i powróć do menu" << endl<<endl;


        cin >> wybor;

        switch(wybor) {
        case '1':
            cout << "Podaj nowe imie dla kontaktu: ";
            adresaci[sprawdzanyKontakt].imie = zmienDaneKontaktu();
            break;
        case '2':
            cout << "Podaj nowe nazwisko dla kontaktu: ";
            adresaci[sprawdzanyKontakt].nazwisko = zmienDaneKontaktu();
            break;
        case '3':
            cout << "Podaj nowy numer telefonu dla kontaktu: ";
            adresaci[sprawdzanyKontakt].telefon = zmienNumerTelKontaktu();
            break;
        case '4':
            cout << "Podaj nowy adres @ dla kontaktu: ";
            adresaci[sprawdzanyKontakt].email = zmienDaneKontaktu();
            break;
        case '5':
            cout << "Podaj nowy adres dla kontaktu: ";
            adresaci[sprawdzanyKontakt].adres = zmienAdresKontaktu();
            break;
        case '0':
            zapisZmianWPliku(adresaci);
            return 0;
            break;
        }
    }
}
void usunKontakt(vector <ksiazkaAdresowa> &adresaci, int & idOstKontaktu ) {

    vector <ksiazkaAdresowa>::iterator itr = adresaci.begin();
    int idKontaktu;
    char wybor;

    system("cls");
    cout << "Podaj id kontaktu który chcesz usunąć: ";
    int sprawdzanyKontakt=0;
    cin >> idKontaktu;


    while (sprawdzanyKontakt < adresaci.size()) {
        if (adresaci[sprawdzanyKontakt].id == idKontaktu) {
            break;  // zatrzymuje petle jesli trafi na to id i dzialamy na kontakt[i] równym idKontaktu
        } else {
            sprawdzanyKontakt++;
            itr++;
            if (sprawdzanyKontakt >= adresaci.size() ) {
                system("cls");
                cout << " Nie ma w książce kontaktu o podanym id" << endl;
                cout << " Za chwilę nastąpi powrót do menu głównego" << endl;
                Sleep(2000);
                return ;
            }
        }

    }
    adresaci.erase(itr);
    sprawdzanyKontakt = adresaci.size() - 1;
    idOstKontaktu = adresaci[sprawdzanyKontakt].id;

    zapisZmianWPliku(adresaci);
    system("cls");
    cout << "-----Kontakt został usunięty!-----";
    cout << sprawdzanyKontakt << endl;
    Sleep(2000);
}

int main() {

    vector <ksiazkaAdresowa> adresaci;

    SetConsoleOutputCP(1250);
    system("chcp 1250");
    int liczba_kontaktow = 0;
    char wybor;
    liczba_kontaktow = wczytajKontakty(adresaci, liczba_kontaktow);

    while (1) {
        system("cls");
        cout<< " ===--__KSIĄŻKA ADRESOWA__--=== " <<endl<<endl;
        cout<< "1. Dodaj adresata" << endl;
        cout<< "2. Wyszukaj po imieniu" << endl;
        cout<< "3. Wyszukaj po nazwisku" << endl;
        cout<< "4. Wyświetl wszystkich adresatów" << endl;
        cout<< "5. Usuń adresata" << endl;
        cout<< "6. Edytuj adresata" << endl << endl<<endl<<endl;

        cout << "Zapisanych kontaków: " << adresaci.size() <<endl;
        cout<< "0.Zakończ program" << endl<< endl;


        cin >> wybor;
        switch(wybor) {
        case '1':
            liczba_kontaktow = zapiszNowyKontakt(adresaci, liczba_kontaktow);
            break;
        case '2':
            wypiszKontaktyPoImieniu(adresaci);
            break;
        case '3':
            wypiszKontaktyPoNazwisku(adresaci);
            break;
        case '4':
            wyswietlWszystkieKontakty(adresaci);
            break;
        case '5':
            usunKontakt(adresaci, liczba_kontaktow);
            break;
        case '6':
            zmienInformacjeWKontakcie(adresaci);
            break;
        case '0':
            system("cls");
            exit(0);
        }
    }
}
