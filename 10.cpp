#include <iostream>
#include <string.h>
#include <cstdlib>
#include <exception>
using namespace std;

class NegativnaVrednost
{
    char text[300];
public:
    NegativnaVrednost(char *text)
    {
        strcpy(this->text,text);
    }
    void print()
    {
        cout<<text<<endl;
    }
};

class Oglas
{
private:
    char naslov[51];
    char kategorija[31];
    char opis[101];
    float cena;

public:
    Oglas() {}
    Oglas(char *naslov, char *kategorija, char *opis, float cena)
    {
        strcpy(this->naslov, naslov);
        strcpy(this->kategorija, kategorija);
        strcpy(this->opis, opis);
        this->cena = cena;
    }
    bool operator>(Oglas &o)
    {
        return (this->cena > o.cena);
    }
    friend ostream &operator<<(ostream &os, Oglas &o)
    {
        os << o.naslov << endl;
        os << o.opis << endl;
        os << o.cena << " evra" << endl;
        return os;
    }
    float getCena()
    {
        return cena;
    }
    char *getNaslov()
    {
        return naslov;
    }
    char *getOpis()
    {
        return opis;
    }
    char *getKategorija()
    {
        return kategorija;
    }
};
class Oglasnik
{
private:
    char ime[21];
    Oglas *oglasi;
    int n;

public:
    Oglasnik()
    {
    }
    Oglasnik(char *ime)
    {
        strcpy(this->ime, ime);
    }
    Oglasnik(char *ime, Oglas *oglasi, int n)
    {
        this->n = n;
        strcpy(this->ime, ime);
        this->oglasi = new Oglas[n];
        for (int i = 0; i < n; i++)
        {
            this->oglasi[i] = oglasi[i];
        }
    }
    void operator+=(Oglas &o)
    {

            if (o.getCena() < 0)
            {
            throw NegativnaVrednost("Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!");
            }

            Oglas *temp;
            temp = new Oglas[n + 1];
            for (int i = 0; i < n; i++)
            {
                temp[i] = oglasi[i];
            }
            temp[n] = o;
            delete[] oglasi;
            oglasi = new Oglas[n + 1];
            for (int i = 0; i < n + 1; i++)
            {
                oglasi[i] = temp[i];
            }
            delete[] temp;
            n++;
        }
        
    

    friend ostream &operator<<(ostream &os, Oglasnik &o)
    {
        os << o.ime << endl;
        for (int i = 0; i < o.n; i++)
        {
            os << o.oglasi[i].getNaslov() << endl;
            os << o.oglasi[i].getOpis() << endl;
            os << o.oglasi[i].getCena() << " evra" << endl;
            os << endl;
        }
        return os;
    }
    void oglasiOdKategorija(const char *k)
    {
        for (int i = 0; i < n; i++)
        {
            if ((strcmp(oglasi[i].getKategorija(), k)) == 0)
            {
                cout << oglasi[i] << endl;
            }
        }
    }
    void najniskaCena()
    {
        float min = oglasi[0].getCena();
        int index = 0;
        for (int i = 0; i < n; i++)
        {
            if (oglasi[i].getCena() < min)
            {
                min = oglasi[i].getCena();
                index = i;
            }
        }
        cout << oglasi[index];
    }
};

int main()
{

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin >> tip;

    if (tip == 1)
    {
        cout << "-----Test Oglas & operator <<-----" << endl;
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout << o;
    }
    else if (tip == 2)
    {
        cout << "-----Test Oglas & operator > -----" << endl;
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov, 49);
        cin.getline(kategorija, 29);
        cin.getline(opis, 99);
        cin >> cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1 > o2)
            cout << "Prviot oglas e poskap." << endl;
        else
            cout << "Prviot oglas ne e poskap." << endl;
    }
    else if (tip == 3)
    {
        cout << "-----Test Oglasnik, operator +=, operator << -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++)
        {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            
            try{
            ogl += o;
            }
            catch(NegativnaVrednost &e)
            {
                e.print();
            }
        }
        cout << ogl;
    }
    else if (tip == 4)
    {
        cout << "-----Test oglasOdKategorija -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++)
        {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            try
            {
                ogl+=o;
            }
            catch (NegativnaVrednost &e)
            {
                e.print();
            }
        }
        cin.get();
        cin.getline(k, 29);
        cout << "Oglasi od kategorijata: " << k << endl;
        ogl.oglasiOdKategorija(k);
    }
    else if (tip == 5)
    {
        cout << "-----Test Exception -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++)
        {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            try
            {
                ogl+=o;
            }
            catch (NegativnaVrednost &e)
            {
                e.print();
            }
        }
        cout << ogl;
    }
    else if (tip == 6)
    {
        cout << "-----Test najniskaCena -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++)
        {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            try
            {
                ogl+=o;
            }
            catch (NegativnaVrednost &e)
            {
                e.print();
            }
        }
        cout << "Oglas so najniska cena:" << endl;
        ogl.najniskaCena();
    }
    else if (tip == 7)
    {
        cout << "-----Test All -----" << endl;
        cin.get();
        cin.getline(naziv, 49);
        cin >> n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++)
        {
            cin.get();
            cin.getline(naslov, 49);
            cin.getline(kategorija, 29);
            cin.getline(opis, 99);
            cin >> cena;
            Oglas o(naslov, kategorija, opis, cena);
            try
            {
                ogl+=o;
            }
            catch (NegativnaVrednost &e)
            {
                e.print();
            }
        }
        cout << ogl;

        cin.get();
        cin.get();
        cin.getline(k, 29);
        cout << "Oglasi od kategorijata: " << k << endl;
        ogl.oglasiOdKategorija(k);

        cout << "Oglas so najniska cena:" << endl;
        ogl.najniskaCena();
    }

    return 0;
}
