#ifndef WYJATKI_H
#define WYJATKI_H
#include <iostream>
#include <stdexcept>

using namespace std;

    /**
    *   Klasa wyjatkow - komunikatow wyswietlanych po wpisaniu zlych danych.
    */
class zla_wartosc : public exception
{
public:

        zla_wartosc(){}
};


    /**
    *   Klasa wyswietlajaca komunikat o wpisaniu zlej wartosci prawdopodobienstwa przekonywania.
    */
class zle_Q : public zla_wartosc
{
public:

        zle_Q() : zla_wartosc() {}
        virtual const char* what() const noexcept { return "Wartosc prawdopodobienstwa musi byc z przedzialu [0,1]!";}
};

    /**
    *   Klasa wyswietlajaca komunikat o wpisaniu zlej wartosci rozmiaru wektora.
    */
class zle_N : public zla_wartosc
{
public:

        zle_N() : zla_wartosc() {}
        virtual const char* what() const noexcept { return "Rozmiar wektora musi byc wiekszy od 2";}
};

    /**
    *	Klasa wyswietlajaca komunikat o wpisaniu zlej wartosci do wektora.
    */
class zle_W : public zla_wartosc
{
public:

        zle_W() : zla_wartosc() {}
        virtual const char* what() const noexcept { return "Przekazany wektor musi miec wartosci 0 lub 1";}
};

    /**
    *	Klasa wyswietlajaca komunikat o wpisaniu indeksu wiekszego od rozmiaru wektora.
    */
class zle_i : public zla_wartosc
{
public:

        zle_i() : zla_wartosc() {}
        virtual const char* what() const noexcept { return "Wektor nie posiada tylu elementow!";}
};

    /**
    *	Klasa wyswietlajaca komunikat o wpisaniu zlej wartosci liczby krokow.
    */
class zle_k : public zla_wartosc
{
public:

        zle_k() : zla_wartosc() {}
        virtual const char* what() const noexcept { return "Liczba krokow musi byc dodatnia!";}
};

#endif
