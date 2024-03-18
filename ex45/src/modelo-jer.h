// Nombre: Antonio, Apellidos: Rodríguez Rodríguez, Titulación: GIADE.
// email: antoniorr@correo.ugr.es DNI o pasaporte: 78108407Q.

#ifndef MODELO_JER_HPP
#define MODELO_JER_HPP

//#include <tup_mat.h>   

#include "objeto3d.h"
#include "malla-ind.h" // para poder usar clase MallaInd
#include "malla-revol.h"
#include "grafo-escena.h"
#include "latapeones.h"
#include "materiales-luces.h"
#include <vector>

//using namespace tup_mat ;

class Cohete : public NodoGrafoEscena
{
   protected:
      glm::mat4 * giro_motor_principal = nullptr,
                * giro_motor_aux_drch = nullptr,
                * giro_motor_aux_izq = nullptr,
                * mover_cohete = nullptr,
                * mover_mot_aux_drch = nullptr,
                * mover_mot_aux_izq = nullptr,
                * mover_reactor_principal = nullptr,
                * mover_reactores_aux_drch = nullptr,
                * mover_reactores_aux_izq = nullptr,
                * giro_lanzadera = nullptr;
      float velocidad_giro_motores = 5,
            velocidad_levantamiento_lanzadera = 1,
            velocidad_subida = 0.75,
            h_inicial = 4.0,
            alpha_inicial = 30.0,
            alpha_lanzadera = 90.0;
   public:
      Cohete( const float h_maxima, const float alpha_rotacion, const float alpha_lanzadera_nuevo );
      void levantar_lanzadera( const float alpha_lanzadera_nuevo ) ;
      void movimiento_cohete( const float h_maxima, const float t_sec ) ;
      void fijar_giro_motor_principal( const float alpha_rotacion );
      void fijar_giro_motores_auxiliares( const float alpha_rotacion );
      virtual unsigned leerNumParametros() const ;
      virtual void actualizarEstadoParametro( const unsigned iParam, const float t_sec );
     // virtual bool cuandoClick(const glm::vec3 &centro_wc);
};

#endif