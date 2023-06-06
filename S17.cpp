#include <iostream>
#include <cstring>
using namespace std;

class FudbalskaEkipa
{
protected:
    char trener[100];
    int golovi[10];
public:
    FudbalskaEkipa(char *trener,int golovi[])
    {
        strcpy(this->trener,trener);
        for(int i=0;i<10;i++)
        {
            this->golovi[i]=golovi[i];
        }
    }
    virtual ~FudbalskaEkipa(){}
    virtual int uspeh()=0;
    friend ostream &operator<<(ostream &os,FudbalskaEkipa &e);
    FudbalskaEkipa &operator+=(int num)
    {
        for(int i=0;i<10;i++)
        {
            golovi[i]=golovi[i+1];
        }
        golovi[9]=num;
    }
    bool operator>(FudbalskaEkipa &dr)
    {
        return uspeh()>dr.uspeh();
    }
};

class Klub:public FudbalskaEkipa
{
    char ime[50];
    int brojTituli;
public:
    Klub(char *trener,int golovi[],char *ime,int brojTituli):FudbalskaEkipa(trener,golovi)
    {
        strcpy(this->ime,ime);
        this->brojTituli=brojTituli;
    }
    int uspeh()
    {
        int sum=0;
        for(int i=0;i<10;i++)
        {
            sum+=golovi[i];
        }
        sum*=3;
        sum+=brojTituli*1000;
        return sum;
    }
    friend ostream &operator<<(ostream &os,FudbalskaEkipa &e);
};

class Reprezentacija:public FudbalskaEkipa
{
    char drzava[50];
    int brojNastapi;
public:
    Reprezentacija(char *trener,int golovi[],char *drzava,int brojNastapi):FudbalskaEkipa(trener,golovi)
    {
        strcpy(this->drzava,drzava);
        this->brojNastapi=brojNastapi;
    }
    int uspeh()
    {
        int sum=0;
        for(int i=0;i<10;i++)
        {
            sum+=golovi[i];
        }
        sum*=3;
        sum+=brojNastapi*50;
        return sum;

    }
    friend ostream &operator<<(ostream &os,FudbalskaEkipa &e);
};

ostream &operator<<(ostream &os,FudbalskaEkipa &e)
{
    Klub *k=dynamic_cast<Klub *>(&e);
    if(k!=0)
    {
        os<<k->ime<<endl;
    }
    Reprezentacija *r=dynamic_cast<Reprezentacija *>(&e);
    if(r!=0)
    {
        os<<r->drzava<<endl;
    }
    os<<e.trener<<endl;
    os<<e.uspeh()<<endl;
    return os;
}

void najdobarTrener(FudbalskaEkipa **e,int num)
{
    FudbalskaEkipa *max=e[0];
    int index=0;
    for(int i=1;i<num;i++)
    {
        if(*e[i]>*max)
        {
            max=e[i];
            index=i;
        }
    }
    cout<<*e[index];
}

int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}