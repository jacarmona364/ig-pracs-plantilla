// Nombre: José Antonio, Apellidos: Carmona Molina, Titulación: GIADE.
// email: jacarmona@correo.ugr.es, DNI o pasaporte: 77552812D

#include "examen-ec-p45.h"

MallaP4::MallaP4()
:  MallaInd( "MallaP4" )
{

   for (int i = 0; i < 3; ++i) {
        vertices.push_back({-1.0, -1.0, -1.0}); // 0  8 16
        vertices.push_back({-1.0, -1.0, +1.0}); // 1  9 17
        vertices.push_back({-1.0, +1.0, -1.0}); // 2 10 18
        vertices.push_back({-1.0, +1.0, +1.0}); // 3 11 19

        vertices.push_back({+1.0, -1.0, -1.0}); // 4 12 20
        vertices.push_back({+1.0, -1.0, +1.0}); // 5 13 21
        vertices.push_back({+1.0, +1.0, -1.0}); // 6 14 22
        vertices.push_back({+1.0, +1.0, +1.0}); // 7 15 23

    } 

    //  TEJADO:
    vertices.push_back({-1.0, +1.0, -1.0}); // 2 24
    vertices.push_back({-1.0, +1.0, +1.0}); // 3 25

/*     vertices.push_back({-1.0, +1.0, -1.0}); // 2 26 
    vertices.push_back({+1.0, +1.0, -1.0}); // 6 27 */

    vertices.push_back({+1.0, +1.0, -1.0}); // 6 26
    vertices.push_back({+1.0, +1.0, +1.0}); // 7 27
/* 
    vertices.push_back({+1.0, +1.0, +1.0}); // 7 30
    vertices.push_back({-1.0, +1.0, +1.0}); // 3 31 */
    
    vertices.push_back({0.0, +2.0, 0.0}); // punta 1, 28
    vertices.push_back({0.0, +2.0, 0.0}); // punta 2, 29
    vertices.push_back({0.0, +2.0, 0.0}); // punta 3, 30
    vertices.push_back({0.0, +2.0, 0.0}); // punta 4, 31


    //CARA X- (Considero Z = -1 --> derecha(s=1) y Y = -1 --> arriba(t=1))
    cc_tt_ver.push_back({0.0, 1.0}); // 0
    cc_tt_ver.push_back({1.0/4.0, 1.0}); // 1
    cc_tt_ver.push_back({0.0, 1.0/2.0}); // 2
    cc_tt_ver.push_back({1.0/4.0, 1.0/2.0}); // 3
    //CARA X+
    cc_tt_ver.push_back({3.0/4.0, 1.0}); // 4
    cc_tt_ver.push_back({1.0/2.0, 1.0}); // 5
    cc_tt_ver.push_back({3.0/4.0, 1.0/2.0}); // 6
    cc_tt_ver.push_back({1.0/2.0, 1.0/2.0}); // 7
    //CARA Y- e Y+ (Considero X = -1 --> izquierda(s=0) y Z = -1 --> abajo(t=0))
    cc_tt_ver.push_back({3.0/4.0, 0.0}); // 8 Y-
    cc_tt_ver.push_back({3.0/4.0, 1.0/2.0}); // 9 Y-
    cc_tt_ver.push_back({0.0, 1.0/2.0}); // 10 Y+
    cc_tt_ver.push_back({1.0/4.0, 1.0/2.0}); // 11 Y+
    cc_tt_ver.push_back({1.0, 0.0}); // 12 Y-
    cc_tt_ver.push_back({1.0, 1.0/2.0}); // 13 Y-
    cc_tt_ver.push_back({0.0, 0.0}); // 14 Y+
    cc_tt_ver.push_back({1.0/4.0, 0.0}); // 15 Y+
    //CARA Z- e Z+ (Considero X = -1 --> izquierda(s=0) y Y = -1 --> arriba(t=1))
    cc_tt_ver.push_back({1.0, 1.0}); // 16 Z-
    cc_tt_ver.push_back({1.0/4.0, 1.0}); // 17 Z+
    cc_tt_ver.push_back({1.0, 1.0/2.0}); // 18 Z-
    cc_tt_ver.push_back({1.0/4.0, 1.0/2.0}); // 19 Z+
    cc_tt_ver.push_back({3.0/4.0, 1.0}); // 20 Z-
    cc_tt_ver.push_back({1.0/2.0, 1.0}); // 21 Z+
    cc_tt_ver.push_back({3.0/4.0, 1.0/2.0}); // 22 Z-
    cc_tt_ver.push_back({1.0/2.0, 1.0/2.0}); // 23 Z+

    cc_tt_ver.push_back({0.0, 0.0}); // 24
    cc_tt_ver.push_back({1.0/4.0, 1.0/2.0}); // 25
    cc_tt_ver.push_back({0.0, 0.0}); // 26
    cc_tt_ver.push_back({1.0/4.0, 0.0}); // 27
    cc_tt_ver.push_back({1.0/8.0, 1.0/8.0}); // 28
    cc_tt_ver.push_back({1.0/8.0, 1.0/8.0}); // 29
    cc_tt_ver.push_back({1.0/8.0, 1.0/8.0}); // 30
    cc_tt_ver.push_back({1.0/8.0, 1.0/8.0}); // 31

   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {8, 13, 9}, {8, 12, 13},
         {10, 11, 28}, {14, 15, 29},

         {16, 22, 20}, {16, 18, 22},
         {17, 21, 23}, {17, 23, 19},

         {27,25,30}, {26,24,31}
      } ;

      calcularNormales();
}

NodoP4::NodoP4() {
    NodoGrafoEscena * cubo = new NodoGrafoEscena();
    Textura * textura_cubo = new Textura("ventanas-tejado-2048x1024.jpg");
    cubo->agregar(new Material(textura_cubo, 0.6f, 0.8f, 0.1f, 15.0f));
    cubo->agregar(new MallaP4());
    agregar(cubo);
}

NodoUrbaP5::NodoUrbaP5(unsigned int ident)
{
    identificador = ident;
    ponerIdentificador(identificador);
    ind_casa = agregar(glm::scale(glm::vec3(1.0,1.0,1.0)));
    agregar(new NodoP4()); 
        
}

void NodoUrbaP5::movimiento() {
    *nuevaTransformacion = glm::rotate(glm::radians(rotacionEjey), glm::vec3(0.0f, 1.0f, 0.0f));
    rotacionEjey+=30.0;
}

unsigned NodoUrbaP5::leerNumParametros() const {
    return NUM_PARAM;
}

void NodoUrbaP5::actualizarEstadoParametro( const unsigned iParam, const float t_sec ) {
    switch (iParam) {
        case 0:
            movimiento();
            break;
        default:
            break;
    }
}

bool NodoUrbaP5::cuandoClick(const glm::vec3 &centro_wc) {
    // Obtener la matriz de transformación actual y aplicar el desplazamiento en Z
    std::cout << "Has hecho click en la casa numero: " << identificador << std::endl;
    nuevaTransformacion = leerPtrMatriz(ind_casa);
    actualizarEstado(ind_casa);
    return true;
}


ObjetoMultiple::ObjetoMultiple(int num_casas) {
    for (int i = 0; i < num_casas; i++) {
        agregar(new NodoUrbaP5(i+1));
        agregar(glm::translate(glm::vec3(2.0f, 0.0f, 0.0)));
    }
}