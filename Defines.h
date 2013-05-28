#pragma once
//#define BUTTON_CLICK_DELAY 30
//info stuff
#define NUMBER_OF_TEXTURES 45
#define NUMBER_OF_BUTTONS 5
#define NUMBER_OF_FILTER_BUTTONS 5
#define NUMBER_OF_COLOR_BUTTONS 3
#define NUMBER_OF_SETTINGS_BUTTONS 4

//textures
#define TEXTURE_BACKGROUND 0
#define TEXTURE_FILTER 1
#define TEXTURE_FILTER_GLOW 2
#define TEXTURE_COLOR 3
#define TEXTURE_COLOR_GLOW 4
#define TEXTURE_ROTATION 5
#define TEXTURE_ROTATION_GLOW 6
#define TEXTURE_ROTATION_ON 7
#define TEXTURE_LIGAND 8
#define TEXTURE_LIGAND_GLOW 9
#define TEXTURE_LIGAND_ON 10
#define TEXTURE_SS_BONDS 11
#define TEXTURE_SS_BONDS_GLOW 12
#define TEXTURE_SS_BONDS_ON 13
#define TEXTURE_H_ATOMS 14
#define TEXTURE_H_ATOMS_GLOW 15
#define TEXTURE_H_ATOMS_ON 16
#define TEXTURE_DOMAINS 17
#define TEXTURE_DOMAINS_GLOW 18
#define TEXTURE_DOMAINS_ON 19
#define TEXTURE_BACK 20
#define TEXTURE_BACK_GLOW 21
#define TEXTURE_BY_ELEMENT 22
#define TEXTURE_BY_ELEMENT_GLOW 23
#define TEXTURE_BY_ELEMENT_ON 24
#define TEXTURE_BY_DOMAIN 25
#define TEXTURE_BY_DOMAIN_GLOW 26
#define TEXTURE_BY_DOMAIN_ON 27
#define TEXTURE_PROTEIN 28
#define TEXTURE_PROTEIN_GLOW 29
#define TEXTURE_PROTEIN_ON 30
#define TEXTURE_SETTINGS 31
#define TEXTURE_SETTINGS_GLOW 32
#define TEXTURE_HIGH 33
#define TEXTURE_HIGH_GLOW 34
#define TEXTURE_HIGH_ON 35
#define TEXTURE_LOW 36
#define TEXTURE_LOW_GLOW 37
#define TEXTURE_LOW_ON 38
#define TEXTURE_MEDIUM 39
#define TEXTURE_MEDIUM_GLOW 40
#define TEXTURE_MEDIUM_ON 41
#define TEXTURE_TRANSLATE 42
#define TEXTURE_TRANSLATE_GLOW 43
#define TEXTURE_TRANSLATE_ON 44

#define BUTTON_NONE 0
//main buttons
#define BUTTON_FILTER 1
#define BUTTON_COLOR 2
#define BUTTON_ROTATION 3
#define BUTTON_TRANSLATE 4
#define BUTTON_SETTINGS 5

//filter buttons
#define BUTTON_FILTER_LIGAND 1
#define BUTTON_FILTER_SS_BONDS 2
#define BUTTON_FILTER_H_ATOMS 3
//#define BUTTON_FILTER_DOMAINS 4
#define BUTTON_FILTER_PROTEIN 4
#define BUTTON_FILTER_BACK 5

//color buttons
#define BUTTON_COLOR_ELEMENT 1
#define BUTTON_COLOR_DOMAIN 2
#define BUTTON_COLOR_BACK 3

//settings buttons
#define BUTTON_HIGH 1
#define BUTTON_MEDIUM 2
#define BUTTON_LOW 3
#define BUTTON_SETTINGS_BACK 4

//button info shizzle
#define MENU_Y -.525f
#define MENU_X 0.0
#define MENU_WIDTH 1
#define MENU_HEIGHT 3
#define BUTTON_Y -.3f
#define BUTTON_X 0.15f
#define BUTTON_INTERVAL 0.1f
#define BUTTON_WIDTH .45f
#define BUTTON_HEIGHT 0.15f

//menu states
#define MENU_MAIN 1
#define MENU_FILTER 2
#define MENU_COLOR 3
#define MENU_SETTINGS 4