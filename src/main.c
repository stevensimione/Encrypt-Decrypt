#include <stdlib.h>

#include "hw1.h"
#include "debug.h"

#ifdef _STRING_H
#error "Do not #include <string.h>. You will get a ZERO."
#endif

#ifdef _STRINGS_H
#error "Do not #include <strings.h>. You will get a ZERO."
#endif

#ifdef _CTYPE_H
#error "Do not #include <ctype.h>. You will get a ZERO."
#endif

int main(int argc, char **argv)
{
    unsigned short mode;

    mode = validargs(argc, argv);


    debug("Mode: 0x%X", mode);

    if(mode >= 0x8000) {
        USAGE(*argv, EXIT_SUCCESS);
    }else if(mode < 0x8000 && mode >= 0x4000){
        if(mode >= 0x6000){
            return fractionated_cipher_decrypt();
        }else{
            return fractionated_cipher_encrypt();
        }
    }else if(mode < 0x4000 && mode > 0x0){
        if(mode >= 0x2000){
            return polybius_cipher_decrypt();
        }else{
            return polybius_cipher_encrypt();
        }
    }else{
        USAGE(*argv, EXIT_FAILURE);
    }

    if(mode == 0x0){
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/*
 * Just a reminder: All non-main functions should
 * be in another file not named main.c
 */