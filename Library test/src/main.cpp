#include "lib_test.h"

void setup() 
{
  Serial.begin(115200);
  int result = addTwoInts(4,3);
  Serial.println(result);
}

void loop() {}