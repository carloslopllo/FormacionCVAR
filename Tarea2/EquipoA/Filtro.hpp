#ifndef __FILTRO_HPP__
#define __FILTRO_HPP__

#include <deque>

using std::deque;
using std::size_t;

class Filtro {
	public:
		virtual double filter (double number) = 0;
};

class Mediamovil : public Filtro {
	private:
		int nvalor;
		double suma;
		deque<double> dq;
	public:
		Mediamovil(size_t size);
		double filter (double number);
};

class Minimo : public Filtro {
	private:
		bool first;
		double minCurrent;
	public:
		Minimo();
		double filter (double number);
};

#endif
