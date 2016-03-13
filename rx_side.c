
// Header Files
#include "mbed.h" 
#include "cmsis_os.h" 

DigitalOut led1(LED1); 

DigitalOut led2(LED2); 

CAN can1(p9, p10); //Initialise P9 as RXD and P10 as TXD of CAN 

CANMessage msg; 

Serial pc(USBTX, USBRX);// USB port used as serial port. 

void tempdisp_thread(void const *args) { 
		while (true) { 
					// Signal flags that are reported as event are automatically cleared 

					osSignalWait(0x1, osWaitForever);//Wait for singal 0x1 and oswaitforever is the time out value 

					pc.printf("thread wakeup\n"); 

					pc.printf("the temperature received is : %f\n\r",msg);//Displays the received temperature on Terminal 

					osDelay(1000);//1000 msec delay 
					} 
				} 

osThreadDef(tempdisp_thread, osPriorityHigh, DEFAULT_STACK_SIZE);//Thread Defination 

int main() { 

osThreadId t1 = osThreadCreate(osThread(tempdisp_thread), NULL);// Create thread t2 

while (true) { 
	
			if (can1.read(msg)) //check if the message is received from the CAN bus 

			{
				osSignalSet(t1, 0x1);//signal the display thread to wake up and dispplay the message 

			} 

			led1 = !led1; 

			osDelay(500); 

			} 

}