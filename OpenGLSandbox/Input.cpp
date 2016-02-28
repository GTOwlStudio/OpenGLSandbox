#include "Input.h"


// Constructeur et Destructeur

Input::Input() : m_x(0), m_y(0), m_xRel(0), m_yRel(0), m_terminer(false),
	m_window_resized(false), m_updateLoopRotation(0)
{
    // Initialisation du tableau m_touches[]
	printf("Careful with the constructor of Input make sure this line is just diplayed once");
	for (int i(0); i < SDL_NUM_SCANCODES; i++) {
		m_keys[i] = false;
	}


    // Initialisation du tableau m_boutonsSouris[]

	for (int i(0); i < 8; i++) {
		m_mouseButton[i] = false;
	}
}


Input::~Input()
{

}


// Méthodes

void Input::updateEvenements()
{
    // Pour éviter des mouvements fictifs de la souris, on réinitialise les coordonnées relatives

    m_xRel = 0;
    m_yRel = 0;

	m_x = m_events.motion.x;
    m_y = m_events.motion.y;
//	m_updateLoopRotation = 0;
    // Boucle d'évènements
	m_window_resized = false;
    while(SDL_PollEvent(&m_events))
    {
        // Switch sur le type d'évènement

        switch(m_events.type)
        {
            // Cas d'une touche enfoncée

            case SDL_KEYDOWN:
				//m_touches[m_evenements.key.keysym.scancode] = true;
				m_keys[m_events.key.keysym.sym] = true;
            break;


            // Cas d'une touche relâchée

            case SDL_KEYUP:
              //  m_touches[m_evenements.key.keysym.scancode] = false;
				m_keys[m_events.key.keysym.sym] = false;
            break;


            // Cas de pression sur un bouton de la souris

            case SDL_MOUSEBUTTONDOWN:

                m_mouseButton[m_events.button.button] = true;

            break;


            // Cas du relâchement d'un bouton de la souris

            case SDL_MOUSEBUTTONUP:

                m_mouseButton[m_events.button.button] = false;

            break;


            // Cas d'un mouvement de souris

            case SDL_MOUSEMOTION:

              /*  m_x = m_evenements.motion.x;
                m_y = m_evenements.motion.y;*/

                m_xRel = m_events.motion.xrel;
                m_yRel = m_events.motion.yrel;

            break;


            // Cas de la fermeture de la fenêtre

            case SDL_WINDOWEVENT:
				//printf("Over\n");
                if(m_events.window.event == SDL_WINDOWEVENT_CLOSE)
                    m_terminer = true;
				if (m_events.window.event == SDL_WINDOWEVENT_SIZE_CHANGED){
					m_window_resized = true;
					//printf("\tHere1\n");
				}

            break;


            default:
            break;
        }
		//m_updateLoopRotation++;
    }
	//printf("\tOut\n");
}


bool Input::terminer() const
{
    return m_terminer;
}


void Input::afficherPointeur(bool reponse) const
{
    if(reponse)
        SDL_ShowCursor(SDL_ENABLE);

    else
        SDL_ShowCursor(SDL_DISABLE);
}


void Input::capturerPointeur(bool reponse) const
{
    if(reponse)
        SDL_SetRelativeMouseMode(SDL_TRUE);

    else
        SDL_SetRelativeMouseMode(SDL_FALSE);
}



// Getters

//bool Input::getTouche(const SDL_Scancode touche) const
bool Input::getKey(const SDL_Keycode touche) const
{
    return m_keys[touche];
}


bool Input::getMouseButton(const Uint8 bouton) const
{
    return m_mouseButton[bouton];
}

bool* Input::getKeyRef(const SDL_Keycode key)
{
	return &m_keys[key];
}


bool* Input::getMouseButtonRef(const Uint8 button)
{
	return &m_mouseButton[button];
}

bool Input::mouseIsMoving() const
{
    if(m_xRel == 0 && m_yRel == 0)
        return false;

    else
        return true;
}

bool Input::windowResized() const{
	return m_window_resized;
}

void Input::setRefWindow(int height){
	m_height = height;
}


// Getters concernant la position du curseur

int Input::getX() const
{
    return m_x;
}

int Input::getY() const
{
    return m_y;
}

int Input::getY_screen() const
{
	return m_height - m_y;
}

int Input::getXRel() const
{
    return m_xRel;
}

int Input::getYRel() const
{
    return m_yRel;
}

Input Input::input;