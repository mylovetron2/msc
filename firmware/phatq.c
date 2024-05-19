#include <16F876a.h>
#device ADC=10
#fuses HS,NOWDT,NOPROTECT,NOLVP 
#use delay(clock=20000000)
#use rs232(baud=115200,parity=E, xmit=PIN_C6, rcv=PIN_C7)  

#bit TR1EN = 0x10.0

#byte portb= 0x06
#bit portc2= 0x07.2
#bit portc3= 0x07.3

#bit portb0=  portb.0
#bit portb1=  portb.1 
#bit portb2=  portb.2
#bit portb3=  portb.3
#bit portb4=  portb.4
#bit portb5= portb.5
#bit portb6=  portb.6
#bit portb7=  portb.7  
#define INT_RB5                   0x010B08

int8 header_down[4]={1,0,0,1}; 
int8 header_up[4]={0,1,1,0};

int8 header_down1[6]={1,0,1,1,0,1};
int8 synch_down[6]={0,0,0,1,1,1};

int8 flag_load,dd,dmt_flag=0,dmt1_flag=0,ncom=0;
int8  send_flag=0,receive_flag=0,rcv_parity,send_parity,rcv_complete,flag_com;
int8 temp,shift_EN,rcv_parity1,rcv_parity2,check_parity;
int8 buffer[3],send_data[2],receive_data[3]; 
int8 donvi,chuc,tram,nghin,chucnghin,tramnghin;
int8 dem=0,rcv_size,byte0,byte1,n_irc=0, send_en=0; 
int8 ck,data_bit,M_code,M_code0;
int8 buffer_com[8],index2,answer_EN,send_data2[40], index6;
int16 index0,index1,index4,index5,next_in,a,word[48],temp3,com_count,nclock=65353,nphase=64752,nn=0,aclock=65473,npgk=65455;//64750
void decode();
void access_data();
int1 no=0,yes=1;
//============================================================================== 


//==============================================================================
#INT_TIMER1

void ngat_timer1(void)
{
TR1EN=0;

   //Gui du lieu
   if(send_flag==1)           // phat dia chi va cw
   {
  
      //SET_TIMER1(65472);
      SET_TIMER1(aclock);
   
      TR1EN=1;
      if(dem<6)                           //gui header
      {
             
         //ck^=1;
         //M_code=ck^header_down1[dem]; //gui 3 bit synch
         
         //M_code = synch_down[dem];
         //M_code0 =M_code^1;         //dao bit
         portb1=synch_down[dem];//M_code;
         portb2=!portb1; //M_code0;    
      
      }
      else
      {
         if(dem<40)                         //gui data
         {                     
                                    
                  portb1=send_data2[dem];
                  portb2=!portb1;     
                                                                                                                   
         }
      }   
      dem++;
      if(dem==41)            //tra duong truyen
      {
           // ck=0;
            //M_code=0;
            portb1=no;
            portb2=no; 
              
      }
     
      if(dem>60)
      {
             TR1EN=0;  //stop bo dem
            
              send_flag=0;
              CLEAR_INTERRUPT(INT_EXT);
              enable_interrupts(INT_EXT);
              dem=0;
      }         
   }

   //Nhan du lieu
   else                                   
   {    
      SET_TIMER1(nclock);                 //47us
   
      TR1EN=1; 
      //portb3=0;
      portb3=yes;
      portb3=yes;
      portb3=no;
      dem++;
   
      if(dem<17)      
      { 
   
         shift_left(buffer,3,! portb0);  //phat qua cong dao=>nhan ve dao lai
         rcv_parity1^= ! portb0;
         
      }
      else
      {
         rcv_parity2=portb0;//input(PIN_B0);
         TR1EN = 0;
         receive_flag=1;               // nhan xong du lieu
         dem=0;   
         decode();
         
      }  
      if((buffer_com[0] == 0x38)||(buffer_com[0] == 0x3d)) 
         nphase = npgk;
   } 
             
                
}


//==========================================
#INT_EXT          // ra vao ham ngat mat 10us
Void ngat_ngoai() 
{
   if(rcv_size==0)     
   return;
   disable_interrupts(INT_EXT );
   dem=0;
   TR1EN = 0;  
   
   
   SET_TIMER1(nphase);                    //105us=65107//180us=64732
 
   TR1EN = 1;                             // bat timer   
   send_flag=0;                            // cho phep nhan du lieu
   portc3=no;                             //bat led  hoi dap 
   portb3=yes;
   portb3=yes;
   portb3=no;
   
}

#INT_RB
void rc_isr()
{
   
   if(portb5==yes)return;
   if(send_en==0)return;
  
   send_en=0;
   access_data();
   disable_interrupts(INT_RB);
   
}

#INT_RDA
void serial_isr()
{

   if (flag_load == 0) 
   {
      dd= fgetc();
      
      if((dd==0xdd) && (ncom == 0)){
         dmt_flag =1;
         dmt1_flag =0;
      
      }
      else if((dd==0xde) && (ncom == 0)){
         dmt1_flag =1;
         dmt_flag =0;
      
      }
      
      if(dmt_flag) {
         ncom++;
         if(ncom == 17)
         {
         ncom=0;
         dmt_flag=0;
         }
      }
      
      if(dmt1_flag) {
         ncom++;
         if(ncom == 3)
         {
         ncom=0;
         dmt1_flag=0;
         }
      }

      if((dd==0xCC) && (ncom == 0))
         {
            flag_load=1;
            next_in=0;
         }
      return;  
   }
   
   else 
   {  
      buffer_com[next_in] = fgetc(); // MSB truoc
      next_in++;   
   } 
   if(next_in==7)
   {
      flag_load = 0;
      //answer_EN=buffer_com[2];
      next_in=0;
      flag_com=1;      
   }  
 
   com_count=1;     
}



//======================================================
void access_data()
{
   int8 i;
   
   disable_interrupts(INT_EXT );    
   ck=0;                                  
   dem=0;
   send_flag=1;
   index1=0;   
   SET_TIMER1(65520);  
   
   TR1EN=1;
   portc2= no;    //led nhay hoi dap
   
   for(i=0;i<48;i++)   word[i]=0;              //xoa bo dem
   
   
}
//========================================
void decode()
{
   
      receive_data[0]=buffer[0];                 //  cat du lieu vao
      receive_data[1]=buffer[1];
        
      if(rcv_parity1==rcv_parity2){
      check_parity=1;
      }
      else   check_parity=0;
      
     
      temp3 = make16(receive_data[1],receive_data[0]);
      word[index1]=temp3;
      index1++;      
     
     
      if(index1 >= rcv_size) {
         rcv_complete=1;
         index1=0;
         
         rcv_size=0; //ko cho nhan
         //enable_interrupts(INT_RB5);
      }          // nhan du so word tu may gieng
     
      
          delay_us(100);
          CLEAR_INTERRUPT(INT_EXT);
          enable_interrupts(INT_EXT);
      
}
//=================================================== chuan bi du lieu gui

void prepare_data1(void)
{
  int i;
   send_parity=1;
   
   for(index6=6;index6<38;index6 = index6+2)  // bat dau tu sau header :dem =6
   {
      send_data2[index6 + 1] = shift_left(send_data,2,0);
      send_data2[index6]   = !send_data2[index6 + 1] ;       // data nam o nua bit sau (n+1)
     
      
      send_parity = send_parity ^ send_data2[index6 + 1];
   }
   send_data2[38] = !send_parity;
   send_data2[39] = send_parity;
   
   for(i=0;i<48;i++)   word[i]=0;
}

//===================================================   xu_li_lenh

//====================================================      gui_cong_com
void gui_cong_com()
{
 
   for(index2=0;index2<24;index2++)
   {
      putc(word[index2]);
      putc(word[index2]>>8);
   }
   putc(buffer_com[0]);
   putc(buffer_com[1]);                               //header
   //putc(0xf5);                            // footer    
   //port_b_pullups (true);
}



//====================================================
void main()
{

// shif en=1 truoc khj gui

set_tris_c(0xb0);
set_tris_b(0xf1);

//port_b_pullups (true);
portb1=no;
portb2=no; 
portb4=no; 
portb6=no; 
portb7=no; 
 
CLEAR_INTERRUPT(INT_EXT);
CLEAR_INTERRUPT(INT_TIMER1);
clear_interrupt(INT_RB);
enable_interrupts(GLOBAL);
enable_interrupts(INT_RDA);
enable_interrupts(INT_TIMER1);
enable_interrupts(INT_EXT);
enable_interrupts(INT_RB5);
EXT_INT_EDGE(H_TO_L);
SETUP_TIMER_1(T1_INTERNAL|T1_DIV_BY_1 );
TR1EN = 0;    

dem=0;
ck=0;
output_bit(PIN_B1,no);
shift_EN=0;
receive_flag=0;
next_in=0;
com_count=0;
buffer_com[0]=0x20;
buffer_com[1]=0x40;
buffer_com[2]=2;          //size
answer_EN=2;
portc3=yes;                       //tat led hoi dap
portc2=yes;     //tat led hoi dap

   while(1)
   {
      /*if(send_en){
         
         send_en=0;
         access_data();
      }  */
      
      if(flag_com)
      {      
         flag_com = 0;
         enable_interrupts(INT_RB5);
         //xu_li_lenh();  
         
         
         send_data[1]=buffer_com[0];
         send_data[0]=buffer_com[1];                     // data                   
         rcv_size=buffer_com[2];
         aclock = 0xffff;
         aclock -= buffer_com[3];
         nclock = 0xffff;
         nclock -= buffer_com[4];
         nphase = 64600;
         nphase += buffer_com[5];
         //nphase <<=8;
         npgk = 65535 - buffer_com[6];
         prepare_data1();
         send_en=1; 
         
         //access_data();
      }

      //-----------------------------------------------

      if(receive_flag)
      {
         receive_flag=0;

         //decode();  
         
         if(rcv_complete)       // nhan du so word tu may gieng
         {
               
               disable_interrupts(INT_EXT );
               rcv_complete=0;
               gui_cong_com();
               
               
         }
      }
      //=======================================================

         
      if (!portc3) {
            
               index4++;
               if(index4>500)
               {
               portc3=yes;                       //tat led hoi dap
               index4=0;
               }
      }
      if (!portc2) {
               
               index5++;
               if(index5 > 500)
               {
               portc2=yes;                       //tat led hoi dap
               index5=0;
               }
      }
         
      //-------------------------------------
   }

}




