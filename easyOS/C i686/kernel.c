int global = 0x9991;
int globaluninitialzed=0;
int globalThree = 0x3;
int my_function() {
    int a=0x1549;
    int b=0x12345;
    int c=0x54329;
    a = a+b+c;
    if(a<0x54329||a>b){
        global = global + globaluninitialzed + globalThree;
        return global+c;
    }
    return 0xbaba;
}