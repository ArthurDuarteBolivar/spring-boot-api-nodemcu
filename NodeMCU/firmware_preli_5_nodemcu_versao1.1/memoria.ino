
#include <EEPROM.h>

#define REG_VAZIO                   (char)0x3F

#define RESETADO                    0x20
#define REG_REFRESH                 10

#define REG_DISPARO_LDR             11  // guardo o valor configurado para disparo do LDR
#define REG_PORTAS_LDR              12  // {12 ao 19} guarda o estado de todos os reles, quando marcados ou não pela Luminosidade


void preparaMemoria(){
   EEPROM.begin(32);
   byte teste = getRegisterMemory(REG_REFRESH, 0);
    if(teste != RESETADO){
      Serial.println(F("Resetando Variaveis"));
      for(int x = 0; x < SIZELDR ; x ++){
        setRegisterMemory(REG_PORTAS_LDR, x ,0);
      }
       setRegisterMemory(REG_REFRESH, 0 ,RESETADO);
       setRegisterMemory(REG_DISPARO_LDR, 0 ,20);
      
    } 
}
void setRegisterMemory(int pos, int increment, byte dado){
    EEPROM.write(pos + increment, int8_t(dado));
    EEPROM.commit();
  
    if(debug){
      Serial.print("Gravando dado: ");
      Serial.println(dado);
      Serial.print("Na Posicao: ");
      Serial.println(pos+increment);
    }
}
byte getRegisterMemory(byte pos, byte increment){
   int8_t val = EEPROM.read(pos+ increment);
  return val;
}

/*
 *  Guarda as portas controladas pelo LDR
 */
void setMemoryPortasLDR(byte in, byte dado){
  setRegisterMemory(REG_PORTAS_LDR, in ,dado);
}
byte getMemoryPortasLDR(byte in)  {
  return getRegisterMemory(REG_PORTAS_LDR,in);
}
/*
 * Guarda valor do Disparo LDR
*/
void setMemoryDisparo(byte dado){
  setRegisterMemory(REG_DISPARO_LDR, 0 ,dado);
}
byte getMemoryDisparo(){
  return getRegisterMemory(REG_DISPARO_LDR,0);
}
