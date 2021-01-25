#include <LiquidCrystal.h>
//LCD pin to Arduino
const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_d4 = 4; 
const int pin_d5 = 5; 
const int pin_d6 = 6; 
const int pin_d7 = 7; 
const int pin_BL = 10; 
LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);

uint8_t clicked = 0;
uint8_t leftNum = 3;
uint8_t rightNum = 2;
uint8_t selectedNum = 1;
char *operators[4]={"+","-","*","/"};
uint8_t selectedOp = 0;
int16_t result;
float divResult;

void setup() {
 lcd.begin(16, 2);
 lcd.setCursor(0,0);
 lcd.print("Let's do math!");
 delay(500);
 lcd.clear();
}
void loop() {
  getKeyPress();
  updateDisplay();
  clicked ^= 1;
} 

void getKeyPress(){
 int x;
 if(!clicked){
   x = analogRead (0);
   clicked = true;
   delay(150); 
   if (x < 60) { //clicked right, move cursor to rightNum
     selectedNum = 2;  
   }
   else if (x < 200) { //UP: increase currently selected Num
    if(selectedNum == 1){
      leftNum++;
    }else{
      rightNum++;
    }
    lcd.clear();
   }
   else if (x < 400){ //DOWN: decrease currently selected Num
     if(selectedNum == 1){
      leftNum--;
     }else{
      rightNum--;
     }
     lcd.clear();
   }
   else if (x < 600){ //LEFT: move cursor to leftNum
     selectedNum = 1;
   }
   else if (x < 800){ //SELECT: Change operator
     if(selectedOp < 3){
      selectedOp++;
     }else{
      selectedOp=0;
     }
     lcd.clear();
   }
 }
}

void updateDisplay(){

 lcd.setCursor(0,1);
 lcd.print(leftNum);
 lcd.setCursor(4,1);
 lcd.print(operators[selectedOp]);
 lcd.setCursor(6,1);
 lcd.print(rightNum);
 lcd.setCursor(10,1);
 lcd.print("=");
 lcd.setCursor(0,0);
 switch(selectedOp){
  case 0:
    lcd.print("Addition!");
    result = leftNum+rightNum;
    break;
  case 1:
    lcd.print("Subtraction!");
    result = leftNum-rightNum;
    break;
  case 2:
    lcd.print("Multiplication!");
    result = leftNum*rightNum;
    break;
  case 3:
    lcd.print("Division!");
    divResult = (float)leftNum/rightNum;
    break;
 }
 lcd.setCursor(12,1);
 if(selectedOp != 3){
  lcd.print(result);
 }else{
  lcd.print(divResult);
 }
}
