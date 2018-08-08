#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <iostream>
#include <conio.h>
#include <string>
#include <Windows.h>
#include <cstring>
#include <fstream>
#include <vector>
#include <sstream>
#include"Highlight.h"
#include"Operator.h"
#include"UI.h"

using namespace std;

//I've deleted paragraph structure and replace with int the index is the position and the value is the frequency
struct keyblock {
	string title;
	int frequency = 1;
	int para[150];//use arr because I'm afraid of using pointer :)) 
	keyblock() { for (int i = 0; i < 12; ++i) para[i] = 0; };
};

struct node {
	string key;
	vector<keyblock> data;
	node* left;
	node* right;
	int height;
};

class AVLtree {
private:
	node * root;
	void traversePreorder(node* N);
	void printPreorder(node* N);
	void printPostorder(node* N);
	void printInorder(node* N);
	node* insert(node* N, string keyword, keyblock data, int position);
	node *search(node *cur, string x);
	void removeAllInternall(node *&N);
public:
	~AVLtree();
	AVLtree();
	void Sort();
	void removeAll();
	node* rotateLeft(node* x);
	node* rotateRight(node* y);
	void insert(string keyword, keyblock data, int position);
	int getHeight(node*N);
	int checkBalance(node* N);
	void printPreorder();
	void printPostorder();
	void printInorder();
	bool search(string x);
	void LoadStopWord();
	node * searchPriceAndHash(string key);
};
//some plugin function =))
int Max(int a, int b);
void LoadFile(string path, AVLtree &a);
string itos(int n);
void fileprocess(ifstream &fin, AVLtree &a, string filename);
void lowercase(string &classname);
bool strcmpi(string source, string des);
void keyblockSort(vector<keyblock> &a);
vector<string> Filter(string in);
void CreateFile_Summary(string path, string a);
void ReLoadFile(string path, AVLtree&a);
void CreateFileHistory(string path, string query)
//input processing
vector<string> splitkeywords(string query, AVLtree stopwords);
void normal_output(vector<string> input, AVLtree &a);
void merge(vector<keyblock>&result, vector<keyblock>query);
void print_vector(vector <keyblock> result, vector<string> query);
int max_index(int a[100]);
#endif
