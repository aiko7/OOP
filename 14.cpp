#include<iostream>
#include<string.h>
#include <cstring>
using namespace std;

class SMS
{
protected:
    float osnovnaCena;
    char pretplatnickiBroj[20];
public:
    SMS(char *pretplatnickiBroj="",float osnovnaCena=0.0)
    {
        this->osnovnaCena=osnovnaCena;
        strcpy(this->pretplatnickiBroj,pretplatnickiBroj);
    }
    virtual float SMS_cena()=0;
    static const float DANOK;
    friend ostream&operator<<(ostream &os,SMS &p);
};

const float SMS::DANOK=0.18;

class RegularSMS:public SMS
{
    char tekst[500];
    bool roaming;
public:
    static float roamin;
    static void set_rProcent(int n)
    {
        roamin=(float)n/100.0;
    }
    RegularSMS(char *pretplatnickiBroj="",float osnovnaCena=0.0,char *tekst="",bool roaming=false)
    :SMS(pretplatnickiBroj,osnovnaCena)
    {
        this->roaming=roaming;
        strcpy(this->tekst,tekst);
    }
    float SMS_cena()
    {
        float sum=osnovnaCena;
        int dolzina =0;
        if(strlen(tekst)>160)
        {
            int n=(strlen(tekst)/160);
            sum=(n+1)*osnovnaCena;
        }
        if(roaming) sum+=sum*roamin;
        else sum+=sum*DANOK;
        return sum;
    }
    friend ostream&operator<<(ostream &os,SMS &p);
};

float RegularSMS::roamin=3.0;

class SpecialSMS:public SMS
{
    bool humanitarniCeli;
public:
    static float hum;
    static void set_sProcent(int n)
    {
        hum=(float)n/100.0;
    }
    SpecialSMS(char *pretplatnickiBroj="",float osnovnaCena=0.0,bool humanitarniCeli=false)
    :SMS(pretplatnickiBroj,osnovnaCena)
    {
        this->humanitarniCeli=humanitarniCeli;
    }
    float SMS_cena()
    {
        float sum=osnovnaCena;
        if(humanitarniCeli)
        {
            return sum;
        }
        else return sum+(sum*hum);
    }
    friend ostream&operator<<(ostream &os,SMS &p);
};

float SpecialSMS::hum=1.5;


ostream &operator<<(ostream &os,SMS &p)
{
    os<<"Tel: "<<p.pretplatnickiBroj<<" - cena: "<<p.SMS_cena()<<"den."<<endl;
    return os;
}

void vkupno_SMS(SMS **poraka,int n)
{
    int regBr=0,specBr=0;
    float regCena=0.0,specCena=0.0;
    for(int i=0;i<n;i++)
    {
        RegularSMS *r=dynamic_cast <RegularSMS*>(poraka[i]);
        if(r)
        {
            regBr++;
            regCena+=r->SMS_cena();
        }
        else
        {
            SpecialSMS *s=dynamic_cast<SpecialSMS*>(poraka[i]);
            specBr++;
            specCena+=s->SMS_cena();
        }
    }
    cout<<"Vkupno ima "<<regBr<<" regularni SMS poraki i nivnata cena e: "<<regCena<<endl;
    cout<<"Vkupno ima "<<specBr<<" specijalni SMS poraki i nivnata cena e: "<<specCena<<endl;
}

int main(){

	char tel[20], msg[1000];
	float cena;
	float price;
    int p;
	bool roam, hum;
	SMS  **sms;
	int n;
	int tip;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing RegularSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new RegularSMS(tel, cena, msg, roam);
			cout << "OPERATOR <<" << endl;
			cout << *sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
	if (testCase == 2){
		cout << "====== Testing SpecialSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
			cin >> hum;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new SpecialSMS(tel, cena, hum);
			cout << "OPERATOR <<" << endl;
			cout << *sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
	if (testCase == 3){
		cout << "====== Testing method vkupno_SMS() ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i<n; i++){

			cin >> tip;
			cin >> tel;
			cin >> cena;
			if (tip == 1) {

				cin.get();
				cin.getline(msg, 1000);
                cin >> roam;

				sms[i] = new RegularSMS(tel, cena, msg, roam);

			}
			else {
				cin >> hum;

				sms[i] = new SpecialSMS(tel, cena, hum);
			}
		}

		vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
    if (testCase == 4){
		cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        	cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			sms1 = new RegularSMS(tel, cena, msg, roam);
			cout << *sms1;

            cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
        	cin >> p;
        	RegularSMS::set_rProcent(p);
        	sms2 = new RegularSMS(tel, cena, msg, roam);
        	cout << *sms2;

        delete sms1, sms2;
	}
    if (testCase == 5){
		cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        	cin >> tel;
			cin >> cena;
			cin >> hum;
			sms1 = new SpecialSMS(tel, cena, hum);
			cout << *sms1;

            cin >> tel;
			cin >> cena;
			cin >> hum;
        	cin >> p;
        	SpecialSMS::set_sProcent(p);
        	sms2 = new SpecialSMS(tel, cena, hum);
        	cout << *sms2;

        delete sms1, sms2;
	}

	return 0;
}
