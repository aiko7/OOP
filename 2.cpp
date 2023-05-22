#include <iostream>
#include <cstring>
using namespace std;

class Vozac
{
protected:
    char name[100];
    int age;
    int races;
    bool veteran;

public:
    Vozac()
    {
    }
    Vozac(char *name, int age, int races, bool veteran)
    {
        strcpy(this->name, name);
        this->age = age;
        this->races = races;
        this->veteran = veteran;
    }

    friend ostream &operator<<(ostream &x, Vozac &v)
    {
        if(v.veteran){
        x << v.name << "\n"
          << v.age << "\n"
          << v.races<< "\n";
        x <<"VETERAN" << endl;
        }
        else{
        x << v.name << "\n"
          << v.age << "\n"
          << v.races<<endl;            
        }

        return x;
    }

    bool operator==(Vozac &v1)
    {
        if (danok() == v1.danok())
        {
            return 1;
        }
        return 0;
    }

    virtual float salary()=0;

    virtual float danok()=0;

};

class Avtomobilist : public Vozac
{
private:
    float price;

public:
    Avtomobilist(char *name, int age, int races, bool veteran, float price) : Vozac(name, age, races, veteran)
    {
        this->price = price;
    }

    float salary() override
    {
        return (price / 5);
    }
    float danok() override
    {
        if (races > 10)
        {
            return (0.15 * salary());
        }
        return (0.1 * salary());
    }
};

class Motociklist : public Vozac
{
private:
    int cc;

public:
    Motociklist(char *name, int age, int races, bool veteran, int cc) : Vozac(name, age, races, veteran)
    {
        this->cc = cc;
    }

    float salary() override
    {
        return (cc * 20);
    }
    float danok() override
    {
        if (veteran)
        {
            return (0.25 * salary());
        }
        return (0.2 * salary());
    }
};

int soIstaZarabotuvachka(Vozac **v, int n, Vozac *vx)
{
    int a = 0;
    for (int i = 0; i < n; i++)
    {
        if (v[i]->danok() == vx->danok())
        {
            a++;
        }
    }
    return a;
}

int main()
{
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac *[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for (int i = 0; i < n; ++i)
    {
        cin >> ime >> vozrast >> trki >> vet;
        if (i < x)
        {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        }
        else
        {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for (int i = 0; i < n; ++i)
    {
        delete v[i];
    }
    delete[] v;
    delete vx;
    return 0;
}
