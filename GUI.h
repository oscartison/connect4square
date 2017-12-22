#ifndef GUI_H_
#define GUI_H_

#include <stdlib.h>

/*
 * Importeert de functies uit SDL2 die je nodig hebt om je GUI te maken.
 */
#include <SDL2/SDL.h>

/*
 * De hoogte en breedte (in pixels) van de afbeeldingen voor de vakjes in het speelveld die getoond worden.
 * Als je andere afbeelding wil gebruiken in je GUI, zorg er dan voor dat deze
 * dimensies ook aangepast worden.
 */
#define IMAGE_HEIGHT 100
#define IMAGE_WIDTH 100

/*
 * De hoogte en breedte (in pixels) van de knoppen die getoond worden.
 * Als je andere afbeelding wil gebruiken in je GUI, zorg er dan voor dat deze
 * dimensies ook aangepast worden.
 */
#define BUTTON_HEIGHT 140
#define BUTTON_WIDTH 200




void initialize_gui(void);
void  read_input(void);
void  free_gui(void);

extern int should_continue;

void draw_window(void);


#endif /* GUI_H_ */
