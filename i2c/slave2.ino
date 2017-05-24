/*
SLAVE
*/

#include <Wire.h>     

// Tamanho do Pacote de Dados
#define PACKET_SIZE 16

// Variavel definida como uniao de caracteres
typedef union float2bytes_t   
{ 
  float f; 
  byte b[sizeof(float)]; 
}; 


const byte addrSlaveI2C =  21;  // I2C Slave address of this device
byte I2C_Packet[PACKET_SIZE];  // Array to hold data sent over I2C to main Arduino
bool printDataflag = false;

void setup()
{
  Serial.begin(9600);
  Serial.println(F("Initialize wire library for slave I2C"));
  Wire.begin(addrSlaveI2C);    // Initiate the Wire library and join the I2C bus 
  Wire.onRequest(wireRequestEvent); // Register a function to be called when a master requests data from this slave device. 
}


void loop()
{
 
  float2bytes_t f2b_temp; 
  float2bytes_t f2b_temp_bast;
  float2bytes_t f2b_umidade; 
  float2bytes_t f2b_corrente; 
  
  
  f2b_temp.f = 1111.11;
  f2b_temp_bast.f=2222.22;
  f2b_umidade.f=3333.33;
  f2b_corrente.f=4444.44;
  
  
  
  I2C_Packet[0] = f2b_temp.b[0];
  I2C_Packet[1] = f2b_temp.b[1];
  I2C_Packet[2] = f2b_temp.b[2];
  I2C_Packet[3] = f2b_temp.b[3];

  I2C_Packet[4] = f2b_temp_bast.b[0];
  I2C_Packet[5] = f2b_temp_bast.b[1];
  I2C_Packet[6] = f2b_temp_bast.b[2];
  I2C_Packet[7] = f2b_temp_bast.b[3];

  I2C_Packet[8] = f2b_umidade.b[0];
  I2C_Packet[9] = f2b_umidade.b[1];
  I2C_Packet[10] =f2b_umidade.b[2];
  I2C_Packet[11] =f2b_umidade.b[3];

  I2C_Packet[12] = f2b_corrente.b[0];
  I2C_Packet[13] = f2b_corrente.b[1];
  I2C_Packet[14] =f2b_corrente.b[2];
  I2C_Packet[15] =f2b_corrente.b[3];

 if (printDataflag)
  {
    PrintData(f2b_temp.f, f2b_temp_bast.f,f2b_umidade.f,f2b_corrente.f);
    printDataflag = false;
  }

}
// Send data to Master.  This is an interrupt driven event
void wireRequestEvent()
{
  // Send byte array from panStamp. Main Arduino will decode bytes
  Wire.write(I2C_Packet, PACKET_SIZE); 
    printDataflag = true;
} 

void PrintData( float temp,float tempbast,float umidade,float corrente )
{
  Serial.print("\t");
  Serial.print("Tempreratura: ");
  Serial.print(temp);
  Serial.print("    ");
 
  Serial.print("\t");
  Serial.print("Tempreratura Bastao: ");
  Serial.print(tempbast);
  Serial.print("    ");

  Serial.print("\t");
  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.print("    ");

  Serial.print("\t");
  Serial.print("Corrente: ");
  Serial.print(corrente);
  Serial.print("    ");
  Serial.println();

  delay(500);
}
