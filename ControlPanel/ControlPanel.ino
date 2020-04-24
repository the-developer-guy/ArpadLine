#define TASK_1_MS 1

void task_1_ms(void);

unsigned long systemTime = 0;
unsigned long counter_task_1_ms = 0;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  systemTime = millis();
  if(systemTime > counter_task_1_ms){
    counter_task_1_ms += TASK_1_MS;
    task_1_ms();
  }
}

void task_1_ms(void){
  
}
