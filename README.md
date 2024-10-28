# XOR_encryption
This was part of a coding challenge at my uni, the challenge is now over, so I decided to add a bunch of stuff so I can test some of my coding skills.

### XOR encryption method:
1. Consider you have a message with the char **A** and a key with the char **t**.
   
2. The first thing you need to do is knowing their values in the ascii table:
  - **A** -> 65
  - **t** -> 116

3. Now, you need to obtain the binary value of those numbers:
  -  **A** -> 65 -> 01000001
  - **t** -> 116 -> 01110100

4. Whith this values you are going to opperate evey digit using an XOR, that way, if in both numbers in the same position there is a 1 or a 0, the output will be a 0, but, if there are different values, the output will be 1:
  - **A** -> 01000001
  - **t** -> 01110100
  - RES  ->  00110101

5. The resulting number will be again interpreted in base 10 and that number will be turned into an ascii character:
   - 00110101 -> 53 -> **5**

6. This same method will be aplied to every character of a message using the same key over and over until the message is fully encrypted.

## Program operation
- To compile the code just run the command ``make`` in your terminal and then you can run it like any other program.
- Currently there is only one way to run the program that is using the temrinal arguments, in the future you will be able to run the program and see a menu.
- To konw how to run the program you can run it like so: ``./xor.out -h`` because I'm too lazy to write that rigth now.

## Code documentation
The code is documented in spanish :P
