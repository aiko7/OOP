#include <iostream>
#include <cstring>
using namespace std;

class Book
{
protected:
	char ISBN[20];
	char name[50];
	char author[30];
	float price;

public:
	Book()
	{
	}
	Book(const char *ISBN, const char *name, const char *author, float price)
	{
		strcpy(this->ISBN, ISBN);
		strcpy(this->name, name);
		strcpy(this->author, author);
		this->price = price;
	}

	void setISBN(const char *ISBN)
	{
		strcpy(this->ISBN, ISBN);
	}

	virtual float bookPrice() const
	{
		return price;
	}

	virtual int type() = 0;

	bool operator<(const Book &other) const
	{
		return bookPrice() < other.bookPrice();
	}

	bool operator>(const Book &other) const
	{
		return bookPrice() > other.bookPrice();
	}

	friend ostream &operator<<(ostream &x, const Book &b)
	{
		x << b.ISBN << ": " << b.name << ", " << b.author << " " << b.bookPrice() << endl;
		return x;
	}
};

class OnlineBook : public Book
{
private:
	char *url;
	int size;

public:
	OnlineBook(const char *ISBN, const char *name, const char *author, float price, const char *url, int size) : Book(ISBN, name, author, price)
	{
		this->url = new char[strlen(url) + 1];
		strcpy(this->url, url);
		this->size = size;
	}

	float bookPrice() const override
	{
		if (size > 20)
		{
			return (price * 1.2);
		}
		return price;
	}
	int type()
	{
		return 1;
	}
};

class PrintBook : public Book
{
private:
	float weight;
	bool inStock;

public:
	PrintBook(const char *ISBN, char *name, const char *author, float price, float weight, bool inStock) : Book(ISBN, name, author, price)
	{
		this->weight = weight;
		this->inStock = inStock;
	}

	float bookPrice() const override
	{
		if (weight > 0.7)
		{
			return (price * 1.15);
		}
		return price;
	}
	int type()
	{
		return 2;
	}
};

void mostExpensiveBook(Book **books, int n)
{
	cout << "FINKI-Education" << endl;
	int onlinebooks = 0;
	int printbooks = 0;
	float maxprice = 0;
	Book *book = nullptr;
	for (int i = 0; i < n; i++)
	{
		if (books[i]->type() == 1)
		{
			onlinebooks++;
		}
		else if (books[i]->type() == 2)
		{
			printbooks++;
		}

		if (books[i]->bookPrice() > maxprice)
		{
			maxprice = books[i]->bookPrice();
			book = books[i];
		}
	}
	cout << "Total number of online books: " << onlinebooks << endl;
	cout << "Total number of print books: " << printbooks << endl;
	cout << "The most expensive book is:\n"
		 << *book << endl;
}

int main()
{

	char isbn[20], title[50], author[30], url[100];
	int size, tip;
	float price, weight;
	bool inStock;
	Book **books;
	int n;

	int testCase;
	cin >> testCase;

	if (testCase == 1)
	{
		cout << "====== Testing OnlineBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++)
		{
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> url;
			cin >> size;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new OnlineBook(isbn, title, author, price, url, size);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 2)
	{
		cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
		cin >> isbn;
		cin.get();
		cin.getline(title, 50);
		cin.getline(author, 30);
		cin >> price;
		cin >> url;
		cin >> size;
		cout << "CONSTRUCTOR" << endl;
		OnlineBook ob1(isbn, title, author, price, url, size);
		cout << ob1 << endl;
		cout << "COPY CONSTRUCTOR" << endl;
		OnlineBook ob2(ob1);
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
		cout << "OPERATOR =" << endl;
		ob1 = ob2;
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
	}
	if (testCase == 3)
	{
		cout << "====== Testing PrintBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++)
		{
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> weight;
			cin >> inStock;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 4)
	{
		cout << "====== Testing method mostExpensiveBook() ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++)
		{

			cin >> tip >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			if (tip == 1)
			{

				cin >> url;
				cin >> size;

				books[i] = new OnlineBook(isbn, title, author, price, url, size);
			}
			else
			{
				cin >> weight;
				cin >> inStock;

				books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			}
		}

		mostExpensiveBook(books, n);
	}

	for (int i = 0; i < n; i++)
		delete books[i];
	delete[] books;
	return 0;
}
