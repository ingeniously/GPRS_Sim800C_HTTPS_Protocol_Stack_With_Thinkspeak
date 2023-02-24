# -GPRS-to-Thinkspeak-with-AT-command
   
![alt tag](https://github.com/ingeniously/GPRS_Sim800C_HTTPS_Protocol_Stack_With_Thinkspeak/blob/main/image/HTTP-POST-Thingspeak-ESP32.webp)  

## Description

   Le General Packet Radio Service ou GPRS est une norme (protocole réseau) pour la téléphonie mobile dérivée du GSM et complémentaire
 de celui-ci, permettant un débit de données plus élevé. On le qualifie souvent de 2,5G ou 2G+. 
 Le G est l'abréviation de génération et le 2,5 indique que c'est une technologie à mi-chemin entre le GSM (deuxième génération) et l'UMTS (troisième génération).
Le GPRS est une extension du protocole GSM : il ajoute par rapport à ce dernier la transmission par paquets. 
Cette méthode est plus adaptée à la transmission des données

## Exemple de Carte concu avec Le module SIM800C

![alt tag](https://user-images.githubusercontent.com/111455408/189918128-64a172f3-ab05-4124-b025-ba71c4d3b04f.jpg)

Les Modules GPRS concu par Makerlab Sont concu principalement avec le  SIM800C et un Avr(Principalement l'Atmega 328P

![alt tag](https://user-images.githubusercontent.com/111455408/189923075-5ba58787-f590-4c0c-8117-a25f340d09b6.jpg)
![alt tag](https://user-images.githubusercontent.com/111455408/189918090-29212168-2329-493e-af07-ac463209a728.jpg)
![alt tag](https://user-images.githubusercontent.com/111455408/189918013-09578672-104e-4303-a9ee-fb07f7768f69.png)
![alt tag](https://user-images.githubusercontent.com/111455408/189917973-81ebb7eb-d89b-4124-83bc-1915e777bc68.png)



 Il est possible avec ses modules de transmettre des informations a travers les
   - Sms ,
   - Les Appels et
   - via Internet en utilisant des protocols internets comme le HTTP,Le HTTPS et le TCP/IP
 
Dans ce tutoriel vous trouverrez principalement comment Etablir une connection a unserveur en utilisant le protocols Htpp qui est differnet du https(Donneé plus securisé et Cryptée


## les Commandes AT

  Les commandes AT sont des instructions utilisées pour contrôler un modem. AT est l'abréviation d’Attention. Chaque ligne de commande commence par "AT" ou "at". 
En général, les modems GSM / GPRS conçus pour les applications sans fil prennent mieux en charge les commandes AT que les téléphones mobiles ordinaires. Les commandes AT dont on aura besoin sont :

   - **AT** ; //Vérifier si le modules est Fonctionnelle     
   - **AT+SAPBR=3,1,"Contype","GPRS"** ; // Connection du type GPRS
   - **AT+SAPBR=3,1,"APN","internet.tn"** ; //l’APN de fournisseur Réseau       
   - **AT+SAPBR=1,1** ; //Ouvrir la communication GPRS
   - **AT+SAPBR=2,1** ; //Envoyer des requêtes à travers la communication GPRS
   - **AT+HTTPINIT** ; //Initialiser le protocole http
   - **AT+HTTPPARA="CID",1** ; //paramètres pour http
   - **AT+HTTPPARA="URL","http://api.thingspeak.com/update?api_key=M9HMBKTN87ITELK7&f ield1=0"** ;  //Mettre l'adresse URL (Universal ressource Locator) C’est à dire L'API du serveur
   - **AT+HTTPACTION=0** ; //commencer la GET session 
   - **AT+HTTPREAD** ; //Lire les données qui viennent du serveur HTTP 
   - **AT+HTTPTERM** ; //Arrêter le protocole http
        
## Le protoccople HTTP

 Le protocole HTTP (HyperText Transfer Protocol) est le protocole le plus utilisé sur Internet depuis 1990. La version 0.9 était uniquement destinée à transférer des données sur Internet en particulier des pages Web écrites en HTML.
En tant que protocole requête-réponse, HTTP offre aux utilisateurs un moyen d’interagir avec des ressources Web. On citera, à ce titre, les fichiers HTML en transmettant des messages hypertexte entre les clients et les serveurs. Les clients HTTP utilisent généralement des connexions TCP (Transmission Control Protocol) pour communiquer avec les serveurs
  
  La communication entre le navigateur et le serveur se fait en deux temps :

   - **Le navigateur effectue une requête http**
   - **Le serveur traite la requête puis envoie une réponse http**
         
         
 ### Avantages
       
Ce protocole possède plusieurs avantages tels que :

   - Fournir un moyen standard pour les navigateurs Web et les serveurs de communiquer entre eux.
   - HTTP n’est généralement pas filtré par les pares-feux réseaux conçus pour autoriser le trafic Web. 
   - HTTP utilise un schéma d’adressage avancé. Il attribue une adresse IP avec des noms reconnaissables afin que celle-ci soit facilement identifiable dans le World Wide Web.


## Les Commandes HTTP

           Tableau lites des commandes HTTP
           
| Commande  | Description          |
| :--------------- |:---------------:|
|GET  |Requête de la ressource située à l'URL spécifiée |
| HEAD | Requête de l'en-tête de la ressource située à l'URL spécifiée |
| POST |Envoi de données au programme situé à l'URL spécifiée |
| PUT |Envoi de données à l'URL spécifiée |
| POST |Suppression de la ressource située à l'URL spécifiée|


## Le serveur ThingSpeak 

![alt tag]() logo Thinkspeak

  ThingSpeak est un service de plate-forme d’analyse données qui permet d'agréger, de
visualiser et d'analyser des flux de données en direct dans le cloud. On peut envoyer des
données à ThingSpeak à partir d’une application via le protocole HTTPS. 
Il existe plusieurs serveurs dédiés à l’IoT. Les plus connus sont:

   - **Ubidots**
   - **Nodered** 
   - **Cayenne**
   - **Firebase**
  
Mais l’une de ces plates-formes d’applications IoT qui offre une grande variété de capacités d’analyse est ThingSpeak. 
Pour utiliser ThingSpeak, on doit s’inscrire et créer un canal. Une fois crée, on peut 
envoyer les données, permettant à ThingSpeak de les traiter et les récupérer.

Ce serveur permet de :

   - **Configurer les comptes et les canaux** : Informations sur les canaux, les    utilisateurs et les licences ThingSpeak.
   - **Écrire des données sur le canal** : par l’utilisation des API pour mettre à jour les canaux avec des logiciels ou des appareils.
   - **Lire les données du canal** : par l’utilisation API pour lire les chaînes à l'aide de logiciels ou d'appareils.
   - **Préparer et analyser les données** : Transformer et répondre aux données dans MATLAB. 
   - **Visualiser les données** : Transformer et visualiser des données dans MATLAB.
   - Analyse spécialisée avec MATLAB : Exemples ThingSpeak qui montrent l'utilisation des outils avancés disponibles dans les boîtes à outils complémentaires

 
 ![alt tag](https://user-images.githubusercontent.com/111455408/189918004-f9956cf7-a5fb-4215-8c56-be1e6d8360e0.png) 
 
**Les liens ci dessous sont les liens utiliser For Read and Write in Thinkspeak**
  ![alt tag](https://user-images.githubusercontent.com/111455408/189921141-cbee3869-49b1-4845-a0ae-f43ea171364f.png) 
 
 # Stucture Programme
 
 On commence par ajouter la librairie **« Software Serial .h»** et en définissant aussi les pins des broches Rx et Tx pour la communication série **UART** .
On déclare ensuite toutes les variables et les énumères actions qui seront utilisées dans le corps du programme écrit en **C/C++**.
La structure de programme principale est décrite ci-dessous. Cinq fonctions sont utilisées:

   - **La fonction resetBuffer()** : Elle sert à remettre la variable « buffer » qui stocke les réponses des commandes AT à 0.

   - **La fonction Send_Command ()** : Elle sert à envoyer les commandes AT et d’en recevoir la réponse grâce au ‘Serial. Read’. Les paramètres de cette fonction sont la commande à envoyer et le temps entre deux envois successifs.

   - **La fonction setup ()** : La fonction setup () est appelée au démarrage du programme Cette fonction est d’abord utilisé pour activer le GRPS en envoyant une impulsion LOW de 1 seconde a la boche ‘Powerkey’ du microcontrôleur,
ensuite à définir la vitesse de transmission des données au SIM800C et la vitesse de l’affichage des données localement sur le moniteur série exprimée en baud. 
Elle permet finalement d’établir la connexion avec le réseau ThingSpeak avec les commandes AT dédiées au protocole http.

      Ci-dessous un aperçu sur la fonction setup().   
```C++  
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
```
   - **La fonction Loop ()** : Elle exécute une routine d’instruction (envoi d’AT+HTTPACTION) pour une lecture continue des données envoyées depuis l’application en fixant le temps d’attente afin que les données soient reçues et analysées dans les bons délais.
Dans ce programme le temps d’attente avant chaque réception a été fixée de valeur a 5 ms.
Ci-dessous un aperçu sur la fonction Loop().
```C++  
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

   - **La fonction Analyse** : Celle-ci accomplit un rôle important dans la mesure où elle permet d’analyser les réponses des commandes AT envoyées et de les afficher sur le moniteur série pour qu’on puisse diagnostiquer d’éventuelle erreur de connexion. 
Grâce à cette fonction on peut sauvegarder la réponse à la commande AT+HTTPREAD qui renvoie une trame de donnée du type :	
```C++  
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
```
 
![alt tag](https://user-images.githubusercontent.com/111455408/189917998-030f156f-1a0b-436a-bcb5-ac278666541e.png) 

 Cette trame est reçue caractère par caractère et stockée dans une variable appelé Buffer.  Elle contient la date, l’heure, la longitude, le nom de la chaine et du canal ThingSpeak utilisé. Cette trame de donnée est lue par le microcontrôleur et affichée sur le moniteur série de l’Arduino
