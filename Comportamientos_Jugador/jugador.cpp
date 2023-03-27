#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;



Action ComportamientoJugador::think(Sensores sensores){

	Action accion = actIDLE;
	
	

	cout << "Posicion: fila " << sensores.posF << " columna " << sensores.posC << " ";
	switch(sensores.sentido){
		case 0: cout << "Norte" << endl; break;
		case 1: cout << "Noreste" << endl; break;
		case 2: cout << "Este" << endl; break;
		case 3: cout << "Sureste" << endl; break;
		case 4: cout << "Sur " << endl; break;
		case 5: cout << "Suroeste" << endl; break;
		case 6: cout << "Oeste" << endl; break;
		case 7: cout << "Noroeste" << endl; break;
	}
	cout << "Terreno: ";
	for (int i=0; i<sensores.terreno.size(); i++)
		cout << sensores.terreno[i];
	cout << endl;

	cout << "Superficie: ";
	for (int i=0; i<sensores.superficie.size(); i++)
		cout << sensores.superficie[i];
	cout << endl;

	cout << "Colisión: " << sensores.colision << endl;
	cout << "Reset: " << sensores.reset << endl;
	cout << "Vida: " << sensores.vida << endl;
	cout << endl;
    

	// Determinar el efecto de la ultima accion enviada


    int a;

	
	//Actualizacion de las variables de estado
	switch(last_action)
	{
	case actFORWARD:
	     switch(current_state.brujula)
		 {
		  case norte: current_state.fil--; break;
		  case noroeste: current_state.fil--; current_state.col++; break;
		  case este: current_state.col++; break;
		  case sur: current_state.fil++;  break;
		  case sureste: current_state.fil++; current_state.col++; break;
		  case suroeste: current_state.fil++; current_state.col--; break;
		  case oeste: current_state.col--; break;
		 }
		 break;
    case actTURN_SL:
	   a = current_state.brujula;
	   a=(a+7)%8;
	   current_state.brujula = static_cast<Orientacion>(a);
	   break;
	case actTURN_SR:
	   a = current_state.brujula;
	   a=(a+1)%8;
	   current_state.brujula = static_cast<Orientacion>(a);
	   break;
	case actTURN_BL:
	// Actualizacion de girar 135 a la izquierda
	   a = current_state.brujula;
	   a=(a+5)%8;
	   current_state.brujula = static_cast<Orientacion>(a);
	break;
	case actTURN_BR:
	// Actualizacion de girar 135 a la derecha
	   a = current_state.brujula;
	   a=(a+3)%8;
	   current_state.brujula = static_cast<Orientacion>(a);
	break;
	}
	
    if(sensores.terreno[0]=='G' and !bien_situado){
		current_state.fil = sensores.posF;
		current_state.col = sensores.posC;
		current_state.brujula = sensores.sentido;
		bien_situado = true;
	}
	if(sensores.terreno[0]=='K'){
		bikini=true;
	}
	if(sensores.terreno[0]=='D'){
		zapatillas=true;
	}
	if(sensores.reset){
		bikini = false;
		zapatillas = false;
	}
	if (bien_situado){
		//mapaResultado[current_state.fil][current_state.col] = sensores.terreno[0];
		PonerTerrenoEnMatriz(sensores.terreno, current_state, mapaResultado, sensores);
	}
	//Decidir la nueva accion
	if (  (  sensores.terreno[2] == 'T' or sensores.terreno[2] == 'S' or 
	        sensores.terreno[2]== 'G') and sensores.superficie[2] == '_'){
				accion = actFORWARD;
			
	}else if (!girar_derecha){
		accion = actTURN_SL;
		girar_derecha = (rand()%2==0);
	}else{
		accion = actTURN_SR;
		girar_derecha = (rand()%2==0);
	}
	
    TipoCasillaDondeCae(sensores, accion, sensores.terreno, sensores.superficie, bikini, zapatillas);

   //Recordar la ultima accion
	last_action = accion;
	return accion;
}
void PonerTerrenoEnMatriz(const vector<unsigned char> &terreno, const state &st, vector< vector<unsigned char>> &matriz, Sensores sensores){
				  //matriz[st.fil][st.col] = terreno[0];
	//{norte, noreste, este, sureste, sur, suroeste, oeste, noroeste};

	switch(sensores.sentido){
		case norte:
		matriz[st.fil][st.col] = terreno[0];
		matriz[st.fil-1][st.col-1] = terreno[1];
		matriz[st.fil-1][st.col] = terreno[2];
		matriz[st.fil-1][st.col+1] = terreno[3];
		matriz[st.fil-2][st.col-2] = terreno[4];
		matriz[st.fil-2][st.col-1] = terreno[5];
		matriz[st.fil-2][st.col] = terreno[6];
		matriz[st.fil-2][st.col+1] = terreno[7];
		matriz[st.fil-2][st.col+2] = terreno[8];
		matriz[st.fil-3][st.col-3] = terreno[9];
		matriz[st.fil-3][st.col-2] = terreno[10];
		matriz[st.fil-3][st.col-1] = terreno[11];
		matriz[st.fil-3][st.col] = terreno[12];
		matriz[st.fil-3][st.col+1] = terreno[13];
		matriz[st.fil-3][st.col+2] = terreno[14];
		matriz[st.fil-3][st.col+3] = terreno[15];
		break;
		case noreste:
		matriz[st.fil][st.col] = terreno[0];
		matriz[st.fil-1][st.col] = terreno[1];
		matriz[st.fil-1][st.col-1] = terreno[2];
		matriz[st.fil][st.col-1] = terreno[3];
		matriz[st.fil-2][st.col] = terreno[4];
		matriz[st.fil-2][st.col-1] = terreno[5];
		matriz[st.fil-2][st.col-2] = terreno[6];
		matriz[st.fil-1][st.col-2] = terreno[7];
		matriz[st.fil][st.col-2] = terreno[8];
		matriz[st.fil-3][st.col] = terreno[9];
		matriz[st.fil-3][st.col-1] = terreno[10];
		matriz[st.fil-3][st.col-2] = terreno[11];
		matriz[st.fil-3][st.col-3] = terreno[12];
		matriz[st.fil-2][st.col-3] = terreno[13];
		matriz[st.fil-1][st.col-3] = terreno[14];
		matriz[st.fil][st.col-3] = terreno[15];
		break;
		case este:
		matriz[st.fil][st.col] = terreno[0];
		matriz[st.fil-1][st.col+1] = terreno[1];
		matriz[st.fil][st.col+1] = terreno[2];
		matriz[st.fil+1][st.col+1] = terreno[3];
		matriz[st.fil-2][st.col+2] = terreno[4];
		matriz[st.fil-1][st.col+2] = terreno[5];
		matriz[st.fil][st.col+2] = terreno[6];
		matriz[st.fil+1][st.col+2] = terreno[7];
		matriz[st.fil+2][st.col-2] = terreno[8];
		matriz[st.fil-3][st.col+3] = terreno[9];
		matriz[st.fil-2][st.col+3] = terreno[10];
		matriz[st.fil-1][st.col+3] = terreno[11];
		matriz[st.fil][st.col+3] = terreno[12];
		matriz[st.fil+1][st.col+3] = terreno[13];
		matriz[st.fil+2][st.col+3] = terreno[14];
		matriz[st.fil+3][st.col+3] = terreno[15];
		break;
		case sureste:
		matriz[st.fil][st.col] = terreno[0];
		matriz[st.fil+1][st.col] = terreno[1];
		matriz[st.fil+1][st.col-1] = terreno[2];
		matriz[st.fil][st.col-1] = terreno[3];
		matriz[st.fil+2][st.col] = terreno[4];
		matriz[st.fil+2][st.col-1] = terreno[5];
		matriz[st.fil+2][st.col-2] = terreno[6];
		matriz[st.fil+1][st.col-2] = terreno[7];
		matriz[st.fil][st.col-2] = terreno[8];
		matriz[st.fil+3][st.col] = terreno[9];
		matriz[st.fil+3][st.col-1] = terreno[10];
		matriz[st.fil+3][st.col-2] = terreno[11];
		matriz[st.fil+3][st.col-3] = terreno[12];
		matriz[st.fil+2][st.col-3] = terreno[13];
		matriz[st.fil+1][st.col-3] = terreno[14];
		matriz[st.fil][st.col-3] = terreno[15];
		break;
		case sur:
		matriz[st.fil][st.col] = terreno[0];
		matriz[st.fil+1][st.col+1] = terreno[1];
		matriz[st.fil+1][st.col] = terreno[2];
		matriz[st.fil+1][st.col-1] = terreno[3];
		matriz[st.fil+2][st.col+2] = terreno[4];
		matriz[st.fil+2][st.col+1] = terreno[5];
		matriz[st.fil+2][st.col] = terreno[6];
		matriz[st.fil+2][st.col-1] = terreno[7];
		matriz[st.fil+2][st.col-2] = terreno[8];
		matriz[st.fil+3][st.col+3] = terreno[9];
		matriz[st.fil+3][st.col+2] = terreno[10];
		matriz[st.fil+3][st.col+1] = terreno[11];
		matriz[st.fil+3][st.col] = terreno[12];
		matriz[st.fil+3][st.col-1] = terreno[13];
		matriz[st.fil+3][st.col-2] = terreno[14];
		matriz[st.fil+3][st.col-3] = terreno[15];
		break;
		case suroeste:
        matriz[st.fil][st.col] = terreno[0];
		matriz[st.fil+1][st.col] = terreno[1];
		matriz[st.fil+1][st.col+1] = terreno[2];
		matriz[st.fil][st.col+1] = terreno[3];
		matriz[st.fil+2][st.col] = terreno[4];
		matriz[st.fil+2][st.col+1] = terreno[5];
		matriz[st.fil+2][st.col+2] = terreno[6];
		matriz[st.fil+1][st.col+2] = terreno[7];
		matriz[st.fil][st.col+2] = terreno[8];
		matriz[st.fil+3][st.col] = terreno[9];
		matriz[st.fil+3][st.col+1] = terreno[10];
		matriz[st.fil+3][st.col+2] = terreno[11];
		matriz[st.fil+3][st.col+3] = terreno[12];
		matriz[st.fil+2][st.col+3] = terreno[13];
		matriz[st.fil+1][st.col+3] = terreno[14];
		matriz[st.fil][st.col+3] = terreno[15];

		break;
		case oeste:
		
		matriz[st.fil][st.col] = terreno[0];
	    matriz[st.fil+1][st.col-1] = terreno[1];
		matriz[st.fil][st.col-1] = terreno[2];
		matriz[st.fil-1][st.col-1] = terreno[3];
		matriz[st.fil+2][st.col-2] = terreno[4];
		matriz[st.fil+1][st.col-2] = terreno[5];
		matriz[st.fil][st.col-2] = terreno[6];
		matriz[st.fil-1][st.col-2] = terreno[7];
		matriz[st.fil-2][st.col-2] = terreno[8];
		matriz[st.fil+3][st.col-3] = terreno[9];
		matriz[st.fil+2][st.col-3] = terreno[10];
		matriz[st.fil+1][st.col-3] = terreno[11];
		matriz[st.fil][st.col-3] = terreno[12];
		matriz[st.fil-1][st.col-3] = terreno[13];
		matriz[st.fil-2][st.col-3] = terreno[14];
		matriz[st.fil-3][st.col-3] = terreno[15];
		break;
		case noroeste:
		matriz[st.fil][st.col] = terreno[0];
		matriz[st.fil-1][st.col] = terreno[1];
		matriz[st.fil-1][st.col+1] = terreno[2];
		matriz[st.fil][st.col+1] = terreno[3];
		matriz[st.fil-2][st.col] = terreno[4];
		matriz[st.fil-2][st.col+1] = terreno[5];
		matriz[st.fil-2][st.col+2] = terreno[6];
		matriz[st.fil-1][st.col+2] = terreno[7];
		matriz[st.fil][st.col+2] = terreno[8];
		matriz[st.fil-3][st.col] = terreno[9];
		matriz[st.fil-3][st.col+1] = terreno[10];
		matriz[st.fil-3][st.col+2] = terreno[11];
		matriz[st.fil-3][st.col+3] = terreno[12];
		matriz[st.fil-2][st.col+3] = terreno[13];
		matriz[st.fil-1][st.col+3] = terreno[14];
		matriz[st.fil][st.col+3] = terreno[15];
		break;

	}
			  }
int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
Action ComportamientoJugador:: giro(Action accion){
	if(!girar_derecha){
		accion = actTURN_SL;
		girar_derecha = (rand()%2==0);
	}else{
		accion = actTURN_SR;
		girar_derecha = (rand()%2==0);
	}
	return accion;
}
void ComportamientoJugador::TipoCasillaDondeCae(Sensores sensores, Action accion, const vector<unsigned char> &terreno, const vector<unsigned char> &superficie, bool &bikini, bool &zapatillas){
	if((superficie[2]=='_')){ //Si la casilla está desocupada
		switch(terreno[2]){
			case 'A': //Agua
			if(bikini){
				accion = actFORWARD;
			}else{
				if(terreno[0]!= 'A'){
					accion = giro(accion);
				}else{
					accion = actFORWARD;
				}
			}
			break;
			case 'P': //Precipio
			accion = giro(accion);
			break;
			case 'S': //Suelo
			accion = actFORWARD;
			break;
			case 'T': //Arena
			accion = actFORWARD;
			break;
			case 'M': // Muro
			accion = giro(accion);
			break;
			case 'G': //Posicionamiento
			accion = actFORWARD;
			break;
			case 'B': //Bosque
			if(zapatillas){
				accion = actFORWARD;
			}else if( terreno[6] != 'A' && terreno[6] != 'P' && terreno[6] != 'M'){
				accion = actFORWARD;
			}else{
				accion = actFORWARD;
			}
			break;
			case 'K': // Bikini
			accion = actFORWARD;
			break;
			case 'D': //Zapatillas
			accion = actFORWARD;
			break;
			case 'X': //Recarga
			accion = actFORWARD;
			break;

		}
	}else{
		accion= giro(accion);
	}
}
void consumoDeBateria(Sensores sensores, Action accion,const vector<unsigned char> &terreno, bool &bikini, bool &zapatillas){
   //Funcion para tener en cuenta la cantidad de bateria que resta cada casilla
   switch(accion){
	   case actFORWARD:
	   if(terreno[2]== 'A' ){
		   if(bikini){
			   sensores.bateria = sensores.bateria -10;
		   }else{
		       sensores.bateria = sensores.bateria - 200;
		   }
		   
	   }else if(terreno[2]== 'B'){
		   if(zapatillas){
			   sensores.bateria = sensores.bateria -15;
		   }else{
			   sensores.bateria = sensores.bateria -100;
		   }
	   }else if(terreno[2]=='T'){
		   sensores.bateria = sensores.bateria -2;
	   }else{
		   sensores.bateria = sensores.bateria -1;
	   }
	   break;
	   case actTURN_SL:
	   if(terreno[2]== 'A' ){
		   if(bikini){
			   sensores.bateria = sensores.bateria -5;
		   }else{
			   sensores.bateria = sensores.bateria -500;
		   }
	   }else if(terreno[2]== 'B'){
		   if(zapatillas){
			   sensores.bateria = sensores.bateria -1;
		   }else{
			   sensores.bateria = sensores.bateria -3;
		   }
	   }else if(terreno[2]=='T'){
		   sensores.bateria = sensores.bateria -2;
	   }else{
		   sensores.bateria = sensores.bateria -1;
	   }
	   break;
	   case actTURN_SR:
	   if(terreno[2]== 'A' ){
		   if(bikini){
			   sensores.bateria = sensores.bateria -5;
		   }else{
			   sensores.bateria = sensores.bateria -500;
		   }
	   }else if(terreno[2]== 'B'){
		   if(zapatillas){
			   sensores.bateria = sensores.bateria -1;
		   }else{
			   sensores.bateria = sensores.bateria -3;
		   }
	   }else if(terreno[2]=='T'){
		   sensores.bateria = sensores.bateria -2;
	   }else{
		   sensores.bateria = sensores.bateria -1;
	   }
	   break;
	   case actTURN_BL:
	   if(terreno[2]== 'A' ){
		   if(bikini){
			   sensores.bateria = sensores.bateria -5;
		   }else{
			   sensores.bateria = sensores.bateria -50;
		   }
	   }else if(terreno[2]== 'B'){
		   if(zapatillas){
			   sensores.bateria = sensores.bateria -1;
		   }else{
			   sensores.bateria = sensores.bateria -3;
		   }
	   }else if(terreno[2]=='T'){
		   sensores.bateria = sensores.bateria -2;
	   }else{
		   sensores.bateria = sensores.bateria -1;
	   }
	   break;
	   case actTURN_BR:
	   if(terreno[2]== 'A' ){
		   if(bikini){
			   sensores.bateria = sensores.bateria -5;
		   }else{
			   sensores.bateria = sensores.bateria -50;
		   }
	   }else if(terreno[2]== 'B'){
		   if(zapatillas){
			   sensores.bateria = sensores.bateria -1;
		   }else{
			   sensores.bateria = sensores.bateria -3;
		   }
	   }else if(terreno[2]=='T'){
           sensores.bateria = sensores.bateria -2;
	   }else{
		   sensores.bateria = sensores.bateria -1;
	   }
	   break;

   }
}

//Crear funcion para el posicionamiento en caso de que los sensores de sentido no funcionen!! Punto 3 del guion.


