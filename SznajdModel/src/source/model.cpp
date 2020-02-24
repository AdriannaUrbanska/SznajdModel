#include "model.h"
#include "wyjatki.h"

using namespace std;

void Model::setAlpha(double a)
{
    if (a<0 || a>1) 
        throw zle_Q();

    alpha = a;
}

void Model::setBeta(double b)
{
    if (b<0 || b>1)
        throw zle_Q();

    beta = b;
}

void Model::setBC(BC a) {my_bc = a;}

void Model::setMethod(Method a) {my_method = a;}

double Model::getAlpha() const {return alpha;}

double Model::getBeta() const {return beta;}

Model::BC Model::getBC() const {return my_bc;}

Model::Method Model::getMethod() const {return my_method;}

string Model::getBCName(Model::BC BC_)
{
    switch (BC_) {
        case periodic:
        {
            return "periodic";
            break;
        }
        case rigid:
        {
            return "rigid";
            break;
        }
        default:
        {
            return "Bledny typ";
            break;
        }
    }
}

string Model::getMethodName(Model::Method Method_)
{
    switch (Method_) {
        case random_:
        {
            return "random_";
            break;
        }
        case random_unique:
        {
            return "random_unique";
            break;
        }
        case in_sequence:
        {
            return "in_sequence";
            break;
        }
        case every_other:
        {
            return "every_other";
            break;
        }
        default:
        {
            return "Bledny typ";
            break;
        }
    }
}
