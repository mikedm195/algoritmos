#include <iostream>
#include <vector>

#define	NPAREJAS 5

using namespace std;

int busquedaHombre(int);
void estabilizar(int);

int hombres[6][NPAREJAS] = {
	{ 10, 20, 30, 40, 50 },
	{ 2, 1, 2, 1, 5 },
	{ 5, 2, 3, 3, 3 },
	{ 1, 3, 5, 2, 2 },
	{ 3, 4, 4, 4, 1 },
	{ 4, 5, 1, 5, 4 }
};

int mujeres[6][NPAREJAS] = {
	{ 1, 2, 3, 4, 5 },
	{ 50, 40, 10, 30, 40 },
	{ 10, 50, 40, 20, 20 },
	{ 40, 20, 20, 40, 30 },
	{ 20, 10, 30, 10, 50 },
	{ 30, 30, 50, 50, 10 },
};

int parejas[NPAREJAS][2] = { { 10, 0 },
{ 20, 0 },
{ 30, 0 },
{ 40, 0 },
{ 50, 0 }
};

bool emparejado[5] = { false, false, false, false, false };


int main()
{
	parejas[0][1] = hombres[1][0];
	emparejado[hombres[1][0] - 1] = true;


	for (int i = 1; i < NPAREJAS; i++)
		estabilizar(i);


	for (int i = 0; i < NPAREJAS; i++)
		cout << "El hombre " << parejas[i][0] << " quedo con la mujer " << parejas[i][1] << endl;

	cout << "\n\nLa complejidad O(h^2*m)\n";

	return 0;
}

int busquedaHombre(int m)
{

	for (int i = 0; i < NPAREJAS; i++)
	{
		if (m == parejas[i][1])
			return parejas[i][0];
	}

}

void estabilizar(int h)
{

	for (int j = 1; j <= NPAREJAS; j++)
	{
		if (!emparejado[hombres[j][h] - 1])
		{
			parejas[h][1] = hombres[j][h];
			emparejado[hombres[j][h] - 1] = true;
			break;
		}
		else
		{
			int hombre = busquedaHombre(hombres[j][h]);
			for (int k = 1; k <= NPAREJAS; k++)
			{

				if (mujeres[k][hombres[j][h] - 1] == hombres[0][h])
				{

					parejas[h][1] = hombres[j][h];
					parejas[(hombre / 10) - 1][1] = 0;
					estabilizar((hombre / 10) - 1);
					j = 1000;
					break;
				}
				else
				{
					if (mujeres[k][hombres[j][h] - 1] == hombre)
						break;
				}
			}
		}
	}

}
