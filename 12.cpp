#include <iostream>
#include <cstring>
using namespace std;

enum tip
{
    smartfon,
    kompjuter
};

class InvalidProductionDate
{
private:
    char *text;

public:
    InvalidProductionDate(char *text)
    {
        this->text = new char[strlen(text) + 1];
        strcpy(this->text, text);
    }
    void print()
    {
        cout << text << endl;
    }
};

class Device
{
private:
    char model[100];
    tip type;
    static float proverka;
    int godina;
    float hours;

public:
    Device() {}
    Device(char *model, tip type, int godina = 0)
    {
        strcpy(this->model, model);
        this->type = type;
        this->godina = godina;
        hours = proverka;
        if (godina > 2015)
            hours += 2.0; // mozebi i 2???
        if (type == 1)
            hours += 2.0;
    }
    friend ostream &operator<<(ostream &os, Device &m)
    {
        os << m.model << endl;
        if (m.type)
        {
            os << "smartfon ";
        }
        else
        {
            os << "kompjuter ";
        }
        if (m.godina > 2015)
        {
            if (m.type)
            {
                os << m.proverka + 4 << endl;
                return os;
            }
            os << m.proverka + 2 << endl;
            return os;
        }
        if (m.type)
        {
            os << m.proverka + 2 << endl;
        }
        return os;
    }
    static void setPocetniCasovi(float value)
    {
        proverka = value;
    }

    friend class MobileServis;
};
float Device::proverka = 1.0;

class MobileServis
{
private:
    char adress[100];
    Device *devices;
    int n;

public:
    MobileServis(char *adress, Device *devices, int n)
    {
        strcpy(this->adress, adress);
        this->n = n;
        this->devices = new Device[n];
        for (int i = 0; i < n; i++)
        {
            this->devices[i] = devices[i];
        }
    }
    MobileServis(char *adress="")
    {
        strcpy(this->adress, adress);
        this->devices = nullptr;
        n = 0;
    }

    MobileServis operator+=(Device &d)
    {
        if (d.godina > 2019 || d.godina < 2000)
        {
            throw InvalidProductionDate("Невалидна година на производство");
        }

        Device *temp;
        temp = new Device[n + 1];
        for (int i = 0; i < n; i++)
        {
            temp[i] = devices[i];
        }
        delete[] devices;
        temp[n + 1] = d;
        devices = temp;
        return *this;
    }

    void pecatiCasovi()
    {
        cout << "Ime: " << adress << endl;

        for (int i = 0; i < n; i++)
        {
            cout << devices[i];
        }
    }
};
int main()
{
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1)
    {
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime, (tip)tipDevice, godina);
        cin >> ime;
        MobileServis t(ime);
        cout << ig;
    }
    if (testCase == 2)
    {
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip)tipDevice, godina);
            t += tmp;
        }
        t.pecatiCasovi();
    }
    if (testCase == 3)
    {
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip)tipDevice, godina);
            try
            {
                t += tmp;
            }
            catch (InvalidProductionDate &e)
            {
                e.print();
            }
        }
        t.pecatiCasovi();
    }
    if (testCase == 4)
    {
        cout << "===== Testiranje na konstruktori ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip)tipDevice, godina);
            try
            {
                t += tmp;
            }
            catch (InvalidProductionDate &e)
            {
                e.print();
            }
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5)
    {
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip)tipDevice, godina);

            try
            {
                t += tmp;
            }
            catch (InvalidProductionDate &e)
            {
                e.print();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6)
    {
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin >> ime;
        cin >> n;
        MobileServis t(ime);
        for (int i = 0; i < n; i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime, (tip)tipDevice, godina);
            try
            {
                t += tmp;
            }
            catch (InvalidProductionDate &e)
            {
                e.print();
            }
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;
}
