#include <iostream>
#include <vector>
#include <string>

using namespace std;

void generaZ(vector<vector<int>>, string, int, int);

int main()
{

	string x, y, z;
	vector<vector<int>> tabla;
	vector<vector<int>> C;

	cout << "Inserte la cadena X\n";
	getline(cin, x);
	cout << "\nInserte la cadena Y\n";
	getline(cin, y);
	x.insert(0, " ");
	y.insert(0, " ");

	for (int i = 0; i < x.length(); i++)
	{
		vector<int> temp;
		for (int j = 0; j < y.length(); j++)
			temp.push_back(0);
		tabla.push_back(temp);
		C.push_back(temp);
	}

	for (int i = 1; i < x.length(); i++)
	{
		for (int j = 1; j < y.length(); j++)
		{
			if (x.at(i) == y.at(j))
			{
				tabla[i][j] = tabla[i - 1][j - 1] + 1;
				C[i][j] = 2;
			}
			else
			{
				if (tabla[i - 1][j] >= tabla[i][j - 1])
				{
					tabla[i][j] = tabla[i - 1][j];
					C[i][j] = 1;
				}
				else
					tabla[i][j] = tabla[i][j - 1];

			}

		}
	}

	cout << "\nLa subsecuencia mas larga es: \n";
	generaZ(C, x, x.length() - 1, y.length() - 1);

	cout << "\n\nLa complejidad O(n*m)\n";

	//system("pause");
	return 0;
}

void generaZ(vector<vector<int>> C, string x, int i, int j)
{

	if (i == 0 || j == 0)
		return;

	if (C[i][j] == 2)
	{
		generaZ(C, x, i - 1, j - 1);
		cout << x.at(i);
	}
	else
	{
		if (C[i][j] == 1)
			generaZ(C, x, i - 1, j);
		else
			generaZ(C, x, i, j - 1);
	}

}
