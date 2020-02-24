#include "model2d.h"
#include "wyjatki.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

Model2D::Model2D(int a, int b, double P) : row(a), col(b)
{
    if ((P > 1) || (P<0))
        throw zle_Q();

    if (a <= 3 || b <=2)
        throw zle_N();

    double r; /** < losowa liczba, z ktora porownujemy prawdopodobienstwo P wylosowania wartosci 1. */
    srand(unsigned (time(NULL)));

    int size = getSize();

    for(int i = 0; i<size; i++)
    {
        r = (double)rand()/RAND_MAX;
        if (r <= P)
            v.push_back(1);
        else
            v.push_back(0);
    }
}

Model2D::Model2D(vector<int> v1, int r, int c) : row(r), col(c)
{
    int size = getSize();

    for(int i = 0; i<size; i++)
    {
        if ( (v1[i] != 1) && (v1[i] != 0) )
                throw zle_W();

        v.push_back(v1[i]);
    }
}

int Model2D::run(int time)
{
    if (time<0)
        throw zle_k();

    for (int i = 0; i<time; i++)
    {
        step();
        conc.push_back(getConcentration());
        int suma = getSum(); /** < zmienna pomocnicza */

//        if (suma == size || suma == 0 )
//            break;
    }

    int x = steps_number; /** < zmienna pomocnicza */
    steps_number = 0;

    return x;
}

void Model2D::step()
{
    int size = getSize();

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
            vector <int> w1; /** < wektor pomocniczy, w ktorym umieszczone sa losowe indeksy bez powtorzen */

            for(int i = 0; i<size; i++)
                w1.push_back(i);

            random_shuffle(w1.begin(), w1.end());

            for (int i = 0; i<size; i++)
            {
                basic_step(w1[i]);
                steps_number++;
                int suma = getSum(); /** < zmienna pomocnicza */

                if (suma == size || suma == 0 )
                    break;
            }

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
            if(col%2)
            {
                for(int i = 0; i<size; i+=2)
                {
                    basic_step(i);
                    steps_number++;

                    int suma = getSum(); /** < zmienna pomocnicza */

                    if (suma == size || suma == 0 )
                        break;
                }

                for(int i = 1; i<size; i++)
                {

                    basic_step(i);
                    steps_number++;

                    int suma = getSum(); /** < zmienna pomocnicza */

                    if (suma == size || suma == 0 )
                        break;
                }
            }
            //FIXME

            /*else
            {
                for(int j = 0; j<size; i+=2)
                {
                    for(int i = j*col; i<(j+1)*col; i+=2)
                    {
                        basic_step(i);
                        steps_number++;

                        int suma = getSum(); /** < zmienna pomocnicza *//*

                        if (suma == size || suma == 0 )
                            break;
                    }
                }

                for(int i = 1; i<size; i++)
                {

                    basic_step(i);
                    steps_number++;

                    int suma = getSum(); /** < zmienna pomocnicza *//*

                    if (suma == size || suma == 0 )
                        break;
                }
            } */
            break;
        }
    }
}

void Model2D::basic_step(int i)
{
    int size = getSize();

    double alpha = getAlpha();
    double beta = getBeta();

    if (size<=i || i<0)
        throw zle_i();

    double x = ((rand()*1.0)/RAND_MAX); /** < losowa liczba, z ktora porownujemy prawdopodobienstwo wplywu zewnetrznego beta */

    //wplyw zewnetrzny
    if(x < beta)
        v[i] = 1 - v[i];


    // sasiedzi wybranego indeksu i
    vector <int> w = neighbors(i);
    int size_w = (int)w.size();

    // losowanie sasiada do porownania opinii
    random_shuffle(w.begin(), w.end());

    // wylosowany sasiad do porownania opinii o indeksie i2 - pierwszy wektor z przetasowanego wektora w
    int i2 = w[0];

    // sasiedzi wybranego sasiada i2
    vector <int> w2 = neighbors(i2);
    int size_w2 = (int)w2.size();


    int tmp = v[i]; /** < zmienna pomocnicza zapamietujaca pierwsza wartosc v[i][j] */
    double y = ((rand()*1.0)/RAND_MAX); /** < losowa liczba, z ktora porownujemy prawdopodobienstwo przekonywania sasiada alpha */

    // porownanie wartosci punktu o indeksie i z wartoscia wybranego sasiada i2
    if(v[i] == v[i2])
    {
        if(y<=alpha)
        {
            // przekonywanie sasiadow punktu o indeksie i
            for(int k = 1; k<size_w; k++)
            {
                int i3 = w[k];
                v[i3] = tmp;
            }

            // przekonywanie sasiadow wybranego sasiada (i2,j2)
            // nie wiadomo, na ktorym miejscu jest tutaj punkt o indeksie i, tmp, aby ominac v[i] = v[i]
            for(int k = 0; k<size_w2; k++)
            {
                int i3 = w2[k];
                v[i3] = tmp;
            }
        }
    }
   /* else
    {
        if(y<=alpha)
        {
            // przekonywanie sasiadow punktu o indeksie i
            for(int k = 1; k<size_w; k++)
            {
                int i3 = w[k];
                v[i3] = v[i2];
            }

            // przekonywanie sasiadow wybranego sasiada i2
            for(int k = 0; k<size_w2; k++)
            {
                int i3 = w2[k];
                v[i3] = tmp;
            }
        }
    }*/
}

vector <int> Model2D::neighbors(int i) const
{
    int size = getSize();
    int col = getCol();

    if(getBC() == rigid)
    {
        // jezeli punkt o indeksie i znajduje sie w rogach - ma 2 sasiadow
        if( (i == 0) ||
            (i == col-1) ||
            (i == size-col-1) ||
            (i == size-1) )
            return neighbors2(i);

        // jezeli punkt o indeksie i znajduje sie na brzegach (ale nie w rogach) - ma 3 sasiadow
        if( (i>0 && i<col-1) ||
            (i != 0 && i != size-col-1 && i%col == 0) ||
            (i != col-1 && i != size-1 && i%col == col-1) ||
            (i>size-col-1 && i<size))
            return neighbors3(i);
    }

    vector <int> w;

    w.push_back((i+size-1)%size);
    w.push_back((i+size+1)%size);
    w.push_back((i+size-col)%size);
    w.push_back((i+size+col)%size);

    return w;
}

vector <int> Model2D::neighbors2(int i) const
{
    int size = getSize();
    int col = getCol();

    vector <int> w;

    if(i == 0)
    {
        w.push_back(i+1);
        w.push_back(i+col);
    }

    if(i == col-1)
    {
        w.push_back(i-1);
        w.push_back(i+col);
    }

    if(i == size-col-1)
    {
        w.push_back(i-col);
        w.push_back(i+1);
    }

    if(i == size-1)
    {
        w.push_back(i-1);
        w.push_back(i-col);
    }

    return w;
}

vector <int> Model2D::neighbors3(int i) const
{
    int size = getSize();
    int col = getCol();

    vector <int> w;

    if(i>0 && i<col-1)
    {
        w.push_back(i-1);
        w.push_back(i+1);
        w.push_back(i+col);
    }

    if(i != 0 && i != size-col-1 && i%col == 0)
    {
        w.push_back(i+1);
        w.push_back(i-col);
        w.push_back(i+col);
    }

    if(i != col-1 && i != size-1 && i%col == col-1)
    {
        w.push_back(i-1);
        w.push_back(i-col);
        w.push_back(i+col);
    }

    if(i>size-col-1 && i<size)
    {
        w.push_back(i-1);
        w.push_back(i+1);
        w.push_back(i-col);
    }

    return w;
}

int Model2D::getRow() const {return row;}

int Model2D::getCol() const {return col;}

int Model2D::getSize() const
{
    return row*col;
}

int Model2D::getSum() const
{
    int sum = 0;
    int size = getSize();

    for (int i = 0; i<size; i++)
    {
        sum+=v[i];
    }

    return sum;
}

vector <int> Model2D::getState() const {return v;}

int Model2D::state (size_t i) const
{
    if (v.size()<=i)
        throw zle_i();

    return v[i];
}

double Model2D::getConcentration() const
{
    int sum = getSum();
    int size = getSize();

    double conc = sum*1.0/size;

    return conc;
}

vector <double> Model2D::getStateConc() const { return conc;}

int Model2D::getSizeConc() const {return (int) conc.size();}


ostream & operator<<(ostream & out, const Model2D & model)
{
    vector <int> tmp = model.getState();
    int col = model.getCol();
    int size = tmp.size();

    for(int i = 0; i<size; i++)
    {
        out<<tmp[i]<<",";

        if(i%col == col-1)
            out<<std::endl;
    }

    return out;
}
