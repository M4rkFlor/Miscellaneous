#include "keyboard.h"
#include "port-IO.h"
#include "screen.h"
#include "../kernel/util.h"

static void keyboard_callback(registers_t regs);

static void keyboard_callback(registers_t regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    u8 scancode = port_byte_in(0x60);
    char sc_ascii[64];
    int_to_ascii(scancode, sc_ascii);
    char keyscan[]="Keyboard scancode: ";
    kprint(keyscan);
    kprint(sc_ascii);
    char commaSpace[]=", ";
    kprint(commaSpace);
    print_letter(scancode);
    char newline[]="\n";
    kprint(newline);
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback); 
}

void print_letter(u8 scancode) {
            char ERROR[]="ERROR";
            char ESC[]="ESC";
            char one[]="1";
            char two[]="2";
            char three[]="3";
            char four[]="4";
            char five[]="5";
            char six[]="6";
            char seven[]="7";
            char eight[]="8";
            char nine[]="9";
            char zero[]="0";
            char dash[]="-";
            char plus[]="+";
            char backspace[]="Backspace";
            char TAB[]="Tab";
            char Q[]="Q";
            char W[]="W";
            char E[]="E";
            char R[]="R";
            char T[]="T";
            char Y[]="Y";
            char U[]="U";
            char I[]="I";
            char O[]="O";
            char P[]="P";
            char Lbracket[]="[";
            char Rbracket[]="]";
            char ENTER[]="ENTER";
            char LCtrl[]="LCtrl";
            char A[]="A";
            char S[]="S";
            char D[]="D";
            char F[]="F";
            char G[]="G";
            char H[]="H";
            char J[]="J";
            char K[]="K";
            char L[]="L";
            char semiColon[]=";";
            char hyphen[]="'";
            char otherhyphen[]="`";
            char LShift[]="LShift";
            char backslash[]="\\";
            char Z[]="Z";
            char X[]="X";
            char C[]="C";
            char V[]="V";
            char B[]="B";
            char N[]="N";
            char M[]="M";
            char comma[]=",";
            char period[]=".";
            char fSlash[]="/";
            char Rshift[]="Rshift";
            char KeypadStar[]="Keypad *";
            char LAlt[]="LAlt";
            char Spc[]="Spc";
                char UKD[]="Unknown key down";
                char KU[]="key up ";
                char UKU[]="Unknown key up";
    switch (scancode) {
        case 0x0:
            kprint(ERROR);
            break;
        case 0x1:
            kprint(ESC);
            break;
        case 0x2:
            kprint(one);
            break;
        case 0x3:
            kprint(two);
            break;
        case 0x4:
            kprint(three);
            break;
        case 0x5:
            kprint(four);
            break;
        case 0x6:
            kprint(five);
            break;
        case 0x7:
            kprint(six);
            break;
        case 0x8:
            kprint(seven);
            break;
        case 0x9:
            kprint(eight);
            break;
        case 0x0A:
            kprint(nine);
            break;
        case 0x0B:
            kprint(zero);
            break;
        case 0x0C:
            kprint(dash);
            break;
        case 0x0D:
            kprint(plus);
            break;
        case 0x0E:
            kprint(backspace);
            break;
        case 0x0F:
            kprint(TAB);
            break;
        case 0x10:
            kprint(Q);
            break;
        case 0x11:
            kprint(W);
            break;
        case 0x12:
            kprint(E);
            break;
        case 0x13:
            kprint(R);
            break;
        case 0x14:
            kprint(T);
            break;
        case 0x15:
            kprint(Y);
            break;
        case 0x16:
            kprint(U);
            break;
        case 0x17:
            kprint(I);
            break;
        case 0x18:
            kprint(O);
            break;
        case 0x19:
            kprint(P);
            break;
		case 0x1A:
			kprint(Lbracket);
			break;
		case 0x1B:
			kprint(Rbracket);
			break;
		case 0x1C:
			kprint(ENTER);
			break;
		case 0x1D:
			kprint(LCtrl);
			break;
		case 0x1E:
			kprint(A);
			break;
		case 0x1F:
			kprint(S);
			break;
        case 0x20:
            kprint(D);
            break;
        case 0x21:
            kprint(F);
            break;
        case 0x22:
            kprint(G);
            break;
        case 0x23:
            kprint(H);
            break;
        case 0x24:
            kprint(J);
            break;
        case 0x25:
            kprint(K);
            break;
        case 0x26:
            kprint(L);
            break;
        case 0x27:
            kprint(semiColon);
            break;
        case 0x28:
            kprint(hyphen);
            break;
        case 0x29:
            kprint(otherhyphen);
            break;
		case 0x2A:
			kprint(LShift);
			break;
		case 0x2B:
			kprint(backslash);
			break;
		case 0x2C:
			kprint(Z);
			break;
		case 0x2D:
			kprint(X);
			break;
		case 0x2E:
			kprint(C);
			break;
		case 0x2F:
			kprint(V);
			break;
        case 0x30:
            kprint(B);
            break;
        case 0x31:
            kprint(N);
            break;
        case 0x32:
            kprint(M);
            break;
        case 0x33:
            kprint(comma);
            break;
        case 0x34:
            kprint(period);
            break;
        case 0x35:
            kprint(fSlash);
            break;
        case 0x36:
            kprint(Rshift);
            break;
        case 0x37:
            kprint(KeypadStar);
            break;
        case 0x38:
            kprint(LAlt);
            break;
        case 0x39:
            kprint(Spc);
            break;
        default:
            /* 'keuyp' event corresponds to the 'keydown' + 0x80 
             * it may still be a scancode we haven't implemented yet, or
             * maybe a control/escape sequence */
            if (scancode <= 0x7f) {
                kprint(UKD);
            } else if (scancode <= 0x39 + 0x80) {
                kprint(KU);
                print_letter(scancode - 0x80);
            } else {
                kprint(UKU);
            }
            break;
    }
}