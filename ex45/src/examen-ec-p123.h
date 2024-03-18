// Nombre: Antonio, Apellidos: Rodríguez Rodríguez, Titulación: GIADE.
// email: antoniorr@correo.ugr.es DNI o pasaporte: 78108407Q.

// NOMBRE: Antonio APELLIDOS: Rodríguez Rodríguez TITULACIÓN: Ingeniería Informática + ADE
// DNI: 78108407Q

#ifndef EXAMEN_EC_P123_HPP
#define EXAMEN_EC_P123_HPP

#include "objeto3d.h"
#include "malla-ind.h" // para poder usar clase MallaInd
#include "malla-revol.h"
#include "materiales-luces.h"
#include <vector>
#include <grafo-escena.h>


class P1MallaCubo : public MallaInd
{
   public:
      P1MallaCubo();
};

class P2Rejilla : public MallaInd
{
   public:
      P2Rejilla(const unsigned n, const unsigned m);
};

class P3Cuadrado : public MallaInd
{
   public:
      P3Cuadrado();
};

class P3Caja : public NodoGrafoEscena
{
   protected:
      const unsigned NUM_PARAM = 2;
      glm::mat4 * levantar_tapa_derecha = nullptr,
                * levantar_tapa_izq = nullptr,
                * levantar_bola = nullptr;
      float alpha_tapas = 1,
            altura_max_bola = 1;

   public:
      P3Caja( const float h_maxima_bola, const float alpha_rotacion );
      void levantar_tapas( const float alpha_rotacion ) ;
      void movimiento_bola( const float h_maxima_nola, const float t_sec ) ;
      virtual unsigned leerNumParametros() const ;
      virtual void actualizarEstadoParametro( const unsigned iParam, const float t_sec );
};

#endif