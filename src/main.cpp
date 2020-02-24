#include "model.h"
#include "model1d.h"
#include "model2d.h"
#include "wyjatki.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <omp.h>
#include <string>

using namespace std;

int main()
{
    /**
    *   1. Model1D - wlasny wektor w konstruktorze
    *   2. Model1D - rozmiar i prawdopodobieństwo w konstruktorze
    *   3. Model2D - wlasny wektor w konstruktorze
    *   4. Model2D - rozmiar i prawdopodobieństwo w konstruktorze
    *   5. Badanie zaleznosci concentration(alpha)
    *   6. Badanie zaleznosci concentration(time)
    *   7. Badanie zaleznosci concentration(beta)
    *   8. Badanie zaleznosc conc_final(conc_initial)
    */

    int number_of_model = 4; /** < zmienna okreslajaca ktory model jest testowany */

    // TODO zrob...
    // FIXME napraw... 

    /**
    *   Dane do testowania:
    *
    *   Size_
    *   Alpha_
    *   Beta_
    *   P_
    *   BC_
    *   Method_
    *   Time_
    *
    */

    int Size_ = 51;
    double Alpha_;
    double Beta_;
    double P_ = 0.5;
    Model::Method Method_ = Model::random_;
    Model::BC BC_ = Model::periodic;
    int Time_ = 10000;

    try
    {
        switch(number_of_model)
        {
            case 1:
            {
                //Model1D - wlasny wektor w konstruktorze
                vector <int> t1;

                srand(unsigned (time(NULL)));

                for(int j = 0; j<10; j++)
                    t1.push_back(rand()%2);

                Model1D m1_1D(t1);
                cout<<m1_1D;
                m1_1D.setAlpha(0.9);
                m1_1D.setBeta(0.1);
                m1_1D.setBC(Model::periodic);
                m1_1D.setMethod(Model::in_sequence);
                cout<<"Alpha = "<<m1_1D.getAlpha()<<endl;
                cout<<"BC: "<<m1_1D.getBCName(Model::periodic)<<endl;
                cout<<"Method: "<<m1_1D.getMethodName(Model::in_sequence) <<endl;
                cout<<"Suma elementow: "<<m1_1D.getSum()<<endl;
                cout<<"I-ty element wektora: "<<m1_1D.state(4)<<endl;
                cout<<"Koncentracja: "<<m1_1D.getConcentration()<<endl;
                cout<<"Liczba krokow: "<<m1_1D.run(1000)<<endl;
                cout<<m1_1D<<endl;
                t1.erase(t1.begin(), t1.end());
                break;
            }

            case 2:
            {
                //Model1D - rozmiar i prawdopodobieństwo w konstruktorze
                Model1D m2_1D(10,0.5);
                cout<<m2_1D;
                m2_1D.setAlpha(0.5);
                m2_1D.setBeta(0.1);
                m2_1D.setBC(Model::periodic);
                m2_1D.setMethod(Model::random_unique);
                cout<<"Alpha = "<<m2_1D.getAlpha()<<endl;
                cout<<"BC: "<<m2_1D.getBCName(Model::periodic)<<endl;
                cout<<"Method: "<<m2_1D.getMethodName(Model::random_unique) <<endl;
                cout<<"Suma elementow: "<<m2_1D.getSum()<<endl;
                cout<<"I-ty element wektora: "<<m2_1D.state(4)<<endl;
                cout<<"Koncentracja: "<<m2_1D.getConcentration()<<endl;
                cout<<"Liczba krokow: "<<m2_1D.run(1000)<<endl;
                cout<<m2_1D<<endl;
                break;
            }

            case 3:
            {
                //Model2D - wlasny wektor w konstruktorze
                vector <int> t;

                srand(unsigned (time(NULL)));

                for(int i = 0; i<30; i++)
                    t.push_back(rand()%2 );

                Model2D m1_2D(t,5,6);
                cout<<m1_2D;
                m1_2D.setAlpha(0.9);
                m1_2D.setBeta(0.1);
                m1_2D.setBC(Model::periodic);
                m1_2D.setMethod(Model::random_unique);
                cout<<"Alpha = "<<m1_2D.getAlpha()<<endl;
                cout<<"BC: "<<m1_2D.getBCName(Model::periodic)<<endl;
                cout<<"Method: "<<m1_2D.getMethodName(Model::random_unique) <<endl;
                cout<<"Suma elementow: "<<m1_2D.getSum()<<endl;
                cout<<"I-ty element wektora: "<<m1_2D.state(4)<<endl;
                cout<<"Koncentracja: "<<m1_2D.getConcentration()<<endl;
                cout<<"Liczba krokow: "<<m1_2D.run(1000)<<endl;
                cout<<m1_2D<<endl;
                t.erase(t.begin(), t.end());
                break;
            }

            case 4:
            {
                //Model1D - rozmiar i prawdopodobieństwo w konstruktorze
                Model2D m2_2D(8,10,0.5);
                cout<<m2_2D;
                m2_2D.setAlpha(0.5);
                m2_2D.setBeta(0.1);
                m2_2D.setBC(Model::periodic);
                m2_2D.setMethod(Model::random_unique);
                cout<<"Alpha = "<<m2_2D.getAlpha()<<endl;
                cout<<"BC: "<<m2_2D.getBCName(Model::periodic)<<endl;
                cout<<"Method: "<<m2_2D.getMethodName(Model::random_unique)<<endl;
                cout<<"Suma elementow: "<<m2_2D.getSum()<<endl;
                cout<<"I-ty element wektora: "<<m2_2D.state(4)<<endl;
                cout<<"Koncentracja: "<<m2_2D.getConcentration()<<endl;
                cout<<"Liczba krokow: "<<m2_2D.run(1000)<<endl;
                cout<<m2_2D<<endl;
                break;
            }

            case 5:
            {
                //Badanie zaleznosci concentration(alpha)

                int points_number = 101;

                double alpha[points_number];
                for(int i = 0; i<points_number; i++)
                    alpha[i] = i*0.01;

                double conc[points_number];

                fstream plik;
                plik.open("dane_alpha.txt", ios::out);
                plik<<"Size: " + std::to_string(Size_)+ "x" + std::to_string(Size_)+ "\n";
                plik<<"P = " + std::to_string(P_) + "\n";
                plik<<"Beta = 0.1\n";
                plik<<"Method = " + Model::getMethodName(Method_) + "\n";
                plik<<"BC = " + Model::getBCName(BC_) + "\n";
                plik<<"Time =" + std::to_string(Time_)+ "\n\n";
                plik<<"alpha\t conc \n";

                #pragma omp parallel for schedule(static)
                for(int i = 0; i<points_number; i++)
                {
                    Model2D model(Size_,Size_,P_);
                    model.setAlpha(alpha[i]);
                    model.setBeta(0.1);
                    model.setBC(BC_);
                    model.setMethod(Method_);
                    int x = model.run(Time_);
                    conc[i] = model.getConcentration();
                    cout<<i<<endl;
                }

                for(int i = 0; i<points_number; i++)
                    plik<<alpha[i]<<"\t"<<conc[i]<<"\n";

                plik.close();
                break;
            }

            case 6:
            {
                //Badanie zaleznosci concentration(time)

                fstream plik;
                plik.open("dane.txt", ios::out);
                plik<<"Size: " + std::to_string(Size_)+ "x" + std::to_string(Size_)+ "\n";
                plik<<"P = " + std::to_string(P_) + "\n";
                plik<<"Alpha = 0.5\n";
                plik<<"Beta = 0.1";
                plik<<"Method = " + Model::getMethodName(Method_) + "\n";
                plik<<"BC = " + Model::getBCName(BC_) + "\n";
                plik<<"Time = " + std::to_string(Time_)+ "\n\n";

                plik<<"time\t conc \n";

                Model2D model(Size_,Size_,P_);
                model.setAlpha(0.5);
                model.setBeta(0.1);
                model.setBC(BC_);
                model.setMethod(Method_);
                int x = model.run(Time_);
                int size_conc = model.getSizeConc();
                vector <double> c = model.getStateConc();

                for(int i = 0; i<size_conc; i++)
                {
                    plik<<i<<"\t"<<c[i]<<"\n";
                }

                plik.close();
                break;
            }

            case 7:
            {
                //Badanie zaleznosci concentration(beta)

                int points_number = 201;

                double beta[points_number];
                for(int i = 0; i<points_number; i++)
                    beta[i] = i*0.001;

                double conc[points_number];

                fstream plik;
                plik.open("dane_beta.txt", ios::out);
                plik<<"Size: " + std::to_string(Size_)+ "x" + std::to_string(Size_)+ "\n";
                plik<<"P = " + std::to_string(P_) + "\n";
                plik<<"Alpha = 1\n";
                plik<<"Method = " + Model::getMethodName(Method_) + "\n";
                plik<<"BC = " + Model::getBCName(BC_) + "\n";
                plik<<"Time = " + std::to_string(Time_)+ "\n\n";
                plik<<"beta\t conc \n";

                #pragma omp parallel for schedule(static)
                for(int i = 0; i<points_number; i++)
                {
                    Model2D model(Size_,Size_,P_);
                    model.setAlpha(1);
                    model.setBeta(beta[i]);
                    model.setBC(BC_);
                    model.setMethod(Method_);
                    int x = model.run(Time_);
                    conc[i] = model.getConcentration();
                    cout<<i<<endl;
                }

                for(int i = 0; i<points_number; i++)
                    plik<<beta[i]<<"\t"<<conc[i]<<"\n";

                plik.close();
                break;
            }

            case 8:
            {
                //Badanie zaleznosci conc_final(conc_initial)

                int points_number = 101;

                double P[points_number];
                for(int i = 0; i<points_number; i++)
                    P[i] = i*0.01;

                double conc[points_number];

                fstream plik;
                plik.open("dane_conc.txt", ios::out);
                plik<<"Size: " + std::to_string(Size_)+ "x" + std::to_string(Size_)+ "\n";
                plik<<"Alpha = 1\n";
                plik<<"Beta = 0.1";
                plik<<"Method = " + Model::getMethodName(Method_) + "\n";
                plik<<"BC = " + Model::getBCName(BC_) + "\n";
                plik<<"Time = " + std::to_string(Time_)+ "\n\n";
                plik<<"conc_initial\t conc_final \n";

                #pragma omp parallel for schedule(static)
                for(int i = 0; i<points_number; i++)
                {
                    Model2D model(Size_,Size_,P[i]);
                    model.setAlpha(1);
                    model.setBeta(0.1);
                    model.setBC(BC_);
                    model.setMethod(Method_);
                    int x = model.run(Time_);
                    conc[i] = model.getConcentration();
                    cout<<i<<endl;
                }

                for(int i = 0; i<points_number; i++)
                    plik<<P[i]<<"\t"<<conc[i]<<"\n";

                plik.close();
                break;
            }
        }

    } catch(zla_wartosc & e)
    {
            cout<<e.what()<<endl;
    }
}
