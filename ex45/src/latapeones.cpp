// Nombre: Antonio, Apellidos: Rodríguez Rodríguez, Titulación: GIADE.
// email: antoniorr@correo.ugr.es DNI o pasaporte: 78108407Q.

#include "latapeones.h"
#include "aplicacion-ig.h"

LataPeones::LataPeones() {
    // LATA
    NodoGrafoEscena * lata_cola = new NodoGrafoEscena();
    lata_cola->agregar(new MallaRevolPLY("lata-pinf.ply", 24));
    lata_cola->agregar(new MallaRevolPLY("lata-psup.ply", 24));
    lata_cola->agregar(new Material(new Textura("lata-coke.jpg"), 0.35f, 1.5f, 1.5f, 10.0f));
    lata_cola->agregar(new MallaRevolPLY("lata-pcue.ply", 24));
    agregar(lata_cola);

    // PEONES
    NodoGrafoEscena * peon1 = new NodoGrafoEscena();
    NodoGrafoEscena * peon2 = new NodoGrafoEscena();
    NodoGrafoEscena * peon3 = new NodoGrafoEscena();
    agregar(glm::translate( glm::vec3(0.0f,0.35f, 1.0f)));
    agregar ( glm::scale(glm::vec3(0.25,0.25,0.25)) );
    peon1->agregar(new Material(new Textura("text-madera.jpg"), 0.35f, 1.5f, 1.5f, 10.0f));
    peon1->agregar(new MallaRevolPLY("peon.ply", 24));
    agregar(peon1);
    agregar(glm::translate( glm::vec3(2.5f,0.0f, 0.0f)));
    peon2->ponerColor({1.0,1.0,1.0});
    peon2->agregar(new MallaRevolPLY("peon.ply", 24));
    agregar(peon2);
    agregar(glm::translate( glm::vec3(2.5f,0.0f, 0.0f)));
    peon3->ponerColor(glm::vec3(0.0,0.0,0.0));
    peon3->agregar(new Material(0.35f, 1.5f, 1.5f, 10.0f));
    peon3->agregar(new MallaRevolPLY("peon.ply", 24));
    agregar(peon3);
}

MallaDiscoP4::MallaDiscoP4(int mode)
{
    ponerColor({1.0, 1.0, 1.0});
    const unsigned ni = 23, nj = 31;
    for (unsigned i = 0; i < ni; i++)
        for (unsigned j = 0; j < nj; j++)
        {
            const float
                fi = float(i) / float(ni - 1),
                fj = float(j) / float(nj - 1),
                ai = 2.0 * M_PI * fi,
                x = fj * cos(ai),
                y = fj * sin(ai),
                z = 0.0;
            vertices.push_back({x, y, z});
            // Añadir las coordenadas de textura
            if (mode == 1)
                cc_tt_ver.push_back({fi, fj});
            else
                cc_tt_ver.push_back({x,y});
        }

    for (unsigned i = 0; i < ni - 1; i++)
        for (unsigned j = 0; j < nj - 1; j++)
        {
            triangulos.push_back({i * nj + j, i * nj + (j + 1), (i + 1) * nj + (j + 1)});
            triangulos.push_back({i * nj + j, (i + 1) * nj + (j + 1), (i + 1) * nj + j});
        }

    
    calcularNormales();
}

NodoDiscoP4::NodoDiscoP4()
{
    ponerNombre("Nodo ejercicio adicional práctica 4, examen 27 enero");
    agregar(new Material(new Textura("cuadricula.jpg"), 0.35f, 1.5f, 1.5f, 10.0f));
    agregar(new MallaDiscoP4(0));
    agregar(glm::translate( glm::vec3(0.0f,2.0f, 0.0f)));
    agregar(new MallaDiscoP4(1));
}


// ****************************************************************************
// Clase 'Cubo24

Cubo24::Cubo24()
:  MallaInd( "cubo24 8 vértices" )
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

    //CARA X- (Considero Z = -1 --> derecha(s=1) y Y = -1 --> arriba(t=1))
    cc_tt_ver.push_back({1.0, 1.0}); // 0
    cc_tt_ver.push_back({0.0, 1.0}); // 1
    cc_tt_ver.push_back({1.0, 0.0}); // 2
    cc_tt_ver.push_back({0.0, 0.0}); // 3
    //CARA X+
    cc_tt_ver.push_back({1.0, 1.0}); // 4
    cc_tt_ver.push_back({0.0, 1.0}); // 5
    cc_tt_ver.push_back({1.0, 0.0}); // 6
    cc_tt_ver.push_back({0.0, 0.0}); // 7
    //CARA Y- e Y+ (Considero X = -1 --> izquierda(s=0) y Z = -1 --> abajo(t=0))
    cc_tt_ver.push_back({0.0, 0.0}); // 8 Y-
    cc_tt_ver.push_back({0.0, 1.0}); // 9 Y-
    cc_tt_ver.push_back({0.0, 0.0}); // 10 Y+
    cc_tt_ver.push_back({0.0, 1.0}); // 11 Y+
    cc_tt_ver.push_back({1.0, 0.0}); // 12 Y-
    cc_tt_ver.push_back({1.0, 1.0}); // 13 Y-
    cc_tt_ver.push_back({1.0, 0.0}); // 14 Y+
    cc_tt_ver.push_back({1.0, 1.0}); // 15 Y+
    //CARA Z- e Z+ (Considero X = -1 --> izquierda(s=0) y Y = -1 --> arriba(t=1))
    cc_tt_ver.push_back({0.0, 1.0}); // 16 Z-
    cc_tt_ver.push_back({0.0, 1.0}); // 17 Z+
    cc_tt_ver.push_back({0.0, 0.0}); // 18 Z-
    cc_tt_ver.push_back({0.0, 0.0}); // 19 Z+
    cc_tt_ver.push_back({1.0, 1.0}); // 20 Z-
    cc_tt_ver.push_back({1.0, 1.0}); // 21 Z+
    cc_tt_ver.push_back({1.0, 0.0}); // 22 Z-
    cc_tt_ver.push_back({1.0, 0.0}); // 23 Z+



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)
        //  {0,5,1}, {0,4,5}, // Y-
        //  {2,3,7}, {2,7,6}, // Y+ (+2)
        //  {0,6,4}, {0,2,6}, // Z-
        //  {1,5,7}, {1,7,3},  // Z+ (+1)

         // {8, 9, 11}, {8, 11, 10},
         // {12, 15, 13}, {12, 14, 15},

         {8, 13, 9}, {8, 12, 13},
         {10, 11, 15}, {10, 15, 14},

         // {8, 14, 12}, {8, 10, 14},
         // {9, 13, 15}, {9, 15, 11},

         // {16, 17, 19}, {16, 19, 18},
         // {20, 23, 21}, {20, 22, 23},
         // {16, 21, 17}, {16, 20, 21},
         // {18, 19, 23}, {18, 23, 22},

         {16, 22, 20}, {16, 18, 22},
         {17, 21, 23}, {17, 23, 19}
      } ;

      calcularNormales();

}

NodoCubo24::NodoCubo24() {
    NodoGrafoEscena * cubo = new NodoGrafoEscena();
    Textura * textura_cubo = new Textura("window-icon.jpg");
    cubo->agregar(new Material(textura_cubo, 2.0f, 2.0f, 2.0f, 2.0f));
    cubo->agregar(new Cubo24());
    agregar(cubo);
}

CuadradoPruebaTexturas::CuadradoPruebaTexturas()
:  MallaInd( "CuadradoPruebaTexturas" )
{

   vertices.push_back({-1.0, -1.0, -1.0}); // 0
   vertices.push_back({-1.0, -1.0, +1.0}); // 1
   vertices.push_back({-1.0, +1.0, -1.0}); // 2
   vertices.push_back({-1.0, +1.0, +1.0}); // 3


   triangulos = {  {0,1,3}, {0,3,2} }; // X- 

    // S --> Coordenadas horizontales
    // T --> Coordenadas verticales

    cc_tt_ver.push_back({1.0, 1.0}); // 0  8 16
    cc_tt_ver.push_back({0.0, 1.0}); // 1  9 17
    cc_tt_ver.push_back({1.0, 0.0}); // 2 10 18
    cc_tt_ver.push_back({0.0, 0.0}); // 3 11 19
    //  NOTA: Si cambio todos los 0.0 por -1.0
    // --> Me saldrían 4 logos en la misma cara.

    calcularNormales();

}

NodoPruebaTextura::NodoPruebaTextura() {
    NodoGrafoEscena * cubo = new NodoGrafoEscena();
    Textura * textura_cubo = new Textura("window-icon.jpg");
    cubo->agregar(new Material(textura_cubo, 2.0f, 2.0f, 2.0f, 2.0f));
    cubo->agregar(new CuadradoPruebaTexturas());
    agregar(cubo);
}

class PeonDesplazable : public NodoGrafoEscena {
private:
    NodoGrafoEscena * peon = new NodoGrafoEscena();
    int identificador = 1;
    glm::mat4 * nuevaTransformacion = nullptr;
    float desplazamientoZ; // Distancia a desplazar en el eje Z al hacer clic
    unsigned int ind_peon = 0;
    int NUM_PARAM = 1;

public:
    PeonDesplazable(int ident, int tipoPeon, float desplazamiento) {
        desplazamientoZ = desplazamiento;
        identificador = ident;
        ponerIdentificador(identificador);
        ind_peon = agregar(glm::scale(glm::vec3(1.0,1.0,1.0)));
        if (tipoPeon == 1) {
            ponerNombre("Peon madera");
            agregar(new Material(new Textura("text-madera.jpg"), 0.35f, 1.5f, 1.5f, 10.0f));
            agregar(new MallaRevolPLY("peon.ply", 24));
        } else if (tipoPeon == 2) {
            ponerNombre("Peon blanco");
            ponerColor(glm::vec3(1.0,1.0,1.0));
            agregar(new Material(0.35f, 1.5f, 1.5f, 10.0f));
            agregar(new MallaRevolPLY("peon.ply", 24));
        } else {
            ponerNombre("Peon negro");
            ponerColor(glm::vec3(0.0,0.0,0.0));
            agregar(new Material(0.35f, 1.5f, 1.5f, 10.0f));
            agregar(new MallaRevolPLY("peon.ply", 24));
        }
    }

    NodoGrafoEscena * Peon() {
        return peon;
    }

    void movimiento() {
        *nuevaTransformacion = glm::translate(glm::vec3(0.0f, 0.0f, desplazamientoZ));
        desplazamientoZ++;
    }

    unsigned leerNumParametros() const {
        return NUM_PARAM;
    }

    void actualizarEstadoParametro( const unsigned iParam, const float t_sec ) {
        switch (iParam) {
            case 0:
                movimiento();
                break;
            default:
                break;
        }
    }

    virtual bool cuandoClick(const glm::vec3 &centro_wc) {
        // Obtener la matriz de transformación actual y aplicar el desplazamiento en Z
        nuevaTransformacion = leerPtrMatriz(ind_peon);
        actualizarEstado(ind_peon);
        return true;
    }
};

class lataPepsi : public NodoGrafoEscena {
    public:
        lataPepsi() {
            ponerNombre("Lata Pepsi");
            ponerIdentificador(123230);
            agregar(glm::translate( glm::vec3(1.0f,0.0f, 0.0f)));
            agregar(new MallaRevolPLY("lata-pinf.ply", 24));
            agregar(new MallaRevolPLY("lata-psup.ply", 24));
            agregar(new Material(new Textura("lata-pepsi.jpg"), 0.35f, 1.5f, 1.5f, 10.0f));
            agregar(new MallaRevolPLY("lata-pcue.ply", 24));
        }
};

class lataCola : public NodoGrafoEscena {
    public:
        lataCola() {
            ponerNombre("Lata Cola");
            ponerIdentificador(1232353);
            agregar(new MallaRevolPLY("lata-pinf.ply", 24));
            agregar(new MallaRevolPLY("lata-psup.ply", 24));
            agregar(new Material(new Textura("lata-coke.jpg"), 0.35f, 1.5f, 1.5f, 10.0f));
            agregar(new MallaRevolPLY("lata-pcue.ply", 24));
        }
};

VariasLatasPeones::VariasLatasPeones(int desplazamientoZ) {
    // LATAS
    agregar(new lataCola());
    agregar(new lataPepsi());

    NodoGrafoEscena * lata_ugr = new NodoGrafoEscena();
    lata_ugr->ponerNombre("Lata UGR");
    lata_ugr->ponerIdentificador(2);
    lata_ugr->agregar(glm::translate( glm::vec3(2.0f,0.0f, 0.0f)));
    lata_ugr->agregar(new MallaRevolPLY("lata-pinf.ply", 24));
    lata_ugr->agregar(new MallaRevolPLY("lata-psup.ply", 24));
    lata_ugr->agregar(new Material(new Textura("window-icon.jpg"), 0.35f, 1.5f, 1.5f, 10.0f));
    lata_ugr->agregar(new MallaRevolPLY("lata-pcue.ply", 24));
    agregar(lata_ugr);
    // NodoGrafoEscena * lata_sprite = new NodoGrafoEscena();
    // lata_sprite->ponerNombre("Lata sprite");
    // lata_sprite->ponerIdentificador(n);
    // lata_sprite->agregar(glm::translate( glm::vec3(3.0f,0.0f, 0.0f)));
    // lata_sprite->agregar(new MallaRevolPLY("lata-pinf.ply", 24));
    // lata_sprite->agregar(new MallaRevolPLY("lata-psup.ply", 24));
    // lata_sprite->agregar(new Material(new Textura("lata-sprite.jpg"), 0.35f, 1.5f, 1.5f, 10.0f));
    // lata_sprite->agregar(new MallaRevolPLY("lata-pcue.ply", 24));
    // agregar(lata_sprite);

    // PEONES
    agregar(glm::translate( glm::vec3(0.0f,0.35f, 1.0f)));
    agregar ( glm::scale(glm::vec3(0.25,0.25,0.25)) );
    agregar(new PeonDesplazable(1234, 1, desplazamientoZ));
    agregar(glm::translate( glm::vec3(2.5f,0.0f, 0.0f)));
    agregar(new PeonDesplazable(12334, 2, desplazamientoZ));
    agregar(glm::translate( glm::vec3(2.5f,0.0f, 0.0f)));
    agregar(new PeonDesplazable(12344, 3, desplazamientoZ));
}

MiEsfera::MiEsfera(int i, int j)
{
    int num_verts_per = 50;
    int nperfiles = 50;
    std::vector<glm::vec3> perfil;
    std::string cadena = std::to_string(i) + " " + std::to_string(j);
    ponerNombre(cadena);
    int identificador = (((i+j)*(i+j+1))/2) + i+1; // evitar que se repita identificador
    ponerIdentificador(identificador);
    for (int i = 0; i < num_verts_per; ++i) {
        float angulo = 2 * M_PI * i / (num_verts_per - 1);
        float x = cos(angulo);
        float y = sin(angulo);
        perfil.push_back( {x, y, 0.0});
    }
    inicializar(perfil,nperfiles);

}

GrafoEsferasP5::GrafoEsferasP5()
{
    const unsigned
        n_filas_esferas = 8,
        n_esferas_x_fila = 5;
    const float
        e = 0.4 / n_esferas_x_fila;
    agregar(glm::scale(glm::vec3(e,e,e)));
    for (unsigned i = 0; i < n_filas_esferas; i++)
    {
        NodoGrafoEscena *fila_esferas = new NodoGrafoEscena();
        for (unsigned j = 0; j < n_esferas_x_fila; j++)
        {
            MiEsfera * esfera = new MiEsfera(i,j);
            fila_esferas->agregar(glm::translate(glm::vec3(2.2, 0.0, 0.0)));
            fila_esferas->agregar(esfera);
        }
        agregar(fila_esferas);
        agregar(glm::translate(glm::vec3(0.0, 0.0, 5.0)));
    }
}

bool MiEsfera::cuandoClick(const glm::vec3 &centro_wc) {
    std::cout << "Se ha seleccionado la esfera número: " << leerNombre() << std::endl;
}

GrafoEsferasP5_2::GrafoEsferasP5_2()
{
    const unsigned
        n_filas_esferas = 8,
        n_esferas_x_fila = 5;
    const float
        e = 2.5 / n_esferas_x_fila;
    agregar(glm::scale(glm::vec3(e,e,e)));
    for (unsigned i = 0; i < n_filas_esferas; i++)
    {
        NodoGrafoEscena *fila_esferas = new NodoGrafoEscena();
        fila_esferas->agregar(glm::translate(glm::vec3(3.0, 0.0, 0.0)));
        for (unsigned j = 0; j < n_esferas_x_fila; j++)
        {
            MiEsfera2 * esfera = new MiEsfera2(i,j);
            fila_esferas->agregar(glm::translate(glm::vec3(2.5, 0.0, 0.0)));
            fila_esferas->agregar(esfera);
        }
        agregar(fila_esferas);
        agregar(glm::rotate( glm::radians(float(360.0 / n_filas_esferas)), glm::vec3(0.0f, 1.0f, 0.0f)) );
    }
}

bool MiEsfera2::cuandoClick(const glm::vec3 &centro_wc)
{      
    if (tieneColor()) {
        if (leerColor() == glm::vec3(1.0,1.0,1.0))
            ponerColor({1.0,0.0,0.0});
        else
            ponerColor({1.0,1.0,1.0});
    } else
        ponerColor({1.0,0.0,0.0});
    std::cout << "Se ha seleccionado la esfera número: " << leerNombre() << std::endl;
}

MiEsfera2::MiEsfera2(int i, int j)
{
    int num_verts_per = 50;
    int nperfiles = 50;
    std::vector<glm::vec3> perfil;
    std::string cadena = std::to_string(i) + " " + std::to_string(j);
    ponerNombre(cadena);
    int identificador = (((i+j)*(i+j+1))/2) + i+1; // evitar que se repita identificador
    ponerIdentificador(identificador);
    for (int i = 0; i < num_verts_per; ++i) {
        float angulo = 2 * M_PI * i / (num_verts_per - 1);
        float x = cos(angulo);
        float y = sin(angulo);
        perfil.push_back( {x, y, 0.0});
    }
    inicializar(perfil,nperfiles);

}

Problema3_DADO::Problema3_DADO() {
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


   triangulos ={  {0,1,3}, {0,3,2}, // X-
                {4,7,5}, {4,6,7}, // X+ (+4)
                {8, 13, 9}, {8, 12, 13},
                {10, 11, 15}, {10, 15, 14},
                {16, 22, 20}, {16, 18, 22},
                {17, 21, 23}, {17, 23, 19} };

    // S --> Coordenadas horizontales (izquierda vs derecha)
    // T --> Coordenadas verticales (inferior vs superior)
    cc_tt_ver = {
        {float(1/2), float(2/3)},
        {float(1/4), float(2/3)},
        {float(1/2), float(1/3)},
        {float(1/4), float(1/3)},

        {float(1/2),float( 2/3)},
        {float(1/4), float(2/3)},
        {float(1/2), float(1/3)},
        {float(1/4), float(1/3)},

        {float(1/2),float( 2/3)},
        {float(1/4), float(2/3)},
        {float(1/2), float(1/3)},
        {float(1/4), float(1/3)},

        {float(1/2),float( 2/3)},
        {float(1/4), float(2/3)},
        {float(1/2), float(1/3)},
        {float(1/4), float(1/3)},

        {float(1/2),float( 2/3)},
        {float(1/4), float(2/3)},
        {float(1/2), float(1/3)},
        {float(1/4), float(1/3)},

        {1/2, 2/3},
        {1/4, 2/3},
        {1/2, 1/3},
        {1/4, 1/3},
    };
    
}

NodoProblemaDado::NodoProblemaDado() {
    NodoGrafoEscena * cubo = new NodoGrafoEscena();
    Textura * textura_cubo = new Textura("lata-coke.jpg");
    cubo->agregar(new Material(textura_cubo, 2.0f, 2.0f, 2.0f, 2.0f));
    cubo->agregar(new Problema3_DADO());
    agregar(cubo);
}