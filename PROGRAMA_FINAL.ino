/***************************************************************************
                                    ALTEBEN
 ***************************************************************************/

#include <LiquidCrystal.h>
#include <Stepper.h>

//dir
#define dirPin 6 

//step
#define stepPin 7 

//revoluciones del motor
#define stepsPerRevolution 600

//definimos los pines del controlador del motor
#define M0Pin 8 
#define M1Pin 9
#define M2Pin 10

// inicializamos el display y le damos los pines que vamos a usar
LiquidCrystal lcd(13, 12, 5, 4, 3, 2);

//definimos las variables a usar 
double P_atmosferica=101.3;  
double Vout;
double Vs=5.0;
double Altura;
double P;
double aux;
int i;
double P_final;

// Ajusta la medida de presión
double tolP=0.04; 


/***************************************************************************
                                    PROGRAMA
 ***************************************************************************/

void setup()
{
  //definimos que display usamos
  lcd.begin(16, 2);
  
  //paramos el cursor de donde queremos escribir (x, y)
  lcd.setCursor(5,0);
  lcd.print("ALTEBEN");
  lcd.setCursor(2,1);
  lcd.print("7mo 1era AVC");
  delay(3000);
  lcd.clear();

  //definimos los pines del controlador de motores
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(M0Pin, OUTPUT);
  pinMode(M1Pin, OUTPUT);
  pinMode(M2Pin, OUTPUT);

  
}

/***************************************************************************
                                    LOOP
 ***************************************************************************/

void loop()
{
   //Voltaje del Sensor MPX5100DP
   aux=0;
   for(i=0;i<10;i++){
    
    //lectura del pin A0 en voltaje que da el sensor y lo dividimos en 1023 bits
    aux = aux + (float(analogRead(A0))*5.0/1023.0); 
    delay(5);
   }
   Vout=aux/10.0;
  
  //Presión en Kpa según Datasheet MPX5100
  P = ( Vout - 0.04*Vs ) / (0.09 * Vs) + tolP; //kPa
  
  //Calculo de la Presion Absoluta
  P_final = P_atmosferica - P;
  
  //Altura de la aeronave en pies
  Altura = (-7999.6527*log(P_final/P_atmosferica))*3.28;  
  
  //imprimimos los datos seteando el cursor
  lcd.clear();
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
  lcd.print("FTS");

  delay(3000);
  
//Configuramos el giro del motor
  digitalWrite(M0Pin,LOW);
  digitalWrite(M1Pin,LOW);
  digitalWrite(M2Pin,LOW);
  
//Ordenamos al motor a girar en el sentido de las agujas del reloj
  digitalWrite(dirPin, HIGH);

  for (int i = 0; i < stepsPerRevolution; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }
  delay(1000);

//Ordenamos al motor a girar en el sentido contrario de las agujas del reloj
  digitalWrite(dirPin, LOW);

 
  for (int i = 0; i < stepsPerRevolution; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }
  delay(1000);
}
