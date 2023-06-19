#include <LiquidCrystal.h>

//definire delay 
#define DELAY1 1000
#define DELAY2 200

//pinii pentru lcd
LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

//textul si lungimea textului le punem ca variabile globale
String text = "Proiect8";
int length = text.length();

void setup()
{
  lcd_1.begin(16, 2);//numarul de coloane si linii
  lcd_1.setCursor(0,0);//setam cursorul la coloana 1 si linia 0
  Serial.begin(9600);
}

void loop()
{
  char input;
  if(length>16)//verificam daca lungimea textului 
  {
    lcd_1.setCursor(0,0);
  	lcd_1.print("Lungime > 16");
    delay(DELAY1);
    
  }
  if(Serial.available())
  {
    input = Serial.read();
    Serial.print("Ai ales optiunea: ");
    Serial.print(input);
    Serial.println();
  }
  switch(input)
    {
    	case 'a':
      			slide();
      			break;
        case 'b':
      			zigzag();
      			break;
      	case 'c':
      			moving_text();
      			break;
        case 'd':
      			middle();
      			break;
      	default:
      			break;
    }
}

//a
//functia slide
void slide(){ 
    // Variabile de setare a dimensiunii ecranului - în acest caz, ecranul are 16 coloane și 2 rânduri.
    int screenWidth = 16;
    int screenHeight = 2;

    // Variabile pentru gestionarea poziției caracterului de la începutul stringului și cursorului în timpul derulării.
    int stringStart = 0; // Indexul primului caracter din șirul care va fi afișat.
    int scrollCursor = screenWidth; // Poziția actuală a cursorului pe ecran.

    // Variabile pentru controlul buclei de derulare.
    int inc = 0; // Variabila utilizată pentru a controla câte caractere au fost afișate pe ecran.
    bool count = true; // Flag pentru a determina când să se oprească bucla.

    // Buclei principale pentru derulare.
    while(inc < length + 1 && count){

        // Imprimă un spațiu la poziția curentă a cursorului + 1, pentru a șterge caracterul anterior la derulare.
        lcd_1.setCursor(scrollCursor + 1, 0);
        lcd_1.print(" ");

        // Mutați cursorul la poziția sa nouă și imprimați următorul caracter din șir.
        lcd_1.setCursor(scrollCursor, 0);
        lcd_1.print(text.substring(stringStart, stringStart + 1));

        // Face o pauză pentru a permite observarea textului care se derulează.
        delay(DELAY2);

        // Actualizează poziția cursorului și indexul de început al șirului.
        if (scrollCursor > inc){
            scrollCursor--;
        }
        else {
            inc++;
            scrollCursor = screenWidth;
            stringStart++;
        }

        // Dacă toate caracterele au fost afișate, curăță ecranul și oprește bucla.
        if (inc > length){
            lcd_1.clear();
            count = false;
            inc = 0;
            stringStart = 0;
        }
    } 
}

//b
//functia zigzag
void zigzag() {
  // Variabila care va urmări rândul curent pe care se afișează caracterele.
  int row = 0;

  // Bucle care parcurge fiecare caracter din șir.
  for (int j = 0; j < length; j++ ) 
  { 
    // Calculează rândul pe care va fi afișat caracterul curent (0 sau 1) într-un model de zig-zag.
    row = (15 - j) % 2;

    // Bucle care parcurge ecranul de la dreapta la stânga.
    for (int i = 15; i >= j; i--) 
    {
      // Setează cursorul la poziția curentă și afișează caracterul.
      lcd_1.setCursor(i, row);
      lcd_1.print(text[j]); 

      // Întârziere între afișări.
      delay(DELAY2);

      // Curăță poziția curentă pentru următorul pas al buclei.
      lcd_1.setCursor(i, row);
      if(i > j)
      {
        lcd_1.print(" ");
      }

      // Comută rândul pentru următoarea iterație.
      if (row == 1) 
      {
        row = 0;
      } 
      else 
      {
        row = 1;
      }
    }
  }

  // Curăță ecranul după terminarea derulării textului.
  lcd_1.clear();

  // Întârziere înainte de a repeta funcția.
  delay(DELAY2);
}


//c

//functia moving_text
void moving_text() 
{ 
  int position = 15;//pozitia initiala 
  bool direction = true; //directia de deplasare (spre stanga)
  int count = 0;//de cate ori sa repetam
  while(count<4) //executa doar o data
  { 
    int poz = 15;
    int j = 1;
    lcd_1.clear(); //se curata ecranul
    lcd_1.setCursor(position, 0); //se seteaza cursorul pe pozitia dorita
    lcd_1.print(text); //printam textul
    delay(DELAY2); //asteaptam 200 de milisecunde
    if(direction) //verificam directia curenta
    { //daca e spre stanga 
      position--; //decrementam pozitia
      if(position == 0)//verificam daca ajungem la capatul din stanga
      {
        lcd_1.clear(); //se curata ecranul 
        for(int i=0; i<length;i++)
        {
           
           lcd_1.setCursor(position, 0);//setam cursorul pe poz (0,0)
           lcd_1.print(text.substring(i,length));//printam substringul
           if(i>0)
           {
           		lcd_1.setCursor(poz,0);//setam cursorul  pe poz 15,14,13..
           		lcd_1.print(text);
           		poz--;
           		j++;
           		if(j == length)
          		{
          			position = poz;	
           		}
           }
           delay(DELAY2);//asteptam 200 de milisecunde
           lcd_1.clear(); //se curata ecranul
           //count++
        }
        count++;
      }
    } 
  }
}

//functia middle
void middle() 
{
  int poz1 = (length/2);//parametrul 1 pentru functia substring 
  int poz2 = poz1 + 1;//parametrul 2 pentru functia substring 
  int cursor1 = 7;//pozitia initiala a cursorului
  
  lcd_1.setCursor(cursor1,0); 
  lcd_1.print(text.substring(poz1-1,poz1));
  delay(1000);
  lcd_1.setCursor(cursor1,0);
  lcd_1.print(text.substring(poz1-1,poz2));
  
  while((poz1>0 && poz2<=length) && (cursor1>=0 && cursor1<=15))
  {
   	cursor1--;
   	poz1--;

   	delay(DELAY1);
  	lcd_1.setCursor(cursor1,0);
   	lcd_1.print(text.substring(poz1-1,poz2));
  
   	poz2++;
  
    delay(DELAY1);
    lcd_1.setCursor(cursor1,0);
    lcd_1.print(text.substring(poz1-1,poz2));
  }
  
  //textul incepe sa se stinga si sa se aprinda cu o latenta de 1 secunda timp de 3 ori
  for(int i = 0; i<3; i++)
  {
   lcd_1.clear();
    delay(DELAY1);
    lcd_1.setCursor(cursor1+1,0);
    lcd_1.print(text);
    delay(DELAY1);
  }
  lcd_1.clear();
}


