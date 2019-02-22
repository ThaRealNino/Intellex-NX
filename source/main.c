#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>

char name[] = "A         ";
char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int number[] = {0, 0, 0, 0};
int state = 0;
int nameCounter = 0;
int alphabetCounter = 0;
int numberCounter = 0;
int age = 0;

void printInfo() {
    printf("\nINTELLEX\n\n");
    printf("UP and DOWN to change value\n");
	printf("LEFT and RIGHT to add/delete character\n");
    printf("A to continue, B to revert\n");
    printf("PLUS to quit\n\n");
}

void reset() {

	for(int c = 0; c < sizeof(name) -2; c++) {
		name[c] = ' ';
	}

	number[0] = 0;
	number[1] = 0;
	number[2] = 0;
	number[3] = 0;
	state = 0;
	nameCounter = 0;
	alphabetCounter = 0;
	numberCounter = 0;
	age = 0;
}

char compareCharacters(char a,char b){
	if(a==b)
		return 0;
	else
		return 1;
}

void processInput(u64 keyDown) {

    printInfo();

    if(state == 0) {

        printf("Enter name: ");

        if(keyDown & KEY_DDOWN) {
            if(alphabetCounter < sizeof(alphabet) -2) {
                alphabetCounter++;
            } else {
                alphabetCounter = 0;
            }

            name[nameCounter] = alphabet[alphabetCounter];
			
        } else if(keyDown & KEY_DUP) {
		
			if(alphabetCounter == 0) {
				alphabetCounter = sizeof(alphabet) -2;
			} else {
				alphabetCounter--;
			}
			
			name[nameCounter] = alphabet[alphabetCounter];
			
		} else if(keyDown & KEY_DLEFT) {
			
			if(nameCounter > 0) {
				name[nameCounter] = ' ';
				nameCounter--;
				
				alphabetCounter = 0;
			}
			
		} else if(keyDown & KEY_DRIGHT) {
			
			if(nameCounter < (sizeof(name) - 2)) {
				if(compareCharacters(name[nameCounter], ' ') == 1) {
				
					nameCounter++;
					alphabetCounter = 0;
				}
			}
			
		} else if(keyDown & KEY_A) {
		
			state = 1;
		}

        printf(name);
		
    } else if(state == 1) {
		
		printf("Name: ");
		printf(name);
		printf("\n");
		
		printf("Enter age: ");
		
		if(keyDown & KEY_DDOWN) {
			
            if(age < 1000) {
				age++;
			}
			
        } else if(keyDown & KEY_DUP) {
		
			if(age > 0) {
				age--;
			}
			
		} else if(keyDown & KEY_B) {
			state = 0;
		
		} else if(keyDown & KEY_A) {
			state = 2;
			
		}
		
		printf("%i", age);
		
	} else if(state == 2) {
	
		printf("Name: ");
		printf(name);
		printf("\n");
		
		printf("Age: ");
		printf("%i\n", age);
		printf("\n");
		
		printf("Enter random 4-digit Number: ");
		
		if(keyDown & KEY_DDOWN) {
			
			if(number[numberCounter] < 9) {
				number[numberCounter]++;
				
			} else {
				number[nameCounter] = 0;
			}
			
        } else if(keyDown & KEY_DUP) {
		
			if(number[numberCounter] > 0) {
				number[numberCounter]--;
				
			} else {
				number[nameCounter] = 9;
			}
			
		} else if(keyDown & KEY_DLEFT) {
			
			if(numberCounter > 0) {
				numberCounter--;
			}
			
		} else if(keyDown & KEY_DRIGHT) {
			
			if(numberCounter < (sizeof(number) - 3)) {
				numberCounter++;
			}
			
		} else if(keyDown & KEY_B) {
			state = 1;
		
		} else if(keyDown & KEY_A) {
			state = 3;
			
		}
		
		printf("%i%i%i%i", number[0], number[1], number[2], number[3]);
	
	} else if(state == 3) {
	
		printf("Name: ");
		printf(name);
		printf("\n");
		
		printf("Age: ");
		printf("%i\n", age);
		
		printf("Number: ");
		printf("%i%i%i%i\n\n", number[0], number[1], number[2], number[3]);
		
		printf("Your IQ: 5\n");
		printf("Press MINUS to restart");
		
		if(keyDown & KEY_MINUS) {
			reset();
        }
	}
}

int main(int argc, char* argv[]) {

    consoleInit(NULL);

    while (appletMainLoop()){
    
        hidScanInput();
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if(kDown & KEY_PLUS) {
            break;
        }

        consoleClear();

        processInput(kDown);

        consoleUpdate(NULL);
    }

    consoleExit(NULL);
    return 0;
}