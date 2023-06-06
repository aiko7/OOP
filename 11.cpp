#include<iostream>
#include<string.h>
using namespace std;

//место за вашиот код
class Delo
{
protected:
    char delo[50];
    int godina;
    char drzava[50];
public:
    Delo(char *delo="",int godina=0,char *drzava="")
    {
        strcpy(this->delo,delo);
        strcpy(this->drzava,drzava);
        this->godina=godina;
    }
    bool operator==(const Delo &dr)
    {
        int flag=1;
        if(strcmp(this->delo,dr.delo)) return false;
        return true;
    }
    Delo &operator=(const Delo &dr)
    {
        if(this!=&dr)
        {
            strcpy(this->delo,dr.delo);
            strcpy(this->drzava,dr.drzava);
            this->godina=dr.godina;
        }
        return *this;
    }
    friend class Pretstava;
    char *getIme()
    {
        return delo;
    }
};

class Pretstava
{
protected:
    Delo delo;
    int brKarti;
    char data[16];
public:
    Pretstava(Delo delo,int brKarti,char *data)
    {
        this->delo=delo;
        this->brKarti=brKarti;
        strcpy(this->data,data);
    }
    virtual int cena()
    {
        int tsena=0;
        if(this->delo.godina>1899) tsena+=50;
        else if(this->delo.godina>1799) tsena+=75;
        else tsena+=100;
        if(strcmp(this->delo.drzava,"Italija")==0) tsena+=100;
        else if(strcmp(this->delo.drzava,"Rusija")==0) tsena+=150;
        else tsena+=80;
        return tsena;
    }
    Delo getDelo()
    {
        return this->delo;
    }
    friend int brojPretstaviNaDelo(Pretstava **p,int n,Delo a);
    friend int prihod(Pretstava **p,int n);
};

class Balet: public Pretstava
{
public:
    static int CenaBalet;
    static void setCenaBalet(int n)
    {
        CenaBalet=n;
    }
    int cena()
    {
        int tsena=Pretstava::cena();
        return tsena+CenaBalet;
    }
    Balet(Delo delo,int brKarti,char *data):Pretstava(delo,brKarti,data){};
};

class Opera: public Pretstava
{
public:
    Opera(Delo delo,int brKarti,char *data):Pretstava(delo,brKarti,data){};
};

int prihod(Pretstava **p,int n)
{
    int sum=0;
    for(int i=0;i<n;i++)
    {
        sum=sum+(p[i]->cena()*p[i]->brKarti);
    }
    return sum;
}

int Balet::CenaBalet=150;

int brojPretstaviNaDelo(Pretstava **p,int n,Delo a)
{
    int br=0;
    for(int i=0;i<n;i++)
    {
        if(p[i]->delo==a)
        {
            br++;
        }
    }
    return br;
}

//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
    case 1:
    //Testiranje na klasite Opera i Balet
    {
        cout<<"======TEST CASE 1======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->getDelo().getIme()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->getDelo().getIme()<<endl;
    }break;

    case 2:
    //Testiranje na  klasite Opera i Balet so cena
    {
        cout<<"======TEST CASE 2======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->cena()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->cena()<<endl;
    }break;

    case 3:
    //Testiranje na operator ==
    {
        cout<<"======TEST CASE 3======="<<endl;
        Delo f1=readDelo();
        Delo f2=readDelo();
        Delo f3=readDelo();

        if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
        if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

    }break;

    case 4:
    //testiranje na funkcijata prihod
    {
        cout<<"======TEST CASE 4======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();

        }
        cout<<prihod(pole,n);
    }break;

    case 5:
    //testiranje na prihod so izmena na cena za 3d proekcii
    {
        cout<<"======TEST CASE 5======="<<endl;
        int cenaBalet;
        cin>>cenaBalet;
        Balet::setCenaBalet(cenaBalet);
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }
        cout<<prihod(pole,n);
        }break;

    case 6:
    //testiranje na brojPretstaviNaDelo
    {
        cout<<"======TEST CASE 6======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }

        Delo f=readDelo();
        cout<<brojPretstaviNaDelo(pole,n,f);
    }break;

    };


return 0;
}
