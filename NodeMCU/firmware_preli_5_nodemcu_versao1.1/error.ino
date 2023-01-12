 enum error {
              E_100,
              E_101,
              E_102,
              E_103,
              E_104
             };


void handleError(byte error){
    HttpRequest();

      String json = "";
      json += "{\"error\":\"";
    
        switch(error){
          case E_100:
                         json +="Comunicacao nao Autorizada";
          break;
          case E_101:
                        json += "Modelo Desconhecido";
          break;
          case E_102:
                        json += "Comando nao autorizado para este modulo, consulte outros modelos no menu LOJA";
          break;
          case E_104:
                        json += "Nao suportado na ";
                        json += _MODELO;
                        
          break;
        }

         json +="\"}";
        if(debug){
          Serial.print(F("Resposta : "));
          Serial.println(json);
        }    
        server.send(200,"text/html",json);
   
}
