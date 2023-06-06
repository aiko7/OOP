#include <iostream>
#include <cstring>
using namespace std;

class Transport
{
protected:
    char *destinacija;
    int cena;
    int rastojanie;
public:
    Transport(char *destinacija="",int cena=0,int rastojanie=0)
    {
        this->destinacija=new char[strlen(destinacija)+1];
        strcpy(this->destinacija,destinacija);
        this->cena=cena;
        this->rastojanie=rastojanie;
    }
    virtual int cenaTransport()=0;
    virtual int getRastojanie()=0;
    friend void pecatiPoloshiPonudi(Transport **t,int num,Transport &ponuda);
    Transport &operator=(const Transport &dr)
    {
        this->destinacija=new char[strlen(dr.destinacija)+1];
        strcpy(this->destinacija,dr.destinacija);
        this->cena=dr.cena;
        this->rastojanie=dr.rastojanie;
    }
};

class AvtomobilTransport:public Transport
{
    bool sofer;
public:
    AvtomobilTransport(char *destinacija="",int cena=0,int rastojanie=0,bool sofer=false)
    :Transport(destinacija,cena,rastojanie)
    {
        this->sofer=sofer;
    }
    int cenaTransport()
    {
        if(sofer) return cena*1.2;
        else return cena;
    }
    int getRastojanie()
    {
        return rastojanie;
    }
    friend void pecatiPoloshiPonudi(Transport **t,int num,Transport &ponuda);
};

class KombeTransport:public Transport
{
    int brojLugje;
public:
    KombeTransport(char *destinacija="",int cena=0,int rastojanie=0,int brojLugje=0)
    :Transport(destinacija,cena,rastojanie)
    {
        this->brojLugje=brojLugje;
    }
    int cenaTransport()
    {
        return cena-(brojLugje*200);
    }
    int getRastojanie()
    {
        return rastojanie;
    }
    friend void pecatiPoloshiPonudi(Transport **t,int num,Transport &ponuda);
};

bool operator<(Transport &a,Transport &b)
{
    if(a.getRastojanie()<b.getRastojanie()) return true;
    else return false;
}

void pecatiPoloshiPonudi(Transport **t,int num,Transport &ponuda)
{
    for(int i=0;i<num;i++)
    {
        for(int j=i;j<num-1-i;j++)
        {
            if(*t[j+1]<*t[j])
            {
                Transport *tmp=*(t+j);
                t[j]=t[j+1];
                *(t+1+j)=tmp;
            }
        }
    }
    for(int i=0;i<num;i++)
    {
        if(t[i]->cenaTransport()>ponuda.cenaTransport())
        {
            cout<<t[i]->destinacija<<" "<<t[i]->rastojanie<<" "<<t[i]->cenaTransport()<<endl;
        }
    }
}

int main(){

char destinacija[20];
int tip,cena,rastojanie,lugje;
bool shofer;
int n;
cin>>n;
Transport  **ponudi;
ponudi=new Transport *[n];

for (int i=0;i<n;i++){

    cin>>tip>>destinacija>>cena>>rastojanie;
    if (tip==1) {
        cin>>shofer;
        ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

    }
    else {
        cin>>lugje;
        ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
    }


}

AvtomobilTransport nov("Ohrid",2000,600,false);
pecatiPoloshiPonudi(ponudi,n,nov);

for (int i=0;i<n;i++) delete ponudi[i];
delete [] ponudi;
return 0;
}