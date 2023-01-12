 
 #define _START    0x3F
 #define _END      0x21
 
byte getEnd(){
  return _END;
}
byte getStart(){
  return _START;
}

void Interpretador(String *buff){
                    if(debug)Serial.println(*buff);
                    byte separador = (*buff).indexOf("&");
                    String data;
                    int tamanho;

                    if(searchData(*buff,"cod=").equals(_KEY)){
                        if(debug){
                          Serial.println(F("Comunicacao Autorizada"));
                          Serial.print(F("Central Modelo :"));
                        }
                        if(searchData(*buff,"model=").equals(_MODELO)){
                                    if(debug)Serial.println(_MODELO);
                                    data = searchData(*buff,"prot=");
                                    tamanho = data.length();
                                    if(tamanho >= 2){
                                      if(data.startsWith("STATUS")){
                                                  RequestStatus();
                                      }else if(data.startsWith(MULT_COMAND)){
                                         setComando(&data);
                                         RequestStatus();
                                         //Serial.println("Indentificou E");

                                      }else if(data[tamanho -1] == RETENCAO){
                                                  int pos = converte(data[tamanho-3],data[tamanho-2]);
                                                  if(pos >= 0){
                                                       if(!isLDR(pos))setSaida(pos,(data[tamanho-4] == '1')? _ON : _OFF);  // ON = 0 OFF = 1
                                                   }else{
                                                               Serial.println(F("***  ATENCAO *** "));
                                                               Serial.println(F("Nao foi possivel identificar Protocolo RETENCAO"));
                                                  }
                                                  RequestStatus();
                                      }else if(data[tamanho -1] == LDR){
                                                  int pos = converte(data[tamanho-3],data[tamanho-2]);
                                                  if(pos >= 0){
                                                       if(setContolledLDR(pos,(data[tamanho-4] == '1')? true : false)){ // Alterar o Status de controle pelo LDR para a posição informada.
                                                             timeLDR = 0;  // altera o valor para fazer uma nova busca
                                                             monitoraLDR();
                                                             RequestStatus();  
                                                             setMemoryPortasLDR(pos,(data[tamanho-4] == '1')? 1 : 0);       // Atualizando Memoria                                       
                                                       }else{
                                                            handleError(E_103);
                                                       }
                                                  }else{
                                                               RequestStatus();
                                                               Serial.println(F("***  ATENCAO *** "));
                                                               Serial.println(F("Nao foi possivel identificar o Protocolo [LDR]"));
                                                   }
                                                 
                                      }else if(data[tamanho -1] == DISPAROLDR && tamanho < 4){
                                        Serial.println("Indentificou D");
                                        Serial.println(data);
                                                  int pos = converte(data[tamanho-3],data[tamanho-2]);
                                                  if(pos >= 0 && pos < 100){
                                                            timeLDR = 0;  // altera o valor para fazer uma nova busca
                                                            monitoraLDR();
                                                            setCalibragemSensorLDR(pos);
                                                            setMemoryDisparo(pos); // Atualizando Memoria
                                                  }else{ 
                                                               Serial.println(F("***  ATENCAO *** "));
                                                               Serial.println(F("Nao foi possivel identificar o Protocolo [DISPARO LDR]"));
                                                   }
                                                   RequestStatus();
                                                 
                                        }
                                    }else{
                                      handleError(E_102);  
                                    }
                                      
                            
                        }else{
                          handleError(E_101);
                        }
                    }else{

                      handleError((*buff).startsWith("?")? E_104: E_100);
                    }
                    if(debug)Serial.println();
                    *buff = "";                    
}

/*
 *  Procura o valor do objeto <localiza> dentro de <prot>
 *  @return o <data> deste objeto
 *  <prot>      = "model=ABCD"
 *  <localiza>  = "prot"
 *  <data>      =  ABCD
 */
 
String searchData(String prot, String localiza){
    byte inicio = (prot).indexOf(localiza);
    byte fim    = (prot).indexOf('&',inicio);
    return prot.substring(inicio+(localiza).length() , fim);
}

int converte(char a, char b){
  char conv[3];
  conv[0] = a;
  conv[1] = b;
  return atoi(conv);
}
