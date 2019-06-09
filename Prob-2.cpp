#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<algorithm>
#define max 2147483647
#define white 0
#define gray 1
#define black 2
using namespace std;

class Node {
public:
	int number;
	string name;
	int d = max;
	int color = white;
	vector<Node*> nexts;
	vector<Node*> path;
	Node(int i, string s) {
		number = i;
		name = s;
	}
};

void bfs_dij(Node* node, int** adjTable) {
	node->color = gray;
	Node* nextnode = nullptr;
	node->path.push_back(node); // �ڱ� �ڽ��� ��ο� �߰�
	
	for (int i = 0; i < node->nexts.size(); i++) {
		
		if (node->nexts[i]->color == white) {
			
			if (node->d + adjTable[node->number][node->nexts[i]->number] < node->nexts[i]->d) { // ���� ��ϵ� �� ����, ���� ��带 ������ ���°� �� ���� ��
				node->nexts[i]->d = node->d + adjTable[node->number][node->nexts[i]->number];
				node->nexts[i]->path = node->path;
				
			}
			if (nextnode == nullptr) {
				nextnode = node->nexts[i];
				continue;
			}
			if (adjTable[node->number][nextnode->number] > adjTable[node->number][node->nexts[i]->number]) {
				nextnode = node->nexts[i];
			}
		}
	}
	if (nextnode == nullptr) {
		return;
	}
	node->color = black;
	bfs_dij(nextnode, adjTable);
}

int main() {
	map<string, Node*> nodeTable; // ��� ���� ����
	int nodeCount;
	int edgeCount;
	cin >> nodeCount >> edgeCount;
	cin.ignore();
	string start;
	string end;
	cin >> start >> end;
	cin.ignore();
	
	int** adjTable = new int*[nodeCount]; // ������ �迭 ����
	for (int i = 0; i < nodeCount; i++) {
		adjTable[i] = new int[nodeCount];
	}

	for (int i = 0; i < nodeCount; i++) { // ��� �߰���
		string name;
		getline(cin, name);
		Node* node = new Node(i, name);
		node->number = i;
		nodeTable.insert(pair<string, Node*>(name, node));
	}

	for (int i = 0; i < edgeCount; i++) { // ���� �߰���
		string a;
		string b;
		int dis;
		cin >> a >> b >> dis;
		adjTable[nodeTable.find(a)->second->number][nodeTable.find(b)->second->number] = dis;
		adjTable[nodeTable.find(b)->second->number][nodeTable.find(a)->second->number] = dis;
		nodeTable.find(a)->second->nexts.push_back(nodeTable.find(b)->second);
		nodeTable.find(b)->second->nexts.push_back(nodeTable.find(a)->second);
	}
	nodeTable.find(start)->second->d = 0;
	bfs_dij(nodeTable.find(start)->second, adjTable);
	for (int i = 0; i < nodeTable.find(end)->second->path.size(); i++) {
		cout << nodeTable.find(end)->second->path[i]->name << " ";
	}
	cout << nodeTable.find(end)->second->d;

}