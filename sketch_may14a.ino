int a = 2;
int b = 3;
int c = 4;
int d = 5;
int e = 6;
int f = 7;
int g = 8;
int h = 9;

int num = 0; 
const int buttonpin = 10;

int buttonstate = 0;
int lastbuttonstate = 0;
long debounceDelay = 50;
long lastDebounceTime = 0;

int Fnd_seg[10][8] = {
  {0,0,0,0,0,0,1,1},
  {1,0,0,1,1,1,1,1},
  {0,0,1,0,0,1,0,1},
  {0,0,0,0,1,1,0,1},
  {1,0,0,1,1,0,0,1},
  {0,1,0,0,1,0,0,1},
  {0,1,0,0,0,0,0,1},
  {0,0,0,1,1,1,1,1},
  {0,0,0,0,0,0,0,1},
  {0,0,0,0,1,0,0,1}
};

void fnd_write(int row)
{
  int seg_Pin = 2;
  for (int segPos=0;segPos <8; segPos++)
  {
    digitalWrite(seg_Pin, Fnd_seg[row][segPos]);
    seg_Pin++;
  }
}

void setup() {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(h, OUTPUT);
}

void loop() {
  int reading = digitalRead(buttonpin);
  if (reading != lastbuttonstate)
  {
    lastDebounceTime = millis();
  }

  if((millis() - lastDebounceTime) > debounceDelay){
    if(reading != buttonstate){
      buttonstate = reading;
      if(buttonstate == HIGH)
      {
        num++;
        if(num > 9){
          num = 0;
        }
        fnd_write(num);
        delay(500);
      }
    }
  }
  lastbuttonstate= reading;
}
