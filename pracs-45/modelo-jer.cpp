// Nombre: José Antonio, Apellidos: Carmona Molina, Titulación: GIADE.
// email: jacarmona@correo.ugr.es, DNI o pasaporte: 77552812D

#include "modelo-jer.h"
#include "latapeones.h"

Portatil::Portatil(const float alpha, const float rango, const float h  ) 
:  NodoGrafoEscena() {

   rango_pen = rango;
   angulo = alpha;
   rango_pant = h;

   ponerNombre( std::string("Portátil"));

   using namespace glm;
    NodoGrafoEscena * raton = new NodoGrafoEscena();
    NodoGrafoEscena * rueda_raton = new NodoGrafoEscena();
    NodoGrafoEscena * bisagras = new NodoGrafoEscena();
    NodoGrafoEscena * pen = new NodoGrafoEscena();
    NodoGrafoEscena * base = new NodoGrafoEscena();
    NodoGrafoEscena * alfombrilla = new NodoGrafoEscena();
    NodoGrafoEscena * pantalla = new NodoGrafoEscena();

   Material * carcasa = new Material(new Textura("metal.jpg"), 0.2f, 0.2f, 0.2f, 20.0f);
   carcasa->ponerNombre("carcasa_portatil");
   Material * alfombrilla_gaming = new Material(new Textura("window-icon.jpg"), 0.2f, 0.2f, 0.8f, 20.0f);
   alfombrilla->ponerNombre("alfombrilla_gaming");
   Material * plastico = new Material(new Textura("plastico.jpg"), 0.2f, 0.2f, 0.8f, 50.0f);
   plastico->ponerNombre("plastico_raton");

   // Raton
   raton->ponerNombre("Ratón");
   raton->ponerIdentificador(1111);
   raton->agregar ( translate( vec3(3.3f,0.1f,-0.2f)) );
   raton->agregar ( scale(vec3(0.1, 0.1, 0.3)) );
   raton->agregar ( rotate(radians(90.0f), vec3(1.0f,0.0f,0.0f)) );
   raton->agregar(plastico);
   raton->agregar ( new Cilindro(12,24) );
   raton->agregar ( scale(vec3(1, 0.6, 1)) );
   raton->agregar ( new Esfera(20,20) );
   raton->agregar ( translate( vec3(0.0f,1.6f,0.0f)) );
   raton->agregar ( scale(vec3(1, 0.6, 1)) );
   raton->agregar ( new Esfera(20,20) );
   agregar(raton);


   // Rueda del ratón
   rueda_raton->ponerNombre("Rueda ratón");
   rueda_raton->ponerIdentificador(1112);
   rueda_raton->agregar ( translate( vec3(4.0f,0.1f,-0.2f)) );
   rueda_raton->agregar ( scale(vec3(0.04, 0.04, 0.04)) );
   rueda_raton->agregar ( rotate(radians(180.0f), vec3(1.0, 1.0, 0.0)));
   rueda_raton->agregar ( translate( vec3(2.0f, -18.0f, -2.0f)) );
   unsigned ind_ani_rr = rueda_raton->agregar(scale(vec3(1.0,1.0,1.0)));
   rueda_raton->agregar(carcasa);
   rueda_raton->agregar ( new Cilindro(20,20) );
   gira_rueda = rueda_raton->leerPtrMatriz(ind_ani_rr);
   agregar(rueda_raton);

   // Bisagras
   bisagras->ponerNombre("Bisagras");
   bisagras->ponerIdentificador(2222);
   bisagras->agregar ( translate( vec3(0.0f,0.0f,0.0f)) );
   bisagras->agregar ( scale(vec3(0.1, 0.1, 0.1)) );
   bisagras->agregar ( rotate(radians(90.0f), vec3(0.0f,0.0f,1.0f)) );
   bisagras->agregar ( translate( vec3(0.0f,0.0f,-15.0f)) );
   bisagras->agregar ( scale(vec3(0.45, 3, 0.45)) );
   bisagras->agregar ( translate( vec3(0.0f,-6.5f,4.5f)) );
   bisagras->agregar(carcasa);
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
   agregar(bisagras);

   // Pen
   pen->ponerNombre("Pen");
   pen->ponerIdentificador(3333);
   unsigned ind_ani_pen = pen->agregar(scale(vec3(1.0,1.0,1.0)));
   pen->agregar ( translate( vec3(-2.1f,0.0f,-1.0f)) );
   pen->agregar ( scale(vec3(0.2, 0.01, 0.05)) );
   pen->agregar ( new Cubo() );
   pen->agregar ( scale(vec3(1.4, 1.8, 1.4)) );
   pen->agregar ( translate( vec3(-0.7f,0.0f,0.0f)) );
   //pen->agregar(carcasa);
   pen->ponerColor(vec3(1.0f,0.0f,0.0f));
   pen->agregar ( new CuboColores() );
   inserta_pen = pen->leerPtrMatriz(ind_ani_pen);
   agregar(pen);


   // Base Portátil
   base->ponerNombre("Base portátil");
   base->ponerIdentificador(4444);
   base->agregar ( translate( vec3(0.0f, 0.0f, 0.0f)) );
   base->agregar ( scale(vec3(2.0, 0.04, 1.25)) );
   base->agregar(carcasa);
   base->agregar ( new CuboColores() );
   agregar(base);

   // Alfombrilla
   alfombrilla->ponerNombre("Alfombrilla");
   alfombrilla->ponerIdentificador(6666);
   alfombrilla->agregar ( rotate(radians(90.0f), vec3(0.0f,0.0f,1.0f)) );
   alfombrilla->agregar ( translate( vec3(1.0f, -3.5f, 0.0f)) );
   alfombrilla->agregar ( scale(vec3(1,1.3,1)) );
   alfombrilla->agregar(alfombrilla_gaming);
   alfombrilla->agregar ( new CuadradoPruebaTexturas() );
   agregar(alfombrilla);

   // Pantalla
   unsigned ind_ani_pan = pantalla->agregar(scale(vec3(1.0,1.0,1.0)));
   unsigned ind_ani_lpan = pantalla->agregar(scale(vec3(1.0,1.0,1.0)));
   pantalla->ponerNombre("Pantalla");
   pantalla->ponerIdentificador(5555);
   pantalla->agregar ( rotate(radians(270.0f), vec3(1.0f,0.0f,0.0f)) );
   pantalla->agregar ( translate( vec3(0.0f, 1.30f, 1.30f)) );
   pantalla->agregar ( scale(vec3(2.0, 0.04, 1.25)) );
   pantalla->agregar(carcasa);
   pantalla->agregar ( new CuboColores() );
   separa_pantalla = pantalla->leerPtrMatriz(ind_ani_pan);
   levanta_pantalla = pantalla->leerPtrMatriz(ind_ani_lpan);
   agregar(pantalla);

}

unsigned Portatil::leerNumParametros() const {
   return 3;
}

void Portatil::actualizarEstadoParametro(const unsigned iParam, const float t_sec){
   switch (iParam)
   {
   case 0:
      insertarPen(rango_pen, t_sec);
      break;
   case 1:
      separarPantalla(angulo, rango_pant, t_sec);
      break;
   case 2:
      girarRueda(angulo * 3 * t_sec);
      break;
   default:
      break;
   }
}

void Portatil::separarPantalla( const float alpha, const float rango, const float t_sec )
{
   *separa_pantalla = glm::rotate( glm::radians(-alpha), glm::vec3( 1.0, 0.0, 0.0 ));
    float movimiento = rango + rango * sin(2 * M_PI * velocidad * t_sec);
   *levanta_pantalla = glm::translate( glm::vec3( 0.0, movimiento, 0.0 ));
}

void Portatil::insertarPen( const float rango, const float t_sec )
{
   float movimiento = rango + rango * sin(2 * M_PI * velocidad * t_sec);
   *inserta_pen = glm::translate( glm::vec3( movimiento, 0, 0 ));
}

void Portatil::girarRueda( const float alpha_nuevo )
{
   *gira_rueda = glm::rotate( glm::radians(alpha_nuevo), glm::vec3( 0.0, 1.0, 0.0 ));
}
