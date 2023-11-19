#include "grafo-escena.h"

class Portatil : public NodoGrafoEscena
{
   protected:
      glm::mat4 * separa_pantalla = nullptr,
                * levanta_pantalla = nullptr,
                * gira_rueda = nullptr,
                * inserta_pen = nullptr;
      const float velocidad = 1.2;
      float rango_pen = -1.0f;
      float angulo = 30.0f;
      float rango_pant = 1.0f;
   public:
      Portatil( const float alpha, const float rango, const float h );
      void separarPantalla( const float alpha, const float rango, const float t_sec ) ;
      void insertarPen( const float rango, const float t_sec );
      void girarRueda(const float alpha);
      virtual void actualizarEstadoParametro(const unsigned iParam, const float t_sec);
      virtual unsigned leerNumParametros() const;
};
