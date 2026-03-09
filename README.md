# -GPRS-to-Thinkspeak-with-AT-command
   
![alt tag](https://github.com/ingeniously/GPRS_Sim800C_HTTPS_Protocol_Stack_With_Thinkspeak/blob/main/image/HTTP-POST-Thingspeak-ESP32.webp)  

## Description

The General Packet Radio Service or GPRS is a standard (network protocol) for mobile telephony derived from GSM and complementary to it, allowing a higher data rate. It is often referred to as 2.5G or 2G+. 
The G stands for generation and the 2.5 indicates that it is a technology halfway between GSM (second generation) and UMTS (third generation).
GPRS is an extension of the GSM protocol: it adds packet transmission compared to the latter. 
This method is better suited for data transmission.

## Example of a Board Designed with the SIM800C Module

![alt tag](https://user-images.githubusercontent.com/111455408/189918128-64a172f3-ab05-4124-b025-ba71c4d3b04f.jpg)

The GPRS modules designed by Makerlab are primarily built with the SIM800C and an AVR (mostly the Atmega 328P).

![alt tag](https://user-images.githubusercontent.com/111455408/189923075-5ba58787-f590-4c0c-8117-a25f340d09b6.jpg)
![alt tag](https://user-images.githubusercontent.com/111455408/189918090-29212168-2329-493e-af07-ac463209a728.jpg)
![alt tag](https://user-images.githubusercontent.com/111455408/189918013-09578672-104e-4303-a9ee-fb07f7768f69.png)
![alt tag](https://user-images.githubusercontent.com/111455408/189917973-81ebb7eb-d89b-4124-83bc-1915e777bc68.png)

With these modules, it is possible to transmit information via:
   - SMS
   - Calls
   - The Internet using internet protocols like HTTP, HTTPS, and TCP/IP
 
In this tutorial, you will primarily learn how to establish a connection to a server using the HTTP protocol, which is different from HTTPS (which handles data that is more secure and encrypted).

## AT Commands

AT commands are instructions used to control a modem. AT stands for Attention. Every command line starts with "AT" or "at". 
In general, GSM/GPRS modems designed for wireless applications support AT commands better than regular mobile phones. The AT commands we will need are:

   - **AT** ; // Check if the module is functional     
   - **AT+SAPBR=3,1,"Contype","GPRS"** ; // GPRS type connection
   - **AT+SAPBR=3,1,"APN","internet.tn"** ; // Network provider's APN       
   - **AT+SAPBR=1,1** ; // Open GPRS communication
   - **AT+SAPBR=2,1** ; // Send requests via GPRS communication
   - **AT+HTTPINIT** ; // Initialize HTTP protocol
   - **AT+HTTPPARA="CID",1** ; // HTTP parameters
   - **AT+HTTPPARA="URL","http://api.thingspeak.com/update?api_key=M9HMBKTN87ITELK7&field1=0"** ;  // Set the URL (Universal Resource Locator), i.e., the server API
   - **AT+HTTPACTION=0** ; // Start the GET session 
   - **AT+HTTPREAD** ; // Read data coming from the HTTP server 
   - **AT+HTTPTERM** ; // Stop the HTTP protocol
        
## The HTTP Protocol

The HTTP (HyperText Transfer Protocol) is the most widely used protocol on the Internet since 1990. Version 0.9 was solely intended to transfer data on the Internet, particularly Web pages written in HTML.
As a request-response protocol, HTTP gives users a way to interact with Web resources. It transmits hypertext messages between clients and servers. HTTP clients typically use TCP (Transmission Control Protocol) connections to communicate with servers.
  
Communication between the browser and the server happens in two steps:

   - **The browser makes an HTTP request**
   - **The server processes the request and then sends an HTTP response**
         
### Advantages
       
This protocol has several advantages, such as:

   - Providing a standard way for Web browsers and servers to communicate with each other.
   - HTTP is usually not filtered by network firewalls designed to allow Web traffic. 
   - HTTP uses an advanced addressing scheme. It assigns an IP address with recognizable names so that it can be easily identified on the World Wide Web.

## HTTP Commands

Table listing HTTP commands:
           
| Command  | Description          |
| :--------------- |:---------------:|
| GET | Request the resource located at the specified URL |
| HEAD | Request the header of the resource located at the specified URL |
| POST | Send data to the program located at the specified URL |
| PUT | Send data to the specified URL |
| DELETE | Delete the resource located at the specified URL |


## The ThingSpeak Server 

![alt tag]() ThingSpeak logo

ThingSpeak is an analytics platform service that allows you to aggregate, visualize, and analyze live data streams in the cloud. You can send data to ThingSpeak from your devices via the HTTPS protocol. 
There are several servers dedicated to IoT. The most well-known are:

   - **Ubidots**
   - **Node-RED** 
   - **Cayenne**
   - **Firebase**
  
However, one of these IoT application platforms that offers a wide variety of analytics capabilities is ThingSpeak. 
To use ThingSpeak, you must sign up and create a channel. Once created, you can send data, allowing ThingSpeak to process and retrieve it.

This server allows you to:

   - **Configure accounts and channels**: Information about channels, users, and ThingSpeak licenses.
   - **Write data to the channel**: Using APIs to update channels via software or devices.
   - **Read data from the channel**: Using APIs to read strings using software or devices.
   - **Prepare and analyze data**: Transform and interact with data in MATLAB. 
   - **Visualize data**: Transform and visualize data in MATLAB.
   - **Specialized analysis with MATLAB**: ThingSpeak examples that show the use of advanced tools available in add-on toolboxes.

 
 ![alt tag](https://user-images.githubusercontent.com/111455408/189918004-f9956cf7-a5fb-4215-8c56-be1e6d8360e0.png) 
 
**The links below are the ones used for Read and Write in ThingSpeak**
  ![alt tag](https://user-images.githubusercontent.com/111455408/189921141-cbee3869-49b1-4845-a0ae-f43ea171364f.png) 
 
 # Program Structure
 
 We begin by adding the **"SoftwareSerial.h"** library and defining the RX and TX pins for **UART** serial communication.
Next, we declare all the variables and action enumerations that will be used in the body of the program written in **C/C++**.
The main program structure is described below. Five functions are used:

   - **The resetBuffer() function**: Used to reset the "buffer" variable, which stores responses from AT commands, back to 0.

   - **The Send_Command() function**: Used to send AT commands and receive the response through 'Serial.read()'. The parameters of this function are the command to be sent and the time between two successive transmissions.

   - **The setup() function**: The setup() function is called when the program starts. This function is first used to activate GPRS by sending a 1-second LOW pulse to the microcontroller's 'Powerkey' pin. 
It then sets the data transmission speed to the SIM800C and the data display speed locally on the serial monitor expressed in baud. 
Finally, it establishes the connection with the ThingSpeak network using the AT commands dedicated to the HTTP protocol.

      Here is an overview of the setup() function:
```cpp  
void setup()
{
  Serial.begin(9600);
  dbug.begin(9600);
  dbug.println("Get Session"); /* Display get session */
  // pinMode(9,OUTPUT); /* Start SIM800C using the Powerkey */
  pinMode(A0,OUTPUT);
  pinMode(9,OUTPUT);
  digitalWrite(9,LOW);
  delay(1000);
  digitalWrite(9,HIGH);
  delay(1000);
  digitalWrite(9,LOW);
  delay(1000);
  send_Command("AT+SAPBR=3,1,\"APN\",\"weborange\"\r\n"); 
  send_Command("AT+SAPBR=3,1,\"Contype\",\"GPRS\"\r\n");  
  send_Command("AT+SAPBR=1,1",3000);
  send_Command("AT+HTTPINIT\r\n"); 
  send_Command("AT+HTTPPARA=\"CID\",1\r\n");
  send_Command("AT+HTTPPARA=\"URL\",\"http://api.thingspeak.com/channels/1748594/fields/1.json?results=1\"\r\n");
}
```
   - **The loop() function**: Executes an instruction routine (sending AT+HTTPACTION) to continuously read the data sent from the application by setting a wait time so that the data is received and analyzed in a timely manner.
In this program, the wait time before each reception was set to a value of 5 ms.
Here is an overview of the loop() function:
```cpp  
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
```

   - **The Analyse function**: This plays an important role as it analyzes the responses of the sent AT commands and displays them on the serial monitor so we can diagnose any potential connection errors. 
Thanks to this function, we can save the response to the AT+HTTPREAD command, which returns a data frame such as:
```cpp  
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
                          dbug.println("Received HTTPACTION");
                           Working_Case = HTTPACTION_TYPE;
                              }
                                   else if ( strcmp(buffer, "+HTTPREAD:") == 0 ) {
                                       dbug.println("Received HTTPREAD");            
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
```
 
![alt tag](https://user-images.githubusercontent.com/111455408/189917998-030f156f-1a0b-436a-bcb5-ac278666541e.png) 

 This frame is received character by character and stored in a variable called Buffer. It contains the date, time, longitude, chain name, and the ThingSpeak channel used. This data frame is read by the microcontroller and displayed on the Arduino's serial monitor.
