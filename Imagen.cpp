//
// Created by admin on 20/09/2022.
//

#include "Imagen.h"

/**
 * @brief constructor por defecto de Imagen
 */
Imagen::Imagen() {}
/**
 * @brief Constructor parametrizado de Imagen
 * @param id
 * @param email
 * @param nombre
 * @param tam
 * @param fecha
 * @param etiquetas
 */
Imagen::Imagen(const string &id, const string &email, const string &nombre, int tam, const Fecha &fecha,
               const string &etiquetas) : id(id), email(email), nombre(nombre), tam(tam), fecha(fecha),
                                          etiquetas(etiquetas) {}

const string &Imagen::getId() const {
    return id;
}

void Imagen::setId(const string &id) {
    Imagen::id = id;
}

const string &Imagen::getEmail() const {
    return email;
}

void Imagen::setEmail(const string &email) {
    Imagen::email = email;
}

const string &Imagen::getNombre() const {
    return nombre;
}

void Imagen::setNombre(const string &nombre) {
    Imagen::nombre = nombre;
}

int Imagen::getTam() const {
    return tam;
}

void Imagen::setTam(int tam) {
    Imagen::tam = tam;
}

const Fecha &Imagen::getFecha() const {
    return fecha;
}

void Imagen::setFecha(const Fecha &fecha) {
    Imagen::fecha = fecha;
}

const string &Imagen::getEtiquetas() const {
    return etiquetas;
}

void Imagen::setEtiquetas(const string &etiquetas) {
    Imagen::etiquetas = etiquetas;
}
/**
 * @brief operador menor que de Imagen
 * @param rhs "right hand side" objeto Imagen con el que se compara
 * @return true si se cumple la condicion, false en cualquier otro caso
 */
bool Imagen::operator<(const Imagen &rhs) const {
    if (stoi(id) < stoi(rhs.id))
        return true;
    return false;
}
/**
 * @brief operador mayor que de Imagen
 * @param rhs "right hand side" objeto Imagen con el que se compara
 * @return true si se cumple la condicion, false en cualquier otro caso
 */
bool Imagen::operator>(const Imagen &rhs) const {
    if (stoi(id) > stoi(rhs.id))
        return true;
    return false;
}
/**
 * @brief operador == de Imagen
 * @param rhs "right hand side" objeto Imagen con el que se compara
 * @return valor booleano true si los objetos de tipo Imagen tienen la misma informacion y false si lo anterior no se cumple
 */
bool Imagen::operator==(const Imagen &rhs) const {
    return stoi(id) == stoi(rhs.id);
}

/**
 * @brief metodo que compara dos objetos de tipo Imagen, a y b, y devuelve un valor booleano si la condicion especificada se cumple o no, necesario para el correcto funcionamiento de CntenedorImagenes::ordenaRev
 * @param a Imagen a comparar
 * @param b Imagen a comparar
 * @return stoi(a.getId()) > stoi(b.getId()) valor booleano segun si dicha condicion se cumple
 */
bool Imagen::mayorQue(Imagen& a, Imagen& b){
    return(stoi(a.getId()) > stoi(b.getId()));
}

Imagen::~Imagen() {

}
