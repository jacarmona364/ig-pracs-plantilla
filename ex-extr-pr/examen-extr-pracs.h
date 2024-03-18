// Nombre: José Antonio, Apellidos: Carmona Molina, Titulación: GIADE.
// email: jacarmona@correo.ugr.es, DNI o pasaporte: 77552812D

#ifndef EXAMEN_EXTR_PRACS_HPP
#define EXAMEN_EXTR_PRACS_HPP
#include "malla-ind.h"
#include "malla-revol.h"
#include "grafo-escena.h"
#include <vector>

class P1Malla : public MallaInd
{
   public:
      P1Malla();
};

class P2Fuente : public MallaRevol
{
   public:
      P2Fuente(const unsigned int n);
};

class P2Anillo : public MallaRevol
{
   public:
      P2Anillo(const int n, const unsigned m, float w);
};

class P3Rotonda : public NodoGrafoEscena
{
    protected:
      glm::mat4 * gira_coche = nullptr;
      const float velocidad = 1.0;
      float angulo = 90.0f;
   public:
      P3Rotonda();
      void girarCoche(const float t_sec );
      virtual void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
      virtual unsigned leerNumParametros() const;
};

class P4Rotonda : public NodoGrafoEscena
{
    public:
      P4Rotonda();
};

class P5Rotonda : public NodoGrafoEscena
{
    public:
      P5Rotonda();
      virtual bool  cuandoClick(const glm::vec3 &centro_wc);

};





#endif