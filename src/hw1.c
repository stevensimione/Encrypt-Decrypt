#include <stdlib.h>
#include "hw1.h"

#ifdef _STRING_H
#error "Do not #include <string.h>. You will get a ZERO."
#endif

#ifdef _STRINGS_H
#error "Do not #include <strings.h>. You will get a ZERO."
#endif

#ifdef _CTYPE_H
#error "Do not #include <ctype.h>. You will get a ZERO."
#endif

int row = 0;
int col = 0;


int compare(const char* left, const char* right){
    int place = 0;
    while(1){
        if(*(left + place) != *(right + place)){
            return 0;
        }

        if(*(left + place) == '\0'){
            return 1;
        }

        place = place + 1;

    }
}

int toInt(char* string){
    int num = 0;
    int i = 0;
    int value = 0;
    while(*(string + i) != '\0'){
        num = num * 10;
        value = (int) *(string + i) - 48;
        num = num + value;

        i = i + 1;
    }

    return num;
}

void rHandler(char** argv, int i, unsigned short* mode){

    if(compare(*(argv + i + 1), "-c") + compare(*(argv + i + 1), "-k")){
        *mode = *mode + 0x0000;
        return;
    }else if(*(*argv + (i + 1)) == '\0'){
        *mode = 0x0;
        return;
    }else{
        int num = toInt(*(argv + i + 1));
        if(num > 8 && num <= 15){
            row = num;
            num = num << 4;
            *mode = *mode + num;
            return;
        }else{
            *mode = 0x0000;
            return;
        }

    }

}

void cHandler(char** argv, int i, unsigned short* mode){
    if(compare(*(argv + i + 1), "-r") + compare(*(argv + i + 1), "-k")){
        *mode = *mode + 0x0000;
        return;
    }else if(*(*argv + (i + 1)) == '\0'){
        *mode = 0x0;
        return;
    }else{
        int num = toInt(*(argv + i + 1));
        if(num > 8 && num <= 15){
            col = num;
            *mode = *mode + num;
            return;
        }else{
            *mode = 0x0000;
            return;
        }

    }

}

int kHandler(char** argv, int i, unsigned short* mode){
    int j = 0;
    if(compare(*(argv + i + 1), "-r") + compare(*(argv + i + 1), "-c")){
        *mode = 0x0;
        return 0;
    }else if(*(*argv + (i + 1)) == '\0'){
        *mode = 0x0;
        return 0;
    }else{
        while(*(*(argv + i + 1) + j) != '\0'){
            if((int) *(*(argv + i + 1) + j) < 33 || (int) *(*(argv + i + 1) + j) > 126){
                *mode = 0x0;
                return 0;
            }
            int k = j + 1;
            while(*(*(argv + i + 1) + k) != '\0'){
                    if((*(*(argv + i + 1)+ j)) == *(*(argv + i + 1)+ k)){
                        *mode = 0x0;
                        return 0;
                    }
                k = k + 1;
            }
                j = j + 1;
        }
     }
     char *place = *(argv + i + 1);
     key = place;
     return 1;
}


/**
 * @brief Validates command line arguments passed to the program.
 * @details This function will validate all the arguments passed to the program
 * and will return a unsigned short (2 bytes) that will contain the
 * information necessary for the proper execution of the program.
 *
 * IF -p is given but no (-r) ROWS or (-c) COLUMNS are specified this function
 * MUST set the lower bits to the default value of 10. If one or the other
 * (rows/columns) is specified then you MUST keep that value rather than assigning the default.
 *
 * @param argc The number of arguments passed to the program from the CLI.
 * @param argv The argument strings passed to the program from the CLI.
 * @return Refer to homework document for the return value of this function.
 */
unsigned short validargs(int argc, char **argv) {
    int pf = 0;
    int hFlag = 0;
    int ed = 0;
    int rFlag = 0;
    int cFlag = 0;
    int k = 0;
    int f = 0;
    unsigned short mode = 0x0;
    int i = 1;
    for (i = 1; i < argc; i++){
        if(compare(*(argv + i), "-h")){
            if (hFlag){
                return 0x0;
            }
            return 0x8000;
        }
        else if(compare(*(argv + i), "-f")){
            if(pf){
                return 0x0;
            }
            f = 1;
            hFlag = 1;
            pf = 1;
            mode = mode + 0x4000;
        }
        else if(compare(*(argv + i), "-d")){
            if(ed){
                return 0x0;
            }
            if(pf == 0){
                return 0x0;
            }
            ed = 1;
            hFlag = 1;
            mode = mode + 0x2000;
        }
        else if(compare(*(argv + i), "-e")){
            if(ed){
                return 0x0;
            }
            if(pf == 0){
                return 0x0;
            }
            hFlag = 1;
            ed = 1;

        }
        else if(compare(*(argv + i), "-p")){
            if(pf){
                return 0x0;
            }
            hFlag = 1;
            pf = 1;

        }
        else if(compare(*(argv + i), "-r")){
            if(rFlag){
                return 0x0;
            }

            if(ed == 0 || pf == 0 || f){
                return 0x0;
            }
            rFlag = 1;

            rHandler(argv, i, &mode);
            if(mode == 0x0){
                return mode;
            }

            i = i + 1;

        }
        else if(compare(*(argv + i), "-c")){
            if(cFlag){
                return 0x0;
            }

            if(ed == 0 || pf == 0 || f){
                return 0x0;
            }

            cFlag = 1;

            cHandler(argv, i, &mode);
            if(mode == 0x0){
                return mode;
            }
            i = i + 1;
        }
        else if(compare(*(argv + i), "-k")){
            if(k){
                return 0x0;
            }

            if(ed == 0 || pf == 0){
                return 0x0;
            }

            if(0 == kHandler(argv, i, &mode)){
                return 0x0;
            }
            k = 1;


            i = i + 1;
        }
        else{
            return 0x0;
        }
    }
    if(ed == 0){
        return 0x0;
    }

    if(cFlag == 0){
        col = 10;
        mode = mode + 0x000A;
    }

    if (rFlag == 0){
        row = 10;
        mode = mode + 0x00A0;
    }
    int size = row * col;
    i = 0;
    int count  = 0;
    while(*(polybius_alphabet + i) != '\0'){
        count = count + 1;

        i = i + 1;
    }

    i = 0;
    if(k){
        while(*(key + i) != '\0'){
            int found = 0;
            int j = 0;
            while(*(polybius_alphabet + j) != '\0'){
                if(*(key + i) == *(polybius_alphabet + j)){
                    found = 1;
                }
                j = j + 1;
            }
            if(found == 0){
                count = count + 1;
            }
            i = i + 1;
        }
    }


    if(size < count){
        return 0x0;
    }
    return mode;
}

int notFoundMethod(int kLength, int size, int i){
        int j;
        for(j = 0; j < kLength; j = j + 1){
            if(*(key + j) == *(polybius_alphabet + i)){
                return 0;
            }
        }
        return 1;
}
void build_table(){
    int kLength = 0;
    if(key != NULL){
    while(*(key + kLength) != '\0'){
        *(polybius_table + kLength) = *(key + kLength);
        kLength = kLength + 1;
    }
}
    int size = row * col;

    int i;
    int j = 0;
    for(i = 0; i < size && *(polybius_alphabet + i) != '\0'; i = i + 1){
    int notFound = notFoundMethod(kLength, size, i);
        if(notFound){
            *(polybius_table + kLength + i - j) = *(polybius_alphabet + i);
        }else{
            j = j + 1;
        }
    }

    if(kLength + i < size){
        for(j = kLength + i; j < size; j = j + 1){
            *(polybius_table + kLength + i) = '\0';
        }
    }

}


int polybius_cipher_encrypt(){
    char a = 'a';
    char num1 = '1';
    char num2 = '2';
    int index = 0;
    build_table();
    int notFound = 1;
    /*printf("Enter word you want to encrypt:\n");*/
    while(a != EOF){
    a = getchar();
    while(a != '\n' && a != EOF){
    int r;
    int c;
    int i = 0;
    int j = 0;
        if(a == ' ' || a== '\n' || a == '\t'){
            printf("%c", a);
            notFound = 0;
        }else{
            for(r = 0; r < row; r = r + 1){
                for(c = 0; c < col; c = c + 1){
                    if(*(polybius_table + (r * col + c)) == a){
                        num1 = (char) (r + 48);
                        num2 = (char) (c + 48);
                        printf("%c%c", num1, num2);
                        notFound = 0;
                    }
                }
            }
        }
        if(notFound){
            return EXIT_FAILURE;
        }
        notFound = 1;
        a = getchar();
    }
    printf("\n");
}
    return EXIT_SUCCESS;
}

int polybius_cipher_decrypt(){
    build_table();
    int EOFFlag = 1;
    char num1 = 'a';
    char num2 = 'b';
    char a = 'c';
    int notFound = 1;
    while(EOFFlag){
        num1 = getchar();
        if(num1 == EOF){
            EOFFlag = 0;
            break;
        }
        if(num1 == '\n' || num1 == '\t' || num1 == ' '){
            num2 = '~';
        }else{
        num2 = getchar();
        if(num2 == EOF){
            EOFFlag = 0;
            break;
        }
    }
    while(EOFFlag && num1 != '\n' && num2 != '\n'){
        int index = 0;


        int r;
        int c;
        int i = 0;
        int j = 0;
            if(num1 == ' ' || num1 == '\n' || num1 == '\t'){
                printf("%c", num1);
            }else{
                int r = (int) num1 - 48;
                int c = (int) num2 - 48;
                if(r*col + c > row * col){
                    return EXIT_FAILURE;
                }
                c = *(polybius_table + (r*col + c));
                printf("%c", c);

            }



        num1 = getchar();
        if(num1 == EOF){
            EOFFlag = 0;
            break;
        }
        if(num1 == '\n' || num1 == '\t' || num1 == ' '){
            num2 = '~';
        }else{
        num2 = getchar();
        if(num2 == EOF){
            EOFFlag = 0;
            break;
        }
    }
    }
    printf("\n");
}
    return EXIT_SUCCESS;
}

int notFound_fract(int kLength, int i){
    int j;
    for(j = 0; j < kLength; j = j + 1){
            if(*(key + j) == *(fm_alphabet + i)){
                return 0;
            }
        }
        return 1;
}

void build_fractionated_table(){
    int kLength = 0;
    if(key != NULL){
    while(*(key + kLength) != '\0'){
        *(fm_key + kLength) = *(key + kLength);

        kLength = kLength + 1;
    }
}

    int i;
    int j = 0;
    for(i = 0; *(fm_alphabet + i) != '\0'; i = i + 1){
        int notFound = notFound_fract(kLength, i);
        if(notFound){
            *(fm_key + kLength + i - j) = *(fm_alphabet + i);
        }else{
            j = j + 1;
        }
    }

}

int length(const char* string){
    int i = 0;
    while(*(string + i) != '\0'){
        i = i + 1;
    }
    return i;
}

void copyString(char* location, const char* string, int* index){
    int i;
    int end = length(string);
    for(i = 0; i < end; i = i + 1){
        *(location + i) = *(string + i);
    }
    *(location + i ) = 'x';
    i = i + 1;
    *(location + i) = '\0';
    *index = *index + i;
}

void clear_buffer(char** buffer){
    char* clear = *buffer;
    int i = 0;
    while(*(clear + i) != '\0'){
        *(clear + i) = '\0';
        i = i + 1;
    }
}

int fractionated_cipher_encrypt(){
    build_fractionated_table();
    char* buffer = polybius_table;
    char* word = polybius_table + 253;

    char a = 'a';
    int i;
    int alter = 1;
    while(a != EOF){
    a = getchar();
    int index = 0;
    while(a != '\n'){
        int locator = (int) a - 33;
        if(locator > 92){
            return EXIT_FAILURE;
        }
        if(a == ' ' || a == '\t'){

            if(alter){
            *(buffer + index) = 'x';
            index = index + 1;
            *(buffer + index) = '\0';
            alter = 0;
         }
        }else{
        if(**(morse_table + locator) == '\0'){
            return EXIT_FAILURE;
        }
        copyString((buffer + index), *(morse_table + locator), &index);
        alter = 1;
        if(length(buffer) % 3 == 0){
            for(i = 0; i < length(buffer); i = i + 1){
                    *(word + i%3) = *(buffer + i);
                    if(i % 3 == 2){

                        int j = 0;
                        while(!compare(*(fractionated_table + j), word)){
                            j = j + 1;
                        }
                        printf("%c", *(fm_key + j));
                    }
                }
                index = 0;
        }

    }
    a = getchar();


    }


    *(buffer + index) = 'x';
    *(buffer + index + 1) = '\0';
    index = index + 1;
    if(i%3 != 0){
        index = 0;
    }
    int len = length(buffer);
    for(i = 0; i < len; i = i + 1){
        *(word + i%3) = *(buffer + i);
        if(i % 3 == 2){
            int j = 0;
            while(!compare(*(fractionated_table + j), word)){
                j = j + 1;
            }
            printf("%c", *(fm_key + j));
            }
    }
    clear_buffer(&buffer);
    index = 0;
    printf("\n");
}
return EXIT_SUCCESS;
}

void decrypt_copy(char* location, const char* string, int* index){
    int i;
    int end = length(string);
    for(i = 0; i < end; i = i + 1){
        *(location + i) = *(string + i);
    }
    *(location + i) = '\0';
    *index = *index + i;
}

int getIndex(char* word){
    int i = 0;
    while(*(morse_table + i) != '\0'){

        if(compare(*(morse_table + i), word)){
            return i;
        }

        i = i + 1;
    }
    return -1;
}

int fractionated_cipher_decrypt(){
    build_fractionated_table();
    char* buffer = polybius_table;
    char* word = (polybius_table + 250);

    char a = 'a';
    char location = 'a';
    int i = 0;
    int some = 0;
    int placer = 0;
    while(a != EOF){
    a = getchar();
    int index = 0;
    int space = 1;
    int space2 = 0;
    int endSpace;
    int nullNotFound = 1;
    int x = 0;
    while(a != '\n'){
        i = 0;
        while(*(fm_key + i) != a){
            if(*(fm_key + i) == '\0'){
                return EXIT_FAILURE;
            }
            i = i + 1;
        }
        decrypt_copy((buffer + index),*(fractionated_table + i), &index);
        if(*buffer == 'x'){
            if(!some){
                printf(" ");
                some = 1;
            }
        }


        if(*(buffer + index - 1) == 'x'){
            some = 0;
            index = index - 1;
        if(*(buffer+ index - 1) == 'x'){
            index = index - 1;
            space2 = 1;
        }
        for(i = 0; i < index + 1; i = i + 1){
            if(*(buffer + i) == 'x' && i != 0){
                if(space){
                    if((*buffer + i + 1) == 'x'){
                        space = 0;
                    }
                 *(word + placer) = '\0';
                 location = (char) getIndex(word) + 33;
                 if(location == ' '){
                    location = 'a';
                 }
                 placer = 0;

                 if(location == -1){
                    break;
                 }
                 printf("%c", location);
                 if(i == index){
                 clear_buffer(&buffer);
                index = 0;
                 }
                }else{
                    printf(" ");
                }
            }else{
                if(*(buffer + i) != 'x'){
                *(word + placer) = *(buffer + i);
                placer = placer + 1;
            }
            }
        }
        space = 1;
    if(space2){
        printf(" ");
        space2 = 0;
    }
}

        a = getchar();

    }
    if(index != 0){
    *(buffer + index) = 'x';
    *(buffer + index + 1) = '\0';
    index = index + 1;
}

        if(*(buffer + index - 1) == 'x'){
            index = index - 1;
        if(*(buffer + index - 1) == 'x'){
            index = index - 1;
            space2 = 1;
        }
    }
    //if(i%3 != 0){
    //    index = 0;
    //}
        for(i = 0; i < index + 1; i = i + 1){
            if(*(buffer + i) == 'x'){
                if(space){
                 space = 0;
                 *(word + i) = '\0';
                 location = (char) getIndex(word) + 33;
                 placer = 0;
                 if(location == -1){
                    return EXIT_FAILURE;
                 }
                 printf("%c", location);
                }else{
                    printf(" ");
                }
            }else{
                *(word + placer) = *(buffer + i);
                placer = placer + 1;
            }
        }
    space = 1;
    if(space2){
        printf(" ");
        space2 = 0;
    }


    printf("\n");
}
return EXIT_SUCCESS;
}
