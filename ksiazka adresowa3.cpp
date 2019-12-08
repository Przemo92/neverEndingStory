#include <iostream>
#include <windows.h> // opoznianie programu funkcja Sleep(), czyszczenie konsoli system("cls");
#include <string>
#include <conio.h> //getch()
#include <fstream> // zapisywanie danych do pliku tekstowego
#include <sstream> // zamiana int na string
#include <vector>

using namespace std;

struct Znajomy
{
    int idUzytkownika;
    int id;
    string imie, nazwisko, nrTelefonu, adres, email;
};
struct Uzytkownik
{
    int idUzytkownika;
    string login;
    string haslo;
};
string zamianaIntNaString (int id)
{
    ostringstream ss;
    ss << id;
    string zmienionyIntNaString = ss.str();
    return zmienionyIntNaString;
}
int policzNastepneIdZnajomego ()
{
    int idUzytkownika;
    string linia;
    string ostatniaLinia = "";
    fstream plik;
    plik.open ("lista.txt", ios::in);

    while (getline (plik, linia))
    {
        if (linia != "")
            ostatniaLinia=linia;
    }
    if (ostatniaLinia == "")
        idUzytkownika = 0;
    else
    {
        vector<string>slowaZLinijki(0);
        for (int i=0; i<ostatniaLinia.length(); i++)
        {
            if (ostatniaLinia[i] == '|')
                ostatniaLinia[i] = ' ';
        }
        string slowo;
        stringstream iss (ostatniaLinia);
        while(iss >> slowo)
        {
            slowaZLinijki.push_back(slowo);
        }
        idUzytkownika = atoi (slowaZLinijki[0].c_str());
    }
    plik.close();
    return idUzytkownika +1;
}
void dodajZnajomego (vector <Znajomy> &nowyZnajomy, int idUzytkownika)
{
    Znajomy dane;
    dane.id =  policzNastepneIdZnajomego();

    zamianaIntNaString (dane.id);

    dane.idUzytkownika = idUzytkownika;
    zamianaIntNaString (dane.idUzytkownika);

    string imie, nazwisko, nrTelefonu, adres, email;
    cout << "Podaj imie znajomego: " << endl;
    cin >> dane.imie;
    cout << "Podaj nazwisko znajomego: " << endl;
    cin >> dane.nazwisko;
    cout << "Podaj numer telefonu komorkowego do znajomego: " << endl;
    cin.sync();
    getline (cin, dane.nrTelefonu);
    cout << "Podaj adres email znajomego: " << endl;
    cin >> dane.email;
    cout << "Podaj adres zamieszkania znajomego: " << endl;
    cin.sync();
    getline(cin, dane.adres);

    nowyZnajomy.push_back(dane);

    fstream plik;
    plik.open("lista.txt", ios::out | ios::app); // ios::app dodaje sie aby dopisywac dane do pliku

    plik << dane.id << "|";
    plik << dane.idUzytkownika << "|";
    plik << dane.imie << "|";
    plik << dane.nazwisko << "|";
    plik << dane.nrTelefonu << "|";
    plik << dane.email << "|";
    plik << dane.adres << "|" << endl;

    plik.close();

    cout << "Znajomy zarejestrowany" << endl;
    Sleep(1000);
}
void szukajImie (vector <Znajomy> nowyZnajomy)
{
    string imie, nazwisko;
    cout << "Podaj szukane imie znajomego" << endl;
    cin >> imie;
    for (int i=0; i<nowyZnajomy.size(); i++)
    {
        if (nowyZnajomy[i].imie == imie)
        {
            cout << nowyZnajomy[i].imie << " " << nowyZnajomy[i].nazwisko << endl;
            cout << "telefon: " << nowyZnajomy[i].nrTelefonu << ", adres:" << nowyZnajomy[i].email << ", adres: " << nowyZnajomy[i].adres << endl;
        }
    }
    getch();

}
void szukajNazwisko(vector <Znajomy> nowyZnajomy)
{
    string imie, nazwisko;
    cout << "Podaj szukane nazwisko znajomego" << endl;
    cin >> nazwisko;
    for (int i=0; i<nowyZnajomy.size(); i++)
    {
        if (nowyZnajomy[i].nazwisko == nazwisko)
        {
            cout << nowyZnajomy[i].imie << " " << nowyZnajomy[i].nazwisko << endl;
            cout << "telefon: "<<nowyZnajomy[i].nrTelefonu << ", adres:" << nowyZnajomy[i].email << ", adres: " << nowyZnajomy[i].adres << endl;
        }
    }
    getch();
}
void wszyscyZnajomi (vector <Znajomy> &nowyZnajomy)
{
    Znajomy dane;

    for (int i=0; i<nowyZnajomy.size(); i++)
    {
        if (nowyZnajomy[i].imie != "" && (nowyZnajomy[i].imie  != nowyZnajomy[i+1].imie ))
        {
            cout << nowyZnajomy[i].imie << " "<<nowyZnajomy[i].nazwisko << endl;
            cout << "telefon: " << nowyZnajomy[i].nrTelefonu << ", adres:" << nowyZnajomy[i].email << ", adres: " << nowyZnajomy[i].adres << endl;
        }
    }
    getch();
}
void wczytanieZnajomych (vector <Znajomy> &nowyZnajomy, int idUzytkownika)
{
    fstream plik;
    plik.open ("lista.txt", ios::in);
    if (plik.good() == false)
    {
        cout << "Nie znaleziono listy znajomych" << endl;
        Sleep(1000);
    }
    else
    {
        string linia;
        int nr_lini = 1;
        Znajomy obiekt;
        while (getline (plik, linia))
        {
            switch (nr_lini)
            {
            case 1:
                vector<string>slowaZLinijki(0);
                for (int i=0; i<linia.length(); i++)
                {
                    if (linia[i] == '|')
                        linia[i] = ' ';
                }
                string slowo;
                stringstream iss (linia);
                while(iss >> slowo)
                {
                    slowaZLinijki.push_back(slowo);
                }

                if (atoi (slowaZLinijki[1].c_str()) == idUzytkownika) // gdy zmieniam idUzyt to id znajomego mi sie sypie
                {
                    obiekt.id = atoi (slowaZLinijki[0].c_str());
                    obiekt.idUzytkownika = atoi (slowaZLinijki[1].c_str());
                    obiekt.imie = slowaZLinijki[2];
                    obiekt.nazwisko = slowaZLinijki[3];
                    obiekt.nrTelefonu = slowaZLinijki[4];
                    obiekt.email = slowaZLinijki[5];
                    obiekt.adres = slowaZLinijki[6];
                    nowyZnajomy.push_back(obiekt);
                }
                slowaZLinijki.clear();
                break;
            }
        }
        plik.close();
    }
}
void zapisNowychDanychDoPliku (vector <Znajomy> &nowyZnajomy, int idUzytkownika)
{
    string linia;
    int nr_lini = 1;
    int j = 0;
    fstream plik;
    plik.open("lista.txt", ios::in);
    fstream plik2;
    plik2.open("listaTymczasowa.txt", ios::out | ios::app);
    while (getline (plik, linia))
    {
        switch (nr_lini)
        {
        case 1:
            vector<string>slowaZLinijki(0);
            for (int i=0; i<linia.length(); i++)
            {
                if (linia[i] == '|')
                    linia[i] = ' ';
            }
            string slowo;
            stringstream iss (linia);
            while(iss >> slowo)
            {
                slowaZLinijki.push_back(slowo);
            }
            if ((atoi (slowaZLinijki[1].c_str()) == idUzytkownika) && (atoi (slowaZLinijki[0].c_str()) == nowyZnajomy[j].id) && (j<nowyZnajomy.size()))
            {
                plik2 << nowyZnajomy[j].id << "|";
                plik2 << nowyZnajomy[j].idUzytkownika << "|";
                plik2 << nowyZnajomy[j].imie << "|";
                plik2 << nowyZnajomy[j].nazwisko << "|";
                plik2 << nowyZnajomy[j].nrTelefonu << "|";
                plik2 << nowyZnajomy[j].email << "|";
                plik2 << nowyZnajomy[j].adres << "|" << endl;
                slowaZLinijki.clear();
                j++;
            }
            else if ((atoi (slowaZLinijki[1].c_str()) == idUzytkownika) && (atoi (slowaZLinijki[0].c_str()) != nowyZnajomy[j].id))
            {
                break;
            }
            else if (atoi (slowaZLinijki[1].c_str()) != idUzytkownika)
            {
                for (int i=0; i<linia.length(); i++)
                {
                    if (linia[i] == ' ')
                        linia[i] = '|';
                }
                plik2 << linia << endl;
            }
        }
    }
    plik.close();
    plik2.close();
    remove ("lista.txt");
    rename ("listaTymczasowa.txt", "lista.txt");
}
void usuwanieZnajomego(vector <Znajomy> &nowyZnajomy, int idUzytkownika)
{
    int liczba;
    cout << "Podaj numer id adresata, ktory chcesz usunac z kontaktow" << endl;
    cin >> liczba;
    char odpowiedz;
    cout << "Jesli chcesz usunac kontakt wcisnij klawisz t..." << endl;
    cin >> odpowiedz;

    if (odpowiedz == 't')
    {
        for (int i=0; i<nowyZnajomy.size(); i++)
        {
            if (nowyZnajomy[i].id == liczba)
            {
                nowyZnajomy.erase(nowyZnajomy.begin()+i);
                zapisNowychDanychDoPliku (nowyZnajomy, idUzytkownika);
                Sleep(1000);
                cout << "Kontakt usunieto" << endl;
            }
        }
    }
}
void edycjaAdresata(vector <Znajomy> &nowyZnajomy, int idUzytkownika)
{
    int liczba;
    char wybor;
    string imie, nazwisko, nrTelefonu, email, adres;
    cout << "Podaj id adresata, ktorego chcesz zedytowac" << endl;
    cin >> liczba;
    for (int i=0; i<nowyZnajomy.size(); i++)
    {
        if (nowyZnajomy[i].id == liczba)
        {
            system("cls");
            cout << "Co chcesz zedytowac?" << endl;
            cout << "1. Imie" << endl;
            cout << "2. Nazwisko" << endl;
            cout << "3. Numer telefonu" << endl;
            cout << "4. Email" << endl;
            cout << "5. Adres" << endl;
            cout << "6. Powrot do menu" << endl;
            cout << "Twoj wybor: ";
            cin >> wybor;

            if (wybor == '1')
            {
                cout << "Podaj nowe imie dla adresata: ";
                cin >> imie;
                nowyZnajomy[i].imie = imie;
                cout << "Zmieniono imie" << endl;
                Sleep(1000);
            }
            else if (wybor == '2')
            {
                cout << "Podaj nowe nazwisko dla adresata: ";
                cin >> nazwisko;
                nowyZnajomy[i].nazwisko = nazwisko;
                cout << "Zmieniono nazwisko" << endl;
                Sleep(1000);
            }
            else if (wybor == '3')
            {
                cout << "Podaj nowy numer telefonu dla adresata: ";
                cin.sync();
                getline (cin, nrTelefonu);
                nowyZnajomy[i].nrTelefonu = nrTelefonu;
                cout << "Zmieniono numer telefonu" << endl;
                Sleep(1000);
            }
            else if (wybor == '4')
            {
                cout << "Podaj nowy email dla adresata: ";
                cin >> email;
                nowyZnajomy[i].email = email;
                cout << "Zmieniono email" << endl;
                Sleep(1000);
            }
            else if (wybor == '5')
            {
                cout << "Podaj nowy adres dla adresata: ";
                cin.sync();
                getline (cin, adres);
                nowyZnajomy[i].adres = adres;
                cout << "Zmieniono adres" << endl;
                Sleep(1000);
            }
            else if (wybor == '6')
            {
                return;
            }
        }
    }
    zapisNowychDanychDoPliku (nowyZnajomy, idUzytkownika);
}
void zapisNowegoHasla (vector <Uzytkownik> &nowyUzytkownik)
{
   fstream plik;
    plik.open("listaUzytkownikow.txt", ios::out);
    string linia;

        for (int i=0; i<nowyUzytkownik.size(); i++)
        {
                        plik << nowyUzytkownik[i].idUzytkownika << "|";
                        plik << nowyUzytkownik[i].login << "|";
                        plik << nowyUzytkownik[i].haslo << "|" << endl;
        }
    plik.close();
    cout << "Zmieniono haslo" << endl;
    Sleep(1000);
}
void zmianaHasla(vector <Uzytkownik> &nowyUzytkownik, int idUzytkownika)
{
    string haslo, haslo2;
    cout << "Podaj aktualne haslo: " << endl;
    cin >> haslo;
    for (int i=0; i<nowyUzytkownik.size(); i++)
    {
        if (nowyUzytkownik[i].idUzytkownika == idUzytkownika && nowyUzytkownik[i].haslo == haslo)
        {
            cout << "Podaj nowe haslo: " << endl;
            cin >> haslo2;
            nowyUzytkownik[i].haslo = haslo2;
            zapisNowegoHasla (nowyUzytkownik);
            return;
        }
    }
    cout << "Podano nieprawidlowe haslo" << endl;
    Sleep(1000);
}
void przejdzDoMenuPoZalogowaniu (int idUzytkownika, vector <Uzytkownik> &nowyUzytkownik) //pokombinuj jak zapetlic ta funkcje
{
    vector <Znajomy> nowyZnajomy;
    char wybor;
    int idWpisu = 1;
    wczytanieZnajomych (nowyZnajomy, idUzytkownika);
    while (1)
    {
        if (idWpisu == 1)
        {
            system("cls");
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj aresata" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "9. Wyloguj sie" << endl;
            cout << "Twoj wybor: ";
            cin >> wybor;

            if (wybor == '1')
            {
                dodajZnajomego (nowyZnajomy, idUzytkownika);
            }
            else if (wybor == '2')
            {
                szukajImie(nowyZnajomy);
            }
            else if (wybor == '3')
            {
                szukajNazwisko(nowyZnajomy);
            }
            else if (wybor == '4')
            {
                wszyscyZnajomi(nowyZnajomy);
            }
            else if (wybor == '5')
            {
                usuwanieZnajomego(nowyZnajomy, idUzytkownika);
            }
            else if (wybor == '6')
            {
                edycjaAdresata(nowyZnajomy, idUzytkownika);
            }
            else if (wybor == '7')
            {
                zmianaHasla(nowyUzytkownik, idUzytkownika);
            }
            else if (wybor == '9')
            {
                return;
            }
        }
    }
}
void rejestrowanie(vector <Uzytkownik> &nowyUzytkownik)
{
    Uzytkownik passyDoKonta;
    string login, haslo;
    int idUzytkownika;

    cout << "Podaj swoj login" << endl;
    cin >> login;

    for (int i=0; i<nowyUzytkownik.size(); i++)
    {
        while (nowyUzytkownik[i].login == login)
        {
            cout << "Juz istnieje taki login. Prosze podaj inny" << endl;
            cin >> login;
        }
    }
    cout << "Podaj swoje haslo" << endl;
    cin >> haslo;

    if (nowyUzytkownik.empty() == true)
    {
        idUzytkownika = 1;
        passyDoKonta.idUzytkownika = idUzytkownika;
    }
    else
    {
        passyDoKonta.idUzytkownika =  nowyUzytkownik.back().idUzytkownika +1;
        idUzytkownika = passyDoKonta.idUzytkownika;
    }

    passyDoKonta.login = login;
    passyDoKonta.haslo = haslo;
    nowyUzytkownik.push_back(passyDoKonta);

    fstream plik;
    plik.open("listaUzytkownikow.txt", ios::out | ios::app); // ios::app dodaje sie aby dopisywac dane do pliku

    plik << passyDoKonta.idUzytkownika << "|";
    plik << passyDoKonta.login << "|";
    plik << passyDoKonta.haslo << "|" << endl;

    plik.close();

    cout << "Uzytkownik zarejestrowany" << endl;
    Sleep(1000);
}
void logowanie (vector <Uzytkownik> &nowyUzytkownik)
{
    string login, haslo;
    cout << "Podaj swoj login" << endl;
    cin >> login;
    for (int i=0; i<nowyUzytkownik.size(); i++)
    {
        if (nowyUzytkownik[i].login == login)
        {
            cout << "Podaj swoje haslo" << endl;
            cin >> haslo;
            if (nowyUzytkownik[i].login == login && nowyUzytkownik[i].haslo == haslo)
            {
                int idUzytkownika = nowyUzytkownik[i].idUzytkownika;
                przejdzDoMenuPoZalogowaniu (idUzytkownika, nowyUzytkownik);
                return;
            }
            else
            {
                cout << "Podales nieprawidlowe haslo" << endl;
                Sleep(1000);
            }
        }
    }
}
void wczytanieUzytkownikow (vector <Uzytkownik> &nowyUzytkownik)
{
    fstream plik;
    plik.open ("listaUzytkownikow.txt", ios::in);
    int idUzytkownikow;
    if (plik.good() == false)
    {
        cout << "Nie znaleziono listy uzytkownikow" << endl;
        Sleep(1000);
    }
    else
    {
        string linia;
        int nr_lini = 1;
        Uzytkownik passyDoKonta;
        while (getline (plik, linia))
        {
            switch (nr_lini)
            {
            case 1:
                vector<string>slowaZLinijki(0);
                for (int i=0; i<linia.length(); i++)
                {
                    if (linia[i] == '|')
                        linia[i] = ' ';
                }
                string slowo;
                stringstream iss (linia);
                while(iss >> slowo)
                {
                    slowaZLinijki.push_back(slowo);
                }
                passyDoKonta.idUzytkownika = atoi (slowaZLinijki[0].c_str());
                passyDoKonta.login = slowaZLinijki[1];
                passyDoKonta.haslo = slowaZLinijki[2];
                slowaZLinijki.clear();
                break;
            }
            nowyUzytkownik.push_back(passyDoKonta);
        }
        plik.close();
    }
}
int main()
{
    vector <Uzytkownik> nowyUzytkownik;
    int idUzytkownika = 0;
    int idWpisu = 0;
    char wybor;
    wczytanieUzytkownikow (nowyUzytkownik);
    while (1)
    {
        if (idWpisu == 0)
        {
            system("cls");
            cout << "1. Logowanie" << endl;
            cout << "2. Rejestracja" << endl;
            cout << "9. Zamknij program" << endl;
            cout << "Twoj wybor: ";
            cin >> wybor;

            if (wybor == '1')
            {
                logowanie(nowyUzytkownik);

            }
            else if (wybor == '2')
            {
                rejestrowanie(nowyUzytkownik);
            }
            else if (wybor == '9')
            {
                exit (0);
            }
        }
    }
    return 0;
}
