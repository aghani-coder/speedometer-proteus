int Motor1 = 2;
int Motor2 = 3;

int PWMControl= 6;

int PWM_Input = 0;

int PWM_Value = 0;
void setup() {
  pinMode(Motor1, OUTPUT);
  pinMode(Motor2, OUTPUT);
  pinMode(PWMControl, OUTPUT);
  pinMode(PWM_Input, INPUT);
  Serial.begin(9600);
}

void loop() {
  PWM_Value = analogRead(PWM_Input);
  PWM_Value = map(PWM_Value, 0, 1023, 0, 255);
  analogWrite(PWMControl, PWM_Value);
  
  if(Serial.available())
  {Serial.println(PWM_Value);
    char data = Serial.read();
    Serial.println(data);
    if(data == 'C'){MotorClockwise();}
    if(data == 'A'){MotorAntiClockwise();}
    if(data == 'S'){MotorStop();}
    
  }
}

void MotorAntiClockwise()
{
  digitalWrite(Motor1, HIGH);
  digitalWrite(Motor2, LOW);
}

void MotorClockwise()
{
  digitalWrite(Motor1, LOW);
  digitalWrite(Motor2, HIGH);
}

void MotorStop()
{
  digitalWrite(Motor1, HIGH);
  digitalWrite(Motor2, HIGH);
}
long getKeypadIntegerMulti()
{
  lcd.clear();
  long value = 0;                                // the number accumulator
  long keyvalue;                                     // the key pressed at current moment
  int isnum;
  Serial.println("Enter the digits,press any non-digit to end ");
  lcd.setCursor(0,0);
  lcd.print("You have typed:");
  lcd.setCursor(0,1);
  do
  {
    keyvalue = keypad.getKey();                          // input the key
    isnum = (keyvalue >= '0' && keyvalue <= '9');         // is it a digit?
    if (isnum)
    {
      lcd.print(keyvalue - '0');
      value = value * 10 + keyvalue - '0';               // accumulate the input number
    }

  } while (isnum || !keyvalue);                          // until not a digit or while no key pressed
  //
  Serial.println(" "); 
  Serial.print("Returning from funtion: "); 
  Serial.println(value);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("THE value is");
  lcd.setCursor(0,1);
  lcd.print(value);
  return value;

}//getKeypadInteger

double getRPM()
{
  //Serial.println("gone to get rpmfunction");
  //Serial.println();
  int count = 0;
  boolean countFlag = LOW;
  unsigned long currentTime = 0;
  unsigned long startTime = millis();
  while (currentTime <= sampleTime)
  {
    if (digitalRead(hallSensorPin) == HIGH){
      countFlag = HIGH;
    }
    if (digitalRead(hallSensorPin) == LOW && countFlag == HIGH){
      count++;
      countFlag=LOW;
    }
    currentTime = millis() - startTime;
  }
  
  double countRpm = 1 * count; // used a multiplier when changing the sample time
  Serial.print("THE RPM  IS ");
Serial.print(countRpm,DEC);
  countRpm*=radius*2*3.14;
  
  
 //lcd.print(countRpm);
Serial.print("THE SPEED IS ");
Serial.print(countRpm,DEC);  
 lcd.clear();
  if (countRpm > speedlim) {
   digitalWrite (relay, HIGH);
   lcd.print("ENGINE OFF");
  //Serial.println("off");
 }
  if (countRpm <= speedlim){
   digitalWrite (relay, LOW);
   lcd.print("ENGINE ON");
  //Serial.println("on");
 }  
 lcd.setCursor(0,1);
 lcd.print("speed:");
 lcd.print(countRpm,DEC);
   return countRpm;
   
}
