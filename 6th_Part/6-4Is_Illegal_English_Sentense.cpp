/*****************************************************************************************************
*Ӣ���ķ�����
* Sentence:
*		Restrict Noun Verb Over
*		Sentence Conjunction Sentence Over
* Conjunction:
*		"and"
*		"but"
*		"or"
* Noun:
*		"birds"
*		"fish"
*		"cats"
* Verb:
*		"rule"
*		"fly"
*		"swim"
* Restrict:
*		"the"
* Over:
*		" ."
* ע�⣺��β�����ǰ��ӿո�
*****************************************************************************************************/
#include"../Head/std_lib_facilities.h"
int isFirsttoken =0;
void Capitalize();
string Noun();
string Verb();
string Restict();
string isConjunction();
string Sentense();

string Sentense()
{
	string sentense;
	string restrict = Restict();
	string noun = Noun();
	string verb = Verb();
	sentense = restrict + ' ' + noun + ' ' + verb;
	string isconjunction = isConjunction();
	if (isconjunction == ".")
	{
		return sentense = sentense + isconjunction;
	}
	else
	{
		return sentense = sentense + ' ' + isconjunction + ' ' + Sentense();
	}
}

void Capitalize()
{
	char ch;
	cin >> ch;
	if (ch<='z'&&ch>='a')
	{
		error("NOT CAPITALIZE THE FIRST NUMBER!");
	}
	else if (ch<='Z'&&ch>='A')
	{
		cin.putback(ch);
	}
}

string Noun()
{
	string s;
	cin >> s;
	if (s == "birds" || s == "cats" || s == "fish")
	{
		isFirsttoken++;
		return s;
	}
	else if (isFirsttoken==0&&(s == "Birds" || s == "Cats" || s == "Fish"))
	{
		isFirsttoken++;
		return s;
	}
	else
	{
		error("WRONG NOUN!");
	}
}

string Verb()
{
	string s_verb;
	cin >> s_verb;
	if (s_verb == "rule" || s_verb == "fly" || s_verb == "swim")
	{
		return s_verb;
	}
	else
	{
		error("WRONG VERBS!");
	}
}

string Restict()
{
	string s;
	cin >> s;
	if (s == "the" )
	{
		isFirsttoken++;
		return s;
	}
	else if (isFirsttoken==0&&(s=="The"))
	{
		isFirsttoken++;
		return s;
	}
	else
	{
		error("WRONG ARTICLE!");
	}
}

string isConjunction()
{
	string s;
	cin >> s;
	if (s == "and" || s == "but" || s == "or")
	{
		return s;
	}
	else if(s==".")
	{
		return s;
	}
	else
	{
		error("WRONG CONJUNCTION OR FULL STOP!");
	}
}

int main()
{
	try
	{
		Capitalize();	//�Ƿ�����ĸ��д
		cout << Sentense() << ' ' << "����Ӣ���ķ�����\n";
	}
	catch (const std::exception&err)
	{
		cout << "���䲻����Ӣ���ķ�����\n" << err.what() << '\n';
	}
}