#include <iostream>
#include <stack>
#include <Windows.h>
#include "tree.h"

using namespace std;

//-------------------------------------------------------------
//Вспомогательные функции

/// <summary>
/// Показ элементов дерева либо в виде древовидной структуры, либо списком
/// </summary>
/// <param name="t">Отображаемое на экране дерево</param>
/// <param name="as_tree">
/// Параметр определяет тип представления содержимого:
/// Если равен true - выводит элементы в виде дерева
/// Если равен false - выводит элементы файловой структуры списком
/// </param>
void show_tree(const tree& t, bool as_tree = true);

/// <summary>
/// Функция отображения элементов дерева в древовидной структуре
/// </summary>
/// <param name="q">Очередь из элементов выводимого дерева</param>
void _show_as_tree(const queue<const node*>& q);

/// <summary>
/// Функция отображения элементов дерева в форме списка
/// </summary>
/// <param name="q">Очередь из элементов выводимого дерева</param>
void _show_as_list(const queue<const node*>& q);

/// <summary>
/// Рекурсивная функция отображения полного пути к элементу файловой структуры
/// </summary>
/// <param name="s">Стек, содержащий элементы файловой структуры</param>
/// <param name="last_item">
/// Признак вывода последнего элемента пути. <br>
/// Данный параметр влияет на используемый символ разделитель между элементами
/// Если равен true, будет выведен конец строки ("\n"), в противном случае - символ "\"
/// </param>
void _show_stack(stack<const node*> s, bool last_item = true);

/// <summary>
/// Вспомогательная функция, используемая для формирования полных имен всех возможных
/// элементов файловой структуры, имеющихся в стеке
/// </summary>
/// <param name="st">Стек элементов файловой структуры</param>
/// <param name="cnt">
/// Количество выводимых элементов или
/// -1 для вывода всех возможных значений
/// </param>
void _show_all_records(stack<const node*>& st, int cnt = -1);
//-------------------------------------------------------------

/// <summary>
/// Основная функция программы
/// </summary>
void main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//Создание дерева папок и файлов
	tree t;
	//Добавление элементов структуры дерева
	add_to_tree(t, "C:\\Windows\\etc\\drivers\\hosts");
	add_to_tree(t, "C:\\Windows\\notepad.exe");
	add_to_tree(t, "C:\\boot.data");
	add_to_tree(t, "C:\\Program Files");
	add_to_tree(t, "C:\\Windows\\System32\\system.dll");
	add_to_tree(t, "D:\\Users\\User1");
	add_to_tree(t, "D:\\Users\\User1\\Desktop");
	add_to_tree(t, "D:\\Users\\User1\\Desktop\\Chrome.lnk");
	//Отображение всех элементов файловой структуры в виде списка
	show_tree(t, false);
	//Отображение всех элементов файловой структуры в виде дерева
	show_tree(t);

	//Далее выполняются изменения структуры дерева и отображение результатов
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
	//Создание очереди из элементов файловой структуры
	const queue<const node*> q = bypass(t);
	//Выбор способа отображения элементов 
	if (as_tree)
		_show_as_tree(q);
	else
		_show_as_list(q);
	cout << endl;
}

void _show_as_tree(const queue<const node*>& queue)
{
	//Формирование копии очереди
	auto q = queue;
	//Пока очередь содержит какие-либо элементы
	while (q.size() > 0)
	{
		//Получение указателя на первый элемент в очереди
		auto el = q.front();
		//Удаление первого элемента из головы очереди
		q.pop();
		//Вывод соединительных линий в зависимости от числа уровней
		auto level = el->level;
		for (int i = 0; i < (level - 1) * 2; i++)
		{
			cout << (i % 2 == 0 ? "|" : " ");
		}
		//Вывод заключительной линии перед элементом файловой структуры
		if (level > 0) cout << "|-";
		//Вывод короткого названия элемента
		cout << el->name << endl;
	}
}

void _show_as_list(const queue<const node*>& queue)
{
	// Формирование копии очереди
	auto q = queue;
	// Создание стека элементов файловой структуры
	stack<const node*> st;
	// Сохранение уровня последнего элемента
	auto last_lvl = 0;
	// Для всех элементов очереди
	while (q.size() > 0)
	{
		// Получение первого элемента из очереди
		auto el = q.front();
		if (el->level > 0) { // Пропуск корня файловой структуры
			if (el->level <= last_lvl) {
				// Если следующий элемент файловой структуры оказался на том же
				// или более высоком уровне, что и предыдущий,
				// отображаем содержимое, которое накопилось в стеке
				_show_all_records(st, last_lvl - el->level);
			}
			//Добавляем очередной элемент в стек
			st.push(el);
		}
		//Запоминаем уровень последнего элемента
		last_lvl = el->level;
		//Извлекаем рассмотренный элемент из очереди
		q.pop();
	}
	//Показываем элементы, накопившиеся в стеке, в конце обработки очереди
	_show_all_records(st);
}

void _show_all_records(stack<const node*>& st, int cnt)
{
	int i = 0;
	// Выводим указанное количество или все элементы из стека
	// Например, для стека, содержащего элементы:
	// - notepad.exe
	// - Windows
	// - C:
	// при параметре cnt=-1 будут выведены записи:
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
	// Формирование полного пути по элементам, расположенным в стеке
	string n = s.top()->name;
	s.pop();
	if (s.size() > 0) _show_stack(s, false);
	cout << n << (last_item ? "\n" : "\\");
}
