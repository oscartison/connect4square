//
//  spelbord.c
//  taak
//
//  Created by Oscar Tison on 13/11/2017.
//  Copyright © 2017 Oscar Tison. All rights reserved.
//

#include "spelbord.h"
#include <ctype.h>

int breedte = 6;
int hoogte = 6;
int spelen = 1;
int aantal_spelinstanties = 0;
int spelinsantie = 1;





int spelbord[6][6] =
{{0,0,0,0,0,0},
    {0,0,0,0,0,0},
    {0,0,0,0,0,0},
    {0,0,0,0,0,0},
    {0,0,0,0,0,0},
    {0,0,0,0,0,0}} ;

int cfileexists(const char * filename){
    /* try to open file to read */
    FILE *file;
    if ((file = fopen(filename, "r"))){
        fclose(file);
        return 1;
    }
    return 0;
}

void initialiseer () {
    FILE *file = fopen("save.txt", "w+");
    putc('$', file);
    for(int i=0; i<hoogte; i++) {
        for(int j=0;j<breedte;j++) {
             fputc('0', file);
        }}
    putc('\n', file);
    fclose(file);
    load_game();
}



void switch_instanties() {
    if ( spelinsantie >= aantal_spelinstanties)
        spelinsantie = 1;
    else
    {spelinsantie++;}
    print_spelbord();
    load_game();
}



void tel_instanties() {
    
    char ch;
    
    FILE *file = fopen("save.txt", "r");
    
    
    while( ( ch = fgetc(file) ) != EOF )
    {
        if (ch == 36) {
            aantal_spelinstanties++;
            printf("%c",ch);
        }
        
    }
    
    fclose(file);
}


void load_game () {
    
    char ch;
    
    FILE *file = fopen("save.txt", "r");
    
    int lijn = 0;
    int eee = 0;
    int s_counter = 0;
    
    while( ( ch = fgetc(file) ) != EOF )
    {
        if (ch == 36) {
            s_counter++;
            printf("%c",ch);
        }
        
        if (s_counter == spelinsantie)
        {
            if (ch==49)
            {spelbord[lijn][eee] = 1;
                eee++;}
            else if (ch==50)
            {spelbord[lijn][eee] = 2;
                eee++;
            }
            else if (ch==48)
            {spelbord[lijn][eee] = 0;
                eee++;
            }
        }
    }
    
    fclose(file);
}

void new_game (){
    FILE *file = fopen("save.txt", "a");
    //fputc('\n', file);
    fputc('$', file);
    for(int i=0; i<hoogte; i++) {
        for(int j=0;j<breedte;j++) {
            fputc('0', file);
        }
    }
    fputc('\n', file);
    fclose(file);
    aantal_spelinstanties++;
    printf("aantal %i", aantal_spelinstanties);
    spelinsantie = aantal_spelinstanties;
    load_game();
    print_spelbord();
}


void save_game () {
    printf("save game");
    FILE *file = fopen("save.txt", "r+");
    int count = 0; //how much have we gone yet?
    char c;
    long position_in_file;
    char s[38] = "$0000000000000000000000000000000000\n";
    
    // https://stackoverflow.com/questions/2510672/overwriting-lines-in-file-in-c
    
    for(int i=0; i<hoogte; i++) {
        for(int j=0;j<breedte;j++) {
            if (spelbord[i][j] == 1)
            {
                s[1 + 6*i + j] = '1';
            }
            else if (spelbord[i][j] == 2)
            {
                s[1 + 6*i + j] = '2';
            }
            else
            {
                s[1 + 6*i + j] = '0';
            }
            
        }
    }
    
    while(count != spelinsantie - 1) {
        if((c = fgetc(file)) == '\n') count++;
    }
    
    // Store the position
    position_in_file = ftell(file);
    // Reposition it
    fseek(file,position_in_file,SEEK_SET); // Or fseek(file,ftell(file),SEEK_SET);
    
    fprintf(file, "%s", s);
    fclose(file);
}

void delete_insantie() {
    int temp = 1;
    int ch = 0;
    
    FILE *file = fopen("save.txt", "r");
    FILE *file2 = fopen("copy.txt", "w");
    
    while (ch != EOF)
    {
        ch = getc(file);
        if(ch == EOF)
            break;
        else {
            
            //except the line to be deleted
            if (temp != spelinsantie)
            {
                //copy all lines in file replica.c
                putc(ch, file2);
            }
            if (ch == '\n')
            {
                temp++;
            }
        }
    }
    fclose(file);
    fclose(file2);
    remove(file);
    //rename the file replica.c to original name
    rename("copy.txt", "save.txt");
    fclose(file2);
    aantal_spelinstanties--;
    switch_instanties();
    
    
}


void print_spelbord () {
    for(int i=0; i<hoogte; i++) {
        for(int j=0;j<breedte;j++) {
            printf("%i ", spelbord[i][j]);
            if(j==(breedte - 1)){
                printf("\n");
            }
        }
    }
    printf("\n");
}

void check_spelbord (int rij, int kolom, int speler){
    if ((spelbord[rij] [kolom - 1] == speler && spelbord[rij + 1] [kolom] == speler && spelbord[rij + 1] [kolom - 1] == speler) || (spelbord[rij] [kolom + 1] == speler && spelbord[rij + 1] [kolom] == speler && spelbord[rij + 1] [kolom + 1] == speler))
        
    {
        print_spelbord ();
        printf("speler %d heeft gewonnen \n",speler);
        spelen = 0;
    }
}

void voegtoe (int kolom, int speler) {
    for (int i=(hoogte - 1); i>-1; i--) {
        if (spelbord [i] [kolom] == 0) {
            spelbord [i] [kolom] = speler;
            check_spelbord(i, kolom, speler);
            break;}
    }
    save_game (spelinsantie);
}

void calc_rectangle_pos (int mouse, int speler){
    if (spelen == 1) {
        if (mouse < 100)
            voegtoe (0, speler);
        else if (mouse < 200)
        {voegtoe (1, speler);
            
        }
        else if (mouse < 300)
        {voegtoe (2, speler);
        }
        else if (mouse < 400)
        {voegtoe (3, speler);
        }
        else if (mouse < 500)
        {voegtoe (4, speler);
        }
        else if (mouse < 600)
        {voegtoe (5, speler);
        }
        print_spelbord();
    }
}




