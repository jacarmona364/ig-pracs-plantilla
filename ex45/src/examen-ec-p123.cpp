// Nombre: Antonio, Apellidos: Rodríguez Rodríguez, Titulación: GIADE.
// email: antoniorr@correo.ugr.es DNI o pasaporte: 78108407Q.

// NOMBRE: Antonio APELLIDOS: Rodríguez Rodríguez TITULACIÓN: Ingeniería Informática + ADE
// DNI: 78108407Q

#include "examen-ec-p123.h"

// EJERCICIO 1:

P1MallaCubo::P1MallaCubo()
:  MallaInd( "Cubo de colores" )
{

    vertices =
    {   { -1.0, -1.0, -1.0 }, // 0
        { -1.0, -1.0, +1.0 }, // 1
        { -1.0, +1.0, -1.0 }, // 2
        { -1.0, +1.0, +1.0 }, // 3
        { +1.0, -1.0, -1.0 }, // 4
        { +1.0, -1.0, +1.0 }, // 5
        { +1.0, +1.0, -1.0 }, // 6
        { +1.0, +1.0, +1.0 }, // 7
        { 0.0, -1.0, 0.0 }, // Nuevo vértice inferior
        { 0.0, +1.0, 0.0 } // Nuevo vértice superior
    } ;

    // Calcular y asignar colores basados en las componentes de posición
    for (const auto& v : vertices) {
        float r = (v.x + 1.0) / 2.0;  // Componente R depende de X
        float g = (v.y + 1.0) / 2.0;  // Componente G depende de Y
        float b = (v.z + 1.0) / 2.0;  // Componente B depende de Z
        col_ver.push_back({r, g, b});
    }

    // Colores de los vértices
    col_ver[8] = {1,0,0};
    col_ver[9] = {0,0,1};


    triangulos =
    {   {0,1,3}, {0,3,2}, // X-
        {4,7,5}, {4,6,7}, // X+ (+4)

        {0,1,8}, {0,4,8}, // Y-
        {1,5,8}, {5,4,8}, // Nuevos triángulos cara inferior
        {2,6,9}, {3,7,9},  // Y+ (+2)
        {7,6,9}, {2,3,9},// Nuevos triángulos cara superior 2 3 6 7

        {0,6,4}, {0,2,6}, // Z-
        {1,5,7}, {1,7,3}  // Z+ (+1)
    } ;

}


// EJERCICIO 2:

P2Rejilla::P2Rejilla(const unsigned n, const unsigned m)
:     MallaInd("P2RejillaY")
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

// EJERCICIO 3:

P3Cuadrado::P3Cuadrado()
:  MallaInd( "Cuadrado" )
{

    vertices =
    {   { -1.0, 0.0, -1.0 }, // 0
        { -1.0, 0.0, +1.0 }, // 1
        { +1.0, 0.0, -1.0 }, // 2
        { +1.0, 0.0, +1.0 }  // 3
    } ;


    triangulos = {   {0,1,3}, {0,3,2}    } ;

}


P3Caja::P3Caja( const float h_max_bola, const float alpha_rotacion) 
:  NodoGrafoEscena() {

    alpha_tapas = alpha_rotacion;
    altura_max_bola = h_max_bola;

    using namespace glm;
    NodoGrafoEscena * caja = new NodoGrafoEscena();
    NodoGrafoEscena * tapa_izq = new NodoGrafoEscena();
    NodoGrafoEscena * tapa_derecha = new NodoGrafoEscena();
    NodoGrafoEscena * bola = new NodoGrafoEscena();

    unsigned ind_mover_bola = bola->agregar(scale(vec3(1.0,1.0,1.0)));

    // PARTE INMÓVIL DE LA CAJA
    caja->agregar( new P3Cuadrado() );
    caja->agregar ( translate( vec3(1.0f,1.0f, 0.0f)) );
    caja->agregar ( rotate(radians(90.0f), vec3(0.0f,0.0f,1.0f)) );
    caja->agregar( new P3Cuadrado() );
    caja->agregar ( rotate(radians(-90.0f), vec3(0.0f,0.0f,1.0f)) );
    caja->agregar ( translate(vec3(-2.0f,0.0f,0.0f)) );
    caja->agregar ( rotate(radians(-90.0f), vec3(0.0f,0.0f,1.0f)) );
    caja->agregar( new P3Cuadrado() );
    caja->agregar ( rotate(radians(90.0f), vec3(0.0f,0.0f,1.0f)) );
    agregar(caja);
    agregar(rotate(radians(90.0f), vec3(0.0f,1.0f,0.0f)));
    agregar(caja);
    agregar(rotate(radians(-90.0f), vec3(0.0f,1.0f,0.0f)));

    // TAPAS DE LA CAJA
    tapa_derecha->agregar ( translate( vec3(0.5f,2.0f, 0.0f)) );
    unsigned ind_mover_tapa_derecha = tapa_derecha->agregar(scale(vec3(1.0,1.0,1.0)));
    tapa_derecha->agregar ( scale(vec3(0.5,1.0,1.0)) );
    tapa_derecha->agregar( new P3Cuadrado() );
    agregar(tapa_derecha);
    agregar(translate( vec3(-1.0f, 0.0f, 0.0f)));
    tapa_izq->agregar(tapa_derecha);
    agregar(tapa_izq);
    unsigned ind_mover_tapa_izq = tapa_izq->agregar(scale(vec3(1.0,1.0,1.0)));
    agregar(translate( vec3(1.0f, 0.0f, 0.0f)));

    bola->agregar ( translate( vec3(0.0f,0.75f, 0.0f)) );
    bola->agregar ( scale(vec3(0.5,0.5,0.5)) );
    bola->agregar(new Esfera(30,30));
    agregar(bola);
    

    agregar(caja);

    // Movimiento de las tapas
    levantar_tapa_derecha = tapa_derecha->leerPtrMatriz(ind_mover_tapa_derecha);
    levantar_tapa_izq = tapa_izq->leerPtrMatriz(ind_mover_tapa_izq);
    // Despegue y aterrizaje
    levantar_bola = bola->leerPtrMatriz(ind_mover_bola);
}
unsigned P3Caja::leerNumParametros() const {
   return NUM_PARAM;
}

void P3Caja::actualizarEstadoParametro( const unsigned iParam, const float t_sec ) {
   switch (iParam)
   {
   case 0:
      levantar_tapas(alpha_tapas);
      break;
   case 1:
      movimiento_bola(altura_max_bola, t_sec);
      break;
   default:
      break;
   }
}

void P3Caja::levantar_tapas( const float alpha_rotacion )
{
   *levantar_tapa_derecha = glm::rotate( -float(glm::radians(alpha_rotacion)), glm::vec3( 0.0, 0.0, 1.0 ));
   *levantar_tapa_izq = glm::rotate( float(glm::radians(alpha_rotacion)), glm::vec3( 0.0, 0.0, 1.0 ));
}

void P3Caja::movimiento_bola( const float h_maxima_bola, const float t_sec )
{
   // Calcula una posición vertical (en el eje Y) en función del tiempo
   float verticalPosition = h_maxima_bola + h_maxima_bola * sin(2 * M_PI * t_sec);
   *levantar_bola = glm::translate( glm::vec3( 0.0, verticalPosition, 0.0 ) );
}