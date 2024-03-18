// Nombre: José Antonio, Apellidos: Carmona Molina, Titulación: GIADE.
// email: jacarmona@correo.ugr.es, DNI o pasaporte: 77552812D

#include "examen-extr-pracs.h"

P1Malla::P1Malla()
:  MallaInd( "P1Malla" )
{

   vertices =
      {  { -3.0, 0.0, -3.0 }, // 0
         { -3.0, 0.0, -1.0 }, // 1
         { -3.0, 0.0, +3.0 }, // 2
         { -1.0, 0.0, +3.0 }, // 3
         { +3.0, 0.0, +3.0 }, // 4
         { +3.0, 0.0, +1.0 }, // 5
         { +3.0, 0.0, -3.0 }, // 6
         { +1.0, 0.0, -3.0 }, // 7
         { -1.0, 0.0, -1.0 }, // 8
         { -1.0, 0.0, +1.0 }, // 9
         { +1.0, 0.0, +1.0 }, // 10
         { +1.0, 0.0, -1.0 }, // 11
         { 0.0, 3.0, 0.0 }, // 12         
      } ;

   //ponerColor({0,0,0});

   triangulos =
      {  {0,1,8}, {1,8,9}, // X-
         {1,9,2}, {2,3,9}, // X+ (+4)

         {3,9,10}, {3,10,4}, // Y-
         {4,10,5}, {5,10,11}, // Y+ (+2)

         {5,11,6}, {6,11,7}, // Z-
         {7,11,8}, {7,8,0},  // Z+ (+1)

         {8,12,9}, {9,12,10},
         {10,12,11}, {11,12,8}
      } ;

   calcularNormales();

}

P2Fuente::P2Fuente(const unsigned int n)
{
   std::vector<glm::vec3> perfil;  // Perfil original
   ponerNombre("P2Fuente");

   assert(n > 23);
   assert(n % 3 == 0);
   
   // Construir perfil
   perfil = {
      {+4, 0, 0},
      {+1, 0.5, 0},
      {0.5, 6, 0},
      {4, 7.5, 0}
   };

   // Inicializar la malla por revolución con el perfil y el número de perfiles
   inicializar(perfil, n+1);
}

P2Anillo::P2Anillo(const int n, const unsigned m, float w)
{
   std::vector<glm::vec3> perfil;  // Perfil original
   ponerNombre("P2Anillo");
   float _w = 1.0 + w;
   
   // Construir perfil
   perfil = {
      {+1.0, 0.00001, 0.0},
      {_w, 0.0, 0.0}
   };


   // Inicializar la malla por revolución con el perfil y el número de perfiles
   inicializar(perfil, n);
}

P3Rotonda::P3Rotonda(){    

    using namespace glm;

    NodoGrafoEscena * fuente = new NodoGrafoEscena();

    fuente->agregar (glm::scale(glm::vec3(0.25, 0.25, 0.25)) );
    fuente->agregar(new P2Fuente(24));
    agregar(fuente);

    NodoGrafoEscena * anillo_interior = new NodoGrafoEscena();

    anillo_interior->agregar (glm::scale(glm::vec3(1.2, 1.2, 1.2)) );
    anillo_interior->agregar(new P2Anillo(24, 1, 3.5));
    agregar(anillo_interior);

    NodoGrafoEscena * anillo_exterior = new NodoGrafoEscena();

    anillo_exterior->agregar (glm::scale(glm::vec3(6, 6, 6)) );
    anillo_exterior->agregar(new P2Anillo(24, 1, 0.6));
    agregar(anillo_exterior);

    NodoGrafoEscena * coche = new NodoGrafoEscena();

    unsigned ind_coche = coche->agregar(glm::scale(glm::vec3(1.0,1.0,1.0)));
    coche->agregar(glm::translate(glm::vec3(7,0.2,0.0)));
    coche->agregar (glm::scale(glm::vec3(0.075, 0.075, 0.075)) );
    coche->agregar(glm::rotate(radians(90.0f), glm::vec3(0.0f,1.0f,0.0f)));
    coche->agregar(new MallaPLY("big_dodge"));
    gira_coche = coche->leerPtrMatriz(ind_coche);
    agregar(coche);


}

unsigned P3Rotonda::leerNumParametros() const {
        return 1;
}

void P3Rotonda::actualizarEstadoParametro(const unsigned iParam, const float t_sec){//Debería quedarse dando vueltas permanentemente, no lo hace debido a la asignación manual de los 90 grados
    switch (iParam)                                                                 
    {
    case 0:
        girarCoche(angulo * 3 * t_sec);
        break;
    }
}

void P3Rotonda::girarCoche(const float t_sec )
{
    *gira_coche = glm::rotate( glm::radians(angulo), glm::vec3( 0.0, 1.0, 0.0 ));
}

P4Rotonda::P4Rotonda(){    

    using namespace glm;

    NodoGrafoEscena * fuente = new NodoGrafoEscena();

    fuente->agregar (glm::scale(glm::vec3(0.25, 0.25, 0.25)) );
    fuente->ponerColor(vec3(0.5f,0.5f,1.0f));
    fuente->agregar(new Material(0.1f, 0.9f, 0.1f, 10.0f));
    fuente->agregar(new P2Fuente(24));
    agregar(fuente);

    NodoGrafoEscena * anillo_interior = new NodoGrafoEscena();

    anillo_interior->agregar (glm::scale(glm::vec3(1.2, 1.2, 1.2)) );
    Textura * textura_ai = new Textura("window-icon.jpg");
    anillo_interior->agregar(new Material(textura_ai, 0.9f, 0.1f, 0.1f, 10.0f));
    anillo_interior->agregar(new P2Anillo(24, 1, 3.5));
    agregar(anillo_interior);

    NodoGrafoEscena * anillo_exterior = new NodoGrafoEscena();

    anillo_exterior->agregar (glm::scale(glm::vec3(6, 6, 6)) );
    Textura * textura_ae = new Textura("asfalto.jpg");
    anillo_exterior->agregar(new Material(textura_ae, 0.1f, 0.1f, 0.9f, 10.0f));
    anillo_exterior->agregar(new P2Anillo(24, 1, 0.6));
    agregar(anillo_exterior);

    NodoGrafoEscena * coche = new NodoGrafoEscena();

    //unsigned ind_coche = coche->agregar(glm::scale(glm::vec3(1.0,1.0,1.0)));
    coche->agregar(glm::translate(glm::vec3(7,0.2,0.0)));
    coche->agregar (glm::scale(glm::vec3(0.075, 0.075, 0.075)) );
    coche->agregar(glm::rotate(radians(90.0f), glm::vec3(0.0f,1.0f,0.0f)));
    coche->ponerColor(vec3(0.5f,1.0f,0.5f));
    coche->agregar(new Material(0.1f, 0.1f, 0.9f, 10.0f));
    coche->agregar(new MallaPLY("big_dodge"));
    //gira_coche = coche->leerPtrMatriz(ind_coche);
    agregar(coche);


   /*  Textura * textura_cubo = new Textura("ventanas-tejado-2048x1024.jpg");
    pen->ponerIdentificador(3333);
    pen->ponerColor(vec3(1.0f,0.0f,0.0f));
    cubo->agregar(new Material(textura_cubo, 0.6f, 0.8f, 0.1f, 15.0f)); */




}

P5Rotonda::P5Rotonda(){    

    using namespace glm;

    NodoGrafoEscena * fuente = new NodoGrafoEscena();

    fuente->ponerIdentificador(1111);
    fuente->agregar (glm::scale(glm::vec3(0.25, 0.25, 0.25)) );
    fuente->ponerColor(vec3(0.5f,0.5f,1.0f));
    fuente->agregar(new Material(0.1f, 0.9f, 0.1f, 10.0f));
    fuente->agregar(new P2Fuente(24));
    agregar(fuente);

    NodoGrafoEscena * anillo_interior = new NodoGrafoEscena();

    anillo_interior->ponerIdentificador(2222);
    anillo_interior->agregar (glm::scale(glm::vec3(1.2, 1.2, 1.2)) );
    Textura * textura_ai = new Textura("window-icon.jpg");
    anillo_interior->agregar(new Material(textura_ai, 0.9f, 0.1f, 0.1f, 10.0f));
    anillo_interior->agregar(new P2Anillo(24, 1, 3.5));
    agregar(anillo_interior);

    NodoGrafoEscena * anillo_exterior = new NodoGrafoEscena();

    anillo_exterior->ponerIdentificador(3333);
    anillo_exterior->agregar (glm::scale(glm::vec3(6, 6, 6)) );
    Textura * textura_ae = new Textura("asfalto.jpg");
    anillo_exterior->agregar(new Material(textura_ae, 0.1f, 0.1f, 0.9f, 10.0f));
    anillo_exterior->agregar(new P2Anillo(24, 1, 0.6));
    agregar(anillo_exterior);

    NodoGrafoEscena * coche = new NodoGrafoEscena();

    coche->ponerIdentificador(4444);
    //unsigned ind_coche = coche->agregar(glm::scale(glm::vec3(1.0,1.0,1.0)));
    coche->agregar(glm::translate(glm::vec3(7,0.2,0.0)));
    coche->agregar (glm::scale(glm::vec3(0.075, 0.075, 0.075)) );
    coche->agregar(glm::rotate(radians(90.0f), glm::vec3(0.0f,1.0f,0.0f)));
    coche->ponerColor(vec3(0.5f,1.0f,0.5f));
    coche->agregar(new Material(0.1f, 0.1f, 0.9f, 10.0f));
    coche->agregar(new MallaPLY("big_dodge"));
    //gira_coche = coche->leerPtrMatriz(ind_coche);
    agregar(coche);

}

bool P5Rotonda::cuandoClick(const glm::vec3 &centro_wc) //Llama al cuandoClick por defecto, desconozco el motivo, esta sería la implementación:
{      
    if (tieneColor()) {
        if (leerColor() == glm::vec3(1.0,1.0,1.0))
            ponerColor({1.0,0.0,0.0});
        else
            ponerColor({1.0,1.0,1.0});
    } else
        ponerColor({1.0,0.0,0.0});
    std::cout << "Se ha seleccionado el objeto número: " << leerIdentificador() << std::endl;

    return true;
}