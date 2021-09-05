/**
 * =====================================================================
 * Description: 
 * This program is the implementation of a text cipher
 * 
 * =====================================================================
 * Author               Dept.            Date                Notes
 * Xiangyun Wang    Electrical Eng.    2021-03-10       Initial version
 * Xiangyun Wang    Electrical Eng.    2021-03-16       Add comments
 * ====================================================================
 **/

#include <stdio.h>

int main(int argc, char *argv[]){

    int key = -1;   // preset key to -1

    if (argc!=4){   // check if number of argument is 4
        puts("Usage : ./cipher [-e|-d] <key> <MESSAGE>");
        return 1;
    }
//-------------------------------------------------------------------------
    int size[3] = {0,0,0}; // get size for each each input
    for (int i = 0; i<3; i++){
        int counter = 0;
        char tmp = argv[i+1][counter];
        while(tmp!='\0'){   // if current char is not '\0'
            counter++;      // keep counting 
            size[i]++;
            tmp = argv[i+1][counter];
        }
    }
//----------------------------------------------------------------------------
    // check option
    // if size is not correct or first char is not '-' or second char is not 'd' or 'e'
    if (size[0]!=2||argv[1][0]!='-'||(argv[1][1]!='d'&&argv[1][1]!='e')){
        printf("Error %s is not a valid option\n", argv[1]);
        return 1;
    }

    // check key
    // if key size is not correct
    if (size[1]<1||size[1]>2){
        printf("Error %s is not a valid key\n", argv[2]);
        return 1;
    }else if(size[1]==1){   // if key size is 1
        if(!(argv[2][0]>='2'&&argv[2][0]<='9')){    // check if between 2 and 9
            printf("Error %s is not a valid key\n", argv[2]);
            return 1;
        }else{      // loop over to find out key value
            for (int i = 2; i<10; i++){
                if(argv[2][0]=='0'+i){
                    key = i;
                    break;
                }
            }
        }
    }else if(size[1]==2){   // if key size is 2
        if(!(argv[2][0]=='1'&&argv[2][1]=='0')){    // check if key is 10
            printf("Error %s is not a valid key\n", argv[2]);
            return 1;
        }else{
            key = 10;
        }
    }

//----------------------------------------------------------------------------
    if(argv[1][1]=='e'){    // if key is 'e', execute
        int jump = 2*(key-1);   // total jump distance between two char for the first and last line
        for (int i = 0; i<key; i++){    // jump index of the first char of each line
            int current_index = i;      // record current index
            int front = jump-2*i;       // calculate the first step of the total jump
            int back = jump-front;      // calculate the second step of the total jump
            int next_step = front;      // preset next jump to the first step
            if(front==0) next_step = back;  // if the first step is 0 (last line), set next step to be second step
            while(current_index<size[2]){   // when current index < string size
                putchar(argv[3][current_index]);    // put char
                current_index += next_step;     // jump to next index
                if (next_step!=jump){           // update next step
                    if(next_step==front){
                      next_step=back;
                    }else{
                        next_step=front;
                    }
                }
            }
        }
        printf("\n");       // print a new line
    }
    return 0;
}
