#include <cstring>
#include <iostream>
using namespace std;

// Your Code goes here

class Pizza{
protected:
    char ime[20];
    char sostojki[100];
    double cena;
public:
    Pizza(char *ime=new char[0],char *sostojki=new char[0],double cena=0.0) {
        strcpy(this->ime, ime);
        strcpy(this->sostojki, sostojki);
        this->cena = cena;
    }
    virtual double price() = 0;
    bool operator<(Pizza &p)
    {
        return price()<p.price();
    }

    const char *getIme() const {
        return ime;
    }

    const char *getSostojki() const {
        return sostojki;
    }

    double getCena() const {
        return cena;
    }
    friend ostream &operator<<(ostream &os, const Pizza &other){
        os<< other.ime<<": ";
        for (int i = 0; i < 49; ++i) {
            if (other.sostojki[i]=='\0')
            {
                break;
            }
            os<<other.sostojki[i];
        }
        os<<", ";
        return os;
    }
};

enum Size{
    MALA,GOLEMA,FAMILIJARNA
};

class FlatPizza : public Pizza{
private:
    Size golemina;
public:
    FlatPizza(char *ime=new char[0],char *sostojki=new char[0],double cena=0.0, Size golemina=(Size)0)
            : Pizza(ime,sostojki,cena)
    {
        this->golemina = golemina;
    }
    double price()
    {
        if(golemina==MALA)
        {
            return cena * 1.10;
        }
        else if(golemina==FAMILIJARNA)
        {
            return cena * 1.30;
        }
        return cena*1.50;
    }

    friend ostream &operator<<(ostream &os, FlatPizza &pizza)
    {
        os<<pizza.ime<<": ";
        for (int i = 0; i < 49; ++i) {
            if (pizza.sostojki[i]=='\0')
            {
                break;
            }
            os<<pizza.sostojki[i];
        }
        os<<", ";
        if(pizza.golemina==0)
        {
            os<<"small - ";
        }
        else if(pizza.golemina==1)
        {
            os<<"medium - ";
        }
        else
        {
            os<<"family - ";
        }
        os<<pizza.price()<<endl;
        return os;
    }

    Size getGolemina()
    {
        return golemina;
    }
};


class FoldedPizza : public Pizza{
private:
    bool daliBelo;
public:
    FoldedPizza(char *ime=new char[0],char *sostojki=new char[0],double cena=0.0, bool daliBelo = true)
            : Pizza(ime,sostojki,cena)
    {
        this->daliBelo = daliBelo;
    }
    void setWhiteFlour(bool s)
    {
        daliBelo = s;
    }
    double price()
    {
        if(daliBelo)
        {
            return cena*1.10;
        }
        return cena*1.30;
    }

    friend ostream &operator<<(ostream &os, FoldedPizza &pizza) {
        os<<pizza.ime<<": "<<pizza.sostojki<<", ";
        if(pizza.daliBelo)
        {
            os<<"wf - ";
        }
        else
        {
            os<<"nwf - ";
        }
        os<<pizza.price()<<endl;
        return os;
    }
};

void expensivePizza (Pizza **p, int n)
{
    Pizza *maxPizza = p[0];
    for (int i = 0; i < n; ++i)
    {
        if (*maxPizza < *p[i])
        {
            maxPizza=p[i];
        }
    }
    if (dynamic_cast<FoldedPizza *>(maxPizza)!= NULL)
    {
        cout<<dynamic_cast<FoldedPizza &>(*maxPizza);
    }else{
        cout<<dynamic_cast<FlatPizza &>(*maxPizza);
    }



}

// Testing

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza fp(name, ingredients, inPrice, (Size)s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp1;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp2;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout<<"Lower price: "<<endl;
        if(*fp1<*fp2)
            cout<<fp1->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp1<*fp3)
            cout<<fp1->price()<<endl;
        else cout<<fp3->price()<<endl;

        if(*fp4<*fp2)
            cout<<fp4->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp3<*fp4)
            cout<<fp3->price()<<endl;
        else cout<<fp4->price()<<endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name,20);

                cin.getline(ingredients,100);
                cin >> inPrice;
                int s;
                cin>>s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name,20);
                cin.getline(ingredients,100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza (name, ingredients, inPrice);
                if(j%2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi,num_p);


    }
    return 0;
}
