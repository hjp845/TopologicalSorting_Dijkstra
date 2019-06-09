#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#define white 0
#define gray 1
#define black 2
using namespace std;

class node {
public:
	int entryLevel;
	node* prev;
	vector<node*> nexts;
	int color;
	int d;
	int f;
	string name;
	int number;
	node(int n, string s) {
		entryLevel = 0;
		number = n;
		name = s;
		prev = nullptr;
		nexts = vector<node*>();
		color = white;
	}

};

int time = 0;
void dfs(node* u) {
	time++;
	u->color = gray;
	u->d = time;
	for (int i = 0; i < u->nexts.size(); i++) {
		if (u->nexts[i]->color == white) {
			u->prev = u;
			dfs(u->nexts[i]);
		}
	}
	time++;
	u->color = black;
	u->f = time;
}

bool compare(node* a, node* b) {
	return a->number < b->number;
}
bool compare2(node* a, node* b) {
	return a->f > b->f;
}

int main() {
	vector<node*> nodeTable;
	vector<node*> firstNodeTable;
	int nodeCount;
	int edgeCount;
	cin >> nodeCount >> edgeCount;
	cin.ignore();
	for (int i = 0; i < nodeCount; i++) {
		string name;
		getline(cin, name);
		node* newnode = new node(i, name);
		nodeTable.push_back(newnode);
	}
	for (int j = 0; j < edgeCount; j++) {
		int a;
		int b;
		cin >> a >> b;
		nodeTable[b]->entryLevel++;
		nodeTable[a]->nexts.push_back(nodeTable[b]);
	}
	for (int k = 0; k < nodeTable.size(); k++) {
		if (nodeTable[k]->nexts.size() > 1) {
			sort(nodeTable[k]->nexts.begin(), nodeTable[k]->nexts.end(), compare);
		}		
		if (nodeTable[k]->entryLevel == 0) {
			firstNodeTable.push_back(nodeTable[k]);
		}
	}
	for (int h = 0; h < firstNodeTable.size(); h++) {
		dfs(firstNodeTable[h]);
	}
	sort(nodeTable.begin(), nodeTable.end(), compare2);
	for (int g = 0; g < nodeTable.size(); g++) {
		cout << nodeTable[g]->name << " ";
	}
}