  /*  *****************************************************
   *   AREA DE CONFIGURAÇÃO
   *  Esta parte do código foi reservada para ajustar o comportamento
   *  do modulo junto a interface.
   *  qualquer dúvida entre em contato com o desenvolvedor.
   ********************************************************/


/*
 * Defina as informações da sua REDE Wifi atual para que 
 * o NodeMCU possa se conectar a ele.
 * 
*/
    #define STASSID "Tenda_191480"   //  Nome da REDE
    #define STAPSK  "99622575"       //  Senha de Acesso
   
 /*
    Coloque uma chave qualquer para a validação do protocolo
    de comunicação WEB.
    Esta mesma chave deverá ser configurada também na
    interface WEB de controle.
 */
    #define _KEY       "A9F5d5f47Db"
 
 /*
     Altere para LOW ou HIGH
     conforme o estado em que as portas de saídas devem
     estar quando o seu módulo de rele estiver ligado.   
     Isso dependerá do tipo de transistor utilizado PNP ou NPN
 */
    #define _ON        HIGH

/*
    Informe a porta que será feita a comunicação de Rede
*/
    #define _PORTA 8082
   
    /*
   *  Utilização dos Recursos de controle de Luminosidade
   *  Habilite somente se optar por utilizar o sensor LDR no projeto
   *  O Sensor monitora o LDR a cada minuto
   *  Caso seja disparado um evento de Ligar ou Desligar, haverá um tempo de 5 minutos   
   *  para próxima leitura evitando que fique piscando a saída, devido a variação no sensor.
   *  true -> Habilitado
   *  false -> Desabilitado
   */
   #define _LDR true

 
   /*
    *  Configure abaixo como deverão se comportar cada saída.
    *  define como
    *  PULSO ou  RETENCAO
   */
   byte comportamento_saidas[] = {
    /*Saida R1*/                      RETENCAO,
    /*Saida R2*/                      RETENCAO,
    /*Saida R3*/                      RETENCAO,
                                };

   /*
  * Define o Tempo de Pulso em Segundos que devera ser respeitado
  * quando determinada saida foi configurada no software
  * para utilizar esta opção de PULSO ao invés de RETENÇÃO
  */
  #define _tPULSO    2
  

/*
 * Defina como 'true' caso deseja habilitar o modo de cenas ao pressionar o pulsador pelo
 * tempo definido em TEMPO_PRESSED
*/
 #define PRESS_OLD true

 /*
  * Defina o tempo necessário que o pulsador deverá ser pressionado
  * para ativar a CENA configurada para ele.
  * (recomendado mínimo 2 segundos)
 */
 #define TEMPO_PRESSED  1.5  // (tempo em segundos)

 
 /*
 * Configure as Cenas que serão executadas quando pressionado cada um dos pulsadores
 * pelo tempo determinado em TEMPO_PRESSED.
 * cada posição corresponde a uma saída.
 * ex: "10x"
 *   saída R1 - "será ligada"
 *   saída R2 - "será desligada"
 *   saída R3 - "será desconsiderado"
 *   
 *   
 *   Então configure as opções abaixo, conforme deseja
 *   onde:
 *   1 - Ligado
 *   0 - Desligado
 *   x - Manter estado atual.
 *  
*/


String cena[] ={
/*CENA P1*/              "x01",
/*CENA P2*/              "111",
/*CENA P3*/              "000"
                };


 
