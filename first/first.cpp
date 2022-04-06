//Дано предложение, состоящее из слов, разделенных запятой или пробелами.
//Составить частотный словарь слов, указав, сколько раз данное слово встретилось в предложении.
//При этом изменить предложение: 
//-удалив повторные вхождения слов и вставив перед первым вхождением слова подстроку вида: 
//(Число), где - Число – определяет количество таких слов в предложении.

//Реализация через string

#include <iostream>
#include <string>
#include <map>
#include <windows.h>

using namespace std;

void createLib(string text, map <string, int>& library)
{
	string word = "";
	for (int i = 0; i < text.size(); i++)
	{
		if ((text[i] != ' ') && (text[i] != ','))
		{
			word += text[i];
			if (i == (text.size() - 1))
			{
				if (library.count(word) == 0) library.insert(make_pair(word, 1));
				else library[word]++;
			}
		}
		else if ((word != "") && (library.count(word) == 0))
		{
			library.insert(make_pair(word, 1));
			word = "";
		}
		else if (word != "")
		{
			library[word]++;
			word = "";
		}
	}
}

void outputLib(map <string, int> library)
{
	cout << "Частотный словарь слов:" << endl;
	map <string, int> ::iterator it = library.begin();
	for (; it != library.end(); it++)
	{
		cout << it->first << ": " << it->second << endl;
	}
}

void change(string text, map <string, int> library)
{
	map <string, int>::iterator it = library.begin();
	for (; it != library.end(); it++)
	{
		int idx = text.find(it->first);
		string add = "(" + to_string(it->second) + ")";
		text.resize(text.size() + add.size());
		text.insert(idx, add);
	}
	it = library.begin();
	for (; it != library.end(); it++)
	{
		if (it->second == 1) continue;
		int idx = 0;
		int start = text.find(it->first, idx);
		while (start != string::npos)
		{
			if (text[start - 1] != ')')
			{
				//text.replace(start, (it->first).size(), "");
				text.erase(start, (it->first).size() + 1);
			}
			idx += 1;
			start = text.find(it->first, idx);
		}
	}
	cout << text;
}


int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string text;
	getline(cin, text);
	map <string, int> library;
	createLib(text, library);
	outputLib(library);
	change(text, library);
	return 0;
}
