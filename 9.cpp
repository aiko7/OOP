#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class Exception
{
public:
    Exception(){}
    void print()
    {
        cout<<"Ne moze da se vnese dadeniot trud"<<endl;
    }
};

class Trud
{
    char vid;
    int godina;
public:
    Trud(char vid,int godina)
    {
        this->vid=vid;
        this->godina=godina;
    }
    Trud()
    {
        this->vid='c';
        this->godina=0;
    }
    friend istream &operator>>(istream &is, Trud &t)
    {
        is>>t.vid>>t.godina;
        return is;
    }
    friend class PhDStudent;
};

class Student
{
protected:
    char ime[31];
    int indeks;
    int godina;
    int *oceni;
    int num;
public:
    Student (char *ime="",int indeks=0,int godina=0,int *oceni=nullptr, int num=0)
    {
        strcpy(this->ime,ime);
        this->indeks=indeks;
        this->godina=godina;
        this->num=num;
        this->oceni=new int [num];
        for(int i=0;i<num;i++)
        {
            this->oceni[i]=oceni[i];
        }
    }
    virtual float rang()
    {
        float sum=0.0;
        for(int i=0;i<num;i++)
        {
            sum+=oceni[i];
        }
        sum/=(float)num;
        return sum;
    }
    friend ostream& operator<<(ostream &os, Student &s)
    {
        os<<s.indeks<<" "<<s.ime<<" "<<s.godina<<" "<<s.rang()<<endl;
        return os;
    }
    int getIndeks()
    {
        return indeks;
    }
    Student &operator+=(Trud &t)
    {
        throw Exception();
    }
};

class PhDStudent : public Student
{
    Trud *trudovi;
    int numTrudovi;
public:
    PhDStudent(char *ime="",int indeks=0,int godina=0,int *oceni=nullptr, int num=0,Trud *trudovi=nullptr,int numTrudovi=0)
    :Student(ime,indeks,godina,oceni,num)
    {
        this->numTrudovi=numTrudovi;
        this->trudovi=new Trud [numTrudovi];
        for(int i=0,j=0;i<numTrudovi;i++)
        {
            if(trudovi[i].godina<godina)
            {
                cout<<"Ne moze da se vnese dadeniot trud"<<endl;
                this->numTrudovi--;
            }
            else
            {
                this->trudovi[j]=trudovi[i];
                j++;
            }
        }
    }
    static int konferenciski;
    static void setKonferenciski(int n)
    {
        konferenciski=n;
    }
    static void setSpisanie(int n)
    {
        spisanie=n;
    }
    static int spisanie;
    float rang()
    {
        float sum=Student::rang();
        for(int i=0;i<numTrudovi;i++)
        {
            if(trudovi[i].vid=='c'||trudovi[i].vid=='C') sum+=(float)konferenciski;
            else if(trudovi[i].vid=='j'||trudovi[i].vid=='J') sum+=spisanie;
        }
        return sum;
    }
    PhDStudent &operator+=(Trud &t)
    {
        if(t.godina<godina) throw Exception();
        Trud *tmp=new Trud[numTrudovi+1];
        for(int i=0;i<numTrudovi;i++)
        {
            tmp[i]=trudovi[i];
        }
        tmp[numTrudovi++]=t;
        delete [] trudovi;
        trudovi=tmp;
        return *this;
    }
    int getIndeks()
    {
        return indeks;
    }
};

int PhDStudent::konferenciski=1;
int PhDStudent::spisanie=3;

int main(){
	int testCase;
	cin >> testCase;

	int god, indeks, n, god_tr, m, n_tr;
	int izbor; //0 za Student, 1 za PhDStudent
	char ime[30];
	int oceni[50];
	char tip;
	Trud trud[50];

	if (testCase == 1){
		cout << "===== Testiranje na klasite ======" << endl;
		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		Student s(ime, indeks, god, oceni, n);
		cout << s;

		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		cin >> n_tr;
		for (int j = 0; j < n_tr; j++){
			cin >> tip;
			cin >> god_tr;
			Trud t(tip, god_tr);
			trud[j] = t;
		}
		PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
		cout << phd;
	}
	if (testCase == 2){
		cout << "===== Testiranje na operatorot += ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;

		for(int i=0;i<m;i++)
		{
		    if(niza[i]->getIndeks()==indeks)
            {
                PhDStudent *p=dynamic_cast <PhDStudent*> (niza[i]);
                if (p)
                {
                    try
                    {
                         *p+=t;
                    }
                        catch (Exception &e)
                    {
                        e.print();
                    }
                }
                else cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
            }
		}
		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 3){
		cout << "===== Testiranje na operatorot += ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;

		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2

        for(int i=0;i<m;i++)
		{
		    if(niza[i]->getIndeks()==indeks)
            {
                PhDStudent *p=dynamic_cast <PhDStudent*>(niza[i]);
                if (p)
                {
                    try
                    {
                        *p+=t;
                    }
                        catch (Exception &e)
                    {
                        e.print();
                    }
                }
                else cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
            }
            else cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 4){
		cout << "===== Testiranje na isklucoci ======" << endl;
		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		cin >> n_tr;
		for (int j = 0; j < n_tr; j++){
			cin >> tip;
			cin >> god_tr;
			Trud t(tip, god_tr);
			trud[j] = t;
		}
		PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
		cout << phd;
	}
	if (testCase == 5){
		cout << "===== Testiranje na isklucoci ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;
        for(int i=0;i<m;i++)
		{
		    if(niza[i]->getIndeks()==indeks)
            {
                PhDStudent *p=dynamic_cast <PhDStudent*> (niza[i]);
                if (p)
                {
                    try
                    {
                         *p+=t;
                    }
                        catch (Exception &e)
                    {
                        e.print();
                    }
                }
                else cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
            }
		}
		// vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 6){
		cout << "===== Testiranje na static clenovi ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		int conf, journal;
		cin >> conf;
		cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi
        PhDStudent::setKonferenciski(conf);
        PhDStudent::setSpisanie(journal);
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}

	return 0;
}
