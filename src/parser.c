#include "scanner.c"


int main(int argc, char* argv[]){
    //Check arguments
    if (argc != 2) {
        fprintf(stderr,"Pouzitie: %s <filename>\n", argv[0]);
        return -1;
    }
    FILE *file = fopen(argv[1], "r");
    // check if file exists
    if (file == NULL) {
        fprintf(stderr,"Error \n");
        return -1; 
    }
    struct Token scannedToken;
    int counter = 0; 
    scannedToken = getToken(file);
    while(scannedToken.ID != 0){
        printf("Token %d: %s\n",counter,scannedToken.symbol);    
        counter++;
        switch(scannedToken.ID){
        case 0: break;
        case 1: break;
        case 2: break;
        case 3: break;
        case 4: break;
        case 5: break;
        case 6: break;
        case 7: break;
        case 8: break;
        case 9: break;
        default: 
            if(scannedToken.ID < 0){
                //komentar, runni while again
                break;
            }
        }
    printf("Scanning Token %d\n",counter);    
    scannedToken = getToken(file);
    }


    fclose(file);
    return 0;
}