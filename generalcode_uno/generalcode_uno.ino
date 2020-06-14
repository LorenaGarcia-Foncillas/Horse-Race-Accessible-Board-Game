void power(bool power); 

//one player 
const int buttonPin1 = 4; 
const int buttonPin2 = 12; 
const int ledPin1 = 6; 
const int ledPin2 = 9; 
const int motor = 5; 

const int pintoMega = 13; 

const int signalmega = 10; 

int x = 0;

int lastbuttonstate1 = 0; 
int lastbuttonstate2 = 0;

int startgame = 0; 

static int lapCount = 0; 

void setup() {
  Serial.begin(9600); 
  
  //one player 
  pinMode (buttonPin1, INPUT); 
  pinMode (buttonPin2, INPUT); 
  pinMode (ledPin1, OUTPUT); 
  pinMode (ledPin2, OUTPUT); 
  pinMode (motor, OUTPUT); 

  pinMode(pintoMega, OUTPUT); 

  pinMode(signalmega, INPUT); 

  attachInterrupt(digitalPinToInterrupt(2),changeLap,RISING);
}

void loop() { //this should run until one round is completed 

 while(digitalRead(signalmega)==HIGH)
  { 
  if (x==0) //to get lapcount and startgame once 
  {
    lapCount=0; 
    startgame = millis();
    x++; 
  }
   
  if(lapCount == 0)
  {
    lap1();
  }
  else if(lapCount == 1)
  {
    lap2();
  }
  else if(lapCount == 2)
  {
    analogWrite(motor, 0);
    digitalWrite(pintoMega, HIGH); 
  }
  }
}

void changeLap()
{
 static unsigned long last_interrupt_time = 0; // static var only initialises the first time the function is called 
 unsigned long interrupt_time = millis();
 // If interrupts come faster than 200ms, assume it's a bounce and ignore
 if ((interrupt_time - last_interrupt_time > 200)&&(interrupt_time - startgame > 10000)) //ignoring the first magnet detection at the beginning of the game 
 {
     lapCount++;
 }
 last_interrupt_time = interrupt_time;
}



void lap1()
{
  int buttonState1 = 0; 
  int buttonState2 = 0; 

  //int buttonstate1_player2 = 0; 
  //int buttonstate2_player2 = 0; 
  
  int number = random (1,3); //genrates 1 or 2 randomly => button to be pressed
  //int number2 = random(1,3); 

  delay(500); 

  digitalWrite(ledPin1, LOW);
  
  digitalWrite(ledPin2, LOW);

  delay(600); 
 
  //light a random LED
  
  if (number == 1)
    digitalWrite(ledPin1, HIGH); 
  
  else if (number == 2)
    digitalWrite(ledPin2, HIGH);
 
  unsigned long starttime = millis(); 
  
  while (millis()-starttime < 3500) //user has 3.5s to press the button
  {
    buttonState1 = digitalRead(buttonPin1); //get value from pin where b1 connected 
    buttonState2 = digitalRead(buttonPin2);

    if ((buttonState1 == HIGH) || (buttonState2 == HIGH)) //when the button is pressed => move on (don't wait for all 3.5s)
      break; 
  }

  //error check & function call 
 if ((buttonState1 == HIGH && number != 1)||(buttonState1 == LOW && number == 1)) { //if user pressed on wrong button
  power(false);
 }

 else if ((buttonState2 == HIGH && number != 2)||(buttonState2 == LOW && number == 2)) {
   power(false); 
}

  else power(true); 

}


void lap2()
{
  digitalWrite(ledPin1, LOW); 
  digitalWrite(ledPin2, LOW); 
  
  int count1, count2, countf, buttonstate1, buttonstate2;
  count1 = count2 = countf = buttonstate1 = buttonstate2 = 0;
  
  unsigned long starttime;
  starttime = millis();

while ((millis() - starttime) < 1000)
{
    buttonstate1 = digitalRead(buttonPin1);
    buttonstate2 = digitalRead(buttonPin2);

    if(buttonstate1 != lastbuttonstate1)
    {
      if(buttonstate1 == HIGH)
      count1++;

      delay(50);
    }

    lastbuttonstate1 = buttonstate1;

    if(buttonstate2 != lastbuttonstate2)
    {
      if(buttonstate2 == HIGH)
      count2++;

      delay(50);
    }

    lastbuttonstate2 = buttonstate2;
}

countf = count1 + count2; // total nb of changes of states (2 pushbuttons)

if (countf < 6)
    analogWrite(motor, countf*15);
else
    analogWrite(motor, 255);
}


void power(bool power) {
  if (power == true) //make sure horse is at max power
    analogWrite(motor, 255);

  else    
    analogWrite(motor, 40);  
}
