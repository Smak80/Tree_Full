#include "tree.h"
#include <sstream>

// ----------------------------------------------------------------
// ������ ��������������� �������

/// <summary>
/// ��������������� ����������� ������� ���������� ���� � ������
/// </summary>
/// <param name="n">���� � ������� ����� �������� ����� �������</param>
/// <param name="name">�������� ��� �������� �������� ���������</param>
void _add_to_tree(node*& n, string name);

// �������� ���� �� ������
bool _delete_from_tree(node*& n, string name);

/// <summary>
/// ���������� �������� ����������� ������� ������ ������. 
/// </summary>
/// <param name="q">������� �� ��������� ������</param>
/// <param name="n">����, ��� �������� ����������� �����</param>
void _bypass(queue<const node*>& q, const node* n);

/// <summary>
/// ������������ ��������������� ������� �������� ������ ���� ������
/// </summary>
/// <param name="name">�������� ��� ������������ ����</param>
/// <returns>��������� �� ����� ���� ��� ���������� � ������</returns>
inline node* _create_new_node(string name);

/// <summary>
/// ���������� ������� �������� ������ 
/// </summary>
/// <param name="t">�������� ���� ���������� ������ ��� ��� �����</param>
void _drop_tree(node*& t);

/// <summary>
/// ��������������� ������� ������ ��������� �� ������� �������� ���������,
/// ��� ��������� �������� ��������� ����
/// </summary>
/// <param name="parent">������������ �������, � ������� ����������� ����� </param>
/// <param name="name">��������  �������� �������� ����</param>
/// <returns>��������� �� ������� ���� ������</returns>
node* _get_node_in_list_by_name(const node* parent, string name);

/// <summary>
/// ��������������� ������� ����������� ����������� ������ ��������� ���� �� ������,
/// ���������������� ��������� ������� ������ t.
/// </summary>
/// <param name="t">���� ������, � ������� ����������� �����</param>
/// <param name="name">�������� ��� �������� ����</param>
/// <returns>����� ���� � ������ �������� ���������, ���� -1, ���� ���� �� ������</returns>
int _get_node_list_index_by_name(const node* t, string name);

/// <summary>
/// ��������� ���� � ������������ �������� �� ������� �����
/// </summary>
/// <param name="full_name">������ ���� � �������� �������� ���������</param>
/// <param name="parent">������������ ����, � ������� �������� ������� �������</param>
/// <returns>��������� �� ������� ���� �������� ��������� ��� nullptr,
/// ���� ������� �� ������</returns>
node* _get_node_by_full_name(string full_name, node*& parent);
// ----------------------------------------------------------------

void add_to_tree(tree& t, string full_name)
{
	// ������� ������ �� ����� �� ������� "\"
	// ��� ���������� �������� ������������ ����� stringstream,
	// �������������� �� ������ � ������ ������ �����
	stringstream ss(full_name);
	string item;
	node* n = t.root;
	// ����� �� ���� ��������� � ���� ������� � ������
	// ������������ ���������,
	// ���� ��������� ����� ������� � ������
	while (getline(ss, item, '\\'))
	{
		// ������� getline �� ������ �������� �����
		// �������� ����� ���������� ������, ������������ ����� ��������� �������,
		// � ���������� item, ������� ������������ ����� �������� ��� ����� ��� �����
		if (!item.empty()) // ���� ��� �� ������
			// ����������� ����� ��������������� (�������������) �������
			// add_to_tree � ������ ���������� ���� node* 
			_add_to_tree(n, item);
	}
}

void _add_to_tree(node*& n, string name)
{
	// ���� ������ �� ����
	if (!n) return;
	// ��������� ������������� ���� ��� ������
	auto container = _get_node_in_list_by_name(n, name);
	// ���� ������������ ���� ������
	if (!container)
	{ // ��������� � ���� ����� ����
		container = new node;
		container->name = name;
		container->level = n->level + 1;
		n->list.push_back(container);
	}
	n = container;
}

bool delete_from_tree(tree& t, string full_name)
{
	// �������� full_name �������� ������ ��� ���������� �������
	node* parent = t.root;
	// ������� ���� (n), ��������������� ������� �����, � ����� ��� ������ (parent)
	node* n = _get_node_by_full_name(full_name, parent);
	if (parent && n) {
		// ���� ���� � ��� ������ �������,
		// ������� �� ������ ������������� �������� ������ ��������� ����
		parent->list.remove(n);
		// ������� ��� ���� �� ������
		_drop_tree(n);
		return true;
	}
	return false;
}

queue<const node*> bypass(const tree& t)
{
	queue<const node*> q;
	const node* root = t.root;
	_bypass(q, root);
	return q;
}

void _bypass(queue<const node*>& q, const node* n)
{
	if (n) { // ���� ������� ������ ������� �� ���������
		q.push(n); //��������� ���� � �������
		for (auto e : n->list)
		{
			// ��� ���� �������� ����� �������� ���� ���������
			// ���������� �� � �������.
			_bypass(q, e);
		}
	}
}

void drop_tree(tree& t)
{
	_drop_tree(t.root);
}

void _drop_tree(node*& t)
{
	// ���������� ������������ �������� ���� �����������
	// �� ������ �������� ����� 
	for (auto el : t->list)
	{
		_drop_tree(el);
	}
	// ������� ������ �������� �����
	t->list.clear();
	// �������� �����, ����� ���������.
	// (�������� ���� ��������� ������ ����� ��������� tree)
	if (t->level > 0) {
		delete t;
		t = nullptr;
	}
}

inline node* _create_new_node(string name)
{
	node* n = new node;
	n->name = name;
	return n;
}

int _get_node_list_index_by_name(const node* t, string name)
{
	int i = 0;
	// ������ ���� ��������� ��������� �� ���� ��������� ������
	for (auto el : t->list)
	{
		// ���� ������� ������� � ��������� ������
		if (el->name == name)
			// ���������� ��� ���������� �����
			return i;
		i++;
	}
	// ���� ���� �� ���� �� ���������, ������ ����� � ���������
	// ������ � ������ �� ����������
	return -1;
}

node* _get_node_in_list_by_name(const node* parent, string name)
{
	if (parent)
		for (auto n : parent->list)
			if (n && n->name == name) return n;
	return nullptr;
}

node* _get_node_by_full_name(string full_name, node*& parent)
{
	// ��� �������� �������� �� �������� ��������� ��� ��� ����� ���������
	// �� ����� �� ������� "\". ��. ����������� ����� � ������� add_to_tree
	stringstream ss(full_name);
	string item;
	node* n = parent;
	while (getline(ss, item, '\\'))
	{// �������� ��������� ����� ����� �����
		// ���������� ������� ���� ������
		parent = n;
		// �������� ����� ������� ������� (item) �� ���� n
		n = _get_node_in_list_by_name(n, item);
		if (!n) return nullptr; //����� �� ������
	}
	return n;
}