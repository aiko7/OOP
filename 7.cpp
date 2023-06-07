#include <iostream>
#include <string.h>
#include <cstring>
using namespace std;

class OutOfBoundException
{
    char text[300];
public:
    OutOfBoundException(char *text)
    {
        strcpy(this->text,text);
    }
    void print()
    {
        cout<<text<<endl;
    }
};

class Karticka{
   protected:
       char smetka[16];
       int pin;
       bool povekjePin;
   public:
    Karticka(char* smetka,int pin){
       strcpy(this->smetka,smetka);
       this->pin=pin;
       this->povekjePin=false;
     }
     virtual int tezinaProbivanje()
     {
         int m=pin,c=0;
         while(m)
         {
             m/=10;
             c++;
         }
         return c;
     }
    friend ostream &operator<<(ostream &os,Karticka &k)
    {
        os<<k.smetka<<": "<<k.tezinaProbivanje()<<endl;
        return os;
    }
     friend class Banka;
     virtual int getDopolnitenPin()
     {
         return 0;
     }
};

class SpecijalnaKarticka:public Karticka
{
    int *dopPinovi;
    int brojPinovi;
public:
    static const int MAX;
    SpecijalnaKarticka(char* smetka,int pin):Karticka(smetka,pin)
    {
        brojPinovi=0;
        dopPinovi=nullptr;
        povekjePin=true;
    }
    friend ostream &operator<<(ostream &os,SpecijalnaKarticka &k)
    {
        os<<k.smetka<<": "<<k.tezinaProbivanje()<<endl;
        return os;
    }
    int tezinaProbivanje()
    {
        int broj = Karticka::tezinaProbivanje();
        broj+=brojPinovi;
        return broj;
    }
    SpecijalnaKarticka &operator+=(int pin)
    {
        if(brojPinovi>=MAX)
        {
            throw OutOfBoundException("Brojot na bin kodovi ne moze da go nadmine dozvolenoto");
        }
        int *tmp=new int [brojPinovi+1];
        for(int i=0;i<brojPinovi;i++)
        {
            tmp[i]=dopPinovi[i];
        }
        tmp[brojPinovi++]=pin;
        delete [] dopPinovi;
        dopPinovi=tmp;
        return *this;
    }
    friend class Banka;
    int getDopolnitenPin()
    {
         return 1;
    }

};

const int SpecijalnaKarticka::MAX=4;

//вметнете го кодот за SpecijalnaKarticka



class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
public:
    Banka(char *naziv, Karticka** karticki,int broj ){
    strcpy(this->naziv,naziv);
      for (int i=0;i<broj;i++)
      {
        if (karticki[i]->getDopolnitenPin())
        {
            this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
        }
        else this->karticki[i]=new Karticka(*karticki[i]);
      }
      this->broj=broj;
    }
    static int LIMIT;
    static void setLIMIT(int n)
    {
        LIMIT=n;
    }
    void pecatiKarticki()
    {
        cout<<"Vo bankata "<<naziv<<" moze da se probijat kartickite:"<<endl;
        for(int i=0;i<broj;i++)
        {
            if(karticki[i]->tezinaProbivanje()<=LIMIT)
            {
                cout<<*karticki[i];
            }
        }
    }
    void dodadiDopolnitelenPin(char *smetka,int novPin)
    {
        for(int i=0;i<broj;i++)
        {
        if(strcmp(karticki[i]->smetka,smetka)==0)
        {
            SpecijalnaKarticka *k= dynamic_cast<SpecijalnaKarticka*>(karticki[i]);
            if(k)
            {
                try
                {
                    *k+=novPin;
                }
                catch (OutOfBoundException &e)
                {
                    e.print();
                }
            }
        }
        }
    }

};

int Banka::LIMIT=7;


int main(){

Karticka **niza;
int n,m,pin;
char smetka[16];
bool daliDopolnitelniPin;
cin>>n;
niza=new Karticka*[n];
for (int i=0;i<n;i++){
   cin>>smetka;
   cin>>pin;
   cin>>daliDopolnitelniPin;
   if (!daliDopolnitelniPin)
    niza[i]=new Karticka(smetka,pin);
   else
    niza[i]=new SpecijalnaKarticka(smetka,pin);
}

Banka komercijalna("Komercijalna",niza,n);
for (int i=0;i<n;i++) delete niza[i];
delete [] niza;
cin>>m;
for (int i=0;i<m;i++){
   cin>>smetka>>pin;

   komercijalna.dodadiDopolnitelenPin(smetka,pin);

}


Banka::setLIMIT(5);

komercijalna.pecatiKarticki();

}
