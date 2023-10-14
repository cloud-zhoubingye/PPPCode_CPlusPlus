#include"../Head/Date.h"
namespace Namespace_Book
{
	enum class Genre
	{
		Fiction, Nonfiction, Periodical, Biography, Children
	};
	class Book
	{
	public:
		Book();
		Book(string Ibsn, string Name, string Author, Genre genre, bool isLent);
		string IBSN() { return Ibsn; }
		string name() { return Name; }
		string author() { return Author; }
		Genre genre() { return MyGenre; }
		bool islent() { return isLent; }
		void lend_it() { isLent = true; }
		string Ibsn;
		string Name;
		string Author;
		Genre MyGenre;
		bool isLent;
		bool IBSN_isvalid();
	};
	Book deault_book()
	{
		Book book{ "0000-0000-0000-0","NAME","AUTHOR",Genre::Fiction,false };
		return book;
	};
	Book::Book()
		:Ibsn{ deault_book().IBSN() }, Name{ deault_book().name() }, Author{ deault_book().author() }, MyGenre{ deault_book().genre() }, isLent{ deault_book().islent() }
	{

	}
	Book::Book(string Ibsn, string Name, string Author, Genre genre, bool isLent)
		:Ibsn{ Ibsn }, Name{ Name }, Author{ Author }, MyGenre{ genre }, isLent{ isLent }
	{
		if (!IBSN_isvalid())
		{
			cout << "WRONG";
		}

	}
	bool Book::IBSN_isvalid()
	{
		char* ch = (char*)malloc(sizeof(char) * (Ibsn.length() + 1));
		strcpy_s(ch, Ibsn.length() + 1, Ibsn.c_str());
		//���ǰ��������
		if (ch != NULL)
		{
			size_t i = 0;
			for (size_t times = 0; times < 3; times++)
			{
				for (i; i < strlen(ch); i++)
				{
					if (ch[i] >= '0' && ch[i] <= '9')
					{
						continue;
					}
					else if (ch[i] == '-')
					{
						i++;
						break;
					}
					else
					{
						return false;
					}
				}
			}
			//���һλ��һ�����ֻ���һ����ĸ
			if ((ch[i] >= '0' && ch[i] <= '9') || (ch[i] >= 'a' && ch[i] <= 'z'))
			{
				return true;
			}
		}

		return false;
	}
	bool operator==(Book book1, Book book2)
	{
		if (book1.IBSN() == book2.IBSN())
		{
			return true;
		}
		return false;
	}
	bool operator!=(Book book1, Book book2)
	{
		if (book1.IBSN() == book2.IBSN())
		{
			return false;
		}
		return true;
	}
	ostream& operator<<(ostream& os, Genre genre)
	{
		switch (genre)
		{
		case Genre::Fiction:
			os << "Fiction";
			break;
		case Genre::Nonfiction:
			os << "Nonfiction";
			break;
		case Genre::Periodical:
			os << "Periodical";
			break;
		case Genre::Biography:
			os << "Biography";
			break;
		case Genre::Children:
			os << "Children";
			break;
		}
		return os;
	}
	ostream& operator<<(ostream& os, Book book)
	{
		os << book.IBSN() << '\n'
			<< book.name() << '\n'
			<< book.author() << '\n'
			<< book.genre() << '\n';
		if (book.islent())
		{
			os << "Already Lent" << '\n';
		}
		else
		{
			os << "Not Lend" << '\n';
		}
		return os;
	}
}
namespace Namespace_Patron
{
	class Patron
	{
	public:
		Patron();
		Patron(string Reader_name, string Lisence_number, double Late_fee);
		string reader_name() { return Reader_name; }
		string lisence_number() { return Lisence_number; }
		double late_fee() { return Late_fee; }
		void set_late_fee(double fee) { Late_fee = fee; }
		bool isArrearage() { if (Late_fee == 0)return false; else return true; }
	private:
		string Reader_name;
		string Lisence_number;
		double Late_fee;
	};
	Patron default_patron()
	{
		Patron patron{ "READER_NAME","LISENCE_NUMBER",0.0 };
		return patron;
	}
	Patron::Patron()
		:Reader_name{ default_patron().reader_name() }, Lisence_number{ default_patron().lisence_number() }, Late_fee{ default_patron().late_fee() }
	{

	}
	Patron::Patron(string Reader_name, string Lisence_number, double Late_fee)
		:Reader_name{ Reader_name }, Lisence_number{ Lisence_number }, Late_fee{ Late_fee }
	{

	}
}
namespace Namespace_Library
{
	struct Transaction
	{
		Namespace_Book::Book book;
		Namespace_Patron::Patron patron;
		Namespace_Date::Date borrow_date;
	};
	class Library
	{
		bool islogged(Transaction adding_transaction);
		bool is_book_available(Transaction adding_transaction);
	public:
		void add_book(Namespace_Book::Book adding_book);
		void add_reader(Namespace_Patron::Patron adding_patron);
		void borrow_book(Transaction adding_transaction);
	private:
		vector<Namespace_Book::Book>book;
		vector<Namespace_Patron::Patron>patron;
		vector<Transaction>transaction;
	};

	void Library::add_book(Namespace_Book::Book adding_book)
	{
		book.push_back(adding_book);
	}
	void Library::add_reader(Namespace_Patron::Patron adding_patron)
	{
		patron.push_back(adding_patron);
	}
	void Library::borrow_book(Transaction adding_transaction)
	{
		islogged(adding_transaction);
		transaction.push_back(adding_transaction);
		adding_transaction.book.lend_it();
	}
	bool Library::is_book_available(Transaction adding_transaction)
	{
		for (size_t i = 0; i < book.size(); i++)
		{
			if (book[i] == adding_transaction.book)
			{
				if (!book[i].islent())
				{
					return true;
				}
			}
		}
	}
	bool Library::islogged(Transaction adding_transaction)
	{
		if (is_book_available(adding_transaction))
		{
			if (!adding_transaction.patron.isArrearage())
			{
				return true;
			}
			else
			{
				cout << "Sorry: You are arrearaged!\n";
			}
		}
		else
		{
			cout << "Sorry: Book not available!\n";
		}
		return false;
	}
}



int main()
{
	Namespace_Book::Book my__book{ "243421-12321-2321-a","bookname","author",Namespace_Book::Genre::Nonfiction,false };
		cout << my__book;
}