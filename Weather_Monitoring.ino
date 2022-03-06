 #include <SoftwareSerial.h>
 #include "DHT.h"

 #define DHTPIN 7     // Digital pin connected to the DHT sensor
 #define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial mySerial(9, 10);

 int r=0;
 float l=0;
 float h=0;
 float t=0;
 
void setup()
{
  dht.begin();
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);

  pinMode(7, INPUT);
  pinMode(A2, INPUT);
  pinMode(A5, INPUT);
  pinMode(4, OUTPUT);
}

void loop()
{
 delay(2000);
 r=analogRead(A5);
 l=analogRead(A2);
 h = dht.readHumidity();
 t = dht.readTemperature();
 Serial.print("Rain");
 Serial.println(r);
 Serial.print("Light");
 Serial.println(l);
 Serial.print("Temperature");
 Serial.println(t);
 Serial.print("Humdity");
 Serial.println(h);
 
 SendMessage();
      
 if (mySerial.available()>0)
   Serial.write(mySerial.read());
}


 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+918848944715\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.print("rain");// The SMS text you want to send
  mySerial.println(r);// The SMS text you want to send
  mySerial.print("Humidity");
  mySerial.println(h);
  mySerial.print("Temperature");
  mySerial.println(t);
  mySerial.print("Light Intensity");
  mySerial.println(l);
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(10000);
}
