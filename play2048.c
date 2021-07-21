#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <math.h>
typedef struct count{
    int comboCnt;
    int moveCnt; 
}CNT;
typedef struct rank_data{
    char name[16];
    char success;
    int duration;
    int comboCnt;
    int moveCnt;
}RANK;

int merge(int A[], int size);
CNT movement(int A[], int size);
void random_appear(int A[], int size);
void print_board(const int A[], int size);
void erase_board(int size);
int isended(const int A[], int size);
void print_interface(void);


int main(void){
    int size=5;
    int index;
    int inputNum;
    CNT cnt;
    char name[16];
    char success;
    int startTime, currentTime, endTime, timerSet=1200, timeLeft, duration;
    int moveCnt;
    int comboCnt;
    FILE* fp;
    RANK* rankPtr;
    int rank_data_size, min_duration, min_index;
    int *data=(int*)malloc(sizeof(int)*size*size);
    for(index=0; index<size*size; index++){
        data[index]=0;
    }

    while(1){
        printf("GAME START(1)\nHOW TO PLAY(2)\nRANKING(3)\nEXIT(4)\nInput: ");
        scanf("%d", &inputNum);
        getchar();
        printf("\n");
        moveCnt=0;
        comboCnt=0;
        timeLeft=timerSet;
    
        switch(inputNum){
        case 1:
            printf("CHOOSE MODE: NORMAL(1) or TIME ATTACK(2)\nInput: ");
            scanf("%d", &inputNum);
            printf("\n");
            random_appear(data, size);
            random_appear(data, size);
            print_board(data, size);
            startTime=time(NULL);
            if(inputNum==2){
                printf("\nTIME LEFT: %dm %02ds\n", timerSet/60, timerSet%60);
            }
            while(1){
                while(1){
                    if((isended(data, size)!=0||(cnt=movement(data, size)).moveCnt!=0)){
                        break;
                    }
                }
                comboCnt+=cnt.comboCnt;
                moveCnt+=cnt.moveCnt;
                erase_board(size);
                if(inputNum==2){
                    printf("\x1b[%dA", 2);
                }
                print_board(data, size);
                if(inputNum==2&&timeLeft<=0){
                    Sleep(700);
                    printf("\n _____   ___  ___  ___ _____    _____  _   _  _____ ______\n|  __ \\ / _ \\ |  \\/  ||  ___|  |  _  || | | ||  ___|| ___ \\\n| |  \\// /_\\ \\| .  . || |__    | | | || | | || |__  | |_/ /\n| | __ |  _  || |\\/| ||  __|   | | | || | | ||  __| |    /\n| |_\\ \\| | | || |  | || |___   \\ \\_/ /\\ \\_/ /| |___ | |\\ \\  _  _  _\n \\____/\\_| |_/\\_|  |_/\\____/    \\___/  \\___/ \\____/ \\_| \\_|(_)(_)(_)\n");
                    success='N';
                    break;
                }
                if(isended(data, size)==1){
                    Sleep(700);
                    printf("\n _____   ___  ___  ___ _____    _____  _      _____   ___  ______   _ \n|  __ \\ / _ \\ |  \\/  ||  ___|  /  __ \\| |    |  ___| / _ \\ | ___ \\ | |\n| |  \\// /_\\ \\| .  . || |__    | /  \\/| |    | |__  / /_\\ \\| |_/ / | |\n| | __ |  _  || |\\/| ||  __|   | |    | |    |  __| |  _  ||    /  | |\n| |_\\ \\| | | || |  | || |___   | \\__/\\| |____| |___ | | | || |\\ \\  |_|\n \\____/\\_| |_/\\_|  |_/\\____/    \\____/\\_____/\\____/ \\_| |_/\\_| \\_| (_)\n");
                    success='Y';
                    break;
                }
                else if(isended(data, size)==-1){
                    Sleep(700);
                    printf("\n _____   ___  ___  ___ _____    _____  _   _  _____ ______\n|  __ \\ / _ \\ |  \\/  ||  ___|  |  _  || | | ||  ___|| ___ \\\n| |  \\// /_\\ \\| .  . || |__    | | | || | | || |__  | |_/ /\n| | __ |  _  || |\\/| ||  __|   | | | || | | ||  __| |    /\n| |_\\ \\| | | || |  | || |___   \\ \\_/ /\\ \\_/ /| |___ | |\\ \\  _  _  _\n \\____/\\_| |_/\\_|  |_/\\____/    \\___/  \\___/ \\____/ \\_| \\_|(_)(_)(_)\n");
                    success='N';
                    break;
                }
                Sleep(300);
                random_appear(data, size);
                erase_board(size);
                print_board(data, size);
                currentTime=time(NULL);
                if(inputNum==2){
                    timeLeft=timerSet+startTime-currentTime;
                    printf("\nTIME LEFT: %dm %02ds\n", timeLeft/60, timeLeft%60);
                }
            }
            endTime=time(NULL);
            duration=endTime-startTime;
            printf("\nInput Your Name: ");
            scanf("%s", name);
            fp=fopen("rank.txt", "a");
            fprintf(fp, "%s\t%c\t%d\t%d\t%d\n", name, success, duration, moveCnt, comboCnt);
            fclose(fp);
            break;
        case 2:
            printf("You can easily play this game by pressing \'w\', \'a\', \'s\', \'d\', for each direction. \'2\' or \'4\' randomly appears during each movement, and now on you to merge these tiles! Make 2048, Good Luck...\n");
            break;
        case 3:
            if((fp=fopen("rank.txt", "r"))==NULL){
                fprintf(stderr, "File could not be found.");
            }
            index=0;
            rank_data_size=0;
            while(!feof(fp)){
                fscanf(fp, "%s\t%c\t%d\t%d\t%d\n", rankPtr[index].name, &rankPtr[index].success, &rankPtr[index].duration, &rankPtr[index].moveCnt, &rankPtr[index].comboCnt);
                rank_data_size=++index;
            }
            for(int i=0; i<rank_data_size; i++){
                min_duration=rankPtr[0].duration;
                min_index=0;
                for(index=1; index<rank_data_size; index++){
                    if(min_duration>rankPtr[index].duration){
                        min_duration=rankPtr[index].duration;
                        min_index=index;
                    }
                }
                printf("NAME: %s\tSUCCESS: %c\tTIME: %dm %02ds\tMOVES: %d\tCOMBO: %d\n", rankPtr[min_index].name, rankPtr[min_index].success, rankPtr[min_index].duration/60, rankPtr[min_index].duration%60, rankPtr[min_index].moveCnt, rankPtr[min_index].comboCnt);
                rankPtr[min_index].duration=__INT_MAX__;
                }
            break;
        case 4:
            free(data);
            return 0;
        default:
            break;
        }
        printf("\n");
    } 
}

CNT movement(int A[], int size){
    char direction;
    int index;
    int x, y;
    int array[size];
    CNT cnt;
    cnt.comboCnt=0;
    cnt.moveCnt=0;

    direction=_getch();
    
    switch(direction){
    case 'w':
        for(x=0; x<size; x++){
            for(index=0; index<size; index++){
                y=index;
                array[index]=A[x+y*size];
            }
            cnt.comboCnt+=merge(array, size);
            for(index=0; index<size; index++){
                y=index;
                if(A[x+y*size]!=array[index]){
                    cnt.moveCnt=1;
                }
                A[x+y*size]=array[index];
            }
        }
        break;
    case 's':
        for(x=0; x<size; x++){
            for(index=0; index<size; index++){
                y=size-1-index;
                array[index]=A[x+y*size];
            }
            cnt.comboCnt+=merge(array, size);
            for(index=0; index<size; index++){
                y=size-1-index;
                if(A[x+y*size]!=array[index]){
                    cnt.moveCnt=1;
                }
                A[x+y*size]=array[index];
            }
        }
        break;
    case 'a':
        for(y=0; y<size; y++){
            for(index=0; index<size; index++){
                x=index;
                array[index]=A[x+y*size];
            }
            cnt.comboCnt+=merge(array, size);
            for(index=0; index<size; index++){
                x=index;
                if(A[x+y*size]!=array[index]){
                    cnt.moveCnt=1;
                }
                A[x+y*size]=array[index];
            }
        }        
        break;
    case 'd':
        for(y=0; y<size; y++){
            for(index=0; index<size; index++){
                x=size-1-index;
                array[index]=A[x+y*size];
            }
            cnt.comboCnt+=merge(array, size);
            for(index=0; index<size; index++){
                x=size-1-index;
                if(A[x+y*size]!=array[index]){
                    cnt.moveCnt=1;
                }
                A[x+y*size]=array[index];
            }
        }
        break;
    default:
        break;
    }

    return cnt;
}

int merge(int A[], int size){
    int index, presentIndex=0, ptrIndex=0, newIndex=0;
    int formerElement, latterElement;
    int ptr[size];
    int comboCnt=0;
  
    while(presentIndex<size){
        if(A[presentIndex]!=0){
            ptr[ptrIndex]=A[presentIndex];
            ptrIndex++;
        }
        presentIndex++;
    }

    for(index=0; index<ptrIndex; index++){
        if(index==ptrIndex-1){
            A[newIndex]=ptr[index];
            newIndex++;
            break;
        }
        formerElement=ptr[index];
        latterElement=ptr[index+1];
        if(formerElement==latterElement){
            A[newIndex]=formerElement+latterElement;
            newIndex++;
            index++;
            comboCnt++;
        }
        else{
            A[newIndex]=formerElement;
            newIndex++;
        }
    }

    for(index=newIndex; index<size; index++){
        A[index]=0;
    }

    return comboCnt;
}

void random_appear(int A[], int size){
    int index, ptrIndex=0;
    int randomInt;
    int ptr[size*size];

    for(index=0; index<size*size; index++){
        if(A[index]==0){
            ptr[ptrIndex]=index;
            ptrIndex++;
        }
    }

    srand((unsigned)time(NULL));

    if(rand()%10<=8){
        randomInt=2;
    }
    else{
        randomInt=4;
    }

    srand((unsigned)time(NULL));
    
    A[ptr[rand()%ptrIndex]]=randomInt;
}

void print_board(const int A[], int size){
    int virtualInt[size*size];
    int index;
    int xIndex, yIndex;
    char asciiArt[12][3][24];

    strcpy(asciiArt[0][0], "|                     |");
    strcpy(asciiArt[0][1], "|                     |");
    strcpy(asciiArt[0][2], "|                     |");
    strcpy(asciiArt[1][0], "|         __          |");
    strcpy(asciiArt[1][1], "|         __|         |");
    strcpy(asciiArt[1][2], "|        |__          |");
    strcpy(asciiArt[2][0], "|                     |");
    strcpy(asciiArt[2][1], "|        |__|         |");
    strcpy(asciiArt[2][2], "|           |         |");
    strcpy(asciiArt[3][0], "|         __          |");
    strcpy(asciiArt[3][1], "|        |__|         |");
    strcpy(asciiArt[3][2], "|        |__|         |");
    strcpy(asciiArt[4][0], "|           __        |");
    strcpy(asciiArt[4][1], "|       |  |__        |");
    strcpy(asciiArt[4][2], "|       |  |__|       |");
    strcpy(asciiArt[5][0], "|       __   __       |");
    strcpy(asciiArt[5][1], "|       __|  __|      |");
    strcpy(asciiArt[5][2], "|       __| |__       |");
    strcpy(asciiArt[6][0], "|       __            |");
    strcpy(asciiArt[6][1], "|      |__  |__|      |");
    strcpy(asciiArt[6][2], "|      |__|    |      |");
    strcpy(asciiArt[7][0], "|        __   __      |");
    strcpy(asciiArt[7][1], "|     |  __| |__|     |");
    strcpy(asciiArt[7][2], "|     | |__  |__|     |");
    strcpy(asciiArt[8][0], "|    __   __   __     |");
    strcpy(asciiArt[8][1], "|    __| |__  |__     |");
    strcpy(asciiArt[8][2], "|   |__   __| |__|    |");
    strcpy(asciiArt[9][0], "|     __      __      |");
    strcpy(asciiArt[9][1], "|    |__   | |__      |");
    strcpy(asciiArt[9][2], "|     __|  | |__|     |");
    strcpy(asciiArt[10][0], "|      __   __        |");
    strcpy(asciiArt[10][1], "|   | |  |  __| |__|  |");
    strcpy(asciiArt[10][2], "|   | |__| |__     |  |");
    strcpy(asciiArt[11][0], "|  __   __        __  |");
    strcpy(asciiArt[11][1], "|  __| |  | |__| |__| |");
    strcpy(asciiArt[11][2], "| |__  |__|    | |__| |");

    for(index=0; index<size*size; index++){
        switch(A[index]){
        case 0:
            virtualInt[index]=0;
            break;
        case 2:
            virtualInt[index]=1;
            break;
        case 4:
            virtualInt[index]=2;
            break;
        case 8:
            virtualInt[index]=3;
            break;
        case 16:
            virtualInt[index]=4;
            break;
        case 32:
            virtualInt[index]=5;
            break;
        case 64:
            virtualInt[index]=6;
            break;
        case 128:
            virtualInt[index]=7;
            break;
        case 256:
            virtualInt[index]=8;
            break;
        case 516:
            virtualInt[index]=9;
            break;
        case 1024:
            virtualInt[index]=10;
            break;
        case 2048:
            virtualInt[index]=11;
            break;
        }
    }

    for(index=0; index<size; index++){
        for(xIndex=0; xIndex<size; xIndex++){
            printf(" __ __ __ __ __ __ __  ");
        }
        printf("\n");
        for(xIndex=0; xIndex<size; xIndex++){
            printf("|                     |");
        }
        printf("\n");
        for(xIndex=0; xIndex<size; xIndex++){
            printf("|                     |");
        }
        printf("\n");
        for(yIndex=0; yIndex<3; yIndex++){
            for(xIndex=index*size; xIndex<(index+1)*size; xIndex++){
                printf("%s", asciiArt[virtualInt[xIndex]][yIndex]);
            }
            printf("\n");
        }
        for(xIndex=0; xIndex<size; xIndex++){
            printf("|                     |");
        }
        printf("\n");
        for(xIndex=0; xIndex<size; xIndex++){
            printf("|                     |");
        }
        printf("\n");
        for(xIndex=0; xIndex<size; xIndex++){
            printf("|__ __ __ __ __ __ __ |");
        }
        printf("\n");
    }
}

void erase_board(int size){
    printf("\x1b[%dA", size*9);
}

int isended(const int A[], int size){
    int index;
    int x, y;

    for(index=0; index<size*size; index++){
        if(A[index]==2048){
            return 1;
        }
    }

    for(index=0; index<size*size; index++){
        if(A[index]==0){
            return 0;
        }
    }

    for(x=0; x<size-1; x++){
        for(y=0; y<size; y++){
            if(A[x+size*y]==A[x+1+size*y]){
                return 0;
            }
        }
    }
    for(y=0; y<size-1; y++){
        for(x=0; x<size; x++){
            if(A[x+size*y]==A[x+size*(y+1)]){
                return 0;
            }
        }
    }
    
    return -1;
}


// 2 4 8 16 32 64 128 256 516 1024 2048
//  __ __ __ __ __ __ __  
// |                     |
// |                     |
// |  __   __        __  |
// |  __| |  | |__| |__| |
// | |__  |__|    | |__| |
// |                     |
// |                     |
// |__ __ __ __ __ __ __ |

//  __ __ __ __ __ __ __ 
// |                     |
// |                     |
// |      __   __        |
// |   | |  |  __| |__|  |
// |   | |__| |__     |  |
// |                     |
// |                     |
// |__ __ __ __ __ __ __ |

//  __ __ __ __ __ __ __ 
// |                     |
// |                     |
// |     __      __      |
// |    |__   | |__      |
// |     __|  | |__|     |
// |                     |
// |                     |
// |__ __ __ __ __ __ __ |

//  __ __ __ __ __ __ __ 
// |                     |
// |                     |
// |    __   __   __     |
// |    __| |__  |__     |
// |   |__   __| |__|    |
// |                     |
// |                     |
// |__ __ __ __ __ __ __ |

//  __ __ __ __ __ __ __ 
// |                     |
// |                     |
// |        __   __      |
// |     |  __| |__|     |
// |     | |__  |__|     |
// |                     |
// |                     |
// |__ __ __ __ __ __ __ |

//  __ __ __ __ __ __ __ 
// |                     |
// |                     |
// |       __            |
// |      |__  |__|      |
// |      |__|    |      |
// |                     |
// |                     |
// |__ __ __ __ __ __ __ |

//  __ __ __ __ __ __ __ 
// |                     |
// |                     |
// |       __   __       |
// |       __|  __|      |
// |       __| |__       |
// |                     |
// |                     |
// |__ __ __ __ __ __ __ |

//  __ __ __ __ __ __ __ 
// |                     |
// |                     |
// |           __        |
// |       |  |__        |
// |       |  |__|       |
// |                     |
// |                     |
// |__ __ __ __ __ __ __ |

//  __ __ __ __ __ __ __ 
// |                     |
// |                     |
// |         __          |
// |        |__|         |
// |        |__|         |
// |                     |
// |                     |
// |__ __ __ __ __ __ __ |

//  __ __ __ __ __ __ __ 
// |                     |
// |                     |
// |                     |
// |        |__|         |
// |           |         |
// |                     |
// |                     |
// |__ __ __ __ __ __ __ |

//  __ __ __ __ __ __ __ 
// |                     |
// |                     |
// |         __          |
// |         __|         |
// |        |__          |
// |                     |
// |                     |
// |__ __ __ __ __ __ __ |