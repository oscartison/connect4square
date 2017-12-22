//
//  spelbord.h
//  taak
//
//  Created by Oscar Tison on 13/11/2017.
//  Copyright © 2017 Oscar Tison. All rights reserved.
//

#ifndef spelbord_h
#define spelbord_h

#include <stdio.h>


extern int spelen;

extern int breedte;

extern int hoogte;

extern int spelinsantie;

extern int aantal_spelinstanties;

int lees_positie_in(void);

extern int spelbord[6][6];

void print_spelbord (void) ;

void calc_rectangle_pos (int mouse, int speler);

void save_game (int sentinel);

void new_game (void);

void tel_instanties (void);

void switch_instanties (void);

void load_game (void);

void initialiseer(void);

int cfileexists(const char * filename);

void delete_insantie(void);

void check_spelbord (int rij, int kolom, int speler);

void voegtoe (int kolom, int speler);

#endif /* spelbord_h */
