//
//  spellus.c
//  Taak2
//
//  Created by Oscar Tison on 19/12/2017.
//  Copyright © 2017 Oscar Tison. All rights reserved.
//

#include "spellus.h"
#include "GUI.h"
#include "spelbord.h"

int speler = 1;



int main(int argc, char *argv[]) {
    while (cfileexists("save.txt") == 0) {
        initialiseer();}
    tel_instanties();
    printf("aantal instanties %i" ,aantal_spelinstanties);
    load_game();
    initialize_gui();
    print_spelbord ();
    while (should_continue) {
        load_game();
        draw_window();
        read_input();
        if (spelen == 0)
        {delete_insantie();}
        if (speler==1)
            speler = 2;
        else speler = 1;
        //  save_game(1);
    }
    free_gui();
    return 0;
}
