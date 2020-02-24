#include <QString>
#include <QtTest>
#include "model1d.h"
#include "wyjatki.h"

/**
*   Klasa testow dla metod modelu 1D oraz metod odziedziczonych po klasie Model
*/
class TestModel : public QObject
{
    Q_OBJECT

public:
    TestModel(){}

private Q_SLOTS:
    void testConstructor1();
    void testConstructor2();
    void testSetAlpha();
    void testSetBeta();
    void testSetBC();
    void testSetMethod();
    void testRun();
    void testGetSum();
    void testGetConcentration();
};

    /**
    *   Funkcja testujaca ustawienie parametru alpha:
    *   - czy przypisana wartosc jest rowna wartosci podanej
    *   - czy przy podaniu nieodpowiedniej wartosci zostanie wyrzucony wyjatek
    */
void TestModel::testSetAlpha()
{
    Model1D m(10);
    m.setAlpha(0.9);
    QCOMPARE(m.getAlpha(), 0.9);
    QVERIFY_EXCEPTION_THROWN(m.setAlpha(2), zla_wartosc);
    QVERIFY_EXCEPTION_THROWN(m.setAlpha(-1), zla_wartosc);
}

    /**
    *   Funkcja testujaca ustawienie parametru beta:
    *   - czy przypisana wartosc jest rowna wartosci podanej
    *   - czy przy podaniu nieodpowiedniej wartosci zostanie wyrzucony wyjatek
    */
void TestModel::testSetBeta()
{
    Model1D m(10);
    m.setBeta(0.9);
    QCOMPARE(m.getBeta(), 0.9);
    QVERIFY_EXCEPTION_THROWN(m.setBeta(2), zla_wartosc);
    QVERIFY_EXCEPTION_THROWN(m.setBeta(-1), zla_wartosc);
}

    /**
    *   Funkcja testujaca ustawienie parametru my_bc:
    *   - czy przypisana wartosc jest rowna wartosci podanej
    *   - czy metoda getBCName zwraca odpowiednia nazwe typu string
    */
void TestModel::testSetBC()
{
    Model1D m(10);
    Model::BC bc = Model::periodic;
    m.setBC(bc);
    QCOMPARE(m.getBC(), Model::periodic);
    QVERIFY(m.getBCName(bc) == "periodic");
}

    /**
    *   Funkcja testujaca ustawienie parametru my_method:
    *   - czy przypisana wartosc jest rowna wartosci podanej
    *   - czy metoda getMethodName zwraca odpowiednia nazwe typu string
    */
void TestModel::testSetMethod()
{
    Model1D m(10);
    Model::Method met = Model::random_;
    m.setMethod(met);
    QCOMPARE(m.getMethod(), Model::random_);
    QVERIFY(m.getMethodName(met) == "random_");
}

    /**
    *   Funkcja testujaca dzialanie konstruktora Model1D(int N, double P):
    *   - czy metoda getSize zwroci rozmiar podany jako argument
    *   - czy przy podaniu nieodpowiedniej wartosci rozmiaru lub prawdopodobieństwa zostanie wyrzucony wyjatek
    */
void TestModel::testConstructor1()
{
    QCOMPARE(Model1D(10).getSize(), 10);
    QVERIFY_EXCEPTION_THROWN(Model1D(1), zla_wartosc);
    QVERIFY_EXCEPTION_THROWN(Model1D(10, 2), zla_wartosc);
    QVERIFY_EXCEPTION_THROWN(Model1D(10, -2), zla_wartosc);
}

    /**
    *   Funkcja testujaca dzialanie konstruktora Model1D(vector <int> v):
    *   - czy przy podaniu wektora z elementem różnym od 0 i 1 zostanie wyrzucony wyjatek
    *   - czy metoda getSize zwroci rozmiar równy rozmiarowi podanego wektora
    */
void TestModel::testConstructor2()
{
    vector <int> v1, v2;
    v1.push_back(2);
    v2.push_back(0);

    QVERIFY_EXCEPTION_THROWN(Model1D m1(v1), zla_wartosc);
    Model1D m2(v2);
    QCOMPARE(m2.getSize(), (int)v2.size());
}

    /**
    *   Funkcja testujaca dzialanie metody run(int n):
    *   - czy przy podaniu nieodpowiedniej wartosci n zostanie wyrzucony wyjatek
    */
void TestModel::testRun()
{
    Model1D m(10);
    QVERIFY_EXCEPTION_THROWN(m.run(-1), zla_wartosc);
}

    /**
    *   Funkcja testujaca dzialanie metody getSum():
    *   - czy metoda zwróci odpowiednia wartosc sumy elementow wektora
    */
void TestModel::testGetSum()
{
    vector <int> v;

    for(int i = 0; i<10; i++)
        v.push_back(1);

    Model1D m(v);
    QCOMPARE(m.getSum(), 10);

}

    /**
    *   Funkcja testujaca dzialanie metody getConcentration():
    *   - czy metoda zwróci odpowiednia wartosc koncentracji elementow wektora
    */
void TestModel::testGetConcentration()
{
    vector <int> v;

    for(int i = 0; i<10; i++)
        v.push_back(1);

    Model1D m(v);
    QCOMPARE(m.getConcentration(), 1.0);
}


QTEST_APPLESS_MAIN(TestModel)

#include "test_model.moc"
