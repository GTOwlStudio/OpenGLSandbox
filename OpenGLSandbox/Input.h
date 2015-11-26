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

    bool getTouche(const SDL_Scancode touche) const;
    bool getBoutonSouris(const Uint8 bouton) const;
    bool mouvementSouris() const;

	bool windowResized() const;

    int getX() const;
    int getY() const;

    int getXRel() const;
    int getYRel() const;

	int getY_screen() const;

	static Input input;

    private:

    SDL_Event m_evenements;
    bool m_touches[SDL_NUM_SCANCODES];
    bool m_boutonsSouris[8];

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

