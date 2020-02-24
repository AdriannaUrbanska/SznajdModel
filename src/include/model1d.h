#ifndef MODEL1D_H
#define MODEL1D_H
#include "model.h"

using namespace std;

    /**
    *	Klasa zawierajaca elementy modelu Sznajdow.
    */
class Model1D : public Model
{
    vector <int> v;         /** < wektor v zawierajacy kolejne opinie - wartości z przedzialu {0,1} */
    double alpha;               /** < Wartosc prawdopodobienstwa przekonywania sasiada */
    int steps_number = 0;   /** < Liczba wykonanych krokow symulacji */

        /**
        *   Funkcja okreslajaca wybór i-tego elementu do sprawdzenia.
        */
    void step();

        /**
        *   Funkcja sprawdzajaca czy sasiad i-tej osoby (i+1) ma taka sama opinie, porownywujaca opinie sasiadow i-1 oraz i+2.
        *   Przyjmuje jeden parametr typu int.
        *
        *   /param[in] i - osoba, od której zaczyna sie sprawdzanie opnii.
        */
    void basic_step(int i);

public:

        /**
        *   Konstruktor ustawiajacy losowo wartosci {0,1} dla wektora v.
        *   Przyjmuje jedna wartosc typu int, jedna wartosc typu double.
        *
        *   \param[in] N - dlugosc wektora v.
        *   \param[in] P - prawdopodobienstwo z jakim losowana jest wartosc 1.
        */
    Model1D(int N, double P = 0.5);

        /**
        *   Konstruktor przypisujacy pobrany vector v1 do wektora v.
        *   Przyjmuje vector typu int.
        *
        *   \param[in] v1 - vector, który przypisujemy wektorowi v.
        */
    Model1D(vector <int> v1);

        /**
        *   Funkcja rozpoczynajaca proces przekonywania sasiadów.
        *   Przyjmuje jeden parametr typu int. Zwraca wartosc typu int.
        *
        *   \param[in] n - maksymalna ilosc krokow jaka program ma wykonac w poszukiwaniu rozwiazania.
        *   \return x - liczba krokow symulacji (liczba wywołań funkcji basic_step).
        */
    int run(int n);

        /**
        *   Funkcja zwracajaca dlugosc wektora v.
        *   Zwraca wartosc typu int.
        *
        *   \return size - rozmiar wektora v.
        */
   int getSize() const;

        /**
        *   Funkcja sumujaca wartosci wektora v.
        *   Zwraca wartosc typu int.
        *
        *   \return s - suma elementów wektora v.
        */
   int getSum() const;

        /**
        *   Funkcja zwracajaca obecny stan wektora v.
        *   Zwraca wartosc typu vector <int>.
        *
        *   \return v - obecny stan wektora.
        */
    vector <int> getState() const;

        /**
        *   Funkcja zwracajaca stan i-tego elementu wektora v.
        *   Zwraca wartosc typu int.
        *
        *   \param[in] i - indeks elementu wektora v, ktorego wartosc ma byc zwrocona.
        *   \return n - i-ty element wektora v.
        */
    int state (size_t i) const;

        /**
        *   Funkcja zwracajaca wartosc koncentracji wektora v
        *   - iloraz sumy elementow przez całkowita liczbe elementow.
        *
        *   \return conc - koncentracja wektora v.
        */
    double getConcentration() const;



};

        /**
        *   Przeciazony operator << wypisujacy stan wektora v.
        */
    ostream & operator <<(ostream & out, const Model1D & model);

#endif // MODEL1D_H
