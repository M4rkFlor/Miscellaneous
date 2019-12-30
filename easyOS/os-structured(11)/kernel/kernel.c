/* This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 */
/* First function is always called (by boot sector) so stack frame will auto return and prevent unwated code to be executed*/
void Do_Nothing() {
}

void start() {
    char* video_memory = (char*) 0xb8000;
    *video_memory = 'X';
}