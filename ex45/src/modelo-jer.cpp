// Nombre: Antonio, Apellidos: Rodríguez Rodríguez, Titulación: GIADE.
// email: antoniorr@correo.ugr.es DNI o pasaporte: 78108407Q.

#include "ig-aux.h"  
#include "modelo-jer.h"
#include "aplicacion-ig.h"
#include "seleccion.h"   // para 'ColorDesdeIdent' 


Cohete::Cohete( const float h_maxima, const float alpha_rotacion, const float alpha_lanzadera_nuevo) 
:  NodoGrafoEscena() {

   using namespace glm;
    NodoGrafoEscena * cohete = new NodoGrafoEscena();
    NodoGrafoEscena * mot_aux_drch = new NodoGrafoEscena();
    NodoGrafoEscena * mot_aux_izq = new NodoGrafoEscena();
    NodoGrafoEscena * reactor_principal = new NodoGrafoEscena();
    NodoGrafoEscena * reactores_aux_drch = new NodoGrafoEscena();
    NodoGrafoEscena * reactores_aux_izq = new NodoGrafoEscena();
    NodoGrafoEscena * lanzadera_fija = new NodoGrafoEscena();
    NodoGrafoEscena * lanzadera_movil = new NodoGrafoEscena();

   Material * chapa = new Material(new Textura("textura-examen.jpg"), 0.2f, 0.2f, 0.8f, 50.0f);
   chapa->ponerNombre("chapa_cohete");
   Material * fuegos = new Material(new TexturaXY("Lava.jpg"), 0.8f, 0.8f, 0.2f, 10.0f);
   fuegos->ponerNombre("fuego_reactores");
   Material * rejilla = new Material(new Textura("rejilla.jpg"), 0.2f, 0.2f, 0.8f, 50.0f);
   rejilla->ponerNombre("rejilla_lanzadera");

   // Cuerpo principal
   unsigned ind_mover_cohete = cohete->agregar(scale(vec3(1.0,1.0,1.0)));
   cohete->ponerNombre("Cohete");
   cohete->ponerIdentificador(12341234);
   cohete->agregar ( translate( vec3(0.0f,3.0f,0.0f)) );
   cohete->agregar ( scale(vec3(0.5, 2, 0.5)) );
   cohete->agregar ( rotate(radians(180.0f), vec3(1.0f,0.0f,0.0f)) );
   cohete->agregar(chapa);
   cohete->agregar ( new Cilindro(12,24) );
   cohete->agregar ( new Esfera(20,20) );

   // Motor auxiliar derecho
   unsigned ind_mover_mot_aux_drch = mot_aux_drch->agregar(scale(vec3(1.0,1.0,1.0)));
   mot_aux_drch->ponerNombre("Motor derecho");
   mot_aux_drch->ponerIdentificador(1234123);
   mot_aux_drch->agregar ( translate( vec3(0.0f,3.0f,0.0f)) );
   mot_aux_drch->agregar ( scale(vec3(0.5, 2, 0.5)) );
   mot_aux_drch->agregar ( rotate(radians(180.0f), vec3(1.0f,0.0f,0.0f)) );
   mot_aux_drch->agregar ( scale(vec3(1, 0.5, 1)) );
   mot_aux_drch->agregar ( rotate(radians(180.0f), vec3(1.0f,0.0f,0.0f)) );
   mot_aux_drch->agregar ( rotate(radians(180.0f), vec3(0.0f,0.0f,1.0f)) );
   mot_aux_drch->agregar ( translate( vec3(0.0f,1.75f,0.0f)) );
   mot_aux_drch->agregar ( scale(vec3(1, 1.25, 1)) );
   mot_aux_drch->agregar ( translate( vec3(0.0f,-0.5f,1.5f)) );
   mot_aux_drch->agregar(chapa);
   mot_aux_drch->agregar ( new Cilindro(12,24));
   mot_aux_drch->agregar ( new Esfera(20,20) );

   // Motor auxiliar izquierdo
   unsigned ind_mover_mot_aux_izq = mot_aux_izq->agregar(scale(vec3(1.0,1.0,1.0)));
   mot_aux_izq->ponerNombre("Motor izquierdo");
   mot_aux_izq->ponerIdentificador(12341231);
   mot_aux_izq->agregar ( translate( vec3(0.0f,3.0f,0.0f)) );
   mot_aux_izq->agregar ( scale(vec3(0.5, 2, 0.5)) );
   mot_aux_izq->agregar ( rotate(radians(180.0f), vec3(1.0f,0.0f,0.0f)) );
   mot_aux_izq->agregar ( scale(vec3(1, 0.5, 1)) );
   mot_aux_izq->agregar ( rotate(radians(180.0f), vec3(1.0f,0.0f,0.0f)) );
   mot_aux_izq->agregar ( rotate(radians(180.0f), vec3(0.0f,0.0f,1.0f)) );
   mot_aux_izq->agregar ( translate( vec3(0.0f,1.75f,0.0f)) );
   mot_aux_izq->agregar ( scale(vec3(1, 1.25, 1)) );
   mot_aux_izq->agregar ( translate( vec3(0.0f,-0.5f,1.5f)) );
   mot_aux_izq->agregar ( translate( vec3(0.0f,0.0f,-3.0f)) );
   mot_aux_izq->agregar(chapa);
   mot_aux_izq->agregar ( new Cilindro(12,24));
   mot_aux_izq->agregar ( new Esfera(20,20) );
   
   // Reactores
   // Reactor motor principal
   reactor_principal->agregar(fuegos);
   unsigned ind_mover_reactor_principal = reactor_principal->agregar(scale(vec3(1.0,1.0,1.0)));
   unsigned ind_giro_reactor_principal = reactor_principal->agregar(scale(vec3(1.0,1.0,1.0)));
   reactor_principal->ponerNombre("Reactor principal");
   reactor_principal->ponerIdentificador(44441);
   reactor_principal->agregar ( translate( vec3(0.0f,3.0f,0.0f)) );
   reactor_principal->agregar ( scale(vec3(0.5, 2, 0.5)) );
   reactor_principal->agregar ( rotate(radians(180.0f), vec3(1.0f,0.0f,0.0f)) );
   reactor_principal->agregar ( scale(vec3(1, 0.5, 1)) );
   reactor_principal->agregar ( rotate(radians(180.0f), vec3(1.0f,0.0f,0.0f)) );
   reactor_principal->agregar ( rotate(radians(180.0f), vec3(0.0f,0.0f,1.0f)) );
   reactor_principal->agregar ( translate( vec3(0.0f,1.75f,0.0f)) );
   reactor_principal->agregar ( new Cono(12,24) );

   // Reactor motor auxiliar derecho
   reactores_aux_drch->agregar(fuegos);
   unsigned ind_mover_reactores_aux_drch = reactores_aux_drch->agregar(scale(vec3(1.0,1.0,1.0)));
   reactores_aux_drch->ponerNombre("Reactor derecho");
   reactores_aux_drch->ponerIdentificador(44442);
   reactores_aux_drch->agregar ( translate( vec3(0.0f,3.0f,0.0f)) );
   reactores_aux_drch->agregar ( scale(vec3(0.5, 2, 0.5)) );
   reactores_aux_drch->agregar ( rotate(radians(180.0f), vec3(1.0f,0.0f,0.0f)) );
   reactores_aux_drch->agregar ( scale(vec3(1, 0.5, 1)) );
   reactores_aux_drch->agregar ( rotate(radians(180.0f), vec3(1.0f,0.0f,0.0f)) );
   reactores_aux_drch->agregar ( rotate(radians(180.0f), vec3(0.0f,0.0f,1.0f)) );
   reactores_aux_drch->agregar ( translate( vec3(0.0f,1.75f,0.0f)) );
   reactores_aux_drch->agregar ( scale(vec3(1, 1.25, 1)) );
   reactores_aux_drch->agregar ( translate( vec3(0.0f,-0.5f,1.5f)) );
   reactores_aux_drch->agregar ( translate( vec3(0.0f,0.0f,-3.0f)) );
   reactores_aux_drch->agregar ( translate( vec3(0.0f,0.5f,3.0f)) );
   unsigned ind_giro_reactores_aux_drch = reactores_aux_drch->agregar(scale(vec3(1.0,1.0,1.0)));
   reactores_aux_drch->agregar ( new Cono(12,24) );

   // Reactor motor auxiliar izquierdo
   reactores_aux_izq->agregar(fuegos);
   unsigned ind_mover_reactores_aux_izq = reactores_aux_izq->agregar(scale(vec3(1.0,1.0,1.0)));
   reactores_aux_izq->ponerNombre("Reactor izquierdo");
   reactores_aux_izq->ponerIdentificador(44443);
   reactores_aux_izq->agregar ( translate( vec3(0.0f,3.0f,0.0f)) );
   reactores_aux_izq->agregar ( scale(vec3(0.5, 2, 0.5)) );
   reactores_aux_izq->agregar ( rotate(radians(180.0f), vec3(1.0f,0.0f,0.0f)) );
   reactores_aux_izq->agregar ( scale(vec3(1, 0.5, 1)) );
   reactores_aux_izq->agregar ( rotate(radians(180.0f), vec3(1.0f,0.0f,0.0f)) );
   reactores_aux_izq->agregar ( rotate(radians(180.0f), vec3(0.0f,0.0f,1.0f)) );
   reactores_aux_izq->agregar ( translate( vec3(0.0f,1.75f,0.0f)) );
   reactores_aux_izq->agregar ( scale(vec3(1, 1.25, 1)) );
   reactores_aux_izq->agregar ( translate( vec3(0.0f,-0.5f,1.5f)) );
   reactores_aux_izq->agregar ( translate( vec3(0.0f,0.0f,-3.0f)) );
   reactores_aux_izq->agregar ( translate( vec3(0.0f,0.5f,3.0f)) );
   reactores_aux_izq->agregar ( translate( vec3(0.0f,0.0f,-3.0f)) );
   unsigned ind_giro_reactores_aux_izq = reactores_aux_izq->agregar(scale(vec3(1.0,1.0,1.0)));
   reactores_aux_izq->agregar ( new Cono(12,24) );

   // Lanzadera_fija
   lanzadera_fija->ponerNombre("Lanzadera");
   lanzadera_fija->ponerIdentificador(3333);
   lanzadera_fija->agregar ( translate( vec3(0.0f,3.0f,0.0f)) );
   lanzadera_fija->agregar ( scale(vec3(0.5,0.75,0.5)) );
   lanzadera_fija->agregar ( translate( vec3(2.0f,-0.5f, 0.0f)) );
   lanzadera_fija->agregar ( scale(vec3(0.25,3.5,0.25)) );
   lanzadera_fija->agregar(rejilla);
   lanzadera_fija->agregar ( new Cubo24( ) );
   lanzadera_fija->agregar ( inverse(scale(vec3(0.25,3.5,0.25))) );
   lanzadera_fija->agregar ( translate( vec3(0.0f,4.0f, 0.0f)) );
   lanzadera_fija->agregar ( scale(vec3(0.75,0.75,0.75)) );
   lanzadera_fija->agregar(rejilla);
   lanzadera_fija->agregar ( new Esfera(20,20) );

   // Lanzadera movil
   lanzadera_movil->ponerNombre("Lanzadera");
   lanzadera_movil->ponerIdentificador(3333);
   lanzadera_movil->agregar ( translate( vec3(0.0f,3.0f,0.0f)) );
   lanzadera_movil->agregar ( scale(vec3(0.5,0.25,0.25)) );
   lanzadera_movil->agregar ( translate( vec3(2.0f,10.0f, 0.0f)) );
   lanzadera_movil->agregar ( rotate(radians(90.0f), vec3(1.0f,0.0f,0.0f)) );
   lanzadera_movil->agregar ( rotate(radians(90.0f), vec3(0.0f,0.0f,1.0f)) );
   unsigned ind_levantar_lanzadera = lanzadera_movil->agregar(scale(vec3(1.0,1.0,1.0)));
   //lanzadera_movil->agregar(rejilla);
   lanzadera_movil->ponerColor(vec3(0.0f,0.0f,0.0f));
   lanzadera_movil->agregar ( new MallaTorre(5) );

   // Dibujar cohete completo
   agregar(cohete);
   agregar(mot_aux_drch);
   agregar(mot_aux_izq);
   agregar(reactor_principal);
   agregar(reactores_aux_drch);
   agregar(reactores_aux_izq);
   agregar(lanzadera_fija);
   agregar(lanzadera_movil);

   // Inicializar parámetros de movimiento de las animaciones
   h_inicial = h_maxima;
   alpha_inicial = alpha_rotacion;
   alpha_lanzadera = alpha_lanzadera_nuevo;

   // Giro de los reactores
   giro_motor_principal = reactor_principal->leerPtrMatriz(ind_giro_reactor_principal);
   giro_motor_aux_drch = reactores_aux_drch->leerPtrMatriz(ind_giro_reactores_aux_drch);
   giro_motor_aux_izq = reactores_aux_izq->leerPtrMatriz(ind_giro_reactores_aux_izq);
   // Movimiento de la lanzadera
   giro_lanzadera = lanzadera_movil->leerPtrMatriz(ind_levantar_lanzadera);
   // Despegue y aterrizaje
   mover_cohete = cohete->leerPtrMatriz(ind_mover_cohete);
   mover_mot_aux_drch = mot_aux_drch->leerPtrMatriz(ind_mover_mot_aux_drch);
   mover_mot_aux_izq = mot_aux_izq->leerPtrMatriz(ind_mover_mot_aux_izq);
   mover_reactor_principal = reactor_principal->leerPtrMatriz(ind_mover_reactor_principal);
   mover_reactores_aux_drch = reactores_aux_drch->leerPtrMatriz(ind_mover_reactores_aux_drch);
   mover_reactores_aux_izq = reactores_aux_izq->leerPtrMatriz(ind_mover_reactores_aux_izq);
}
unsigned Cohete::leerNumParametros() const {
   return 3;
}

void Cohete::actualizarEstadoParametro( const unsigned iParam, const float t_sec ) {
   switch (iParam)
   {
   case 0:
      fijar_giro_motor_principal(velocidad_giro_motores*alpha_inicial*t_sec);
      fijar_giro_motores_auxiliares(velocidad_giro_motores*alpha_inicial*t_sec);
      break;
   case 1:
      levantar_lanzadera(alpha_lanzadera);
      break;
   case 2:
      movimiento_cohete(h_inicial, t_sec);
      break;
   default:
      break;
   }
}

void Cohete::fijar_giro_motor_principal( const float alpha_nuevo )
{
   *giro_motor_principal = glm::rotate( alpha_nuevo, glm::vec3( 0.0, 1.0, 0.0 ));
}

void Cohete::fijar_giro_motores_auxiliares( const float alpha_nuevo )
{
   *giro_motor_aux_drch = glm::rotate( alpha_nuevo, glm::vec3( 0.0, 1.0, 0.0 ));
   *giro_motor_aux_izq = glm::rotate( alpha_nuevo, glm::vec3( 0.0, 1.0, 0.0 ));
}

void Cohete::levantar_lanzadera( const float alpha_lanzadera_nuevo )
{
   *giro_lanzadera = glm::rotate( float(glm::radians(alpha_lanzadera_nuevo)), glm::vec3( 1.0, 0.0, 0.0 ));
}

void Cohete::movimiento_cohete( const float h_inicial, const float t_sec )
{
   // Quitamos la lanzadera para evitar colisiones
   levantar_lanzadera(alpha_lanzadera);
   // Calcula una posición vertical (en el eje Y) en función del tiempo
   float verticalPosition = h_inicial + h_inicial * sin(2 * M_PI * velocidad_subida * t_sec);
   *mover_cohete = glm::translate( glm::vec3( 0.0, verticalPosition, 0.0 ) );
   *mover_mot_aux_drch = glm::translate( glm::vec3( 0.0, verticalPosition, 0.0 ) );
   *mover_mot_aux_izq = glm::translate( glm::vec3( 0.0, verticalPosition, 0.0 ) );
   *mover_reactor_principal = glm::translate( glm::vec3( 0.0, verticalPosition, 0.0 ) );
   *mover_reactores_aux_drch = glm::translate( glm::vec3( 0.0, verticalPosition, 0.0 ) );
   *mover_reactores_aux_izq = glm::translate( glm::vec3( 0.0, verticalPosition, 0.0 ) );
}

// bool cuandoClick(const glm::vec3 &centro_wc) {
   
// }