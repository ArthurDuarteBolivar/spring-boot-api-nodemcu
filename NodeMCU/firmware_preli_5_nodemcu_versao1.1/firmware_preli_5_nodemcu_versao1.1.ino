/*

******************************     Firmware Central PRELI_5, Adapatada para AppWEB   ***********************************************************************
******************************     Autor : Carlos Freitas                            ***********************************************************************
******************************     Atualizado em : 09/03/2021                            ***********************************************************************
******************************     Versão 1.1                                        ***********************************************************************
      
*/

/*
 *  Projeto Automação na Veia NODEMCU 
 *  Autor  : Carlos Freitas (carlos@autofreitas.com.br)
 *  Modulo : PRELI_5
 *   
 *  Controle seu Arduino pela WEB, de maneira simples, rápida e profissional.
 *  Acesse o endereço https://appweb.automacaohouseonline.com.br
 *  Cadastre o Modulo e ajuste suas configuração.
 *  
 *  Para configurar este sketch, utilize apenas a aba 'CONFIG'.
 *  
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

 #define _MODELO "PRELI5"
 #define RETENCAO     (char)0x52 
 #define PULSO        (char)0x50 
 #define LDR          (char)0x4C 
 #define DISPAROLDR   (char)0x44 
 #define MULT_COMAND  "E" 
 #define LIMITATOR    (char)0x2E 
 boolean debug  = false;


void setup() {
    prepare_serial();
    preparaMemoria();
    prepareLDR();    
    prepare_connection();  
    prepare_hardware();    
    limpaComandos();
    imprimeMenu();
}
void loop() {
    monitoraLDR();
    monitora_rede();
    monitora_pulsador();
    monitora_serial();
    monitoraComandos();
}
