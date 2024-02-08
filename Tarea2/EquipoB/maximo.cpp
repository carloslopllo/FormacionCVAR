#include "Filtro.hpp"
#include <deque>
#include <cstddef>
#include <iostream>

Maximo::Maximo(){
            max = 0;
            vacio = true;
        }

void Maximo::estadistico(std::ifstream* ptr){
            double number = 0; 
            while (leer(ptr, number)) {
                if (vacio) {
                    max = number;
                    vacio = false;
                }
                else if (max < number) {
                    max = number;
                }
            }  
            if (!vacio) {
                std::cout << "El maximo es: " << max << std::endl;
            }            
}

