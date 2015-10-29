#include "engine_core.h"

engine_core::engine_core(int w, int h, std::string mainwindowtitle, int fpsCap) :// m_input(),
	m_fpsCap(fpsCap), m_while_start(0), m_while_duration(0), m_timeBetweenFrames(1000/fpsCap)
{
	m_mainwindow = new engine_window(w,h,mainwindowtitle);
}


engine_core::~engine_core()
{
	delete m_mainwindow;
	m_mainwindow = 0;
}

bool engine_core::init(){
	if (!m_mainwindow->init())
		return false;

	if (!m_mainwindow->init_gl())
		return false;
	
	return true;
}

void engine_core::mainLoop(){

	glm::mat4 projection = glm::ortho(0.0f,960.0f, 0.0f, 600.0f);
	//glm::mat4 projection = glm::ortho(0.0f,960.0f, 0.0f, 600.0f, -1.0f, 100.0f);
    glm::mat4 modelview = glm::mat4(1.0);
	FontAtlas ftest("fonts/tahoma.ttf", 12);
	//Quad q(20.0,20.0,512.0,48,1.0,"shaders/font.vert", "shaders/font.frag", "textures/base_texture.jpg");
	//Quad q(0.0,0.0,512.0,512.0,1.0,"shaders/font_dev.vert", "shaders/font_dev.frag", "textures/dev_atlasredtest.png");
    /*Quad q(20.0,250.0,512,72.0,0.2,"shaders/font_dev.vert", "shaders/font_dev.frag", ftest.getTexID());
	q.load();*/
	//ftest.getATextWidth("testt");
	/*QuadC t(1.0f,589.0f,18.0f,9.0f,0.2f,1.0f,0.0f,1.0f, 0.5f);
	t.load();*/
	//gui_Button button("OpenGL", ftest, 100.0,100.0,     100.0, 20.0, 0.7, 1.0, 1.0, 0.0);

	/*gui_Button button("File",  ftest,  50.0,  50, 200.0, 200.0, 0.7, 1.0, 0.0, 0.0);
	button.load();*/
	//std::string test_string("Why the majuscle o not display see here ->OpenGL");
	std::string test_string("File");
	/*QuadC rect(50.0, 50.0, 150.0,  150.0, 0.7, 1.0, 0.0, 0.0, 0.2);
	rect.load();*/
	printf("File/2.0=%f\n", ftest.getATextWidth("File")/2.0);
	/*QuadC rect2(50.0, 50.0, 689,  ftest.getATextHeight(test_string), 0.7, 0.0, 1.0, 0.0, 0.2);
	rect2.load();*/
	//printf("textsize w=%f h=%f\n", ftest.getATextWidth("Why the majuscle o not display see here ->OpenGL"), ftest.getATextHeight("Why the majuscle o not display see here ->OpenGL"));
	minimum_gui gui(m_mainwindow->getWidth(), m_mainwindow->getHeight(), ftest);
	gui.load();

	/*gui_devtest dev("File", ftest);
	dev.update();*/

	/*Quad r(40.0,40.0,400.0,400.0,0.0,"shaders/texture.vert", "shaders/texture.frag", "textures/test_texture.jpg");
	r.load();*/

	float v[18] = {50.0,14.0,0.0,	50.0,32.0,0.0,	64.0,32.0,0.0,
					50.0,14.0,0.0,	64.0,32.0,0.0,	64.0,14.0,0.0};
	/*Quad debug(v, "shaders/font_dev.vert", "shaders/font_dev.frag", "textures/base_texture.jpg");
	debug.load();*/
	//char allleter[128-32];
	std::string allLetter = "";
	for (int i=64;i<128;i++){
		allLetter+=char(i);
	}
	/*gui_Label alphabet(allLetter, ftest, glm::vec4(10,200,80,10), 0.1, 1.0,0.0,0.0);
	alphabet.load();*/
	gui_Label label(test_string, ftest, glm::vec4(50.0,50.0,ftest.getATextWidth(test_string),ftest.getATextHeight(test_string)), 0.1,1.0,0.0,0.0);
	label.load();
	label.move(100.0,0.0);
	//label.move(100.0, 0.0);

	/*gui_Label l(test_string, ftest, 50.0+0.7,50.0, 0.1,0.0,0.0,1.0);
	l.load();*/
	QuadC mq(20.0f,20.0f,20.0f,20.0f, 0.1f, 1.0f,0.0f,0.0f,1.0f);
	mq.load();
	mq.setPosition(100.0,20.0);
	glClearColor(0.25,0.25,0.25,1.0);
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//while(!m_input.terminer())
	while(!Input::input.terminer())
    {

		m_while_start = SDL_GetTicks();

       // m_input.updateEvenements();
		Input::input.updateEvenements();
        if(Input::input.getTouche(SDL_SCANCODE_ESCAPE))
           break;
		/*if (m_input.getTouche(SDL_SCANCODE_G)){
			std::cout << "GL : "<< gl_version_major << "." << gl_version_minor << std::endl;
		}*/
			
       // camera.deplacer(m_input);
		modelview = glm::mat4(1.0);
        glClear(GL_COLOR_BUFFER_BIT/* | GL_DEPTH_BUFFER_BIT*/);
		//RENDU
      //  caisse.afficher(projection, modelview);
		//q.render(projection, modelview);
		//r.render(projection, modelview);	
		label.render(projection, modelview);
		mq.render(projection, modelview);
		//alphabet.render(projection, modelview);
		//l.render(projection, modelview);
	//	dev.update();
		//dev.render(projection, modelview);

		gui.update();
		gui.render(projection);

		//t.render(projection, modelview);

		/*button.update();
		button.render(projection, modelview);*/

		//rect.render(projection, modelview);
		//rect2.render(projection, modelview);
		//debug.render(projection, modelview);

		m_mainwindow->update();

		m_while_duration = SDL_GetTicks()-m_while_start;		
		if(m_while_duration< m_timeBetweenFrames)
			SDL_Delay(m_timeBetweenFrames - m_while_duration);
    }

}