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

bool AVLtree::search(string x)
{
	node * tmp = search(root, x);
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
void LoadFile(string path, AVLtree &a)//ctreate filename
{
	ifstream fin;
	for (int i = 2; i <=25 ; ++i)//because we have 25 group =))
	{
		string filename;
		for (int j = 1; j <= 100; ++j)
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
					para = (para + 1);
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
		for (int i = 0; i < N->data.size(); ++i)
		{
			//paragraphSort(N->data[i].para);
		}
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
