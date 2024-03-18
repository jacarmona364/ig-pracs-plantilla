// Nombre: José Antonio, Apellidos: Carmona Molina, Titulación: GIADE.
// email: jacarmona@correo.ugr.es, DNI o pasaporte: 77552812D

#ifndef LATAPEONES_HPP
#define LATAPEONES_HPP

#include "objeto3d.h"
#include "malla-ind.h" 
#include "malla-revol.h"
#include "materiales-luces.h"
#include <vector>
#include <grafo-escena.h>

class LataPeones : public NodoGrafoEscena
{
   public:
      LataPeones( );
};

class MallaDiscoP4 : public MallaInd
{
   public:
      MallaDiscoP4(int mode);
};

class NodoDiscoP4 : public NodoGrafoEscena
{
   public:
      NodoDiscoP4( );
};

class Cubo24 : public MallaInd
{
   public:
      Cubo24();
};

class NodoCubo24 : public NodoGrafoEscena
{
   public:
      NodoCubo24( );
};

class CuadradoPruebaTexturas : public MallaInd
{
   public:
      CuadradoPruebaTexturas();
};

class NodoPruebaTextura : public NodoGrafoEscena
{
   public:
      NodoPruebaTextura( );
};

class VariasLatasPeones : public NodoGrafoEscena
{
   public:
      VariasLatasPeones(int desplazamientoZ);
};

class MiEsfera : public MallaRevol
{
public:
   // Constructor: crea el perfil original y llama a inicializar
   // La MiEsfera tiene el centro en el origen, el radio es la unidad
   MiEsfera(int i, int j);
   virtual bool  cuandoClick(const glm::vec3 &centro_wc);
};

class GrafoEsferasP5 : public NodoGrafoEscena
{
   public:
      GrafoEsferasP5();
};

class MiEsfera2 : public MallaRevol
{
public:
   // Constructor: crea el perfil original y llama a inicializar
   // La MiEsfera2 tiene el centro en el origen, el radio es la unidad
   MiEsfera2(int i, int j);
   virtual bool  cuandoClick(const glm::vec3 &centro_wc);
};


class GrafoEsferasP5_2 : public NodoGrafoEscena
{
   public:
      GrafoEsferasP5_2();
};

class Problema3_DADO : public MallaInd
{
   public:
      Problema3_DADO( );
};

class NodoProblemaDado : public NodoGrafoEscena
{
   public:
      NodoProblemaDado( );
};

#endif