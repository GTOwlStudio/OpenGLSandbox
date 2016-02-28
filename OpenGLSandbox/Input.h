#ifndef DEF_INPUT
#define DEF_INPUT

// Include

#include <SDL2/SDL.h>
#include <stdio.h>

#include "engine_window.h"

// Classe

class Input
{
    public:

	Input();
    ~Input();

    void updateEvenements();
    bool terminer() const;
    void afficherPointeur(bool reponse) const;
    void capturerPointeur(bool reponse) const;
	void setRefWindow(int height); //To addapt some data to the window

    bool getKey(const SDL_Keycode key) const;
    bool getMouseButton(const Uint8 button) const;
	bool& getKeyRef(const SDL_Keycode key);
	bool& getMouseButtonRef(const Uint8 button);
    bool mouvementSouris() const;

	bool windowResized() const;

    int getX() const;
    int getY() const;

    int getXRel() const;
    int getYRel() const;

	int getY_screen() const;

	static Input input;

    private:

    SDL_Event m_events;
   bool m_keys[SDL_NUM_SCANCODES];
//	bool m_touches[SDL_NUM];
    bool m_mouseButton[8];

    int m_x;
    int m_y;
    int m_xRel;
    int m_yRel;

	bool m_window_resized;
    bool m_terminer;

	int m_updateLoopRotation; //Nbre d 'execution de la boucle dans la func update()
	int m_height;
};

#endif

