    #include <iostream>
    #include <cstring>
    using namespace std;

    class Koncert
    {
    protected:
        char name[20];
        char location[20];
        float price;
        static double discount;
    public:
        Koncert(char *name, char *location,float price)
        {
            strcpy(this->name, name);
            strcpy(this->location, location);
            this->price = price;
        }


        char *getNaziv()
        {
            return name;
        }

        static void setSezonskiPopust(float discount)
        {
            Koncert::discount = discount;
        }
        virtual float cena()
        {
            return ((price * (100.0 - discount*100)) / 100.0);
        }
        virtual bool type()
        {
            return 0;
        }
    };
double Koncert::discount=20;
    class ElektronskiKoncert : public Koncert
    {
    private:
        char *djname;
        float duration;
        bool time;

    public:

        ElektronskiKoncert(char *name, char *location, float price, char *djname, float duration, bool time) : Koncert(name, location, price)
        {
            this->djname = new char[strlen(djname) + 1];
            strcpy(this->djname, djname);
            this->duration = duration;
            this->time = time;
        }

        float getSezonskiPopust()
        {
            return discount;
        }

        float cena() override
        {
            if (time == 0)
            {
                price -= 50;
            }
            if (time == 1)
            {
                price += 100;
            }

            if (duration >= 5)
            {
                return (price + 150);
            }
            if (duration >= 7)
            {
                return (price += 360);
            }
            return price;
        }
        bool type() override
        {
            return 1;
        }
    };
    void najskapKoncert(Koncert **koncerti, int n)
    {
        float max = 0;
        int location = -1;
        int c = 0;

        for (int i = 0; i < n; i++)
        {
            if (koncerti[i]->cena() > max)
            {
                max = koncerti[i]->cena();
                location = i;
            }
            if (koncerti[i]->type() == 1)
            {
                c++;
            }
        }
        if (location != -1)
        {
            cout << "Najskap koncert: " << koncerti[location]->getNaziv() << " " << koncerti[location]->cena() << endl;
            cout << "Elektronski koncerti: " << c << " od vkupno " << n << endl;
        }
        else
        {
            cout << "FUCK" << endl;
        }
    }
    bool prebarajKoncert(Koncert **koncerti, int n, char *naziv, bool elektronski)
    {

        if (elektronski)
        {
            for (int i = 0; i < n; i++)
            {
                if (koncerti[i]->type())
                {
                    if (strcmp((koncerti[i]->getNaziv()), naziv) == 0)
                    {
                        cout << koncerti[i]->getNaziv() << endl;
                        return 1;
                    }
                }
            }
        }
        else
        {
            for (int i = 0; i < n; i++)
            {
                if (strcmp((koncerti[i]->getNaziv()), naziv) == 0)
                {
                    cout << koncerti[i]->getNaziv() << endl;
                    return 1;
                }
            }

            return 0;
        }
    }

int main()
{

    int tip, n, novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

8    cin >> tip;
    if (tip == 1)
    { // Koncert
        cin >> naziv >> lokacija >> cenaBilet;
        Koncert k1(naziv, lokacija, cenaBilet);
        cout << "Kreiran e koncert so naziv: " << k1.getNaziv() << endl;
    }
    else if (tip == 2)
    { // cena - Koncert
        cin >> naziv >> lokacija >> cenaBilet;
        Koncert k1(naziv, lokacija, cenaBilet);
        cout << "Osnovna cena na koncertot so naziv " << k1.getNaziv() << " e: " << k1.cena() << endl;
    }
    else if (tip == 3)
    { // ElektronskiKoncert
        cin >> naziv >> lokacija >> cenaBilet >> imeDJ >> casovi >> dnevna;
        ElektronskiKoncert s(naziv, lokacija, cenaBilet, imeDJ, casovi, dnevna);
        cout << "Kreiran e elektronski koncert so naziv " << s.getNaziv() << " i sezonskiPopust " << s.getSezonskiPopust() << endl;
    }
    else if (tip == 4)
    { // cena - ElektronskiKoncert
        cin >> naziv >> lokacija >> cenaBilet >> imeDJ >> casovi >> dnevna;
        ElektronskiKoncert s(naziv, lokacija, cenaBilet, imeDJ, casovi, dnevna);
        cout << "Cenata na elektronskiot koncert so naziv " << s.getNaziv() << " e: " << s.cena() << endl;
    }
    else if (tip == 5)
    { // najskapKoncert
    }
    else if (tip == 6)
    { // prebarajKoncert
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso", "Mykonos", 8800, "Guetta", 3, true);
        char naziv[100];
        najskapKoncert(koncerti, 5);
    }
    else if (tip == 7)
    { // prebaraj
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso", "Mykonos", 8800, "Guetta", 3, true);
        char naziv[100];
        bool elektronski;
        cin >> elektronski;
        if (prebarajKoncert(koncerti, 5, "Area", elektronski))
            cout << "Pronajden" << endl;
        else
            cout << "Ne e pronajden" << endl;

        if (prebarajKoncert(koncerti, 5, "Area", !elektronski))
            cout << "Pronajden" << endl;
        else
            cout << "Ne e pronajden" << endl;
    }
    else if (tip == 8)
    { // smeni cena
        Koncert **koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area", "BorisTrajkovski", 350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand", "Belgium", 8000, "Afrojack", 7.5, false);
        koncerti[2] = new ElektronskiKoncert("SeaDance", "Budva", 9100, "Tiesto", 5, true);
        koncerti[3] = new Koncert("Superhiks", "PlatoUkim", 100);
        koncerti[2]->setSezonskiPopust(0.9);
        najskapKoncert(koncerti, 4);
    }

    return 0;
}
