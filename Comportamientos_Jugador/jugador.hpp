#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
using namespace std;
struct state {
  int fil;
  int col;
  Orientacion brujula;
};
void PonerTerrenoEnMatriz(const vector<unsigned char> &terreno, const state &st,
              vector< vector<unsigned char>> &matriz, Sensores sensores);
void TipoCasillaDondeCae(Sensores sensores, Action accion, const vector<unsigned char> &terreno, const vector<unsigned char> &superficie,bool &bikini, bool &zapatillas);

Action giro(Action accion);
void consumoDeBateria(Sensores sensores, Action accion,const vector<unsigned char> &terreno, bool &bikini, bool &zapatillas);

class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Constructor de la clase
      // Dar el valor inicial a las variables de estado
      current_state.fil = current_state.col = 99;
      current_state.brujula = norte;
      last_action = actIDLE;
      girar_derecha=false;
      bien_situado=false;
      
    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    Action giro(Action accion);
    void TipoCasillaDondeCae(Sensores sensores, Action accion, const vector<unsigned char> &terreno, const vector<unsigned char> &superficie,bool &bikini, bool &zapatillas);

  private:
  
  // Declarar aquí las variables de estado
  state current_state;
  Action last_action;
  
  bool girar_derecha, bien_situado, bikini, zapatillas;
};

#endif
