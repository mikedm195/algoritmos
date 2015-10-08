#include <iostream>
#include <vector>

using namespace std;


vector<int> posicion = {7, 13, 24, 34, 40, 44, 55, 60, 69, 75};

vector<int> camionero(int maxKilometraje);


main(){
    int maxKilometraje;
	// Ejercicio 1

	cout << "Km en los que se encuentran las gasolineras:: " << endl;
	for (auto km:posicion)
		cout << km << ", ";
	cout << endl;

	cout << "Cuantos km aguanta el tanque de gasolina?: " << endl;
	cin >> maxKilometraje;

	vector<int> solucion = camionero(maxKilometraje);

	cout << "Resultado ejercicio 1:" << endl;
	for (auto km:solucion)
		cout << km << ", ";
	cout << endl;

	return 0;
}

vector<int> camionero(int maxKilometraje){
	vector<int> solucion;
	int kmActual = 0;
	int distancia=0;
	for(int i = 0; i < posicion.size()-1;i++){
        distancia = posicion[i+1] - kmActual;
        if((posicion[i+1]-posicion[i])>maxKilometraje){
            solucion.clear();
            return solucion;
        }
        if(distancia > maxKilometraje){
            kmActual=posicion[i];
            solucion.push_back(kmActual);
        }
	}
	return solucion;
}

