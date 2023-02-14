#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include "Imagen.h"
#include "VDinamico.h"

/**
 * @author Manuel Lara Torres mlt00024@red.ujaen.es
 */

/**
 * @brief recupera un numero de imagenes determinado por el usuario conociendo el email que figura en el atributo email de esta y el vector donde estan contenidas estas, y las asigna a un nuevo ContenedorImagenes
 * @param num numero de imagenes a recuperar
 * @param email cadena de caracteres que quieres buscar en la imagen
 * @param vectorOrigen vector donde estan almacenadas las imgs
 * @param anio año en el que se tomaron las imagenes a almacenar en el nuevo ContenedorImagenes
 */
void recuperaImgs(VDinamico<Imagen>& vec, string correo, VDinamico<Imagen>& vnuevo){
    for(int i=0; i<vec.tamlog(); ++i){
        if(vec[i].getEmail()==correo){
            vnuevo.insertar(vec[i]);
            vec.borrar(i);
        }
    }
}

int main() {
    try {
       VDinamico<Imagen> vectorImgs;

        std::ifstream is;
        std::stringstream columnas;
        std::string fila;
        int contador = 0;

        std::string id = "";
        std::string email = "";
        std::string nombre = "";
        int tam = 0;
        int dia = 0;
        int mes = 0;
        int anno = 0;
        std::string etiquetas = "";

        Imagen aux;
        Fecha fec_aux;

        is.open("../imagenes_v1.csv"); //carpeta de proyecto
        if (is.good()) {

            clock_t t_ini = clock();

            while (getline(is, fila)) {

                //¿Se ha leído una nueva fila?
                if (fila != "") {

                    columnas.str(fila);

                    //formato de fila: id;email;nombre;tam;fecha;etiquetas

                    getline(columnas, id, ';'); //leemos caracteres hasta encontrar y omitir ';'
                    getline(columnas, email, ';');
                    getline(columnas, nombre, ';');

                    columnas >> tam;   //las secuencia numéricas se leen y trasforman directamente
                    columnas.ignore(); //omitimos carácter ';' siguiente

                    columnas >> dia;
                    columnas.ignore();
                    columnas >> mes;
                    columnas.ignore();
                    columnas >> anno;
                    columnas.ignore();

                    getline(columnas, etiquetas, ';');

                    fila = "";
                    columnas.clear();

                    aux.setId(id);
                    aux.setEmail(email);
                    aux.setNombre(nombre);
                    fec_aux.asignarDia(dia, mes, anno);
                    aux.setFecha(fec_aux);
                    aux.setTam(tam);
                    aux.setEtiquetas(etiquetas);


                    vectorImgs.insertar(aux, contador);

                    ++contador;

                    /*std::cout << ++contador
                              << " Imagen: ( ID=" << id
                              << " Email=" << email << " Fichero=" << nombre << " Tam=" << tam
                              << " Fecha=" << dia << "/" << mes << "/" << anno
                              << " Etiquetas=" << etiquetas
                              << ")" << std::endl;*/
                }
            }

            is.close();

            std::cout << "Tiempo lectura: " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;
        } else {
            std::cout << "Error de apertura en archivo" << std::endl;
        }
        std::cout << "Bienvenido/a a nuestro gestor de imagenes en linea" << endl;
        int accion;
        Imagen img1, img2, img3, img4, img5; //Imagenes para el apartado de busqueda binaria
        VDinamico<Imagen> vnuevo; //Vector para el apartado 4
        do {
            std::cout
                    << "Si quiere ordenar nuestra base de datos de mayor a menor ID, y visualizar el ID de las 50 primeras, pulse 1."
                    << endl
                    << "De lo contrario si quiere ordenar nuestra base de datos de menor a mayor ID y visualizar el ID de las 50 primeras, pulse 2."
                    << endl
                    << "De lo contrario, si quiere buscar las imagenes con los ID especificados en el enunciado de la practica, una vez ordenado el vector, pulse 3."
                    << endl
                    << "Y si lo que desea es conocer que imagenes tiene el usuario magdalen_upton99@gmail.com subidas en nuestra plataforma, asi como alamcenarlas en un contenedor personal y borrarlas de nuestra plataforma, pulse 4."
                    << endl
                    << "Si desea salir de nuestro sistema pulse cualquier otra tecla." << endl;
            std::cout << "Opcion elegida por el usuario: ";
            std::cin >> accion;
            switch (accion) {
                case 1:

                    vectorImgs.ordenarRev();
                    for (int i = 0; i < 50; ++i) {
                        std::cout << "ID " << i + 1 << ": " << vectorImgs[i].getId() << endl;
                    }
                    system("pause");
                    break;
                case 2:
                    vectorImgs.ordenar();
                    for (int i = 0; i < 50; ++i) {
                        std::cout << "ID " << i + 1 << ": " << vectorImgs[i].getId() << endl;
                    }
                    system("pause");
                    break;
                case 3:
                    vectorImgs.ordenar();
                    img1.setId("346335905");
                    img2.setId("999930245");
                    img3.setId("165837");
                    img4.setId("486415569");
                    img5.setId("61385551");
                    std::cout << "la posicion del elemento es la " << vectorImgs.busquedaBin(img1) << endl;
                    std::cout << "la posicion del elemento es la " << vectorImgs.busquedaBin(img2) << endl;
                    std::cout << "la posicion del elemento es la " << vectorImgs.busquedaBin(img3) << endl;
                    std::cout << "la posicion del elemento es la " << vectorImgs.busquedaBin(img4) << endl;
                    std::cout << "la posicion del elemento es la " << vectorImgs.busquedaBin(img5) << endl;
                    system("pause");
                    break;
                case 4:
                    recuperaImgs(vectorImgs, "magdalen_upton99@gmail.com", vnuevo);
                    std::cout << "El tamaño logico de la base de datos original es: " << vectorImgs.tamlog() << endl;
                    std::cout << "El tamaño logico de la base de datos de magdalen_upton99@gmail.com: " << vnuevo.tamlog() << endl;
                    for (int i = 0; i < 10; ++i) {
                        std::cout << i + 1
                                  << " Imagen: (ID = " << vnuevo[i].getId()
                                  << ", Email = " << vnuevo[i].getEmail() << ", Fichero = "
                                  << vnuevo[i].getNombre()
                                  << ", Tam =" << vnuevo[i].getTam()
                                  << ", Fecha =" << vnuevo[i].getFecha().verDia() << "/"
                                  << vnuevo[i].getFecha().verMes()
                                  << "/" << vnuevo[i].getFecha().verAnio()
                                  << ", Etiquetas =" << vnuevo[i].getEtiquetas()
                                  << ")" << std::endl;
                    }
                    system("pause");
                    break;
                default:
                    std::cout << "¡Hasta luego!";
            }
        } while (accion == 1 || accion == 2 || accion == 3 || accion == 4);

    }catch(exception e){
        std::cerr<<e.what();
    }
    return 0;
}