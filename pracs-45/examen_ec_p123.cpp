
// Nombre: José Antonio, Apellidos: Carmona Molina, Titulación: GIADE.
// email: jacarmona@correo.ugr.es, DNI o pasaporte: 77552812D

#include "examen-ec-p123.h"

P1MallaCubo::P1MallaCubo()
:  MallaInd( "P1MallaCubo" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0 ci
         { -1.0, -1.0, +1.0 }, // 1 ci
         { -1.0, +1.0, -1.0 }, // 2 cs
         { -1.0, +1.0, +1.0 }, // 3 cs
         { +1.0, -1.0, -1.0 }, // 4 ci
         { +1.0, -1.0, +1.0 }, // 5 ci
         { +1.0, +1.0, -1.0 }, // 6 cs
         { +1.0, +1.0, +1.0 }, // 7 cs
         { 0.0, +1.0, 0.0 }, // 8 centro cara superior
         { 0.0, -1.0, 0.0 } // 9 centro cara inferior
      } ;

   // Calcular y asignar colores basados en las componentes de posición
   for (const auto& v : vertices) {
      float r = (v.x + 1.0) / 2.0;  // Componente R depende de X
      float g = (v.y + 1.0) / 2.0;  // Componente G depende de Y
      float b = (v.z + 1.0) / 2.0;  // Componente B depende de Z
      col_ver.push_back({r, g, b});
   }

   col_ver.pop_back();
   col_ver.pop_back();
   col_ver.push_back({1,0,0});
   col_ver.push_back({0,1,1});



   triangulos =
      {  {0,1,3}, {0,3,2}, 
         {4,7,5}, {4,6,7}, 

         {8,6,7}, {8,7,3}, //cara superior
         {8,2,3}, {8,6,2},

         {9,4,5},{9,0,1}, //cara inferior
         {9,4,0},{9,5,1},           

         {0,6,4}, {0,2,6}, 
         {1,5,7}, {1,7,3}  
      } ;

}

P2Rejilla::P2Rejilla(unsigned n, unsigned m)
:  MallaInd( "P2Rejilla" )
{

   assert (n > 1);
   assert (m > 1);
   
   // Vértices
   for (unsigned i = 0; i < n; i++ ) {
      for (unsigned j = 0; j < m; j++ ) {
         float coordenadaX = i / float(n-1);
         float coordenadaZ = j / float(m-4);
         vertices.push_back({coordenadaX, 0.0, coordenadaZ});
      }
   }

   // Triangulos
   for (unsigned i = 0; i < m - 1; ++i)
   {
      for (unsigned j = 0; j < n - 1; ++j)
      {
         unsigned v0 = i * n + j;
         unsigned v1 = v0 + 1;
         unsigned v2 = (i + 1) * n + j;
         unsigned v3 = v2 + 1;

         // Primer triángulo de la celda.
         triangulos.push_back({v0, v1, v2});

         // Segundo triángulo de la celda.
         triangulos.push_back({v2, v1, v3});
      }
   }

}


P3Cuadrado::P3Cuadrado()
:  MallaInd( "P3Cuadrado" )
{

   vertices =
      {  { -1.0, 0.0, -1.0 }, // 0
         { -1.0, 0.0, +1.0 }, // 1
         { +1.0, 0.0, -1.0 }, // 2
         { +1.0, 0.0, +1.0 }, // 3
      } ;

   //ponerColor({0,0,0});

   triangulos =
      {  {3,2,0}, {0,1,3}

      } ;

}



P3Caja::P3Caja(const float alpha, const float rango) 
:  NodoGrafoEscena() {

   rango_esfera = rango;
   angulo = alpha;

   ponerNombre( std::string("P3Caja"));

   using namespace glm;

    NodoGrafoEscena * esfera = new NodoGrafoEscena();
    NodoGrafoEscena * base = new NodoGrafoEscena();
    NodoGrafoEscena * tapa_dch = new NodoGrafoEscena();
    NodoGrafoEscena * tapa_izq = new NodoGrafoEscena();


   // Esfera
   unsigned ind_ani_esf = esfera->agregar(scale(vec3(1.0,1.0,1.0)));

   esfera->agregar ( translate( vec3(0.0f, 0.5f, 0.0f)) );
   esfera->agregar ( scale(vec3(0.3, 0.3, 0.3)) );

   esfera->agregar ( new Esfera(50,50) );

   sube_esfera = esfera->leerPtrMatriz(ind_ani_esf);

   agregar(esfera);


   // Base Caja 
   base->agregar ( new P3Cuadrado() ); //base

   base->agregar ( translate( vec3(-1.0f, 0.5f, 0.0f)) );
   base->agregar ( rotate(radians(90.0f), vec3(0.0f,0.0f,1.0f)) );
   base->agregar ( scale(vec3(0.5, 1.0, 1.0)) );
   base->agregar ( new P3Cuadrado() ); //cara izq

   base->agregar ( translate( vec3(0.0f, -2.0f, 0.0f)) );
   base->agregar ( new P3Cuadrado() ); //cara dch

   base->agregar ( translate( vec3(0.0f, 1.0f, -1.0f)) );
   base->agregar ( rotate(radians(90.0f), vec3(1.0f,0.0f,0.0f)) );
   base->agregar ( new P3Cuadrado() ); //cara posterior

   base->agregar ( translate( vec3(0.0f, 2.0f, 0.0f)) );
   base->agregar ( new P3Cuadrado() ); //cara anterior

   agregar(base);


   // Tapa dch
   unsigned ind_ani_tap_dch = tapa_dch->agregar(scale(vec3(1.0,1.0,1.0)));

   tapa_dch->agregar ( translate( vec3(0.5f, 1.0f, 0.0f)) );
   tapa_dch->agregar ( scale(vec3(0.5, 1.0, 1.0)) );

   tapa_dch->agregar ( new P3Cuadrado() ); // tapa dch

   abre_caja_dch = tapa_dch->leerPtrMatriz(ind_ani_tap_dch);
   agregar(tapa_dch);

   // Tapa izq
   unsigned ind_ani_tap_izq = tapa_izq->agregar(scale(vec3(1.0,1.0,1.0)));
   tapa_izq->agregar ( scale(vec3(0.5, 1.0, 1.0)) );
   tapa_izq->agregar ( translate( vec3(-1.0f, 1.0f, 0.0f)) );
   tapa_izq->agregar ( new P3Cuadrado() ); // tapa izq

   abre_caja_izq = tapa_izq->leerPtrMatriz(ind_ani_tap_izq);
   agregar(tapa_izq);
   
}

unsigned P3Caja::leerNumParametros() const {
   return 2;
}

void P3Caja::actualizarEstadoParametro(const unsigned iParam, const float t_sec){
   switch (iParam)
   {
   case 0:
      subirEsfera(rango_esfera, t_sec);
      break;
   case 1:
      abrirCaja(angulo * t_sec);
      break;
   default:
      break;
   }
}


void P3Caja::subirEsfera( const float rango, const float t_sec )
{
   float movimiento = rango + rango * sin(2 * M_PI * velocidad * t_sec);
   *sube_esfera = glm::translate( glm::vec3( 0, movimiento, 0 ));
}

void P3Caja::abrirCaja( const float alpha )
{
   *abre_caja_dch = glm::rotate( glm::radians(-alpha), glm::vec3( 0.0, 0.0, 1.0 ));
    *abre_caja_izq = glm::rotate( glm::radians(alpha), glm::vec3( 0.0, 0.0, 1.0 ));

}