// Простая система управленя 3-мя сервоприводами бионической экзокисти с помощью миниатюрного пульта на радиоуправлении.

void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT); // mot 1
  pinMode(3, OUTPUT); // mot 1
  pinMode(4, OUTPUT); // mot 2
  pinMode(5, OUTPUT); // mot 2
  pinMode(6, OUTPUT); // mot 3
  pinMode(7, OUTPUT); // mot 3

  pinMode(10, INPUT); // radio_signal 1
  pinMode(9, INPUT); // radio_signal 2
}

void loop()
{
  if ((digitalRead(10) == 1))
    {
      digitalWrite(6,1); // моторы работает в одну сторону
      digitalWrite(7,0);

      digitalWrite(2,1); 
      digitalWrite(3,0);

      digitalWrite(4,1); 
      digitalWrite(5,0);
    }
 
  else if ((digitalRead(9) == 1))
    {
      digitalWrite(6,0); // моторы работают в другую сторону
      digitalWrite(7,1); 

      
      digitalWrite(2,0); 
      digitalWrite(3,1);

      digitalWrite(4,0); 
      digitalWrite(5,1);
    }

    else {
      digitalWrite(6,0); // стоп всех моторов
      digitalWrite(7,0); 

      
      digitalWrite(2,0); 
      digitalWrite(3,0);

      digitalWrite(4,0); 
      digitalWrite(5,0);
    }


}
