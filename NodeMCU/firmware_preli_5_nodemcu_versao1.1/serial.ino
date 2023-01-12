#define  START_SERIAL  '@'
#define  END_SERIAL    '>'
#define  VERSAO        "2.2"

#define STATUS  "STATUS"


void prepare_serial(){
   Serial.begin(9600);
}

void imprimeMenu(){
   Serial.println(F("********************************************"));
   Serial.println(F("****** COMANDOS SERIAIS DE CONTROLE ********"));
   Serial.println(F("********************************************"));
   Serial.println(F("@STATUS>     Mostra o Status do Sistema"));
   Serial.println(F("@DEBUGON>    Ativa o Modo Debug"));
   Serial.println(F("@DEBUGOFF>   Desativa o modo de Debug"));
   Serial.println(F("@REFRESH>    Tenta se reconectar a rede"));
   Serial.println(F("@RESTART>    Reinicia Sistema"));
   Serial.println(F("@CENAS>      Mostra as Cenas configuradas"));
   Serial.println(F("@RESET>      Volta as Configuracoes de Fabrica"));
   Serial.println(F("********************************************"));

}

void monitora_serial(){
  escutaSerial();
}

void escutaSerial(){
   if(Serial.available() > 0){
         delay(50);
         while(Serial.available() > 0){
                   delay(10);
                   char c = toupper(Serial.read());
                    if( c == END_SERIAL){
                                gravar = false;
                                InterpretaSerial(&buffered);
                                break;
                    }
                     if(gravar){
                        buffered += c;
                        if(buffered.length() > 50){
                                gravar = false;
                                buffered = "";
                                break;
                        }
                    }
                    if( c == START_SERIAL){
                          gravar = true;
                    }
        }
               
   }
}
void InterpretaSerial(String *buff){
    if((*buff).startsWith(STATUS)){
        Serial.println(F("******************************************"));
        Serial.println(F("***********  STATUS DO MODULO  ***********"));
        Serial.println(F("******************************************"));
        Serial.print(F("MODELO     : "));Serial.println(_MODELO);
        Serial.print(F("VERSAO     : "));Serial.println(VERSAO);
        Serial.print(F("IP         : "));Serial.println(WiFi.localIP());
        Serial.print(F("PORTA      : "));Serial.println(_PORTA);
        Serial.print(F("KEY        : "));Serial.println(_KEY);
        Serial.print(F("HIGH       : "));Serial.println(_ON);
        Serial.print(F("SAIDAS     : {"));
        for(int x = 0; x < SIZE_SAIDAS ; x ++){
          Serial.print(F("R"));
          Serial.print(x+1);
          Serial.print(F("["));
          Serial.print(digitalRead(saidas[x]));
          Serial.print(F("]"));
          if(x < (SIZE_SAIDAS -1))Serial.print(F(","));
        }
        Serial.println(F("}"));

        
        Serial.print(F("TIPO       : {"));
        for(int x = 0; x < SIZE_SAIDAS ; x ++){
          Serial.print(F("R"));
          Serial.print(x+1);
          Serial.print(F("["));
          isPulso(x)? Serial.print(F("P")):Serial.print(F("R"));
          Serial.print(F("]"));
          if(x < (SIZE_SAIDAS -1))Serial.print(F(","));
        }
        Serial.println(F("}"));

        Serial.print(F("PRESSOLD   : "));PRESS_OLD ? Serial.println(F("ATIVADO")) : Serial.println(F("DESATIVADO"));
        Serial.print(F("T_PRESSED  : ")); Serial.print(TEMPO_PRESSED);Serial.println(F(" segundos"));
        
        Serial.print(F("PULSOS     : {"));
        for(int x = 0; x < SIZE_PULSADOR ; x ++){
            Serial.print(F("P"));
            Serial.print(x+1);
            Serial.print(F("["));
            Serial.print(digitalRead(pulsador[x]));
            Serial.print(F("]"));
           if(x < (SIZE_PULSADOR -1))Serial.print(F(","));
        }
        Serial.println(F("}"));
        
        Serial.print(F("T_PULSO    : "));Serial.print(_tPULSO);Serial.println(F(" segundos"));
        Serial.print(F("LDR     (%): ")); _LDR ? Serial.println(map(valorLDR,0,1000,0,100)) : Serial.println(F(" DESATIVADO"));
        Serial.print(F("DIS_LDR (%): "));
        //Serial.println(converteMinLDR());
        Serial.println(getCalibragemSensorLDR());

        Serial.print(F("P_LDR      : {"));
        for(int x = 0; x < SIZELDR ; x ++){
            Serial.print(F("R"));
            Serial.print(x+1);
            Serial.print(F("["));
            Serial.print(isLDR(x));
            Serial.print(F("]"));
           if(x < (SIZELDR -1))Serial.print(F(","));
        }
        Serial.println(F("}"));
        
        Serial.print(F("DEBUG      : ")); debug ? Serial.println("ATIVADO"):Serial.println("DESATIVADO");
        Serial.println(F("******************************************"));
    }else if((*buff).startsWith(F("DEBUGON"))){
        Serial.println(F("DEBUG   : ATIVADO"));
        debug = true;
    }else if((*buff).startsWith(F("DEBUGOFF"))){
        Serial.println(F("DEBUG   : DESATIVADO"));
        debug = false;
    }else if((*buff).startsWith(F("REFRESH"))){
        Serial.println(F("REDE    : REFRESH"));
         prepare_connection();
    }else if((*buff).startsWith(F("RESTART"))){
        Serial.println(F("SISTEMA    : RESTART APOS 8s"));
        while(1);
    }else if((*buff).startsWith(F("CENAS"))){
      Serial.println(F("******************************************"));
        Serial.println(F("CONFIGURACOES DE CENAS"));

      for(int x = 0; x < SIZE_SAIDAS ; x ++){
            Serial.print(F("CENA "));
            Serial.print(x+1);
            Serial.print(F("  : {"));
            Serial.print(cena[x]);
            Serial.println(F("}"));
        }
        Serial.println(F("******************************************"));
        
    }else if((*buff).startsWith(F("RESET"))){
      setRegisterMemory(REG_REFRESH, 0 ,REG_VAZIO);
      Serial.println(F("Retornando as configuracoes de Fabrica"));
      Serial.println(F("SISTEMA    : RESTART APOS 8s"));
       while(1);
    }
    *buff = "";
}
