
#define size_comandos                   14   // Tamanho máximo de comandos que poderá ser executado.
String _comandos[size_comandos];
int comandoExecutado                  = 1;
unsigned long tempo_corrido_comandos  = 0;

byte buffer_cena                      = 100;  // quantidade máxima de caracteres em cada cena


void limpaComandos(){
  for(int x = 0 ; x < size_comandos; x ++){
    _comandos[x] = "?";
  }
  comandoExecutado = 1;
   if(debug)Serial.println(F("Comandos  Limpos"));
}

boolean isComando(){
  return (_comandos[0] == MULT_COMAND) ? true : false;  
}

void setTempoComando(unsigned long tempo){
   tempo_corrido_comandos = millis() + (tempo * 1000);
}

/*
 *  Executa Multiplos comandos
 */
void setComando(String *buf_data){
  String  data = "";
  int count = 0;
  int a;
  for(a = 0 ; a < size_comandos; a ++){
      data = "";    
      for(int x = count; x < (*buf_data).length(); x ++){
        count ++;
        if((*buf_data)[x] != LIMITATOR){
          data += (*buf_data)[x];  
        }else{
          break;  
        }
       }
       if(data.length() < 1)
         return; 
      _comandos[a] = data;
  }
}

/*
 * Função responsável por monitorar se a variavel 
 * possui comandos pendentes a executar.
 * 
*/
void monitoraComandos(){
      if(isComando() && temporizador(tempo_corrido_comandos)){
        if(comandoExecutado < size_comandos){
          if(_comandos[comandoExecutado].endsWith("S")){
             int tempo = converte('0',_comandos[comandoExecutado][0]);
            if(debug){
                  Serial.print(F("Tempo de : "));
                  Serial.println(tempo);
                }
            setTempoComando(tempo);
            comandoExecutado ++;
            return;
          }else if(!(_comandos[comandoExecutado].equals("?")) ){
              String data = "cod=";
              data += _KEY;
              data += "&model=";
              data += _MODELO;
              data += "&prot=";  
              data += _comandos[comandoExecutado];  
              Interpretador(&data);
              comandoExecutado ++;
          }else{
            limpaComandos();
          }
        }else{
         limpaComandos();
        }
      }
}

void executaCenaPulsador(int pos){
  setComando(&cena[pos]);
}
