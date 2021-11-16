/***************************************************************************
                                    ALTEBEN
 ***************************************************************************/

#include <LiquidCrystal.h>
#include <Stepper.h>
#define dirPin 6 //dir
#define stepPin 7 //step
#define stepsPerRevolution 600
#define M0Pin 8
#define M1Pin 9
#define M2Pin 10

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(13, 12, 5, 4, 3, 2);


double P_atmosferica=101.3;  
double Vout;
double Vs=5.0;
double Altura;
double P;
double aux;
double tolP=0.04; // Ajusta la medida de presión
int i;
double P_final;

void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setCursor(5,0);
  lcd.print("ALTEBEN");
  lcd.setCursor(2,1);
  lcd.print("7mo 1era AVC");
  delay(3000);
  lcd.clear();

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(M0Pin, OUTPUT);
  pinMode(M1Pin, OUTPUT);
  pinMode(M2Pin, OUTPUT);

  
}
void loop()
{
   //Voltaje del Sensor MPC5010DP
   aux=0;
   for(i=0;i<10;i++){
    aux = aux + (float(analogRead(A0))*5.0/1023.0); //v
    delay(5);
   }
   Vout=aux/10.0;
  
  //Presión en Kpa según Datasheet MPX5100
  P = ( Vout - 0.04*Vs ) / (0.09 * Vs) + tolP; //kPa
  //P = Vout/Vs/0.009 - 0.04;
  //Calculo de la Presion Absoluta
  P_final = P_atmosferica - P;
  Altura = (-7999.6527*log(P_final/P_atmosferica))*3.28;  //Altura de la aeronave
  //*lcd.print("\n\nVoltaje:");
  //lcd.puts(Vout);
  //lcd.println(" v"); 


  lcd.setCursor(0,0);
  lcd.print("Presion: ");

  lcd.setCursor(8,0);
  lcd.print(P_final);

  lcd.setCursor(13,0);
  lcd.print("kPa");

  lcd.setCursor(0,1);
  lcd.print("Altura: ");

  lcd.setCursor(7,1);
  lcd.print(Altura);
  lcd.print("mts");

  delay(3000);

  digitalWrite(M0Pin,LOW);
  digitalWrite(M1Pin,LOW);
  digitalWrite(M2Pin,LOW);
  

  digitalWrite(dirPin, HIGH);

  for (int i = 0; i < stepsPerRevolution; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }

  delay(1000);

  
  digitalWrite(dirPin, LOW);

 
  for (int i = 0; i < stepsPerRevolution; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }

  delay(1000);
  
}
