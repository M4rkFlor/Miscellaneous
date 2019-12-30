/* This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 */
/* First function is always called (by boot sector) so stack frame will auto return and prevent unwated code to be executed*/
#include "../drivers/screen.h"
#include "util.h"

void Do_Nothing() {
}

void start() {
 
   monitor_clear();
   char c = 'c';
   monitor_put(c);
   char msg[] = "char * is the message";
   monitor_write(msg);
   char m2[] = "Hello,This is a realy Long Lorem Ispsm and should reach 64";
   monitor_write(m2);

   char sd[] = "Hello,This is a realy Long Lorem Ispsm and should reach 64";
   monitor_write(sd);
   char da[] = "Hello,This is a realy Long Lorem Ispsm and should reach 64";
   monitor_write(da);
   char bn[] = "Hello,This is a realy Long Lorem Ispsm and should reach 64";
   monitor_write(bn);
   char vb[] = "Hello,This is a realy Long Lorem Ispsm and should reach 64";
   monitor_write(vb);
   char sg[] = "Hello,This is a realy Long Lorem Ispsm and should reach 64";
   monitor_write(sg);
   char xy[] = "Hello,This is a realy Long Lorem Ispsm and should reach 64";
   monitor_write(xy);
   char fa[] = "Hello,This is a realy Long Lorem Ispsm and should reach 64";
   monitor_write(fa);
   char ze[] = "Hello,This is a realy Long Lorem Ispsm and should reach 64";
   monitor_write(ze);
   char ht[] = "Hello,This is a realy Long Lorem Ispsm and should reach 64";
   monitor_write(ht);
   char jy[] = "Hello,This is a realy Long Lorem Ispsm and should reach 64";
   monitor_write(jy);
   char yu[] = "Hello,This is a realy Long Lorem Ispsm and should reach 64";
   monitor_write(yu);
   char er[] = "Hello,This is a realy Long Lorem Ispsm and should reach 64";
   monitor_write(er);
   char we[] = "Hello,This is a realy Long Lorem Ispsm and should reach 64";
   monitor_write(we);
   char qw[] = "Hello,This is a realy Long Lorem Ispsm and should reach 64";
   monitor_write(qw);
   char fsd[] = "Hello,This is a realy Long Lorem Ispsm and should reach 64";
   monitor_write(fsd);
   char ns[] = "Hello,This is a realy Long Lorem Ispsm and should reach 64";
   monitor_write(ns);
   char hs[] = "Hello,This is a realy Long Lorem Ispsm and should reach 64";
   monitor_write(hs);

}