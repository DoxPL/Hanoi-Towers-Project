#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <map>
using namespace std;
void hanoi(int discs, char from, char to, char tmp1, char tmp2);
int pegNum[4] = {4, 0, 0, 0};
void draw();
int n;
void init(int *c, map<int, int> pos);
int getNum(char c);
int *colors;
map<int, int> pos;
map <int, int> :: iterator iter;
int **table;
void swap(int **tab, int fromPeg, int dest2);
int main()
{
	srand(time(NULL));
    cout << "Podaj ilosc dyskow: ";
    cin >> n;
    table = new int *[n];
    //inicjacja planszy
    for(int i=0; i < n; i++)
    {
    	table[i] = new int [4];
    	for(int j=0; j < 4; j++)
    	{
    		if(j == 0)
    		{
    			table[i][j] = i + 1; //ustawianie koloru dyskow
			}
			else
			{
				table[i][j] = 0;
			}
		}
	}
    pegNum[0] = n;
    colors = new int[n];
    init(colors, pos);
    cout << endl;
    hanoi(n, 'A', 'D', 'B', 'C');

    for(int i=0; i<n; i++)
    	delete table[i];
	delete []table;
    return 0;
}
void hanoi(int discs, char from, char to, char tmp1, char tmp2)
{
    if(discs > 0)
    {
        hanoi(discs-2, from, tmp1, tmp2, to);
        cout << "Przenies dysk " << discs-1 << " : " << from << " -> " << tmp2 << endl;
        swap(table, getNum(from), getNum(tmp2));
        draw();
		//from 1, to 4, tmp1 2, tmp2 3
        cout << "Przenies dysk " << discs << " : " << from << " -> " << to << endl;
        swap(table, getNum(from), getNum(to));
        draw();
        cout << "Przenies dysk " << discs-1 << " : " << tmp2 << " -> " << to << endl;
    	swap(table, getNum(tmp2), getNum(to));
        draw();
        hanoi(discs-2, tmp1, to, from, tmp2);
    }
}

void init(int *c, map<int, int> pos)
{
	for(int i=0; i < n; i++)
		c[i] = i+7;
	for(int i=0; i < n; i++)
	{
		pos.insert(pair<int, int> (0, i));
	}
}

void draw()
{
	HANDLE consoleHandler = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << endl;
	for(int i=0; i < 10; i++)
		cout << "*";
	cout << endl;
	for(int i=0; i<n; i++)
	{
		for(int j=0; j < 4; j++)
		{
			if(table[i][j] == 0)
				cout << '|';
			else
			{
			    SetConsoleTextAttribute(consoleHandler, colors[ table[i][j] ]);
                cout << table[i][j];
                SetConsoleTextAttribute(consoleHandler, 0x0f);
			}
			cout << ' ';
		}
		cout << endl;
	}
	for(int i=0; i < 10; i++)
		cout << "*";
	cout << endl;
}

void swap(int **tab, int fromPeg, int dest2)
{

	int copy = -1, first_pos = -1, position = -1;
	//zabranie pierwszego wolnego dysku
	for(int i=0; i < n; i++)
	{
		if(tab[i][fromPeg] != 0)
		{
			copy = tab[i][fromPeg];
			tab[i][fromPeg] = 0;
			break;
		}

	}
	//szukanie wolnego miejsca
	for(int i= (n - 1); i >= 0; i--)
	{
		if(tab[i][dest2] == 0)
		{
			position = i;
			break;
		}
	}
	if(copy >= 0)
		table[position][dest2] = copy;
	//cout << "zmiana z " << a << ", " << b << " na: " << position << ", " << dest << endl;
}
int getNum(char c)
{
	switch((char)c)
	{
		case 'A':
			return 0;
		case 'B':
			return 1;
		case 'C':
			return 2;
		case 'D':
			return 3;
	}
}
