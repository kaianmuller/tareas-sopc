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
      vTaskDelay(1000/portTICK_PERIOD_MS);  

      xSemaphoreGive( xSerialSemaphore ); 
    }

    
  }
}

void Tarea2( void *pvParameters __attribute__((unused)) )  
{

  for (;;)
  {

    int sensorValue = analogRead(A0);


    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {

      Serial.println(sensorValue);

      xSemaphoreGive( xSerialSemaphore ); 
    }

    vTaskDelay(1);  
  }
}

void Tarea3( void *pvParameters __attribute__((unused)) )  
{

  for (;;)
  {

    int sensorValue = analogRead(A0);


    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {

      Serial.println(sensorValue);

      xSemaphoreGive( xSerialSemaphore ); 
    }

    vTaskDelay(1);  
  }
}
