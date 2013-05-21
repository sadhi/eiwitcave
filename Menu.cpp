#include "Menu.h"
#include <FreeImage.h>
#include <Windows.h>
#include <mmsystem.h>

cMenu::cMenu(void)
{
	textures[TEXTURE_BACKGROUND] = new Texture("data/PdbViewer/Menu_images/Menu_background.png");

	textures[TEXTURE_FILTER] = new Texture("data/PdbViewer/Menu_images/Filter_Button.png");
	textures[TEXTURE_FILTER_GLOW] = new Texture("data/PdbViewer/Menu_images/Filter_Button_Hover.png");

	textures[TEXTURE_COLOR] = new Texture("data/PdbViewer/Menu_images/Color_Button.png");
	textures[TEXTURE_COLOR_GLOW] = new Texture("data/PdbViewer/Menu_images/Color_Button_Glow.png");

	textures[TEXTURE_ROTATION] = new Texture("data/PdbViewer/Menu_images/Rotation_Button.png");
	textures[TEXTURE_ROTATION_GLOW] = new Texture("data/PdbViewer/Menu_images/Rotation_Button_Glow.png");
	textures[TEXTURE_ROTATION_ON] = new Texture("data/PdbViewer/Menu_images/Rotation_Button_On.png");

	textures[TEXTURE_LIGAND] = new Texture("data/PdbViewer/Menu_images/Ligand_Button.png");
	textures[TEXTURE_LIGAND_GLOW] = new Texture("data/PdbViewer/Menu_images/Ligand_Button_Glow.png");
	textures[TEXTURE_LIGAND_ON] = new Texture("data/PdbViewer/Menu_images/Ligand_Button_On.png");

	textures[TEXTURE_SS_BONDS] = new Texture("data/PdbViewer/Menu_images/SS-Bonds_Button.png");
	textures[TEXTURE_SS_BONDS_GLOW] = new Texture("data/PdbViewer/Menu_images/SS-Bonds_Button_Glow.png");
	textures[TEXTURE_SS_BONDS_ON] = new Texture("data/PdbViewer/Menu_images/SS-Bonds_Button_On.png");

	textures[TEXTURE_H_ATOMS] = new Texture("data/PdbViewer/Menu_images/H-Atoms_Button.png");
	textures[TEXTURE_H_ATOMS_GLOW] = new Texture("data/PdbViewer/Menu_images/H-Atoms_Button_Glow.png");
	textures[TEXTURE_H_ATOMS_ON] = new Texture("data/PdbViewer/Menu_images/H-Atoms_Button_On.png");

	/*textures[TEXTURE_DOMAINS] = new Texture("data/PdbViewer/Menu_images/Filter_Domains_Button.png");
	textures[TEXTURE_DOMAINS_GLOW] = new Texture("data/PdbViewer/Menu_images/Filter_Domains_Button_Glow.png");
	textures[TEXTURE_DOMAINS_ON] = new Texture("data/PdbViewer/Menu_images/Filter_Domains_Button_On.png");*/

	textures[TEXTURE_BACK] = new Texture("data/PdbViewer/Menu_images/Back_Button.png");
	textures[TEXTURE_BACK_GLOW] = new Texture("data/PdbViewer/Menu_images/Back_Button_Glow.png");

	textures[TEXTURE_BY_ELEMENT] = new Texture("data/PdbViewer/Menu_images/Color_Element_Button.png");
	textures[TEXTURE_BY_ELEMENT_GLOW] = new Texture("data/PdbViewer/Menu_images/Color_Element_Button_Glow.png");
	textures[TEXTURE_BY_ELEMENT_ON] = new Texture("data/PdbViewer/Menu_images/Color_Element_Button_On.png");

	textures[TEXTURE_BY_DOMAIN] = new Texture("data/PdbViewer/Menu_images/Color_Domain_Button.png");
	textures[TEXTURE_BY_DOMAIN_GLOW] = new Texture("data/PdbViewer/Menu_images/Color_Domain_Button_Glow.png");
	textures[TEXTURE_BY_DOMAIN_ON] = new Texture("data/PdbViewer/Menu_images/Color_Domain_Button_On.png");

	textures[TEXTURE_PROTEIN] = new Texture("data/PdbViewer/Menu_images/Protein_Button.png");
	textures[TEXTURE_PROTEIN_GLOW] = new Texture("data/PdbViewer/Menu_images/Protein_Button_Glow.png");
	textures[TEXTURE_PROTEIN_ON] = new Texture("data/PdbViewer/Menu_images/Protein_Button_On.png");

	textures[TEXTURE_SETTINGS] = new Texture("data/PdbViewer/Menu_images/Settings_Button.png");
	textures[TEXTURE_SETTINGS_GLOW] = new Texture("data/PdbViewer/Menu_images/Settings_Button_Glow.png");

	textures[TEXTURE_HIGH] = new Texture("data/PdbViewer/Menu_images/High_Button.png");
	textures[TEXTURE_HIGH_GLOW] = new Texture("data/PdbViewer/Menu_images/High_Button_Glow.png");
	textures[TEXTURE_HIGH_ON] = new Texture("data/PdbViewer/Menu_images/High_Button_On.png");

	textures[TEXTURE_MEDIUM] = new Texture("data/PdbViewer/Menu_images/Medium_Button.png");
	textures[TEXTURE_MEDIUM_GLOW] = new Texture("data/PdbViewer/Menu_images/Medium_Button_Glow.png");
	textures[TEXTURE_MEDIUM_ON] = new Texture("data/PdbViewer/Menu_images/Medium_Button_On.png");

	textures[TEXTURE_LOW] = new Texture("data/PdbViewer/Menu_images/Low_Button.png");
	textures[TEXTURE_LOW_GLOW] = new Texture("data/PdbViewer/Menu_images/Low_Button_Glow.png");
	textures[TEXTURE_LOW_ON] = new Texture("data/PdbViewer/Menu_images/Low_Button_On.png");

	textures[TEXTURE_TRANSLATE] = new Texture("data/PdbViewer/Menu_images/Translate_Button.png");
	textures[TEXTURE_TRANSLATE_GLOW] = new Texture("data/PdbViewer/Menu_images/Translate_Button_Glow.png");
	textures[TEXTURE_TRANSLATE_ON] = new Texture("data/PdbViewer/Menu_images/Translate_Button_On.png");

	MenuState = MENU_MAIN;
	//InitSound();
	resetButtons();
	resetModes();
}

cMenu::~cMenu(void)
{
}

//void cMenu::InitSound(void)
//{
//	channel = 0;
//
//	FMOD::System_Create(&system);
//
//	system->init(32, FMOD_INIT_NORMAL, 0);
//	system->createSound("sounds/jaguar.wav", FMOD_SOFTWARE, 0, &clickSound);
//}

void cMenu::resetModes(void)
{ /*
	ModeRotation = false;
	ModeLigand = true;
	ModeSSBonds = false;
	ModeHAtoms = true;
	//ModeDomains = false;
	ModeProtein = false;
	ModeByElement = true;
	ModeByDomain = false;
	ModeHigh = false;
	ModeMedium = true;
	ModeLow = false;
	ModeTranslation = false;
	*/
	ModeRotation = false;
	ModeLigand = false;
	ModeSSBonds = false;
	ModeHAtoms = false;
	//ModeDomains = false;
	ModeProtein = true;
	ModeByElement = true;
	ModeByDomain = false;
	ModeHigh = false;
	ModeMedium = true;
	ModeLow = false;
	ModeTranslation = false;
	Mode3DSelectie = false;
	ModeSelectSingelAtom = false;
	ModeDistanceMeasure = true;
}

void cMenu::resetButtons(void)
{
	buttonFilterGlow = false;
	buttonColorGlow = false;
	buttonRotationGlow = false;
	buttonLigandGlow = false;
	buttonSSBondsGlow = false;
	buttonHATOMSGLow = false;
	//buttonDomainsGlow = false;
	buttonProteinGlow = false;
	buttonBackGlow = false;
	buttonByElementGlow = false;
	buttonByDomainGlow = false;
	buttonHighGlow = false;
	buttonMediumGlow = false;
	buttonLowGlow = false;
	buttonSettingsGlow = false;
	buttonTranslationGlow = false;
}

int cMenu::WhichButtonIsActive(void)
{
	if(buttonFilterGlow) { return BUTTON_FILTER; }
	if(buttonColorGlow) { return BUTTON_COLOR; }
	if(buttonRotationGlow) { return BUTTON_ROTATION; }
	if(buttonLigandGlow) { return BUTTON_FILTER_LIGAND; }
	if(buttonSSBondsGlow) { return BUTTON_FILTER_SS_BONDS; }
	if(buttonHATOMSGLow) { return BUTTON_FILTER_H_ATOMS; }
	//if(buttonDomainsGlow) { return BUTTON_FILTER_DOMAINS; }
	if(buttonProteinGlow) { return BUTTON_FILTER_PROTEIN; }
	if(buttonBackGlow) 
	{ 
		if(MenuState == MENU_FILTER)
			return BUTTON_FILTER_BACK; 
		else if(MenuState == MENU_SETTINGS)
			return BUTTON_SETTINGS_BACK; 
		else
			return BUTTON_COLOR_BACK;
	}
	if(buttonByElementGlow) { return BUTTON_COLOR_ELEMENT; }
	if(buttonByDomainGlow) { return BUTTON_COLOR_DOMAIN; }
	if(buttonHighGlow) { return BUTTON_HIGH; }
	if(buttonMediumGlow) { return BUTTON_MEDIUM; }
	if(buttonLowGlow) { return BUTTON_LOW; }
	if(buttonSettingsGlow) { return BUTTON_SETTINGS; }
	if(buttonTranslationGlow) { return BUTTON_TRANSLATE; }

	return BUTTON_NONE;
}

void cMenu::SetButtonGlow(int button)
{
	resetButtons();
	switch (MenuState)
	{
	case MENU_MAIN:
		switch (button)
		{
			case BUTTON_NONE :
				break;
			case BUTTON_FILTER :
				buttonFilterGlow = true;
				break;
			case BUTTON_COLOR :
				buttonColorGlow = true;
				break;
			case BUTTON_ROTATION :
				buttonRotationGlow = true;
				break;
			case BUTTON_SETTINGS :
				buttonSettingsGlow = true;
				break;
			case BUTTON_TRANSLATE :
				buttonTranslationGlow = true;
				break;
			default:
				throw "You`ve cocked up!!!";
				break;
		}
		break;
	case MENU_FILTER:
		switch (button)
		{
			case BUTTON_NONE :
				break;
			case BUTTON_FILTER_LIGAND :
				buttonLigandGlow = true;
				break;
			case BUTTON_FILTER_SS_BONDS :
				buttonSSBondsGlow = true;
				break;
			case BUTTON_FILTER_H_ATOMS:
				buttonHATOMSGLow = true;
				break;
			/*case BUTTON_FILTER_DOMAINS:
				buttonDomainsGlow = true;
				break;*/
			case BUTTON_FILTER_PROTEIN:
				buttonProteinGlow = true;
				break;
			case BUTTON_FILTER_BACK :
				buttonBackGlow = true;
				break;
			default:
				throw "You`ve cocked up!!!";
				break;
		}
		break;

	case MENU_COLOR:
		switch (button)
		{
			case BUTTON_NONE :
				break;
			case BUTTON_COLOR_ELEMENT:
				buttonByElementGlow = true;
				break;
			case BUTTON_COLOR_DOMAIN:
				buttonByDomainGlow = true;
				break;
			case BUTTON_COLOR_BACK :
				buttonBackGlow = true;
				break;
			default:
				throw "You`ve cocked up!!!";
				break;
		}
		break;

	case MENU_SETTINGS:
		switch (button)
		{
			case BUTTON_NONE :
				break;
			case BUTTON_HIGH:
				buttonHighGlow = true;
				break;
			case BUTTON_MEDIUM:
				buttonMediumGlow = true;
				break;
			case BUTTON_LOW :
				buttonLowGlow = true;
				break;
			case BUTTON_SETTINGS_BACK :
				buttonBackGlow = true;
				break;
			default:
				throw "You`ve cocked up!!!";
				break;
		}
		break;

	default:
		throw "You`ve cocked up!!!";
		break;
	}
}

void cMenu::AutoSetButtonGlow(glm::vec2 pos)
{
	//rotate the x/y positions to the rotated button positions
	float x = pos[0]*glm::cos(1.57f) - pos[1]*glm::sin(1.57f);
	float y = pos[0]*glm::sin(1.57f) + pos[1]*glm::cos(1.57f);

	switch (MenuState)
	{
	case MENU_MAIN:

		if(y >= BUTTON_Y && y <= BUTTON_Y + BUTTON_WIDTH)
		{
			for(int i = 0; i < NUMBER_OF_BUTTONS; i++)
			{
				if(x >= BUTTON_X && x <= BUTTON_X + ((i+1) * BUTTON_HEIGHT) + (i * BUTTON_INTERVAL))
				{
					SetButtonGlow(i+1);
					return;
				}
			}
		}
	
		SetButtonGlow(BUTTON_NONE);
		break;

	case MENU_FILTER:
		if(y >= BUTTON_Y && y <= BUTTON_Y + BUTTON_WIDTH)
		{
			for(int i = 0; i < NUMBER_OF_FILTER_BUTTONS; i++)
			{
				if(x >= BUTTON_X && x <= BUTTON_X + ((i+1) * BUTTON_HEIGHT) + (i * BUTTON_INTERVAL))
				{
					SetButtonGlow(i+1);
					return;
				}
			}
		}
	
		SetButtonGlow(BUTTON_NONE);
		break;

	case MENU_COLOR:
		if(y >= BUTTON_Y && y <= BUTTON_Y + BUTTON_WIDTH)
		{
			for(int i = 0; i < NUMBER_OF_COLOR_BUTTONS; i++)
			{
				if(x >= BUTTON_X && x <= BUTTON_X + ((i+1) * BUTTON_HEIGHT) + (i * BUTTON_INTERVAL))
				{
					SetButtonGlow(i+1);
					return;
				}
			}
		}
		SetButtonGlow(BUTTON_NONE);
		break;
	case MENU_SETTINGS:
		if(y >= BUTTON_Y && y <= BUTTON_Y + BUTTON_WIDTH)
		{
			for(int i = 0; i < NUMBER_OF_SETTINGS_BUTTONS; i++)
			{
				if(x >= BUTTON_X && x <= BUTTON_X + ((i+1) * BUTTON_HEIGHT) + (i * BUTTON_INTERVAL))
				{
					SetButtonGlow(i+1);
					return;
				}
			}
		}
	
		SetButtonGlow(BUTTON_NONE);
		break;

	default:
		throw "You`ve cocked up!!!";
		break;
	}
}

void cMenu::playClickSound(void)
{
	//LPCWSTR sound = "Sounds/jaguar.wav";
	PlaySound(TEXT("Sounds/invaderkilled.wav"),NULL, SND_ASYNC);
	/*FMOD_RESULT result = system->getDriver(1);
	if(result)
	{
		system->playSound(FMOD_CHANNEL_FREE, clickSound, false, &channel);
		system->update();
	}*/
}

void cMenu::AutoSetMode(void)
{
	switch (MenuState)
	{
	case MENU_MAIN:
		switch (WhichButtonIsActive())
		{
			case BUTTON_NONE :
				break;
			case BUTTON_FILTER :
				playClickSound();
				MenuState = MENU_FILTER;
				break;
			case BUTTON_COLOR :
				playClickSound();
				MenuState = MENU_COLOR;
				break;
			case BUTTON_ROTATION :
				playClickSound();
				ModeRotation = !ModeRotation;
				if(ModeRotation)
					ModeTranslation = false;
				break;
			case BUTTON_SETTINGS :
				playClickSound();
				MenuState = MENU_SETTINGS;
				break;
			case BUTTON_TRANSLATE :
				playClickSound();
				ModeTranslation = !ModeTranslation;
				if(ModeTranslation)
					ModeRotation = false;
				break;
			default:
				throw "You`ve cocked up!!!";
				break;
		}
		break;

	case MENU_FILTER:
		switch (WhichButtonIsActive())
		{
			case BUTTON_NONE :
				break;
			case BUTTON_FILTER_LIGAND :
				playClickSound();
				ModeLigand = !ModeLigand;
				break;
			case BUTTON_FILTER_SS_BONDS :
				playClickSound();
				ModeSSBonds = !ModeSSBonds;
				break;
			case BUTTON_FILTER_H_ATOMS :
				playClickSound();
				ModeHAtoms = !ModeHAtoms;
				break;
			/*case BUTTON_FILTER_DOMAINS :
				playClickSound();
				ModeDomains = !ModeDomains;
				break;*/
			case BUTTON_FILTER_PROTEIN :
				playClickSound();
				ModeProtein = !ModeProtein;
				break;
			case BUTTON_FILTER_BACK :
				playClickSound();
				MenuState = MENU_MAIN;
				break;
			default:
				throw "You`ve cocked up!!!";
				break;
		}
		break;

	case MENU_COLOR:
	switch (WhichButtonIsActive())
	{
		case BUTTON_NONE :
			break;
		case BUTTON_COLOR_ELEMENT :
			if(!ModeByElement)
			{
				playClickSound();
				ModeByElement = true;
				ModeByDomain = false;
			}
			break;
		case BUTTON_COLOR_DOMAIN :
			if(!ModeByDomain)
			{
				playClickSound();
				ModeByElement = false;
				ModeByDomain = true;
			}
			break;
		case BUTTON_COLOR_BACK :
			playClickSound();
			MenuState = MENU_MAIN;
			break;
		default:
			throw "You`ve cocked up!!!";
			break;
	}
	break;

	case MENU_SETTINGS:
	switch (WhichButtonIsActive())
	{
		case BUTTON_NONE :
			break;
		case BUTTON_HIGH :
			if(!ModeHigh)
			{
				playClickSound();
				ModeHigh = true;
				ModeMedium = false;
				ModeLow = false;
			}
			break;
		case BUTTON_MEDIUM :
			if(!ModeMedium)
			{
				playClickSound();
				ModeHigh = false;
				ModeMedium = true;
				ModeLow = false;
			}
			break;
		case BUTTON_LOW :
			if(!ModeLow)
			{
				playClickSound();
				ModeHigh = false;
				ModeMedium = false;
				ModeLow = true;
			}
			break;
		case BUTTON_SETTINGS_BACK :
			playClickSound();
			MenuState = MENU_MAIN;
			break;
		default:
			throw "You`ve cocked up!!!";
			break;
	}
	break;

	default:
		throw "You`ve cocked up!!!";
		break;
	}
}

void cMenu::menuDraw(float x, float y, float z, float width, float height)
{
	glColor4f(1,1,1,1);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BACKGROUND]->textureId);

	glBegin(GL_QUADS);
		glNormal3f(0.0,0.0,1.0);
		glTexCoord2f(1, 0);	glVertex3f(x + height, y + width, z);
		glTexCoord2f(1, 1);	glVertex3f(x, y + width, z);
		glTexCoord2f(0, 1);	glVertex3f(x, y, z);
		glTexCoord2f(0, 0);	glVertex3f(x + height, y, z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cMenu::filterDraw(float x, float y, float z, float width, float height)
{
	glColor4f(1,1,1,1);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	if(buttonFilterGlow)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_FILTER_GLOW]->textureId);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_FILTER]->textureId);
	}

	glBegin(GL_QUADS);
		glNormal3f(0.0,0.0,1.0);
		glTexCoord2f(1, 0);	glVertex3f(x + height, y + width, z);
		glTexCoord2f(1, 1);	glVertex3f(x, y + width, z);
		glTexCoord2f(0, 1);	glVertex3f(x, y, z);
		glTexCoord2f(0, 0);	glVertex3f(x + height, y, z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cMenu::zoomDraw(float x, float y, float z, float width, float height)
{
	glColor4f(1,1,1,1);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	if(buttonColorGlow)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_COLOR_GLOW]->textureId);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_COLOR]->textureId);
	}

	glBegin(GL_QUADS);
		glNormal3f(0.0,0.0,1.0);
		glTexCoord2f(1, 0);	glVertex3f(x + height, y + width, z);
		glTexCoord2f(1, 1);	glVertex3f(x, y + width, z);
		glTexCoord2f(0, 1);	glVertex3f(x, y, z);
		glTexCoord2f(0, 0);	glVertex3f(x + height, y, z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cMenu::rotationDraw(float x, float y, float z, float width, float height)
{
	glColor4f(1,1,1,1);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	if(buttonRotationGlow)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_ROTATION_GLOW]->textureId);
	}
	else if(ModeRotation)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_ROTATION_ON]->textureId);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_ROTATION]->textureId);
	}

	glBegin(GL_QUADS);
		glNormal3f(0.0,0.0,1.0);
		glTexCoord2f(1, 0);	glVertex3f(x + height, y + width, z);
		glTexCoord2f(1, 1);	glVertex3f(x, y + width, z);
		glTexCoord2f(0, 1);	glVertex3f(x, y, z);
		glTexCoord2f(0, 0);	glVertex3f(x + height, y, z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cMenu::ligandDraw(float x, float y, float z, float width, float height)
{
	glColor4f(1,1,1,1);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);

	if(buttonLigandGlow)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_LIGAND_GLOW]->textureId);
	}
	else if(ModeLigand)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_LIGAND_ON]->textureId);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_LIGAND]->textureId);
	}

	glBegin(GL_QUADS);
		glNormal3f(0.0,0.0,1.0);
		glTexCoord2f(1, 0);	glVertex3f(x + height, y + width, z);
		glTexCoord2f(1, 1);	glVertex3f(x, y + width, z);
		glTexCoord2f(0, 1);	glVertex3f(x, y, z);
		glTexCoord2f(0, 0);	glVertex3f(x + height, y, z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cMenu::ssBondDraw(float x, float y, float z, float width, float height)
{
	glColor4f(1,1,1,1);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);

	if(buttonSSBondsGlow)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_SS_BONDS_GLOW]->textureId);
	}
	else if(ModeSSBonds)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_SS_BONDS_ON]->textureId);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_SS_BONDS]->textureId);
	}

	glBegin(GL_QUADS);
		glNormal3f(0.0,0.0,1.0);
		glTexCoord2f(1, 0);	glVertex3f(x + height, y + width, z);
		glTexCoord2f(1, 1);	glVertex3f(x, y + width, z);
		glTexCoord2f(0, 1);	glVertex3f(x, y, z);
		glTexCoord2f(0, 0);	glVertex3f(x + height, y, z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cMenu::hAtomsDraw(float x, float y, float z, float width, float height)
{
	glColor4f(1,1,1,1);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);

	if(buttonHATOMSGLow)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_H_ATOMS_GLOW]->textureId);
	}
	else if(ModeHAtoms)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_H_ATOMS_ON]->textureId);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_H_ATOMS]->textureId);
	}

	glBegin(GL_QUADS);
		glNormal3f(0.0,0.0,1.0);
		glTexCoord2f(1, 0);	glVertex3f(x + height, y + width, z);
		glTexCoord2f(1, 1);	glVertex3f(x, y + width, z);
		glTexCoord2f(0, 1);	glVertex3f(x, y, z);
		glTexCoord2f(0, 0);	glVertex3f(x + height, y, z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

//void cMenu::domainsDraw(float x, float y, float z, float width, float height)
//{
//	glColor4f(1,1,1,1);
//	glActiveTexture(GL_TEXTURE0);
//	glEnable(GL_TEXTURE_2D);
//
//	if(buttonDomainsGlow)
//	{
//		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_DOMAINS_GLOW]->textureId);
//	}
//	else if(ModeDomains)
//	{
//		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_DOMAINS_ON]->textureId);
//	}
//	else
//	{
//		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_DOMAINS]->textureId);
//	}
//
//	glBegin(GL_QUADS);
//		glNormal3f(0.0,0.0,1.0);
//		glTexCoord2f(1, 0);	glVertex3f(x + height, y + width, z);
//		glTexCoord2f(1, 1);	glVertex3f(x, y + width, z);
//		glTexCoord2f(0, 1);	glVertex3f(x, y, z);
//		glTexCoord2f(0, 0);	glVertex3f(x + height, y, z);
//	glEnd();
//
//	glDisable(GL_TEXTURE_2D);
//}

void cMenu::backDraw(float x, float y, float z, float width, float height)
{
	glColor4f(1,1,1,1);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	if(buttonBackGlow)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BACK_GLOW]->textureId);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BACK]->textureId);
	}

	glBegin(GL_QUADS);
		glNormal3f(0.0,0.0,1.0);
		glTexCoord2f(1, 0);	glVertex3f(x + height, y + width, z);
		glTexCoord2f(1, 1);	glVertex3f(x, y + width, z);
		glTexCoord2f(0, 1);	glVertex3f(x, y, z);
		glTexCoord2f(0, 0);	glVertex3f(x + height, y, z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cMenu::byElementDraw(float x, float y, float z, float width, float height)
{
	glColor4f(1,1,1,1);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);

	if(buttonByElementGlow)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BY_ELEMENT_GLOW]->textureId);
	}
	else if(ModeByElement)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BY_ELEMENT_ON]->textureId);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BY_ELEMENT]->textureId);
	}

	glBegin(GL_QUADS);
		glNormal3f(0.0,0.0,1.0);
		glTexCoord2f(1, 0);	glVertex3f(x + height, y + width, z);
		glTexCoord2f(1, 1);	glVertex3f(x, y + width, z);
		glTexCoord2f(0, 1);	glVertex3f(x, y, z);
		glTexCoord2f(0, 0);	glVertex3f(x + height, y, z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cMenu::byDomainDraw(float x, float y, float z, float width, float height)
{
	glColor4f(1,1,1,1);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);

	if(buttonByDomainGlow)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BY_DOMAIN_GLOW]->textureId);
	}
	else if(ModeByDomain)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BY_DOMAIN_ON]->textureId);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_BY_DOMAIN]->textureId);
	}

	glBegin(GL_QUADS);
		glNormal3f(0.0,0.0,1.0);
		glTexCoord2f(1, 0);	glVertex3f(x + height, y + width, z);
		glTexCoord2f(1, 1);	glVertex3f(x, y + width, z);
		glTexCoord2f(0, 1);	glVertex3f(x, y, z);
		glTexCoord2f(0, 0);	glVertex3f(x + height, y, z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cMenu::proteinDraw(float x, float y, float z, float width, float height)
{
	glColor4f(1,1,1,1);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);

	if(buttonProteinGlow)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_PROTEIN_GLOW]->textureId);
	}
	else if(ModeProtein)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_PROTEIN_ON]->textureId);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_PROTEIN]->textureId);
	}

	glBegin(GL_QUADS);
		glNormal3f(0.0,0.0,1.0);
		glTexCoord2f(1, 0);	glVertex3f(x + height, y + width, z);
		glTexCoord2f(1, 1);	glVertex3f(x, y + width, z);
		glTexCoord2f(0, 1);	glVertex3f(x, y, z);
		glTexCoord2f(0, 0);	glVertex3f(x + height, y, z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cMenu::settingsDraw(float x, float y, float z, float width, float height)
{
	glColor4f(1,1,1,1);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);

	if(buttonSettingsGlow)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_SETTINGS_GLOW]->textureId);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_SETTINGS]->textureId);
	}

	glBegin(GL_QUADS);
		glNormal3f(0.0,0.0,1.0);
		glTexCoord2f(1, 0);	glVertex3f(x + height, y + width, z);
		glTexCoord2f(1, 1);	glVertex3f(x, y + width, z);
		glTexCoord2f(0, 1);	glVertex3f(x, y, z);
		glTexCoord2f(0, 0);	glVertex3f(x + height, y, z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cMenu::highDraw(float x, float y, float z, float width, float height)
{
	glColor4f(1,1,1,1);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);

	if(buttonHighGlow)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_HIGH_GLOW]->textureId);
	}
	else if(ModeHigh)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_HIGH_ON]->textureId);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_HIGH]->textureId);
	}

	glBegin(GL_QUADS);
		glNormal3f(0.0,0.0,1.0);
		glTexCoord2f(1, 0);	glVertex3f(x + height, y + width, z);
		glTexCoord2f(1, 1);	glVertex3f(x, y + width, z);
		glTexCoord2f(0, 1);	glVertex3f(x, y, z);
		glTexCoord2f(0, 0);	glVertex3f(x + height, y, z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cMenu::mediumDraw(float x, float y, float z, float width, float height)
{
	glColor4f(1,1,1,1);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);

	if(buttonMediumGlow)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_MEDIUM_GLOW]->textureId);
	}
	else if(ModeMedium)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_MEDIUM_ON]->textureId);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_MEDIUM]->textureId);
	}

	glBegin(GL_QUADS);
		glNormal3f(0.0,0.0,1.0);
		glTexCoord2f(1, 0);	glVertex3f(x + height, y + width, z);
		glTexCoord2f(1, 1);	glVertex3f(x, y + width, z);
		glTexCoord2f(0, 1);	glVertex3f(x, y, z);
		glTexCoord2f(0, 0);	glVertex3f(x + height, y, z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cMenu::lowDraw(float x, float y, float z, float width, float height)
{
	glColor4f(1,1,1,1);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);

	if(buttonLowGlow)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_LOW_GLOW]->textureId);
	}
	else if(ModeLow)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_LOW_ON]->textureId);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_LOW]->textureId);
	}

	glBegin(GL_QUADS);
		glNormal3f(0.0,0.0,1.0);
		glTexCoord2f(1, 0);	glVertex3f(x + height, y + width, z);
		glTexCoord2f(1, 1);	glVertex3f(x, y + width, z);
		glTexCoord2f(0, 1);	glVertex3f(x, y, z);
		glTexCoord2f(0, 0);	glVertex3f(x + height, y, z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cMenu::translationDraw(float x, float y, float z, float width, float height)
{
	glColor4f(1,1,1,1);
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);

	if(buttonTranslationGlow)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_TRANSLATE_GLOW]->textureId);
	}
	else if(ModeTranslation)
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_TRANSLATE_ON]->textureId);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, textures[TEXTURE_TRANSLATE]->textureId);
	}

	glBegin(GL_QUADS);
		glNormal3f(0.0,0.0,1.0);
		glTexCoord2f(1, 0);	glVertex3f(x + height, y + width, z);
		glTexCoord2f(1, 1);	glVertex3f(x, y + width, z);
		glTexCoord2f(0, 1);	glVertex3f(x, y, z);
		glTexCoord2f(0, 0);	glVertex3f(x + height, y, z);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cMenu::Draw()
{//TODO fix it!!!!
	//AutoSetButtonGlow(0.75,-1.9);
	glPushMatrix();
	glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
	//glTranslatef(0.0f, 0.0f, 0.0f);
	menuDraw(MENU_X, MENU_Y, 0.5f, MENU_WIDTH, MENU_HEIGHT);
	switch (MenuState)
	{
	case MENU_MAIN:
		filterDraw(BUTTON_X, BUTTON_Y, 0.6f, BUTTON_WIDTH, BUTTON_HEIGHT);
		zoomDraw(BUTTON_X + BUTTON_HEIGHT + BUTTON_INTERVAL, BUTTON_Y, 0.6f, BUTTON_WIDTH, BUTTON_HEIGHT);
		rotationDraw(BUTTON_X + BUTTON_HEIGHT*2 + BUTTON_INTERVAL*2, BUTTON_Y, 0.6f, BUTTON_WIDTH, BUTTON_HEIGHT);
		translationDraw(BUTTON_X + BUTTON_HEIGHT*3 + BUTTON_INTERVAL*3, BUTTON_Y, 0.6f, BUTTON_WIDTH, BUTTON_HEIGHT);
		settingsDraw(BUTTON_X + BUTTON_HEIGHT*4 + BUTTON_INTERVAL*4, BUTTON_Y, 0.6f, BUTTON_WIDTH, BUTTON_HEIGHT);
	break;
	case MENU_FILTER:
		ligandDraw(BUTTON_X, BUTTON_Y, 0.6f, BUTTON_WIDTH, BUTTON_HEIGHT);
		ssBondDraw(BUTTON_X + BUTTON_HEIGHT + BUTTON_INTERVAL, BUTTON_Y, 0.6f, BUTTON_WIDTH, BUTTON_HEIGHT);
		hAtomsDraw(BUTTON_X + BUTTON_HEIGHT*2 + BUTTON_INTERVAL*2, BUTTON_Y, 0.6f, BUTTON_WIDTH, BUTTON_HEIGHT);
		//domainsDraw(BUTTON_X + BUTTON_HEIGHT*3 + BUTTON_INTERVAL*3, BUTTON_Y, 0.6f, BUTTON_WIDTH, BUTTON_HEIGHT);
		proteinDraw(BUTTON_X + BUTTON_HEIGHT*3 + BUTTON_INTERVAL*3, BUTTON_Y, 0.6f, BUTTON_WIDTH, BUTTON_HEIGHT);
		backDraw(BUTTON_X + BUTTON_HEIGHT*4 + BUTTON_INTERVAL*4, BUTTON_Y, 0.6f, BUTTON_WIDTH, BUTTON_HEIGHT);
		break;
	case MENU_COLOR:
		byElementDraw(BUTTON_X, BUTTON_Y, 0.6f, BUTTON_WIDTH, BUTTON_HEIGHT);
		byDomainDraw(BUTTON_X + BUTTON_HEIGHT + BUTTON_INTERVAL, BUTTON_Y, 0.6f, BUTTON_WIDTH, BUTTON_HEIGHT);
		backDraw(BUTTON_X + BUTTON_HEIGHT*2 + BUTTON_INTERVAL*2, BUTTON_Y, 0.6f, BUTTON_WIDTH, BUTTON_HEIGHT);
		break;
	case MENU_SETTINGS :
		highDraw(BUTTON_X, BUTTON_Y, 0.6f, BUTTON_WIDTH, BUTTON_HEIGHT);
		mediumDraw(BUTTON_X + BUTTON_HEIGHT + BUTTON_INTERVAL, BUTTON_Y, 0.6f, BUTTON_WIDTH, BUTTON_HEIGHT);
		lowDraw(BUTTON_X + BUTTON_HEIGHT*2 + BUTTON_INTERVAL*2, BUTTON_Y, 0.6f, BUTTON_WIDTH, BUTTON_HEIGHT);
		backDraw(BUTTON_X + BUTTON_HEIGHT*3 + BUTTON_INTERVAL*3, BUTTON_Y, 0.6f, BUTTON_WIDTH, BUTTON_HEIGHT);
		break;
	default:
		throw "You`ve cocked up!";
		break;
	}
	//glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glPopMatrix();
}