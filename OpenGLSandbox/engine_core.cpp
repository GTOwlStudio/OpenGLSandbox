#include "engine_core.h"

engine_core::engine_core(int w, int h, std::string mainwindowtitle, int fpsCap) :// m_input(),
	m_fpsCap(fpsCap), m_while_start(0), m_while_duration(0), m_timeBetweenFrames(1000/fpsCap)
{
	m_mainwindow = new engine_window(w,h,mainwindowtitle);
	Input::input.setRefWindow(m_mainwindow->getHeight());
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

	//glm::mat4 guiMat = glm::ortho(0.0f,960.0f, 0.0f, 600.0f);
	glm::mat4 guiMat = glm::ortho(0.0f,(float)m_mainwindow->getWidth(), 0.0f, (float)m_mainwindow->getHeight());
	//glm::mat4 projection = glm::ortho(0.0f,960.0f, 0.0f, 600.0f, -1.0f, 100.0f);
	glm::mat4 projection = glm::perspective(60.0f, (float)m_mainwindow->getWidth()/m_mainwindow->getHeight(), 0.0f, 100.0f);
	glm::mat4 m = glm::mat4(1.0); 
	m = glm::lookAt(glm::vec3(3.0, 3.0, 3.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 modelview = glm::mat4(1.0);
//	glm::mat4 modelview = glm::lookAt(glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	FontAtlas ftest("fonts/tahoma.ttf", 12);
	FontAtlas ebrima("fonts/ebrima.ttf", 48);
	std::string allLetter = "The Quick Brown Fox Jum Over The Lazy Dog";
	//Quad q(20.0,20.0,512.0,48,1.0,"shaders/font.vert", "shaders/font.frag", "textures/base_texture.jpg");
	//Quad q(0.0,0.0,512.0,512.0,1.0,"shaders/font_dev.vert", "shaders/font_dev.frag", "textures/dev_atlasredtest.png");
	/*Quad q(200.0,10.0,512,ftest.getAtlasHeight(),0.2,"shaders/font_dev.vert", "shaders/font_dev.frag", ftest.getTexID());
	q.load();*/

	float qVertices[18] = {0.0f,0.0f+512.0f,0.2f, 0.0f+512.0f,0.0f+512.0f,0.2f,	0.0f,0.0f,0.2f,
							 0.0f,0.0f,0.2f,	 0.0f+512.0f,0.0f+512.0f,0.2f,		0.0f+512.0f,0.0f,0.2f};
	float qTexc[12] = {0.0,1.0, 1.0,1.0, 0.0,0.0, 
								0.0,0.0, 1.0,1.0, 1.0, 0.0};
	
	Quad test(qVertices, qTexc, "shaders/texture.vert", "shaders/texture.frag", "textures/texu.png");
	test.load();
	/*gui_Button button("OpenGL", ftest, 100.0,100.0,     100.0, 20.0, 0.7, 1.0, 1.0, 0.0);
	button.load();*/
	
/*	int gsMI;
	glGetIntegerv(GL_MAX_GEOMETRY_SHADER_INVOCATIONS, &gsMI);
	printf("GL_MAX_GEOMETRY_SHADER_INVOCATIONS=%i\n", gsMI);*/

	std::string test_string("The Quick Brown Fox Jump Over The Lazy Dog");

//	printf("File/2.0=%f\n", ftest.getATextWidth("File")/2.0);

	glLineWidth(2.0);
	glEnable(GL_LINE_SMOOTH);
	Line line(50.0, 50.0, 0.2,  100.0, 100.0, 0.2f, 1.0, 0.0, 1.0, 1.0);
	line.load();
	line.addPoints(400.0, 000.0, 0.2);
	line.addPoints(450.0, 300.0, 0.2);
	line.addPoints(500.0, 250.0, 0.2);//2nd
	line.addPoints(450.0, 100.0, 0.2);
	//line.addPoints(300.0, 50.0, 0.2);
	//line.addPoints(150.0, 300.0, 0.2);
	printf("engine_width=%i engine_height=%i\n", m_mainwindow->getWidth(), m_mainwindow->getHeight());
	minimum_gui gui(m_mainwindow->getWidth(), m_mainwindow->getHeight(), ftest);
	gui.load();

	QuadC rq(-1.0, -1.0, 2.0, 2.0, 0.0, 1.0, 0.3, 1.0, 1.0);
	rq.load();

	dev_gs geometrys(200.0f, 200.0f, 300.0f, 200.0f, 0.2f, "shaders/gs_basic.vert", "shaders/gs_basic.frag", "shaders/gs_basic.gs");
	geometrys.load();

	gui_Button b(allLetter, ftest,100.0, 400.0, 100.0, 100.0, 0.8, 1.0, 1.0, 1.0,1.0, LABEL_POS_CENTERED, LABEL_POS_CENTERED);
	b.load();

	//gui_Action action("Action 1", ftest, 0.0, 570.0,45.0,10.0,0.1);
	//action.load();
	/*gui_devtest dev("File", ftest);
	dev.update();*/

	/*Quad r(40.0,40.0,400.0,400.0,0.0,"shaders/texture.vert", "shaders/texture.frag", "textures/test_texture.jpg");
	r.load();*/

	float v[18] = {50.0,14.0,0.0,	50.0,32.0,0.0,	64.0,32.0,0.0,
					50.0,14.0,0.0,	64.0,32.0,0.0,	64.0,14.0,0.0};
	/*Quad debug(v, "shaders/font_dev.vert", "shaders/font_dev.frag", "textures/base_texture.jpg");
	debug.load();*/
	//char allleter[128-32];

	for (int i=64;i<128;i++){
		allLetter+=char(i);
	}
	/*gui_Label alphabet(allLetter, ftest, glm::vec4(10,200,80,10), 0.1, 1.0,0.0,0.0);
	alphabet.load();*/
	/*gui_Label label(test_string, ftest, glm::vec4(50.0,50.52,ftest.getATextWidth(test_string),ftest.getATextHeight(test_string)), 0.1,1.0,0.0,0.0);
	label.load();*/
	//label.setPosition(100.0,100.0);
	//label.move(100.0,0.0);
	//label.move(100.0, 0.0);
	
	/*dev_Quad dq(400.0f, 300.0f, 100.0f, 100.0f, 0.2f, 1.0f, 0.0f, 1.0f, 1.0f);
	dq.load();*/

	BSpline spline(50.0, 50.0, 0.2,  100.0, 100.0, 0.2f, 1.0, 0.0, 0.0, 1.0);
	spline.load();
	spline.addControlPoint(400.0, 000.0, 0.2);
	spline.addControlPoint(450.0, 300.0, 0.2);
	//spline.addControlPoint(500.0, 250.0, 0.2);
	//spline.addControlPoint(500.0, 250.0, 0.2);//2nd
	//spline.addControlPoint(450.0, 100.0, 0.2);
	//spline.addControlPoint(520.0, 50.0, 0.2);
	//spline.addControlPoint(150.0, 300.0, 0.2);
	spline.generateSpline(0.025f);
	//spline.hardGenerateSpline(0.025f);

	//Line segment(100.0, 100.0, 400.0, 100.0, 0.2, 1.0, 0.0, 1.0, 1.0);
	Line segment(100.0, 200.0, 0.2,  400.0, 200.0, 0.2f, 1.0, 0.0, 1.0, 1.0);
	segment.load();
	//segment.addPoints(200.0, 100.0, 0.2);

	gui_Label l(test_string, ebrima, 51.0, 51.0, 0.1,0.0,0.0,1.0);
	l.load();
	//l.move(0.0, 0.5);
	//l.move(0.0, -0.5);
	/*gui_devtest l (test_string, ftest, 50.0f, 50.0f,0.1,0.0,0.0,1.0);
	l.load();*/
	/*QuadC mq(20.0f,20.0f,20.0f,20.0f, 0.1f, 1.0f,0.0f,0.0f,1.0f);
	mq.load();
	mq.setPosition(100.0,20.0);*/
	float greyValue = 0.50f;
	//glClearColor(0.25,0.25,0.25,1.0);
	glClearColor(greyValue, greyValue,greyValue,1.0f);
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	bool dev_hit = false;
	float angle = 0.0f;
	unsigned int plusEachFrame = 0;
	//glm::vec4 ();
	Util::getPointPositionOnScreen(guiMat, glm::vec4(50.0, 50.0, 0.2, 1.0), m_mainwindow->getWidth(), m_mainwindow->getHeight());
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	/*Uint32 m_S, m_L;
	Uint32 updateFreq = 240;
	//while(!m_input.terminer())
	m_S = SDL_GetTicks();*/
	while(!Input::input.terminer())
	//while(!Input::input.terminer())
    {

		/*m_while_start = SDL_GetTicks();
		m_L = SDL_GetTicks();
		if ((m_L-m_S)>=(1000/updateFreq)){
			m_S = SDL_GetTicks();
			//printf("here\n");
			l.setPosition(Input::input.getX(), m_mainwindow->getHeight()- Input::input.getY());
			//l.move(0.0, 0.05);
		}*/
       // m_input.updateEvenements();
		
		plusEachFrame += 1;
		if (plusEachFrame>=60) {
			m = glm::rotate(m, angle, glm::vec3(0.0, 1.0, 0.0));
			plusEachFrame = 0;
			angle = 1.0f;
		}

		Input::input.updateEvenements();
		if (Input::input.windowResized()){
			m_mainwindow->updateResize(); // Just To Set The Good With and Height
			Input::input.setRefWindow(m_mainwindow->getHeight());
			printf("x:%i y:%i\n", 150, (int)m_mainwindow->getHeight()-50);
			gui.resize(m_mainwindow->getWidth(), m_mainwindow->getHeight());
			
			//std::cout << m_mainwindow->getHeight()-50 << std::endl;
			//rq.setPosition(150.0, (float)m_mainwindow->getHeight()-50.0f);
			guiMat = glm::ortho(0.0f, (float)m_mainwindow->getWidth(), 0.0f, (float)m_mainwindow->getHeight());
			projection = glm::perspective(60.0f, (float)m_mainwindow->getWidth()/m_mainwindow->getHeight(), 0.0f, 100.0f);
			glViewport(0, 0, m_mainwindow->getWidth(), m_mainwindow->getHeight());
		}
		if(Input::input.getTouche(SDLK_ESCAPE))
           break;
		if (Input::input.getTouche(SDLK_g)){
			gui.resize(m_mainwindow->getWidth(), m_mainwindow->getHeight());
		}
		if (Input::input.getTouche(SDLK_p)){
			//rq.setPosition(300, (m_mainwindow->getHeight())-50);
		}
		if (Input::input.getTouche(SDLK_a)&&!dev_hit){
			printf("Here\n");
			segment.setPoint(1, 150.0, 10.0, 0.2);
			dev_hit = true;
		}
		if (!gui.isFinished()){
			break;
		}

		


		/*if (m_input.getTouche(SDL_SCANCODE_G)){
			std::cout << "GL : "<< gl_version_major << "." << gl_version_minor << std::endl;
		}*/
			
       // camera.deplacer(m_input);
		modelview = glm::mat4(1.0);
        glClear(GL_COLOR_BUFFER_BIT/* | GL_DEPTH_BUFFER_BIT*/);
		//RENDU
      //  caisse.afficher(projection, modelview);
	//	q.render(projection, modelview);
		//r.render(projection, modelview);	
	//	label.render(projection, modelview);
//		mq.render(projection, modelview);
		//alphabet.render(projection, modelview);
		//l.render(guiMat, modelview);
		//geometrys.render(guiMat, modelview);
		rq.render(projection, m);
	//	dq.render(guiMat, modelview);
	//	dev.update();
		//dev.render(projection, modelview);
	//	aLetter.render(projection, modelview);
		//test.render(projection, modelview);
		segment.render(guiMat);
		line.render(guiMat);
		spline.render(guiMat);
		gui.update();
		gui.render(guiMat);
		b.update();
		b.render(guiMat, modelview);

		m_mainwindow->update();

		m_while_duration = SDL_GetTicks()-m_while_start;		
		if(m_while_duration< m_timeBetweenFrames)
			//glFlush();
			SDL_Delay(m_timeBetweenFrames - m_while_duration);
    }

}