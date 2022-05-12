#include <16f877.h>
#FUSES NOWDT, PUT, HS, NOPROTECT, NOLVP
#USE DELAY(CLOCK=20M) 
#include <tv_lcd_16x2.c>
#include <tv_matran_phim.c>
#include <tv_stuff.c>

//CONST UNSIGNED CHAR HANG2[16]={"ERROR        "};

void main ()
{
   unsigned int16 mp,so1,so2,so3,t;
   int8 n0=0;
   int8 pt1,pt2;
   
   set_tris_b(0xf0);
   set_tris_d(0x00);
   port_b_pullups(0xf0);
   lcd_setup();
   lcd_command(addr_line1); delay_us(10);
   so1=so2=t=0x00;
   while (true)
   {
      mp=key_4x4();
      switch(mp)
      {
         case 0 ://AC
         lcd_command(clear_display);
         break;
         
         case 1 ://1
         t=t*10+1;
         lcd_data(0x31);delay_us(20);
         break;
         case 2 ://4
         t=t*10+4;
         lcd_data(0x34);delay_us(20);
         break;
         case 3 ://7
         t=t*10+7;
         lcd_data(0x37);delay_us(20);
         break;
         case 4 ://0
         t=t*10+0;
         lcd_data(0x30);delay_us(20);
         break;
         case 5 ://2
         t=t*10+2;
         lcd_data(0x32);delay_us(20);
         break;
         case 6 ://5
         t=t*10+5;
         lcd_data(0x35);delay_us(20);
         break;
         case 7 ://8
         t=t*10+8;
         lcd_data(0x38);delay_us(20);
         break;
         case 9 ://3
         t=t*10+3;
         lcd_data(0x33);delay_us(20);
         break;
         case 10 ://6
         t=t*10+6;
         lcd_data(0x36);delay_us(20);
         break;
         case 11 ://9
         t=t*10+9;
         lcd_data(0x39);delay_us(20);
         break;
         
         
         
         
         case 12 ://cong
         lcd_data(0x2b);
         if (n0==0) {so1=t;n0=1;pt1=1;}
         else {so2=t;pt2=1;}
         t=0x00;
         break;
         case 13 ://tru
         lcd_data(0x2d);
         if (n0==0) {so1=t;n0=1;pt1=2;}
         else {so2=t;pt2=2;}
         t=0x00;
         break;
         case 14 ://nhan
         lcd_data(0x2a);
         if (n0==0) {so1=t;n0=1;pt1=3;}
         else {so2=t;pt2=3;}
         t=0x00;
         break;
         case 15 ://chia
         lcd_data(0x2f);
         if (n0==0) {so1=t;n0=1;pt1=4;}
         else {so2=t;pt2=4;}
         t=0x00;
         break;
         
      
         
         case 8 ://=
         {
            so3=t;
            lcd_command(addr_line2);
            unsigned int16 a,r1;
            
            if      (pt1==1 && pt2==1)
            {
               a=so1+so2+so3;
               HIENTHIKQ(a,0x1,0);
            }
            else if (pt1==1 && pt2==2)
            {
               if((so1+so2) > so3) a=so1+so2-so3;
               else 
                  {
                     lcd_data(0x2d);
                     a=so3-(so1+so2);
                  }
               HIENTHIKQ(a,0x1,0);
            }
            else if (pt1==1 && pt2==3)
            {
               a=so1+so2*so3;
               HIENTHIKQ(a,0x1,0);
            }
            else if (pt1==1 && pt2==4)
            {
               r1=so1*so3+so2;
               a=r1/so3;
               HIENTHIKQ(a,so3,r1%so3);
            }
            
            
            else if (pt1==2 && pt2==1)
            {
              if((so1+so3) > so2) a=so1+so3-so2;
               else 
                  {
                     lcd_data(0x2d);
                     a=so2-(so1+so3);
                  }
               HIENTHIKQ(a,0x1,0); 
            }
            else if (pt1==2 && pt2==2)
            {
               if((so2+so3) < so1) a=so1-so2-so3;
               else 
                  {
                     lcd_data(0x2d);
                     a=(so2+so3)-so1;
                  }
               HIENTHIKQ(a,0x1,0);
            }
            else if (pt1==2 && pt2==3)
            {
               if(so1 > (so2*so3)) a=so1-(so2*so3);
               else 
                  {
                     lcd_data(0x2d);
                     a=(so2*so3)-so1;
                  }
               HIENTHIKQ(a,0x1,0);   
            }
            else if (pt1==2 && pt2==4)
            {
               if((so1*so3) > so2) r1=so1*so3-so2;
               else 
                  {
                     lcd_data(0x2d);
                     r1=so2-(so1*so3);
                  }
               a=r1/so3;   
               HIENTHIKQ(a,so3,r1%so3);
            }
            
            else if (pt1==3 && pt2==1)
            {
               a=so1*so2+so3;
               HIENTHIKQ(a,0x1,0);
            }
            else if (pt1==3 && pt2==2)
            {
               if((so1*so2) >so3) a=so1*so2-so3;
               else
               {
                  lcd_data(0x2d);
                  a=so3-so1*so2;
               }
               HIENTHIKQ(a,0x1,0);
            }
            else if (pt1==3 && pt2==3)
            {
               a=so1*so2*so3;
               HIENTHIKQ(a,0x1,0);
            }
            else if (pt1==3 && pt2==4)
            {
               r1=so1*so2;
               a=r1/so3;
               HIENTHIKQ(a,so3,r1%so3);
            }
            
            
            else if (pt1==4 && pt2==1)
            {
               r1=so1+so3*so2;
               a=r1/so2;
               HIENTHIKQ(a,so2,r1%so2);
            }
            else if (pt1==4 && pt2==2)
            {
               if(so1 > so3*so2) r1=so1-so2*so3;
               else
               {
                  lcd_data(0x2d);
                  r1=so3*so2-so1;
               }
               a=r1/so2;
               HIENTHIKQ(a,so2,r1%so2);
            }
            else if (pt1==4 && pt2==3)
            {
               r1=so1*so3;
               a=r1/so2;
               HIENTHIKQ(a,so2,r1%so2);
            }
            else if (pt1==4 && pt2==4)
            {
               r1=so2*so3;
               a=so1/r1;
               HIENTHIKQ(a,r1,so1%r1);
            }
            
                
            so1=so2=so3=t=n0=0x00;
         }
         break;
         
         default:
         break;
      }
   }
}
