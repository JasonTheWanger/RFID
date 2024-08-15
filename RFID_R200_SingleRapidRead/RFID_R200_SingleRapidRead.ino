#include <SoftwareSerial.h> //Using the preset Arduino Software Serial library to read and write from the RFID module

SoftwareSerial mySerial(2, 3); //pin2 Rx, pin3 Tx 
#include "RFID_R200.h" // Using cmd struct header file

struct RapidSingleRead *cmd = &(singleRead);
struct maxRange *maximum = &(max);

int newLineFlag = 0; // Boolean flag variable that controls whether to output a \n character when RFID output is detected

void setup() { 

    Serial.begin(115200);
    mySerial.listen();
    Serial.println("Reading out put is printed here, please refers to the specific module manual to check the output reference:\n"); 
    mySerial.begin(115200); // RFID R200 is manually set to 115200 baud rate, to match with the setting, we use 115200 here
    delay(10);
    SerialSendCmd(maximum -> settingCmd, maximum -> settingCmdDec, maximum -> size); // setup the module to maximum receiving range
    delay(10);
} 

void loop() { 

    SerialSendCmd(cmd -> readCmd, cmd -> readCmdDec, cmd -> size); // Calls to the function to send and receive messages from the module
    delay(50); // Time break between each read
}

/*
 * function SerialReadHexDigit()
 * 
 * operation: converts Hex digit to Decimal number
 * returns: return -1 if the input is not a Hex number; therefore, can not be written as a decimal digit.
 */
int SerialReadHexDigit(){

    byte c = (byte) Serial.read(); // read the Hex input from the user
    if (c >= '0' && c <= '9') {
        return c - '0'; // // calculate the corresponding decimal number by subtraction the char '0' in the ASCII table.
    } else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10; // calculate the corresponding decimal number by subtraction the char 'A' in the ASCII table, adding 10 to match the hex digit rule
    } else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10; // calculate the corresponding decimal number by subtraction the char 'A' in the ASCII table, adding 10 to match the hex digit rule
    } else {
        return -1;   // Returns -1 when the chracter is not able to convert from hex to decimal 
    }
}

/*
 * function SerialConvertHex2DecCmd()
 * 
 * operation: converts 8 bit Hex digit to Decimal number and store them in an int array
 */
void SerialConvertHex2DecCmd(unsigned char *cmdHex, int *cmdDec, int size){

    for (int i = 0; i < size; i++){
        *(cmdDec + i) = (int) *(cmdHex + i); // convert 8 bit command to decimal format.
    }
}

/*
 * function SerialConvertHex2DecCmd()
 * 
 * operation: converts 8 bit Hex digits to Decimal number and store them in an int array
 */
void SerialSendCmd(unsigned char *cmdHex, int *cmdDec, int size){

    SerialConvertHex2DecCmd(cmdHex, cmdDec, size); // Calls to the function to convert 8 bit Hex digits to Decimal number and store them in an int array

    for (int i = 0; i < size; i++){ 
        mySerial.write(*(cmdDec + i)); // Iterate through the int array to send decimal command to the module.
    }

    while (mySerial.available()) {

      byte Char = mySerial.read(); // Read the decimal response from RFID module (0 - 255)

      if (Char < 16) {
        Serial.print("0"); // Adding leading 0 to hex number < 16
      }

      Serial.print(Char, HEX); //Display the Serial Number in HEX 
      Serial.print(" "); 
      newLineFlag = 1; // If something is printed, then set the flag to true
    }

    if (newLineFlag > 0) {
       Serial.println(); // print a \n character when flag is true
       newLineFlag = 0; // reset the flag for the next input detection
     }
}



