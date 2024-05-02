#include <iostream>
#include <stack>
#include <Windows.h>
#include "tree.h"

using namespace std;

//-------------------------------------------------------------
//��������������� �������

/// <summary>
/// ����� ��������� ������ ���� � ���� ����������� ���������, ���� �������
/// </summary>
/// <param name="t">������������ �� ������ ������</param>
/// <param name="as_tree">
/// �������� ���������� ��� ������������� �����������:
/// ���� ����� true - ������� �������� � ���� ������
/// ���� ����� false - ������� �������� �������� ��������� �������
/// </param>
void show_tree(const tree& t, bool as_tree = true);

/// <summary>
/// ������� ����������� ��������� ������ � ����������� ���������
/// </summary>
/// <param name="q">������� �� ��������� ���������� ������</param>
void _show_as_tree(const queue<const node*>& q);

/// <summary>
/// ������� ����������� ��������� ������ � ����� ������
/// </summary>
/// <param name="q">������� �� ��������� ���������� ������</param>
void _show_as_list(const queue<const node*>& q);

/// <summary>
/// ����������� ������� ����������� ������� ���� � �������� �������� ���������
/// </summary>
/// <param name="s">����, ���������� �������� �������� ���������</param>
/// <param name="last_item">
/// ������� ������ ���������� �������� ����. <br>
/// ������ �������� ������ �� ������������ ������ ����������� ����� ����������
/// ���� ����� true, ����� ������� ����� ������ ("\n"), � ��������� ������ - ������ "\"
/// </param>
void _show_stack(stack<const node*> s, bool last_item = true);

/// <summary>
/// ��������������� �������, ������������ ��� ������������ ������ ���� ���� ���������
/// ��������� �������� ���������, ��������� � �����
/// </summary>
/// <param name="st">���� ��������� �������� ���������</param>
/// <param name="cnt">
/// ���������� ��������� ��������� ���
/// -1 ��� ������ ���� ��������� ��������
/// </param>
void _show_all_records(stack<const node*>& st, int cnt = -1);
//-------------------------------------------------------------

/// <summary>
/// �������� ������� ���������
/// </summary>
void main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//�������� ������ ����� � ������
	tree t;
	//���������� ��������� ��������� ������
	add_to_tree(t, "C:\\Windows\\etc\\drivers\\hosts");
	add_to_tree(t, "C:\\Windows\\notepad.exe");
	add_to_tree(t, "C:\\boot.data");
	add_to_tree(t, "C:\\Program Files");
	add_to_tree(t, "C:\\Windows\\System32\\system.dll");
	add_to_tree(t, "D:\\Users\\User1");
	add_to_tree(t, "D:\\Users\\User1\\Desktop");
	add_to_tree(t, "D:\\Users\\User1\\Desktop\\Chrome.lnk");
	//����������� ���� ��������� �������� ��������� � ���� ������
	show_tree(t, false);
	//����������� ���� ��������� �������� ��������� � ���� ������
	show_tree(t);

	//����� ����������� ��������� ��������� ������ � ����������� �����������
	delete_from_tree(t, "C:\\Windows\\etc\\drivers\\hosts");
	show_tree(t);
	delete_from_tree(t, "D:");
	show_tree(t);
	add_to_tree(t, "C:\\Users\\User1");
	show_tree(t);
	delete_from_tree(t, "C:\\Users");
	show_tree(t);
	delete_from_tree(t, "C:\\Windows");
	show_tree(t);
	drop_tree(t);
	show_tree(t);
	system("pause");
}

void show_tree(const tree& t, bool as_tree)
{
	//�������� ������� �� ��������� �������� ���������
	const queue<const node*> q = bypass(t);
	//����� ������� ����������� ��������� 
	if (as_tree)
		_show_as_tree(q);
	else
		_show_as_list(q);
	cout << endl;
}

void _show_as_tree(const queue<const node*>& queue)
{
	//������������ ����� �������
	auto q = queue;
	//���� ������� �������� �����-���� ��������
	while (q.size() > 0)
	{
		//��������� ��������� �� ������ ������� � �������
		auto el = q.front();
		//�������� ������� �������� �� ������ �������
		q.pop();
		//����� �������������� ����� � ����������� �� ����� �������
		auto level = el->level;
		for (int i = 0; i < (level - 1) * 2; i++)
		{
			cout << (i % 2 == 0 ? "|" : " ");
		}
		//����� �������������� ����� ����� ��������� �������� ���������
		if (level > 0) cout << "|-";
		//����� ��������� �������� ��������
		cout << el->name << endl;
	}
}

void _show_as_list(const queue<const node*>& queue)
{
	// ������������ ����� �������
	auto q = queue;
	// �������� ����� ��������� �������� ���������
	stack<const node*> st;
	// ���������� ������ ���������� ��������
	auto last_lvl = 0;
	// ��� ���� ��������� �������
	while (q.size() > 0)
	{
		// ��������� ������� �������� �� �������
		auto el = q.front();
		if (el->level > 0) { // ������� ����� �������� ���������
			if (el->level <= last_lvl) {
				// ���� ��������� ������� �������� ��������� �������� �� ��� ��
				// ��� ����� ������� ������, ��� � ����������,
				// ���������� ����������, ������� ���������� � �����
				_show_all_records(st, last_lvl - el->level);
			}
			//��������� ��������� ������� � ����
			st.push(el);
		}
		//���������� ������� ���������� ��������
		last_lvl = el->level;
		//��������� ������������� ������� �� �������
		q.pop();
	}
	//���������� ��������, ������������ � �����, � ����� ��������� �������
	_show_all_records(st);
}

void _show_all_records(stack<const node*>& st, int cnt)
{
	int i = 0;
	// ������� ��������� ���������� ��� ��� �������� �� �����
	// ��������, ��� �����, ����������� ��������:
	// - notepad.exe
	// - Windows
	// - C:
	// ��� ��������� cnt=-1 ����� �������� ������:
	// C:\Windows\notepad.exe
	// C:\Windows
	// C:
	while (st.size() > 0 && (i++ <= cnt || cnt < 0)) {
		_show_stack(st);
		st.pop();
	}
}

void _show_stack(stack<const node*> s, bool last_item)
{
	// ������������ ������� ���� �� ���������, ������������� � �����
	string n = s.top()->name;
	s.pop();
	if (s.size() > 0) _show_stack(s, false);
	cout << n << (last_item ? "\n" : "\\");
}
