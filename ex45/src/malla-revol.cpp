// Nombre: Antonio, Apellidos: Rodríguez Rodríguez, Titulación: GIADE.
// email: antoniorr@correo.ugr.es DNI o pasaporte: 78108407Q.

// *********************************************************************
// **
// ** Asignatura: INFORMÁTICA GRÁFICA
// ** 
// ** Mallas indexadas (implementación)
// ** Copyright (C) 2016-2023 Carlos Ureña
// **
// ** Implementación de las clases 
// **    + MallaRevol: malla indexada de triángulos obtenida por 
// **      revolución de un perfil (derivada de MallaInd)
// **    + MallaRevolPLY: malla indexada de triángulos, obtenida 
// **      por revolución de un perfil leído de un PLY (derivada de MallaRevol)
// **    + algunas clases derivadas de MallaRevol
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
#include "lector-ply.h"
#include "malla-revol.h"

using namespace std ;

// *****************************************************************************




// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar
(
   const std::vector<glm::vec3> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias  // número de copias del perfil
)
{
   using namespace glm ;
   
   // COMPLETAR: práctica 2: implementar algoritmo de creación de malla de revolución
   //
   // Escribir el algoritmo de creación de una malla indexada por revolución de un 
   // perfil, según se describe en el guion de prácticas.
   //
   // ...............................
   int m = perfil.size();

   // Calcular las normales de las aristas y distancias euclidias para coordenadas de textura del perfil
   vector<vec3> normales_aristas_perfil;
   vector<float> di;
   float suma_dist = 0.0;
   for (int i = 0; i < m - 1; i++) {
      vec3 mi = (cross(perfil[i + 1] - perfil[i], vec3(1.0f, 1.0f, 1.0f)));
      normales_aristas_perfil.push_back(normalize(mi));

      di.push_back(sqrt((perfil[i + 1] - perfil[i]).length() * (perfil[i + 1] - perfil[i]).length()));
      suma_dist += di[i];
   }

   // Cálculo de las normales de los vertices del perfil
   int tam_aristas_perfil = normales_aristas_perfil.size();
   std::vector<vec3> normales_vertices_perfil;
   normales_vertices_perfil.push_back(normales_aristas_perfil[0]);
   for (int i = 1; i < tam_aristas_perfil; i++) {
      normales_vertices_perfil.push_back(normalize(normales_aristas_perfil[i - 1] + normales_aristas_perfil[i]));
   }
   normales_vertices_perfil.push_back(normales_aristas_perfil[tam_aristas_perfil-1]);

   // Cálculo de las coordenadas de textura.
   vector<float> ti;
   float suma_parcial = 0;
   for (unsigned i = 0; i < m; i++)
   {
      ti.push_back(suma_parcial / suma_dist);
      if (i < m - 1)
         suma_parcial += di[i];
   }
   ti.push_back(1.0);
   
   // GENERACIÓN DE VÉRTICES. 
   for (int i = 0; i < num_copias; i++) {
      for (int j = 0; j < m; j++) {
         float angulo = 2 * M_PI * i / (num_copias - 1);
         vertices.push_back({perfil[j].x * cos(angulo), perfil[j].y, (-perfil[j].x )* sin(angulo)});

         // GENERACIÓN DE LAS NORMALES
         nor_ver.push_back(normalize(vec3(normales_vertices_perfil[j].x * cos(angulo), normales_vertices_perfil[j].y,-normales_vertices_perfil[j].x * sin(angulo)))); 

         // GENERACIÓN DE LAS COORDENADAS DE TEXTURA
         cc_tt_ver.push_back({((float)i) / ((float)num_copias - 1), 1 - ti[j]});      
      }  
   }

   // Calcular y asignar colores // Lo utilicé para el cohete
   // int n = 0;
   // for (const auto& v : vertices) {
   //    if (n % 2 == 0)
   //       col_ver.push_back({0.0, 0.0, 0.0});
   //    else
   //       col_ver.push_back({1.0, 1.0, 1.0});
   //    n++;
   // }

   // GENERACIÓN DE TRIÁNGULOS.
   for (int i = 0; i < num_copias - 1; i++) {
      for (int j = 0; j < m - 1; j++) {
         int k = i * m + j;
         triangulos.push_back({k, k + m, k + m + 1});
         triangulos.push_back({k, k + m + 1, k + 1});
      }
   }

}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY
(
   const std::string & nombre_arch,
   const unsigned      nperfiles
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
   // ...........................
   vector<glm::vec3> perfil;
   LeerVerticesPLY(nombre_arch, perfil);
   inicializar(perfil, nperfiles);

}

Cilindro::Cilindro(const int num_verts_per, const unsigned nperfiles)
{
   std::vector<glm::vec3> perfil;  // Perfil original

   // Construir perfil
   perfil = {
      {+1, 0, 0},
      {+1, 0, 1},
      {+1, 1, 1},
      {+1, 1, 0}
   };

   // Inicializar la malla por revolución con el perfil y el número de perfiles
   inicializar(perfil, nperfiles);
}

Cono::Cono(const int num_verts_per, const unsigned nperfiles)
{
   std::vector<glm::vec3> perfil;  // Perfil original

   // Construir perfil
   perfil = {
      {+1, 0, 0},
      {+1, 0, 1},
      {0, 1, 0}
   };

   // Inicializar la malla por revolución con el perfil y el número de perfiles
   inicializar(perfil, nperfiles);
}

Esfera::Esfera(const int num_verts_per, const unsigned nperfiles)
{
   //ponerNombre("Ésfera por malla por revolución del perfil");
   //std::vector<glm::vec3> perfil;  // Perfil original

   // Construir perfil (manualmente)
   /*perfil = {
     {0,-1,0},
     {0.37,-0.9,0.37},
     {0.65,-0.75,0.65},
     {0.75,-0.65,0.75},
     {0.85,-0.5,0.85},
     {0.95,-0.25,0.95},
     {1,0,1},
     // mitad superior:
     {0.95,0.25,0.95},
     {0.85,0.5,0.85},
     {0.75,0.65,0.75},
     {0.65,0.75,0.65},
     {0.37,0.9,0.37},
     {0,1,0}

   };*/
   std::vector<glm::vec3> perfil;
   for (int i = 0; i < num_verts_per; ++i) {
      float angulo = 2 * M_PI * i / (num_verts_per - 1);
      float x = cos(angulo);
      float y = sin(angulo);
      perfil.push_back( {x, y, 0.0});
   }
   inicializar(perfil,nperfiles);

}

SemiEsfera::SemiEsfera(const int num_verts_per, const unsigned nperfiles)
{
   std::vector<glm::vec3> perfil;
   for (int i = 0; i < num_verts_per/2; ++i) {
      float angulo = M_PI * i / (num_verts_per - 1);
      float x = cos(angulo);
      float y = sin(angulo);
      perfil.push_back( {x, y, 0.0});
   }
   perfil.push_back({0.0, 0.0, 1.0});
   inicializar(perfil,nperfiles);

}

Piramide::Piramide(const int num_verts_per, const unsigned nperfiles)
{
   std::vector<glm::vec3> perfil;
   perfil = {{0.5, 0.0, -0.5},
            {0.5, 0.0, 0.5},
            {0.0, 1.0, 0.0}};
   inicializar(perfil,nperfiles);
}