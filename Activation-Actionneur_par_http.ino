#include <SoftwareSerial.h>
SoftwareSerial dbug(6, 5); // RX, TX

enum _Working_Case {
  MSG_TYPE,
  IGNORE_REPONSE,
  HTTPACTION_TYPE,
  HTTPACTION_REPONSE_VALUE,
  HTTPACTION_LENGTH,
  HTTPREAD_LENGTH,
  HTTPREAD_CONTENT
};

enum _actionState {
  WORKING,
  WAITING_FOR_RESPONSE
};

byte actionState = WORKING;
unsigned long lastActionTime = 0;

byte Working_Case = MSG_TYPE;
char buffer[280];
 const char* V1 ="999";
 char* p;
byte pos = 0;

int contentLength = 0;

void resetBuffer() {
  memset(buffer, 0, sizeof(buffer));
  pos = 0;
}

void send_Command(const char* msg, int waitMs = 500) {
  Serial.println(msg);
  while(Serial.available()) {
    Analyse(Serial.read());
  }
  delay(waitMs);
}

void setup()
{
  Serial.begin(9600);
  dbug.begin(9600);
    dbug.println("Get Session");/* Afficher get session  */
 // pinMode(9,OUTPUT);/*  Demarer Sim800c grace au Powerkey */
    pinMode(A0,OUTPUT);
  pinMode(9,OUTPUT);
   digitalWrite(9,LOW);
  delay(1000);
  digitalWrite(9,HIGH);
  delay(1000);
  digitalWrite(9,LOW);
  delay(1000);
             send_Command("AT+SAPBR=3,1,\"APN\",\"weborange\"\r\n"); 
  send_Command("AT+SAPBR=3,1,\"Contype,\"GPRS\"\r\n");  
  send_Command("AT+SAPBR=1,1",3000);
  send_Command("AT+HTTPINIT\r\n"); 
  send_Command("AT+HTTPPARA=\"CID\",1\r\n");
  send_Command("AT+HTTPPARA=\"URL\",\"http://api.thingspeak.com/channels/1748594/fields/1.json?results=1\"\r\n");
}

void loop()
{ 
  unsigned long now = millis();
    
  if ( actionState == WORKING ) {
    if ( now > lastActionTime + 5000 ) {
 
      send_Command("AT+HTTPPARA=\"URL\",\"http://api.thingspeak.com/channels/1748594/fields/1.json?results=1\"\r\n");
      send_Command("AT+HTTPACTION=0");
      
      lastActionTime = now;
      actionState = WAITING_FOR_RESPONSE;
    }
  }
  
  while(Serial.available()) {
    lastActionTime = now;
    Analyse(Serial.read());
  }
}

void Analyse(byte b) {

  buffer[pos++] = b;

  if ( pos >= sizeof(buffer) )
    resetBuffer(); // just to be safe

  switch (Working_Case) {
  case MSG_TYPE: 
    {
      if ( b == '\n' )
        resetBuffer();
      else {        
                   if ( pos == 3 && strcmp(buffer, "AT+") == 0 ) {
                           Working_Case = IGNORE_REPONSE;
                              }
                      else if ( b == ':' ) {   
                                 if ( strcmp(buffer, "+HTTPACTION:") == 0 ) {
                          dbug.println("Reception de HTTPACTION");
                           Working_Case = HTTPACTION_TYPE;
                              }
                                   else if ( strcmp(buffer, "+HTTPREAD:") == 0 ) {
                                       dbug.println("Recption de HTTPREAD");            
                                         Working_Case =HTTPREAD_LENGTH;
                                               }
                                               resetBuffer();
                                                } 
      }
    }
    break;

  case IGNORE_REPONSE:
    {
      if ( b == '\n' ) {
        dbug.print("Ignoring echo: ");
        dbug.println(buffer);
        Working_Case = MSG_TYPE;
        resetBuffer();
      }
    }
    break;

  case HTTPACTION_TYPE:
    {
      if ( b == ',' ) {
        dbug.print("HTTPACTION type is ");
        dbug.println(buffer);
        Working_Case = HTTPACTION_REPONSE_VALUE;
        resetBuffer();
      }
    }
    break;

  case HTTPACTION_REPONSE_VALUE:
    {
      if ( b == ',' ) {
        dbug.print("HTTPACTION result is ");
        dbug.println(buffer);
        Working_Case = HTTPACTION_LENGTH;
        resetBuffer();
      }
    }
    break;

  case HTTPACTION_LENGTH:
    {
      if ( b == '\n' ) {
        dbug.print("HTTPACTION length is ");
        dbug.println(buffer);
        
        // now request content
        Serial.print("AT+HTTPREAD=0,");
        Serial.println(buffer);
         
        Working_Case = MSG_TYPE;
        resetBuffer();
           // send_Command("AT+HTTPTERM\r\n");     
      }
    }
    break;

case HTTPREAD_LENGTH:
    {
      if ( b == '\n' ) {
        contentLength = atoi(buffer);
        dbug.print("HTTPREAD length is ");
        dbug.println(contentLength); 
        dbug.print("HTTPREAD content: ");
        Working_Case = HTTPREAD_CONTENT;
        resetBuffer();
      }
    }
    break;

case HTTPREAD_CONTENT:
    {
     
      // for this demo I'm just showing the content bytes in the serial monitor
      dbug.write(b);
      contentLength--;
      
      if ( contentLength <=40 ) {
 p=strstr(buffer,V1);
 if(p)
 {
  dbug.println ("yes");
  digitalWrite(A0,HIGH);
  digitalWrite(3,HIGH);
 }
 else
 {
   digitalWrite(A0,LOW);
   digitalWrite(3,LOW);
  dbug.println ("no");
 }
       
        // all content bytes have now been read
 
        Working_Case = MSG_TYPE;
        resetBuffer();
        
        dbug.println("\n\n\n");
        dbug.print("--------------------------------------------------------------------------------");
        
        actionState = WORKING;
      }
    }
    break;
  }
}
