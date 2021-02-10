#include <iostream>
#include <Windows.h>
#include "tree.h"

using namespace std;
void show_tree(tree t);
void show_node(queue<node*> q);

void main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	tree t;
	add_to_tree(t, "C:\\Windows\\System32");
	add_to_tree(t, "C:\\Windows\\etc");
	add_to_tree(t, "C:\\Windows\\etc\\drivers");
	add_to_tree(t, "C:\\Windows\\etc\\drivers\\hosts");
	add_to_tree(t, "C:\\boot.data");
	add_to_tree(t, "C:\\Program Files");
	add_to_tree(t, "C:\\Windows\\System32\\system.dll");
	add_to_tree(t, "D:\\Users\\User1");
	add_to_tree(t, "D:\\Users\\User1\\Desktop");
	add_to_tree(t, "D:\\Users\\User1\\Desktop\\Chrome.lnk");
	show_tree(t);
	cout << endl;
	delete_from_tree(t, "C:\\Windows\\etc\\drivers\\hosts");
	show_tree(t);
	cout << endl;
	delete_from_tree(t, "D:");
	show_tree(t);
	cout << endl;
	delete_from_tree(t, "C:\\Windows");
	show_tree(t);
	cout << endl;
	drop_tree(t);
	show_tree(t);
	cout << endl;
	system("pause");
}

void show_tree(tree t)
{
	auto q = traverse(t);
	show_node(q);
}

void show_node(queue<node*> q)
{
	while (q.size() > 0)
	{
		auto el = q.front();
		q.pop();
		auto level = el->level;
		for (int i = 0; i < (level - 1) * 2; i++)
		{
			cout << (i % 2 == 0 ? "|" : " ");
		}
		if (level > 0) cout << "|-";
		cout << el->name.c_str() << endl;
	}
}