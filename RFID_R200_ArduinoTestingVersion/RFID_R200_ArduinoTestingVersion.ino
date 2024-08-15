#include <SoftwareSerial.h> //Using the preset Arduino Software Serial library to read and write from the RFID module
SoftwareSerial mySerial(2, 3); //pin2 Rx, pin3 Tx 

int cmdLine[64]; // Command line that takes input RFID command from the user form the Arduino Serial Monitor, act as a stack that stores local cmd.
int cmdCharIndex = 0; // Command charactor Index Iterator that skips the space between the user hex command, act as a stack pointer.
int newLineFlag = 0; // Boolean flag variable that controls whether to output a \n character when RFID output is detected

void setup() { 
Serial.begin(115200);
mySerial.listen();
Serial.println("Reading out put is printed here, please refers to the specific module manual to check the output reference:\n"); 

mySerial.begin(115200); // RFID R200 is manually set to 115200 baud rate, to match with the setting, we use 115200 here
delay(10);
// mySerial.write(0x02); //Send the command to RFID, please refer to RFID manual 
} 

void loop() { 

      while (Serial.available()) 
      {
          int a = SerialReadHexDigit(); // Using the user defined function that converts hex input into decimal input
          // Serial.println(a);  // Prints the converted decimal input for process visualization
          if(a>=0){
          cmdLine[cmdCharIndex] = a; // Store the hex 2 decimal cmd input in the cmd array and prepare to send to the RFID module
          cmdCharIndex++;
          }
          delay(10); 
      }
      
      for(int i = 0; i < cmdCharIndex; i += 2){
          int c = mySerial.write(cmdLine[i] * 16 + cmdLine[i + 1]); // Send the cmd to the module by merging a pair of hex number to a single decimal number within the range of (0 - 255)
          // Serial.println(c);  // Prints the converted decimal input for process visualization
      }

      cmdCharIndex = 0; // Reset the cmd Array stack pointer back to 0, preparing to overwrite the local hex cmd variable in the Array for next use
      
      while (mySerial.available()) {

      byte Char = mySerial.read(); // Read the decimal response from RFID module (0 - 255)

      if (Char < 16) {
        Serial.print("0");
      }

      Serial.print(Char, HEX); //Display the Serial Number in HEX 
      Serial.print(" "); 
      newLineFlag = 1; // If smth is printed, then set the flag to true
      }

     if (newLineFlag > 0) {
       Serial.println(); // print a \n character when flag is true
       newLineFlag = 0; // reset the flag for the next input detection
     }
     
}

/*
 * function SerialReadHexDigit()
 * 
 * operation: converts Hex digit to Decimal number
 * returns: return -1 if the input is not a Hex number; therefore, can not be written as a decimal digit.
 */
int SerialReadHexDigit() {

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
