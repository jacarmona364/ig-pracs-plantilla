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
      }
   }
   // 4. Restaurar la copia guardada de la matriz de modelado (con 'popMM')
   cauce->popMM();
   // 5. Si el objeto tiene color asignado:
   //     - restaurar el color original a la entrada (con 'popColor')
   if (tieneColor())
      cauce->popColor();

   // COMPLETAR: práctica 4: añadir gestión de los materiales cuando la iluminación está activada    
   //
   // Si 'apl->iluminacion' es 'true', se deben de gestionar los materiales:
   //
   //   1. al inicio, hacer 'push' de la pila de materiales (guarda material actual en la pila)
   //   2. si una entrada es de tipo material, activarlo usando a pila de materiales
   //   3. al finalizar, hacer 'pop' de la pila de materiales (restaura el material activo al inicio)

   // ......


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

   // 1. Guardar copia de la matriz de modelado (con 'pushMM'), 
   cauce->pushMM();

   // 2. Para cada entrada del vector de entradas:
   //         - Si la entrada es de tipo objeto: llamar recursivamente a 'visualizareGomGL'.
   //         - Si la entrada es de tipo transformación: componer la matriz (con 'compMM').
   for (int i = 0; i < vectorEntradas.size(); i++)
   {
      switch (vectorEntradas[i].tipo) {
         case TipoEntNGE::objeto:               // si es entrada objeto:
            vectorEntradas[i].objeto->visualizarGL(); // visualizar objeto
            break;
         case TipoEntNGE::transformacion:         // si entrada transf.:
            cauce->compMM(*(vectorEntradas[i].matriz)); // componer matriz
            break;
      }
   }

   //   3. Restaurar la copia guardada de la matriz de modelado (con 'popMM')
   cauce->popMM();
   

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


}

// -----------------------------------------------------------------------------
// Añadir una entrada (al final).
// genérica (de cualqiuer tipo de entrada)

unsigned NodoGrafoEscena::agregar( const EntradaNGE & entrada )
{
   // COMPLETAR: práctica 3: agregar la entrada al nodo, devolver índice de la entrada agregada

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

   // 1. calcula el centro del objeto, (solo la primera vez)
   // ........


   // 2. si el identificador del nodo es el que se busca, ya está (terminar)
   // ........


   // 3. El nodo no es el buscado: buscar recursivamente en los hijos
   //    (si alguna llamada para un sub-árbol lo encuentra, terminar y devolver 'true')
   // ........


   // ni este nodo ni ningún hijo es el buscado: terminar
   return false ;
}

Portatil::Portatil( const float h_inicial, const float alpha_inicial ) 
:  NodoGrafoEscena() {

   ponerNombre( std::string("Portátil"));

   using namespace glm;
    NodoGrafoEscena * raton = new NodoGrafoEscena();
    NodoGrafoEscena * bisagras = new NodoGrafoEscena();
    NodoGrafoEscena * pen = new NodoGrafoEscena();
    NodoGrafoEscena * base = new NodoGrafoEscena();
    NodoGrafoEscena * alfombrilla = new NodoGrafoEscena();
    NodoGrafoEscena * pantalla = new NodoGrafoEscena();

   // Raton
   raton->agregar ( translate( vec3(3.3f,0.1f,-0.2f)) );
   raton->agregar ( scale(vec3(0.1, 0.1, 0.3)) );
   raton->agregar ( rotate(radians(90.0f), vec3(1.0f,0.0f,0.0f)) );
   raton->agregar ( new Cilindro(12,24) );

   raton->agregar ( scale(vec3(1, 0.6, 1)) );
   raton->agregar ( new Esfera(20,20) );

   raton->agregar ( translate( vec3(0.0f,1.6f,0.0f)) );
   raton->agregar ( scale(vec3(1, 0.6, 1)) );
   raton->agregar ( new Esfera(20,20) );

   raton->agregar ( translate( vec3(0.0f,-2.0f,-1.0f)) );
   raton->agregar ( scale(vec3(0.2, 0.6, 0.2)) );
   raton->agregar ( new Esfera(20,20) );

   // Bisagras
   bisagras->agregar ( translate( vec3(0.0f,0.0f,0.0f)) );
   bisagras->agregar ( scale(vec3(0.1, 0.1, 0.1)) );
   bisagras->agregar ( rotate(radians(90.0f), vec3(0.0f,0.0f,1.0f)) );
   bisagras->agregar ( translate( vec3(0.0f,0.0f,-15.0f)) );
   bisagras->agregar ( scale(vec3(0.45, 3, 0.45)) );
   bisagras->agregar ( translate( vec3(0.0f,-6.5f,4.5f)) );
   bisagras->agregar ( new Cilindro(12,24));

   bisagras->agregar ( translate( vec3(0.0f,12.0f,0.0f)) );
   bisagras->agregar ( new Cilindro(12,24));

   bisagras->agregar ( translate( vec3(0.0f,1.0f,0.0f)) );
   bisagras->agregar ( scale(vec3(1, 0.2, 1)) );
   bisagras->agregar ( new Esfera(20,20) );

   bisagras->agregar ( translate( vec3(0.0f,-5.0f,0.0f)) );
   bisagras->agregar ( new Esfera(20,20) );

   bisagras->agregar ( translate( vec3(0.0f,-55.0f,0.0f)) );
   bisagras->agregar ( new Esfera(20,20) );

   bisagras->agregar ( translate( vec3(0.0f,-5.0f,0.0f)) );
   bisagras->agregar ( new Esfera(20,20) );



   // Pen
   pen->agregar ( translate( vec3(-2.1f,0.0f,-1.0f)) );
   pen->agregar ( scale(vec3(0.2, 0.01, 0.05)) );

   pen->agregar ( new Cubo() );
   
   pen->agregar ( scale(vec3(1.4, 1.8, 1.4)) );
   pen->agregar ( translate( vec3(-0.7f,0.0f,0.0f)) );

   pen->agregar ( new CuboColores() );


   // Base Portátil
   base->agregar ( translate( vec3(0.0f, 0.0f, 0.0f)) );
   base->agregar ( scale(vec3(2.0, 0.04, 1.25)) );
   base->agregar ( new CuboColores() );


   // Alfombrilla
   alfombrilla->agregar ( scale(vec3(2,0,1.25)) );
   alfombrilla->agregar ( translate( vec3(1.15f,-4.0f, -0.5f)) );
   alfombrilla->agregar ( new RejillaY(10,10) );

   // Pantalla
   pantalla->agregar ( rotate(radians(270.0f), vec3(1.0f,0.0f,0.0f)) );
   pantalla->agregar ( translate( vec3(0.0f, 1.30f, 1.30f)) );
   pantalla->agregar ( scale(vec3(2.0, 0.04, 1.25)) );
   pantalla->agregar ( new CuboColores() );



   // Dibujar portátil completo
   agregar(raton);
   agregar(bisagras);
   agregar(pen);
   agregar(base);
   agregar(alfombrilla);
   agregar(pantalla);
   
}

void Portatil::fijarAlpha( const float alpha_nuevo )
{
   *pm_rot_alpha = glm::rotate( alpha_nuevo, glm::vec3( 0.0, 0.0, 1.0 ));
}

void Portatil::fijarH( const float h_nuevo )
{
   *pm_escy_h = glm::scale( glm::vec3( 1.0, h_nuevo/1.5, 1.0 ));
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






