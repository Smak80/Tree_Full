#pragma once
#include <list>
#include <queue>
#include <string>
using namespace std;

/// <summary>
/// Структура для работы с узлами дерева
/// </summary>
struct node
{
	/// <summary>
	/// Название хранимого элемента (файла, папки или буквы диска)
	/// Каждый узел предназначен для хранения короткого имени файла или папки
	/// </summary>
	std::string name = "";

	/// <summary>Уровень, на котором расположен элемент файловой структуры</summary>
	int level = -1;

	///<summary>Список дочерних элементов</summary>
	list<node*> list;
};

/// <summary>Структура для работы с деревом в целом</summary>
struct tree
{
	/// <summary>Указатель на корень дерева</summary>
	node* root = new node;

	/// <summary>
	/// Инициализация корня значением обратного слэша (с этого символа
	/// будет начинаться файловая структура устройства с несколькими дисками).
	/// Уровень, на котором располагается корень файловой структуры - 0 
	/// </summary>
	tree()
	{
		root->name = "\\";
		root->level = 0;
	}

	/// <summary>Удаление корня при удалении переменной типа tree</summary>
	~tree()
	{
		delete root;
		root = nullptr;
	}
};

/// <summary>
/// Функция размещает объект с указанным полным именем в дереве.<br><br>
/// Например, если в качестве параметра full_name было передано значение
/// C:\\Windows\\System32\\driver.dll
/// и функция вызывается впервые, то в дерево будет добавлено 4 новых элемента :
/// C:, Windows, System32 и driver.dll <br>
/// При повторном вызове функции с параметром full_name равным, например,
/// C:\\Windows\\notepad.exe,
/// в дерево будет добавлен только один новый элемент :
/// notepad.exe
/// Два других(C: и Windows) в нем уже присутствуют.
/// </summary>
/// <param name="t">Дерево, к которое добавляется новый(ые) элементы</param>
/// <param name="full_name">Полный путь к элементу файловой структуры</param>
void add_to_tree(tree& t, string full_name);

/// <summary>
/// Удаление элемента из дерева
/// </summary>
/// <param name="t">Дерево, из которого нужно удалить узел</param>
/// <param name="full_name">Полный путь к элементу файловой структуры</param>
/// <returns>true, если удаление успешно и false в противном случае</returns>
bool delete_from_tree(tree& t, string full_name);

/// <summary>
/// Функция обхода дерева для внешнего вызова
/// </summary>
/// <param name="t">Дерево, элементы которого требуется получить</param>
/// <returns>Очередь из элементов дерева</returns>
queue<const node*> bypass(const tree& t);

/// <summary>
/// Удаление дерева.
/// </summary>
/// <param name="t">Ссылка на удаляемое дерево</param>
void drop_tree(tree& t);
