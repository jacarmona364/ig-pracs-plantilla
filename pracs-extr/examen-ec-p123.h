// Nombre: José Antonio, Apellidos: Carmona Molina, Titulación: GIADE.
// email: jacarmona@correo.ugr.es, DNI o pasaporte: 77552812D

#ifndef EXAMEN_EC_P123_HPP
#define EXAMEN_EC_P123_HPP

#include "malla-ind.h"
#include "grafo-escena.h"




class P1MallaCubo : public MallaInd
{
   public:
      P1MallaCubo();
};

class P2Rejilla : public MallaInd
{
   public:
      P2Rejilla(unsigned n, unsigned m);
};

class P3Cuadrado : public MallaInd
{
   public:
      P3Cuadrado();
};

class P3Caja : public NodoGrafoEscena
{
   protected:
      glm::mat4 * abre_caja_dch = nullptr,
                * abre_caja_izq = nullptr,
                * sube_esfera = nullptr;
      const float velocidad = 1.2;
      float rango_esfera = 1.0f;
      float angulo = 30.0f;
   public:
      P3Caja( const float alpha, const float rango);
      void subirEsfera( const float rango, const float t_sec );
      void abrirCaja(const float alpha);
      virtual void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
      virtual unsigned leerNumParametros() const;
};















#endif