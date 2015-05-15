//Libreria para comunicaciones seriales
#include <SPI.h>
//Libreria para tarjetas SD
#include <SD.h>
//Constante CS de conexion del modulo SD
const int chipSelect = 53;
File myFile;
void setup(){
  //Establecemos el pin 48 como salida 
  pinMode(48, OUTPUT);
  //Establecemos la velocidad de conexion serial
  Serial.begin(9600);
  //Establecemos el pin 53 como salida
  pinMode(53, OUTPUT);
  //Limpiamos el puerto serial de datos
  Serial.flush();
  //Esperamos 5 milisegundos
  delay(500);
 
  
  
}

void loop(){

  // Esperamos ha recibir datos a traves del puerto serie (Bluetooth)
  if (Serial.available()){
    
    //Leemos el comando de entrada
    String comando = Serial.readString();
    //Limpiamos el puerto serie
    Serial.flush();
   
   //Verificamos el estado de configuración del Arduino
    if (comando.equals("inicio")){
      
      //Verifica si hay datos de configuración guardados en la tarjeta SD
      verificarEstado();
      //tarjeta();
      Serial.flush();
      digitalWrite(48,HIGH);
      //Serial.println('on');
      delay(1000);
      digitalWrite(48,LOW);
      
    }
   
    if(comando.startsWith("write_user")){ 
      escribirUsuario(comando.substring(11));
      Serial.flush();
      digitalWrite(48,HIGH);
      //Serial.println('on');
      delay(1000);
      digitalWrite(48,LOW);
    }
    
  }
}

//Metod que verifica si hay datos de configuración guardados en el arduino
void verificarEstado(){
  String estado="";
  if (!SD.begin(53)) {
    estado="error_t";
  }else if (SD.exists("config.txt")) {
    estado="configurado";
  }else{
    estado="vacio";
  }
  
  //Imprime el estado 
  Serial.println(estado);
}

void escribirUsuario(String user){
  String estadoEscritura="";
  File dataFile=SD.open("config.txt",FILE_WRITE);
  
  if(dataFile){
    dataFile.println(user);
    dataFile.close();
    estadoEscritura="ok";
  }else{
     estadoEscritura="error_w";
  }
  Serial.println(estadoEscritura);
}

void tarjeta(){
  String est="";
  myFile=SD.open("config.txt");
  if(myFile.available()){
    est="configurado";
  }else{
    est="vacio";
  }
  myFile.close();
  Serial.println(est);
}
