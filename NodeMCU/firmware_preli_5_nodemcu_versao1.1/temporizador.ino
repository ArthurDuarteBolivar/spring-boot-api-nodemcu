

boolean temporizador(unsigned long time){
    return (millis() > time) ? true : false;
}
