#include "derivative.h"

string derivative(string wyrazenie) {
	derTable drabina;
	drabina.dividing(wyrazenie);
	drabina.derivativeIt(drabina.getDivided(), drabina.getCheckToDerivative());
	wyrazenie = drabina.makeString();
	return wyrazenie;//zwraca obliczon¹ pochodna
}
