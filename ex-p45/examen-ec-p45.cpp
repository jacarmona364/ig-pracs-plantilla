// Nombre: José Antonio, Apellidos: Carmona Molina, Titulación: GIADE.
// email: jacarmona@correo.ugr.es, DNI o pasaporte: 77552812D

#include "examen-ec-p45.h"

MallaP4::MallaP4()
:  MallaInd( "MallaP4" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, -1.0 },
         { -1.0, -1.0, -1.0 },
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, -1.0, +1.0 },
         { -1.0, -1.0, +1.0 },
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, -1.0, +1.0 },
         { -1.0, -1.0, +1.0 },
         { -1.0, +1.0, +1.0 }, // 3
         { -1.0, +1.0, +1.0 },
         { -1.0, +1.0, +1.0 },
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, -1.0 },
         { +1.0, -1.0, -1.0 },
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, -1.0, +1.0 },
         { +1.0, -1.0, +1.0 },
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, -1.0 },
         { +1.0, +1.0, -1.0 },
         { +1.0, +1.0, +1.0 }, // 7
         { +1.0, +1.0, +1.0 },
         { +1.0, +1.0, +1.0 },
         { +1.0, +1.75, 0 }, //8
         { +1.0, +1.75, 0 },
         { +1.0, +1.75, 0 },
         { -1.0, +1.75, 0 }, //9
         { -1.0, +1.75, 0 },
         { -1.0, +1.75, 0 },
      } ;


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

      /* cc_tt_ver = 
      {  {0.0, 1.0},     // 1 
         {1.0, 1.0},     // 4 
         {1.0, 0.0},     // 6 
         
         {1.0, 1.0},     // 1 
         {0.0, 1.0},     // 2
         {1.0, 1.0},     // 6
         
         {0.0, 0.0},     // 1 
         {1.0, 0.0},     // 4
         {1.0, 0.0},     // 5  

         {1.0, 0.0},     // 1
         {0.0, 0.0},     // 2 
         {0.0, 0.0},     // 5

         {1.0, 1.0},     // 3
         {0.0, 1.0},     // 4   
         {0.0, 0.0},     // 6

         {1.0, 1.0},     // 2  
         {0.0, 1.0},     // 3
         {0.0, 1.0},     // 6

         {1.0, 0.0},     // 3 
         {0.0, 0.0},     // 4 
         {1.0, 1.0},     // 5
         
         {1.0, 0.0},     // 2 
         {0.0, 0.0},     // 3 
         {0.0, 1.0},     // 5  
      }; */

   calcularNormales();
}

class NodoP4 : public NodoGrafoEscena {
private:
    NodoGrafoEscena * nodoP4 = new NodoGrafoEscena();
    int identificador = 1;
    unsigned int ind_casa = 0;
    glm::mat4 * nuevaTransformacion = nullptr;
    float rotacionY; // Distancia arotar en el eje Y al hacer clic
    int NUM_PARAM = 1;

public:
    NodoP4() {
        ponerIdentificador(identificador);        
            ponerNombre("NodoP4");
            agregar(new Material(new Textura("ventanas-tejado-2048x1024.jpg"), 0.6f, 0.8f, 0.1f, 15.0f));
            agregar(new MallaP4);
    }

/*     NodoGrafoEscena * MallaP4() {
        return nodoP4;
    } */

    void movimiento() {
        *nuevaTransformacion = glm::rotate( glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
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
        // Obtener la matriz de transformación actual y aplicar la rotación en Y
        std::cout << "Se ha seleccionado la casa número: " << leerIdentificador() << std::endl;
        nuevaTransformacion = leerPtrMatriz(ind_casa);
        actualizarEstado(ind_casa);
        return true;
    }
};

NodoUrbaP5::NodoUrbaP5(unsigned int n)
{
    
        NodoGrafoEscena *fila_casas = new NodoGrafoEscena();
        for (unsigned j = 0; j < n; j++)
        {
            NodoP4 * casa = new NodoP4();
            fila_casas->agregar(glm::translate(glm::vec3(2.0, 0.0, 0.0)));
            fila_casas->agregar(casa);
        }
        agregar(fila_casas); 
}