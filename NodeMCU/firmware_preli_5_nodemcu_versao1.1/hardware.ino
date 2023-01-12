
 #define _OFF     !_ON


  byte saidas[]      = {D4,D6,D7};
  byte pulsador[]    = {D1,D2,D3};



 #define SIZE_SAIDAS     sizeof(saidas)/sizeof(byte)
 #define SIZE_PULSADOR   sizeof(pulsador)/sizeof(byte)
 boolean pressed[SIZE_PULSADOR];

 unsigned long time_pressed ;
 boolean executouCena         = false;
 
 void prepare_hardware(){
    for(int x = 0; x < SIZE_SAIDAS ; x ++){
        pinMode(saidas[x], OUTPUT);
        digitalWrite(saidas[x],_OFF);
    }
    for(int x = 0; x < SIZE_PULSADOR ; x ++){
       pinMode(pulsador[x],INPUT_PULLUP);
       pressed[x] = false;
    }
}

void setSaida(byte pos, boolean _status){
  if(pos < SIZE_SAIDAS){
    if(isPulso(pos)){
        if(_status == _ON){
            digitalWrite(saidas[pos],_ON);
              delay(_tPULSO * 1000);
            digitalWrite(saidas[pos],_OFF);
        }
    }else{
        digitalWrite(saidas[pos],_status);
    }
  }
}
boolean getSaida(byte pos){
  return digitalRead(saidas[pos]);
}

boolean isPulso(byte pos){
  return (comportamento_saidas[pos] == PULSO)? true : false;
}

/*
 * Verifica se tem alguma saida Ligada
*/
boolean isOutOFF(){
  for(int x = 0; x < SIZE_SAIDAS ; x ++){
     if(getSaida(x) == _ON)
            return false;
  }
  return true;
}

String getStatus(){
  String aux;
  for(int x = 0; x < SIZE_SAIDAS ; x ++){
    if(isLDR(x)){
       aux += (digitalRead(saidas[x]) == _ON)? 3 : 2;
    }else{
       aux += (digitalRead(saidas[x]) == _ON)? 1 : 0;
    }
  }
  return aux;
}

 void monitora_pulsador(){
    for(int x = 0; x < SIZE_PULSADOR ; x ++){
      
           if(digitalRead(pulsador[x]) == LOW && !pressed[x]){
             delay(40); 
              if(digitalRead(pulsador[x]) == LOW){
                
                    if(debug){
                      Serial.print(F("Entrada [P"));
                      Serial.print(x+1);
                      Serial.println(F("] Pressionada"));
                    }
                    pressed[x] = true;
                                        
                    if(isLDR(x)){
                       alertaVisualLDR(x);
                       Serial.println(F("MODO VISUAL LDR DISPARADO"));
                    }else{
                       if(!PRESS_OLD)setSaida(x,!getSaida(x));
                         time_pressed = millis() + (TEMPO_PRESSED*1000);  
                    }
              }
           }else{
                if(digitalRead(pulsador[x]) == HIGH && pressed[x]){
                    pressed[x] = false;
                    executouCena = false;
                     if(PRESS_OLD && !temporizador(time_pressed))setSaida(x,!getSaida(x));
                     
                     if(debug){
                       Serial.print(F("Entrada [P"));
                       Serial.print(x+1);
                       Serial.println(F("] Liberada"));
                     }
                }
                if(temporizador(time_pressed) && digitalRead(pulsador[x]) == LOW && pressed[x] && PRESS_OLD && !isLDR(x)){
                    if(!executouCena){
                      if(debug){
                        Serial.print(F("EXECUTA CENA "));
                        Serial.println(x+1);
                      }
                       executaCena(x);
                       executouCena = true;
                    }
                }
           }
     
    }
 }

 
void executaCena(byte pos){
     int _size  = (cena[pos]).length();
     for(int x = 0; x < _size ; x ++){
        if(cena[pos][x] != 'x'){
           setSaida(x,(cena[pos][x] == '1')?_ON:!_ON);
           delay(100);
        }
     }
}
