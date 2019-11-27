#include <iostream>
#include <windows.h> // opoznianie programu funkcja Sleep()
#include <string>
#include <conio.h> //getch()
#include <fstream> // zapisywanie danych do pliku tekstowego
#include <sstream> // zamiana int na string
#include <vector>

using namespace std;

struct Znajomy
{
    int id;
    string imie, nazwisko, nrTelefonu, adres, email;
};
string zamianaIntNaString (int id)
{
    ostringstream ss;
    ss << id;
    string zmienionyIntNaString = ss.str();
    return zmienionyIntNaString;
}
int dodajZnajomego (vector <Znajomy> &nowyZnajomy, int wartosc)
{
    Znajomy dane;

    string imie, nazwisko, nrTelefonu, adres, email;
    cout << "Podaj imie znajomego: " << endl;
    cin >> dane.imie;
    cout << "Podaj nazwisko znajomego: " << endl;
    cin >> dane.nazwisko;
    cout << "Podaj numer telefonu komorkowego do znajomego skladajacego sie z 9 cyfr " << endl;
    cin.sync();
    getline (cin, dane.nrTelefonu);
    cout << "Podaj adres email znajomego" << endl;
    cin >> dane.email;
    cout << "Podaj adres zamieszkania znajomego" << endl;
    cin.sync();
    getline(cin, dane.adres);

    if (wartosc == 1)
    {
        for (int i=0; i<nowyZnajomy.size(); i++)
        {
         dane.id =  nowyZnajomy[i].id +1;
        }
    }
    else
    {
        dane.id = 1;
        wartosc = 1;
    }
    zamianaIntNaString (dane.id);

    nowyZnajomy.push_back(dane);

    fstream plik;
    plik.open("lista.txt", ios::out | ios::app); // ios::app dodaje sie aby dopisywac dane do pliku

    plik << dane.id << "|";
    plik << dane.imie << "|";
    plik << dane.nazwisko << "|";
    plik << dane.nrTelefonu << "|";
    plik << dane.email << "|";
    plik << dane.adres << "|" << endl;

    plik.close();

    cout << "Znajomy zarejestrowany" << endl;
    Sleep(1000);
    return wartosc;
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
void wszyscyZnajomi (vector <Znajomy> nowyZnajomy)
{
    Znajomy dane;
    for (int i=0; i<nowyZnajomy.size(); i++)
    {
        cout << nowyZnajomy[i].imie << " "<<nowyZnajomy[i].nazwisko << endl;
        cout << "telefon: " << nowyZnajomy[i].nrTelefonu << ", adres:" << nowyZnajomy[i].email << ", adres: " << nowyZnajomy[i].adres << endl;
    }
    getch();
}
int wczytanieZnajomych (vector <Znajomy> &nowyZnajomy)
{
    fstream plik;
    plik.open ("lista.txt", ios::in);
    int wartosc;
    if (plik.good() == false)
    {
        cout << "Nie znaleziono listy znajomych" << endl;
        Sleep(1000);
        wartosc = 0;
        return wartosc;
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
                obiekt.id = atoi (slowaZLinijki[0].c_str());
                obiekt.imie = slowaZLinijki[1];
                obiekt.nazwisko = slowaZLinijki[2];
                obiekt.nrTelefonu = slowaZLinijki[3];
                obiekt.email = slowaZLinijki[4];
                obiekt.adres = slowaZLinijki[5];
                slowaZLinijki.clear();
                break;
            }
            nowyZnajomy.push_back(obiekt);
        }
        plik.close();
        wartosc = 1;
        return wartosc;
    }
}
void zapisNowychDanychDoPliku (vector <Znajomy> &nowyZnajomy)
{
    string id;
    fstream plik;
    plik.open("lista.txt", ios::out);
    for (int i=0; i<nowyZnajomy.size(); i++)
    {
        plik << nowyZnajomy[i].id << "|";
        plik << nowyZnajomy[i].imie << "|";
        plik << nowyZnajomy[i].nazwisko << "|";
        plik << nowyZnajomy[i].nrTelefonu << "|";
        plik << nowyZnajomy[i].email << "|";
        plik << nowyZnajomy[i].adres << "|" << endl;

    }
    plik.close();
}
void usuwanieZnajomego(vector <Znajomy> &nowyZnajomy)
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
                zapisNowychDanychDoPliku (nowyZnajomy);
                cout << "Kontakt usunieto" << endl;
            }
        }
        Sleep(1000);
    }
}
void edycjaAdresata(vector <Znajomy> &nowyZnajomy)
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
                ;
            }
        }
    }
    zapisNowychDanychDoPliku (nowyZnajomy);
}
int main()
{
    vector <Znajomy> nowyZnajomy;
    Znajomy dane;
    int idWpisu = 0;
    int wartosc;
    wartosc = wczytanieZnajomych (nowyZnajomy);
    char wybor;
    while (1)
    {
        if (idWpisu == 0)
        {

            system("cls");
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj aresata" << endl;
            cout << "9. Zakoncz program" << endl;
            cout << "Twoj wybor: ";
            cin >> wybor;

            if (wybor == '1')
            {
                wartosc = dodajZnajomego (nowyZnajomy, wartosc);
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
                usuwanieZnajomego(nowyZnajomy);
            }
            else if (wybor == '6')
            {
                edycjaAdresata(nowyZnajomy);
            }
            else if (wybor == '9')
            {
                exit (0);
            }
        }
    }
    return 0;
}
