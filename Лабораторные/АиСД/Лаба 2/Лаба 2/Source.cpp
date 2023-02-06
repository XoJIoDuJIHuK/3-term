#include <iostream>
using namespace std;

struct list
{
	int value;
	list* next = nullptr;
};

struct stack
{
	int value;
	stack* previous = nullptr;
};

//глобальные переменные

list spisokSmezhnosti[10]; //каждый элемент массива является началом односвязного списка из вершин, соединённых с данной вершиной
//O(V + E)
int spisokReber[10][2] = //список рёбер O(V + E)
{
	{ 1, 5 },
	{ 2, 7 },
	{ 2, 8 },
	{ 7, 8 },
	{ 3, 8 },
	{ 5, 6 },
	{ 4, 6 },
	{ 4, 9 },
	{ 6, 9 },
	{ 9, 10 }
};

bool matricaSmezhnosti[10][10] = //единица на пересечении Н-й строки и К-го столбца значит, что вершины Н и К соединены
{//O(n^2)
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},//1
	{ 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},//2
	{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},//3
	{ 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},//4
	{ 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},//5
	{ 1, 0, 0, 1, 1, 0, 0, 0, 1, 0},//6
	{ 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},//7
	{ 0, 1, 1, 0, 0, 0, 1, 0, 0, 0},//8
	{ 0, 0, 0, 1, 0, 1, 0, 0, 0, 1},//9
	{ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},//10
};

void addVertex(int vertex, int number) //добавляет вершину vertex в список вершины number
{
	list* listPtr = new list;
	*listPtr = { vertex };
	list tempList = spisokSmezhnosti[number];
	while (tempList.next != nullptr) tempList = *(tempList.next);
	tempList.next = listPtr;
}

void pushToStack(stack** pointer, int vertex)
{
	stack* newVertex = new stack; //выделение памяти
	*newVertex = { vertex, *pointer }; //инициализация и помещение в конец стека
	*pointer = newVertex; //сдвиг указателя на вершину стека
}
void popFromStack(stack** pointer)
{
	stack* tempPtr = *pointer;
	*pointer = (*pointer)->previous; //сдвиг указателя вершины стека на единицу вниз
	delete tempPtr;
}
void popFromQueue(stack** pointer)
{
	if ((*pointer)->previous == nullptr) //если первый элемент в очереди указывает на NULL
	{
		cout << "Очередь уже пуста\n";
		return;
	}
	stack* temp = *pointer;
	if (temp->previous->previous == nullptr) //если в очереди один элемент
	{
		*pointer = temp->previous;
		delete temp;
		return;
	}
	while (temp->previous->previous->previous != nullptr) temp = temp->previous; //поиск предполседнего элемента
	stack* del = temp->previous; //указатель на удаляемый элемент
	temp->previous = temp->previous->previous; //связывание предпоследнего элемента с концом очереди
	delete del;
}

bool notVisitedOrInStack(stack* ptrVisited, stack* ptrStack, int value)
{
	do
	{
		if (ptrVisited->value == value) return 0; //если переданный элемент посещён, возвращает "ложь"
		else if (ptrVisited->previous == nullptr) break; //если достигнут конец стека, прерывает цикл
		else ptrVisited = ptrVisited->previous;
	} while (ptrVisited->value != 0); //пока не будет достигнут конец стека
	do
	{
		if (ptrStack->value == value) return 0;
		else if (ptrStack->previous == nullptr) break;
		else ptrStack = ptrStack->previous;
	} while (ptrStack->value != 0);
	return 1;
}

void DFS(int currentVertex, int destination)
{
	stack* stackPointer = new stack; //указатель на вершину стека вершин, находящихся в очереди на посещение
	stackPointer->value = { 0 };
	stack* visitedPointer = new stack; //указатель на вершину стека посещённых вершин
	visitedPointer->value = { 0 };
	while (currentVertex != destination) //пока не будет достигнута вершина назначения
	{
		stack* temp = new stack;
		*temp = { currentVertex, visitedPointer }; //добавление текущей вершины в стек посещённых
		visitedPointer = temp;
		for (int i = 0; i < 10; i++) //в данном случае используется список рёбер, то есть необходимо пройтись по нему дважды:
		{//по разу с каждой стороны рёбер
			if (spisokReber[i][0] == currentVertex && notVisitedOrInStack(visitedPointer, stackPointer, spisokReber[i][1]))
			{//поиск текущего ребра в списке рёбер и помещение в стек ребра, смежного с ним, если оно ещё не в стеке
				pushToStack(&stackPointer, spisokReber[i][1]); //и не было посещено
			}
			if (spisokReber[i][1] == currentVertex && notVisitedOrInStack(visitedPointer, stackPointer, spisokReber[i][0]))
			{
				pushToStack(&stackPointer, spisokReber[i][0]);
			}
		}
		if (stackPointer->value != 0) //есле остались непосещённые вершины
		{
			cout << "Текущий стек: "; //вывод значений, находящихся в стеке
			stack* temp = stackPointer;
			while (temp->value != 0)
			{
				cout << temp->value << " ";
				temp = temp->previous;
			}
			cout << endl << "Перейти в вершину " << stackPointer->value << endl;
			currentVertex = stackPointer->value; //перемещение в следующую по очереди вершину
			popFromStack(&stackPointer); //удаление первого элемента в стеке
			if (currentVertex == destination)
			{
				cout << "Точка назначения достигнута\n";
			}
		}
	}
}

void BFS(int currentVertex, int destination)
{
	stack* stackPointer = new stack;
	stackPointer->value = { 0 };
	stack* visitedPointer = new stack;
	visitedPointer->value = { 0 };
	while (currentVertex != destination)
	{
		stack* temp = new stack;
		*temp = { currentVertex, visitedPointer };
		visitedPointer = temp;
		for (int i = 0; i < 10; i++)
		{
			if (spisokReber[i][0] == currentVertex && notVisitedOrInStack(visitedPointer, stackPointer, spisokReber[i][1]))
			{
				pushToStack(&stackPointer, spisokReber[i][1]);
			}
			if (spisokReber[i][1] == currentVertex && notVisitedOrInStack(visitedPointer, stackPointer, spisokReber[i][0]))
			{
				pushToStack(&stackPointer, spisokReber[i][0]);
			}
		}
		if (stackPointer->value != 0)
		{
			cout << "Текущий стек: ";
			stack* temp = stackPointer;
			while (temp->value != 0)
			{
				cout << temp->value << " ";
				temp = temp->previous;
			}
			temp = stackPointer;
			if (stackPointer->previous == nullptr)
			{
				cout << "Пустая очередь" << endl;
				return;
			}
			while (temp->previous->previous != nullptr) temp = temp->previous;
			cout << endl << "Перейти в вершину " << temp->value << endl;
			currentVertex = temp->value;
			popFromQueue(&stackPointer);
			if (currentVertex == destination)
			{
				cout << "Точка назначения достигнута\n";
			}
		}
	}
}

void main()
{
	setlocale(LC_ALL, "ru");
	addVertex(5, 1);
	addVertex(7, 2);
	addVertex(8, 2);
	addVertex(8, 3);
	addVertex(6, 4);
	addVertex(9, 4);
	addVertex(1, 5);
	addVertex(6, 5);
	addVertex(4, 6);
	addVertex(5, 6);
	addVertex(9, 6);
	addVertex(2, 7);
	addVertex(8, 7);
	addVertex(2, 8);
	addVertex(3, 8);
	addVertex(7, 8);
	addVertex(4, 9);
	addVertex(6, 9);
	addVertex(10, 9);
	addVertex(9, 10);

	BFS(1, 10);
	DFS(1, 10);
}