#ifndef __FILTRO_HPP__
#define __FILTRO_HPP__

#include <deque>
#include <fstream>

class Filtro
{
public:
    virtual void estadistico(std::ifstream* ptr) = 0;

    bool leer(std::ifstream* ptr, double &leido) {
        if(*ptr >> leido) return true;
        return false;
    }
};

class Mediamovil : public Filtro{
    private:
        int nvalor, contador;
        double suma;
        std::deque<double> dq;
    public:
        Mediamovil(int tamanno);
        void estadistico(std::ifstream* ptr) override;
};

class Maximo : public Filtro{
    private:
        double max;
        bool vacio;
    public:
        Maximo();
        void estadistico(std::ifstream* ptr) override;
};

#endif