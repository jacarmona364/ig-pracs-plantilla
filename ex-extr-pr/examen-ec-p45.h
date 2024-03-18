// Nombre: José Antonio, Apellidos: Carmona Molina, Titulación: GIADE.
// email: jacarmona@correo.ugr.es, DNI o pasaporte: 77552812D

#ifndef EXAMEN_EC_P45_HPP
#define EXAMEN_EC_P45_HPP

#include "objeto3d.h"
#include "malla-ind.h" 
#include "malla-revol.h"
#include "materiales-luces.h"
#include <vector>
#include <grafo-escena.h>

class MallaP4 : public MallaInd
{
   public:
      MallaP4();
};

class NodoP4 : public NodoGrafoEscena
{
   public:
      NodoP4();
};

class NodoUrbaP5 : public NodoGrafoEscena {
private:
    NodoGrafoEscena * casa = new NodoGrafoEscena();
    int identificador = 1;
    glm::mat4 * nuevaTransformacion = nullptr;
    float rotacionEjey = 30.0;
    unsigned int ind_casa = 0;
    int NUM_PARAM = 1;
public:
    NodoUrbaP5(unsigned int ident);
    void movimiento();
    unsigned leerNumParametros() const;
    void actualizarEstadoParametro( const unsigned iParam, const float t_sec );
    virtual bool cuandoClick(const glm::vec3 &centro_wc);
};

class ObjetoMultiple : public NodoGrafoEscena
{
   public:
      ObjetoMultiple(int num_casas);
};











#endif