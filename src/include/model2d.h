#ifndef MODEL2D_H
#define MODEL2D_H
#include "model.h"

using namespace std;

class Model2D : public Model
{
    vector <int> v;         /** < Wektor v zawierajacy kolejne opinie - wartości z przedzialu {0,1} */
    double alpha;               /** < Wartosc prawdopodobienstwa przekonywania sasiada */
    int steps_number = 0;   /** < Liczba wykonanych krokow symulacji */
    vector <double> conc;    /** < Wektor conc zawierajacy wartosci koncentracji po kolejnych wywolaniach funkcji step() */
    int row;
    int col;

        /**
        *   Funkcja okreslajaca wybór i elementu do sprawdzenia.
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
        *   Przyjmuje dwie wartosci typu int, jedna wartosc typu double.
        *
        *   \param[in] a - dlugosc wektora v.
        *   \param[in] b - dlugosc wektora v.
        *   \param[in] P - prawdopodobienstwo z jakim losowana jest wartosc 1.
        */
    Model2D(int a, int b, double P=0.5);

        /**
        *   Konstruktor przypisujacy pobrany vector v1 do wektora v.
        *   Przyjmuje vector typu int.
        *
        *   \param[in] v1 - vector, który przypisujemy wektorowi v.
        */
    Model2D(vector<int> v1, int r, int c);

        /**
        *   Funkcja rozpoczynajaca proces przekonywania sasiadów.
        *   Przyjmuje jeden parametr typu int. Zwraca wartosc typu int.
        *
        *   \param[in] time - maksymalna ilosc krokow jaka program ma wykonac w poszukiwaniu rozwiazania.
        *   \return x - liczba krokow symulacji (liczba wywołań funkcji basic_step).
        */
    int run(int time);

        /**
        *   Funkcja zwracająca wektor ze wspolrzednymi wszystkich sasiadow punktu (i, j).
        *
        *   /param[in] i, j - wspolrzedne punktu
        */
    vector <int> neighbors(int i) const;

        /**
        *   Funkcja zwracająca wektor ze wspolrzednymi dwoch sasadow punktu (i, j) dla sztywnych warunkow brzegowych.
        *
        *   /param[in] i, j - wspolrzedne punktu
        */
    vector <int> neighbors2(int i) const;

        /**
        *   Funkcja zwracająca wektor ze wspolrzednymi trzech sasadow punktu (i, j) dla sztywnych warunkow brzegowych.
        *
        *   /param[in] i, j - wspolrzedne punktu
        */
    vector <int> neighbors3(int i) const;

        /**
         *  Funkcja zwracajaca liczbe wierszy tablicy.
         *
         *  \return r - liczba wierszy
         */
    int getRow() const;

        /**
         *  Funkcja zwracajaca liczbe kolumn tablicy.
         *
         *  \return c - liczba kolumn
         */
    int getCol() const;

        /**
        *   Funkcja zwracajaca liczbe elementow typu int wektora v.
        *   Zwraca wartosc typu int.
        *
        *   \return size - liczbe elementow typu int wektora v.
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

        /**
        *   Funkcja zwracajaca stan wektora conc
        *
        *   \return conc - stan wektora conc
        */
    vector <double> getStateConc() const;


        /**
        *   Funkcja zwracajaca rozmiar wektora conc
        *
        *   \return sizeConc - rozmiar wektora conc
        */
    int getSizeConc() const;
};

        /**
        *   Przeciazony operator << wypisujacy stan wektora v.
        */
    ostream & operator<<(ostream & out, const Model2D & model);

#endif // MODEL2D_H
