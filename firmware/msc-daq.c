
#include <16f886.h>
#device ADC=10
#fuses HS, NOLVP, NOWDT, NOPROTECT
#use   delay (clock=20000000) //Use built-in function: delay_ms() & delay_us()

#use rs232(baud=312500,parity=e,xmit=PIN_C6, rcv=PIN_C7)

#bit TR1EN = 0x10.0
#byte portc = 0x07

#bit portc1 = portc.0
#bit portc2 = portc.2
#bit portc3 = portc.3
#bit portc4 = portc.4
#bit portc5 = portc.5

int1 yes=1,no=0;
int8 send_com=0,dd=0,ncom=0;


int16 ad_value[8],ntimer=65455; 
unsigned int16 buf[48],buffer[16];

int8 i,j;

#INT_TIMER1
void timer1_isr(void)
{
   set_timer1(ntimer);            //50us -> 20khz
   //portc5 ^= yes;
    //portc5 = portc4;
   
}

#INT_RDA
void uart_isr()
{
   
   dd = fgetc();

   if(dd == 0x55) send_com=1; 
   if(dd == 0xaa) send_com=2;
  
  
   
   //portc4 ^= yes;
   
         
}

void GetADChannels()
{
      
      set_adc_channel(4);  
      delay_us(6);
      ad_value[0]=read_adc();
      
      
      set_adc_channel(3);  
      delay_us(6);
      ad_value[1]=read_adc();
      
      
      set_adc_channel(2);  
      delay_us(6);
      ad_value[2]=read_adc();
      
      
      set_adc_channel(1);  
      delay_us(6);
      ad_value[3]=read_adc();
      
            
      set_adc_channel(0);  
      delay_us(6);
      ad_value[4]=read_adc();
      
      
      set_adc_channel(13);  
      delay_us(6);
      ad_value[5]=read_adc();
      
      
      set_adc_channel(11);  
      delay_us(6);
      ad_value[6]=read_adc();
      
      
      set_adc_channel(9);  
      delay_us(6);
      ad_value[7]=read_adc();
      
                  
}

void update_data()
{
portc3=no; portc2=no; portc1=no;        //kenh 0
GetADChannels();
for(i=0;i<8;i++){
   buf[i] = ad_value[i];
   
}
portc3=no; portc2=no; portc1=yes;      //kenh 1
GetADChannels();
for(i=0;i<8;i++){
   buf[8+i] = ad_value[i];
  
}
portc3=no; portc2=yes; portc1=no;      //kenh 2
GetADChannels();
for(i=0;i<8;i++){
   buf[16+i] = ad_value[i];
   
}
portc3=no; portc2=yes; portc1=yes;      //kenh 3
GetADChannels();
for(i=0;i<8;i++){
   buf[24+i] = ad_value[i];
   
}
portc3=yes; portc2=no; portc1=no;      //kenh 4
GetADChannels();
for(i=0;i<8;i++){
   buf[32+i] = ad_value[i];
   
}
portc3=yes; portc2=no; portc1=yes;      //kenh 5
GetADChannels();
for(i=0;i<8;i++){
   buf[40+i] = ad_value[i];
   
}
portc3=yes; portc2=yes; portc1=no;      //kenh 6
GetADChannels();
for(i=0;i<8;i++){
   buffer[i] = ad_value[i];
   
}
portc3=yes; portc2=yes; portc1=yes;      //kenh 7
GetADChannels();
for(i=0;i<8;i++){
   buffer[8+i] = ad_value[i];
   
}  
}

void initdata()
{
   for(i=0;i<48;i++){
      
      buf[i]=0;
      
   }  
   for(i=0;i<16;i++){
      
      buffer[i]=0;
      
   }
     

}

void simudata()
{
   for(i=0;i<48;i++){
      
      buf[i]++;
      
   }  
   for(i=0;i<16;i++){
      
      buffer[i]--;
      
   }
     

}

void send_data()
{
if(send_com == 2) 
   for(i=0;i<48;i++){
      putc(buf[i]);
      putc(buf[i]>>8);
   }
else  {
   for(i=0;i<48;i++){
      
      putc(buf[i]);
      putc(buf[i]>>8);
     
     }
   for(i=0;i<12;i++){
      putc(buffer[i]);
      putc(buffer[i]>>8);
     }
   }
   
}
   

void main(void)
{
   set_tris_c(0xb0);          //#10000000

   
   enable_interrupts(INT_RDA);
   //enable_interrupts(INT_TIMER1);
   enable_interrupts(GLOBAL);
   SETUP_TIMER_1( T1_INTERNAL | T1_DIV_BY_1 ); // setb tr1: 1 clock = 1/6 us
   set_timer1(ntimer);            //50us -> 20khz
   TR1EN=0;
   
   setup_adc(adc_clock_internal);
   setup_adc_ports(sAN0|sAN1|sAN2|sAN3||sAN4|sAN9|sAN11|sAN13);
   setup_ccp2(CCP_PWM);   
   
          // Configure CCP2 as a PWM

          //   The cycle time will be (time+1)*t2div(1/clock)*4

          //     (1/20000000)*4*1*256 =  51.2 us or 19.5 khz

   setup_timer_2(T2_DIV_BY_1, 255, 1);
   set_pwm2_duty(128);      
   initdata();
   
while(true)  {
     
   if(send_com==1) {
      send_com=0;
      //portc5 ^= yes;
      //initdata();
      update_data();
      //simudata();
      send_data();  
    
 }
 
}

}

