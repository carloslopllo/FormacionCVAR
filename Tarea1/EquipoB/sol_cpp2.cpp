#include <iostream>
#include <fstream>

// Esta es la alternativa en C con entrada y salida de C++
// Autores: Luis y Mario
// Uso: ./ejecutable path_fichero_datos tamaño_media

void media(float suma, int size){
    std::cout << (suma/size) << std::endl;
}

float inizializar_punteros(std::ifstream* head, int size){

    float suma = 0;
    float actual;

    for(int i=0; i<size; i++){
        *head >> actual;
        suma += actual;
    }

    return suma;
}

void calcular_media_movil(std::ifstream* head, std::ifstream* tail, int size) {

    float suma = inizializar_punteros(head,size);

    float nuevo, viejo;

    media(suma,size);
    while (*head >> nuevo) {
        *tail >> viejo;
        suma += nuevo;
        suma -= viejo;
        media(suma,size);
    }
}

int main(int argc, char* argv[]){

    if(argc!=3){
        std::cerr << "Error en argumentos. Uso: ./ejecutable path_fichero_datos tamaño_media" << std::endl;
        return 1;
    }

    std::ifstream head(argv[1]);
    std::ifstream tail(argv[1]);

    if(!head.is_open() || !tail.is_open()){
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

    calcular_media_movil(&head,&tail,size);

    head.close();
    tail.close();
    return 0;
}