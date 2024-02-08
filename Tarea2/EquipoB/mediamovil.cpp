#include "Filtro.hpp"
#include <deque>
#include <cstddef>
#include <iostream>

Mediamovil::Mediamovil(int tamanno){
            nvalor = tamanno;
            contador = 0;
            suma = 0;
        }

void Mediamovil::estadistico(std::ifstream* ptr){
            double number = 0; 
            while (leer(ptr, number)) {
                dq.push_back(number);
                contador++;
                if (contador < nvalor){
                    suma += number;
                }
                else if(contador==nvalor){
                    suma += number;
                    std::cout << "La media mvoil es: " << (suma/nvalor) << std::endl;
                } else {
                    suma = suma - dq.front() + number;
                    dq.pop_front();
                    std::cout << "La media mvoil es: " << (suma/nvalor) << std::endl;
                }
            }                 
}

