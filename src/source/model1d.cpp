#include "model1d.h"
#include <iostream>
#include "wyjatki.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

Model1D::Model1D(int N, double P)
{
    if ((P > 1) || (P<0))
        throw zle_Q();

    if (N <= 2)
        throw zle_N();

    double a; /** < losowa liczba, z ktora porownujemy prawdopodobienstwo P wylosowania wartosci 1. */
    srand(unsigned (time(NULL)));

    for(int i = 0; i<N; i++)
    {
        a = (double)rand()/RAND_MAX;
        if (a <= P)
            v.push_back(1);
        else
            v.push_back(0);
    }
}


Model1D::Model1D(vector <int> v1)
{
    int size = (int)v1.size(); /** < zmienna pomocnicza */

    for(int i = 0; i<size;i++)
    {
        if ( (v1[i] != 1) && (v1[i] != 0) )
            throw zle_W();

        v.push_back(v1[i]);
    }
}

int Model1D::run(int n)
{
    int size = getSize(); /** < zmienna pomocnicza */

    if (n<0)
        throw zle_k();

    for (int i = 0; i<n; i++)
    {
        step();
        int suma = getSum(); /** < zmienna pomocnicza */

        if (suma == size || suma == 0 )
            break;
    }

    int x = steps_number; /** < zmienna pomocnicza */
    steps_number = 0;

    return x;
}

void Model1D::step()
{
    int size = (int)v.size(); /** < zmienna pomocnicza */

    switch (getMethod())
    {
        case random_:
        {
            for (int i = 0; i<size; i++)
            {
                int x = rand()%size; /** < losowanie indeksu wektora v */
                basic_step(x);
                steps_number++;
                int suma = getSum(); /** < zmienna pomocnicza */

                if (suma == size || suma == 0 )
                    break;
            }
            break;
        }

        case random_unique:
        {
            vector <int> w; /** < wektor pomocniczy, w ktorym umieszczone sa losowe indeksy bez powtorzen */
            for (int i = 0; i<size; i++)
                w.push_back(i);

            random_shuffle(w.begin(), w.end());

            for (int i = 0; i<size; i++)
            {
                basic_step(w[i]);
                steps_number++;
                int suma = getSum(); /** < zmienna pomocnicza */

                if (suma == size || suma == 0 )
                    break;
            }
            w.erase(w.begin(),w.end());
            break;

        }

        case in_sequence:
        {
            for(int i = 0; i<size; i++)
            {
                basic_step(i);
                steps_number++;
                int suma = getSum(); /** < zmienna pomocnicza */

                if (suma == size || suma == 0 )
                    break;
            }
            break;
        }

        case every_other:
        {
            for(int i = 0; i<size; i+=2)
            {
                basic_step(i);
                steps_number++;
                int suma = getSum(); /** < zmienna pomocnicza */

                if (suma == size || suma == 0 )
                    break;
            }

            for(int i = 1; i<size; i+=2)
            {
                basic_step(i);
                steps_number++;
                int suma = getSum(); /** < zmienna pomocnicza */

                if (suma == size || suma == 0 )
                    break;
            }
            break;
        }

    }
}



void Model1D::basic_step(int i)
{
    int size = (int)v.size(); /** < zmienna pomocnicza */
    BC my_bc = getBC();
    double alpha = getAlpha();
    double beta = getBeta();

    if (size<=i || i<0)
        throw zle_i();


    double x = ((rand()*1.0)/RAND_MAX); /** < losowa liczba, z ktora porownujemy prawdopodobienstwo wplywu zewnetrznego beta */

    if(x<beta)
        v[i] = 1 - v[i];

    double y = ((rand()*1.0)/RAND_MAX); /** < losowa liczba, z ktora porownujemy prawdopodobienstwo przekonywania sasiada alpha */

    //porownanie wartosci z wartoscia sasiada
    if(v[(i+size)%size] == v[(i+size+1)%size])
    {
        if(y<=alpha)
        {
            if((my_bc == rigid && i == 0) || my_bc == periodic)
                v[(i+size+2)%size] = v[(i+size)%size];
            if((my_bc == rigid && i == size-1) || my_bc == periodic)
                v[(i+size-1)%size] = v[(i+size)%size];
        }
    }
    else
    {
        if(y<=alpha)
        {
            if((my_bc == rigid && i == 0) || my_bc == periodic)
                v[(i+size+2)%size] = v[(i+size)%size];
            if((my_bc == rigid && i == size-1) || my_bc == periodic)
                v[(i+size-1)%size] = v[(i+size+1)%size];
        }
    }
}

int Model1D::getSize() const {return (int)v.size();}

int Model1D::getSum() const
{
    int sum = 0;
    int size = (int)v.size(); /** < zmienna pomocnicza */

    for (int i = 0; i<size; i++)
        sum+=v[i];

    return sum;
}

vector <int> Model1D::getState() const { return v;}

int Model1D::state (size_t i) const
{
    if (v.size()<=i)
        throw zle_i();

    return v[i];
}

double Model1D::getConcentration() const
{
    int sum = getSum();
    int size = getSize();

    double conc = sum*1.0/size;

    return conc;
}

ostream & operator<<(ostream & out, const Model1D & model)
{
    vector <int> tmp = model.getState();
    int size = (int)tmp.size(); /** < zmienna pomocnicza */

    for(int i = 0; i<size; i++)
        out<<tmp[i]<<", ";

    out<<endl;
    return out;
}

