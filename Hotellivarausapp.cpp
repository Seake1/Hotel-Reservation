#include<iostream>
#include<conio.h>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<dos.h>
#include <locale>
#include <clocale>
using namespace std;

class hotelli
{
    int room_no;
    char Sukunimi[30];
    char osoite[50];
    char puhelin_nmr[10];
    char saapuminen[10];
    int nights;

public:
    void etusivu();
    void add();
    void display();
    void rooms();
    void edit();
    int check(int);
    void modify(int);
    void delete_rec(int);
};

//Etusivu, jossa valinnat
void hotelli::etusivu()
{
    std::locale::global(std::locale(""));
    int choice{};
    while (choice != 5)
    {
        system("cls");
        cout << "\n\t\t\t\t\t\t*************************";
        cout << "\n\t\t\t\t\t\t  HOTELLI VARAUSSYSTEEMI ";
        cout << "\n\t\t\t\t\t\t      * ETUSIVU *";
        cout << "\n\t\t\t\t\t\t*************************";
        cout << "\n\n\n\t\t\t\t\t\t1.Varaa Huone";
        cout << "\n\t\t\t\t\t\t2.Asiakkaan tiedot";
        cout << "\n\t\t\t\t\t\t3.Varatut Huoneet";
        cout << "\n\t\t\t\t\t\t4.Muokkaa varauksia";
        cout << "\n\t\t\t\t\t\t5.Exit";
        cout << "\n\n\t\t\t\t\t\tSy�t� valintasi: ";
        cin >> choice;

        switch (choice)
        {
        case 1:	add();
            break;

        case 2: display();
            break;

        case 3: rooms();
            break;

        case 4:	edit();
            break;

        case 5: break;

        default:
        {
            cout << "\n\n\t\t\tV��r� valinta.!!!";
            cout << "\n\t\t\tPaina mit� tahansa n�pp�in�t jatkaaksesi....!!";
            _getch();
        }
        }
    }
}
//Etusivu loppuu

//1. Valinta eli funktio Huoneen varaukselle
void hotelli::add()
{
    std::locale::global(std::locale(""));

    system("cls");
    int r, flag;
    int hinta;
    ofstream fout("Record.dat", ios::app);

    cout << "\n Sy�t� asiakastiedot";
    cout << "\n ----------------------";
    cout << "\n\n Huoneiden numerot: ";
    cout << "\n Huoneita yhteens� - 50";
    cout << "\n Normaalit huoneet 1 - 30, hinta 150� y�lt�.";
    cout << "\n Luksushuone 31 - 45, hinta 200� y�lt�.";
    cout << "\n Sviitit 46 - 50, hinta 300� y�lt�.";
    // cout << "\n Mink� hintaisessa huoneessa tahtoisit y�py�? 150�, 200� vai 300�?" << endl;
    // cin >> hinta;
    cout << " Sy�t� huoneen numero, jossa tahtoisit y�py�: " << endl;
    cin >> r;
    flag = check(r);

    if (r < 31 && r > 0) {
        hinta = 150;
    }
    if (r < 46 && r > 30) {
        hinta = 200;
    }
    if (r < 51 && r > 45) {
        hinta = 300;
    }


    if (flag)
        cout << "\n Pahoittelut!!! Huone on t�ll� hetkell� varattu";

    else
    {
        room_no = r;
        cout << " Sy�t� sukunimesi: ";
        cin >> Sukunimi;
        cout << " Kotiosoite ilman v�limerkkej�: ";
        cin >> osoite;
        cout << " Puhelinnumero: ";
        cin >> puhelin_nmr;
        cout << " Milloin saavut (dd-mm-yyyy): ";
        cin >> saapuminen;
        cout << " Kuinka monta y�t� tahdot viipy�?:" << endl;
        cin >> nights;
        cout << "\n Huoneen varauksen summa tulee olemaan:" << hinta * nights << " Euroa" << endl;

        fout.write((char*)this, sizeof(hotelli));
        cout << "\n\n Huone on nyt varattu teille! Hyv�� p�iv�njatkoa. :)" << endl;
    }

    cout << "\n\n Paina mit� tahansa n�pp�int� palataksesi etusivulle.";
    _getch();
    fout.close();
}
//1. valinta eli varausosuus loppuu.

//2. valinta, eli Asiakkaan tiedot, jolla voi tarkistella tietyn huoneen asiakkaan tietoja
void hotelli::display()
{
    std::locale::global(std::locale(""));
    system("cls");

    ifstream fin("Record.dat", ios::in);
    int r, flag;

    cout << "\n Sy�t� huonenmumero kenen asiakkaan tietoja tahdot tarkastella " << endl;
    cin >> r;

    while (!fin.eof())
    {

        fin.read((char*)this, sizeof(hotelli));
        if (room_no == r)
        {
            system("cls");
            cout << "\n Cusromer Details";
            cout << "\n ----------------";
            cout << "\n\n Huone numero " << room_no;
            cout << "\n Sukunimi: " << Sukunimi;
            cout << "\n Osoite: " << osoite;
            cout << "\n Puhelin numero: " << puhelin_nmr;
            cout << "\n Saapumisp�iv�m��r�: " << saapuminen;
            cout << "\n �iden lukum��r�: " << nights;
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        cout << "\n Huonetta jota etsit ei ole tai se on t�ll� hetkell� vapaana!!";
    cout << "\n\n Paina mit� tahansa nappia jatkaaksesi!!";
    _getch();
    fin.close();
}
//2. valinta eli asiakkaan tiedot loppuu.

//3. valinta, eli n�ytt�� kaikki varatut huoneet ja asiakkaiden tiedot huoneissa.
//listassa ei n�y ��kk�set ja p�iv�m��r�n j�lkeen ilmestyy ylim��r�inen merkki, v�lill� tekee jostain syyst� tuplana bookkauksen listaan -- ty�n alla......
void hotelli::rooms()
{
    std::locale::global(std::locale(""));
    system("cls");
    ifstream fin("Record.dat", ios::in);
    cout << "\n\t\t\t    Lista varatuista huoneista";
    cout << "\n\t\t\t    ----------------------";
    cout << "\n\n Huoneen no.\tSukunimi\t\tOsoite\t\tPuh-numero\t\tSaapumisp�iv�\t\t�iden m��r�:\n";

    while (!fin.eof())
    {
        fin.read((char*)this, sizeof(hotelli));
        cout << "\n\n " << room_no << "\t\t" << Sukunimi;
        cout << "\t\t" << osoite << "\t" << puhelin_nmr;
        cout << "\t\t" << saapuminen << "\t\t" << nights;
    }
    cout << "\n\n\n\n\t\t\tPaina mit� tahansa nappia jatkaaksesi!!";

    _getch();
    fin.close();
}
//3. valinta loppuu

//4. Valinta eli muokkaa varauksia vaihtoehto
void hotelli::edit()
{
    std::locale::global(std::locale(""));
    system("cls");

    int choice, r;
    cout << "\n Muokkaus menu";
    cout << "\n ---------";
    cout << "\n\n 1.Muokkaa asiakkaan tietoja";
    cout << "\n 2.Poista asiakas";
    cout << "\n Sy�t� valintasi: ";

    cin >> choice;
    system("cls");

    cout << "\n Sy�t� huoneen numero: ";
    cin >> r;

    switch (choice)
    {
    case 1:	modify(r);
        break;
    case 2:	delete_rec(r);
        break;
    default: cout << "\n V��r� valinta!!";
    }
    cout << "\n Paina mit� tahansa nappia jatkaaksesi!!";

    _getch();
}

int hotelli::check(int r)
{
    std::locale::global(std::locale(""));
    int flag = 0;
    ifstream fin("Record.dat", ios::in);
    while (!fin.eof())
    {
        fin.read((char*)this, sizeof(hotelli));
        if (room_no == r)
        {
            flag = 1;
            break;
        }
    }
    fin.close();
    return(flag);
}


//Funktio jolla muokataan asiakkaan tietoja
void hotelli::modify(int r)
{
    std::locale::global(std::locale(""));
    long pos, flag = 0;

    fstream file("Record.dat", ios::in | ios::out | ios::binary);

    while (!file.eof())
    {
        pos = file.tellg();
        file.read((char*)this, sizeof(hotelli));

        if (room_no == r)
        {
            cout << "\n Asiakkaan uudet tiedot:";
            cout << "\n -----------------";
            cout << "\n Sukunimi: ";
            cin >> Sukunimi;
            cout << " Osoite: ";
            cin >> osoite;
            cout << " Puhelin no: ";
            cin >> puhelin_nmr;
            cout << " Saapumisp�iv�: ";
            cin >> saapuminen;
            cout << "Y�vytt�v�t y�t: ";
            cin >> nights;
            file.seekg(pos);
            file.write((char*)this, sizeof(hotelli));
            cout << "\n Asiakastiedot on p�ivitetty!";
            flag = 1;
            break;
        }

    }
    if (flag == 0)
        cout << "\n Huonenumeroa ei ole tai se ei ole k�yt�ss�!!";
    file.close();
}
//Asiakastietojen muokkauksen loppuu


//Asiakkaan poistofunktio.
void hotelli::delete_rec(int r)
{
    std::locale::global(std::locale(""));
    int flag = 0;
    char ch;
    ifstream fin("Record.dat", ios::in);
    ofstream fout("temp.dat", ios::out);

    while (!fin.eof())
    {
        fin.read((char*)this, sizeof(hotelli));
        if (room_no == r)
        {
            cout << "\n Sukunimi: " << Sukunimi;
            cout << "\n Osoite: " << osoite;
            cout << "\n Puhelin numero: " << puhelin_nmr;
            cout << "\n\n Tahdotko poistaa asiakkaan tiedot(y/n): ";
            cin >> ch;

            if (ch == 'n')
                fout.write((char*)this, sizeof(hotelli));
            flag = 1;
        }
        else
            fout.write((char*)this, sizeof(hotelli));
    }
    fin.close();
    fout.close();

    if (flag == 0)
        cout << "\n Huonetta ei ole tai huone ei ole varattuna!!";

    else
    {
        remove("Record.dat");
        rename("temp.dat", "Record.dat");
    }
}
//Poistofunktio loppuu
//4. valinta loppuu

//Alkusivu/etusivu, jossa esitell��n mik� ty� on.
int main()
{
    std::locale::global(std::locale(""));
    hotelli h;

    system("cls");

    cout << "\n\n\n\t\t\t\t\t\t**********************************";
    cout << "\n\t\t\t\t\t\t** Hotellihuoneen varausohjelma **";
    cout << "\n\t\t\t\t\t\t**********************************";

    cout << "\n\n\n\n\n\n\t\t\t\t\t** C++ Harjoitusty� by Christian Eriksson **";

    cout << "\n\n\n\n\n\n\n\t\t\t\t\tPaina mit� tahansa n�pp�int� aloittaaksesi ohjelman! :)";

    _getch();

    h.etusivu();
    return 0;
}