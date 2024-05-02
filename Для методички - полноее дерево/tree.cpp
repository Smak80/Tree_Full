#include "tree.h"
#include <sstream>

// ----------------------------------------------------------------
// Список вспомогательных функций

/// <summary>
/// Вспомогательная рекурсивная функция добавления узла в дерево
/// </summary>
/// <param name="n">Узел в котором будет размещен новый элемент</param>
/// <param name="name">Короткое имя элемента файловой структуры</param>
void _add_to_tree(node*& n, string name);

// Удаление узла из дерева
bool _delete_from_tree(node*& n, string name);

/// <summary>
/// Внутренняя основная рекурсивная функция обхода дерева. 
/// </summary>
/// <param name="q">Очередь из элементов дерева</param>
/// <param name="n">Узел, для которого выполняется обход</param>
void _bypass(queue<const node*>& q, const node* n);

/// <summary>
/// Встраиваемая вспомогательная функция создания нового узла дерева
/// </summary>
/// <param name="name">Короткое имя создаваемого узла</param>
/// <returns>Указатель на новый узел для размещения в дереве</returns>
inline node* _create_new_node(string name);

/// <summary>
/// Внутренняя функция удаления дерева 
/// </summary>
/// <param name="t">Корневой узел удаляемого дерева или его части</param>
void _drop_tree(node*& t);

/// <summary>
/// Вспомогательная функция поиска указателя на элемент файловой структуры,
/// как дочернего элемента заданного узла
/// </summary>
/// <param name="parent">Родительский элемент, в котором выполняется поиск </param>
/// <param name="name">Короткое  название искомого узла</param>
/// <returns>Указатель на искомый узел дерева</returns>
node* _get_node_in_list_by_name(const node* parent, string name);

/// <summary>
/// Вспомогательная функция определения порядкового номера дочернего узла из списка,
/// соответствующего указанной вершине дерева t.
/// </summary>
/// <param name="t">Узел дерева, в котором выполняется поиск</param>
/// <param name="name">Короткое имя искомого узла</param>
/// <returns>Номер узла в списке дочерних элементов, либо -1, если узел не найден</returns>
int _get_node_list_index_by_name(const node* t, string name);

/// <summary>
/// Получение узла в родительском элементе по полному имени
/// </summary>
/// <param name="full_name">Полный путь к элементу файловой структуры</param>
/// <param name="parent">Родительский узел, в котором размещен искомый элемент</param>
/// <returns>Указатель на искомый узел файловой структуры или nullptr,
/// если таковой не найден</returns>
node* _get_node_by_full_name(string full_name, node*& parent);
// ----------------------------------------------------------------

void add_to_tree(tree& t, string full_name)
{
	// Деление строки на части по символу "\"
	// Для выполнения операции используется класс stringstream,
	// сформированный по строке с полным именем файла
	stringstream ss(full_name);
	string item;
	node* n = t.root;
	// Бежим по всем элементам и либо находим в дереве
	// существующий указатель,
	// либо добавляем новый элемент в дерево
	while (getline(ss, item, '\\'))
	{
		// Функция getline на каждой итерации цикла
		// помещает часть строкового потока, размещенного между обратными слешами,
		// в переменную item, которая представляет собой короткое имя файла или папки
		if (!item.empty()) // если имя не пустое
			// Выполняется вызов вспомогательной (перегруженной) функции
			// add_to_tree с первым аргументом типа node* 
			_add_to_tree(n, item);
	}
}

void _add_to_tree(node*& n, string name)
{
	// Если корень не пуст
	if (!n) return;
	// Получение родительского узла для нового
	auto container = _get_node_in_list_by_name(n, name);
	// Если родительский узел найден
	if (!container)
	{ // Добавляем в него новый узел
		container = new node;
		container->name = name;
		container->level = n->level + 1;
		n->list.push_back(container);
	}
	n = container;
}

bool delete_from_tree(tree& t, string full_name)
{
	// Параметр full_name содержит полное имя удаляемого объекта
	node* parent = t.root;
	// Находим узел (n), соответствующий полному имени, а также его предка (parent)
	node* n = _get_node_by_full_name(full_name, parent);
	if (parent && n) {
		// Если узел и его предок найдены,
		// удаляем из списка родительского элемента ссылку требуемый узел
		parent->list.remove(n);
		// Удаляем сам узел из дерева
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
	if (n) { // Если уровень записи отличен от корневого
		q.push(n); //Добавляем узел в очередь
		for (auto e : n->list)
		{
			// Для всех дочерних узлов текущего узла выполняем
			// добавление их в очередь.
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
	// Выполнение рекурсивного удаления всех поддеревьев
	// по списку дочерних узлов 
	for (auto el : t->list)
	{
		_drop_tree(el);
	}
	// Очистка списка дочерних узлов
	t->list.clear();
	// Удаление узлов, кроме корневого.
	// (Корневой узел удаляется внутри самой структуры tree)
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
	// Данный цикл позволяет пробежать по всем элементам списка
	for (auto el : t->list)
	{
		// Если находим элемент с требуемым именем
		if (el->name == name)
			// возвращаем его порядковый номер
			return i;
		i++;
	}
	// Если цикл ни разу не прервался, значит файла с указанным
	// именем в списке на обнаружено
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
	// Для удаления элемента из файловой структуры это имя нужно разделить
	// на части по символу "\". См. аналогичный прием в функции add_to_tree
	stringstream ss(full_name);
	string item;
	node* n = parent;
	while (getline(ss, item, '\\'))
	{// Получаем очередную часть имени файла
		// Запоминаем текущий узел дерева
		parent = n;
		// Пытаемся найти текущий элемент (item) из узла n
		n = _get_node_in_list_by_name(n, item);
		if (!n) return nullptr; //поиск не удался
	}
	return n;
}