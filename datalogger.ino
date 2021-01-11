#include <SoftwareSerial.h>

#include <DS3232RTC.h>  //RTC Library https://github.com/JChristensen/DS3232RTC
#include <SPI.h>        //SPI library for the sd breakout board. Part of the Arduino IDE
#include <SdFat.h>         //SD library for the sd breakout board. Part of the Arduino IDE
SdFat SD;
#include <string.h>
SoftwareSerial myserial(7, 8);
const int chipSelect = 10;
const int donePin = 4;
char filename[] = "00000000.txt";
char oldfilename[]= "00000000.txt";

File dataFile;
File oldfile;
long sensor1, cm;
long sensor2, cm2;
long sensor3, cm3;
long sensor4, cm4;
long sensor5, cm5;
long sensor6, cm6;
long sensor7, cm7;
long sensor8, cm8;
long sensor9, cm9;
long sensor10, cm10;

const int pwPin1 = 3;
//card reader variabls
//RTC Module global variables
//const int time_interval=1;// Sets the wakeup intervall in minutes
const time_t ONE_DAY(86400);

//int8_t answer;


void setup() {
  DIDR0 = 0x0F; 
  Serial.begin(9600);//Start Serial Comunication
  myserial.begin(9600);
  pinMode(donePin, OUTPUT); 
  
  /**
  pinMode(5, OUTPUT); //SimModul sleepmode
  delay(500);
  digitalWrite(5, HIGH);
  sendATcommand("AT+CFUN=0", "OK", 2000);
  sendATcommand("AT+CSCLK=1", "OK", 2000);
    
  **/
 
    /*
     * Uncomment the block block to set the time on your RTC. Remember to comment it again 
     * otherwise you will set the time at everytime you upload the sketch
     **/
    
    tmElements_t tm;
    tm.Hour = 8;               // set the RTC to an arbitrary time
    tm.Minute = 20;
    tm.Second = 00;
    tm.Day = 22;
    tm.Month = 12;
    tm.Year = 2020 - 1970;      // tmElements_t.Year is the offset from 1970
    RTC.write(tm);              // set the RTC from the tm structure
   
   
   
    


    
}

void loop() {
  
 delay(500);//wait 5 seconds before going to sleep. In real senairio keep this as small as posible
 
 Going_To_Sleep();
}

void Going_To_Sleep(){
    
    
    
    
    
    
    time_t t;// creates temp time variable
    t=RTC.get(); //gets current time from rtc
    //Serial.println(("Sleep  Time: "+String(hour(t))+":"+String(minute(t))+":"+String(second(t))));//prints time stamp on serial monitor
   
  
   
    read_sensor();
    getFileName();
    createFileName();
    logsd();
    t=RTC.get();
    digitalWrite(donePin, LOW); 
    digitalWrite(donePin, HIGH);
    
   
  }


void read_sensor(){

  unsigned long startTime = millis ();
 
  sensor1 = pulseIn(pwPin1, HIGH);
  cm = sensor1/58;
  delay(1000);
  sensor2 = pulseIn(pwPin1, HIGH);
  cm2 = sensor2/58;
  delay(1000);
  sensor3 = pulseIn(pwPin1, HIGH);
  cm3 = sensor3/58;
  delay(1000);
  sensor4 = pulseIn(pwPin1, HIGH);
  cm4 = sensor4/58;
  delay(1000);
  sensor5 = pulseIn(pwPin1, HIGH);
  cm5 = sensor5/58;
  delay(1000);
  sensor6 = pulseIn(pwPin1, HIGH);
  cm6 = sensor6/58;
  delay(1000);
  sensor7 = pulseIn(pwPin1, HIGH);
  cm7 = sensor7/58;
  delay(1000);
  sensor8 = pulseIn(pwPin1, HIGH);
  cm8 = sensor8/58;
  delay(1000);
  sensor9 = pulseIn(pwPin1, HIGH);
  cm9 = sensor9/58;
  delay(1000);
  sensor10 = pulseIn(pwPin1, HIGH);
  cm10 = sensor10/58;
  unsigned long endTime = millis ();
  unsigned long elapsedTime = endTime - startTime;
  Serial.println (elapsedTime);
 
 
}


void printall(){
 
 
  Serial.print(cm);
  Serial.print(cm2);
  Serial.print(cm3);
  Serial.print(cm4);
  Serial.print(cm5);
  Serial.print(cm6);
  Serial.print(cm7);
  Serial.print(cm8);
  Serial.print(cm9);
  Serial.print(cm10);
 
}

void logsd(){
 
  unsigned long startTime = millis ();

  //Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
       Serial.println(F("initialization failed!"));
        return;
    }
    Serial.println(F("initialization done."));
  time_t p; //create time object for time and date stamp
  
  p=RTC.get();
  tmElements_t tm;
  RTC.read(tm);



   char dateBuffer[20];

   
   sprintf(dateBuffer,"%04u-%02u-%02u %02u:%02u:%02u",tm.Year+1970,tm.Month,tm.Day,tm.Hour,tm.Minute,tm.Second);
   Serial.println(dateBuffer);


  
  
  dataFile = SD.open(filename, FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    //dataFile.println(String(hour(p))+":"+String(minute(p))+";"+cm);
    //dataFile.println(String(tm.Hour)+":"+String(tm.Minute)+";"+cm);
    dataFile.print(dateBuffer);
    dataFile.print(";");
    dataFile.print(cm);
    dataFile.print(";");
    dataFile.print(cm2);
    dataFile.print(";");
    dataFile.print(cm3);
    dataFile.print(";");
    dataFile.print(cm4);
    dataFile.print(";");
    dataFile.print(cm5);
    dataFile.print(";");
    dataFile.print(cm6);
    dataFile.print(";");
    dataFile.print(cm7);
    dataFile.print(";");
    dataFile.print(cm8);
    dataFile.print(";");
    dataFile.print(cm9);
    dataFile.print(";");
    dataFile.print(cm10);
    dataFile.println();
    //Serial.println(String(tm.Hour)+":"+String(tm.Minute)+";"+cm);
    dataFile.close();
    // print to the serial port too:
    //Serial.println(String(hour(p))+":"+String(minute(p))+";"+cm);
  }
  // if the file isn't open, pop up an error:
  else {
    //Serial.println("error opening file");
  }
  unsigned long endTime = millis ();
  unsigned long elapsedTime = endTime - startTime;
  Serial.println (elapsedTime);
  
}

/*
char* string2char(String command){
  if(command.length() != 0){
    char *p = const_cast<char*>(command.c_str());
    return p;
  }
}
**/


void getFileName(){
time_t t;
t=RTC.get();


filename[0] = (year(t)/1000)%10 + '0'; //To get 1st digit from year()

filename[1] = (year(t)/100)%10 + '0'; //To get 2nd digit from year()

filename[2] = (year(t)/10)%10 + '0'; //To get 3rd digit from year()

filename[3] = (year(t))%10 + '0'; //To get 4th digit from year()

filename[4] = month(t)/10 + '0'; //To get 1st digit from month()

filename[5] = month(t)%10 + '0'; //To get 2nd digit from month()

filename[6] = day(t)/10 + '0'; //To get 1st digit from day()

filename[7] = day(t)%10 + '0'; //To get 2nd digit from day()

//Serial.println(filename);

}


void getoldFileName(){
time_t t;
t=RTC.get();
time_t oneday = t - ONE_DAY;

oldfilename[0] = (year(oneday)/1000)%10 + '0'; //To get 1st digit from year()

oldfilename[1] = (year(oneday)/100)%10 + '0'; //To get 2nd digit from year()

oldfilename[2] = (year(oneday)/10)%10 + '0'; //To get 3rd digit from year()

oldfilename[3] = (year(oneday))%10 + '0'; //To get 4th digit from year()

oldfilename[4] = month(oneday)/10 + '0'; //To get 1st digit from month()

oldfilename[5] = month(oneday)%10 + '0'; //To get 2nd digit from month()

oldfilename[6] = day(oneday)/10 + '0'; //To get 1st digit from day()

oldfilename[7] = day(oneday)%10 + '0'; //To get 2nd digit from day()

}
void createFileName(){

//Check file name exist?
SD.begin(chipSelect);
if (SD.exists(filename)) {

//Serial.println("exists.");

}

else {

//Serial.println("doesn't exist.");
getoldFileName();
//Serial.println("Send old file.");
ftpupload();
//Serial.println("Creating new file");

//Serial.println(filename);


//Serial.println(oldfilename);
dataFile = SD.open(filename, FILE_WRITE);

dataFile.close();

}

}
void ftpupload(){
  
  delay(5000);
    // SD function
    
   // Serial.print("Initializing SD card...");
    if (!SD.begin(chipSelect)) {
      //  Serial.println("initialization failed!");
        return;
    }
    //Serial.println("initialization done.");
   
    
    oldfile = SD.open(oldfilename, FILE_READ);
    if (oldfile)
      //Serial.println("is opened in read mode.");
    // GSM function
    
    myserial.begin(9600);
    delay(3000);
   
    sendATcommand("AT", "OK", 3000);
    Serial.println("GSM modem working!");
    sendATcommand("AT+CFUN=1", "OK", 2000);
    sendATcommand("AT+CSCLK=0", "OK", 2000);
    delay(3000);
   
    // waits for signal
    
    /**
    while( (sendATcommand("AT+CREG?", "+CREG: 0,1", 500) ||
            sendATcommand("AT+CREG?", "+CREG: 0,5", 500)) == 0 );
    **/

    byte answer = 0;
    int i = 0;
    while (i < 10 && answer == 0){
    answer = sendATcommand("AT+CREG?","+CREG: 0,1", 1000);
    i++;
    delay(1000);
    }
    if (answer == 0) {
    while (i < 20 && answer == 0){
      answer = sendATcommand("AT+CREG?","+CREG: 0,5", 1000);
      i++;
      delay(1000);
    }
    }
    
    
   
    // sets APN, user name and password
    sendATcommand("AT+SAPBR=3,1,\"Contype\",\"GPRS\"", "OK", 2000);
    // ther is no username and password for my GPRS connection so I commented out this line
    sendATcommand("AT+SAPBR=3,1,\"APN\",\"TM\"", "OK", 2000);
   
    sendATcommand("AT+SAPBR=1,1", "OK", 2000);
    sendATcommand("AT+FTPCID=1", "OK", 2000);
   
    // sets the paremeters for the FTP server
    sendATcommand("AT+FTPSERV=server.com", "OK", 2000);
    sendATcommand("AT+FTPPORT=21", "OK", 2000);
    sendATcommand("AT+FTPUN=username", "OK", 2000);
    sendATcommand("AT+FTPPW=password", "OK", 2000);
    sendATcommand(string2char("AT+FTPPUTNAME=\"" + String(oldfilename) + "\""), "OK", 2000);
    sendATcommand("AT+FTPPUTPATH=\"/home/path/loggerfile/\"", "OK", 2000);
    if (sendATcommand("AT+FTPPUT=1", "+FTPPUT: 1,1,", 30000) == 1){

    oldfile = SD.open(oldfilename);

    if (oldfile) {
    int archivosize = oldfile.size();
      while(oldfile.available()){

        while(archivosize >= 1000){
          sendATcommand("AT+FTPPUT=2,1000","+FTPPUT: 2,1000",3000);
          for(int i = 0; i < 1000; i++){
            myserial.write(oldfile.read());
            archivosize -= 1;
          }
        }

      String  ScomA = "";
      String  ScomB = "";
        // archivosize += 1;
        ScomA.concat("AT+FTPPUT=2,");
        ScomA.concat(archivosize);
        ScomA.concat("\"");

        ScomB.concat("+FTPPUT: 2,");
        ScomB.concat(archivosize);
        ScomB.concat("\"");

        char CcomA[ScomA.length()], CcomB[ScomB.length()];

        ScomA.toCharArray(CcomA,ScomA.length());
        ScomB.toCharArray(CcomB,ScomB.length());


        sendATcommand(CcomA,CcomB,3000);
        for(int i = 0; i < archivosize; i++){
          myserial.write(oldfile.read());
          
        }
      }
      // close the file:
      oldfile.close();
    }
    //Finalizo envio de datos
    sendATcommand("AT+FTPPUT=2,0", "OK", 3000);
    sendATcommand("AT+SAPBR=0,1", "OK", 2000);
    sendATcommand("AT+CFUN=0", "OK", 2000);
    sendATcommand("AT+CSCLK=2", "OK", 2000);
    //Serial.println("Upload Succes!");
  }
  else{
   Serial.println("FTPERROr");
   sendATcommand("AT+SAPBR=0,1", "OK", 2000);
   sendATcommand("AT+CFUN=0", "OK", 2000);
   sendATcommand("AT+CSCLK=2", "OK", 2000);
  }

}


/*
int8_t sendATcommand(char* ATcommand, char* expected_answer, unsigned int timeout){

    uint8_t x=0,  answer=0;
    char response[100];
    unsigned long previous;

    memset(response, '/0', 100);    // Initialize the string

    delay(100);

    while( myserial.available() > 0) myserial.read();    // Clean the input buffer

    myserial.println(ATcommand);    // Send the AT command


        x = 0;
    previous = millis();

    // this loop waits for the answer
    do{
        if(myserial.available() != 0){
            // if there are data in the UART input buffer, reads it and checks for the asnwer
            response[x] = myserial.read();
            Serial.print(response[x]);
            x++;
            // check if the desired answer  is in the response of the module
            if (strstr(response, expected_answer) != NULL)
            {
                answer = 1;
            }
        }
    }
    // Waits for the asnwer with time out
    while((answer == 0) && ((millis() - previous) < timeout));

        return answer;
}
**/

const char* string2char(const String& command){
  return command.c_str();
}
/**
char* string2char(String command){
  if(command.length() != 0){
    char* p = const_cast<char*>(command.c_str());
    return p;
  }
}

**/
unsigned char sendATcommand(const char* ATcommand, const char* expected_answer1, unsigned int timeout) {
  unsigned char x = 0;
  unsigned char answer = 0;
  char response[100];
  unsigned long previous;
  memset(response, '\0', 100);
  delay(100);
  while( myserial.available() > 0) myserial.read();
  myserial.println(ATcommand);
  x = 0;
  previous = millis();
  do{
    if(myserial.available() != 0){   
      response[x] = myserial.read();
      //myserial.print(response[x]);
      x++;
      if (strstr(response, expected_answer1) != NULL) {
        answer = 1;
      }
    }
  } while((answer == 0) && ((millis() - previous) < timeout));
  Serial.println(response);
  return answer;
}
