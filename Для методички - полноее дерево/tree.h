#pragma once
#include <list>
#include <queue>
#include <string>
using namespace std;

/// <summary>
/// ��������� ��� ������ � ������ ������
/// </summary>
struct node
{
	/// <summary>
	/// �������� ��������� �������� (�����, ����� ��� ����� �����)
	/// ������ ���� ������������ ��� �������� ��������� ����� ����� ��� �����
	/// </summary>
	std::string name = "";

	/// <summary>�������, �� ������� ���������� ������� �������� ���������</summary>
	int level = -1;

	///<summary>������ �������� ���������</summary>
	list<node*> list;
};

/// <summary>��������� ��� ������ � ������� � �����</summary>
struct tree
{
	/// <summary>��������� �� ������ ������</summary>
	node* root = new node;

	/// <summary>
	/// ������������� ����� ��������� ��������� ����� (� ����� �������
	/// ����� ���������� �������� ��������� ���������� � ����������� �������).
	/// �������, �� ������� ������������� ������ �������� ��������� - 0 
	/// </summary>
	tree()
	{
		root->name = "\\";
		root->level = 0;
	}

	/// <summary>�������� ����� ��� �������� ���������� ���� tree</summary>
	~tree()
	{
		delete root;
		root = nullptr;
	}
};

/// <summary>
/// ������� ��������� ������ � ��������� ������ ������ � ������.<br><br>
/// ��������, ���� � �������� ��������� full_name ���� �������� ��������
/// C:\\Windows\\System32\\driver.dll
/// � ������� ���������� �������, �� � ������ ����� ��������� 4 ����� �������� :
/// C:, Windows, System32 � driver.dll <br>
/// ��� ��������� ������ ������� � ���������� full_name ������, ��������,
/// C:\\Windows\\notepad.exe,
/// � ������ ����� �������� ������ ���� ����� ������� :
/// notepad.exe
/// ��� ������(C: � Windows) � ��� ��� ������������.
/// </summary>
/// <param name="t">������, � ������� ����������� �����(��) ��������</param>
/// <param name="full_name">������ ���� � �������� �������� ���������</param>
void add_to_tree(tree& t, string full_name);

/// <summary>
/// �������� �������� �� ������
/// </summary>
/// <param name="t">������, �� �������� ����� ������� ����</param>
/// <param name="full_name">������ ���� � �������� �������� ���������</param>
/// <returns>true, ���� �������� ������� � false � ��������� ������</returns>
bool delete_from_tree(tree& t, string full_name);

/// <summary>
/// ������� ������ ������ ��� �������� ������
/// </summary>
/// <param name="t">������, �������� �������� ��������� ��������</param>
/// <returns>������� �� ��������� ������</returns>
queue<const node*> bypass(const tree& t);

/// <summary>
/// �������� ������.
/// </summary>
/// <param name="t">������ �� ��������� ������</param>
void drop_tree(tree& t);
