#include <16F886.h>
#device ADC=10
#fuses HS,NOWDT,NOPROTECT,NOLVP 
#use delay(clock=20000000)

#use rs232(baud=312500, xmit=PIN_C6, rcv=PIN_C7,stop=2)
#define TN 0x07e2  // so may 2017
#bit TR1EN = 0x10.0

#byte porta= 0x05
#byte portb= 0x06
#byte portc= 0x07

#bit rin  = portb.0
#bit ntout  = portb.6
#bit tout  = portb.7


#bit close= portc.0
#bit open  = portc.1

#bit clktest  = portc.5
#bit ring  = portc.3
#bit sent  = portc.4


int8 header_down1[6]={1,0,1,1,0,1};
int8 header_up1[6]={0,1,0,0,1,0};

int8 synch_down[6]={0,0,0,1,1,1};
int8 synch_up[6]={1,1,1,0,0,0};

int1 yes=1,no=0,send_flag=0,receive_flag=0,send_parity;

int8 device_flag=0,ncom=0,ip=0,iq;

int8 rcv_parity1,rcv_parity2,check_parity;
int8 buffer[3],send_data[2],send_data2[40],nsend_data2[40],bufcom[2]; 
float ft=0;
int8 dem=0; 

int8 index,i,j,ocflag=0,nn=0,nt=0;
int16 word[48],ad_value[8],subword[20];//,adtemp[8]={0,0,0,0,0,0,0,0};
int16 phaseR=65475,sendckl=65468,revclk=65356,temp3;
int16 index4,index5,index6,index7,nave=200;
int32 tint=0,text=0,xin=0,yin=0;

const int16 info[] = {0x0014,0xc0aa,0x3f55,0xf731,0x8000,0x0000,0xffff,0x08ce,0x1010,TN,4};// 11 words info so may skpd 2017, version 4
const int16 msctest[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,
                       50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68};
void decode();


#INT_TIMER1 

void ngat_timer1(void)
{
TR1EN=0;
 
 //--------------- ------------------------- 
 if(send_flag)           // phat dia chi va cw
 {
   
   
   SET_TIMER1(65470);
   TR1EN=1;
      
   if(dem<40) {               //gui 40 1/2 bit data coded manchester
        tout=send_data2[dem];
        ntout=nsend_data2[dem];//!tout;     
   }
    dem++;
    
    if(dem==41)  {                      //tra duong truyen
        tout=no;
        ntout=no; 
               
     }        
     
     if(dem>42)  {                         //dung 2 chu ky
         tout = no;
         ntout=no;
         TR1EN=0;  //stop bo dem
         send_flag=0;     
         dem=0;
        
     }         
   }
   
//   ------------------------------------------------------
  
  else {                                  // nhan du lieu
     
    
     SET_TIMER1(revclk);                 //46.85us
     
     TR1EN=1; 
     open=0;  //khanh
    
      
     
     clktest=yes;
     clktest=no;
     dem++;
     
     if(dem<20)  {            //doc 20 bit gom 3 synch + 16 addr va cw + parity 
         shift_left(buffer,3,rin);  //nhan tung bit
         rcv_parity1^= rin;
             
      
      }
      else     {
         rcv_parity2=rin;               //input(PIN_B0);
         TR1EN = 0;
         receive_flag=1;                   // nhan xong du lieu
         dem=0;   
               
      }  
      
    }        
                
}


//==========================================
#INT_EXT          // ra vao ham ngat mat 10us
Void ngat_ngoai() 
{
  
   disable_interrupts(INT_EXT);
   
   TR1EN = 0;  
   
    
   SET_TIMER1(phaseR);                  //Doc bit dau tien tai 35us
   
   TR1EN = 1;                             // bat timer   
   send_flag=0;                            // cho phep nhan du lieu
   dem=0;
   ring = no;   
   
   clktest=yes;
   clktest=no;
   
   
   
}

#INT_RDA
void serial_isr()
{

bufcom[ip]=fgetc();

if(ip){
   if(ncom < 48) {
      word[ncom] = make16(bufcom[1],bufcom[0]);
   }
   else {
      subword[ncom-48]=make16(bufcom[1],bufcom[0]);
   }
   ncom++;
}


ip = (ip+1)%2;
if(ncom == 60) { 
   ncom=0;
   ip=0;
}
}

//======================================================
void access_data()
{
     
   disable_interrupts(INT_EXT );    
                                     
   dem=0;
   send_flag=1;
   sent = 0; 
   SET_TIMER1(65530);  
   
   TR1EN=1;
 
}


void decode()
{
    
      
      if(rcv_parity1==rcv_parity2){
         check_parity=1;
      }
      else   check_parity=0;
      
      temp3 = make16(buffer[1],buffer[0]);    // nhan du so word tu may gieng
      
      if(temp3 == 0x1000)            device_flag   = 1; //truy xuat du lieu 48 word tha
      else if(temp3 == 0x100a)       device_flag   = 2; //mo cang trong 40s     
      else if(temp3 == 0x1005)       device_flag   = 3; //dong cang trong 40s    
      
      else if(temp3 == 0x10a0)       device_flag   = 4; //mo cang trong 40s va gui du lieu 
      else if(temp3 == 0x1050)       device_flag   = 5; //dong cang trong 40s va gui du lieu 
      
          
      else if(temp3 == 0x105e)       device_flag   = 6; //kiem tra duong truyen 11 words(get info)
     
      else if(temp3 == 0x105f)       device_flag   = 7; //kiem tra duong truyen 48 words
      
//!      else {
//!         open=-open;
//!         close=-close;
//!      }
//!      
      //else if(open) open = no;
}
//=================================================== chuan bi du lieu gui

void prepare_data1(void)
{
  
   send_parity=1;
   
   for(index=0;index<6;index++)   
   {
      send_data2[index] = synch_up[index]; 
   }

   for(index=6;index<38;index = index+2)  // bat dau tu sau Synch :dem =6
   {
      send_data2[index + 1] = shift_left(send_data,2,0);  // data nam o nua bit sau (index+1)
      send_data2[index]   = !send_data2[index - 1] ;        // dao du lieu cua bit truoc (index-1)    
     
      send_parity = send_parity ^ send_data2[index + 1];
   }
   send_data2[38] = !send_parity;
   send_data2[39] = send_parity;
   
}

void prepare_data()
{
   int8 i;
   int8 clk=1,parity=1,bt;
   
   for(i=0;i<40;i++)
   {
      if (i<6) send_data2[i] = clk^header_up1[i];            // load Synch
      else if (i<38){                                        // load data
         if((i+1)%2) bt = shift_left(send_data,2,0);
         send_data2[i] = clk^bt;
         parity ^= bt;
      }
      else      send_data2[i] = clk^parity;             // load parity

      clk ^=1;
      nsend_data2[i]=!send_data2[i];
   }


}

void GetADChannels()
{
            
      set_adc_channel(0);  //headv
      delay_us(10);
      ad_value[0]=read_adc();
      
      set_adc_channel(1);  //5V
      delay_us(10);
      ad_value[1]=read_adc(); 
      
      set_adc_channel(2);  //15v
      delay_us(10);
      ad_value[2]=read_adc();
      
      set_adc_channel(3);  //T-int
      delay_us(10);
      tint += read_adc();
      
      set_adc_channel(4);  //T-ext
      delay_us(10);
      text +=read_adc();
          
      set_adc_channel(10);  //Xin
      delay_us(10);
      xin +=read_adc();
      
      set_adc_channel(8);  //Yin
      delay_us(10);
      yin +=read_adc();
      
      nt++;
      
      if(nt>=nave){
         ft = tint;
         ft /= nave;
         ft *=100;
         ad_value[3] = ft;
         
         ft = text;
         ft /= nave;
         ft *=100;
         ad_value[4] = ft;
         
         ft = xin;
         ft /= nave;
         ft *=10;
         ad_value[5] = ft;
         
         ft = yin;
         ft /= nave;
         ft *=10;
         ad_value[6] = ft;
         
         tint=0;
         text=0;
         xin=0;
         yin=0;
         nt=0;
         
         
      }
      
      set_adc_channel(9);  //res
      delay_us(10);
      ad_value[7]= 601; //read_adc(); MSC-60 so 601
           
   
}

/*void GetADCs()
{
            
      set_adc_channel(0);  //headv
      delay_us(10);
      adtemp[0] +=read_adc();
      
      set_adc_channel(1);  //5V
      delay_us(10);
      adtemp[1] +=read_adc(); 
      
      set_adc_channel(2);  //15v
      delay_us(10);
      adtemp[2] +=read_adc();
      
      set_adc_channel(3);  //T-int
      delay_us(10);
      adtemp[3] += read_adc();
      
      set_adc_channel(4);  //T-ext
      delay_us(10);
      adtemp[4] +=read_adc();
                
      set_adc_channel(10);  //Xin
      delay_us(10);
      adtemp[5] +=read_adc();
      
      set_adc_channel(8);  //Yin
      delay_us(10);
      adtemp[6] +=read_adc();
      
      set_adc_channel(9);  //res
      delay_us(10);
      adtemp[7] +=read_adc();
       nt++;
      
      if(nt>49){
         for(iq=0;iq<8;iq++){
            ft = adtemp[iq];
            ft /= 50;
            if((iq==3)||(iq==4)){
               ft *=100;
            }
         
            ad_value[iq]=ft;
            adtemp[iq]=0;
        }
         
         nt=0;
                  
      }    
      
}*/

void update_data()
{
     // GetADChannels();  //lay cac kenh AD phu tro va Xin, Yin
      
      ft = ad_value[0];
      ft *= 0.20431;
      
      
      ad_value[0] = ft*10; // headv 1 so le a=0.190972 b=7.6
      
      ft = ad_value[1];
      ft *= 0.012128;
      
      
      ad_value[1] = ft*100; // 5v 2 so le a=0.001125 b=4.565
      
      ft = ad_value[2];
      ft *= 0.026145;
      
      
      ad_value[2] = ft*100; // 15v 2 so le a=0.001125 b=4.565
      
      ft = ad_value[3];
      ft *= 1;
      ft += 0;
      
      ad_value[3] = ft; // t_int 1 so le a=0.001125 b=4.565
      
      ft = ad_value[4];
      ft *= 1;
      ft += 0;
      
      ad_value[4] = ft; // t_ext 1 so le a=0.001125 b=4.565
      
       
      
     // for(i=60;i<68;i++){ 
    //     subword[i-48] = ad_value[i-60];
    //  }
      for(i=0;i<8;i++){ 
         subword[12+i] = ad_value[i];
      }
      
  
    
}





//====================================================
void main()
{

set_tris_b(0x3f);
set_tris_c(0x80);

receive_flag=0;
dem=0;

tout = no;
ntout = no;
close =no;
open=no;
open=1;            //khanh


ring = yes;
sent = yes;

clear_interrupt(INT_EXT);
enable_interrupts(INT_TIMER1);
enable_interrupts(GLOBAL);
enable_interrupts(INT_RDA);
enable_interrupts(INT_EXT);
EXT_INT_EDGE(H_TO_L);
SETUP_TIMER_1(T1_INTERNAL|T1_DIV_BY_1 );
TR1EN = 0; 

setup_adc(adc_clock_internal);
setup_adc_ports(sAN0|sAN1|sAN2|sAN3||sAN4|sAN8|sAN9|sAN10|sAN11);

//setup_ccp1(CCP_PWM);   // Configure CCP2 as a PWM

          //   The cycle time will be (time+1)*t2div(1/clock)*4

          //  T =  (1/20000000)*4*1*250 =  50 us or 20 khz

//setup_timer_2(T2_DIV_BY_1, 249, 1);
//set_pwm1_duty(128);           //    value*t2div*(1/clock)*4      value=128 

ncom=0;
ip=0;
putc(0x55); //doc du lieu 40 cang dau tu mcu daq lan dau tien
delay_ms(6);
while(1)
{

//-----------------------------------------------

  if(receive_flag)
{
 receive_flag=0;

   decode();  
   
    if(device_flag)       // nhan du so word tu may gieng
    {
               
         if (device_flag == 1){   //truy xuat du lieu
            open = no;
            close = no;
            delay_us(2000);
            for(j=0;j<48;j++){   // msc 48 words
               send_data[1]= word[j]>>8;
               send_data[0]= word[j];
               prepare_data();
               access_data();         
            }
            for(j=0;j<20;j++){   // msc 48 words
               send_data[1]= subword[j]>>8;
               send_data[0]= subword[j];
               prepare_data();
               access_data();         
            }
         }
         else if (device_flag == 2){   //mo cang trong 40s va gui du lieu tra loi
            open = yes;
            close = no;
            //if(!ocflag) {index7 = 0; nn=0;}
            //ocflag =1;
           
            delay_us(2000);
            for(j=0;j<48;j++){   // msc 48 words
               send_data[1]= word[j]>>8;
               send_data[0]= word[j];
               prepare_data();
               access_data();         
            }
            for(j=0;j<20;j++){   // msc 48 words
               send_data[1]= subword[j]>>8;
               send_data[0]= subword[j];
               prepare_data();
               access_data();         
            }
         }
         
         else if (device_flag == 3){   //dong cang trong 40s va gui du lieu tra loi
            open = no;
            close = yes;
            //if(!ocflag) {index6 = 0;nn=0;}
            //ocflag =1;
                     
            delay_us(2000);           
            for(j=0;j<48;j++){   // msc 48 words
               send_data[1]= word[j]>>8;
               send_data[0]= word[j];
               prepare_data();
               access_data();         
            }
            for(j=0;j<20;j++){   // msc 48 words
               send_data[1]= subword[j]>>8;
               send_data[0]= subword[j];
               prepare_data();
               access_data();         
            }
         }
         else if (device_flag == 4){   //mo cang trong 40s 
            open = yes;
            close = no;
           // if(!ocflag) {index7=0;nn=0;}
           // ocflag =1;
            
                      
            delay_us(2000);
            for(j=0;j<48;j++){   // msc 48 words
               send_data[1]= word[j]>>8;
               send_data[0]= word[j];
               prepare_data();
               access_data();         
            }
            for(j=0;j<20;j++){   // msc 48 words
               send_data[1]= subword[j]>>8;
               send_data[0]= subword[j];
               prepare_data();
               access_data();         
            }
            
         }
         
         else if (device_flag == 5){   //dong cang trong 40s 
            open = no;
            close = yes;
           // if(!ocflag) {index6 = 0;nn=0;}
           // ocflag =1;
            
            //if(!ocflag) {index6 = 0;nn=0;}
            //ocflag =1;
                     
            delay_us(2000);           
            for(j=40;j<48;j++){   // msc 48 words
               send_data[1]= word[j]>>8;
               send_data[0]= word[j];
               prepare_data();
               access_data();         
            }
            for(j=0;j<20;j++){   // msc 48 words
               send_data[1]= subword[j]>>8;
               send_data[0]= subword[j];
               prepare_data();
               access_data();         
            }
         }
         
         
         else if (device_flag == 6){                  //truy xuat trang thai 11
            
            delay_us(2000);
            for(j=0;j<11;j++){   //skpd 11 words
               send_data[1]= info[j]>>8;
               send_data[0]= info[j];
            
               prepare_data();
               access_data();         
            }
         }
         
         else if (device_flag == 7){                  //truy xuat trang thai 68
            
            delay_us(2000);
            for(j=0;j<68;j++){   //skpd 11 words
               send_data[1]= msctest[j]>>8;
               send_data[0]= msctest[j];
            
               prepare_data();
               access_data();         
            }
         }
         device_flag=0;
                  
    }
      
      delay_ms(1);
      
      clear_interrupt(INT_EXT);
      enable_interrupts(INT_EXT);
      ncom=0;
      ip=0;
      putc(0x55);
      delay_ms(6);
      delay_ms(20);   //khanh
      update_data();
      open=1;   //khanh
      
    
}
//=======================================================

  GetADChannels();
  
  if (!ring) {
        
          index4++;
         if(index4>500)
         {
         ring=yes;                       //tat led hoi dap
         index4=0;
         }
      }
  if (!sent) {
         
         index5++;
         if(index5 > 500)
         {
         sent=yes;                       //tat led hoi dap
         index5=0;
         }
      }
  /*if (open) {
        
          index7++;
         if(index7>1000)         {
            nn++;
            index7=0;
            if(nn>140){
               //open = no;                       //tat led hoi dap
               
               ocflag =0;
               nn=0;
            }
         }
      }
  if (close) {
         
         index6++;
         if(index6 > 1000){
            nn++;
            index6=0;
            if(nn>140){
               //close=no;                       //tat led hoi dap
               
               ocflag =0;
               nn=0;
            }
         }
      }   */
//-------------------------------------
}

}
