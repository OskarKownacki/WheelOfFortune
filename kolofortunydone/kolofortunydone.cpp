// Kolory.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <conio.h>
#include <Windows.h> 
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <cassert>
#include <locale.h>

using namespace std;

struct Player {
    string name;
    int money = 0;
    int ballance = 0; //kasa z wygranych rund
    int vowels = 0; //ilość posiadanych samogłosek
};


struct Player players[3];

int turn = 0;

int wheelof[] = { -1, 0, 100, 200, 100, 200, 100, 200, 500, 500, 1000, 1000, 1500, 2000, 3000, 5000 };
// -1 bankrut
// 0 strata kolejki

int isVowel(char c)
{
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y' ||
        c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' || c == 'Y')
        return 1;
    else
        return 0;

}
int checkletter(char letter, string phrase, int mask[]) {
    int Lettercount = 0;
    for (int i = 0; i < phrase.length(); i++) {
        if (phrase[i] == letter) {
            mask[i] = 1;
            Lettercount++;
        }
    }
    return Lettercount;
}

void textPlayers()
{
    int i;
    cout << "\n";
    for (i = 0; i < 3; i++) {
        if (i == turn) {
            cout << "\033[1;30m";
        }
        cout << "gracz numer" << i << endl;
        cout << players[i].name << "\t" << players[i].money << "\t" << players[i].vowels << "\n" << endl;
        cout << "\033[0m";

    }
    cout << "\n";
}

void buyingVowels(string phrase, Player& player) {
    int Vowelcount = 0;
    for (char c : phrase) {
        if (isVowel(c)) {
            Vowelcount++;
        }
    }
    cout << "Ilość samogłosek w haśle: " << Vowelcount << endl;

    if (Vowelcount == 0) {
        cout << "Brak samogłosek do kupienia." << endl;
        return;
    }

    cout << "Cena jednej samogłoski: 500 zł." << endl;
    cout << "Posiadasz " << player.ballance << " zł." << endl;

    int howmuchtobuy;
    do {
        cout << "Ile samogłosek chcesz kupić? ";
        cin >> howmuchtobuy;
    } while (howmuchtobuy < 0 || howmuchtobuy > Vowelcount || 500 * howmuchtobuy > player.money);

    player.vowels += howmuchtobuy;
    player.ballance -= 500 * howmuchtobuy;
    cout << "Zakupiłeś " << howmuchtobuy << " samogłosek." << endl;
    cout << "Twoje saldo: " << player.money << " zł." << endl;
    cout << "Liczba posiadanych samogłosek: " << player.vowels << endl;

    // WYŚWIETLENIE KUPIONEJ SAMOGŁOSKI W KODZIE
    if (howmuchtobuy > 0) {
        cout << "Kupiłeś samogłoskę: ";
        for (char c : phrase) {
            if (isVowel(c) && howmuchtobuy > 0) {
                cout << c << " ";
                howmuchtobuy--;
            }
        }
        cout << endl;
    }
}

char LoadChoice()
{
    char choice;
    choice = LoadChar();

    while (choice != '1' && choice != '2' && choice != '3')
    {
        cout << endl << "Wybierz [1-2 lub 3]: ";
        cin >> choice;
    }

    return choice;

}

char LoadChar()
{
    string letter;
    cin >> letter;

    while (letter.length() != 1)
    {
        cout << endl << "Podaj JEDNĄ literę: ";
        cin >> letter;
    }

    for (auto& c : letter)  // & zapamietuje modyfikacje w petli & - referencja
        c = toupper(c);

    return letter[0];

}

int main()
{
    int i;

    setlocale(LC_ALL, "pl_PL");

    string phrase; // = "wielka antarktyda";
    string WhichTry;
    char letter;
    int VowelPrice = 500;
    int n;
    int mask[100];
    int sum = 0;
    int right = 0;
    int areVowels = 0;
    int amount = 0;
    char choice;
    srand(time(NULL));
    string result;
    vector<string> phrases;
    int j;

    string name1;
    string name2;
    string name3;


    cout << "podaj imię gracza:" << endl;
    cin >> name1;
    cout << "podaj imię gracza:" << endl;
    cin >> name2;
    cout << "podaj imię gracza:" << endl;
    cin >> name3;




    ifstream strum;
    int kat = rand() % 5;
    if (kat == 0)
    {
        strum.open("Historia.txt");
        cout << "KATEGORIA: Historia";
    }

    if (kat == 1)
    {
        strum.open("Przyroda.txt");
        cout << "KATEGORIA: Przyroda";
    }

    if (kat == 2)
    {
        strum.open("Miasta.txt");
        cout << "KATEGORIA: Miasta";
    }

    if (kat == 3)
    {
        strum.open("Informatyka.txt");
        cout << "KATEGORIA: Informatyka";
    }

    if (kat == 4)
    {
        strum.open("gry.txt");
        cout << "KATEGORIA: GRY";
    }

    cout << endl << endl;

    while (!strum.eof())
    {
        string s;
        //strum >> s;
        getline(strum, s);
        //cout << s << endl;
        phrases.push_back(s);

    }

    strum.close();




    // for (i = 0; i < phrases.size(); i++)
     //    cout << phrases[i] << endl;



    /*for (string item : phrases)
        cout << item << endl;*/



    cout << endl << endl;

    assert(phrases.size() > 0);
    j = rand() % phrases.size(); // losujemy j-te haslo z przedzialu 0 ... size - 1
    //cout << phrases[j];

    phrase = phrases[j];
    n = phrase.size();

    players[0].name = name1;
    players[1].name = name2;
    players[2].name = name3;


    for (i = 0; i < n; i++)
    {
        if (phrase[i] == ' ')
            mask[i] = 0;
        else
            mask[i] = 1;
    }




    do
    {
        // cout << "\033[2J";

        cout << "\033[47m" << "\033[31m";
        for (i = 0; i < n; i++)
        {

            if (mask[i] == 1)
                cout << ".";
            else
                cout << phrase[i];
        }

        cout << "\033[0m";
        cout << endl;


        areVowels = 0;
        amount = 0;

        for (i = 0; i < n; i++)
            if ((!isVowel(phrase[i])) && (mask[i]))
            {
                areVowels = 1;
                break;
            }

        if (areVowels)
            cout << " -- Spolgloski sa --" << endl;


        //cout << gracze[kolejka].name << " " << endl;
        cout << "\033[1;36m";
        cout << endl << "Lista wyników graczy:";
        cout << endl << "Imię   Kasa   Samogłoski";
        textPlayers();

        cout << "Wybierz opcję:" << endl;
        cout << "1. Zgadnij hasło" << endl;
        cout << "2. Odkryj literę" << endl;
        cout << "3. Kup samogłoskę (" << VowelPrice << ")" << endl;

        // TODO tylko 1 i 2, nie mozna wprowadzac liter



        char choice = LoadChoice();

        if (choice == '1')
        {
            cout << "Podaj phrase" << endl;
            getline(cin >> ws, WhichTry);  // wczytanie z klawiatury string z uwzgl. whitespa
            for (auto& c : WhichTry)  // & zapamietuje modyfikacje w petli & - referencja
                c = toupper(c);
            if (phrase == WhichTry) {
                cout << endl << " !!!!!!!!!! =======   WYGRANA ========== !!!!!!!!!!!!!" << endl;
                players[turn].ballance += players[turn].money;
                break;
            }
            else
            {
                turn = (turn + 1) % 3;
                sum = 1;
                cout << endl << " !!!!!!!!!! =======   ZLE ========== !!!!!!!!!!!!!" << endl;
                cout << endl << "=================================================" << endl;
                continue;


            }



        }
        else if (choice == '2') {
            result = "";
            i = rand() % 15;
            if (wheelof[i] == 0)
                result = "Strata kolejki";
            if (wheelof[i] == -1)
                result = "Bankrut";
            if (result != "")
                cout << "\033[1;31m" << result << "\033[0m" << endl;
            else
            {
                cout << "\033[1;34m" << wheelof[i] << "\033[0m" << endl;
                amount = wheelof[i];
            }

            // Strata kolejki i bankrut
            if ((wheelof[i] == 0) || (wheelof[i] == -1))
            {
                if (wheelof[i] == -1) // bankrut
                    players[turn].money = 0;

                turn = (turn + 1) % 3;
                sum = 1;
                cout << endl << "=================================================" << endl;

                // TODO
                // sleep for
                // kupowanie samoglosek

                continue;

            }


            cout << players[turn].name << ": Podaj litere" << endl;



            // Odczytanie litery od gracza
            letter = LoadChar();

            // Sprawdzenie ile razy letter występuje w haśle i zaktualizowanie maski
            int ilosc = checkletter(letter, phrase, mask);

            // Wyświetlenie informacji o ilości znalezionych liter
            /*if (ilosc == 0) {
                cout << "Nie znaleziono litery \"" << letter << "\"." << endl;
            }
            else {
                cout << "Znaleziono " << ilosc << " liter \"" << letter << "\"." << endl;
            }*/

            // Wyświetlenie hasła z zaktualizowaną maską
            /*cout << "Hasło: ";
            for (int i = 0; i < phrase.length(); i++) {
                if (mask[i] == 1) {
                    cout << phrase[i] << " ";
                }
                else {
                    cout << "_ ";
                }
            }
            cout << endl;*/


            right = 0;

            if (isVowel(letter))
                cout << "samogloska";
            else
                cout << "spolgloska";
            cout << endl;

            for (i = 0; i < n; i++)
            {
                if ((phrase[i] == letter) && (mask[i] == 1)) {
                    mask[i] = 0;
                    right++;
                }
            }

            if (right)
            {
                cout << "OK";
                players[turn].money += amount * right;

                cout << endl << players[turn].name << "\033[1;32m " << players[turn].money << "\033[0m";


            }
            else {
                cout << "Zle!";
                // strata kolejki
                turn = (turn + 1) % 3;
                cout << endl << "=================================================" << endl;
                sum = 1;
                continue;
            }
        }
        else if (choice == '3') {
            buyingVowels(phrase, players[turn]);
        }
        else {
            cout << "Nieznany wybór. Spróbuj jeszcze raz." << endl;
        }


        cout << endl;



        sum = 0;

        for (i = 0; i < n; i++)
        {
            sum += mask[i];
        }



    } while (sum);
    cout << "BRAWO!";
    cout << "Tabela Wyników" << endl;
    cout << "Imię   Kasa   Samogłoski" << endl;
    cout << "wynik gracza nr 1:" << endl;
    cout << players[0].name << "\033[1;32m " << "    " << players[0].money << "\033[0m" << "    " << players[0].vowels << endl;
    cout << "wynik gracza nr 2:" << endl;
    cout << players[1].name << "\033[1;32m " << "    " << players[1].money << "\033[0m" << "    " << players[1].vowels << endl;
    cout << "wynik gracza nr 3:" << endl;
    cout << players[2].name << "\033[1;32m " << "    " << players[2].money << "\033[0m" << "    " << players[2].vowels << endl;
    exit(0);

    textPlayers();
    Beep(523, 500);
}