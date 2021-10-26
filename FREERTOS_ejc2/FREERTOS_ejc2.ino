#include <MPU9250_asukiaaa.h> //Library to interface with sensor
MPU9250_asukiaaa motionSensor;
#define LED 32

TaskHandle_t TaskHandle_3;

struct Accelerometer{
  float ax;
  float ay;
  float az;
  float aSqrt; 
};

QueueHandle_t SensorQueueS;
//Queue to send data between tasks

void motionSensorInit(void){
  Wire.begin(21, 22); //default i2c pins of esp32 are pin 21 and 22
  motionSensor.setWire(&Wire);
  motionSensor.beginAccel();
}

void Task1( void *pvParameters)
{
  struct Accelerometer AccelerometerR;  //Struct to store the read values from i2c sensor
  const TickType_t xDelay100ms = pdMS_TO_TICKS (100); 
  TickType_t xLastWakeTime; 
  /*variable to save the current tick count, it has to be initialized to the 
   *current tick count before it is used for the first time,then with the  
   *function vTaskDelayUntil is updated atomatically
   */   
   motionSensorInit();
   xLastWakeTime = xTaskGetTickCount();
 
  //Converts time in ms to the same time in system ticks
  while(1)
  {
    motionSensor.accelUpdate();
    AccelerometerR.ax =  motionSensor.accelX(); 
    AccelerometerR.ay =  motionSensor.accelY(); 
    AccelerometerR.az =  motionSensor.accelZ(); 
    AccelerometerR.aSqrt = motionSensor.accelSqrt();
    xQueueSendToBack(SensorQueueS, (void *) &AccelerometerR, 0); 
    vTaskDelayUntil(&xLastWakeTime, xDelay100ms);
    /* Delay for a period. A call to vTaskDelay() is used which places
       the task into the Blocked state until the delay period has expired.*/
  }
  
}

void Task2( void *pvParameters)
{
  struct Accelerometer AccelerometerW;  //Struct to store the read values from task1
  BaseType_t xStatus; //To receive data from queue
  const TickType_t xDelay1s = pdMS_TO_TICKS (1000); 
  TickType_t xLastWakeTime; 
  /*variable to save the current tick count, it has to be initialized to the 
   *current tick count before it is used for the first time,then with the  
   *function vTaskDelayUntil is updated atomatically
   */
  xLastWakeTime = xTaskGetTickCount();
 
  //Converts time in ms to the same time in system ticks
  while(1)
  {
    digitalWrite(LED, HIGH); //Switch on LED
    if( uxQueueSpacesAvailable != 0)
    {
      Serial.println("---- START ----");
      while((xQueueReceive(SensorQueueS, (void *) &AccelerometerW, 0) == pdPASS)){
        Serial.println(AccelerometerW.aSqrt);
      }
    }
    Serial.println("---- END ----");
    vTaskResume( TaskHandle_3 );
    /* Delay for a period. A call to vTaskDelay() is used which places
       the task into the Blocked state until the delay period has expired.*/
    
    vTaskDelayUntil(&xLastWakeTime, xDelay1s);
  }
}

void Task3( void *pvParameters)
{
  const TickType_t xDelay200ms = pdMS_TO_TICKS (200); 
  TickType_t xLastWakeTime; 
  /*variable to save the current tick count, it has to be initialized to the 
   *current tick count before it is used for the first time,then with the  
   *function vTaskDelayUntil is updated atomatically
   */
   xLastWakeTime = xTaskGetTickCount();
 
  //Converts time in ms to the same time in system ticks
  while(1)
  {
    vTaskDelay(xDelay200ms);
    digitalWrite(LED, LOW); //Switch off LED
    /* Delay for a period. A call to vTaskDelay() is used which places
       the task into the Blocked state until the delay period has expired.*/
    vTaskSuspend(TaskHandle_3);
  }
  
}



void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);   //Set pin as output
  SensorQueueS = xQueueCreate(10, sizeof( struct Accelerometer));
  if(  SensorQueueS != NULL){   //Create tasks only if the queue is created succesfully
      xTaskCreate( Task1, /* Pointer to the function that implements the task. */
               "Task 1",/* Text name for the task. This is to facilitate
                           debugging only. */
               1000, /* Stack depth - small microcontrollers will use much
                        less stack than this. */
               NULL, /* This example does not use the task parameter. */
               1, /* This task will run at priority 1. */
               NULL ); /* This example does not use the task handle. */
      xTaskCreate(Task2, "Task 2", 1000, NULL, 1, NULL);
      xTaskCreate(Task3, "Task 3", 1000, NULL, 1, &TaskHandle_3); 
  }
}

void loop() {
}
