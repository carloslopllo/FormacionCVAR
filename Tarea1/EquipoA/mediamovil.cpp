#include "Filtro.hpp"
#include <deque>

Mediamovil::Mediamovil(int tamanno){
            nvalor = tamanno;
            contador = 0;
            suma = 0;
        }

bool Mediamovil::mean(float number, float &media){
            dq.push_back(number);
            contador++;
            if (contador < nvalor){
                suma += number;
                return false;
            }
            else if(contador==nvalor){
                suma = suma + number;
            } else {
                suma = suma - dq.front() + number;
                dq.pop_front();
            }
            media = suma/nvalor;
            return true;                        
}