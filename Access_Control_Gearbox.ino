 /* Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */
#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define Password_Length 5 
#define SS_PIN 53
#define RST_PIN 15

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(30, 31); //SIM800L Tx & Rx is connected to Arduino #3 & #2
char Data[Password_Length]; 
char Aineah[Password_Length]= "1111"; 
char Mike[Password_Length] =  "1222"; 
char Paul[Password_Length] =  "1333"; 
char Ken[Password_Length] =   "1444"; 
char Brenda[Password_Length] = "1555"; 
char Charity[Password_Length]="1666";
char customKey;

byte data_count = 0, master_count = 0;
bool Pass_is_good;

String welcome="Welcome ";
String password="Your password is: ";
String blocked=" card is blocked";
String names[7] = {"Aineah","Mike","Paul","Ken","Brenda","Charity" };
String ids[8]={"E9 5E 99 06","C9 CE 64 09","91 8A 51 00","EA 70 F1 0B","01 F8 C1 6C", "19 3B E7 06", "61 E6 C3 6C"};
String pass[6] = { "1111", "1222" , "1333","1444", "1555","1666"};

String new_ids[4];

int user_;
int counter1,counter2,counter3,counter4,counter5,counter6=0;
int count=0;
int block_1=0;
int led=10;
int red=18;
int h;
int i,m,p,new_=0;

char incomingByte; 
String inputString;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = 
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
LiquidCrystal_I2C lcd(0x27, 16, 2);  

void setup() 
{
  lcd.init();
  lcd.backlight();
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  lcd.setCursor(0,0);
  lcd.print("    GEARBOX    ");
  delay(1500);
  lcd.clear();
  lcd.print("Scan Card");
  pinMode(led,OUTPUT);
  pinMode(red,OUTPUT);
 
//Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);
}
void loop() 
{

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  lcd.clear();
  lcd.setCursor(0,0);
  content.toUpperCase();

  if (content.substring(1) == ids[0]) //change here the UID of the card/cards that you want to give access
  {
  lcd.clear();
  lcd.print("Aineah Detected");
  delay(2000);
  lcd.clear();
  enter_pass();
  user_=1;
  pass_check();
   }

 
  if (content.substring(1) == ids[1]) 
  {
  lcd.clear();
  lcd.print("Mike Detected");
  delay(2000);
  lcd.clear();
  enter_pass();
  user_=2;
  pass_check();
  }

  if (content.substring(1) == ids[2]) 
  {
  lcd.clear();
  lcd.print("Paul Detected");
  delay(2000);
  lcd.clear();
  enter_pass();
  user_=3;
  pass_check();
  }

   if (content.substring(1) == ids[3]) 
  {
  lcd.clear();
  lcd.print("Ken Detected");
  delay(2000);
  lcd.clear();
  enter_pass();
  user_=4;
  pass_check();
  }

   if (content.substring(1) == ids[4]) 
  {
  lcd.clear();
  lcd.print("Brenda Detected");
  delay(2000);
  lcd.clear();
  enter_pass();
  user_=5;
  pass_check();
  }

  
   if (content.substring(1) == ids[5]) 
  {
    Serial.println("Here");
  lcd.clear();
  lcd.print("Charity Detected");
  delay(2000);
  lcd.clear();
  enter_pass();
  user_=6;
  pass_check();
  }

   if (content.substring(1) == ids[6] ) 
  {
    //admin();
    lcd.print("Welcome Admin");
    delay(2000);
    scan_card();
    
  } 

}


 
void admin()
{
  lcd.clear();
 lcd.print("ADMIN ACCESS");
 delay(2000);
 lcd.clear();
 lcd.print("Cards Blocked");
 lcd.setCursor(0,1);

 
 if(block_1==0)
 {
  lcd.print("No blocked cards");
   delay(2000);
 }
 
//AINEAH
 if(block_1==1)
 {
  lcd.print(names[0]);
  blocked_();
  delay(2000);
 }

//MIKE
 if(block_1==2)
 {
  lcd.print(names[1]);
  blocked_();
  delay(2000);
 }

//PAUL
  if(block_1==3)
 {
  lcd.print(names[2]);
  blocked_();
  delay(2000);
 }
//KEN
  if(block_1==4)
 {
  lcd.print(names[3]);
  blocked_();
  delay(2000);
 }
//BRENDA
  if(block_1==5)
 {
  lcd.print(names[4]);
  blocked_();
  delay(2000);
 }

   if(block_1==6)
 {
  lcd.print(names[5]);
  blocked_();
  delay(2000);
 }

 block_1=0;
 scan_card();
 return;
}


void pass_check()
{
  start_:
  data_count=0;
  while(h==0)
  {
  customKey = customKeypad.getKey();
  
  if (customKey && customKey!='C' && customKey!='A' && data_count!=Password_Length-1)
  {
    Data[data_count] = customKey; 
    lcd.setCursor(data_count,1); 
    lcd.print("*"); 
    data_count++; 
   }

   if(customKey =='C')
   {

    Serial.println(data_count);
    if(data_count >=1 && data_count<=3)
    {
     data_count--; 
     Data[data_count] = '0';
     Data[data_count-1]= '\0'; 
     lcd.setCursor(data_count,1);
     lcd.print(" ");
    }

    else 
    {
      lcd.setCursor(0,0);
      lcd.print("End of deletion");
      delay(2000);
      data_count=0;
      enter_pass();
    }
    
   }

  if(data_count == Password_Length-1 && customKey=='A')
  {
    lcd.clear();

    if(user_==1)
    {
    if(!strcmp(Data, Aineah) && counter1<3)
    {
      lcd.print("Correct Password");
      delay(2000);
      lcd.clear();
      lcd.print(welcome + names[0]);
      delay(2000);
      lcd.clear();
      clearData(); 
      scan_card();
      h=1;
      return;
     }
    else
      {
        if(counter1<3)
      {
       incorrect_pass();
       counter1++;
       goto start_; 
      }

     else
      {
        card_blocked();
        block_1=1;
        Aineah_text();
        counter1=0;
        return;
      }
    }
    }

  if(user_==2)
    {
    if(!strcmp(Data, Mike) && counter2<3)
    {
      counter2=0;
      lcd.print("Correct Password");
      delay(2000);
      lcd.clear();
      lcd.print(welcome + names[1]);
      delay(2000);  
      lcd.clear();
      clearData(); 
      scan_card();
      h=1;
      return;
     }
    else
     {
     if(counter2<3)
      {  
       incorrect_pass();
       counter2++;
       goto start_;
      }

      else
      {
        card_blocked();
        block_1=2;
        Mike_text();
        counter2=0;
        return;
      }
   
      }
    }

//PAUL
  if(user_==3)
    {
    if(!strcmp(Data, Paul) && counter3<3)
    {
      counter3=0;
      lcd.print("Correct Password");
      delay(2000);
      lcd.clear();
      lcd.print(welcome + names[2]);
      delay(2000);  
      lcd.clear();
      clearData(); 
      scan_card();
      h=1;
      return;
     }
    else
     {
     if(counter3<3)
      {  
       incorrect_pass();
       counter3++;
       goto start_;
      }

      else
      {
        card_blocked();
        block_1=3;
        Paul_text();
        counter3=0;
        return;
      }
   
      }
    }


      if(user_==4)
    {
    if(!strcmp(Data, Ken) && counter4<3)
    {
      counter4=0;
      lcd.print("Correct Password");
      delay(2000);
      lcd.clear();
      lcd.print(welcome + names[3]);
      delay(2000);  
      lcd.clear();
      clearData(); 
      scan_card();
      h=1;
      return;
     }
    else
     {
     if(counter4<3)
      {  
       incorrect_pass();
       counter4++;
       goto start_;
      }

      else
      {
        card_blocked();
        block_1=4;
        counter4=0;
        Ken_text();  
        return;
      }
   
      }
    }


  if(user_==5)
    {
    if(!strcmp(Data, Brenda) && counter5<3)
    {
      counter5=0;
      lcd.print("Correct Password");
      delay(2000);
      lcd.clear();
      lcd.print(welcome + names[4]);
      delay(2000);  
      lcd.clear();
      clearData(); 
      scan_card();
      h=1;
      return;
     }
    else
     {
     if(counter5<3)
      {  
       incorrect_pass();
       counter5++;
       goto start_;
      }

      else
      {
       card_blocked();
       block_1=5;
       counter5=0;
       Brenda_text();
       return;
      }
   
      }
    }


    
  if(user_==6)
    {
    if(!strcmp(Data, Charity) && counter6<3)
    {
      counter6=0;
      lcd.print("Correct Password");
      delay(2000);
      lcd.clear();
      lcd.print(welcome + names[5]);
      delay(2000);  
      lcd.clear();
      clearData(); 
      scan_card();
      h=1;
      return;
     }
    else
     {
     if(counter6<3)
      {  
       incorrect_pass();
       counter6++;
       goto start_;
      }

      else
      {
       card_blocked();
       block_1=6;
       counter6=0;
       Charity_text();
       return;
      }
   
      }
    }



    
  }

  }

}

void blocked_()
{
//AINEAH
  if(user_==1)
  {
  mySerial.print("AT+CMGF=1\r"); // Set the shield to SMS mode
  delay(100);
  mySerial.print("AT+CMGS=\"+254701448559\"\r");  
  delay(200);
  mySerial.print(names[0]+blocked); //the content of the message
  mySerial.print("\r"); 
  delay(500);
  mySerial.print((char)26);//the ASCII code of the ctrl+z is 26 (required according to the datasheet)
  delay(100);
  mySerial.println();
  delay(1000);
  return;
  }

//MIKE
  if(user_==2)
  {
  mySerial.print("AT+CMGF=1\r"); // Set the shield to SMS mode
  delay(100);
  mySerial.print("AT+CMGS=\"+254701448559\"\r");  
  delay(200);
  mySerial.print(names[1]+blocked); //the content of the message
  mySerial.print("\r"); 
  delay(500);
  mySerial.print((char)26);//the ASCII code of the ctrl+z is 26 (required according to the datasheet)
  delay(100);
  mySerial.println();
  delay(1000);
  return;
  }

//PAUL
    if(user_==3)
{
  mySerial.print("AT+CMGF=1\r"); // Set the shield to SMS mode
  delay(100);
  mySerial.print("AT+CMGS=\"+254701448559\"\r");  
  delay(200);
  mySerial.print(names[2]+blocked); //the content of the message
  mySerial.print("\r"); 
  delay(500);
  mySerial.print((char)26);//the ASCII code of the ctrl+z is 26 (required according to the datasheet)
  delay(100);
  mySerial.println();
  delay(1000);
  return;
}

//KEN
    if(user_==4)
  {
  mySerial.print("AT+CMGF=1\r"); // Set the shield to SMS mode
  delay(100);
  mySerial.print("AT+CMGS=\"+254701448559\"\r");  
  delay(200);
  mySerial.print(names[3]+blocked); //the content of the message
  mySerial.print("\r"); 
  delay(500);
  mySerial.print((char)26);//the ASCII code of the ctrl+z is 26 (required according to the datasheet)
  delay(100);
  mySerial.println();
  delay(1000);
  return;
  }

//BRENDA
    if(user_==5)
  {
  mySerial.print("AT+CMGF=1\r"); // Set the shield to SMS mode
  delay(100);
  mySerial.print("AT+CMGS=\"+254701448559\"\r");  
  delay(200);
  mySerial.print(names[4]+blocked); //the content of the message
  mySerial.print("\r"); 
  delay(500);
  mySerial.print((char)26);//the ASCII code of the ctrl+z is 26 (required according to the datasheet)
  delay(100);
  mySerial.println();
  delay(1000);
  return;
  }

}

  void Aineah_text()
   {
  mySerial.print("AT+CMGF=1\r"); // Set the shield to SMS mode
  delay(100);
  mySerial.print("AT+CMGS=\"+254701448559\"\r");  
  delay(200);
  mySerial.print(password+pass[0]); //the content of the message
  mySerial.print("\r"); 
  delay(500);
  mySerial.print((char)26);//the ASCII code of the ctrl+z is 26 (required according to the datasheet)
  delay(100);
  mySerial.println();
  delay(1000);
   return;
   }

  void Mike_text()
   {
   mySerial.print("AT+CMGF=1\r"); // Set the shield to SMS mode
  delay(100);
  mySerial.print("AT+CMGS=\"+254701448559\"\r");  
  delay(200);
  mySerial.print(password+pass[1]); //the content of the message
  mySerial.print("\r"); 
  delay(500);
  mySerial.print((char)26);//the ASCII code of the ctrl+z is 26 (required according to the datasheet)
  delay(100);
  mySerial.println();
  delay(500);
    }
   
 void Paul_text()
{
  mySerial.print("AT\r"); // Set the shield to SMS mode
  delay(100);
  mySerial.print("AT+CMGF=1\r"); // Set the shield to SMS mode
  delay(100);
  mySerial.print("AT+CMGS=\"+254701069036\"\r");  
  delay(200);
  mySerial.print(password+pass[2]); //the content of the message
  mySerial.print("\r"); 
  delay(500);
  mySerial.print((char)26);//the ASCII code of the ctrl+z is 26 (required according to the datasheet)
  delay(100);
  mySerial.println();
  delay(500);
  return;
    }
    
  void Ken_text()
    {
  mySerial.print("AT+CMGF=1\r"); // Set the shield to SMS mode
  delay(100);
  mySerial.print("AT+CMGS=\"+254701448559\"\r");  
  delay(200);
  mySerial.print(password+pass[3]); //the content of the message
  mySerial.print("\r"); 
  delay(500);
  mySerial.print((char)26);//the ASCII code of the ctrl+z is 26 (required according to the datasheet)
  delay(100);
  mySerial.println();
  delay(500);
    }

  void Brenda_text()
    {
   mySerial.print("AT+CMGF=1\r"); // Set the shield to SMS mode
  delay(100);
  mySerial.print("AT+CMGS=\"+254701448559\"\r");  
  delay(200);
  mySerial.print(password+pass[4]); //the content of the message
  mySerial.print("\r"); 
  delay(500);
  mySerial.print((char)26);//the ASCII code of the ctrl+z is 26 (required according to the datasheet)
  delay(100);
  mySerial.println();
  delay(1000);
    }


     void Charity_text()
    {
   mySerial.print("AT+CMGF=1\r"); // Set the shield to SMS mode
  delay(100);
  mySerial.print("AT+CMGS=\"+254701448559\"\r");  
  delay(200);
  mySerial.print(password+pass[5]); //the content of the message
  mySerial.print("\r"); 
  delay(500);
  mySerial.print((char)26);//the ASCII code of the ctrl+z is 26 (required according to the datasheet)
  delay(100);
  mySerial.println();
  delay(1000);
    }


    

void card_blocked()
{
  lcd.setCursor(0,0);
  lcd.print("Card Blocked");
  lcd.setCursor(0,1);
  lcd.print("Sending Password");
  delay(2500);
  scan_card();
  return;
}

void incorrect_pass()
{
  lcd.print("Incorrect");
  delay(1000);
  lcd.clear();
  clearData(); 
  lcd.print("Enter Password:");
  return;
}


void access_denied()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Access denied");
  lcd.setCursor(0,1);
  lcd.print("Card Not Defined");
  delay(2000);
  return;
  
}

void scan_card()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Scan card");
  return;
}

void enter_pass()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter Password:");
  h=0;
}


void clearData()
{
  while(data_count !=0)
  {
    Data[data_count--] = 0; 
  }
  return;
}
