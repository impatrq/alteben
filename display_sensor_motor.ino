/***************************************************************************
                                    ALTEBEN
 ***************************************************************************/
// include the library code:
#include <LiquidCrystal.h>
#include <Stepper.h>
// Define stepper motor connections and steps per revolution:
#define dirPin 8 //dir
#define stepPin 9 //step
#define stepsPerRevolution 200


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(13, 12, 5, 4, 3, 2);


double P_atmosferica=101.3;  
double Vout,Vs=5.0;
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


   // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);


  
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

   // Set the spinning direction clockwise:
  digitalWrite(dirPin, HIGH);

  // Spin the stepper motor 1 revolution slowly:
  for (int i = 0; i < stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }

  delay(1000);

  // Set the spinning direction counterclockwise:
  digitalWrite(dirPin, LOW);

  // Spin the stepper motor 1 revolution quickly:
  for (int i = 0; i < stepsPerRevolution; i++) {
    // These four lines result in 1 step:
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }

  delay(1000);
}
