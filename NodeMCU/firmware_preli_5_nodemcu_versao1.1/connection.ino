 

boolean gravar =  false;
String buffered;


const char *ssid = STASSID;
const char *password = STAPSK;

ESP8266WebServer server(_PORTA);

/*
 *  Responsável por fazer as configurações 
 *  preparação do Ethernet
*/
void prepare_connection(){

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("Aguarde a conexão");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  
    if(debug){
        Serial.println("");
        Serial.print("Connected to ");
        Serial.println(ssid);
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    }

     server.on("/", []() {
        String params;
        if(server.args() == 3){
          params = "cod=";
          params += server.arg("cod");
          params += "&model=";
          params += server.arg("model");
          params += "&prot=";
           String prot = server.arg("prot");
           byte fim    = (prot).indexOf('!');
           params += prot.substring(0, fim);
        }
        Interpretador(&params);        
      });
      
      server.onNotFound(handleNotFound);
      server.begin();
    
}

void handleNotFound() {
  
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\n";

  server.send(404, "text/plain", message);
  
}

/*
 * Função Responsável pelo Gerenciamento de 
 * dados recebidos pela Rede
*/
void monitora_rede(){
    server.handleClient();
   // MDNS.update();
}

void RequestStatus(){
  HttpRequest();
  String json = "";
  json += "{\"status\":\"";
  json += RETENCAO;
  json += getStatus();
  json += "00";
  
  json += LDR;
  int _ldr = map(getValLDR(),0,1000,0,99);

  if(_ldr < 10)
      json += "0";
 
  json += _ldr; 
    
  json += DISPAROLDR; 
  if(getCalibragemSensorLDR() < 10)
      json += "0";
  
  json += getCalibragemSensorLDR();
  json +="\"}";
    if(debug){
      Serial.print(F("Resposta : "));
      Serial.println(json);
    }
    
    server.send(200,"text/html",json);
    
}


/*
 * Gera o cabeçalho de retorno das conexões Http
 */
void HttpRequest(){
  server.sendHeader("Access-Control-Allow-Origin","*");
}
