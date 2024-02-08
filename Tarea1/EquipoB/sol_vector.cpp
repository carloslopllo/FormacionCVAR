#include <vector>
#include <iostream>
#include <fstream>

// Alternativa en c++ usando std::vector
// Autores: Luis y Mario
// Uso: ./ejecutable path_fichero_datos tamaño_media

void media(std::vector<float> v){

    float suma=0;
    for(float elem : v) suma += elem;
    std::cout << (suma/v.size()) << std::endl;
}

std::vector<float> inicializar_vector(std::ifstream* fin, int size){

    std::vector<float> res(0);
    float actual;

    for(int i=0; i<size; i++){
        *fin >> actual;
        res.push_back(actual);
    }
    return res;
}

void calcular_media_movil(std::ifstream* fin, int size) {

    std::vector<float> vector = inicializar_vector(fin,size);

    media(vector);
    float nuevo_elem;

    while (*fin >> nuevo_elem) {
        vector.push_back(nuevo_elem);
        vector.erase(vector.begin());
        media(vector);
    }
}

int main(int argc, char* argv[]){

    if(argc!=3){
        std::cerr << "Error en argumentos. Uso: ./ejecutable path_fichero_datos tamaño_media" << std::endl;
        return 1;
    }

    std::ifstream fin(argv[1]);

    if(!fin.is_open()){
        std::cerr << "Error accediendo al archivo." << std::endl;
        return 1;
    }

    int size;
    try {
        size = std::stoi(argv[2]);
    } catch (const std::invalid_argument &e) {
        std::cerr << "Error con el formato del tamaño. Debe ser un entero." << std::endl;
        return 1;
    }

    calcular_media_movil(&fin,size);

    fin.close();
    return 0;
}