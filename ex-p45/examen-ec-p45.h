// Nombre: José Antonio, Apellidos: Carmona Molina, Titulación: GIADE.
// email: jacarmona@correo.ugr.es, DNI o pasaporte: 77552812D

#ifndef EXAMEN_EC_P45_HPP
#define EXAMEN_EC_P45_HPP

#include "malla-ind.h"
#include "grafo-escena.h"

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

class NodoUrbaP5 : public NodoGrafoEscena
{
   public:
      NodoUrbaP5(unsigned int n);
};













#endif