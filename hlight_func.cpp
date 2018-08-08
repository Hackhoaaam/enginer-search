#include "Highlight.h"
#include "Header.h"
void color_print(string &text) {
	//print the word but not the associated punctuation
	string punct;
	if (ispunct(text[text.size() - 1])) {
		punct = text[text.size() - 1];
		text.erase(text.size() - 1, 1);
	}
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 2);
	cout << text;
	SetConsoleTextAttribute(h, 15);
	if (!punct.empty())cout << punct;//print the punctuation seperately
}

void to_lower(string &text) {
	int n = text.size();
	for (int i = 0; i < n; i++)
		text[i] = tolower(text[i]);
}
void remove_puctuation(string &word) {
	if (word.size() <= 1)return;
	int last_char = word.size() - 1;
	if (int(word[last_char])>0 && int(word[last_char])<127)
		if (ispunct(word[last_char])) {
			word.erase(last_char, 1);
		}
}
void normalize(string &text) {
	//cout << "$" << text << "$" << endl;
	to_lower(text);
	//cout << "lower" << endl;
	remove_puctuation(text);
	//cout << "remove punct" << endl;
}

bool is_qry(vector<string> queries, int n, string word) {
	normalize(word);
	for (int i = 0; i < n; i++)if (word == queries[i]) return true;
	return false;
}

void highLightQueries(vector<string> queries, int n, string text) {
	unsigned int sz = text.size();
	while (!text.empty()) {
		//if a word can not be found inside text
		if (text.find(" ") < 0 || text.find(" ") > sz) {
			if (is_qry(queries, n, text)) color_print(text);
			else cout << text;
			cout << endl;
			return;
		}
		//cout << "get word" << endl;
		string word = text.substr(0, text.find(" "));
		//cout << "check query"<<endl;
		if (is_qry(queries, n, word)) {
			color_print(word);
			cout << " ";
		}
		else cout << word << " ";
		//cout << "erase" << endl;
		text.erase(0, text.find(" ") + 1);
	}
}

void hightlight_para(string file_name, int para, vector<string> query) {
	int n = query.size();
	int pos = 1;
	string text;
	string file = "C:\\Users\\Light\\Downloads\\CS163-Project-Data\\CS163-Project-Data\\";
	ifstream read(file + file_name + ".txt");
	if (!read.is_open())cout << "ERROR: CANT OPEN FILE" << endl;
	//while not end of file, we still be able to getline into text
	while (getline(read, text)) {
		//at correct position
		if (pos == para) {
			//cout << "HL: "; system("pause");
			highLightQueries(query, n, text);
			while (text != "") {
				//cout << "HL: "; system("pause");
				if (getline(read, text)) highLightQueries(query, n, text);
				else return;
			}
			return;
		}
		//move to correct position
		if (text == "")pos++;
	}
	read.close();
}
