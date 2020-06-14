//Code for 4 players 

const int controller[4] = {28, X1, Y1, Z1}; //put pins of each controller
const int app[4] = {30, X2, Y2, Z2}; 

// to check for press 
bool pressed1 = false; 
bool pressed2= false; 

int howmany = 0; //need to know how many are playing 

//arrays that can be used for the sorting algorithm
long double winnertime = 0; 
int whowon = 0; 
int winnerorder[4] = {0, 0, 0, 0};

int winnerpin[4] = {8, X3, Y3, Z3}; 

//endtimes 
long double endtime[4] = {0, 0, 0, 0}; 

/*************************ARRAYS*************************/
//how many players 
int players[4] = {0, 0, 0, 0}; //array storing the number of players 

//ARDUINO UNO <-> ARDUINO MEGA
int pins_to_uno[4] = {7, X6, Y6, Z6}; //chose to have arrays for multiple players 
int pins_from_uno[4] = {6, X4, Y4, Z4}; 

//APP <-> ARDUINO MEGA
int pins_to_app[4]={9, X7, Y7, Z7};
int pins_from_app[4]={35, X5, Y5, Z5};
/********************************************************/


//checking if pressed
bool p1[4]; //button/joystick
bool p2[4]; //app
 
void setup() {
  
/*************************SWITCHES***********************/
// controller chosen by the player: either a controller or the app 
pinMode(controller[0], INPUT);
pinMode(app[0], INPUT);

pinMode(controller[1], INPUT);
pinMode(app[1], INPUT);

pinMode(controller[2], INPUT);
pinMode(app[2], INPUT);

pinMode(controller[3], INPUT);
pinMode(app[3], INPUT);
/********************************************************/

/************************COMMUNICATION*******************/
//FROM ARDUINO (Nano to Mega)
pinMode(pins_from_uno[0], INPUT);
pinMode(pins_from_uno[1], INPUT);
pinMode(pins_from_uno[2], INPUT);
pinMode(pins_from_uno[3], INPUT);

//FROM APP (App to Mega)
pinMode(pins_from_app[0], INPUT); 
pinMode(pins_from_app[1], INPUT);
pinMode(pins_from_app[2], INPUT); 
pinMode(pins_from_app[3], INPUT);

//TO ARDUINO (Mega to Nano)
pinMode(pins_to_uno[0], OUTPUT); 
pinMode(pins_to_uno[1], OUTPUT);
pinMode(pins_to_uno[2], OUTPUT); 
pinMode(pins_to_uno[3], OUTPUT);

//TO APP (Mega to Nano)
pinMode(pins_to_app[0], OUTPUT);
pinMode(pins_to_app[1], OUTPUT);  
pinMode(pins_to_app[2], OUTPUT);
pinMode(pins_to_app[3], OUTPUT);

pinMode(winnerpin[0], OUTPUT); 
pinMode(winnerpin[1], OUTPUT); 
pinMode(winnerpin[2], OUTPUT); 
pinMode(winnerpin[3], OUTPUT); 

pinMode(otherpin[0], INPUT);
pinMode(otherpin[1], INPUT); 
pinMode(otherpin[2], INPUT); 
pinMode(otherpin[3], INPUT);
/********************************************************/

}

//the followig code will be launched when the switch is turned ON and the players have already chosen their controller

void loop() {
  
  unsigned long starttime = millis(); 

//the type of controller chosen is determined & stored
    for (int i =0; i<4; i++)                                            //the 2 for loops have been put together 
      { 
        if (digitalRead(controller[i])==HIGH) //has player chosen button/joystick? 
            players[i] = 1; 
  
        if (digitalRead(app[i])==HIGH) //has player chosen app?
          players[i] = 2;
        
        if ((digitalRead(app[i])!=HIGH)&&(digitalRead(controller[i])!=HIGH))
          players[i] = 0;
      }

for (int k=0, k<4; k++) //how many are playing
  {
    if (players[k] != 0)
      howmany++; 
  }

int c = 0; 

while(c!=howmany) //get an input from each user that is playing 
{
    
    for (int m=0, m<4, m++)
    {
      if (players[m] == 1) 
      {
        pressed1 = digitalRead(pins_from_uno[m]);
        if(pressed1 == true)
          p1[m] = true; 
      }
      
      else if (players[m] == 2)
      {
        pressed2 = digitalRead(pins_from_app[m]);
        if(pressed2 == true)
            p2[m]= true; 
      }
      
      else if (players[m] == 0)
        p1[m] = p2[m] = false; 

      if((p1[m]==true) || (p2[m]==true))  //now this is included in for loop otherwise c would be larger than howmany
        c++;
    }         
}

for (int i=0, i<4, i++) //we cannot include this loop in the preceeding one because all players need to be ready 
{
    if (p1[i]==true) //if signal from buttons/joystick
        digitalWrite(pins_to_uno[i], HIGH); //signal Nano to start the rounds
        
    if(p2[i]==true) //if signal from app
        digitalWrite(pins_to_app[i], HIGH); //signal App to start
}


int d = 0;    
while(d!=howmany)
{
    for (int j=0, j<4, j++)
    {
      if((digitalRead(otherpin[j]) == HIGH)&&(endtime[j]==0)) //input from Nano that user has completed 2 rounds 
      {
        endtime[j]=millis(); 
        d++
      }
    }
}

 
/*if (b==howmany) //everyone is done => anounce winner
{ 
  winnertime = millis(); 
  for (int i=0, i<4, i++)
    {
      if ((endtime[i]<endtime[i+1])&&(endtime[i]<winnertime)&&(endtime[i]!=0))  HOW DO I KEEP TRACK OF WHICH PLAYER IT IS HELP
      {
          winnertime = endtime[i]; 
          whowon = i+1;   
      }
      
      
  //the player i+1 won */     
}
  
 
