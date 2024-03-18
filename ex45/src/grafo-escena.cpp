// Nombre: Antonio, Apellidos: Rodríguez Rodríguez, Titulación: GIADE.
// email: antoniorr@correo.ugr.es DNI o pasaporte: 78108407Q.

// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Gestión de grafos de escena (implementación)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Implementación de: 
// **     + Clase 'NodoGrafoEscena' (derivada de 'Objeto3D')
// **     + Clase 'EntradaNGE' (una entrada de un nodo del grafo de escena)
// **     + Tipo enumerado 'TipoEntNGE' (tipo de entradas del nodo del grafo de escena)
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#include "ig-aux.h"  
#include "grafo-escena.h"
#include "aplicacion-ig.h"
#include "seleccion.h"   // para 'ColorDesdeIdent' 



// *********************************************************************
// Entrada del nodo del Grafo de Escena

// ---------------------------------------------------------------------
// Constructor para entrada de tipo sub-objeto

EntradaNGE::EntradaNGE( Objeto3D * pObjeto )
{
   assert( pObjeto != nullptr );
   tipo   = TipoEntNGE::objeto ;
   objeto = pObjeto ;
}
// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( const glm::mat4 & pMatriz )
{
   tipo    = TipoEntNGE::transformacion ;
   matriz  = new glm::mat4() ; // matriz en el heap, puntero propietario
   *matriz = pMatriz ;
}

// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( Material * pMaterial )
{
   assert( pMaterial != nullptr );
   tipo     = TipoEntNGE::material ;
   material = pMaterial ;
}

// -----------------------------------------------------------------------------
// Destructor de una entrada

EntradaNGE::~EntradaNGE()
{
   /**  no fnciona debido a que se hacen copias (duplicados) de punteros
   if ( tipo == TipoEntNGE::transformacion )
   {
      assert( matriz != NULL );
      delete matriz ;
      matriz = NULL ;
   }
   * **/
}

// *****************************************************************************
// Nodo del grafo de escena: contiene una lista de entradas
// *****************************************************************************

NodoGrafoEscena::NodoGrafoEscena()
{

}

// -----------------------------------------------------------------------------
// Visualiza usando OpenGL

void NodoGrafoEscena::visualizarGL(  )
{
   using namespace std ;
   assert( apl != nullptr );

    // comprobar que hay un cauce y una pila de materiales y recuperarlos.
   Cauce *          cauce           = apl->cauce ;           assert( cauce != nullptr );
   PilaMateriales * pila_materiales = apl->pila_materiales ; assert( pila_materiales != nullptr );

   // COMPLETAR: práctica 3: implementar la visualización del nodo
   //
   // Se deben de recorrer las entradas y llamar recursivamente de visualizarGL, pero 
   // teniendo en cuenta que, al igual que el método visualizarGL de las mallas indexadas,
   // si el nodo tiene un color, debemos de cambiar el color del cauce (y hacer push/pop). 
   // Además, hay que hacer push/pop de la pila de modelado. 
   // Así que debemos de dar estos pasos:
   //
   // 1. Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //     - hacer push del color actual del cauce (con 'pushColor') y después
   //     - fijar el color en el cauce (con 'fijarColor'), usando el color del objeto (se lee con 'leerColor()')
   if (tieneColor()) {
      cauce->pushColor();
      cauce->fijarColor(leerColor());
   }
   if (apl->iluminacion) {
      apl->pila_materiales->push();
   }
   // 2. Guardar copia de la matriz de modelado (con 'pushMM'), 
   cauce->pushMM();
   // 3. Para cada entrada del vector de entradas:
   for (int i = 0; i < vectorEntradas.size(); i++)
   {
      switch (vectorEntradas[i].tipo) {
         case TipoEntNGE::objeto:               // si es entrada objeto:
            vectorEntradas[i].objeto->visualizarGL(); // visualizar objeto
            break;
         case TipoEntNGE::transformacion:         // si entrada transf.:
            cauce->compMM(*(vectorEntradas[i].matriz)); // componer matriz
            break;
         case TipoEntNGE::material:
            if (apl->iluminacion) {
               apl->pila_materiales->activar(vectorEntradas[i].material);
            }
            break;
      }
   }
   // 4. Restaurar la copia guardada de la matriz de modelado (con 'popMM')
   cauce->popMM();
   // 5. Si el objeto tiene color asignado:
   //     - restaurar el color original a la entrada (con 'popColor')
   if (apl->iluminacion) {
      apl->pila_materiales->pop();
   }
   if (tieneColor())
      cauce->popColor();
   
   // COMPLETAR: práctica 4: añadir gestión de los materiales cuando la iluminación está activada    
   //
   // Si 'apl->iluminacion' es 'true', se deben de gestionar los materiales:
   //
   //   1. al inicio, hacer 'push' de la pila de materiales (guarda material actual en la pila)
   //   2. si una entrada es de tipo material, activarlo usando a pila de materiales
   //   3. al finalizar, hacer 'pop' de la pila de materiales (restaura el material activo al inicio)

   // ...... DIAPOSITIVA 211 TEMA 3 --> (he portado el siguiente codigo un poco más arriba para ahorrar recorrer las entradas dos veces)
   // if (apl->iluminacion == true) {
      
   //    apl->pila_materiales->push();
   //    for (int i = 0; i < vectorEntradas.size(); i++) {
   //       if (vectorEntradas[i].tipo == TipoEntNGE::material) {
   //          apl->pila_materiales->activar(vectorEntradas[i].material);
   //       }
   //    }
   //    apl->pila_materiales->pop();
   // }


}

// *****************************************************************************
// visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...

void NodoGrafoEscena::visualizarGeomGL(  )
{
   using namespace std ;
   // comprobar que hay un cauce 
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce; assert( cauce != nullptr );
  
   // COMPLETAR: práctica 3: implementar la visualización del nodo (ignorando colores)
   //
   // Este método hace un recorrido de las entradas del nodo, parecido a 'visualizarGL', pero más simple,
   // Se dan estos pasos:
   //
   // 1. Guardar copia de la matriz de modelado (con 'pushMM'), 
   cauce->pushMM();
   // 2. Para cada entrada del vector de entradas:
   //         - Si la entrada es de tipo objeto: llamar recursivamente a 'visualizareGomGL'.
   //         - Si la entrada es de tipo transformación: componer la matriz (con 'compMM').
   for (int i = 0; i < vectorEntradas.size(); i++)
   {
      switch (vectorEntradas[i].tipo) {
         case TipoEntNGE::objeto:               // si es entrada objeto:
            vectorEntradas[i].objeto->visualizarGeomGL(); // visualizar objeto
            break;
         case TipoEntNGE::transformacion:         // si entrada transf.:
            cauce->compMM(*(vectorEntradas[i].matriz)); // componer matriz
            break;
      }
   }
   //   3. Restaurar la copia guardada de la matriz de modelado (con 'popMM')
   cauce->popMM();

   // .......

}

// -----------------------------------------------------------------------------
// Visualizar las normales de los objetos del nodo

void NodoGrafoEscena::visualizarNormalesGL(  )
{
   using namespace std ;

   // comprobar que hay un cauce 
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce; assert( cauce != nullptr );
  

   // COMPLETAR: práctica 4: visualizar las normales del nodo del grafo de escena
   //
   // Este método hace un recorrido de las entradas del nodo, parecido a 'visualizarGL', teniendo 
   // en cuenta estos puntos:
   //
   // - usar push/pop de la matriz de modelado al inicio/fin (al igual que en visualizatGL)
   // - recorrer las entradas, llamando recursivamente a 'visualizarNormalesGL' en los nodos u objetos hijos
   // - ignorar el color o identificador del nodo (se supone que el color ya está prefijado antes de la llamada)
   // - ignorar las entradas de tipo material, y la gestión de materiales (se usa sin iluminación)
   cauce->pushMM();
   // 3. Para cada entrada del vector de entradas:
   for (int i = 0; i < vectorEntradas.size(); i++)
   {
      if (vectorEntradas[i].tipo == TipoEntNGE::objeto) {
         vectorEntradas[i].objeto->visualizarNormalesGL(); 
      }
      if (vectorEntradas[i].tipo == TipoEntNGE::transformacion) {
         cauce->compMM(*(vectorEntradas[i].matriz));
      }
   }
   // 4. Restaurar la copia guardada de la matriz de modelado (con 'popMM')
   cauce->popMM();

   // .......

}

// -----------------------------------------------------------------------------
// visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
// basados en los identificadores de los objetos
void NodoGrafoEscena::visualizarModoSeleccionGL()
{
   using namespace std ;
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce ; assert( cauce != nullptr );

   // COMPLETAR: práctica 5: visualizar este nodo en modo selección.
   //
   // Se debe escribir código para dar estos pasos:
   // 
   // 2. Leer identificador (con 'leerIdentificador'), si el identificador no es -1 
   //      + Guardar una copia del color actual del cauce (con 'pushColor')
   //      + Fijar el color del cauce de acuerdo al identificador, (usar 'ColorDesdeIdent'). 
   // 3. Guardar una copia de la matriz de modelado (con 'pushMM')
   // 4. Recorrer la lista de nodos y procesar las entradas transformación o subobjeto:
   //      + Para las entradas subobjeto, invocar recursivamente a 'visualizarModoSeleccionGL'
   //      + Para las entradas transformación, componer la matriz (con 'compMM')
   // 5. Restaurar la matriz de modelado original (con 'popMM')   
   // 6. Si el identificador no es -1, restaurar el color previo del cauce (con 'popColor')
   //
   // ........
   int ident = leerIdentificador();
   if (ident != -1) {
      cauce->pushColor();
      cauce->fijarColor(ColorDesdeIdent(ident));
   }
   cauce->pushMM();
   for (int i = 0; i < vectorEntradas.size(); i++)
   {
      if (vectorEntradas[i].tipo == TipoEntNGE::objeto) {
         vectorEntradas[i].objeto->visualizarModoSeleccionGL();
      }
      if (vectorEntradas[i].tipo == TipoEntNGE::transformacion) {
         cauce->compMM(*(vectorEntradas[i].matriz));
      }
   }
   cauce->popMM();
   if (ident != -1) {
      cauce->popColor();
   }


}

// -----------------------------------------------------------------------------
// Añadir una entrada (al final).
// genérica (de cualqiuer tipo de entrada)

unsigned NodoGrafoEscena::agregar( const EntradaNGE & entrada )
{
   // COMPLETAR: práctica 3: agregar la entrada al nodo, devolver índice de la entrada agregada
   // ........
   vectorEntradas.push_back(entrada);

   return (vectorEntradas.size()-1) ; 

}
// -----------------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// objeto (copia solo puntero)

unsigned NodoGrafoEscena::agregar( Objeto3D * pObjeto )
{
   return agregar( EntradaNGE( pObjeto ) );
}
// ---------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// matriz (copia objeto)

unsigned NodoGrafoEscena::agregar( const glm::mat4 & pMatriz )
{
   return agregar( EntradaNGE( pMatriz ) );
}
// ---------------------------------------------------------------------
// material (copia solo puntero)
unsigned NodoGrafoEscena::agregar( Material * pMaterial )
{
   return agregar( EntradaNGE( pMaterial ) );
}

// devuelve el puntero a la matriz en la i-ésima entrada
glm::mat4 * NodoGrafoEscena::leerPtrMatriz( unsigned indice )
{
   // COMPLETAR: práctica 3: leer un puntero a una matriz en una entrada de un nodo
   //
   // Devolver el puntero a la matriz en la entrada indicada por 'indice'. 
   // Debe de dar error y abortar si: 
   //   - el índice está fuera de rango 
   //   - la entrada no es de tipo transformación
   //   - el puntero a la matriz es nulo 
   //
   // Sustituir 'return nullptr' por lo que corresponda.
   //
   assert (indice < vectorEntradas.size());
   assert (vectorEntradas[indice].tipo == TipoEntNGE::transformacion);
   assert (vectorEntradas[indice].matriz != nullptr);

   return vectorEntradas[indice].matriz;
}
// -----------------------------------------------------------------------------
// si 'centro_calculado' es 'false', recalcula el centro usando los centros
// de los hijos (el punto medio de la caja englobante de los centros de hijos)

void NodoGrafoEscena::calcularCentroOC()
{
   using namespace std ;
   using namespace glm ;

   // COMPLETAR: práctica 5: calcular y guardar el centro del nodo
   //    en coordenadas de objeto (hay que hacerlo recursivamente)
   //   (si el centro ya ha sido calculado, no volver a hacerlo)
   // ........
   
   if(!centro_calculado) {
      int num_hijos = 0;
      glm::mat4 mmodelado = mat4(1.0);
      glm::vec4 centro_aux = {0,0,0,1};

      for(unsigned int i = 0; i < vectorEntradas.size(); i++) {
         if(vectorEntradas[i].tipo == TipoEntNGE::transformacion )
            mmodelado = mmodelado * (*vectorEntradas[i].matriz);
         if(vectorEntradas[i].tipo == TipoEntNGE::objeto ){
            vectorEntradas[i].objeto->calcularCentroOC();
            centro_aux = centro_aux + (mmodelado * vec4(vectorEntradas[i].objeto->leerCentroOC(),1.0f));        
            num_hijos++; // para calcular promedio
         }
      }

      ponerCentroOC(centro_aux/float(num_hijos)); // promedio de dichos centros.
      centro_calculado = true;
      cout << "He calculado el centro de "<<centro_aux.x << endl;
   }

}

// -----------------------------------------------------------------------------
// método para buscar un objeto con un identificador y devolver un puntero al mismo

bool NodoGrafoEscena::buscarObjeto
(
   const int          ident_busc, // identificador a buscar
   const glm::mat4 &  mmodelado,  // matriz de modelado
   Objeto3D       **  objeto,     // (salida) puntero al puntero al objeto
   glm::vec3 &        centro_wc   // (salida) centro del objeto en coordenadas del mundo
)
{
   using namespace std ;
   using namespace glm ;
   
   assert( 0 < ident_busc );

   // COMPLETAR: práctica 5: buscar un sub-objeto con un identificador
   // Se deben de dar estos pasos:
   glm::mat4 mmodelado_transf = mmodelado;

   // 1. calcula el centro del objeto, (solo la primera vez)
   // ........
   calcularCentroOC();

   // 2. si el identificador del nodo es el que se busca, ya está (terminar)
   // ........
   // 3. El nodo no es el buscado: buscar recursivamente en los hijos
   //    (si alguna llamada para un sub-árbol lo encuentra, terminar y devolver 'true')
   // ........
   if ( leerIdentificador() == ident_busc ) {
      centro_wc = mmodelado*vec4( leerCentroOC(), 1.0f ) ;
      if ( objeto != nullptr )
         *objeto = this ;
      return true ;
   } else {
      for (const EntradaNGE &entrada : vectorEntradas) {
         switch (entrada.tipo) {
         case TipoEntNGE::objeto:               // si es entrada objeto:
            if(entrada.objeto->buscarObjeto(ident_busc, mmodelado, objeto, centro_wc))
               return true;
            break;
         case TipoEntNGE::transformacion:         // si entrada transf.:
            glm::mat4 transf = *(entrada.matriz);
            mmodelado_transf = mmodelado_transf * transf; // componer matriz
            break;
      }
      }
   }

   // ni este nodo ni ningún hijo es el buscado: terminar
   return false ;
}


/////////////////////////////////////////////////

GrafoEstrellaX::GrafoEstrellaX( const float alpha, unsigned n ) 
:  NodoGrafoEscena() {

   velocidad_giro = alpha;
   
   using namespace glm;
   NodoGrafoEscena * estrella = new NodoGrafoEscena();
   unsigned ind_animacion = agregar(scale(vec3(1.0,1.0,1.0)));
   estrella->agregar( scale(vec3(2.6, 2.6, 2.6)) );
   estrella->agregar( rotate(radians(90.0f), vec3(0.0, 1.0, 0.0)) );
   estrella->agregar( translate(vec3(-0.5, -0.5, 0.0)) );
   estrella->agregar( new EstrellaZ(n) );
   agregar(estrella);

   NodoGrafoEscena * puntas = new NodoGrafoEscena();
   puntas->agregar( rotate(radians(90.0f), vec3(0.0,1.0,0.0)) );
   puntas->agregar( translate(vec3(1.3,0.0,0.0)) );
   puntas->agregar( scale(vec3(0.14, 0.15, 0.14)) );
   puntas->agregar( rotate(radians(-90.0f), vec3(0.0,0.0,1.0)) );
   puntas->agregar( new Cono(12,24) );
   for (unsigned i = 0; i < n; i++) {
      float angulo = 2.0 * M_PI * i / n;
      agregar(rotate(angulo, vec3(1.0,0.0,0.0)));
      agregar(puntas);
   }

   giro_estrella = leerPtrMatriz(ind_animacion);

}

unsigned GrafoEstrellaX::leerNumParametros() const {
   return 1;
}

void GrafoEstrellaX::actualizarEstadoParametro( const unsigned iParam, const float t_sec ) {
   switch (iParam)
   {
   case 0:
      girar_estrella(velocidad_giro*t_sec);
      break;
   default:
      break;
   }
}

void GrafoEstrellaX::girar_estrella(const float alpha) {
   *giro_estrella = glm::rotate( alpha, glm::vec3( 0.0, 1.0, 0.0 ));
}

/////////////////////////////////////////////////

GrafoCubos::GrafoCubos( const float velocidad, unsigned n, unsigned m ) 
:  NodoGrafoEscena() {

   velocidad_giro = velocidad;
   
   using namespace glm;
   NodoGrafoEscena * cubo_principal = new NodoGrafoEscena();
   NodoGrafoEscena * cubos_auxiliares_ejeX = new NodoGrafoEscena();
   NodoGrafoEscena * cubos_auxiliares_ejeZ = new NodoGrafoEscena();
   NodoGrafoEscena * cubos_auxiliares_ejeY = new NodoGrafoEscena();
   unsigned ind_animacion_ejeX = cubos_auxiliares_ejeX->agregar((scale(vec3(1.0,1.0,1.0))));
   unsigned ind_animacion_ejeZ = cubos_auxiliares_ejeZ->agregar((scale(vec3(1.0,1.0,1.0))));
   unsigned ind_animacion_ejeY = cubos_auxiliares_ejeY->agregar((scale(vec3(1.0,1.0,1.0))));
   cubo_principal->agregar( translate(vec3(-0.5, -0.5, -0.5)) );
   //cubos_auxiliares->agregar( scale)
   for(int t = 0; t < 2; t++) {
      for (int j = 0; j < 2; j++) {
         for (int i = 0; i < 2; ++i) {
            cubo_principal->agregar( new RejillaY(n, m) );
            cubo_principal->agregar( rotate(radians(90.0f), vec3(0.0, 0.0, 1.0)) );
         }
         cubo_principal->agregar( translate(vec3(-1.0, -1.0, 0.0)));
      }
      cubo_principal->agregar( rotate(radians(90.0f), vec3(0.0, 1.0, 0.0)) );
      cubo_principal->agregar( translate(vec3(-1.0, 0.0, 0.0)));
   }

   cubos_auxiliares_ejeX->agregar(translate(vec3(-0.75,0.0,0.0)));
   cubos_auxiliares_ejeX->agregar(scale(vec3(0.25,0.15,0.15)));
   cubos_auxiliares_ejeX->agregar(new Cubo());
   cubos_auxiliares_ejeX->agregar(translate(vec3(1.5*(4),0.0,0.0)));
   cubos_auxiliares_ejeX->agregar(new Cubo());
   agregar(cubos_auxiliares_ejeX);
   cubos_auxiliares_ejeY->agregar(rotate(radians(90.0f), vec3(0.0,0.0,1.0)));
   cubos_auxiliares_ejeY->agregar(cubos_auxiliares_ejeX);
   agregar(cubos_auxiliares_ejeY);
   cubos_auxiliares_ejeZ->agregar(rotate(radians(90.0f), vec3(1.0,0.0,0.0)));
   cubos_auxiliares_ejeZ->agregar(cubos_auxiliares_ejeY);
   agregar(cubos_auxiliares_ejeZ);


   agregar(cubo_principal);

   giro_cubos_ejeX = cubos_auxiliares_ejeX->leerPtrMatriz(ind_animacion_ejeX);
   giro_cubos_ejeY = cubos_auxiliares_ejeY->leerPtrMatriz(ind_animacion_ejeY);
   giro_cubos_ejeZ = cubos_auxiliares_ejeZ->leerPtrMatriz(ind_animacion_ejeZ);

}

unsigned GrafoCubos::leerNumParametros() const {
   return 1;
}

void GrafoCubos::actualizarEstadoParametro( const unsigned iParam, const float t_sec ) {
   switch (iParam)
   {
   case 0:
      girar_cubos(velocidad_giro*t_sec);
      break;
   default:
      break;
   }
}

void GrafoCubos::girar_cubos(const float velocidad) {
   *giro_cubos_ejeX = glm::rotate( velocidad, glm::vec3( 1.0, 0.0, 0.0 ));
   *giro_cubos_ejeY = glm::rotate( velocidad, glm::vec3( 0.0, 1.0, 0.0 ));
   *giro_cubos_ejeZ = glm::rotate( velocidad, glm::vec3( 0.0, 0.0, 1.0 ));
}

// GrafoCubos::GrafoCubos( const float velocidad, unsigned n, unsigned m ) 
//  :  NodoGrafoEscena() {

//    using namespace glm;

//    // Rejilla
//    NodoGrafoEscena * rejilla= new NodoGrafoEscena();
//    rejilla->agregar(translate(vec3((-0.5,-0.5,-0.5))));
//    rejilla->agregar(new RejillaY(10,10));                   // Esto da lugar al "suelo" del cubo grande

//    // Cubo
//    NodoGrafoEscena * cubo = new NodoGrafoEscena();
//    unsigned ind1 = cubo->agregar(rotate(0.0f,vec3(0,1,0)));  // Animación: Cada cubo pequeño rota entorno al eje que pasa por su centro y el origen
//    cubo->agregar(translate(vec3{0,-0.75,0}));               
//    cubo->agregar(scale(vec3(0.15,0.25,0.15)));
//    cubo->agregar(new Cubo());                        // eSTO DA LUGAR AL CUBO DEL SUELO

//    // Como ya tenemos el objeto compuesto que se va a repetir ,agregamos 4 caras de nuestro 
//    // objeto compuesto rotando cada objeto 90 grados sobre el eje X
//    for(int i = 0; i < 4; i++){
//       agregar(rotate(float(radians(90.0)),vec3{1,0,0}));
//       agregar(rejilla);
//       agregar(cubo);
//    }

//    // Agregamos las 2 caras restantes de nuestro objeto compuesto rotando cada objeto 90 grados sobre el eje Z
//    agregar(rotate(float(radians(90.0)),vec3{0,0,1}));
//    agregar(rejilla);
//    agregar(cubo);
//    agregar(rotate(float(radians(180.0)),vec3{1,0,0}));
//    agregar(rejilla);
//    agregar(cubo);

//    giro_cubos_ejeX = cubo->leerPtrMatriz(ind1);
   
// }

// unsigned GrafoCubos::leerNumParametros () const{
//    return 1;
// }

// void GrafoCubos::actualizarEstadoParametro(const unsigned iParam, float t_sec){
//    assert( iParam < leerNumParametros() );
//             switch (iParam)
//             {
//             case 0:
//                girar_cubos(t_sec*90.0);
//                break;
//             }
// }

// void GrafoCubos::girar_cubos(float velocidad){
//    *giro_cubos_ejeX = (glm::rotate(float(glm::radians(velocidad)),glm::vec3{0,1,0}));


// }

/////////////////////////////////////////////////

GrafoPiramides::GrafoPiramides( const float velocidad_principal, const float velocidad_secundaria) 
:  NodoGrafoEscena() {

   velocidad_giro_principal = velocidad_principal;
   velocidad_giro_secundaria = velocidad_secundaria;
   
   using namespace glm;
   NodoGrafoEscena * piramide_principal = new NodoGrafoEscena();
   NodoGrafoEscena * piramide_secundaria = new NodoGrafoEscena();

   unsigned ind_animacion_principal = piramide_principal->agregar((scale(vec3(1.0,1.0,1.0))));
   unsigned ind_animacion_secundaria = piramide_secundaria->agregar((scale(vec3(1.0,1.0,1.0))));

   piramide_principal->agregar( new Piramide(5,5) );
   piramide_principal->agregar( rotate(radians(45.0f), vec3(0.0,1.0,0.0)) );
   piramide_principal->agregar( translate(vec3(-0.35,0.0,-0.35)) );
   piramide_principal->agregar( scale(vec3(0.7, 0.7, 0.7)) );
   piramide_principal->agregar( new RejillaY(5,5) );
   piramide_secundaria->agregar( translate(vec3(0.0,1.5,0.0)) );
   piramide_secundaria->agregar( rotate(radians(180.0f), vec3(1.0,0.0,0.0)) );
   piramide_secundaria->agregar( scale(vec3(0.5, 0.5, 0.5)) );
   piramide_secundaria->agregar( piramide_principal );
   agregar(piramide_principal);
   agregar(piramide_secundaria);

   giro_piramide_principal = piramide_principal->leerPtrMatriz(ind_animacion_principal);
   giro_piramide_secundaria = piramide_secundaria->leerPtrMatriz(ind_animacion_secundaria);

}

unsigned GrafoPiramides::leerNumParametros() const {
   return NUM_PARAM;
}

void GrafoPiramides::actualizarEstadoParametro( const unsigned iParam, const float t_sec ) {
   switch (iParam)
   {
   case 0:
      girar_piramide_principal(velocidad_giro_principal*t_sec);
      break;
   case 1:
      girar_piramide_secundaria(velocidad_giro_secundaria*t_sec);
      break;
   default:
      break;
   }
}

void GrafoPiramides::girar_piramide_principal(const float velocidad_principal) {
   *giro_piramide_principal = glm::rotate( velocidad_principal, glm::vec3( 0.0, 1.0, 0.0 ));
}

void GrafoPiramides::girar_piramide_secundaria(const float velocidad_secundaria) {
   *giro_piramide_secundaria = glm::rotate( velocidad_secundaria, glm::vec3( 0.0, 1.0, 0.0 ));
}

//////////////////////////////////////////////////
// EJERCICIOS 2.24 + 2.25 TEORÍA
Android::Android(const float velocidad_cabeza, const float velocidad_brazoi, const float velocidad_brazod) {
   using namespace glm;
   NodoGrafoEscena *cabeza= new NodoGrafoEscena();
   unsigned int ind_rot_cabeza = cabeza->agregar(rotate(0.0f,vec3{0,1,0}));
   //cabeza->ponerColor({0.0,1.0,0.0});
   cabeza->agregar(rotate(165.0f,vec3{0,1,0}));
   cabeza->agregar(new Material(new Textura("ojo.jpg"), 0.35f, 1.5f, 1.5f, 10.0f));
   cabeza->agregar(translate(vec3{0,1.0,0}));
   cabeza->agregar(scale(vec3(0.48,0.48,0.48)));
   cabeza->agregar(new SemiEsfera(100,100));
   agregar(cabeza);
   pm_rot_cabeza = cabeza->leerPtrMatriz(ind_rot_cabeza);

   NodoGrafoEscena *cuerpo=new NodoGrafoEscena();
   cuerpo->agregar(scale(vec3{0.5,1.0,0.5}));
   cuerpo->ponerColor({0.0,1.0,0.0});
   cuerpo->agregar(new Cilindro(10,10));
   agregar(cuerpo);

   NodoGrafoEscena *brazo_izq=new NodoGrafoEscena();
   unsigned int ind_rot_brazoi = brazo_izq->agregar(rotate(0.0f,vec3{0,1,0}));
   brazo_izq->ponerColor({0.0,1.0,0.0});
   brazo_izq->agregar(translate(vec3{3.4,4.3,0}));
   extremidad(brazo_izq);
   agregar(brazo_izq);
   pm_rot_brazoi = brazo_izq->leerPtrMatriz(ind_rot_brazoi);


   NodoGrafoEscena *brazo_derch=new NodoGrafoEscena();
   unsigned int ind_rot_brazod = brazo_derch->agregar(rotate(0.0f,vec3{0,1,0}));
   brazo_derch->ponerColor({0.0,1.0,0.0});
   brazo_derch->agregar(scale(vec3{5,5,5}));
   brazo_derch->agregar(translate(vec3{-3.4,4.3,0}));
   extremidad(brazo_derch);
   this->agregar(brazo_derch);
   pm_rot_brazod = brazo_derch->leerPtrMatriz(ind_rot_brazod);

   NodoGrafoEscena *pie_izq=new NodoGrafoEscena();
   pie_izq->ponerColor({0.0,1.0,0.0});
   pie_izq->agregar(scale(vec3{25,25,25}));
   pie_izq->agregar(translate(vec3{-1,0,0}));
   extremidad(pie_izq);
   agregar(pie_izq);


   NodoGrafoEscena *pie_derch=new NodoGrafoEscena();
   pie_derch->ponerColor({0.0,1.0,0.0});
   pie_derch->agregar(scale(vec3{125,125,125}));
   pie_derch->agregar(translate(vec3{1,0,0}));
   extremidad(pie_derch);
   agregar(pie_derch);

   
}

void Android::fijarRotBrazos( const float alpha )
{
    float rot = -sin(2*M_PI*0.7*alpha)/10;
   *pm_rot_brazod = glm::rotate(rot, glm::vec3{1.0, 0.0, 0.0});
   *pm_rot_brazoi = glm::rotate(-rot, glm::vec3{1.0, 0.0, 0.0});
   
}

void Android::fijarRotCabeza( const float alpha )
{
   float rot = alpha * 360.0;
   *pm_rot_cabeza = glm::rotate(rot, glm::vec3{0.0, 1.0, 0.0});
}

unsigned Android::leerNumParametros() const
{
   return 2;
}

void Android::actualizarEstadoParametro( const unsigned iParam, const float t_sec )
{
   assert(iParam < leerNumParametros()); 

   switch(iParam)
   {
      case 0:
         fijarRotBrazos(t_sec);
         break;
      case 1: 
         fijarRotCabeza(t_sec);
         break;

   }
}

void Android::extremidad(NodoGrafoEscena* transicion){
   using namespace glm;
   NodoGrafoEscena *extremidad = new NodoGrafoEscena(); 
   extremidad->agregar(scale(vec3(0.45,0.45,0.45)));
   extremidad->agregar(new SemiEsfera(100,100));

   extremidad->agregar(inverse(scale(vec3(0.45,0.45,0.45))));
   extremidad->agregar(scale(vec3(0.45,2.72,0.45)));
   extremidad->agregar(translate(vec3(0,-1,0)));
   extremidad->agregar(new Cilindro(10,30));

   extremidad->agregar(inverse(scale(vec3{0.45,2.72,0.45})));
   extremidad->agregar(scale(vec3(0.45,0.45,0.45)));
   extremidad->agregar(rotate(160.22f,vec3{0,0,1}));
   extremidad->agregar(new SemiEsfera(100,100));


   agregar(scale(vec3(0.2,0.2,0.2)));
   transicion->agregar(extremidad);

}