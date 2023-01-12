byte calibra_sensor_ldr       = 30;       //  guarda o valor da luminosidade de disparo | variavel é atualizada na função prepareLDR()
#define _portLDR              A0
#define _LDR                  true


boolean saidasAtivasLDR[]   = {false,false,false};
#define SIZELDR             sizeof(saidasAtivasLDR)/sizeof(boolean)
boolean ultimoStatusLDR     = false;
int valorLDR;

const long delay_disparoLDR_prox_leitura      = 5*60;      // Tempo para a próxima Leitura após alterar o Status (em segundos)
int delay_tempo_ldr                           = 60;         // Tempo entre uma leitura e outra (em segundos)

unsigned long timeLDR;

void prepareLDR(){
  pinMode(_portLDR,INPUT);
  for(int x = 0 ; x < SIZELDR ; x++){
      saidasAtivasLDR[x] = getMemoryPortasLDR(x);
  } 
  calibra_sensor_ldr       = getMemoryDisparo();                // Atualiza valor do sensor LDR da memória
}

void monitoraLDR(){
  if(_LDR){
     if(temporizador(timeLDR)){
        valorLDR = getValLDR();
        boolean statusLDR = disparaLDR(valorLDR);
        for(int x= 0; x < SIZELDR; x++){
          if(isLDR(x)){
              if(!isPulso(x))setSaida(x,statusLDR);
          } 
        } 
        if(statusLDR != ultimoStatusLDR){
          timeLDR = millis() + (delay_disparoLDR_prox_leitura * 1000);
          ultimoStatusLDR = statusLDR;
          if(debug){
           Serial.print(F("ALTERANDO LDR, Proxima leitura em "));    
           Serial.print(delay_disparoLDR_prox_leitura);  
           Serial.println(F("(s)"));  
          }
        }else{
          timeLDR = millis() + (delay_tempo_ldr * 1000);  
                                       
        }
     } 
  }
}

void setCalibragemSensorLDR(char val){
  calibra_sensor_ldr = val;
}


/*
 * Atualiza novo Status WEB com valor real do sensor LDR
 */
int getCalibragemSensorLDR(){
  return calibra_sensor_ldr;
}

/*
 *  Captura o valor atual do Sensor LDR
 */
int getValLDR(){
   return analogRead(_portLDR);
}

String getStatusLDR(){
  String aux;
  for(int x = 0; x < SIZELDR; x++){
    aux += (saidasAtivasLDR[x] == true)? 1 : 0;
  }
  return aux;
}


boolean disparaLDR(int sensor){
  return (sensor <= map(calibra_sensor_ldr,0,99,0,1000))? _ON : !_ON;
}

/*
 *  Altera Status do Ponto para controle ou não de modo automatico (LDR)
 *  para Aplicação WEB
*/
boolean setContolledLDR(byte pos, boolean _status){
  if(isPulso(pos)){
    return false;
  }else{
    saidasAtivasLDR[pos] = _status;
    return true;
  }
}


boolean isLDR(byte pos){
  return saidasAtivasLDR[pos];
}

void alertaVisualLDR(byte pos){
  setSaida(pos,!getSaida(pos));
  delay(500);
  setSaida(pos,!getSaida(pos));
  delay(500);
  setSaida(pos,!getSaida(pos));
  delay(500);
  setSaida(pos,!getSaida(pos));
}
