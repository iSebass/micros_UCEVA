#include "DISPLAY_7_SEG.h"

void display_init(void){
    DIR_segA = OUT;
    DIR_segB = OUT;
    DIR_segC = OUT;
    DIR_segD = OUT;
    DIR_segE = OUT;
    DIR_segF = OUT;
    DIR_segG = OUT;
}
void display_ac(char dig);
void display_cc(char dig){
    
    switch(dig){
        case 0: segA = 1;
                segB = 1;
                segC = 1;
                segD = 1;
                segE = 1;
                segF = 1;
                segG = 0;
                break;
                
        case 1: segA = 0;
                segB = 1;
                segC = 1;
                segD = 0;
                segE = 0;
                segF = 0;
                segG = 0;
                break;
    }
}
