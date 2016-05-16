#include "engine_core.h"

engine_core::engine_core(int w, int h, std::string mainwindowtitle, int fpsCap) :// m_input(),
	m_fpsCap(fpsCap), m_while_start(0), m_while_duration(0), m_last_while_duration(0), m_timeBetweenFrames(1000/fpsCap)
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
	
	engine_camera cam(60.0f, (float)m_mainwindow->getWidth() / m_mainwindow->getHeight(), 0.1f, 100.0f);
	engine_camera ocam(0.0f,1.0f,0.0f,1.0f,0.0f,100.0f);

	cam.lookAt(glm::vec3(0.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	ocam.lookAt(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,0.0f,1.0f));

	glm::mat4 guiMat = glm::ortho(0.0f,(float)m_mainwindow->getWidth(), 0.0f, (float)m_mainwindow->getHeight());
	//glm::mat4 projection = glm::ortho(0.0f,960.0f, 0.0f, 600.0f, -1.0f, 100.0f);
	glm::mat4 projection = glm::perspective(60.0f, (float)m_mainwindow->getWidth()/m_mainwindow->getHeight(), 0.0f, 100.0f);
	glm::mat4 m = glm::mat4(1.0); 
//	m = glm::translate(m, glm::vec3(0.5, 0.5, 0.0));
	m = glm::lookAt(glm::vec3(2.0, 2.0, 2.0), glm::vec3(-0.0f, -0.0f, -0.0f), glm::vec3(0.0, 1.0, 0.0));
	//m = glm::lookAt(glm::vec3(2.0, 2.0, 2.0), glm::vec3(0.5f, 0.5f, 0.0f), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 modelview = glm::mat4(1.0);
	
	glm::mat4 rotation = glm::translate(glm::mat4(1.0f), glm::vec3(-.5, -.5, -.5));
	//m = m* rotation;
//	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0, 1.0, 0.0));

	glm::mat4 model = glm::translate(glm::mat4(1.0f),glm::vec3(-0.5, -0.5, -.5) );
	/*glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	*/
//	glm::mat4 modelview = glm::lookAt(glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	FontAtlas ftest("fonts/tahoma.ttf", 12);
	FontAtlas ebrima("fonts/ebrima.ttf", 48);
	FontAtlas metro("fonts/MetroScript Regular.otf",48);
	std::string allLetter = "The Quick Brown Fox Jum Over The Lazy Dog";
	//Quad q(20.0,20.0,512.0,48,1.0,"shaders/font.vert", "shaders/font.frag", "textures/base_texture.jpg");
	//Quad q(0.0,0.0,512.0,512.0,1.0,"shaders/font_dev.vert", "shaders/font_dev.frag", "textures/dev_atlasredtest.png");
	/*Quad q(200.0,10.0,512,ftest.getAtlasHeight(),0.2,"shaders/font_dev.vert", "shaders/font_dev.frag", ftest.getTexID());
	q.load();*/
	
	Mesh mesh("obj/surface.obj");
	//Mesh mesh("obj/plane.obj");
	mesh.load();

	engine_shader pp("shaders/ps_basic.vert", "shaders/ps_basic.frag");
	pp.load();
	engine_shader bck("phyX/phyX_bucket.vert", "phyX/phyX_bucket.frag");
	bck.load();
	engine_shader lineShader("shaders/universal.vert", "shaders/universal.frag");
	lineShader.load();
	BasePoint bp(lineShader);
	bp.load();
	float qVertices[18] = {0.0f,0.0f+512.0f,0.2f, 0.0f+512.0f,0.0f+512.0f,0.2f,	0.0f,0.0f,0.2f,
							 0.0f,0.0f,0.2f,	 0.0f+512.0f,0.0f+512.0f,0.2f,		0.0f+512.0f,0.0f,0.2f};
	float qTexc[12] = {0.0,1.0, 1.0,1.0, 0.0,0.0, 
								0.0,0.0, 1.0,1.0, 1.0, 0.0};
	
	/*Quad test(qVertices, qTexc, "shaders/texture.vert", "shaders/texture.frag", "textures/texu.png");
	test.load();*/
	/*gui_Button button("OpenGL", ftest, 100.0,100.0,     100.0, 20.0, 0.7, 1.0, 1.0, 0.0);
	button.load();*/
	
/*	int gsMI;
	glGetIntegerv(GL_MAX_GEOMETRY_SHADER_INVOCATIONS, &gsMI);
	printf("GL_MAX_GEOMETRY_SHADER_INVOCATIONS=%i\n", gsMI);*/

	std::string test_string("The Quick Brown Fox Jump Over The Lazy Dog");

//	printf("File/2.0=%f\n", ftest.getATextWidth("File")/2.0);

	//glLineWidth(2.0);
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

	//printf("x=%f y=%f w=%f h=%f\n", rq.getX(), rq.getY(), rq.getWidth(), rq.getHeight());

	/*dev_gs geometrys(200.0f, 200.0f, 300.0f, 200.0f, 0.2f, "shaders/gs_basic.vert", "shaders/gs_basic.frag", "shaders/gs_basic.gs");
	geometrys.load();*/

	/*gui_Button b(allLetter, ftest,100.0, 400.0, 100.0, 100.0, 0.8, 1.0, 1.0, 1.0,1.0, LABEL_POS_CENTERED, LABEL_POS_CENTERED);
	b.load();*/

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
	gui_Label label(test_string, metro, glm::vec4(50.0f,50.0f,ftest.getATextWidth(test_string),ftest.getATextHeight(test_string)), 0.1f,0.0f,0.0f,0.0f);
	label.load();
	gui_Label fpsLabel("FPS : %i", ftest, glm::vec4(m_mainwindow->getWidth()-ftest.getATextWidth("FPS : 000-"), m_mainwindow->getHeight()-ftest.getATextHeight("FPS : 000-"), 0.0f, 0.0f), 0.1, 1.0, 0.0, 0.0);
	fpsLabel.load();
	gui_Label fpsN("000", ftest, glm::vec4(m_mainwindow->getWidth() - ftest.getATextWidth("000-"), m_mainwindow->getHeight() - ftest.getATextHeight("000-"), 0.0f, 0.0f), 0.1, 1.0, 0.0, 0.0);
	fpsN.load();
	//label.setPosition(100.0,100.0);
	//label.move(100.0,0.0);
	//label.move(100.0, 0.0);
	glm::mat4 devFontMatrix = glm::ortho(0.0f,(float)metro.getAtlasWidth(), 0.0f, (float)metro.getAtlasHeight());
	debug_font dbf(metro.getTexID(), metro);
	dbf.load();

	dev_Quad dq(50.0f, 50.0f, 50.0f, 50.0f, 0.2f, 1.0f, 0.0f, 1.0f, 1.0f);
	dq.load();

	BSpline spline(50.0, 50.0, 0.2,  100.0, 300.0, 0.2f, 1.0, 0.0, 0.0, 1.0);
	spline.load();
	spline.addControlPoint(400.0, 000.0, 0.2);
	spline.addControlPoint(500.0, 300.0, 0.2);//2nd
	spline.generateSpline(0.025f);

	/*BSpline hspline(50.0f, 50.0f, 0.2f, 20.0f, 300.0f, 0.2f, 1.0f, 0.0f, 0.0f, 1.0f);
	hspline.load();
	hspline.addControlPoint(400.0f, 800.0f, 0.2f);
	hspline.addControlPoint(300.0f, 300.0f, 0.2f);//2nd
	hspline.addControlPoint(600.0f, 100.0f,0.2f);
	hspline.addControlPoint(1200.0f, 600.0f, 0.2f);
	hspline.hardGenerateSpline(0.025f);*/

	BSpline hspline(.0f,.0f,.0f, 1.0f,.0f,.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	hspline.load();
	hspline.addControlPoint(1.0f, 1.0f, 0.0f);
	hspline.addControlPoint(0.0f, 1.0f, 1.0f);
	hspline.addControlPoint(0.0f, 0.0f, 1.0f);
	hspline.addControlPoint(1.0f, 0.0f, 1.0f);
	
	hspline.hardGenerateSpline(0.025f);


	//Line segment(100.0, 100.0, 400.0, 100.0, 0.2, 1.0, 0.0, 1.0, 1.0);
	/*Line segment(100.0, 200.0, 0.2,  400.0, 200.0, 0.2f, 1.0, 0.0, 1.0, 1.0);
	segment.load();*/
	//segment.addPoints(200.0, 100.0, 0.2);

	/*gui_Label l(test_string, ebrima, 51.0, 51.0, 0.1,0.0,0.0,1.0);
	l.load();*/

	/*EventManager mng;
	bool a = false;
	mng.addValueSpy(&a);*/

	engine_texture texture("textures/texu.png");
	texture.load();

	
	//FramebufferInfo tinfo = { GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, 512,  512 };
	FramebufferInfo tinfo = { GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_mainwindow->getWidth(),  m_mainwindow->getHeight() };
	RenderbufferInfo rinfo = {GL_RENDERBUFFER, GL_DEPTH_COMPONENT, GL_DEPTH_ATTACHMENT};
	GLuint tfbo;
	GLuint fboId;
	FramebufferManager::genFBOTAndTexture(tfbo, fboId, tinfo);
	printf("tbo=%i %i\n", tfbo, fboId);
	EzyTex etex(texture.getID());
	//EzyTex etex(texture.getID(), Ressou, "shaders/texture2d.frag");
	etex.load();
	/*EzyTex etex(tfbo, "shaders/red2grey.vert", "shaders/red2grey.frag");
	etex.load();*/
	/*gui_Slider slider("test=%v", ftest, 100.0f, 100.0f, 200.0f, 20.0f, 0.2f, 100.0f, 50.0f, 0.0f);
	slider.load();
	*/
	//dev_Label ls(test_string, ftest, glm::vec4(100.0f, 350.0f, 10.0f, 10.0f), 0.2f, 1.0f, 1.0f, 1.0f);
	//ls.setShaderSource("shaders/font_auto.vert", "shaders/font_auto.frag");
	//ls.load();
	
	/*ParticleSystem sys(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, *m_mainwindow);
	sys.load();
	dev_ut uti;
	uti.load();*/
	//sys.initParticle(PHYX_INITMODE_UNIFORM, 64, 64, 64);

	/*dev_ro q(0.0f, 0.0f,1.0f,1.0f);
	q.load();*/
	//sys.setR_T(ftest.getTexID());

	/*ParticleSystem box(-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f);
	box.load();*/

	/*dev_line li(0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f, -1.0f, -1.0f, 0.0f);
	li.load();*/

	/*dev_line li(0.0f, 0.0f, 0.2f, 100.0f, 100.0f, 0.2f, 250.0f, 100.0f, 0.2f);
	li.load();*/

	/*gui_TextField tf(ftest, 200.0f, 200.0f, 50.0f, 50.0f, 0.2f, "Test default", 1.0f, 0.0f, 1.0f,1.0f);
	tf.load();*/

	//l.move(0.0, 0.5);
	//l.move(0.0, -0.5);
	/*gui_devtest l (test_string, ftest, 50.0f, 50.0f,0.1,0.0,0.0,1.0);
	l.load();*/
	/*QuadC mq(20.0f,20.0f,20.0f,20.0f, 0.1f, 1.0f,0.0f,0.0f,1.0f);
	mq.load();
	mq.setPosition(100.0,20.0);*/
	float greyValue = 0.5f;
	//glClearColor(0.25,0.25,0.25,1.0);
	glClearColor(greyValue, greyValue,greyValue,1.0f);
	glEnable(GL_DEPTH_TEST);
	glPointSize(4.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	bool dev_hit = false;
	float angle = 0.0f;
	unsigned int plusEachFrame = 0;
	Util::getPointPositionOnScreen(guiMat, glm::vec4(50.0, 50.0, 0.2, 1.0), m_mainwindow->getWidth(), m_mainwindow->getHeight());
	clock_t t;
	clock_t update_clock = clock();
	t = clock();
/*	Uint32 lastSecond = 0;
	Uint32 average = 0;*/
	float averageFPS=0;
	printf("cursor = %i\n", SDL_SYSTEM_CURSOR_CROSSHAIR);
	int cursorId = 0;
	//glEnable(GL_DEBUG_OUTPUT);
	//ftest.runTest();
	float angleX = 0.0f;
	float angleY = 0.0f;
	float devStep = 45.0f;
	while(!Input::input.terminer())
    {
		m_while_start = SDL_GetTicks();
		plusEachFrame += 1;
		//if (plusEachFrame>=1) {
			//m = glm::mat4(1.0);
			//fpsN.setText(std::to_string(m_while_duration));
			//m = glm::rotate(m, angle, glm::vec3(0.0, 1.0, 0.0));
			//printf();
			//MVP = projection * m *  rotation*model;
			cam.rotate(angle, glm::vec3(0.0, 0.0, 1.0));
			//plusEachFrame = 0;
			angle += 0.5f;
			if (angle>=360.0f) {
				angle = angle - 360.0f;
			}
	//	}

		Input::input.updateEvenements();
		if (Input::input.windowResized()){
			m_mainwindow->updateResize(); // Just To Set The Good With and Height
			Input::input.setRefWindow(m_mainwindow->getHeight());
			printf("x:%i y:%i\n", 150, (int)m_mainwindow->getHeight()-50);
			gui.resize(m_mainwindow->getWidth(), m_mainwindow->getHeight());
			cam.resize(m_mainwindow->getWidth(), m_mainwindow->getHeight());
			//std::cout << m_mainwindow->getHeight()-50 << std::endl;
			//rq.setPosition(150.0, (float)m_mainwindow->getHeight()-50.0f);
			guiMat = glm::ortho(0.0f, (float)m_mainwindow->getWidth(), 0.0f, (float)m_mainwindow->getHeight());
			projection = glm::perspective(60.0f, (float)m_mainwindow->getWidth()/m_mainwindow->getHeight(), 0.0f, 100.0f);
			glViewport(0, 0, m_mainwindow->getWidth(), m_mainwindow->getHeight());
		}
		if(Input::input.getKey(SDLK_ESCAPE))
           break;
		if (Input::input.getKey(SDLK_g) && clock()-t>=1000) {
			t = clock();
			printf("Grid Generation");
			//sys.gridGeneration(ocam.getMatrix());
		}
		if (Input::input.getKey(SDLK_p) && clock() - t >= 800){
			t = clock();			
			//a = true;
			//mng.updateEvent();
			cursorId += 1;
			printf("%i\n",cursorId);
			if (cursorId>12) {
				printf("Turn");
				cursorId = 0;
			}
			m_mainwindow->setCursor(SDL_SystemCursor(cursorId));
		}
		if (Input::input.getKey(SDLK_a)&&clock()-t>=800){
			printf("Pressed\n");
			t = clock();
			//fpsLabel.replace(6,8, std::to_string(1000/m_last_while_duration));
			

			//segment.setPoint(1, 150.0, 10.0, 0.2);
		
		}
		if (Input::input.getKey(SDLK_i)&&(clock()-t>=1000)) {
			t = clock();
			printf("Init PhyX");
			//sys.initParticle(PHYX_INITMODE_UNIFORM,16);
		}

		if (!gui.isFinished()){
			break;
		}

		/*if (Input::input.getMouseButton(2)) {
			printf("here %i\n", Input::input.getMouseButtonRef(2));
		}*/

		/*if (clock()-update_clock>=1000/30) {
			update_clock = clock();
			//gui.update();
			
			//slider.update();
		}*/

		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
		//RENDU
		if (Input::input.getKey(SDLK_m)) {
			if (clock() - t >= 1000) {
				//slider.setPosition();
				t = clock();
				printf("PhyX\n");
				//sys.texProcess(sys.getFBOtexId(), sys.getFBOId(), pp, 512*8,64);
				//sys.dev_manip(uti.getFBOId(), uti.getShader(), 512,512);
				//sys.texProcess(uti.getTexId(), uti.getFBOId(), bck, 512 * 8, 64);
				
				printf("done\n");
				//sys.physX(guiMat, modelview);
			}
		}
		if(Input::input.getKey(SDLK_z)) {
			if (clock() - t >= 150) {
				t = clock();
				angleX += devStep;
				cam.setRotation(angleX, glm::vec3(1.0f, 0.0f, 0.0f));
				//cam.rotationAtp(45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
				//cam.rotationAtp(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			}
		}
		if (Input::input.getKey(SDLK_s)) {
			if (clock() - t >= 150) {
				t = clock();
				angleY += devStep;
				cam.setRotation(angleY, glm::vec3(0.0f, 0.0f, 1.0f));
				//cam.rotationAtp(-45.0f, glm::vec3(1.0f, 0.0f, 0.0f));
				//cam.rotationAtp(90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			}
		}

		etex.render(modelview);
		//dbf.render(modelview, devFontMatrix);
		bp.render(cam.getMatrix());
		//spline.render(guiMat);
		hspline.render(cam.getMatrix()*model);
		hspline.renderEditLine(cam.getMatrix()*model);
		/*glBindFramebuffer(GL_FRAMEBUFFER, fboId);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
			glViewport(0,0,512,512);
			mesh.render(cam.getMatrix());
			glViewport(0, 0, m_mainwindow->getWidth(), m_mainwindow->getHeight());
		glBindFramebuffer(GL_FRAMEBUFFER, 0);*/
		//q.render();
		//DEV INFO
		
		//fpsN.render(guiMat,modelview);
		if (plusEachFrame>=2) {
			plusEachFrame = 0;
			cam.update();
			gui.update();
		}
		
		gui.render(guiMat);
		//etex.render(modelview);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//	mesh.render(cam.getMatrix(), modelview);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		/*dq.render(guiMat, modelview);
		glDisable(GL_DEPTH_TEST);
		label.render(guiMat,modelview);
		glEnable(GL_DEPTH_TEST);*/
		
		//glDisable(GL_DEPTH_TEST);
		//glClear(GL_DEPTH_BUFFER_BIT);
		//bp.render(cam.getMatrix());
		//glEnable(GL_DEPTH_TEST);
		//fpsLabel.render(guiMat, modelview);
		//***Dont Touch Under*********************************************************************
		m_mainwindow->update();

		m_while_duration = SDL_GetTicks()-m_while_start;		
		if (m_while_duration < m_timeBetweenFrames)
			//glFlush();
			//printf("Here");
			SDL_Delay(m_timeBetweenFrames - m_while_duration);
			m_last_while_duration = SDL_GetTicks()-m_while_start;//#dev_tag
    }

}

void engine_core::cleanUp()
{
	FramebufferManager::cleanUp();
	RessourcesManager::cleanUp();
}
