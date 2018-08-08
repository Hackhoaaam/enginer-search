#ifndef HIGHLIGHT
#define HIGHLIGHT

//just use hightlight_para (string name_of_the_file.txt, int position_of_the_paragraph, string input_query)

#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <Windows.h>
#include <cstring>
#include <vector>

					
void color_print(string &text);				//print the word in color
void normalize(string &text);				//lower case the word + remove punctuation
void to_lower(string &text);			
void remove_puctuation(string &word);		
bool is_qry(vector<string> queries, int n, string word);							//check if a word is == query							
void highLightQueries(vector<string> queries, int n, string text);					//highlight queries in the text
void hightlight_para(string file_name, int para, vector<string> queries);			//highlight the all the queries in a paragraph (para th) from file_name.txt
#endif // !HIGHLIGHT

