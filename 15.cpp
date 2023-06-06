#include<iostream>
#include<string.h>
using namespace std;

class BadInputException
{
    char text[100];
public:
    BadInputException(const char *text)
    {
        strcpy(this->text,text);
    }
    void print()
    {
        cout<<text<<endl;
    }
};

class StudentKurs{
   protected:
       char ime[30];
       int oc;
       bool daliUsno;

    public:
    const static int MINOCENKA;
    StudentKurs(char* ime,int finalenIspit)
    {
       strcpy(this->ime,ime);
       this->oc=finalenIspit;
       this->daliUsno=false;
    }
    virtual ~StudentKurs(){}
    static int MAX;
    static void setMAX(int a)
    {
        MAX=a;
    }
    friend ostream &operator<<(ostream &os,StudentKurs &k);
    virtual int ocenka()
    {
        return oc;
    }
    bool getDaliUsno()
    {
        return daliUsno;
    }
    friend class KursFakultet;
};

int StudentKurs::MAX=9;

class StudentKursUsno:public StudentKurs
{
    char *opisno;
public:
    StudentKursUsno(char* ime,int ocenka):StudentKurs(ime,ocenka)
    {
        daliUsno=true;
        opisno=nullptr;
    }
    ~StudentKursUsno()
    {
        delete [] opisno;
    }
    friend ostream &operator<<(ostream &os,StudentKurs &k);
    int ocenka() override
    {
        return oc;
    }
    StudentKursUsno &operator+=(char *opisno)
    {
        int flag=0;
        for(int i=0;i<strlen(opisno);i++)
        {
            if(isalpha(*(opisno+i))==0)
            {
                flag=1;
                for(int j=i;j<strlen(opisno)-1;j++)
                {
                    opisno[j]=opisno[j+1];
                }
            }
        }
        if(strncmp(opisno,"odl",3)==0) if(oc+2<StudentKurs::MAX) this->oc+=2; else this->oc=StudentKurs::MAX;
        else if(strncmp(opisno,"dobro",5)==0) if(oc+1<StudentKurs::MAX) this->oc+=1; else this->oc=StudentKurs::MAX;
        else if(strncmp(opisno,"los",3)==0) this->oc-=1;
        if (flag) throw BadInputException("Greshna opisna ocenka");

    }
    bool getDaliUsno()
    {
        return daliUsno;
    }
    friend class KursFakultet;
};

ostream &operator<<(ostream &os,StudentKurs &k)
{
    os<<k.ime<<" --- "<<k.ocenka()<<endl;
    return os;
}

const int StudentKurs::MINOCENKA=6;

class KursFakultet{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;

public:
    KursFakultet(char *naziv, StudentKurs** studenti,int broj )
    {
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++)
        {
            if (studenti[i]->getDaliUsno())
            {
                this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
            }
            else this->studenti[i]=new StudentKurs(*studenti[i]);
        }
        this->broj=broj;
    }
    ~KursFakultet()
    {
        for (int i=0;i<broj;i++) delete studenti[i];
    }
    void pecatiStudenti()
    {
        cout<<"Kursot "<<naziv<<" go polozile:"<<endl;
        for(int i=0;i<broj;i++)
        {
            if(studenti[i]->ocenka()>=StudentKurs::MINOCENKA) cout<<*studenti[i];
        }
    }
    void postaviOpisnaOcenka(const char *ime, char *ocenka)
    {
        for(int i=0;i<broj;i++)
        {
            if(strcmp(ime,studenti[i]->ime)==0)
            {
                StudentKursUsno *u=dynamic_cast<StudentKursUsno*>(studenti[i]);
                if(u!=0)
                {
                    try
                    {
                        *u+=ocenka;
                    }
                    catch (BadInputException &e)
                    {
                        e.print();
                    }
                }
                else cout << "Student " << ime << " ne moze da dobie opisna ocenka." << endl;
            return ;
            }
        }
    }

};

int main(){

StudentKurs **niza;
int n,m,ocenka;
char ime[30],opisna[10];
bool daliUsno;
cin>>n;
niza=new StudentKurs*[n];
for (int i=0;i<n;i++){
   cin>>ime;
   cin>>ocenka;
   cin>>daliUsno;
   if (!daliUsno)
    niza[i]=new StudentKurs(ime,ocenka);
   else
    niza[i]=new StudentKursUsno(ime,ocenka);
}

KursFakultet programiranje("OOP",niza,n);
for (int i=0;i<n;i++) delete niza[i];
delete [] niza;
cin>>m;

for (int i=0;i<m;i++){
   cin>>ime>>opisna;
   programiranje.postaviOpisnaOcenka(ime,opisna);
}

StudentKurs::setMAX(9);

programiranje.pecatiStudenti();

}
