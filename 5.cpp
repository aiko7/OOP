#include <iostream>
#include <cstring>
#include <exception>
#include <cstdlib>

using namespace std;

enum typeC
{
  standard,
  loyal,
  vip
};
const int MAX = 50;

class UserExistsException
{
private:
  char *text;

public:
  UserExistsException(const char *text)
  {
    this->text = new char[strlen(text) + 1];
    strcpy(this->text, text);
  }

  void print()
  {
    cout << text << endl;
  }
};

class Customer
{
private:
  char name[MAX];
  char email[MAX];
  typeC type;
  int basediscount = 10;
  const int additionaldiscount = 20;
  int n;

public:
  Customer() {}

  Customer(const Customer &c)
  {
    strcpy(name, c.name);
    strcpy(email, c.email);
    type = c.type;
    n = c.n;
    basediscount = c.basediscount;
  }

  Customer(const char *name, const char *email, typeC type, int n)
  {
    strcpy(this->name, name);
    strcpy(this->email, email);
    this->type = type;
    this->n = n;
  }

  typeC getType()
  {
    return type;
  }

  void setType(typeC type)
  {
    this->type = type;
  }

  int getN()
  {
    return n;
  }

  void setDiscount1(int basediscount)
  {
    this->basediscount = basediscount;
  }

  const char *getEmail() const
  {
    return email;
  }

  friend ostream &operator<<(ostream &os, Customer &c)
  {
    os << c.name << endl;
    os << c.email << endl;
    os << c.n << endl;

    switch (c.type)
    {
    case standard:
      os << "standard 0";
      break;
    case loyal:
      os << "loyal " << c.basediscount;
      break;
    case vip:
      os << "vip " << (c.basediscount + c.additionaldiscount);
      break;
    }
    os << "\n";
    return os;
  }

  Customer &operator=(const Customer &c)
  {
    if (this != &c)
    {
      strcpy(name, c.name);
      strcpy(email, c.email);
      type = c.type;
      n = c.n;
      basediscount = c.basediscount;
    }
    return *this;
  }
};

class FINKI_bookstore
{
private:
  Customer *customers;
  int n;

public:
  FINKI_bookstore() : customers(nullptr), n(0) {}

  FINKI_bookstore(const Customer *customers, int n)
  {
    this->n = n;
    this->customers = new Customer[n];
    for (int i = 0; i < n; i++)
    {
      this->customers[i] = customers[i];
    }
  }

  void setCustomers(const Customer *customers, int n)
  {
    delete[] this->customers;
    this->n = n;
    this->customers = new Customer[n];
    for (int i = 0; i < n; i++)
    {
      this->customers[i] = customers[i];
    }
  }

  void operator+=(const Customer &c)
  {
    for (int i = 0; i < n; i++)
    {
      if (strcmp(c.getEmail(), customers[i].getEmail()) == 0)
      {
        throw UserExistsException("The user already exists in the list!");
      }
    }

    Customer *newCustomers = new Customer[n + 1];
    for (int i = 0; i < n; i++)
    {
      newCustomers[i] = customers[i];
    }
    newCustomers[n] = c;

    delete[] customers;
    customers = newCustomers;
    n++;
  }

  friend ostream &operator<<(ostream &os, FINKI_bookstore &f)
  {
    for (int i = 0; i < f.n; i++)
    {
      os << f.customers[i];
    }
    return os;
  }

  void update()
  {
    for (int i = 0; i < n; i++)
    {
      if (customers[i].getType() == 0)
      {
        if (customers[i].getN() > 5)
        {
          customers[i].setType((typeC)1);
        }
      }
      else if (customers[i].getType() == 1)
      {
        if (customers[i].getN() > 10)
        {
          customers[i].setType((typeC)2);
        }
      }
    }
  }
    ~FINKI_bookstore()
    {
      delete[] customers;
    }
  };

  int main()
  {
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;

    if (testCase == 1)
    {
      cout << "===== Test Case - Customer Class ======" << endl;
      cin.ignore();
      cin.getline(name, MAX);
      cin.getline(email, MAX);
      cin >> tC;
      cin >> numProducts;
      cout << "===== CONSTRUCTOR ======" << endl;
      Customer c(name, email, (typeC)tC, numProducts);
      cout << c;
    }

    if (testCase == 2)
    {
      cout << "===== Test Case - Static Members ======" << endl;
      cin.ignore();
      cin.getline(name, MAX);
      cin.getline(email, MAX);
      cin >> tC;
      cin >> numProducts;
      cout << "===== CONSTRUCTOR ======" << endl;
      Customer c(name, email, (typeC)tC, numProducts);
      cout << c;

      c.setDiscount1(5);

      cout << c;
    }

    if (testCase == 3)
    {
      cout << "===== Test Case - FINKI-bookstore ======" << endl;
      FINKI_bookstore fc;
      int n;
      cin >> n;
      Customer customers[MAX];
      for (int i = 0; i < n; ++i)
      {
        cin.ignore();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC)tC, numProducts);
        customers[i] = c;
      }

      fc.setCustomers(customers, n);

      cout << fc << endl;
    }

    if (testCase == 4)
    {
      cout << "===== Test Case - operator+= ======" << endl;
      FINKI_bookstore fc;
      int n;
      cin >> n;
      Customer customers[MAX];
      for (int i = 0; i < n; ++i)
      {
        cin.ignore();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC)tC, numProducts);
        customers[i] = c;
      }

      fc.setCustomers(customers, n);
      cout << "OPERATOR +=" << endl;
      cin.ignore();
      cin.getline(name, MAX);
      cin.getline(email, MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC)tC, numProducts);
      fc += c;

      cout << fc;
    }

    if (testCase == 5)
    {
      cout << "===== Test Case - operator+= (exception) ======" << endl;
      FINKI_bookstore fc;
      int n;
      cin >> n;
      Customer customers[MAX];
      for (int i = 0; i < n; ++i)
      {
        cin.ignore();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC)tC, numProducts);
        customers[i] = c;
      }

      fc.setCustomers(customers, n);
      cout << "OPERATOR +=" << endl;
      cin.ignore();
      cin.getline(name, MAX);
      cin.getline(email, MAX);
      cin >> tC;
      cin >> numProducts;

      try
      {
        Customer c(name, email, (typeC)tC, numProducts);
        fc += c;
      }
      catch (UserExistsException &e)
      {
        e.print();
      }

      cout << fc;
    }

    if (testCase == 6)
    {
      cout << "===== Test Case - update method  ======" << endl
           << endl;
      FINKI_bookstore fc;
      int n;
      cin >> n;
      Customer customers[MAX];
      for (int i = 0; i < n; ++i)
      {
        cin.ignore();
        cin.getline(name, MAX);
        cin.getline(email, MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC)tC, numProducts);
        customers[i] = c;
      }

      fc.setCustomers(customers, n);

      cout << "Update:" << endl;
      fc.update();
      cout << fc;
    }

    return 0;
  }
