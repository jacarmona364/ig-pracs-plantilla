// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Mallas indexadas (implementación)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Implementación de las clases 
// **        + MallaInd: malla indexada de triángulos (derivada de Objeto3D)
// **        + MallaPLY: malla indexada de triángulos, leída de un PLY (derivada de MallaInd)
// **        + algunas clases derivadas de MallaInd.
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
#include "aplicacion-ig.h"
#include "malla-ind.h"   // declaración de 'ContextoVis'
#include "lector-ply.h"
#include "seleccion.h"   // para 'ColorDesdeIdent' 


// *****************************************************************************
// funciones auxiliares

// *****************************************************************************
// métodos de la clase MallaInd.

MallaInd::MallaInd()
{
   // nombre por defecto
   ponerNombre("malla indexada, anónima");
}
// -----------------------------------------------------------------------------

MallaInd::MallaInd( const std::string & nombreIni )
{
   // 'identificador' puesto a 0 por defecto, 'centro_oc' puesto a (0,0,0)
   ponerNombre(nombreIni) ;
}

//-----------------------------------------------------------------------------
// calcula la tabla de normales de triángulos una sola vez, si no estaba calculada

void MallaInd::calcularNormalesTriangulos()
{

   
   // si ya está creada la tabla de normales de triángulos, no es necesario volver a crearla
   const unsigned nt = triangulos.size() ;
   assert( 1 <= nt );
   if ( 0 < nor_tri.size() )
   {
      assert( nt == nor_tri.size() );
      return ;
   }

   // COMPLETAR: Práctica 4: creación de la tabla de normales de triángulos
   // ....

}


// -----------------------------------------------------------------------------
// calcula las dos tablas de normales

void MallaInd::calcularNormales()
{
   using namespace glm ;
   // COMPLETAR: en la práctica 4: calculo de las normales de la malla
   // se debe invocar en primer lugar 'calcularNormalesTriangulos'
   // .......


}


// --------------------------------------------------------------------------------------------

void MallaInd::visualizarGL( )
{
   // comprobar algunas precondiciones básicas
   using namespace std ;
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce ; assert( cauce != nullptr );
   CError();

   // si la malla no vértices o no tiene triángulos, imprimir advertencia y salir.
   if ( triangulos.size() == 0 || vertices.size() == 0 )
   {  cout << "advertencia: intentando dibujar malla vacía '" << leerNombre() << "'" << endl << flush ;
      return ;
   }

   // COMPLETAR: práctica 1: cambiar color del cauce
   //
   // Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //    - hacer push del color actual del cauce
   //    - fijar el color en el cauce usando el color del objeto (se lee con 'leerColor()')

      if(tieneColor()){
         cauce->pushColor();
         cauce->fijarColor(leerColor());
      }

   // COMPLETAR: práctica 1: crear el descriptor de VAO, si no está creado
   //  Si el puntero 'dvao' es nulo, crear el descriptor de VAO
   //   * en primer lugar se crea el descriptor de VAO, con su constructor 
   //     (se le pasa como parámetro la tabla de posiciones y el número de atributos del cauce). 
   //   * se añade el descriptor de VBO con la tabla de índices (la tabla de triángulos),
   //   * finalmente se añaden al VAO los descriptores VBOs con tablas de atributos 
   //     que no estén vacías
   //  Si el VAO ya está creado, (dvao no nulo), no hay que hacer nada.
   //

      if(dvao == nullptr){
         dvao = new DescrVAO(numero_atributos_cauce, new DescrVBOAtribs(ind_atrib_posiciones, vertices));
         if(triangulos.size() > 0){
            dvao->agregar(new DescrVBOInds(triangulos));
         }
         if(col_ver.size() > 0){
            dvao->agregar(new DescrVBOAtribs(ind_atrib_colores, col_ver));
         }
         if(nor_ver.size() > 0){
            dvao->agregar(new DescrVBOAtribs(ind_atrib_normales, nor_ver));
         }
         if(cc_tt_ver.size() > 0){
            dvao->agregar(new DescrVBOAtribs(ind_atrib_coord_text, cc_tt_ver));
         }
      }

   // COMPLETAR: práctica 1: visualizar el VAO usando el método 'draw' de 'DescrVAO'
      dvao->draw(GL_TRIANGLES);

   // COMPLETAR: práctica 1: restaurar color anterior del cauce 
   //
   // Si el objeto tiene un color asignado (se comprueba con 'tieneColor')
   //    - hacer 'pop' del color actual del cauce
      if(tieneColor()){
         cauce->popColor();
      }


}


// -----------------------------------------------------------------------------
// Visualizar el objeto con OpenGL
// usa las tablas de normales, colores y coordenadas de textura, si no están vacías.
      
void MallaInd::visualizarGeomGL( )
{
   // Comprobar que el descriptor de VAO ya está creado
   // (es decir, este método únicamente se podrá invocar después de que 
   // se haya llamado a 'visualizaGL')
   
   assert( dvao != nullptr );

   // COMPLETAR: práctica 1: visualizar únicamente la geometría del objeto 
   // 
   //    1. Desactivar todas las tablas de atributos del VAO (que no estén vacías)
            if(col_ver.size() > 0){
               dvao->habilitarAtrib(ind_atrib_colores, false);
            }
            if(nor_ver.size() > 0){
               dvao->habilitarAtrib(ind_atrib_normales, false);
            }
            if(cc_tt_ver.size() > 0){
               dvao->habilitarAtrib(ind_atrib_coord_text, false);
            }
            
            
   //    2. Dibujar la malla (únicamente visualizará los triángulos)
            dvao->draw(GL_TRIANGLES);
   //    3. Volver a activar todos los atributos para los cuales la tabla no esté vacía
            if(col_ver.size() > 0){
               dvao->habilitarAtrib(ind_atrib_colores, true);
            }
            if(nor_ver.size() > 0){
               dvao->habilitarAtrib(ind_atrib_normales, true);
            }
            if(cc_tt_ver.size() > 0){
               dvao->habilitarAtrib(ind_atrib_coord_text, true);
            }
   // ....

}

// -----------------------------------------------------------------------------
// Visualizar las normales del objeto, si no tiene tabla de normales imprime 
// advertencia y no hace nada.

void MallaInd::visualizarNormalesGL(  )
{
   using namespace std ;
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce ; assert( cauce != nullptr );

   if ( nor_ver.size() == 0 )
   {
      cout << "Advertencia: intentando dibujar normales de una malla que no tiene tabla (" << leerNombre() << ")." << endl ;
      return ;
   }  

   if( nor_ver.size() != vertices.size() )
   {
      cout << "Error visu. normales: tabla de normales no vacía y de tamaño distinto a la de vértices." << endl ;
      cout << "Nombre del objeto        : " << leerNombre() << endl ;
      cout << "Tamaño tabla vértices    : " << vertices.size() << endl ;
      cout << "Tamaño tabla de normales : " << nor_ver.size() << endl ;
      exit(1);
   }
   CError();

   // COMPLETAR: práctica 4: visualizar las normales del objeto MallaInd
   // 
   // *1* Si el puntero al descriptor de VAO de normales ('dvao_normales') es nulo, 
   //    debemos de crear dicho descriptor, con estos pasos:
   //
   //       * Para cada posición 'v_i' de un vértice en el vector 'vertices':
   //             - Leer la correspondiente normal 'n_i' del vector de normales ('nor_ver').
   //             - Añadir 'v_i' al vector 'segmentos_normales'.
   //             - Añadir 'v_i+a*n_i' al vector 'segmentos_normales'.
   //
   //       * Crear el objeto descriptor del VAO de normales, para ello se usa el vector 
   //          'segmentos_normales' y se tiene en cuenta que esa descriptor únicamente gestiona 
   //          una tabla de atributos de vértices (la de posiciones, ya que las otras no se 
   //          necesitan).
   // 
   // *2* Visualizar el VAO de normales, usando el método 'draw' del descriptor, con el 
   //       tipo de primitiva 'GL_LINES'.

   //  ..........

}

// -----------------------------------------------------------------------------
// visualizar el objeto en 'modo seleccion', es decir, sin iluminación y con los colores 
// basados en los identificadores de los objetos
void MallaInd::visualizarModoSeleccionGL() 
{

   using namespace std ;
   assert( apl != nullptr );
   Cauce * cauce = apl->cauce ; assert( cauce != nullptr );

   // COMPLETAR: práctica 5: visualizar la malla en modo selección 
   //
   // Se debe escribir código para visualizar únicamente la geometría, pero usando el color 
   // obtenido a partir del identificador. El código da estos pasos:
   // 
   // 1. Leer el identificador del objeto (con 'leerIdentificador'). Si el objeto tiene 
   //    identificador (es decir, si su identificador no es -1)
   //       + Hacer push del color del cauce, con 'pushColor'.
   //       + Fijar el color del cauce (con 'fijarColor') usando un color obtenido a 
   //         partir del identificador (con 'ColorDesdeIdent'). 
   // 2. Invocar 'visualizarGeomGL' para visualizar la geometría.
   // 3. Si tiene identificador: hacer pop del color, con 'popColor'.
   //

}


// ****************************************************************************
// Clase 'MallaPLY'

MallaPLY::MallaPLY( const std::string & nombre_arch )
{
   ponerNombre( std::string("malla leída del archivo '") + nombre_arch + "'" );

   // COMPLETAR: práctica 2: leer archivo PLY e inicializar la malla
   // ..........................
   LeerPLY(nombre_arch, vertices, triangulos);

   // COMPLETAR: práctica 4: invocar  a 'calcularNormales' para el cálculo de normales
   // .................

}

// ****************************************************************************
// Clase 'Cubo

Cubo::Cubo()
:  MallaInd( "cubo 8 vértices" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;

   //ponerColor({0,0,0});

   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

}

Tetraedro::Tetraedro()
:  MallaInd( "Tetraedro" )
{

   vertices =
      {  { 0, -1, -1 }, // 0
         {-1, -1, +1}, // 1
         {+1, -1, +1}, //2
         {0, 1, 0} //3
      } ;
   
   //ponerColor({1,1,1});

   triangulos =
      {  {0,1,2}, {0,1,3}, // X-
         {0,2,3}, {1,2,3}, // X+ (+4)

         //{0,5,1}, {0,4,5}, // Y-
         //{2,3,7}, {2,7,6}, // Y+ (+2)

         //{0,6,4}, {0,2,6}, // Z-
         //{1,5,7}, {1,7,3}  // Z+ (+1)
      } ;
   


}

CuboColores::CuboColores()
:  MallaInd( "cubo 8 vértices colores" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;

   // Calcular y asignar colores basados en las componentes de posición
   for (const auto& v : vertices) {
      float r = (v.x + 1.0) / 2.0;  // Componente R depende de X
      float g = (v.y + 1.0) / 2.0;  // Componente G depende de Y
      float b = (v.z + 1.0) / 2.0;  // Componente B depende de Z
      col_ver.push_back({r, g, b});
   }


   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

}

EstrellaZ::EstrellaZ(unsigned n)
:  MallaInd( "EstrellaZ" )
{

   float radio = 0.5;
   float centroX = 0.5;
   float centroY = 0.5;
   float centroZ = 0;

   //Vertice central
   vertices.push_back({centroX, centroY, centroZ});
   col_ver.push_back({1,1,1});

   //Vertices de las puntas
   for (unsigned i = 0; i < n; i++) {
      float angulo = 2.0 * M_PI * i/n;
      float x = centroX + radio * cos(angulo);  
      float y = centroY + radio * sin(angulo);
      float z = centroZ;
      vertices.push_back({x,y,z});  
      col_ver.push_back({x,y,z});
   }

   for (unsigned i = 0; i < n; ++i){
      float angulo = 2.0 * M_PI * i / n + M_PI / n;
      float x = centroX + radio/2.0 * cos(angulo);
      float y = centroY + radio/2.0 * sin(angulo);
      float z = centroZ;

      vertices.push_back({x, y, z});
      col_ver.push_back({x, y, z}); // Color basado en las coordenadas X, Y y Z
   }


   // Crear los triángulos
   for (unsigned i = 0; i < 2*n-1; ++i)
   {
      if(i < n){
         triangulos.push_back({0, i+1, n+1+i});
      }
      else{
         triangulos.push_back({0, i+1, (n+1+i)%(2*n-1)});
      }
   }
   triangulos.push_back({0,1,2*n});

}


CasaX::CasaX()
:  MallaInd( "CasaX" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
         { +1.0, +1.75, 0 }, //8
         { -1.0, +1.75, 0 }, //9
      } ;

   // Calcular y asignar colores basados en las componentes de posición
   for (const auto& v : vertices) {
      float r = (v.x + 1.0) / 2.0;  // Componente R depende de X
      float g = (v.y + 1.0) / 2.0;  // Componente G depende de Y
      float b = (v.z + 1.0) / 2.0;  // Componente B depende de Z
      col_ver.push_back({r, g, b});
   }


   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         //{2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3},  // Z+ (+1)

         {7,8,6}, {2,3,9},
         {7,8,9}, {3,7,9},
         {6,8,9}, {6,9,2}

      } ;

}

MallaTriangulo::MallaTriangulo()
:  MallaInd( "MallaTriangulo" )
{

   vertices =
      {  { 0, 0, -0.5 }, // 0
         { 0, 0, +0.5 }, // 1
         { 0, sqrt(2), 0 } // 2
      } ;

   // Calcular y asignar colores basados en las componentes de posición
   for (const auto& v : vertices) {
      float r = (v.x + 1.0) / 2.0;  // Componente R depende de X
      float g = (v.y + 1.0) / 2.0;  // Componente G depende de Y
      float b = (v.z + 1.0) / 2.0;  // Componente B depende de Z
      col_ver.push_back({r, g, b});
   }


   triangulos =
      {  {0,1,2}

      } ;

}

MallaCuadrado::MallaCuadrado()
:  MallaInd( "MallaCuadrado" )
{

   vertices =
      {  { 0, -1, -1 }, // 0
         { 0, -1, 1 }, // 1
         { 0, 1, -1 }, // 2
         { 0, 1, 1 } //3
      } ;

   // Calcular y asignar colores basados en las componentes de posición
   for (const auto& v : vertices) {
      float r = (v.x + 1.0) / 2.0;  // Componente R depende de X
      float g = (v.y + 1.0) / 2.0;  // Componente G depende de Y
      float b = (v.z + 1.0) / 2.0;  // Componente B depende de Z
      col_ver.push_back({r, g, b});
   }


   triangulos =
      {  { 0, 1, 2 },
         { 1, 2, 3 }
      } ;

}

MallaPiramideL::MallaPiramideL()
:  MallaInd( "MallaPiramideL" )
{

   vertices =
      {  { 0, 0, 1 }, // 0
         { -1, 0, 1 }, // 1
         { -1, 0, -1 }, // 2
         { 1, 0, -1 }, //3
         { 1, 0, 0 }, //4
         { 0, 0, 0 }, //5
         { 0, 2, 0 } //6
      } ;

   // Calcular y asignar colores basados en las componentes de posición
   for (const auto& v : vertices) {
      float r = (v.x + 1.0) / 2.0;  // Componente R depende de X
      float g = (v.y + 1.0) / 2.0;  // Componente G depende de Y
      float b = (v.z + 1.0) / 2.0;  // Componente B depende de Z
      col_ver.push_back({r, g, b});
   }


   triangulos =
      {  {0,1,5}, {2,1,5},
         {2,5,4}, {2,3,4},
         {3,4,6}, {6,2,3},
         {1,2,6}, {0,1,6},
         {0,5,6}, {4,5,6}

      } ;

}

PiramideEstrellaZ::PiramideEstrellaZ(unsigned n)
:  MallaInd( "PiramideEstrellaZ" )
{

   float radio = 0.5;
   float centroX = 0.5;
   float centroY = 0.5;
   float centroZ = 0;

   //Vertice central
   vertices.push_back({centroX, centroY, centroZ});
   col_ver.push_back({1,1,1});

   //Vertices de las puntas
   for (unsigned i = 0; i < n; i++) {
      float angulo = 2.0 * M_PI * i/n;
      float x = centroX + radio * cos(angulo);  
      float y = centroY + radio * sin(angulo);
      float z = centroZ;
      vertices.push_back({x,y,z});  
      col_ver.push_back({x,y,z});
   }

   //Vertices interiores
   for (unsigned i = 0; i < n; ++i){
      float angulo = 2.0 * M_PI * i / n + M_PI / n;
      float x = centroX + radio/2.0 * cos(angulo);
      float y = centroY + radio/2.0 * sin(angulo);
      float z = centroZ;

      vertices.push_back({x, y, z});
      col_ver.push_back({x, y, z}); // Color basado en las coordenadas X, Y y Z
   }

   vertices.push_back({0.5, 0.5, 0.5});//falta unir este vertice con los demás
   col_ver.push_back({1, 1, 1});

   // Crear los triángulos
   for (unsigned i = 0; i < 2*n-1; ++i)
   {
      if(i < n){
         triangulos.push_back({0, i+1, n+1+i});
      }
      else{
         triangulos.push_back({0, i+1, (n+1+i)%(2*n-1)});
      }
   }
   triangulos.push_back({0,1,2*n});

   for (unsigned i = 0; i < 2*n-1; ++i)
   {
      if(i < n){
         triangulos.push_back({2*n+1, i+1, n+1+i});
      }
      else{
         triangulos.push_back({2*n+1, i+1, (n+1+i)%(2*n-1)});
      }
   }
   triangulos.push_back({2*n+1,1,2*n});   
};

RejillaY::RejillaY(unsigned n, unsigned m)
:  MallaInd( "RejillaY" )
{

    assert (n > 1);
   assert (m > 1);
   
   // vértices de la rejilla
   for (unsigned i = 0; i < n; i++ ) {
      for (unsigned j = 0; j < m; j++ ) {
         float coordenadaX = i / float(n-1);
         float coordenadaZ = j / float(m-1);
         vertices.push_back({coordenadaX, 0.0, coordenadaZ});
      }
   }

   // Calcular y asignar colores basados en las componentes de posición
   for (const auto& v : vertices) {
      float r = v.x;  // Componente R depende de X
      float g = v.y;  // Componente G depende de Y
      float b = v.z;  // Componente B depende de Z
      col_ver.push_back({r, g, b});
   }

   // triangulos de la rejilla
   for (unsigned i = 0; i < m - 1; ++i)
   {
      for (unsigned j = 0; j < n - 1; ++j)
      {
         unsigned v0 = i * n + j;
         unsigned v1 = v0 + 1;
         unsigned v2 = (i + 1) * n + j;
         unsigned v3 = v2 + 1;
         //std::cout << "valor i: " << i << " valor j: " << j << " --> " << v0 << " " << v1 << " " << v2 << std::endl;


         // Primer triángulo de la celda.
         triangulos.push_back({v0, v1, v2});

         // Segundo triángulo de la celda.
         triangulos.push_back({v2, v1, v3});
      }
   }

}

MallaTorre::MallaTorre(unsigned n)
:  MallaInd( "MallaTorre" )
{

   // vértices de la torre
   float coordenadaX = 0.5;
   float coordenadaZ = 0.5;
   for (float i = 0; i < n+1; i++ ) {
      vertices.push_back({coordenadaX, i, coordenadaZ});
      vertices.push_back({-coordenadaX, i, coordenadaZ});
      vertices.push_back({-coordenadaX, i, -coordenadaZ});
      vertices.push_back({coordenadaX, i, -coordenadaZ});
   }

   // triángulos para la torre
   for (unsigned j = 0; j < n; j++) {
      for (unsigned i = 0; i < 4; i++) {
         triangulos.push_back({i+(j*4), ((i+1)%4)+(j*4), (i+4)+(j*4)});
         if ((i+1) % 4 == 0)
            triangulos.push_back({(i+4)+(j*4), (i+1)+(j*4), (j*4)});
         else
            triangulos.push_back({(i+4)+(j*4), (i+1)+(j*4), (i+5)+(j*4)});
      }
   }

}
// -----------------------------------------------------------------------------------------------

