int ledPin[] = {A2, 2, 3, 4, 5, 6, 7, 8, 9, 10 , 11, 12, A3};
int Notes[] = {261, 277, 293, 311, 329, 349, 369, 392, 415, 440, 466, 493};
int song[100];

// boleans for conditionals
boolean listenToNotes;
boolean reset;
boolean gameStart;

// pins
int buzzer = 13;
int potentiometer = A1;
int buttons = A0;

// varaibles for values of analog input
int level = 3;
int gameSpeed = 0;
int whichButton = 0;

int iteration = 0;

void setup()
{

  Serial.begin(9600);
  randomSeed(analogRead(3)); 
  
  pinMode(buzzer, OUTPUT); // buzzer output
  
  // settignt the values of booleans
  listenToNotes = true;
  reset = true;
  gameStart = false;
  
  for(int i = 0; i <= 99; i++) { // for making random sequence of notes
    song[i] = randomNote();
    
    Serial.println(song[i]);
    
    if (i <=12 ) // for setting pins to output
    {
      pinMode(ledPin[i], OUTPUT);
    }
    
  }
  
  
}


void loop(){
  
 gameSpeed = analogRead(potentiometer); // checks potentiometer for speed
 whichButton = analogRead(buttons); // checks which button has been pressed
  //Serial.println(gameSpeed);
  if (gameStart == true) 
  {
     
    
    
      if (!listenToNotes) // first phase of the game
      {  
          playRandomNotes(buzzer, level, gameSpeed, song); // plays notes

          level++; // increment for increasing notes
          listenToNotes = true;
          reset = true;
      }
    
      else // second phase of the game
      {
         switch(whichButton) 
         {
          case 1013:   // middle c
              Serial.println("c");
              beep(buzzer, Notes[0], 300);
              reset = comparePressedButton(Notes[0], iteration);
              iteration++;
              break;
          case 1003:   // c#
              Serial.println("c#");
              beep(buzzer, Notes[1], 300);
              reset = comparePressedButton(Notes[1], iteration);
              iteration++;
              break;
          case 993:   // d
              Serial.println("d");
              beep(buzzer, Notes[2], 300);
              reset = comparePressedButton(Notes[2], iteration);
              iteration++;
              break;
          case 984:   // d#
              Serial.println("d#");
              beep(buzzer, Notes[3], 300);
              reset = comparePressedButton(Notes[3], iteration);
              iteration++;
              break;
          case 974:   // e
              Serial.println("e");
              beep(buzzer, Notes[4], 300);
              reset = comparePressedButton(Notes[4], iteration);
              iteration++;
              break;
          case 965:   // f
              Serial.println("f");
              beep(buzzer, Notes[5], 300);
              reset = comparePressedButton(Notes[5], iteration);
              iteration++;
              break;
          case 956:   // f#
              Serial.println("f#");
              beep(buzzer, Notes[6], 300);
              reset = comparePressedButton(Notes[6], iteration);
              iteration++;
              break;
          case 947:   // g
              Serial.println("g");
              beep(buzzer, Notes[7], 300);
              reset = comparePressedButton(Notes[7], iteration);
              iteration++;
              break;
          case 939:   // g#
              Serial.println("g#");
              beep(buzzer, Notes[8], 300);
              reset = comparePressedButton(Notes[8], iteration);
              iteration++;
              break;
          case 930:   // a
              Serial.println("a");
              beep(buzzer, Notes[9], 300);
              reset = comparePressedButton(Notes[9], iteration);
              iteration++;
              break;
          case 922:   // a#
              Serial.println("a#");
              beep(buzzer, Notes[10], 300);
              reset = comparePressedButton(Notes[10], iteration);
              iteration++;
              break;
          case 913:   // b
              Serial.println("b");
              beep(buzzer, Notes[11], 300);
              reset = comparePressedButton(Notes[11], iteration);
              iteration++;
              break;       
          default:
              break;
          }

      }
    
      if (!reset) {
            listenToNotes = false;
            reset = true;
            iteration = 0;
            level = 3;

            delay(2000);
       } 



      if (iteration+1 >= level) {
          listenToNotes = false;
          iteration = 0;
          Serial.println(level);
          delay(1000);
      }
  }
  
  if (whichButton == 905) 
  {
    if (!gameStart){
      digitalWrite(ledPin[12], HIGH);
      gameStart = true;
      listenToNotes = false;
      level = 3;
    }
    else {
      gameStart = false;
      digitalWrite(ledPin[12], LOW);
    }
    delay(1500);
  }
  
}









void playRandomNotes(int buzz, int amount, int Speed, int noteArray[]) { // for playing random notes 
  for ( int i = 0; i < amount; i ++) {
    beep(buzz, noteArray[i], Speed);
    delay(50);
  }
}

int noteToLed(int note) {
  int led;
  switch(note) {
    case 261:   // middle c
        led = 0;
        break;
    case 277:   // c#
        led = 1;
        break;
    case 293:   // d
        led = 2;
        break;
    case 311:   // d#
        led = 3;
        break;
    case 329:   // e
        led = 4;
        break;
    case 349:   // f
        led = 5;
        break;
    case 369:   // f#
        led = 6;
        break;
    case 392:   // g
        led = 7;
        break;
    case 415:   // g#
        led = 8;
        break;
    case 440:   // a
        led = 9;
        break;
    case 466:   // a#
        led = 10;
        break;
    case 493:   // b
        led = 11;
        break;
    default:
      led = 0;
      break;
  }
 return led;
}


void beep(int buzz, int note, int duration) { // for beeping a note and a LED
  
  int led = noteToLed(note);
  digitalWrite(ledPin[led], HIGH);
  tone(buzz, note);
  delay(duration);
  digitalWrite(ledPin[led], LOW);
  noTone(buzz);
  delay(50); 
}


int randomNote() {
  int note = Notes[random(12)];
  return note;
}


boolean comparePressedButton(int note, int notePosition) {
  
  boolean ifCorrectNote;
  
  if (note == song[notePosition]){
    ifCorrectNote = true;
  }
  else {
    ifCorrectNote = false;
  }
  return ifCorrectNote;
  
}
