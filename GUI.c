#include "GUI.h"
#include "spelbord.h"
#include "spellus.h"



/*
 * Deze renderer wordt gebruikt om figuren in het venster te tekenen. De renderer
 * wordt geïnitialiseerd in de initialize_window-functie.
 */
static SDL_Renderer *renderer;

/*
 * Dit is het venster dat getoond zal worden en waarin het speelveld weergegeven wordt.
 * Dit venster wordt aangemaakt bij het initialiseren van de GUI en wordt weer afgebroken
 * wanneer het spel ten einde komt.
 */
static SDL_Window *window;

/* De afbeelding die een vakje met een blauw steentje in het speelbord voorstelt. */
static SDL_Texture *blue_circle_texture;
static SDL_Texture *red_circle_texture;
static SDL_Texture *empty_texture;


/*
 * Elke afbeelding die in een GUI getekend wordt, wordt getekend in een bepaald deel van het GUI-venster.
 * Dat deel wordt voorgesteld als een rechthoek en is van het type SDL_Rect.
 * Een SDL_Rect bestaat uit de volgende 4 velden:
 *    x (de x-positie van het linkerbovenpunt van de rechthoek)
 *    y (de y-positie van het linkerbovenpunt van de rechthoek)
 *    w (de breedte van de rechthoek)
 *    h (de hoogte van de rechthoek)
 *
 * De rechthoeken van de drie knoppen worden hier apart bijgehouden omdat de positie van deze
 * knoppen nooit verandert. De rechthoeken van deze knoppen zijn niet alleen belangrijk om
 * te weten waar elke knop moet getekend worden, maar zijn in het geval van een muisklik ook
 * belangrijk om te achterhalen of deze klik in een van deze rechthoeken viel. Zoja wil dat
 * natuurlijk zeggen dat de gebruiker op de overeenkomstige knop heeft geklikt.
 */
static SDL_Rect new_button_rect;
static SDL_Rect stop_button_rect;
static SDL_Rect switch_button_rect;


/* De afbeelding die de "Nieuw"-knop voorstelt. */
static SDL_Texture *new_button_texture;
static SDL_Texture *stop_button_texture;
static SDL_Texture *switch_button_texture;


/*
 * Onderstaande twee lijnen maken deel uit van de minimalistische voorbeeldapplicatie:
 * ze houden de laatste positie bij waar de gebruiker geklikt heeft.
 */
int mouse_x = 0;
int mouse_y = 0;

/*
 * Geeft aan of de applicatie moet verdergaan.
 * Dit is waar zolang de gebruiker de applicatie niet wilt afsluiten door op het kruisje te klikken.
 */
int should_continue = 1;

/*
 * Controleert of het gegeven event relevant is voor onze applicatie:
 * we zijn nl. enkel geïnteresseerd in muisklikken (events van het type SDL_MOUSEBUTTONDOWN)
 * en in de gebruiker die op het kruisje van het venster klikt om de applicatie stop te zetten (SDL_QUIT).
 */
int is_relevant_event(SDL_Event *event) {
    if (event == NULL) {
        return 0;
    }
    return (event->type == SDL_MOUSEBUTTONDOWN) || (event->type == SDL_QUIT);
}

/*
 * Vangt de input uit de GUI op. Deze functie is al deels geïmplementeerd, maar je moet die zelf
 * nog afwerken. Je mag natuurlijk alles aanpassen aan deze functie, inclusies return-type en argumenten.
 */
void read_input() {
    SDL_Event event;
    
    /*
     * Handelt alle input uit de GUI af.
     * Telkens de speler een input in de GUI geeft (bv. een muisklik, muis bewegen, toets indrukken enz.)
     * wordt er een 'event' (van het type SDL_Event) gegenereerd dat hier wordt afgehandeld.
     *
     * Niet al deze events zijn relevant voor jou: als de muis bv. gewoon wordt bewogen, hoef
     * je niet te reageren op dit event.
     * We gebruiken daarom de is_relevant_event-functie die niet-gebruikte events wegfiltert.
     *
     * Zie ook https://wiki.libsdl.org/SDL_PollEvent en http://www.parallelrealities.co.uk/2011_09_01_archive.html
     */
    while (! (SDL_PollEvent(&event) && is_relevant_event(&event))) {}
    
    switch (event.type) {
        case SDL_QUIT:
            /* De gebruiker heeft op het kruisje van het venster geklikt om de applicatie te stoppen. */
            
            // TODO Te implementeren
            should_continue = 0;
            
        case SDL_MOUSEBUTTONDOWN:
            /*
             * De speler heeft met de muis geklikt: met de onderstaande lijn worden de coördinaten in het
             * het speelveld waar de speler geklikt heeft bewaard in de variabelen mouse_x en mouse_y.
             *
             * Je moet zelf nog controleren of de gebruiker in het speelbord heeft geklikt,
             * of op een knop heeft geklikt.
             */
            SDL_GetMouseState(&mouse_x, &mouse_y);
            
            // TODO Te implementeren
            break;
    }
}



void calculate () {
    for(int i=0; i<hoogte; i++) {
        for(int j=0;j<breedte;j++) {
            if (spelbord[i][j] == 1)
            {
                SDL_Rect rectangle = { j * 100, i * 100, IMAGE_WIDTH, IMAGE_HEIGHT };
                SDL_RenderCopy(renderer, blue_circle_texture, NULL, &rectangle);
                
            }
            else if (spelbord[i][j] == 2)
            {
                SDL_Rect rectangle = { j * 100, i * 100, IMAGE_WIDTH, IMAGE_HEIGHT };
                SDL_RenderCopy(renderer, red_circle_texture, NULL, &rectangle);
            }
            else
            { SDL_Rect empty = { j * 100, i * 100, IMAGE_WIDTH, IMAGE_HEIGHT };
                SDL_RenderCopy(renderer, empty_texture, NULL, &empty);
            }
        }
        
    }
}


/*
 * Deze functie moet je zelf vervolledigen: je mag alles aan deze functie
 * (inclusief return-type en argumenten) aanpassen, indien nodig.
 */
void draw_window() {
    /*
     * Maakt het hele venster blanco: deze functie kan je eventueel aanroepen voor
     * je iets begint te tekenen in het venster, zodat alle afbeeldingen die eerder
     * in het venster getekend waren verwijderd worden.
     */
    SDL_RenderClear(renderer);
    
    
    /* Twee voorbeelden van hoe je afbeeldingen tekent. */
    
    /*
     * Bereken de plaats (t.t.z., de rechthoek) waar de blauwe cirkel moet getekend worden.
     * Dit is op de plaats waar de gebruiker het laatst geklikt heeft.
     */
    // SDL_RenderCopy(renderer, achtergrond_texture, NULL, &achtergrond_rect);
    if (mouse_x > 20) {
        if (mouse_y < 6 * IMAGE_HEIGHT )
        {
            calc_rectangle_pos (mouse_x, speler);
        }
        else if (mouse_x < BUTTON_WIDTH)
        {new_game();}
        else if (mouse_x < 2 * BUTTON_WIDTH)
        {switch_instanties();}
        else if (aantal_spelinstanties == 1)
        {initialiseer();}
        else {delete_insantie();}
    }
    
    
    calculate ();
    
    /* Teken een blauwe cirkel op deze plaats. */
    
    
    // SDL_Rect rectangle = { calculate(), 490, IMAGE_WIDTH, IMAGE_HEIGHT };
    //SDL_RenderCopy(renderer, blue_circle_texture, NULL, &rectangle);
    /* Teken de Nieuw-knop op de juiste positie. */
    SDL_RenderCopy(renderer, new_button_texture, NULL, &new_button_rect);
    SDL_RenderCopy(renderer, switch_button_texture, NULL, &switch_button_rect);
    SDL_RenderCopy(renderer, stop_button_texture, NULL, &stop_button_rect);
    
    
    // TODO Te implementeren
    
    /*
     * Onderstaande code moet zeker worden uitgevoerd op het einde van deze functie.
     * Wanneer je iets tekent in het venster wordt dit venster nl. niet meteen aangepast.
     * Via de SDL_RenderPresent functie wordt het venster correct geüpdatet.
     */
    SDL_RenderPresent(renderer);
}

/*
 * Initialiseer het venster en alle extra structuren die nodig zijn om het venster te manipuleren.
 */
void initialize_window(const char *title) {
    /*
     * Code o.a. gebaseerd op: http://lazyfoo.net/tutorials/SDL/02_getting_an_image_on_the_screen/index.php
     */
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    
    int FIELD_HEIGHT = 6;
    int FIELD_WIDTH = 6;
    int window_height = (FIELD_HEIGHT * IMAGE_HEIGHT) + BUTTON_HEIGHT;
    int window_width = FIELD_WIDTH * IMAGE_WIDTH;
    /* Maak het venster aan, met de correcte dimensies. */
    window = SDL_CreateWindow(title, 0, 0, window_width, window_height, SDL_WINDOW_SHOWN);
    
    if (window == NULL) {
        printf("Couldn't set screen mode to required dimensions: %s\n", SDL_GetError());
        exit(1);
        
    }
    
    /* Initialiseer de renderer. */
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    /* Laat de default-kleur die de renderer in het venster tekent wit zijn. */
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    /*
     * Bereken de correcte positie van de rechthoeken waarin de knoppen getekend zullen worden.
     * We proberen deze knoppen onderaan het venster, ongeveer in het midden, te tekenen.
     */
    int button_y = FIELD_HEIGHT * IMAGE_HEIGHT + 10;
    
    new_button_rect = (SDL_Rect) { 0, button_y, BUTTON_WIDTH, BUTTON_HEIGHT };
    switch_button_rect = (SDL_Rect) { BUTTON_WIDTH, button_y, BUTTON_WIDTH, BUTTON_HEIGHT };
    stop_button_rect = (SDL_Rect) { 2 * BUTTON_WIDTH, button_y, BUTTON_WIDTH, BUTTON_HEIGHT };
}

/*
 * Laadt alle afbeeldingen die getoond moeten worden in.
 */
void initialize_textures() {
    
    /* Laadt de afbeeldingen in. In deze minimalistische applicatie laden we slechts twee afbeeldingen in. */
    SDL_Surface* blue_circle = SDL_LoadBMP("blue_circle.bmp");
    SDL_Surface* red_circle = SDL_LoadBMP("red_circle.bmp");
    SDL_Surface* empty = SDL_LoadBMP("blank.bmp");
    SDL_Surface* new_button = SDL_LoadBMP("new_button.bmp");
    SDL_Surface* switch_button = SDL_LoadBMP("switch_button.bmp");
    SDL_Surface* stop_button = SDL_LoadBMP("stop_button.bmp");
    
    
    /* Zet deze afbeeldingen om naar textures die getoond kunnen worden in het venster.	*/
    blue_circle_texture = SDL_CreateTextureFromSurface(renderer, blue_circle);
    red_circle_texture = SDL_CreateTextureFromSurface(renderer, red_circle);
    empty_texture = SDL_CreateTextureFromSurface(renderer, empty);
    new_button_texture = SDL_CreateTextureFromSurface(renderer, new_button);
    stop_button_texture = SDL_CreateTextureFromSurface(renderer, stop_button);
    switch_button_texture = SDL_CreateTextureFromSurface(renderer, switch_button);
    
    /* Dealloceer de SDL_Surfaces die werden aangemaakt. */
    SDL_FreeSurface(blue_circle);
    SDL_FreeSurface(red_circle);
    SDL_FreeSurface(empty);
    SDL_FreeSurface(new_button);
    SDL_FreeSurface(switch_button);
    SDL_FreeSurface(stop_button);
}

/*
 * Initialiseert onder andere het venster waarin het speelveld getoond zal worden.
 * Deze functie moet gecalled worden aan het begin van het spel, vooraleer je
 * de spelwereld begint te tekenen.
 */
void initialize_gui() {
    initialize_window("4-op-een-rij");
    initialize_textures();
}


/*
 * Dealloceert alle SDL structuren die geïnitialiseerd werden.
 */
void free_gui() {
    /* Dealloceert de SDL_Textures die werden aangemaakt. */
    SDL_DestroyTexture(blue_circle_texture);
    SDL_DestroyTexture(new_button_texture);
    
    /* Dealloceert het venster. */
    SDL_DestroyWindow(window);
    /* Dealloceert de renderer. */
    SDL_DestroyRenderer(renderer);
    
    /* Sluit SDL af. */
    SDL_Quit();
}



