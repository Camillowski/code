short an0 = 14;
unsigned long timeRec = 0;
unsigned long startTime = 0;
long dd = 0, hh = 19, mm =30, ss = 0;


void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Enter Time hh:mm:ss = ");

 
    //Read time string
    String str;
    do {
      str = Serial.readString();
    } while (str == "");

    //Parse string and assign time
    hh = str.substring(0, 2).toInt();
    mm = str.substring(3, 5).toInt();
    ss = str.substring(6, 8).toInt();
  

  //Calculate starting timeto seconds
  startTime = hh * 3600l + mm * 60l + ss;
}

void loop() {

  float temp = 0;

  //Read temp from LM35
  for (int i = 0; i < 20; ++i) {
    temp += analogRead(an0) * (5.0 / 1024) / 0.01;
    delay(250);
  }
  temp /= 20; //Average temp from 20 readings

  //Calculate time
  timeRec = startTime + millis() / 1000;
  dd = timeRec / 86400;
  hh = (timeRec - (dd * 86400)) / 3600;
  mm = (timeRec - (dd * 86400) - (hh * 3600)) / 60;
  ss = timeRec - (dd * 86400) - (hh * 3600) - (mm * 60);

  //Save data to file temp.dat
  /*
    String data;
    data.concat('d');
    data.concat(dd);
    data.concat(';');
    data.concat(hh);
    data.concat(':');
    data.concat(mm);
    data.concat(':');
    data.concat(ss);
    data.concat(';');
    data.concat(String(temp,1));

    Serial.println(data);
  */
  //Print day:X;hh:mm:ss temp
  Serial.print("day:");
  Serial.print(dd);
  Serial.print("; ");
  Serial.print("Godzina: ");
  Serial.print(hh);
  Serial.print(":");

  Serial.print(mm);
  Serial.print(":");

  Serial.print(ss);
  Serial.print("; ");

  Serial.print("Temperatura: ");
  Serial.print(temp, 1);
  Serial.println("'C");
}

