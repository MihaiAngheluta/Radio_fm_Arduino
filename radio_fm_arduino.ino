#include <RDA5807.h> //includem libraria pentru receptorul radio RDA5708
#include <LiquidCrystal.h> //includem libraria pentru lcd 16x2

//////////// Partea de initializare pentru derulare //////////////////
  int screenWidth = 16; //dimensiunea pe lungime = 16 coloane
  int screenHeight = 2; //dimensiunea pe inaltimea = 2 randuri
  int stringStart, stringStop = 0; // Start/Stop derulare sir = 0
  int scrollCursor = screenWidth; //textul va fi derulat pe lungime
//////////////////////////////////////////////////////////////////////

  RDA5807 radio = RDA5807();  

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  double frequence = 87.5; //definim o constanta cu o precizie dubla numita frecventa = 87.5 MHz
  double frequence_ant = 87.5; // definim o constanta cu o precizie dubla numita frecventa de la antena = 87.5 MHz
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////// initializam led-urile pentru cele 6 posturi radio gasite ////////////////////
  int led1 = 16; //verde
  int led2 = 17; //albasru
  int led3 = 2; //albastru
  int led4 = 3; //rosu
  int led5 = 4; //verde
  int led6 = 5; //rosu

  LiquidCrystal lcd(11, 12, 6, 7, 8, 9); //initializam rs=11, en=12, d4=2, d5=3, d6=4, d7=5 pentru lcd
////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////
void setup(){
  Serial.begin(9600); //incepem pe seriala de 9600 baud
  Wire.begin(); 
  lcd.begin (16, 2); //16 coloane, 2 linii
  lcd.setCursor(3, 0); //seteaza coloana si randul
  lcd.print("Proiect SC"); //afiseaza textul
  lcd.setCursor(0, 1); //seteaza coloana si randul
  lcd.print("Radio FM Arduino"); //afiseaza textul
  delay(2000); //afiseaza textul timp de 2 sec
}
/////////////////////////////////////////////////////////

///////////////////////////////////////////// Bucla Loop ////////////////////////////////////////////////
void loop(){
  //////////////////////////////////////////////////////////////////////////////////////////////////
  int val_pot = analogRead(A0); //valoarea potentiometrului se citeste de la intrarea analogica AO
  frequence = ((double)val_pot * (108.0 - 87.5)) / 1024.0 + 87.5; //rezolva ecuatia = valoarea analogica * (108.0-97.5)/1024.0 +87.5, adica valoarea de la potentiometru se inmulteste cu raportul dintre diferenta pragurilor max si min ale benzii de frecventa si 1024.0 adunat cu pragul min al benzii de frecventa.
  frequence = ((int)(frequence * 10)) / 10.0; // calcul pentru obtinerea celor 1000 Hz
  /////////////////////////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////////////////
  if (frequence_ant != frequence){ //daca frecventa de la antena este egala cu frecventa
    lcd.clear(); //sterge continutul de pe lcd
    lcd.setCursor(1, 0); //seteaza coloana si randul
    lcd.print("Freq: "); //afisseaza textul : "Freq:"
    lcd.setCursor(6, 0); //seteaza coloana si randul
    lcd.print("      MHz"); //afisseaza textul : "   MHz"
    lcd.setCursor(6, 0); //seteaza coloana si randul
    lcd.print(frequence, 1); //afisseaza textul: valoarea frecventei curente
    radio.setFrequency(frequence); 
    frequence_ant = frequence; //seteaza ca frecventa sa fie egala cu frecventa de la antena
  }
  ///////////////////////////////////////////////////////////////////////////////////////////

////////////////////// Daca frecventa este egala cu 92.4 /////////////////////////
   if (frequence == 92.4){
  /////////////////// Partea de derulare spre stanga ///////////////////////////
    String line1= " Freq:92.4 MHz" ; // prima linie = textul din gilimele
    String line2= "  Lider FM " ; // a doua linie = textul din gilimele
    lcd.setCursor(0, 0); // seteaza cursor - primul cursor de pe prima linie
    lcd.print(line1); // afiseaza pe prima linie textul respectiv
    lcd.setCursor(scrollCursor, 1); // selecteaza linia 2, linia care va fi derulata
    lcd.print(line2.substring(stringStart,stringStop)); //afiseaza linia in functie de subtring-urile: stringStart si stringStop
    delay(400); // viteza de derulare
    lcd.clear(); 
    if(stringStart == 0 && scrollCursor > 0){ //daca start = 0 si derulare cursor > 0 
      scrollCursor--; // derulare cursor spre stanga
      stringStop++; // derulare continua
    } else if (stringStart == stringStop){ //daca start derulare = stop derulare
      stringStart = stringStop = 0; // start = stop = 0
      scrollCursor = screenWidth; // deruleaza textul pe lungime
    } else if (stringStop == line2.length() && scrollCursor == 0) { // daca textul de pe linia 2 a ajuns la cursorul 0
      stringStart++; // porneste derularea 
    } else {
      stringStart++; // porneste derularea
      //stringStop++;
    } 
   //////////////////////////////////////////////////////////////////////////////
    
    digitalWrite (2, HIGH);
  }
  else { digitalWrite (2, LOW);
  }
 
///////////////////////////////////////////////////////////////////////////////
  
  ///// De aici in jos se repreta aceleasi structuri "if" si "else" pentru alte posturi de radio  
   if (frequence == 92.8){
  /////////////////// Partea de derulare spre stanga ///////////////////////////
    String line1= " Freq:92.8 MHz" ;
    String line2= "  Kiss FM " ;
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(scrollCursor, 1);
    lcd.print(line2.substring(stringStart,stringStop));
    delay(400);
    lcd.clear();
    if(stringStart == 0 && scrollCursor > 0){ 
      scrollCursor--; 
      stringStop++;
    } else if (stringStart == stringStop){ 
      stringStart = stringStop = 0; 
      scrollCursor = screenWidth; 
    } else if (stringStop == line2.length() && scrollCursor == 0) { 
      stringStart++; 
    } else { // altfel
      stringStart++;
      //stringStop++;
    } 
  //////////////////////////////////////////////////////////////////////////////
    
    digitalWrite (16, HIGH);
  }
  else {
    digitalWrite (16, LOW ); //stinge led-ul
       }  

  if (frequence == 94.8){
  /////////////////// Partea de derulare spre stanga ///////////////////////////
    String line1= " Freq:94.8 MHz" ;
    String line2= "  ZU FM " ;
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(scrollCursor, 1);
    lcd.print(line2.substring(stringStart,stringStop));
    delay(400);
    lcd.clear();
    if(stringStart == 0 && scrollCursor > 0){
      scrollCursor--;
      stringStop++;
    } else if (stringStart == stringStop){
      stringStart = stringStop = 0;
      scrollCursor = screenWidth;
    } else if (stringStop == line2.length() && scrollCursor == 0) {
      stringStart++;
    } else {
      stringStart++;
      //stringStop++;
    } 
  //////////////////////////////////////////////////////////////////////////////
    
    digitalWrite (17, HIGH);
  }
  else {
    digitalWrite (17, LOW );
       }

   if (frequence == 101.6){
   /////////////////// Partea de derulare spre stanga //////////////////////////
    String line1= " Freq:101.6 MHz" ;
    String line2= "  Cultural FM " ;
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(scrollCursor, 1);
    lcd.print(line2.substring(stringStart,stringStop));
    delay(400);
    lcd.clear();
    if(stringStart == 0 && scrollCursor > 0){
      scrollCursor--;
      stringStop++;
    } else if (stringStart == stringStop){
      stringStart = stringStop = 0;
      scrollCursor = screenWidth;
    } else if (stringStop == line2.length() && scrollCursor == 0) {
      stringStart++;
    } else {
      stringStart++;
      //stringStop++;
    } 
   //////////////////////////////////////////////////////////////////////////////
    
    digitalWrite (3, HIGH);
  }
  else {
    digitalWrite (3, LOW );
       }

  if (frequence == 103.4){  
  /////////////////// Partea de derulare spre stanga //////////////////////////
    String line1= " Freq:103.4 MHz" ;
    String line2= "  Europa FM " ;
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(scrollCursor, 1);
    lcd.print(line2.substring(stringStart,stringStop));
    delay(400);
    lcd.clear();
    if(stringStart == 0 && scrollCursor > 0){
      scrollCursor--;
      stringStop++;
    } else if (stringStart == stringStop){
      stringStart = stringStop = 0;
      scrollCursor = screenWidth;
    } else if (stringStop == line2.length() && scrollCursor == 0) {
      stringStart++;
    } else {
      stringStart++;
      //stringStop++;
    } 
  //////////////////////////////////////////////////////////////////////////////
    
    digitalWrite (5, HIGH);
  }
  else {
    digitalWrite (5, LOW );
       }

  if (frequence == 104.8){
  /////////////////// Partea de derulare spre stanga //////////////////////////
    String line1= " Freq:104.8 MHz" ;
    String line2= "  Rock FM ";
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(scrollCursor, 1);
    lcd.print(line2.substring(stringStart,stringStop));
    delay(400);
    lcd.clear();
    if(stringStart == 0 && scrollCursor > 0){
      scrollCursor--;
      stringStop++;
    } else if (stringStart == stringStop){
      stringStart = stringStop = 0;
      scrollCursor = screenWidth;
    } else if (stringStop == line2.length() && scrollCursor == 0) {
      stringStart++;
    } else {
      stringStart++;
      //stringStop++;
    } 
 /////////////////////////////////////////////////////////////////////////////
 
    digitalWrite (4, HIGH);
  }
  else {
    digitalWrite (4, LOW );
       }
  }

 
