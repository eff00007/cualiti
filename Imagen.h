//
// Created by admin on 20/09/2022.
//

#ifndef IMAGENES_IMAGEN_H
#define IMAGENES_IMAGEN_H
#include <string>
#include <iostream>
#include "Fecha.h"


class Imagen {
public:
    Imagen();

    Imagen(const string &id, const string &email, const string &nombre, int tam, const Fecha &fecha,
           const string &etiquetas);

    const string &getId() const;

    void setId(const string &id);

    const string &getEmail() const;

    void setEmail(const string &email);

    const string &getNombre() const;

    void setNombre(const string &nombre);

    int getTam() const;

    void setTam(int tam);

    const Fecha &getFecha() const;

    void setFecha(const Fecha &fecha);

    const string &getEtiquetas() const;

    void setEtiquetas(const string &etiquetas);

    bool operator<(const Imagen &rhs) const;

    bool operator>(const Imagen &rhs) const;

    bool operator==(const Imagen &rhs) const;

    bool operator!=(const Imagen &rhs) const;

    static bool mayorQue(Imagen& a, Imagen& b);

    virtual ~Imagen();

private:
    string id;
    string email;
    string nombre;
    int tam;
    Fecha fecha;
    string etiquetas;


};


#endif //IMAGENES_IMAGEN_H
