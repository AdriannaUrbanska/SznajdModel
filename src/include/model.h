#ifndef KLASY_H
#define KLASY_H
#include <iostream>
#include <vector>

using namespace std;

    /**
    *	Klasa zawierajaca elementy modelu Sznajdow.
    */
class Model
{
    vector <int> v;         /** < wektor v zawierajacy kolejne opinie - wartości z przedzialu {0,1} */
    double alpha;           /** < Wartosc prawdopodobienstwa przekonywania sasiada */
    double beta;            /** < Wartosc prawdopodobienstwa wplywu zewnetrznego */
    int steps_number = 0;   /** < Liczba wykonanych krokow symulacji */

public:

        /**
        *   Wyliczenie zawierajace rodzaje warunkow brzegowych.
        */
    enum BC
    {
            periodic = 1, 	/** < periodyczne warunki brzegowe */
            rigid		/** < sztywne warunki brzegowe */
    };

        /**
        *   Wyliczenie zawierajace metody wybierania opinii do sprawdzenia
        */
    enum Method
    {
            random_ = 1,	/** < wybieranie opinii losowo */
            random_unique,	/** < wybieranie opinii losowo bez powtorzen */
            in_sequence,	/** < wybieranie opinii kolejno od poczatku */
            every_other		/** < wybieranie co drugiej opinii*/
    };

private:

    BC my_bc;           /** < enum dotyczacy wyboru rodzaju warunkow brzegowych*/
    Method my_method;   /** < enum dotyczacy metody wybierania opinii do sprawdzania*/


public:

        Model(){}

        /**
        *   Funkcja ustawiajaca wartosc prawdopodobienstwa przekonywania sasiada.
        *   Przyjmuje jeden parametr typu double.
        *
        *   \param[in] a - prawdopodobienstwo przekonywania sasiada
        */
    void setAlpha(double a = 0.5);

        /**
        *   Funkcja ustawiajaca wartosc prawdopodobienstwa wplywu zewnetrznego.
        *   Przyjmuje jeden parametr typu double.
        *
        *   \param[in] b - prawdopodobienstwo wplywu zewnetrznego
        */
    void setBeta(double b = 0.5);

        /**
        *   Funkcja ustawia typ warunków brzegowych BC {periodic, rigid}.
        *   Przyjmuje jeden parametr typu enum BC.
        *
        *   \param[in] a - typ warunków brzegowych
        */
    void setBC(BC a = Model::periodic);

        /**
        *   Funkcja ustawia metode wybierania opinii do sprawdzenia Method {random_, random_unique, in_sequence, every_other}.
        *   Przyjmuje jeden parametr typu enum Method.
        *
        *   \param[in] a - metoda wybierania opinii do sprawdzenia.
        */
    void setMethod(Method a = Model::random_);


        /**
        *   Funkcja, dzieki której mozna dostac sie do prywatnego parametru alpha (prawdopodobienstwo przekonywania) obiektu.
        *   Zwraca wartosc typu double.
        *
        *   \return alpha - prawdopodobienstwo przekonywania sasiada.
        */
    double getAlpha() const;

        /**
        *   Funkcja, dzieki której mozna dostac sie do prywatnego parametru beta (prawdopodobienstwo wplywu zewnetrznego) obiektu.
        *   Zwraca wartosc typu double.
        *
        *   \return beta - prawdopodobienstwo przekonywania sasiada.
        */
    double getBeta() const;

        /**
        *   Funkcja, dzieki której mozna dostac sie do prywatnego parametru BC (typ warunków brzegowych) obiektu.
        *   Zwraca wartosc typu enum BC.
        *
        *   \return b - typ warunkow brzegowych.
        */
    BC getBC() const;

        /**
        *   Funkcja, dzieki której mozna dostac sie do prywatnego parametru X (metoda losowania i-tego elementu) obiektu.
        *   Zwraca wartosc typu enum Method.
        *
        *   \return m - metoda losowania i-tego elementu.
        */
   Method getMethod() const;

       /**
       *    Statyczna funkcja zwracajaca nazwe podanego warunku brzegowego BC_
       *    Zwraca wartosc typu std::string.
       *
       *    \return std::string s - nazwa podanego warunku brzegowego.
       */
   static string getBCName(BC BC_);

       /**
       *    Statyczna funkcja zwracajaca nazwe podanej metody Method_
       *    Zwraca wartosc typu std::string.
       *
       *    \return std::string s - nazwa podanej metody.
       */
   static string getMethodName(Method Method_);
};

#endif





