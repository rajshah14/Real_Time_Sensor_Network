
// Header Files
#include "mbed.h" 
#include "cmsis_os.h" 

// Initialize a pins to perform analog input and digital output fucntions 

AnalogIn ain(p20);//Take input from temperature sensor 

AnalogIn tin(p18);//Take input from IR led which detects the person 

DigitalOut led(LED1); 

CAN can1(p9, p10);//Initialise P9 as RXD and P10 as TXD of CAN 

CANMessage msg; 

Serial pc(USBTX, USBRX);// USB port used as serial port. 

float ADCdata; 

char temp; 

void tempsend_thread(void const *args) { 
	while (true) { 
				// Signal flags that are reported as event are automatically cleared 

				osSignalWait(0x1, osWaitForever);//Wait for singal 0x1 and oswaitforever is the time out value 

				ADCdata = (ain*5) * 100; 

				temp = ADCdata;//Convert the data to Character 

				can1.write(CANMessage (1337, &temp));//Send char a via can transmit buffer ,1337 is message ID to the Filter 

				pc.printf("the temperature tranmitted is : %d\n\r",msg); 

				osDelay(1000);//1000 msec delay 
				} 
	} 

	osThreadDef(tempsend_thread, osPriorityHigh, DEFAULT_STACK_SIZE);//Thread definition 

	int main() { 

	while (1){ 

	osThreadId t2 = osThreadCreate(osThread(tempsend_thread), NULL); // Create thread t2
	
	if (tin > 1)// check the presence of a person, if detected the voltage will be more than 1 else it is less than 1

	{ 

		osSignalWait(0x1, osWaitForever);// signal 0x1 to thread t2 so it wakes the thread 

		osDelay(500);// msec delay 
	} 

} 

}
