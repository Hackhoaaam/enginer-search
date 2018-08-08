#include"Header.h"
#include"Highlight.h"

AVLtree::AVLtree() {
	root = NULL;
}

AVLtree::~AVLtree() {
	removeAllInternall(root);
}

int AVLtree::getHeight(node* N) {
	if (N == NULL) {
		return 0;
	}
	return N->height;
}

node* AVLtree::rotateLeft(node* x) {
	node* y = x->right;
	node* z = y->left;
	y->left = x;
	x->right = z;
	x->height = Max(getHeight(x->left), getHeight(x->right)) + 1;
	y->height = Max(getHeight(y->left), getHeight(y->right)) + 1;
	return y;
}

node* AVLtree::rotateRight(node* x) {
	node* y = x->left;
	node* z = y->right;
	y->right = x;
	x->left = z;
	x->height = Max(getHeight(x->left), getHeight(x->right)) + 1;
	y->height = Max(getHeight(y->left), getHeight(y->right)) + 1;
	return y;
}

int AVLtree::checkBalance(node* N) {
	if (N == NULL) {
		return 0;
	}
	return getHeight(N->left) - getHeight(N->right);
}

void AVLtree::insert(string keyword, keyblock data, int position) {
	root = insert(root, keyword, data, position);
}
//Just fix today 26/7 but dont know it word or not =))
node* AVLtree::insert(node* N, string keyword, keyblock data, int position) {
	if (N == NULL) {
		N = new node;
		N->key = keyword;
		if(!data.title.empty())
			N->data.push_back(data);
		N->left = NULL;
		N->right = NULL;
		N->height = 1;
		return N;
	}
	if (keyword == N->key)
	{
		int size = N->data.size();
		for (int i = 0; i <size; ++i)
		{
			if (data.title == N->data[i].title)
			{
				N->data[i].frequency++;//update frequency
				N->data[i].para[position]++;//update frequency in the paragraph

			}
			else if (i == size - 1)
				//forget to update the next title =)). This line is to update the next title
				N->data.push_back(data);
		}

		return N;
	}
	if (keyword < N->key) {
		N->left = insert(N->left, keyword, data, position);
	}
	else N->right = insert(N->right, keyword, data, position);
	N->height = Max(getHeight(N->left), getHeight(N->right)) + 1;
	int balance = checkBalance(N);
	if (balance > 1 && keyword < N->left->key) {
		return rotateRight(N);
	}
	if (balance < -1 && keyword > N->right->key) {
		return rotateLeft(N);
	}
	if (balance > 1 && keyword > N->left->key) {
		N->left = rotateLeft(N->left);
		return rotateRight(N);
	}
	if (balance < -1 && keyword < N->right->key) {
		N->right = rotateRight(N->right);
		return rotateLeft(N);
	}
	return N;
}

int Max(int a, int b) {
	return ((a > b) ? a : b);
}

void AVLtree::printPreorder() {
	printPreorder(root);
}

void AVLtree::printPreorder(node* N) {
	if (N != NULL) {
		cout << N->key << "/" << N->height << "    ";
		printPreorder(N->left);
		printPreorder(N->right);
	}
}

void AVLtree::printInorder() {
	printInorder(root);
}

void AVLtree::printInorder(node* N) {
	if (N != NULL) {
		printInorder(N->left);
		cout << N->key << "/" << N->height << "    ";
		printInorder(N->right);
	}
}

void AVLtree::printPostorder() {
	printPostorder(root);
}

void AVLtree::printPostorder(node* N) {
	if (N != NULL) {
		printPostorder(N->left);
		printPostorder(N->right);
		cout << N->key << "/" << N->height << "    ";
	}
}

node* AVLtree::search(node *cur, string x)
{
	if (cur == NULL) return NULL;
	if (cur->key == x) return cur;
	if (cur->key > x) return search(cur->left, x);
	return search(cur->right, x);
}

bool AVLtree::search(string x,node*&tmp)
{
	tmp = search(root, x);
	if (tmp == NULL) return false;
	if (tmp->key == x) return true;
	return false;
}

void AVLtree::LoadStopWord()
{
	ifstream fin;
	string tmp;
	keyblock sample;
	fin.open("D:\\Gruop02\\Project\\Stopword.txt");
	if (fin.is_open()) {
		while (!fin.eof()) {
			getline(fin, tmp, '\n');
			lowercase(tmp);
			insert(tmp, sample, 0);
		}
		fin.close();
	}
	//tree.printLevelOrder();

}

// now I'll make a function to make the file name
string itos(int n)
{
	stringstream ss;
	ss << n;
	return ss.str();
}
// Just write today 26/7
//chưa sửa nữa nè.
void LoadFile(string path, AVLtree &a)//ctreate filename
{
	ifstream fin;
	for (int i = 1; i <=25 ; ++i)//because we have 25 group =))
	{
		string filename;
		int j;
		int limit;
		if (i == 3 || i == 5 || i == 11 || i == 12 || i == 15 || i == 17 || i == 25)
		{
			j = 0;
			limit = 99;
		}
		else if (i == 7)
		{
			j = 1;
			limit = 112;
		}
		else if (i == 19)
		{
			j = 1;
			limit = 101;
		}
		//else if (i == 5||i==14||i==15) continue;
		else
		{
			j = 1;
			limit = 100;
		}
		for (; j <= 100; ++j)
		{
			if (i < 10 || j < 10)
			{
				string tmp;
				if (i < 10)
					tmp = "Group0" + itos(i);
				else
					tmp = "Group" + itos(i);
				if (j < 10)
					tmp += "News0" + itos(j);
				else
					tmp += "News" + itos(j);
				filename = tmp;
			}

			else
			{
				string tmp = "Group" + itos(i) + "News" + itos(j);
				filename = tmp;
			}
			string fullpath = path + filename + ".txt";
			//CreateFile_Path(path, filename);
			fin.open(fullpath);
			if (fin.is_open())//need to put a funtion to read and insert =))
				fileprocess(fin, a, filename);
		}
	}
	a.Sort();
}
//now we need to write a function dosth =))
//Just write not yet check
void fileprocess(ifstream &fin, AVLtree &a, string filename)
{
	char sample[20];
	int para = 0;
	//if (fin.is_open()) {
		while (!fin.eof()) {// this after this step we still need to update sth =))
			int pos = fin.tellg();
			fin.get(sample, 20, ' ');
			fin.ignore(1000, ' ');
			if (strlen(sample) == 0)
				break;
			string keyword;
			for (int i = 0; i < strlen(sample); ++i)
			{
				if (sample[0] == '\n'&&sample[1] == '\n')
				{
					++para;
					fin.seekg(pos+2);
				}
				if (sample[i] == '\n')//try to find location of the next word
				{

					fin.seekg(pos + i + 1);
					break;
				}
				if (sample[i] <= 255 && sample[i] >= 0)
				{
					if (sample[i] == 39 && sample[i + 1] == 's')//remove 's
						i += 2;
					else if (!ispunct(sample[i])&&!isspace(sample[i])||sample[i]=='#'||sample[i]=='$')
						keyword += sample[i];
				}
			}
			if (!keyword.empty())
			{
				keyblock data;
				data.title = filename;
				//right here we need to initialize a keyblock in order to put it to vector
				//if it doesn't exist, if it exist we may need a variable of postion to access quickly
				//to an arr
				data.para[para] = 1;

				lowercase(keyword);//convert to lowercase
				a.insert(keyword, data, para);
			}

		}
		cout << filename << endl;
		fin.close();
	//}
}

// we need some sort function to search when we done with processing the file
// we will need to process the node which mean sort by descending
void keyblockSort(vector<keyblock> &a)
{
	int j;
	keyblock k;
	int n = a.size();
	for (int i = 1; i < n; ++i)
	{
		k.frequency = a[i].frequency;
		j = i - 1;
		while (j >= 0 && a[j].frequency < k.frequency)
		{
			a[j + 1] = a[j];
			--j;
		}
		a[j + 1] = k;

	}
}
/*void paragraphSort(vector<paragraph> &a)
{
int j;
paragraph k;
int n = a.size();
for (int i = 1; i < n; ++i)
{
k.frequency = a[i].frequency;
j = i - 1;
while (j >= 0 && a[j].frequency < k.frequency)
{
a[j + 1] = a[j];
--j;
}
a[j + 1] = k;
}
}*/
//traverse preorder to sort =))
void AVLtree::Sort() {//by traverse preoder
	traversePreorder(root);
}
//not yet check if it work or not but the sort function has been checked and it worked well. 
void AVLtree::traversePreorder(node* N) {
	if (N != NULL) {
		keyblockSort(N->data);
		traversePreorder(N->left);
		traversePreorder(N->right);
	}
}
//need a function to convert all characters in the string to uppercase or lowercase 
//because we dont have the function to compare and ignore the case-sensitive in string
void lowercase(string &classname)
{
	for (int i = 0; i < classname.length(); ++i)
	{
		classname[i] = tolower(classname[i]);
	}
}

bool strcmpi(string source, string des)
{
	lowercase(source);
	if (source == des) return true;
	else return false;
}
//need to write a function to delete all the tree lol =))
void AVLtree::removeAllInternall(node* &N)
{
	if (N == NULL)
		return;
	removeAllInternall(N->left);
	removeAllInternall(N->right);
	delete N;
	N = NULL;
	//dont need to deallocate  the vector beacause vector is already had the destructor
}

void AVLtree::removeAll()
{
	removeAllInternall(root);
}

//below here is the place for 
vector<string> Filter(string in) {
	AVLtree tree_sw;
	ifstream fin;
	string tmp;
	keyblock sample;
	int l = 0, r, i, temp_sw = 0;
	vector<string> split;
	string temp;
	int length = in.length();
	tree_sw.LoadStopWord();

	for (i = 0; i < length; i++) {
		if (in[i] == ' ') {
			r = i;
			temp = in.substr(l, (r - l));
			l = i + 1;
			lowercase(temp);
			if (!tree_sw.search(temp) || temp == "and"&&temp_sw == 0 || temp == "or"&&temp_sw == 0) {
				if (temp == "and" || temp == "or")
					temp_sw++;
				split.push_back(temp);
			}
		}
	}
	temp = in.substr(l, (i - l));
	lowercase(temp);
	if (!tree_sw.search(temp) || temp == "and"&&temp_sw == 0 || temp == "or"&&temp_sw == 0) {
		if (temp == "and" || temp == "or")
			temp_sw++;
		split.push_back(temp);
	}
	return split;
}


node * AVLtree::searchPriceAndHash(string key) {
	node* tmp = search(root, key);
	return out;
}


void ReLoadFile(string path, AVLtree&a) {
	ifstream fin, fin_file;
	string tmp = path;
	path += "summary.txt";
	fin.open(path);

	if (fin.is_open()) {
		while (!fin.eof()) {
			string filename;
			getline(fin,filename, '\n');
			string fullpath = tmp + filename + ".txt";
			fin_file.open(fullpath);
			if (fin_file.is_open())
				fileprocess(fin_file, a, filename);
		}
		fin.close();
	}
	a.Sort();
}

void CreateFile_Summary(string path, string a) {
	ofstream fout;
	path += "summary.txt";
	fout.open(path, ios::app);
	if (fout.is_open())
	{
		fout << a << endl;
		fout.close();
	}
}

//save the history search
void CreateFileHistory(string path,string query) {
	ofstream fout;
	fout.open(path, ios::app);
	if (fout.is_open()) {
		fout << query << endl;
		fout.close();
	}
}
//below here is the place for 
//input processing
vector<string> splitkeywords(string query, AVLtree stopwords) {
	int l = 0, r, i;
	vector<string> split;
	string temp;
	node*dumb=NULL;
	int length = query.length();
	for (i = 0; i<length; i++) {
		if (query[i] == ' ') {
			r = i;
			temp = query.substr(l, (r - l));
			l = i + 1;
			lowercase(temp);
			if (!stopwords.search(temp,dumb)) {
			split.push_back(temp);
			}
		}
	}
	temp = query.substr(l, (i - l));
	lowercase(temp);
	if (!stopwords.search(temp,dumb)) {
		split.push_back(temp);
	}
	delete dumb;
	return split;
}
void normal_output(vector<string> input,AVLtree &a) {
	vector <keyblock> result;
	for (int i = 0; i < input.size(); i++) {
		node*get=NULL;
		a.search(input[i],get);
		if (get != NULL)
			merge(result, get->data);
	}
	keyblockSort(result);
	print_vector(result, input);
}
void merge(vector<keyblock>&result, vector<keyblock>query) {
	int n_res = result.size();
	int n_que = query.size();
	bool is_update = false;
	int update = 0;
	for (int i = 0; i < n_que; i++) {
		if (update >= 5)return;
		for (int j = 0; j < n_res; j++)
			if (query[i].title == result[j].title) {
				result[j].frequency += query[i].frequency;
				for (int k = 0; k < 100; k++)result[j].para[k] += query[i].para[k];
				is_update = true;
				update++;
				j += 999;//stop the loop
			}
		if (!is_update) {
			result.push_back(query[i]);
			n_res++;
		}
		is_update = false;
	}
}
void print_vector(vector <keyblock> result, vector<string> query) {
	for (int i = 0; i < result.size(); i++) {
		if (i >= 5)return;
		int pr = max_index(result[i].para)+1;
		cout << "$";
		color_print(result[i].title);
		cout << "$ ";
		cout << "f = " << result[i].frequency;
		cout << "p = " << pr << "$"<<endl;
		hightlight_para(result[i].title, pr, query);
		cout << endl << endl;
	}
}
int max_index(int a[100]) {
	int idx = 0;
	for (int i = 1; i < 100; i++)
		if (a[i] > a[idx]) idx = i;
	return idx;
}
