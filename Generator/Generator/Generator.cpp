#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <cstdlib>
#include <stdlib.h>
#include <algorithm>
#include <stdio.h>
#include <sstream>
#include <windows.h>
#include <vector>
#include <locale.h>

using namespace std;

int czy_tutorial();
void tutorial();
void kod(int ile, string* tablica_kody);
void rejestracje(int ile, string* tab, string file);
int fsize(string file);
void ffill(string file, string* tab_imiona);
int queryGenerate(int ile, int wielkosc_tablicy, string tab_zapytania[], string tabela, int wybor, string pola, string tablica_pola[], string* tablica_wartosci);

int main()
{
    /************************ ZMIENNE ************************/
    int wybor; //wybor zapytania
    int ile; //ilosc rekordow
    int wielkosc_tablicy{}; //wielkosc wektora

    string* tablica_pola{}; //tablica z polami w zapytaniu
    string* tablica_wartosci{}; //tablica z wartosciami do zapytania

    string zapytanie; //zmienna do ktorej zapisywane jest cale zapytanie
    string tabela; //wybor tabeli przez uzytkownika
    const static string insert = "INSERT INTO "; //zapytanie
    const static string update = "UPDATE "; //zapytanie
    string tab_zapytania[2] = { insert, update }; //tablica zapytan
    string odpowiedz; //pole podawane przez uzytkownika
    string pola = "";  //pole w klauzuli
    string wartosci_pola = ""; //wartosci w klauzuli values

    vector <string > wektor; //wektor pomocniczy

    srand(time(NULL));

    /************************ ZMIENNE ************************/
    /************************ KONSOLA ************************/

    int czyTutorial = czy_tutorial();
    if (czyTutorial < 1)
    {
        tutorial();
    }
    system("cls");

    cout << " ------------------------------" << endl;
    cout << "|" << "      1       " << "|" << "       2       " << "|" << endl;
    cout << " ------------------------------" << endl;
    cout << "|" << " " << tab_zapytania[0] << " " << "|" << "    " << tab_zapytania[1] << "    " << "|" << endl;
    cout << " ------------------------------" << endl;
    cout << "Wybierz klauzule ktora chcesz wygenerowac: " << endl;
    cin >> wybor;
    wybor = wybor - 1;
    system("cls");

    cout << "Na jakiej tabeli chcesz pracowac?: " << endl;
    cin >> tabela;
    system("cls");

    //dodawanie pol do zapytania (tabela(..., ...,))
    if (wybor == 0)
    {
        do
        {
            cout << tab_zapytania[wybor] + tabela + "(" + pola + ")" + " VALUES(); " << endl;
            cout << "Dla jakich pol generujesz dane?: " << endl;
            cout << "Prosze wpisac 'koniec' kiedy wszystkie potrzebne pola zostana wpisane." << endl;
            cin >> odpowiedz;

            system("cls");
            if (odpowiedz != "koniec")
            {
                wektor.push_back(odpowiedz);
                pola = pola + odpowiedz + ", ";
            }
        } while (odpowiedz != "koniec");
        pola = pola.substr(0, pola.size() - 2);
        //dodawanie pol do zapytania (tabela(..., ...,))

        wielkosc_tablicy = wektor.size();
        tablica_pola = new string[wielkosc_tablicy];

        //przepisywanie pol z wektora do tablicy
        for (int i = 0; i < wektor.size(); i++)
        {
            tablica_pola[i] = wektor[i];
        }
        //przepisywanie pol z wektora do tablicy
        wektor.erase(wektor.begin(), wektor.end());

        //dodawanie wartosci do zapytania VALUES(..., ...,)
        int counter = 0;
        for (int i = 0; i < wielkosc_tablicy; i++)
        {
            cout << tab_zapytania[wybor] + tabela + "(" + pola + ")" + " VALUES" << "(" << wartosci_pola << ");" << endl;
            cout << "Jakie dane wygenerowac dla pola " << tablica_pola[counter] << "?:" << endl;
            cout << "Dostepne dane: " << endl;
            cout << "1. id" << endl;
            cout << "2. imie" << endl;
            cout << "3. nazwisko" << endl;
            cout << "4. miasto" << endl;
            cout << "5. nr_rejestracyjny" << endl;
            cout << "6. kod" << endl;

            cin >> odpowiedz;
            system("cls");
            if (odpowiedz != "koniec")
            {
                if (odpowiedz == "1")
                {
                    odpowiedz = "id";
                }

                if (odpowiedz == "2")
                {
                    odpowiedz = "imie";
                }

                if (odpowiedz == "3")
                {
                    odpowiedz = "nazwisko";
                }

                if (odpowiedz == "4")
                {
                    odpowiedz = "miasto";
                }

                if (odpowiedz == "5")
                {
                    odpowiedz = "nr_rejestracyjny";
                }

                if (odpowiedz == "6")
                {
                    odpowiedz = "kod";
                }

                wektor.push_back(odpowiedz);
                wartosci_pola = wartosci_pola + odpowiedz + ", ";
            }
            counter++;
        }
        wartosci_pola = wartosci_pola.substr(0, wartosci_pola.size() - 2);
        //dodawanie wartosci do zapytania (VALUES(..., ...,))

        tablica_wartosci = new string[wielkosc_tablicy];

        //przepisywanie wartosci z wektora do tablicy
        for (int i = 0; i < wielkosc_tablicy; i++)
        {
            tablica_wartosci[i] = wektor[i];
        }
        //przepisywanie wartosci z wektora do tablicy
        wektor.erase(wektor.begin(), wektor.end());
    }
    else if (wybor == 1)
    {
        int pola_counter = 0;
        int wartosci_counter = 0;

        do
        {
            cout << tab_zapytania[wybor] + tabela + " SET " + pola << endl;
            cout << "Prosze wpisac potrzebne wartosci: " << endl;
            cout << "Prosze wpisac 'koniec' kiedy wszystkie potrzebne pola zostana wpisane." << endl;
            cout << "Dostepne dane: " << endl;
            cout << "1. id" << endl;
            cout << "2. imie" << endl;
            cout << "3. nazwisko" << endl;
            cout << "4. miasto" << endl;
            cout << "5. nr_rejestracyjny" << endl;
            cout << "6. kod" << endl;

            cin >> odpowiedz;
            system("cls");
            if (odpowiedz != "koniec")
            {
                if (odpowiedz == "1")
                {
                    odpowiedz = "id";
                }

                if (odpowiedz == "2")
                {
                    odpowiedz = "imie";
                }

                if (odpowiedz == "3")
                {
                    odpowiedz = "nazwisko";
                }

                if (odpowiedz == "4")
                {
                    odpowiedz = "miasto";
                }

                if (odpowiedz == "5")
                {
                    odpowiedz = "nr_rejestracyjny";
                }

                if (odpowiedz == "6")
                {
                    odpowiedz = "kod";
                }
            }

            system("cls");
            if (odpowiedz != "koniec")
            {
                wektor.push_back(odpowiedz);
                if (pola_counter % 2 == 0)
                {
                    pola = pola + odpowiedz + " = ";
                }
                else
                {
                    pola = pola + odpowiedz + ", ";
                }
                pola_counter++;
            }
        } while (odpowiedz != "koniec");
        pola = pola.substr(0, pola.size() - 2);
        //dodawanie pol do zapytania (tabela(..., ...,))

        pola_counter = 0;
        wartosci_counter = 0;

        wielkosc_tablicy = wektor.size() / 2;
        tablica_pola = new string[wielkosc_tablicy];
        tablica_wartosci = new string[wielkosc_tablicy];

        //przepisywanie pol z wektora do tablicy
        for (int i = 0; i < wektor.size(); i++)
        {
            if (i % 2 == 0)
            {
                tablica_pola[pola_counter] = wektor[i];
                pola_counter++;
            }
            else
            {
                tablica_wartosci[wartosci_counter] = wektor[i];
                wartosci_counter++;
            }
        }
        //przepisywanie wartosci z wektora do tablicy
        wektor.erase(wektor.begin(), wektor.end());
    }
    cout << "Ile chcesz wygenerowac rekordow?: " << endl;
    cin >> ile;
    system("cls");

    /************************ KONSOLA ************************/
    //generowanie zapytan
    int queryGenerateReturn = queryGenerate(ile, wielkosc_tablicy, tab_zapytania, tabela, wybor, pola, tablica_pola, tablica_wartosci);
    cout << "Wygenerowano " << queryGenerateReturn << " zapytan." << endl;
    return 0;
}

int czy_tutorial()
{
    ifstream plik_input;
    string linia;
    int counter = 0;
    plik_input.open("data.txt");
    while (getline(plik_input, linia))
    {
        counter++;
    }
    plik_input.close();

    return counter;
}

void tutorial()
{
    ofstream data;
    int ile = 1;
    int wielkosc_tablicy = 3;
    string* tablica_kody;
    tablica_kody = new string[1];
    tablica_kody[0] = "A102";
    string* tablica_wartosci;
    tablica_wartosci = new string[3];
    tablica_wartosci[0] = "kod";
    tablica_wartosci[1] = "imie";
    tablica_wartosci[2] = "nazwisko";
    string* tab_imiona;
    tab_imiona = new string[1];
    tab_imiona[0] = "Stefan";
    string* tab_nazwiska;
    tab_nazwiska = new string[1];
    tab_nazwiska[0] = "Kolanko";
    string tab_zapytania[1];
    tab_zapytania[0] = "INSERT INTO ";
    string tabela = "Przyklad";
    int wybor = 0;
    string pola = "";
    string* tablica_pola;
    tablica_pola = new string[3];
    tablica_pola[0] = "kod_uzytkownika";
    tablica_pola[1] = "imie_uzytkownika";
    tablica_pola[2] = "nazwisko_uzytkownika";

    char pom;

    cout << "Witaj w generatorze!" << endl;
    Sleep(3000);
    system("cls");
    cout << "W tym generatorze masz okazje wygenerowac zapytania do swojej bazy danych." << endl;
    Sleep(5000);
    system("cls");
    cout << "Jak to dziala? To proste! pierwsze podajemy typ zapytania ktory chcemy wygenerowac: " << endl;
    cout << " ------------------------------" << endl;
    cout << "|" << "      1       " << "|" << "       2       " << "|" << endl;
    cout << " ------------------------------" << endl;
    cout << "|" << " " << "INSERT INTO " << " " << "|" << "    " << "UPDATE " << "    " << "|" << endl;
    cout << " ------------------------------" << endl;
    Sleep(2000);
    cout << "Przykladowom, wybieramy 1, czyli INSERT INTO." << endl;
    Sleep(4000);
    system("cls");
    cout << "Teraz wpisujemy nazwe tabeli do ktorej chcemy dodac rekordy ktore zaraz wygenerujemy." << endl;
    Sleep(4000);
    cout << "Pozwole sobie ja nazwac 'Przyklad'." << endl;
    Sleep(4000);
    system("cls");
    cout << "W tym momencie nasze zapytanie juz zaczyna byc generowane. Wyglada ono nastepujaco:" << endl;
    Sleep(4000);
    cout << tab_zapytania[wybor] + tabela + "(" + pola + ")" + " VALUES();" << endl;
    Sleep(4000);
    cout << "Czegos tu brakuje, prawda? Potrzebujemy dodac pola w tabeli Przyklad dla ktorych chcemy generowac dane." << endl;
    Sleep(4000);
    cout << "Mysle ze mozemy uzupelnic pola kod_uzytkownika, imie_uzytkownika, nazwisko_uzytkownika." << endl;
    Sleep(4000);
    system("cls");
    pola = "kod_uzytkownika, imie_uzytkownika, nazwisko_uzytkownika";
    cout << tab_zapytania[wybor] + tabela + "(" + pola + ")" + " VALUES();" << endl;
    Sleep(4000);
    cout << "Juz troche lepiej, teraz uzupelnijmy te pola takimi wartosciami jakie chcemy." << endl;
    Sleep(4000);
    cout << "W tym przypadku beda to: kod, imie, nazwisko." << endl;
    Sleep(4000);
    system("cls");
    cout << "Ostatnim krokiem jest podanie ile chcemy wygenerowac rekordow." << endl;
    Sleep(4000);
    system("cls");
    cout << "Ja wygeneruje jeden, jednak Ty mozesz wygenerowac ich ile tylko chcesz." << endl;
    Sleep(4000);
    system("cls");
    queryGenerate(ile, wielkosc_tablicy, tab_zapytania, tabela, wybor, pola, tablica_pola, tablica_wartosci);
    Sleep(4000);
    cout << "I gotowe! Nasze zapytanie zostalo wypisane i zapisane do pliku." << endl;
    Sleep(4000);
    system("cls");
    cout << "Milego uzytkowania!" << endl;
    Sleep(4000);
    system("cls");
    cout << "Czy chcesz zeby ten poradnik pokazal sie nastepnym razem?" << endl;
    cout << "Y/N " << endl;
    cin >> pom;

    if (pom == 'N' || pom == 'n')
    {
        data.open("data.txt");
        data << 1 << endl;
        data.close();
    }
}

void kod(int ile, string* tablica_kody)
{
    char znak; //litera kodu
    int liczba; //ciag cyfr dolaczanych do znaku
    string kod; //pelen kod produktu

    int counter = 0; //ilosc powtorzonych kodow

    for (int i = 0; i < ile;)
    {

        liczba = rand() % 4 + 1;
        znak = 'a' + rand() % 4;

        ostringstream ss;
        ss << liczba;
        string str = ss.str();

        kod = str + znak;

        for (int j = 0; j <= i; j++)
        {
            if (tablica_kody[j] == kod)
            {
                counter++;
            }
        }
        if (counter == 0)
        {
            tablica_kody[i] = kod;
            i++;
        }
        counter = 0;
    }
}

void rejestracje(int ile, string* tab, string file)
{
    ifstream plik_input;
    string linia;
    string vfinal;
    int number;
    int counter = 0;
    int pom = 0;
    int randomPrefix;
    string* prefix;
    prefix = new string[ile];

    plik_input.open(file.c_str());
    while (getline(plik_input, linia))
    {
        prefix[counter] = linia;
        counter++;
        pom++;
    }
    counter = 0;
    while (counter < ile)
    {
        number = rand() % 9000 + 1000;

        ostringstream ss;
        ss << number;
        string str = ss.str();

        randomPrefix = rand() % pom;
        linia = prefix[randomPrefix];

        vfinal = linia + str;
        tab[counter] = vfinal;
        counter++;
    }


    plik_input.close();
}

int fsize(string file)
{
    ifstream plik_input;
    string linia;
    int counter = 0;

    plik_input.open(file.c_str());

    while (getline(plik_input, linia))
    {
        counter++;
    }

    plik_input.close();
    return counter;
}

void ffill(string file, string* tab)
{
    ifstream plik_input;
    string linia;
    int counter = 0;
    plik_input.open(file.c_str());
    while (getline(plik_input, linia))
    {
        tab[counter] = linia;
        counter++;
    }

    plik_input.close();
}

int queryGenerate(int ile, int wielkosc_tablicy, string tab_zapytania[], string tabela, int wybor, string pola, string tablica_pola[], string* tablica_wartosci)
{
    ofstream zapytania;
    string value = "";
    string zapytanie;
    string file;

    int size;
    int vnamesSize = 1;
    int vsurnamesSize = 1;
    int vcitiesSize = 1;
    int counter = 0;

    string* tablica_kody = {}; //tablica pomocnicza, do przechowywania kodow
    string* tab_imiona = {}; //tablica z imionami
    string* tab_nazwiska = {}; //tablica z nazwiskami
    string* tab_miasta = {}; //tablica z namiastami
    string* tab_rejestracje = {}; //tablica z rejestracjami pojazdow

    string tablica_z_wyborem_danych[6];
    tablica_z_wyborem_danych[0] = "id";
    tablica_z_wyborem_danych[1] = "imie";
    tablica_z_wyborem_danych[2] = "nazwisko";
    tablica_z_wyborem_danych[3] = "miasto";
    tablica_z_wyborem_danych[4] = "nr_rejestracyjny";
    tablica_z_wyborem_danych[5] = "kod";

    for (int i = 0; i < wielkosc_tablicy; i++)
    {
        if (tablica_wartosci[i] == tablica_z_wyborem_danych[1])
        {
            file = "imiona.txt";
            size = fsize(file);
            tab_imiona = new string[size];
            vnamesSize = fsize(file);
            ffill(file, tab_imiona);
        }
        else if (tablica_wartosci[i] == tablica_z_wyborem_danych[2])
        {
            file = "nazwiska.txt";
            size = fsize(file);
            tab_nazwiska = new string[size];
            vsurnamesSize = fsize(file);
            ffill(file, tab_nazwiska);
        }
        else if (tablica_wartosci[i] == tablica_z_wyborem_danych[3])
        {
            file = "miasta.txt";
            size = fsize(file);
            tab_miasta = new string[size];
            vcitiesSize = fsize(file);
            ffill(file, tab_miasta);
        }
        else if (tablica_wartosci[i] == tablica_z_wyborem_danych[4])
        {
            int ile_pom;
            file = "rejestracje.txt";
            size = fsize(file);

            if (ile < size)
            {
                ile_pom = size;
            }
            else
            {
                ile_pom = ile;
            }
            tab_rejestracje = new string[ile_pom];
            ffill(file, tab_rejestracje);
            rejestracje(ile_pom, tab_rejestracje, file);
        }
        else if (tablica_wartosci[i] == tablica_z_wyborem_danych[5])
        {
            tablica_kody = new string[ile];
            kod(ile, tablica_kody);
        }
    }
    //generowanie zapytan w funkcji
    zapytania.open("zapytania.txt");
    for (int i = 0; i < ile; i++)
    {
        int imiona_pom = rand() % vnamesSize;
        int nazwiska_pom = rand() % vsurnamesSize;
        int miasta_pom = rand() % vcitiesSize;
        for (int z = 0; z < wielkosc_tablicy; z++)
        {
            if (wybor == 1)
            {
                value = value + tablica_pola[z];
            }

            if (tablica_wartosci[z] == tablica_z_wyborem_danych[0])
            {
                ostringstream ss;
                ss << (i + 1);
                string str = ss.str();
                if (wybor == 1)
                {

                    value = value + " = " + "'" + str + "'" + ", ";
                }
                else
                {
                    value = value + "'" + str + "'" + ", ";
                }
            }

            else if (tablica_wartosci[z] == tablica_z_wyborem_danych[1])
            {
                if (wybor == 1)
                {
                    value = value + " = " + "'" + tab_imiona[imiona_pom] + "'" + ", ";
                }
                else
                {
                    value = value + "'" + tab_imiona[imiona_pom] + "'" + ", ";
                }
            }

            else if (tablica_wartosci[z] == tablica_z_wyborem_danych[2])
            {
                if (wybor == 1)
                {
                    value = value + " = " + "'" + tab_nazwiska[nazwiska_pom] + "'" + ", ";
                }
                else
                {
                    value = value + "'" + tab_nazwiska[nazwiska_pom] + "'" + ", ";
                }
            }

            else if (tablica_wartosci[z] == tablica_z_wyborem_danych[3])
            {
                if (wybor == 1)
                {
                    value = value + " = " + "'" + tab_miasta[miasta_pom] + "'" + ", ";
                }
                else
                {
                    value = value + "'" + tab_miasta[miasta_pom] + "'" + ", ";
                }
            }
            else if (tablica_wartosci[z] == tablica_z_wyborem_danych[4])
            {
                if (wybor == 1)
                {
                    value = value + " = " + "'" + tab_rejestracje[i] + "'" + ", ";
                }
                else
                {
                    value = value + "'" + tab_rejestracje[i] + "'" + ", ";
                }
            }
            else if (tablica_wartosci[z] == tablica_z_wyborem_danych[5])
            {
                if (wybor == 1)
                {
                    value = value + " = " + "'" + tablica_kody[i] + "'" + ", ";
                }
                else
                {
                    value = value + "'" + tablica_kody[i] + "'" + ", ";
                }
            }
        }
        //koncowy wypis i zapius do pliku
        value = value.substr(0, value.size() - 2);
        if (wybor == 1)
        {
            ostringstream ss;
            ss << (i + 1);
            string str = ss.str();
            zapytanie = tab_zapytania[wybor] + tabela + " SET " + value + " WHERE id = " + str + ";";
        }
        else
        {
            zapytanie = tab_zapytania[wybor] + tabela + "(" + pola + ")" + " VALUES" + "(" + value + ");";
        }
        /* cout << zapytanie <<endl; */
        zapytania << zapytanie << endl;
        value = "";
        counter++;
    }
    zapytania.close();
    return counter;
}
