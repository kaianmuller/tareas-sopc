#include <Arduino_FreeRTOS.h>
#include <semphr.h>


SemaphoreHandle_t xSerialSemaphore;


void Tarea1( void *pvParameters );
void Tarea2( void *pvParameters );
void Tarea3( void *pvParameters );



void setup() {

  Serial.begin(9600);
  
  while (!Serial) {
    ; 
  }

  if ( xSerialSemaphore == NULL )
  {
    xSerialSemaphore = xSemaphoreCreateMutex();
    if ( ( xSerialSemaphore ) != NULL )
      xSemaphoreGive( ( xSerialSemaphore ) );
  }


  xTaskCreate(
    Tarea1
    ,  "Tarea1" 
    ,  128  
    ,  NULL
    ,  1  
    ,  NULL );

  xTaskCreate(
    Tarea2
    ,  "Tarea2"
    ,  128  
    ,  NULL
    ,  1  
    ,  NULL );

  xTaskCreate(
    Tarea3
    ,  "Tarea3"
    ,  128  
    ,  NULL
    ,  1 
    ,  NULL );

 
}


void loop()
{

}



void Tarea1( void *pvParameters __attribute__((unused)) )  // This is a Task.
{

int contador = 0;
  


 

  for (;;) 
  {
    
  contador++;
    
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
     
     
      Serial.println(contador);


      xSemaphoreGive( xSerialSemaphore ); 
    }
vTaskDelay(1000/portTICK_PERIOD_MS); 
    
  }
}

void Tarea2( void *pvParameters __attribute__((unused)) )  
{

  for (;;)
  {

    int pinValue = analogRead(A0);


    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {

      Serial.println(pinValue);
  
      xSemaphoreGive( xSerialSemaphore ); 
    }

 vTaskDelay(3000/portTICK_PERIOD_MS); 
  }
}

void Tarea3( void *pvParameters __attribute__((unused)) )  
{


  pinMode(13,OUTPUT);

  int state = LOW;
  for (;;)
  {

    if(state == LOW){
      state = HIGH;
      }else{
        state = LOW;
        }
        
    digitalWrite(13,state);
  

   vTaskDelay(2000/portTICK_PERIOD_MS);  
  }
}
