//
// Created by borri on 05/10/2022.
//

#ifndef IMAGENES_VDINAMICO_H
#define IMAGENES_VDINAMICO_H
#include <cmath>
#include <climits>
#include <iostream>
#include <algorithm>

template <typename T>
class VDinamico {
private:
    unsigned int _tamfis;
    unsigned int _tamlog;
    T* v = nullptr;

    void disminuye();

    void aumenta();

public:
    VDinamico();

    explicit VDinamico(unsigned int tamlog);

    VDinamico(const VDinamico<T> &orig);

    VDinamico(const VDinamico<T> &orig, unsigned int posicionInicial, unsigned int numElementos);

    VDinamico<T>& operator=(const VDinamico<T> &vec);

    T& operator[](unsigned int pos);

    void insertar(const T& dato, unsigned int pos = UINT_MAX);

    T borrar(unsigned int pos = UINT_MAX);

    void ordenar();

    static bool mayorQue(T& a, T& b);

    void ordenarRev();

    int busquedaBin(T& dato);

    unsigned int tamlog();

    virtual ~VDinamico();

};
/**
 * @brief metodo privado que disminuye el tamaño fisico _tamfis de un VDinamico a la mitad una vez que el tamaño logico _tamlog sea igual a un tercio del _tamfis
 * @tparam T tipo de dato
 */
template<typename T>
void VDinamico<T>::disminuye(){
    _tamfis = _tamfis/2;
    T* vnuevo = new T[_tamfis];
    for(int i=0; i<_tamlog;++i){
        vnuevo[i] = v[i];
    }
    delete []v;
    v = vnuevo;
}
/**
 * @brief metodo privado que aumenta el tamaño fisico _tamfis de un VDinamico al doble una vez que el tamaño logico _tamlog sea igual a _tamfis
 * @tparam T tipo de dato
 */
template<typename T>
void VDinamico<T>::aumenta() {
    _tamfis = _tamfis * 2;
    T *vnuevo = new T[_tamfis];
    for (int i=0; i<_tamlog; ++i) {
        vnuevo[i] = v[i];
    }
    delete [] v;
    v = vnuevo;
}
/**
 * @brief constructor por defecto de VDinamico, inicializa todos sus atributos a los valores por defecto especificados
 * @tparam T tipo de dato
 */
template<typename T>
VDinamico<T>::VDinamico(){
    _tamfis = 1;
    _tamlog = 0;
    v = new T[_tamfis];
}
/**
 * @brief constructor parametrizado de VDinamico, al que se le pasará un tamaño logico _tamlog y construira un VDinamico de tamaño fisico _tamfis de la potencia de 2 inmediatamente superior al tamaño logico
 * @tparam T tipo de dato
 * @param tamlog tamaño logico, es decir, el numero de elementos que se quieren almacenar en el VDinamico
 */
template<typename T>
VDinamico<T>::VDinamico(unsigned int tamlog) :  _tamlog(tamlog){
    if(tamlog == 0)
        _tamfis = 1;
    unsigned int exp = 1; //Voy a empezar en 1 porque por defecto el Vdinamico mas pequeño que voy a crear tiene 2^0 posiciones, es decir, 1 posicion
    for(int i=0; i<=exp; ++i){
        if((int)pow((double)2,(double)exp) > tamlog)
            _tamfis = (int)pow((double)2,(double)exp);//Estos cambio de tipo son para que la funcion pow, que devuelve un double, trabaje con double y almacenemos un entero
        ++exp;
    }
}
/**
 * @brief constructor de copia de VDinamico
 * @tparam T tipo de dato
 * @param orig VDinamico del que se copian sus valores
 */
template<typename T>
VDinamico<T>::VDinamico(const VDinamico<T> &orig):_tamfis(orig._tamfis), _tamlog(orig._tamlog) {
    v = new T[_tamfis];
    for (int c = 0; c < _tamfis; c++) {
        v[c] = orig.v[c];
    }

}
/**
 * @brief constructor de copia parcial de VDinamico, copaiara los valores del VDinamico orig en un intervalo de posiciones determinado por los parametros
 * @tparam T tipo de dato
 * @param orig Vdinamico del que se quiere copiar
 * @param posicionInicial posicion del VDinamico desde la que se quiere copiar valores
 * @param numElementos numero de elementos del VDinamico que queremos copiar
 * @throw std::invalid_argument si se le pasa alguna posicionInicial o numElementos que supere el tamaño fisico _tamfis
 */
template<typename T>
VDinamico<T>::VDinamico(const VDinamico<T> &orig, unsigned int posicionInicial,
                           unsigned int numElementos) {
    if (posicionInicial>=_tamlog || numElementos>=_tamlog)
        throw std::invalid_argument("VDinamico<T>::VDinamico: Algun parametro es incorrecto, por favor, introduzca paramteros validos");
    unsigned int exp = 1;
    for(int i=0; i<=exp; ++i){
        if((int)pow((double)2,(double)exp) > numElementos) {
            _tamfis = (int) pow((double) 2, (double) exp);
            v = new T[_tamfis];
        }
        ++exp;
    }
    for (int c = (int)posicionInicial; c < posicionInicial+numElementos; c++) {
        v[c-posicionInicial] = orig.v[c];
    }

}
/**
 * @brief operador de asignacion de VDinamico
 * @tparam T tipo de dato
 * @param vec VDinamico en el que queremos asignar
 * @return puntero al VDinamico al que se le asignan los datos
 */
template<typename T>
VDinamico<T>& VDinamico<T>::operator=(const VDinamico<T> &vec) {
    if (&vec != this) {
        delete[] v;
        _tamfis = vec._tamfis;
        _tamlog = vec._tamlog;

        v = new T[_tamfis];
        for (int c = 0; c < _tamfis; c++) {
            v[c] = vec.v[c];
        }
    }
    return *this;
}
/**
 * @brief operador [] de VDinamico, permite trabajar con cualquier objeto de este tipo usando los corchetes para acceder a el elemento almacenado en la posicion pos
 * @tparam T tipo de dato
 * @param pos posicion de v* de la cual se quiere consultar su contendido
 * @return v[pos] el elemento alamcenado en la posicion pos que se pasa como parametro
 */
template<typename T>
T& VDinamico<T>::operator[](unsigned int pos) {
    return v[pos];
}
/**
 * @brief metodo para insertar datos en un objeto VDinamico
 * @tparam T tipo de dato
 * @param dato elemento a insertar en el VDinamico
 * @param pos posicion en la que se insertará el elemento dato
 * @throw std::invalid_argument si se introduce una posicion pos incorrecta
 */
template<typename T>
void VDinamico<T>::insertar(const T& dato, unsigned int pos){
    if(pos != UINT_MAX && pos > _tamlog)
        throw std::invalid_argument("VDinamico<T>::insertar: El parametro introducido es incorrecto, por favor, introduzca otro");
    if(_tamlog == _tamfis)
        aumenta();
    if(pos == 0)
        v[0]=dato;
    if(pos != UINT_MAX && pos != 0){
        for(int i=_tamlog-1; i>=pos; --i){
            v[i+1]=v[i];
        }
        v[pos]=dato;
    }else
        v[_tamlog]=dato;
    ++_tamlog;
}
/**
 * @brief metodo para borrar datos en un objeto VDinamico
 * @tparam T tipo de dato
 * @param pos posicion del elemento que se quiere borrar
 * @return el elemento borrado del VDinamico
 * @throw std::invalid_argument si se introduce una posicion pos incorrecta
 */
template<typename T>
T VDinamico<T>::borrar(unsigned int pos){
    if(pos != UINT_MAX && pos > _tamlog)
        throw std::invalid_argument("VDinamico<T>::borrar: Has introducido una posicion incorrecta ");
    if(_tamlog*3 < _tamfis)
        disminuye();
    T borrado = v[pos];
    if(pos != UINT_MAX){
        for(int i=(int)pos; i<_tamlog; ++i){
            v[i]=v[i+1];
        }
    }
    --_tamlog;
    return borrado;

}
/**
 * @brief ordena el VDinamico utilizando el metodo sort de la libreria algorithm
 * @tparam T tipo de dato
*/
template<typename T>
void VDinamico<T>::ordenar() {
    sort(v, v + _tamlog);
}
/**
 * @brief metodo que compara dos objetos genericos, necesaria para que ordenaRev funcione con sort
 * @param a primer objeto que se quiere comparar
 * @param b segundo objeto que se quiere comparar
 * @tparam T tipo de dato
 * @return valor booleano true si a es mayor que b y false en cualquier otro caso
 */
template<typename T>
bool VDinamico<T>::mayorQue(T& a, T& b){
    return(a > b);
}
/**
 * @brief ordena el VDinamico de mayor a menor usando el metodo sort de algorithm
 * @tparam T tipo de dato
 */
template<typename T>
void VDinamico<T>::ordenarRev() {
    sort(v, v + _tamlog, mayorQue);
}

/**
 * @brief busqueda de una Imaagen dentro de un VDinamico mediante el algoritmo de la busqueda binaria
 * @pre el ContenedorImagenes debe estar ordenado habiendose usdado el correspondiente metodo ordenar()
 * @return la posicion del elemento buscado en el ContenedorImagenes
 */
template<typename T>
int VDinamico<T>::busquedaBin(T& dato) {
    int primeraPos = 0;
    int ultimaPos = _tamlog-1;
    int corte;
    while (primeraPos <= ultimaPos) {
        corte = (primeraPos + ultimaPos) / 2;
        if (v[corte] == dato)
            return corte;
        else
        if (v[corte] < dato)
            primeraPos = corte + 1;
        else
            ultimaPos = corte - 1;
    }
    return -1;
}
/**
 * @brief metodo para consultar el tamaño logico _tamlog de un VDinamico
 * @tparam T tipo de dato
 * @return _tamlog tamaño logico del objeto VDinamico
 */
template<typename T>
unsigned int VDinamico<T>::tamlog(){
    return _tamlog;
}
/**
 * @brief destructor de VDianmico
 * @tparam T tipo de dato
 */
template<typename T>
VDinamico<T>::~VDinamico() {
    delete [] v;
    v = nullptr;
}

#endif //IMAGENES_VDINAMICO_H
