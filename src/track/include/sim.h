#ifndef SIM_H
#define SIM_H

#define TINY_GSM_MODEM_SIM800
#define TINY_GSM_RX_BUFFER 1024 // Set RX buffer to 1Kb
#define SIM_RX 26
#define SIM_TX 27
#define SIM_PWRKEY 4
// #define SIM_RST 5 
#define SIM_PWR 23
#define SIM_BAUD 115200

void setupSim();

void sendSMS(char* message);

void makeCall(char* phoneNumber);

void publishData(char* data);


#endif
