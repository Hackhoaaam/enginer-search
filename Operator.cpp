#include"Operator.h"
#include"Header.h"
#include<string>
#include"Highlight.h"

bool is_txt(string text) {
	int txt = text.find(":txt");
	if (txt <= 0 || txt>text.size())return false;
	if (text[txt - 1] == ' ')return false;
	else return true;
}

bool is_wildcard(string text) {
	int card = text.find("*");
	if (card<0 || card>text.size())return false;
	for (int i = 0; i < card; i++) if (text[i] != ' ')
		return true;
	for (int i = card + 1; i < text.size(); i++)
		if (text[i] != ' ')
			return true;
	return false;
}

bool is_currency(string text) {
	int money = text.find("$");
	if (money < 0 || money>text.size())return false;
	if (text.size() == money + 1)return false;
	if (isdigit(text[money + 1]))return true;
	else return false;
}

bool is_hashtag(string text) {
	int tag = text.find("#");
	if (tag < 0 || tag > text.size()) return false;
	if (text.size() == tag + 1)return false;
	if (text[tag + 1] != ' ')return true;
	else return false;
}

bool is_title(string text) {
	int tit = text.find("intitle:");
	if (tit != 0)return false;
	for (int i = tit + 8; i < text.size(); i++)
		if (text[i] != ' ')return true;
	return false;
}

bool is_exclude(string text) {
	bool fw = false;
	int excl = text.find("-");
	if (excl <= 0 || excl > text.size())return false;
	if (text[excl - 1] != ' ')return false;
	for (int i = 0; i < excl - 1; i++)
		if (text[i] != ' ') fw = true;
	for (int i = excl + 1; i < text.size() && fw == true; i++)
		if (text[i] != ' ') return true;
	return false;
}

bool is_OR(string text) {
	bool fw = false;//first word
	int And = -1;//or operator position
	for (int i = 0; i < text.size(); i++) {
		if (text[i] != ' ' && fw == false) {
			fw = true;
			And = text.find("OR", i + 1);
			if (And < 0 || And > text.size())return false;
			else {
				i += And +2;
				if (i > text.size())return false;
			}
		}
		if (And != -1 && text[i] != ' ')return true;
	}
	return false;
}

bool is_included(string text) {
	bool fw = false;
	int incl = text.find("+");
	if (incl <= 0 || incl > text.size() || text[incl - 1] != ' ') return false;
	for (int i = 0; i < incl - 1; ++i)
		if (text[i] != ' ') fw = true;
	for (int i = incl + 1; i < text.size() && fw == true; i++)
		if (text[i] != ' ') return true;
	return false;
}

bool isWildCard(string query)
{
	if (isExact(query))
	{
		if (query.find('*') != -1) return true;
		else return false;
	}
	return false;
}

bool isExact(string query)
{
	int start = query.find('"');
	int end = query.find('"', start + 1);
	if (start != -1 && end != -1)
		return true;
	else return false;
}
//write some function
bool isExist(string keyword, keyblock &tmp)
{
	string path = "D:\\Gruop02\\CS163-Project-Data\\";
	ifstream fin; string fullpath = path + tmp.title + ".txt";
	fin.open(fullpath);
	string sample;
	int pos = 0;
	bool check = false;
	while (!fin.eof())
	{
		getline(fin, sample);
		lowercase(sample);
		if (sample.empty())
			++pos;
		if (sample.find(keyword) != -1)
		{
			tmp.frequency++;
			tmp.para[pos]++;
			check = true;
		}
	}
	fin.close();
	return check;
}
