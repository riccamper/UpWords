


/*////////////////////////////////////////////////////////////////////////////////
//																				//
//									UpWords										//
//																				//
//		SCRITTO DA		:	© Riccardo Campi									//
//																				//
//		DATA INIZIO		:	03/12/2017											//
//																				//
//		DATA FINE		:	00/00/2017											//
//																				//
//		LIBRERIE		:	OpenGl - Open Graphics Library						//
//							FreeGlut - Free OpenGl Utility Tookit				//
//							M.B. Comp. - Proprietario Marchio UpWords (1997)	//
//																				//
////////////////////////////////////////////////////////////////////////////////*/



/*////////////////////////////////////////////////////////////////////////////////
//						DEFINIZIONI E INCLUSIONI HEADERS						//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cmath>
#include <windows.h>
#include <windowsx.h>
#include <olectl.h>
#include <TlHelp32.h>
#include <algorithm>
#include <thread>
#include <shlobj.h>
#define PI 3.14159265

#define FREEGLUT_STATIC
#include "GL/freeglut.h"
#include "GL/glext.h"

#include "header.h"

using namespace std;

/*////////////////////////////////////////////////////////////////////////////////
//				DICHIARAZIONI E INIZIALIZZAZIONI VARIABILI GLOBALI				//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

///// VARIABILI PROGRAMMA
	HINSTANCE hinstance=0;
	string titolo = "UpWords!";
	string nome_programma = "UpWords";
	string loc = "c:\\" + titolo;							// MODIFICATO AT RUNTIME %APPDATA%
	string loc_impostazioni = loc + "\\impostazioni.dat";	// MODIFICATO AT RUNTIME %APPDATA%\impostazioni.dat
	string loc_partita = loc + "\\partita.dat";				// MODIFICATO AT RUNTIME %APPDATA%\partita.dat

///// VARIABILI DI DISEGNO OPENGL
	static int slices = 0;
	static int stacks = 0;
	static int zoomed = 0;
	
///// VARIABILI PER CALCOLO FPS
	float fps=0;
	int frame=0,tempo,timebase=0;

///// VARIABILI D'AMBIENTE OPENGL
	const GLfloat light_ambient[]  = { 0.75f, 0.75f, 0.75f, 1.0f };
	const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
	
	const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
	const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
	const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat high_shininess[] = { 100.0f };
	
	int max_multisample = MAX_MULTISAMPLE;
	bool bool_multisample = true;

///// VARIABILI DISEGNO BACKGROUND	
	int max_triangoli = MAX_TRIANGLES;
	struct triangles triangoli[MAX_TRIANGLES] = {0};

///// VARIABILI DISEGNO FINESTRE	
	vector <finestra> finestre;
	vector <finestra> finestre_wait;

///// VARIABILI DISEGNO SCACCHIERA	
	scacchiera table;

///// VARIABILI DISEGNO TESSERE	
	vector <tessera> tessere;
	vector <tessera> tessere_back;
	string lettere = "AAAAAAAAAEEEEEEEEEIIIIIIIIIOOOOOOOOOUUUUUCCCCCRRRRRSSSSSTTTTTLLLLLMMMMMNNNNNBBBDDDFFFGGGPPPVVVHHQQZZ";
	vector <vector <string>> errori;

///// VARIABILI GESTIONE GRAFICA
	float inizializzazione = 10000;
	bool quit = false;
	bool fullScreen = true;
	float velocita=.30;
	int stato=FIN_BENVENUTO;
	int wait = ATT_COMPLETA;
	bool wait_thread = true;
	bool init = false;
	double init_time = 0;
	
///// VARIABILI DI GIOCO
	vector <giocatore> giocatori;
	int turni_passati = 0;
	vector <string> vocabolario;
	bool prosegui = false;
	bool riprendi = false;
	suggerim suggerendo = {false, 0};
	vector <sugg> suggerimenti;

	

/*////////////////////////////////////////////////////////////////////////////////
//		GLUT CALLBACK, E' CHIAMATO QUANDO LA FINESTRA VIENE RIDIMENSIONATA		//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

static void 
resize(int width, int height)
{
	///// VARIABILE RAPPORTO LARGHEZZA / ALTEZZA
	const float ar = (float) width / (float) height;

	///// IMPOSTO LA VIEWPORT 3D
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-ar, ar, -1.0, 1.0, 2.5, 100000.0);
	
	///// SE DISATTIVATI, ATTIVO PARAMETRI 3D
	if(!glIsEnabled(GL_STENCIL_TEST)) glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity() ;
	
	///// SETTAGGIO VARIABILI D'AMBIENTE OPENGL
	glClearColor(0,0,0,1);
	if(!glIsEnabled(GL_CULL_FACE)) glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	if(!glIsEnabled(GL_DEPTH_TEST)) glEnable(GL_DEPTH_TEST);
	if(glIsEnabled(GL_ALPHA_TEST)) glDisable(GL_ALPHA_TEST);
	glDepthFunc(GL_LESS);
	
	
	if(!glIsEnabled(GL_LINE_SMOOTH)) glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	if(!glIsEnabled(GL_BLEND)) glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	if(!glIsEnabled(GL_LIGHT0)) glEnable(GL_LIGHT0);
	if(!glIsEnabled(GL_NORMALIZE)) glEnable(GL_NORMALIZE);
	if(!glIsEnabled(GL_COLOR_MATERIAL)) glEnable(GL_COLOR_MATERIAL);
	if(!glIsEnabled(GL_LIGHTING)) glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	
	if(bool_multisample){
		if(!glIsEnabled(GL_MULTISAMPLE)) glEnable(GL_MULTISAMPLE);
		glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
	}else{
		if(glIsEnabled(GL_MULTISAMPLE)) glDisable(GL_MULTISAMPLE);
	}
	
}

static void
make2D() {

	///// IMPOSTO LA VIEWPORT 2D
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();  
  	gluOrtho2D(1600/(-2), 1600/2, accomodaRisoluzione(1600)/(-2), accomodaRisoluzione(1600)/2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	///// SETTAGGIO VARIABILI D'AMBIENTE OPENGL
	glClearColor(0,0,0,1);
	if(glIsEnabled(GL_CULL_FACE)) glDisable(GL_CULL_FACE);
	
	if(glIsEnabled(GL_DEPTH_TEST)) glDisable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	if(glIsEnabled(GL_LIGHT0)) glDisable(GL_LIGHT0);
	if(glIsEnabled(GL_NORMALIZE)) glDisable(GL_NORMALIZE);
	if(glIsEnabled(GL_COLOR_MATERIAL)) glDisable(GL_COLOR_MATERIAL);
	if(glIsEnabled(GL_LIGHTING)) glDisable(GL_LIGHTING);
	
}



/*////////////////////////////////////////////////////////////////////////////////
//		GLUT CALLBACK, E' CHIAMATO OGNI FRAME PER IL DISEGNO DEGLI ELEMENTI		//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

static void 
display(void)
{
	///// OTTENGO TEMPO DI ESECUZIONE E VARIE
	const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0 - init_time;
	const double a = t*90.0;
	
	///// CALCOLO IL NUMERO DI FPS (FRAME PER SECONDO)
	frame++;
	tempo=glutGet(GLUT_ELAPSED_TIME);
	if (tempo - timebase > 1000) {
		fps = frame*1000.0/(tempo-timebase);
		timebase = tempo;
		frame = 0;
	}
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	///// IMPOSTO AMBIENTE 3D
	resize(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	
	///// RESETTO IDENTIFICATORE
	glStencilFunc(GL_ALWAYS, 0, -1);
	
	///// SE NON MI TROVO NELLA SITUAZIONE "ATTESA COMPLETA DURANTE IL CARICAMENTO"
	if(wait!=ATT_COMPLETA){
	
		///// DISEGNO TRIANGOLI DI BACKGROUND
		for(int s=0; s<max_triangoli; s++){
			glColor4d (triangoli[s].colore.r, triangoli[s].colore.g, triangoli[s].colore.b, triangoli[s].colore.a);
			glPushMatrix();
				glLineWidth(1);
				glTranslated(triangoli[s].cordinata.x*400, triangoli[s].cordinata.y*200, triangoli[s].cordinata.z*600 - inizializzazione);
				glRotated(60,1,0,0);
				glRotated(a*triangoli[s].rotazione.vel, triangoli[s].rotazione.x, triangoli[s].rotazione.y, triangoli[s].rotazione.z);
				glutWireCone(1,1,3,1);
			glPopMatrix();
		}
		
		
		///// DISEGNO LA SCACCHIERA E LE EVENTUALI TESSERE
		DisegnaScacchiera(table, tessere, table.posx, table.posxx, 0);
		
		///// DISEGNO LA SCACCHIERA E LE EVENTUALI TESSERE
		DisegnaRastrelliere(table, tessere, giocatori, table.posx, table.posxx, 0);
		
		///// DISEGNO LA SCACCHIERA E LE EVENTUALI TESSERE
		//DisegnaTessere(table, tessere, table.posx, slices, 0);
		
	
		
		///// IMPOSTO AMBIENTE 2D
		make2D();
		
		///// ITERO LE FINESTRE
		for (int count = 0; count < finestre.size(); count++){
			
		  	DisegnaFinestra(finestre, count, inizializzazione, 0, 0);
				
		}
		
		///// SCRIVO IL NUMERO DI FPS (FRAME PER SECONDO)
		glColor4f(1.0, 1.0, 1.0, 0.75 );
		drawBitmapText(GLUT_BITMAP_HELVETICA_12, "" + to_string((int)fps) + " fps", -800 +3, -450 + 3);
	
	}
	
	
	{
		
		///// IMPOSTO AMBIENTE 2D
		make2D();
		
		///// ITERO LE FINESTRE DI ATTESA
		for (int count = 0; count < finestre_wait.size(); count++){
		
		  	DisegnaFinestra(finestre_wait, count, 0, 0, 0);
			
		}
		
	}
	
	
	glutSwapBuffers();
}



/*////////////////////////////////////////////////////////////////////////////////
//		GLUT CALLBACK, E' CHIAMATO QUANDO RILEVA UN INPUT DA TASTIERA			//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

static void 
key(unsigned char key, int x, int y)
{
	///// OTTENGO TEMPO DI ESECUZIONE E VARIE
	const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0 - init_time;
	static double last_key_time = 0;
	
	///// BOOLEANO PER SAPERE SE UTILIZZARE LA TASTIERA PER SCRIVERE O PER INTERAGIRE
	bool scrivi = false;
	
	///// PROTEZIONE CONTRO CHIAMATE PRIMA DEL TEMPO E CONTRO LE ATTESE
	if(inizializzazione<=1 && wait==ATT_NO){
		
		///// ITERO LE FINESTRE PER SAPERE SE UNA E' TEXTBX
		for (int count = 0; count < finestre.size(); count++)
			for (int count2 = 0; count2 < finestre.at(count).ogg.size(); count2++)
				if(finestre.at(count).ogg.at(count2).tipo == TEXTBX && finestre.at(count).ogg.at(count2).active)
					if(key >= 32 && key <= 126 && finestre.at(count).ogg.at(count2).testo.size() < 15){
						finestre.at(count).ogg.at(count2).testo += key;
						scrivi = true;
					}else
						if(key == 8){
							finestre.at(count).ogg.at(count2).testo = finestre.at(count).ogg.at(count2).testo . substr(0, finestre.at(count).ogg.at(count2).testo.size()-1);
							scrivi = true;
						}
		
		///// ALTRIMENTI LEGGO I TASTI PER IL NORMALE FUNZIONAMENTO
		if(!scrivi && last_key_time < t*1000)
		switch (key) 
		{
			case 27 :
				for (int count = 0; count < finestre.size(); count++)
					if(count == stato)
						if(stato>0)
							if(finestre.at(count).child >= 0){
								stato = finestre.at(count).child;
								break;
							}
							else{
								stato--;
								break;
							}
						else
							if(finestre.at(count).child >= 0){
								stato = finestre.at(count).child;
								break;
							}
							else{
								quit=true;
								break;
							}
				
				last_key_time = t*1000 + 500;
								
				break;
				
			//case 'f':
			//	///// MODIFICO LA MODALITA' FULLSCREEN
			//	glutFullScreenToggle();
			//	fullScreen = !fullScreen;
			//	if (fullScreen) {
			//
			//	} else {
			//
			//	}
			//	break;
		}
	
		glutPostRedisplay();
		
	}
}



/*////////////////////////////////////////////////////////////////////////////////
//			GLUT CALLBACK, E' CHIAMATO QUANDO RILEVA UN CLICK DA MOUSE			//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

static void 
mouse(int button, int state, int x, int y)
{
	///// OTTENGO TEMPO DI ESECUZIONE E VARIE
	const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0 - init_time;
	static double last_key_time = 0;
	
	///// PROTEZIONE CONTRO CHIAMATE PRIMA DEL TEMPO E CONTRO LE ATTESE
	if(inizializzazione<=1 && wait==ATT_NO && last_key_time < t*1000){
		
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) last_key_time = t*1000 + 100;
		
		///// OTTENGO COORDINATE MOUSE 2D
		float x2d=(float)x/glutGet(GLUT_WINDOW_WIDTH)*(1600)-(1600/2);
		float y2d=(float)-y/glutGet(GLUT_WINDOW_HEIGHT)*(accomodaRisoluzione(1600))+(accomodaRisoluzione(1600)/2);
		
		///// OTTENGO IDENTIFICATORE OGGETTI 3D
  		GLuint index;
  		glReadPixels(x, glutGet(GLUT_WINDOW_HEIGHT) - y - 1, 1, 1, GL_STENCIL_INDEX, GL_INT, &index);
	  	
		bool esc = false;
		bool click = false;
	  	
	  	
		///// ITERO LE FINESTRE
		if(inizializzazione <= 1)
		for (int count = 0; count < finestre.size(); count++)
			if(count == stato)
				if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
					///// SE SIAMO ALL'INTERNO DELLA 'X' IN ALTO
			  		if(	x2d>=finestre.at(count).top.x - 30 &&
					  	x2d<=finestre.at(count).top.x &&
						y2d>=finestre.at(count).top.y + finestre.at(count).posx -30 &&
						y2d<=finestre.at(count).top.y + finestre.at(count).posx	){
						
						if(stato>0)
							if(finestre.at(count).child >= 0){
								stato = finestre.at(count).child;
								break;
							}
							else{
								stato--;
								break;
							}
						else
							if(finestre.at(count).child >= 0){
								stato = finestre.at(count).child;
								break;
							}
							else{
								quit=true;
								break;
							}
						
						esc = true;
						click = true;
					}
					///// SE SIAMO ALL'INTERNO DELLA FRECCIA FULLSCREEN
			  		if(	x2d>=finestre.at(count).top.x - 60 &&
					  	x2d<=finestre.at(count).top.x - 30 &&
						y2d>=finestre.at(count).top.y + finestre.at(count).posx -30 &&
						y2d<=finestre.at(count).top.y + finestre.at(count).posx	) {
							///// MODIFICO LA MODALITA' FULLSCREEN
							glutFullScreenToggle();
							fullScreen = !fullScreen;
							if (fullScreen) {
								
							} else {
								
							}
						esc = true;
						click = true;
						}
				
					
				///// ITERO GLI OGGETTI ALL'INTERNO DELLA FINESTRA
				for (int count2 = 0; count2 < finestre.at(count).ogg.size(); count2++){
					
					///// SE L'ELEMENTO E' DI TIPO TBITMA
					if(finestre.at(count).ogg.at(count2).tipo == BUTTON)
					  	if(stato == FIN_SUGG){
							///// RICAVO LA POSIZIONE DEL MOUSE E LA RELATIVA CONFIGURAZIONE
							int sel = -1;
							for(int s = 0, i = 0; s < suggerimenti.size(); s++)
								if(i < 15)
									if(to_string( suggerimenti.at(s).punti ) != "0"){
										if(finestre.at(FIN_SUGG).ogg.at(5 + i).active == 1 || finestre.at(FIN_SUGG).ogg.at(20 + i).active == 1 || finestre.at(FIN_SUGG).ogg.at(35 + i).active == 1 || finestre.at(FIN_SUGG).ogg.at(50 + i).active == 1){
											sel = s;
											break;
										}
										i++;
									}
							if(sel != -1)
								if(suggerimenti.size() > sel)
									if(to_string( suggerimenti.at(sel).punti ) != "0"){
										tessere_back = suggerimenti.at(sel).tess;
										click = true;
									}
						}
					
					///// SE L'ELEMENTO E' DI TIPO BUTTON
					if(finestre.at(count).ogg.at(count2).tipo == BUTTON)
				  		if(	x2d>=finestre.at(count).ogg.at(count2).bot.x &&
						  	x2d<=finestre.at(count).ogg.at(count2).top.x &&
							y2d>=finestre.at(count).ogg.at(count2).bot.y + finestre.at(count).posx &&
							y2d<=finestre.at(count).ogg.at(count2).top.y + finestre.at(count).posx	) if(finestre.at(count).ogg.at(count2).hidden==0){
								
								///// ECCEZIONI BOTTONI
								///// CONTROLLO NOMI GIOCATORI
								bool ok=true;
								if(count == FIN_NUMERO && count2 == 5){
									for(int s = 0; s < stoi(finestre.at(FIN_NUMERO).ogg.at(0).testo); s++)
										if(finestre.at(FIN_NUMERO).ogg.at(1+s).testo.size() < 3) ok=false;
									for(int s = 0; s < stoi(finestre.at(FIN_NUMERO).ogg.at(0).testo); s++) 
										for(int i = 0; i < stoi(finestre.at(FIN_NUMERO).ogg.at(0).testo); i++)
											if(i != s && finestre.at(FIN_NUMERO).ogg.at(1+s).testo == finestre.at(FIN_NUMERO).ogg.at(1+i).testo) ok = false;
								}
								if(!ok){
									
									infoBox({finestre_wait, finestre.at(stato).titolo +  " > " + "Nomi Giocatori", "Nomi Giocatori", "Errore nella scrittura dei Nomi.", IDI_BACK7, 3000, wait});
									break;
								}
								
								////// PER USCIRE DAL PROGRAMMA
								if(finestre.at(count).ogg.at(count2).target == CHIUSURA)
									quit = true;
								
								
								///// SE DEVO CARICARE LA PARTITA SALVATA
								if(count == FIN_NUMERO && count2 == 6){
									if(sePartitaSalvata(loc_partita)){
										riprendi = true;
									}else{
										riprendi = false;
										break;
									}
								}
								
								///// SALVATAGGIO PARTITA IN CORSO
								if(count == FIN_PAUSA && count2 == 2){
									scrivi(loc_partita, tessere, giocatori);
								}
								
								///// ELIMINO PARTITE SALVATE
								if(count == FIN_PAUSA && count2 == 1){
									//ofstream out(loc_partita, ios::trunc);
									//out << "# Nessuna Partita Salvata UpWords" << endl;
									//out << "# Non modificare in alcuno modo questo File" << endl;
									//out.close();
								}
	
								
								///// CONTROLLO PASSAGGIO TURNO
								if(count == FIN_PARTITA && count2 == 4){
									
									///// BLOCCO IL SUGGERIMENTO (SE IN ESECUZIONE)
									suggerendo.vero = false;
									
									if(wait == ATT_NO){
										
										prosegui = false;
										wait = ATT_SEMPLICE;
										thread vaglia = thread (vagliaParole, ref(prosegui), tessere, vocabolario, ref(wait), errori, ref(finestre_wait), finestre.at(stato).titolo, IDI_BACK8, 3000);
										vaglia.detach();
									}
								}
								
								///// PER RICHIAMARE LE TESSERE
								if(count == FIN_PARTITA && count2 == 2){
									for(int g=0;g<giocatori.size();g++)
										if(giocatori.at(g).turno == 1)
											for(int r=0;r<7;r++){
												int ce = -1;
												for(int s = 0; s < 100; s++)
													if(tessere.at(s).posizionata == POS_GIOCATORE && tessere.at(s).pos == r && tessere.at(s).giocatore == g)
														ce = r;
												if(ce == -1)
													for(int s = 0; s < 100; s++)
														if(tessere.at(s).posizionata == POS_SCACC_MOB){
															tessere.at(s).posizionata = POS_GIOCATORE;
															tessere.at(s).giocatore = g;
															tessere.at(s).pos = r;
															break;
														}
											}
								}
								
								///// PER RANDOMIZZARE LE TESSERE
								if(count == FIN_PARTITA && count2 == 0){
									for(int g=0;g<giocatori.size();g++)
										if(giocatori.at(g).turno == 1){
											vector <int> randomizzatore;
											int n = 0;
											for(int s = 0; s < 100; s++)
												if(tessere.at(s).posizionata == POS_GIOCATORE && tessere.at(s).giocatore == g)
													randomizzatore.push_back(tessere.at(s).pos);
											for(int r=0;r<10;r++)
												random_shuffle(randomizzatore.begin(),randomizzatore.end());
											for(int s = 0; s < 100; s++)
												if(tessere.at(s).posizionata == POS_GIOCATORE && tessere.at(s).giocatore == g){
													tessere.at(s).pos = randomizzatore.at(n);
													n++;
												}
										}
								}
								
								///// PER SUGGERIMENTO
								if(count == FIN_PARTITA && count2 == 3){
									mostraSuggerimento(suggerendo, {finestre_wait, finestre.at(stato).titolo +  " > Spunti", "Gli Spunti", "Saranno mostrati in ordine di Punteggio e Interattivi.", IDI_BACK1, 3000, wait}, tessere, giocatori, vocabolario);
								}
								
								///// PER SOSTITUIRE UNA TESSERA
								if(count == FIN_PARTITA && count2 == 1){
									
									///// BLOCCO IL SUGGERIMENTO (SE IN ESECUZIONE)
									suggerendo.vero = false;
									
									///// RICAVO LA TESSERA SELEZIONATA
									int seltess=-1;
									for(int s=0;s<100;s++) if(tessere.at(s).selected && tessere.at(s).posizionata == POS_GIOCATORE ) seltess=s;
									
									///// TROVO IL GIOCATORE CORRENTE
									if(seltess != -1){
										///// RICAMBIO TESSERA
										for(int s = 0; s < 100; s++)
											if(tessere.at(s).posizionata == POS_NULLA && tessere.at(s).lettera != tessere.at(seltess).lettera){
												tessere.at(s).posizionata = POS_GIOCATORE;
												tessere.at(s).giocatore = tessere.at(seltess).giocatore;
												tessere.at(s).pos = tessere.at(seltess).pos;
												///// SPOSTO LA VECCHIA TESSERA NEL MUCCHIO
												tessere.at(seltess).posizionata = POS_NULLA;
												///// FINISCO IL TURNO
												fineTurno({finestre_wait, finestre.at(stato).titolo +  " > ", "", "", IDI_BACK7, 4000, wait}, tessere, giocatori, stato, true);
												break;
											}
									}
								}
								
								///// NORMALE LINKAGGIO DELLE FINESTRE
								if(finestre.at(count).ogg.at(count2).target >= 0)
									stato=finestre.at(count).ogg.at(count2).target;
								esc = true;
								click = true;
							}
					///// SE L'ELEMENTO E' DI TIPO LISTBX
					if(finestre.at(count).ogg.at(count2).tipo == LISTBX)
				  		if(	x2d>=finestre.at(count).ogg.at(count2).bot.x &&
						  	x2d<=finestre.at(count).ogg.at(count2).bot.x + finestre.at(count).ogg.at(count2).top.y - finestre.at(count).ogg.at(count2).bot.y &&
							y2d>=finestre.at(count).ogg.at(count2).bot.y &&
							y2d<=finestre.at(count).ogg.at(count2).top.y	){
							finestre.at(count).ogg.at(count2).testo = modListbx(finestre.at(count).ogg.at(count2).testo, SOTTRAZIONE);
							click = true;
						}
						else
					  		if(	x2d>=finestre.at(count).ogg.at(count2).top.x - (finestre.at(count).ogg.at(count2).top.y - finestre.at(count).ogg.at(count2).bot.y) &&
							  	x2d<=finestre.at(count).ogg.at(count2).top.x &&
								y2d>=finestre.at(count).ogg.at(count2).bot.y &&
								y2d<=finestre.at(count).ogg.at(count2).top.y	){
								finestre.at(count).ogg.at(count2).testo = modListbx(finestre.at(count).ogg.at(count2).testo, SOMMA);
								click = true;
							}
						
				}
				if(esc) break;
			}
	
		///// SE SONO NELLA FINESTRA "PARTITA", ATTIVO IL SISTEMA DI IDENTIFICAZIONE OGGETTI 3D (PER SELEZIONARE)
		if(stato == FIN_PARTITA){
			
			if(index >= CELLE && index < CELLE+100)
				if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
					///// SELEZIONO CELLA SCACCHIERA
					for(int s=0;s<100;s++)
						if(index == CELLE + s)
							table.cell.at(s).selected = !table.cell.at(s).selected;
						else table.cell.at(s).selected = 0;
					///// DESELEZIONO CELLA RASTRELLIERA
						for(int g=0;g<giocatori.size();g++)
							for(int s=0;s<7;s++)
								giocatori.at(g).cell.at(s).selected = 0;
					click = true;
				}
			
			if(index >= TESSERE && index < TESSERE+100)
				if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
					for(int s=0;s<100;s++)
						if(index == TESSERE + s && tessere.at(s).posizionata != POS_SCACC)
							tessere.at(s).selected = !tessere.at(s).selected;
						else tessere.at(s).selected = 0;
					click = true;
				}
			
			if(index >= RASTR_1 && index < RASTR_1+(7*giocatori.size()))
				if (button == GLUT_LEFT_BUTTON && state == GLUT_UP){
					///// SELEZIONO CELLA RASTRELLIERA DEL GIOCATORE DI TURNO
					for(int g=0;g<giocatori.size();g++)
						for(int s=0;s<7;s++)
							if(index == g*7 + RASTR_1 + s)
								giocatori.at(g).cell.at(s).selected = !giocatori.at(g).cell.at(s).selected;
							else giocatori.at(g).cell.at(s).selected = 0;
					///// DESELEZIONO CELLA SCACCHIERA
					for(int s=0;s<100;s++)
						table.cell.at(s).selected = 0;
					click = true;
				}
			
		}
	
		///// RIPRODUZIONE SUONO DI CLICK
		if (click){
			PlaySound(NULL, 0, 0);
			PlaySound(MAKEINTRESOURCE(IDI_WAV2), hinstance, SND_RESOURCE | SND_ASYNC);
		}
	
		glutPostRedisplay();
	
	}
}



/*////////////////////////////////////////////////////////////////////////////////
//					GLUT CALLBACK, RILEVA POSIZIONE MOUSE						//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

static void 
mouseMove(int x, int y)
{
	///// PROTEZIONE CONTRO CHIAMATE PRIMA DEL TEMPO E CONTRO LE ATTESE
	if(inizializzazione<=1 && wait==ATT_NO){

		///// OTTENGO COORDINATE MOUSE 2D
		float x2d=(float)x/glutGet(GLUT_WINDOW_WIDTH)*(1600)-(1600/2);
		float y2d=(float)-y/glutGet(GLUT_WINDOW_HEIGHT)*(accomodaRisoluzione(1600))+(accomodaRisoluzione(1600)/2);

		///// OTTENGO IDENTIFICATORE OGGETTI 3D
  		GLuint index;
  		glReadPixels(x, glutGet(GLUT_WINDOW_HEIGHT) - y - 1, 1, 1, GL_STENCIL_INDEX, GL_INT, &index);
  		
		///// ATTIVAZIONE TASTI ED ELEMENTI TRAMITE LA FUNZIONE
		if(inizializzazione <= 1)
			AttivaElemento(finestre, x2d, y2d, stato);
		
		///// SE SONO NELLA FINESTRA "PARTITA", ATTIVO IL SISTEMA DI IDENTIFICAZIONE OGGETTI 3D (PER ATTIVARE, "ILLUMINARE GLI OGGETTI")
		if(stato == FIN_PARTITA)
			for(int s=0;s<100;s++) if(index == CELLE + s) table.cell.at(s).active = 1;
			else table.cell.at(s).active = 0;
			
		if(stato == FIN_PARTITA)
			for(int s=0;s<100;s++) if(index == TESSERE + s) tessere.at(s).active = 1;
			else tessere.at(s).active = 0;
			
		if(stato == FIN_PARTITA)
			for(int g=0;g<giocatori.size();g++)
				for(int s=0;s<7;s++) if(index == g*7 + RASTR_1 + s) giocatori.at(g).cell.at(s).active = 1;
				else giocatori.at(g).cell.at(s).active = 0;
	  	
	  	if(stato == FIN_SUGG){
			///// RICAVO LA POSIZIONE DEL MOUSE
			int sel = -1;
			for(int s = 0; s < 15; s++)
				if(finestre.at(FIN_SUGG).ogg.at(5 + s).active == 1 || finestre.at(FIN_SUGG).ogg.at(20 + s).active == 1 || finestre.at(FIN_SUGG).ogg.at(35 + s).active == 1 || finestre.at(FIN_SUGG).ogg.at(50 + s).active == 1)
					if(finestre.at(FIN_SUGG).ogg.at(50 + s).testo != ""){
						sel = s;
						break;
					}
			if(sel != -1) glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR);
			else glutSetCursor(GLUT_CURSOR_INHERIT);
		}
		
		glutPostRedisplay();
	
	}
}



/*////////////////////////////////////////////////////////////////////////////////
//					FUNIONE DI INIZIALIZZAZIONE DI GIOCO						//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

static void 
init_play(void)
{
	
	///// POSIZIONE INIZIALE ELEMENTI 3D
	table.posx = 50;
	table.posxx = 0;
	
	///// RESETTO TURNI PASSATI CONSECUTIVAMENTE
	turni_passati = 0;
	
	///// BLOCCO IL SUGGERIMENTO (SE IN ESECUZIONE)
	suggerendo.vero = false;
									
	if(riprendi){
		if(!leggi(loc_partita, tessere, giocatori)) stato = FIN_BENVENUTO;
		riprendi = false;
	}else{
		///// RESETTO LE INFORMAZIONI GIOCATORI
		giocatori.clear();
		int turno = rand()%stoi(finestre.at(FIN_NUMERO).ogg.at(0).testo);
		for(int s=0;s<  stoi(finestre.at(FIN_NUMERO).ogg.at(0).testo)  ;s++){
			giocatori.push_back({});
			giocatori.at(giocatori.size()-1).punti = 0;
			giocatori.at(giocatori.size()-1).nome = finestre.at(FIN_NUMERO).ogg.at(s+1).testo;
			for(int c=0;c<7;c++){
				giocatori.at(giocatori.size()-1).cell.push_back({0,0});
			}
			if(turno == s)
				giocatori.at(giocatori.size()-1).turno = 1;
			else
				giocatori.at(giocatori.size()-1).turno = 0;
			giocatori.at(giocatori.size()-1).numero_parole = 0;
			giocatori.at(giocatori.size()-1).numero_lettere = 0;
		}
		
		///// SETTO IMPOSTAZIONI TESSERE
		tessere.clear();
		for(int s=0;s<100;s++){
			tessere.push_back({});
			tessere.at(tessere.size()-1).lettera = lettere[s];
			tessere.at(tessere.size()-1).xpos = 0;
			tessere.at(tessere.size()-1).ypos = 0;
			tessere.at(tessere.size()-1).zpos = 0;
			tessere.at(tessere.size()-1).posizionata = POS_NULLA;
			tessere.at(tessere.size()-1).giocatore = 0;
			tessere.at(tessere.size()-1).pos = 0;
			tessere.at(tessere.size()-1).active = 0;
			tessere.at(tessere.size()-1).selected = 0;
		}
		for(int r=0;r<100;r++) random_shuffle(tessere.begin(),tessere.end());
		
		///// ASSEGNO LE TESSERE AD OGNI GIOCATORE
		for(int g=0;g<giocatori.size();g++)
			for(int t=0;t<7;t++){
				tessere.at(g*7+t).posizionata = POS_GIOCATORE;
				tessere.at(g*7+t).giocatore = g;
				tessere.at(g*7+t).pos = t;
			}
	}
	
	
	wait = ATT_NO;
	
}



/*////////////////////////////////////////////////////////////////////////////////
//			GLUT CALLBACK, E' CHIAMATO OGNI FRAME PER FUNZIONI DI IDLE			//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

static void 
idle(void)
{
	///// OTTENGO TEMPO DI ESECUZIONE E VARIE
	const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0 - init_time;
	const double a = t*90.0;
	
	static int init_operation_number = 0;
	
	///// SE DEVO ANCORA INIZIALIZZARE
	if(!init && t>5){
		
		///// SE E' IL PROMO CICLO DI INIZIALIZZAZIONE
		if(init_operation_number == 0){
			///// RIPRODUZIONE SUONO DI AVVIO PROGRAMMA
			PlaySound(MAKEINTRESOURCE(IDI_WAV1), hinstance, SND_RESOURCE | SND_ASYNC);
			
			thread inizializza(init_thread);
			inizializza.detach();
		}
		
		///// ESEGUO IL CARICAMENTO FINCHE' NON HA TERMINATO (RITORNA 0)
		if(!init_running(init_operation_number)) init = true;
		
		init_operation_number++;
	}
	
	///// ELABORO VARIABILI DI ATTESA
	if(init && !wait_thread && wait == ATT_COMPLETA){
		wait = ATT_NO;
		init_time =  t - 0;
	}
	
	///// ELABOLO POSIZIONE FINESTRA DI ATTESA
	if(wait == ATT_NO){
		if(finestre_wait.at(ATT_COMPLETA).posx<=100) finestre_wait.at(ATT_COMPLETA).posx+=velocita*(sqrt(finestre_wait.at(ATT_COMPLETA).posx*finestre_wait.at(ATT_COMPLETA).posx)+1);
		if(finestre_wait.at(ATT_SEMPLICE).posx<=100) finestre_wait.at(ATT_SEMPLICE).posx+=velocita*(sqrt(finestre_wait.at(ATT_SEMPLICE).posx*finestre_wait.at(ATT_SEMPLICE).posx)+1);
		if(finestre_wait.at(ATT_INFO).posx<=100) finestre_wait.at(ATT_INFO).posx+=velocita*(sqrt(finestre_wait.at(ATT_INFO).posx*finestre_wait.at(ATT_INFO).posx)+1);
	}else if(wait == ATT_SEMPLICE){
		if(finestre_wait.at(ATT_SEMPLICE).posx>=0) finestre_wait.at(ATT_SEMPLICE).posx-=velocita*sqrt(finestre_wait.at(ATT_SEMPLICE).posx*finestre_wait.at(ATT_SEMPLICE).posx);
		if(finestre_wait.at(ATT_SEMPLICE).posx<=0) finestre_wait.at(ATT_SEMPLICE).posx+=velocita*sqrt(finestre_wait.at(ATT_SEMPLICE).posx*finestre_wait.at(ATT_SEMPLICE).posx);
		if(finestre_wait.at(ATT_COMPLETA).posx<=100) finestre_wait.at(ATT_COMPLETA).posx+=velocita*(sqrt(finestre_wait.at(ATT_COMPLETA).posx*finestre_wait.at(ATT_COMPLETA).posx)+1);
		if(finestre_wait.at(ATT_INFO).posx<=100) finestre_wait.at(ATT_INFO).posx+=velocita*(sqrt(finestre_wait.at(ATT_INFO).posx*finestre_wait.at(ATT_INFO).posx)+1);
	}else if(wait == ATT_COMPLETA){
		if(finestre_wait.at(ATT_SEMPLICE).posx<=100) finestre_wait.at(ATT_SEMPLICE).posx+=velocita*(sqrt(finestre_wait.at(ATT_SEMPLICE).posx*finestre_wait.at(ATT_SEMPLICE).posx)+1);
		if(finestre_wait.at(ATT_COMPLETA).posx>=0) finestre_wait.at(ATT_COMPLETA).posx-=velocita*sqrt(finestre_wait.at(ATT_COMPLETA).posx*finestre_wait.at(ATT_COMPLETA).posx);
		if(finestre_wait.at(ATT_COMPLETA).posx<=0) finestre_wait.at(ATT_COMPLETA).posx+=velocita*sqrt(finestre_wait.at(ATT_COMPLETA).posx*finestre_wait.at(ATT_COMPLETA).posx);
		if(finestre_wait.at(ATT_INFO).posx<=100) finestre_wait.at(ATT_INFO).posx+=velocita*(sqrt(finestre_wait.at(ATT_INFO).posx*finestre_wait.at(ATT_INFO).posx)+1);
	}else if(wait == ATT_INFO){
		if(finestre_wait.at(ATT_SEMPLICE).posx<=100) finestre_wait.at(ATT_SEMPLICE).posx+=velocita*(sqrt(finestre_wait.at(ATT_SEMPLICE).posx*finestre_wait.at(ATT_SEMPLICE).posx)+1);
		if(finestre_wait.at(ATT_COMPLETA).posx<=100) finestre_wait.at(ATT_COMPLETA).posx+=velocita*(sqrt(finestre_wait.at(ATT_COMPLETA).posx*finestre_wait.at(ATT_COMPLETA).posx)+1);
		if(finestre_wait.at(ATT_INFO).posx>=0) finestre_wait.at(ATT_INFO).posx-=velocita*sqrt(finestre_wait.at(ATT_INFO).posx*finestre_wait.at(ATT_INFO).posx);
		if(finestre_wait.at(ATT_INFO).posx<=0) finestre_wait.at(ATT_INFO).posx+=velocita*sqrt(finestre_wait.at(ATT_INFO).posx*finestre_wait.at(ATT_INFO).posx);
	}
	
	///// SE POSSO MOSTRARE LA GRAFICA
	if(wait!=ATT_COMPLETA){
		
		///// VARIABILE PER CONOSCERE CAMBIAMENTI DI STATO
		static int stato_corrente = stato;
		
		///// CALCOLO VARIABILI DI GESTIONE GRAFICA
		if(!quit)
			if(inizializzazione > 0)
				inizializzazione = inizializzazione * cos((a/18)*PI/180);
			else
				inizializzazione = 0;
		else
			if(inizializzazione < 10000)
				inizializzazione +=  (inizializzazione+1)/10 ;
			else
				glutLeaveMainLoop();
		
		///// CALCOLO POSIZIONI FINESTRE IN BASE A STATO
		for (int count = 0; count < finestre.size(); count++){
			if(stato != stato_corrente && stato > count && stato_corrente < count){
				finestre.at(count).posx = 100;
			}
			if(stato != stato_corrente && stato_corrente > count && stato < count){
				finestre.at(count).posx = -100;
			}
			if(count == stato){
				if(finestre.at(count).posx>=0) finestre.at(count).posx-=velocita*sqrt(finestre.at(count).posx*finestre.at(count).posx);
				if(finestre.at(count).posx<=0) finestre.at(count).posx+=velocita*sqrt(finestre.at(count).posx*finestre.at(count).posx);
			}else
				if(count < stato){
					if(finestre.at(count).posx<=100) finestre.at(count).posx+=velocita*(sqrt(finestre.at(count).posx*finestre.at(count).posx)+1);
				}else{
					if(finestre.at(count).posx>=-100) finestre.at(count).posx-=velocita*(sqrt(finestre.at(count).posx*finestre.at(count).posx)+1);
				}
		}
				
		///// CALCOLO TRIANGOLI DI BACKGROUND
		for(int s=0; s<MAX_TRIANGLES; s++){
			//triangoli[s].cordinata.x	+= cos(a/10000) * triangoli[s].direzione.x / 10000;
			//triangoli[s].cordinata.y	+= cos(a/10000) * triangoli[s].direzione.y / 10000;
			//triangoli[s].cordinata.z	+= cos(a/10000) * triangoli[s].direzione.z / 10000;
			triangoli[s].cordinata.x	= triangoli[s].posizione.x + cos(a/10000) * triangoli[s].direzione.x;
			triangoli[s].cordinata.y	= triangoli[s].posizione.y + cos(a/10000) * triangoli[s].direzione.y;
			triangoli[s].cordinata.z	= triangoli[s].posizione.z + cos(a/10000) * triangoli[s].direzione.z;
		}
		
		///// AGGIUSTAMENTI IN BASE AGLI FPS
		if(( fps * (MAX_MULTISAMPLE/2) ) / 30 > 3) bool_multisample = true;
		else bool_multisample = false;


		///// CALCOLO NUMERO TEXTBX NOME GIOCATORI
		if(stato == FIN_NUMERO) for(int s = 0; s<4 ; s++) if(stoi(finestre.at(FIN_NUMERO).ogg.at(0).testo) > s) finestre.at(FIN_NUMERO).ogg.at(s+1).hidden = 0; else finestre.at(FIN_NUMERO).ogg.at(s+1).hidden = 1;
		
		///// CALCOLO IMPOSTAZIONI SCACCHIERA 3D
		if(stato >= FIN_PARTITA) table.visible = 1; else table.visible = 0;
		
		if(stato == FIN_PARTITA){
			if(table.posx>=0) table.posx-=(velocita/2)*sqrt(table.posx*table.posx);
			if(table.posx<=0) table.posx+=(velocita/2)*sqrt(table.posx*table.posx);
			if(table.posxx>=0) table.posxx-=(velocita/2)*sqrt(table.posxx*table.posxx);
			if(table.posxx<=0) table.posxx+=(velocita/2)*sqrt(table.posxx*table.posxx);
		}else

		if(stato == FIN_SUGG){
			if(table.posx<=10) table.posx+=(velocita/2)*(sqrt(table.posx*table.posx)+1);
			if(table.posxx<=10) table.posxx+=(velocita/2)*(sqrt(table.posxx*table.posxx)+1);
		}else
		
		if(stato > FIN_PARTITA){
			if(table.posx<=50) table.posx+=(velocita/2)*(sqrt(table.posx*table.posx)+1);
		}
		
		if(stato == FIN_PARTITA && prosegui){
			
			fineTurno({finestre_wait, finestre.at(stato).titolo +  " > ", "", "", IDI_BACK7, 4000, wait}, tessere, giocatori, stato);
			
			prosegui = false;
		}
		
		///// CALCOLO AZIONI E MOVIMENTI TESSERE
		int selcell=-1;
		int seltess=-1;
		int selrast=-1;
		for(int s=0;s<100;s++) if(tessere.at(s).selected && ( tessere.at(s).posizionata == POS_SCACC_MOB || tessere.at(s).posizionata == POS_GIOCATORE ) ) seltess=s;
		for(int i=0;i<100;i++) if(table.cell.at(i).selected) selcell=i;
		for(int g=0;g<giocatori.size();g++)
			if(giocatori.at(g).turno == 1)
				for(int r=0;r<7;r++) if(giocatori.at(g).cell.at(r).selected) selrast=r;
		
		///// SPOSTAMENTI TESSERE NELLA SCACCHIERA
		if(selcell != -1 && seltess != -1){			
			int x=selcell % 10;
			int y=(selcell/10) % 10;
			int z=0;
			for(int k=0;k<100;k++) if(tessere.at(k).xpos == x && tessere.at(k).ypos == y && ( tessere.at(k).posizionata == POS_SCACC || tessere.at(k).posizionata == POS_SCACC_MOB ) ) z++;
			
			int err = controlloInserimento(tessere, table, x, y, z, seltess, selcell);
			if(err == ERR_NO){
				tessere.at(seltess).xpos = x;
				tessere.at(seltess).ypos = y;
				tessere.at(seltess).zpos = z;
				tessere.at(seltess).posizionata = POS_SCACC_MOB;
			}else{
				infoBox({finestre_wait, finestre.at(stato).titolo +  " > " + errori.at(err).at(0), errori.at(err).at(0), errori.at(err).at(1), IDI_BACK8, 3000, wait});
			}
			
			tessere.at(seltess).selected=0;
			table.cell.at(selcell).selected=0;
		}
		
		///// SPOSTAMENTI TESSERE NELLA RASTRELLIERA
		if(selrast != -1 && seltess != -1){			
			int x=selcell % 10;
			int y=(selcell/10) % 10;
			
			int err = ERR_NO;
			for(int g=0;g<giocatori.size();g++)
				if(giocatori.at(g).turno == 1)
					for(int t = 0; t < tessere.size(); t++) if(tessere.at(t).posizionata == POS_GIOCATORE && tessere.at(t).pos == selrast && tessere.at(t).giocatore == g) err = ERR_CELL_RASTR_OCC;
			
			if(err == ERR_NO){
				tessere.at(seltess).pos = selrast;
				tessere.at(seltess).posizionata = POS_GIOCATORE;
			}else{
				infoBox({finestre_wait, finestre.at(stato).titolo +  " > " + errori.at(err).at(0), errori.at(err).at(0), errori.at(err).at(1), IDI_BACK8, 3000, wait});
			}
				
			tessere.at(seltess).selected=0;
			for(int g=0;g<giocatori.size();g++)
				for(int r=0;r<7;r++) giocatori.at(g).cell.at(r).selected = 0;
		}
		
		
		///// CONTROLLI ESEGUITI DURANTE IL GIOCO
		if(stato == FIN_PARTITA){
			///// CALCOLO NUMERO DI TESSERE GIOCATE
			int num_tess_gioc = 7;
			for(int s=0;s<100;s++)
				if(tessere.at(s).posizionata == POS_SCACC_MOB)
					num_tess_gioc--;
			if(num_tess_gioc < 7){
				finestre.at(FIN_PARTITA).ogg.at(0).hidden=0;
				finestre.at(FIN_PARTITA).ogg.at(1).hidden=1;
				finestre.at(FIN_PARTITA).ogg.at(2).hidden=0;
				finestre.at(FIN_PARTITA).ogg.at(3).hidden=1;
				finestre.at(FIN_PARTITA).ogg.at(4).testo="Prosegui >";
			}else{
				finestre.at(FIN_PARTITA).ogg.at(0).hidden=0;
				if(seltess != -1)
					finestre.at(FIN_PARTITA).ogg.at(1).hidden=0;
				else
					finestre.at(FIN_PARTITA).ogg.at(1).hidden=1;
				finestre.at(FIN_PARTITA).ogg.at(2).hidden=1;
				finestre.at(FIN_PARTITA).ogg.at(3).hidden=0;
				finestre.at(FIN_PARTITA).ogg.at(4).testo="Passa";
			}
			
			///// INFORMAZIONI SUGGERIMENTO
			if(suggerendo.vero){
				finestre.at(FIN_PARTITA).ogg.at(3).testo = "Spunti (" + to_string( suggerendo.percentuale ) + "%)";
				finestre.at(FIN_PARTITA).ogg.at(3).colore = {0.75, 1*((int)(t*2)%2), 1*((int)(t*2)%2), 0.75};
			}else{
				finestre.at(FIN_PARTITA).ogg.at(3).testo = "Spunti";
				finestre.at(FIN_PARTITA).ogg.at(3).colore = {0.75, 1, 1, 0.75};
			}
			
			///// RESETTO NOME E PUNTI GIOCATORI
			for(int g=0;g<4;g++){
				finestre.at(FIN_PARTITA).ogg.at(5 + g).testo = "";
				finestre.at(FIN_PARTITA).ogg.at(9 + g).testo = "";
			}
			
			///// SCRIVO NOME E PUNTI GIOCATORE CORRENTE
			for(int g=0;g<giocatori.size();g++){
				finestre.at(FIN_PARTITA).ogg.at(5 + g).testo = "" + giocatori.at(g).nome;
				finestre.at(FIN_PARTITA).ogg.at(9 + g).testo = "" + to_string(giocatori.at(g).punti);
				if(giocatori.at(g).turno == 1){
					finestre.at(FIN_PARTITA).ogg.at(5 + g).colore = {1, 0.6, 0, 1};
					finestre.at(FIN_PARTITA).ogg.at(9 + g).colore = {1, 0.6, 0, 1};
				}else{
					finestre.at(FIN_PARTITA).ogg.at(5 + g).colore = {1, 1, 1, 1};
					finestre.at(FIN_PARTITA).ogg.at(9 + g).colore = {1, 1, 1, 1};
				}
			}
		}
		
		
		///// CARICO LE STRUTTURE DI GIOCO
		if(stato == FIN_PARTITA && stato_corrente<FIN_PARTITA){
			///// INIZIALIZZO STRUTTURE DI GIOCO
			init_play();
			
		}
		
		
		///// RESTITUISCO LE INFORMAZIONI
		if(stato == FIN_TERMINE && stato_corrente<FIN_TERMINE){
			
			///// ORDINO I GIOCATORI IN BASE AL PUNTEGGIO
			sort( giocatori.begin(), giocatori.end(), []( giocatore a, giocatore b ){ return a.punti > b.punti; });
			
			finestre.at(FIN_TERMINE).ogg.at(12-4).testo = "";	finestre.at(FIN_TERMINE).ogg.at(12).testo = "";	finestre.at(FIN_TERMINE).ogg.at(12+4).testo = "";	finestre.at(FIN_TERMINE).ogg.at(12+4*2).testo = "";	finestre.at(FIN_TERMINE).ogg.at(12+4*3).testo = "";	finestre.at(FIN_TERMINE).ogg.at(12+4*4).testo = "";
			finestre.at(FIN_TERMINE).ogg.at(13-4).testo = "";	finestre.at(FIN_TERMINE).ogg.at(13).testo = "";	finestre.at(FIN_TERMINE).ogg.at(13+4).testo = "";	finestre.at(FIN_TERMINE).ogg.at(13+4*2).testo = "";	finestre.at(FIN_TERMINE).ogg.at(13+4*3).testo = "";	finestre.at(FIN_TERMINE).ogg.at(13+4*4).testo = "";
			finestre.at(FIN_TERMINE).ogg.at(14-4).testo = "";	finestre.at(FIN_TERMINE).ogg.at(14).testo = "";	finestre.at(FIN_TERMINE).ogg.at(14+4).testo = "";	finestre.at(FIN_TERMINE).ogg.at(14+4*2).testo = "";	finestre.at(FIN_TERMINE).ogg.at(14+4*3).testo = "";	finestre.at(FIN_TERMINE).ogg.at(14+4*4).testo = "";
			finestre.at(FIN_TERMINE).ogg.at(15-4).testo = "";	finestre.at(FIN_TERMINE).ogg.at(15).testo = "";	finestre.at(FIN_TERMINE).ogg.at(15+4).testo = "";	finestre.at(FIN_TERMINE).ogg.at(15+4*2).testo = "";	finestre.at(FIN_TERMINE).ogg.at(15+4*3).testo = "";	finestre.at(FIN_TERMINE).ogg.at(15+4*4).testo = "";
			
			for(int g = 0; g < giocatori.size(); g++){
				///// EVITO DIVISIONE PER 0
				if(giocatori.at(g).numero_parole != 0){
					finestre.at(FIN_TERMINE).ogg.at(12+g-4).testo = intRomano(g + 1);	finestre.at(FIN_TERMINE).ogg.at(12+g).testo = giocatori.at(g).nome;	finestre.at(FIN_TERMINE).ogg.at(12+g+4).testo = to_string(giocatori.at(g).punti);	finestre.at(FIN_TERMINE).ogg.at(12+g+4*2).testo = to_string(giocatori.at(g).numero_parole);	finestre.at(FIN_TERMINE).ogg.at(12+g+4*3).testo = to_string(giocatori.at(g).numero_lettere / giocatori.at(g).numero_parole);	finestre.at(FIN_TERMINE).ogg.at(12+g+4*4).testo = to_string(giocatori.at(g).punti / giocatori.at(g).numero_parole);	
				}else{
					finestre.at(FIN_TERMINE).ogg.at(12+g-4).testo = intRomano(g + 1);	finestre.at(FIN_TERMINE).ogg.at(12+g).testo = giocatori.at(g).nome;	finestre.at(FIN_TERMINE).ogg.at(12+g+4).testo = to_string(giocatori.at(g).punti);	finestre.at(FIN_TERMINE).ogg.at(12+g+4*2).testo = to_string(giocatori.at(g).numero_parole);	finestre.at(FIN_TERMINE).ogg.at(12+g+4*3).testo = to_string(0);	finestre.at(FIN_TERMINE).ogg.at(12+g+4*4).testo = to_string(0);		
				}
				///// COLORO
				float ridotto = (float)g/8;
				color colore = {1-ridotto, 1, 1 , 1 -ridotto};
				finestre.at(FIN_TERMINE).ogg.at(12+g-4).colore = colore;	finestre.at(FIN_TERMINE).ogg.at(12+g).colore = colore;	finestre.at(FIN_TERMINE).ogg.at(12+g+4).colore = colore;	finestre.at(FIN_TERMINE).ogg.at(12+g+4*2).colore = colore;	finestre.at(FIN_TERMINE).ogg.at(12+g+4*3).colore = colore;	finestre.at(FIN_TERMINE).ogg.at(12+g+4*4).colore = colore;	
			}
		}
			
		///// SE SI STA PER APRIRE LA FINESTRA DI SCELTA GIOCATORI, CONTROLLO SE CI SONO PARTITE SAVATE
		if(stato == FIN_NUMERO && stato_corrente != FIN_NUMERO){
			///// SE CI SONO PARTITE SALVATE ATTIVO IL BOTTONE PER RIPRISTINARE
			if(sePartitaSalvata(loc_partita)){
				finestre.at(FIN_NUMERO).ogg.at(6).hidden = 0;
				finestre.at(FIN_NUMERO).ogg.at(7).testo = "La Partita Salvata:";
				finestre.at(FIN_NUMERO).ogg.at(8).testo = "";	finestre.at(FIN_NUMERO).ogg.at(12).testo = "";	finestre.at(FIN_NUMERO).ogg.at(8).colore = {1, 1, 1, 1};	finestre.at(FIN_NUMERO).ogg.at(12).colore = {1, 1, 1, 1};
				finestre.at(FIN_NUMERO).ogg.at(9).testo = "";	finestre.at(FIN_NUMERO).ogg.at(13).testo = "";	finestre.at(FIN_NUMERO).ogg.at(9).colore = {1, 1, 1, 1};	finestre.at(FIN_NUMERO).ogg.at(13).colore = {1, 1, 1, 1};
				finestre.at(FIN_NUMERO).ogg.at(10).testo = "";	finestre.at(FIN_NUMERO).ogg.at(14).testo = "";	finestre.at(FIN_NUMERO).ogg.at(10).colore = {1, 1, 1, 1};	finestre.at(FIN_NUMERO).ogg.at(14).colore = {1, 1, 1, 1};
				finestre.at(FIN_NUMERO).ogg.at(11).testo = "";	finestre.at(FIN_NUMERO).ogg.at(15).testo = "";	finestre.at(FIN_NUMERO).ogg.at(11).colore = {1, 1, 1, 1};	finestre.at(FIN_NUMERO).ogg.at(15).colore = {1, 1, 1, 1};
				///// RICHIEDO LE INFO DELLA PARTITA SALVATA
				vector <tessera> tessere_provv;
				vector <giocatore> giocatori_provv;
				if(leggi(loc_partita, tessere_provv, giocatori_provv)){
					for(int g = 0; g < giocatori_provv.size(); g++){
						finestre.at(FIN_NUMERO).ogg.at(8+g).testo = giocatori_provv.at(g).nome;
						finestre.at(FIN_NUMERO).ogg.at(8+4+g).testo = to_string(giocatori_provv.at(g).punti);
						if(giocatori_provv.at(g).turno == 1){ finestre.at(FIN_NUMERO).ogg.at(8+g).colore = {1, 0.6, 0, 1};	finestre.at(FIN_NUMERO).ogg.at(8+4+g).colore = {1, 0.6, 0, 1}; }
						else{ finestre.at(FIN_NUMERO).ogg.at(8+g).colore = {1, 1, 1, 1};	finestre.at(FIN_NUMERO).ogg.at(8+4+g).colore = {1, 1, 1, 1}; }
					}
				}
			}else{
				finestre.at(FIN_NUMERO).ogg.at(6).hidden = 1;
				finestre.at(FIN_NUMERO).ogg.at(7).testo = "La Partita Salvata non esiste.";
				finestre.at(FIN_NUMERO).ogg.at(8).testo = "";	finestre.at(FIN_NUMERO).ogg.at(12).testo = "";	finestre.at(FIN_NUMERO).ogg.at(8).colore = {1, 1, 1, 1};	finestre.at(FIN_NUMERO).ogg.at(12).colore = {1, 1, 1, 1};
				finestre.at(FIN_NUMERO).ogg.at(9).testo = "";	finestre.at(FIN_NUMERO).ogg.at(13).testo = "";	finestre.at(FIN_NUMERO).ogg.at(9).colore = {1, 1, 1, 1};	finestre.at(FIN_NUMERO).ogg.at(13).colore = {1, 1, 1, 1};
				finestre.at(FIN_NUMERO).ogg.at(10).testo = "";	finestre.at(FIN_NUMERO).ogg.at(14).testo = "";	finestre.at(FIN_NUMERO).ogg.at(10).colore = {1, 1, 1, 1};	finestre.at(FIN_NUMERO).ogg.at(14).colore = {1, 1, 1, 1};
				finestre.at(FIN_NUMERO).ogg.at(11).testo = "";	finestre.at(FIN_NUMERO).ogg.at(15).testo = "";	finestre.at(FIN_NUMERO).ogg.at(11).colore = {1, 1, 1, 1};	finestre.at(FIN_NUMERO).ogg.at(15).colore = {1, 1, 1, 1};
			}
		}
			
		///// SE SI VOGLIONO VISUALIZZARE I SUGGERIMENTI
		if(stato == FIN_SUGG){
			if(suggerendo.vero){
				finestre.at(FIN_SUGG).ogg.at(0).testo = "Gli Spunti  -  Caricamento " + to_string( suggerendo.percentuale ) + "%";
				//finestre.at(FIN_SUGG).ogg.at(0).testo += "" + string((int)(t*3)%10, '.');
				finestre.at(FIN_SUGG).ogg.at(0).colore = {1, 1*((int)(t*2)%2), 1*((int)(t*2)%2), 1};
			}
			else{
				finestre.at(FIN_SUGG).ogg.at(0).testo = "Gli Spunti";
				finestre.at(FIN_SUGG).ogg.at(0).colore = {1, 1, 1, 1};
			}
				
			for(int s = 0; s < 15; s++){
				finestre.at(FIN_SUGG).ogg.at(5 + s).testo = "";
				finestre.at(FIN_SUGG).ogg.at(20 + s).testo = "";
				finestre.at(FIN_SUGG).ogg.at(35 + s).testo = "";
				finestre.at(FIN_SUGG).ogg.at(50 + s).testo = "";
			}
			
			
			for(int s = 0, i = 0; s < suggerimenti.size(); s++)
				if(i < 15)
					if(to_string( suggerimenti.at(s).punti ) != "0"){
						float ridotto = (float)i/30;
						finestre.at(FIN_SUGG).ogg.at(5 + i).testo = intRomano(i + 1);								finestre.at(FIN_SUGG).ogg.at(5 + i).colore = {1 -ridotto, 1, 1, 1 -ridotto};
						finestre.at(FIN_SUGG).ogg.at(35 + i).testo = suggerimenti.at(s).parola;						finestre.at(FIN_SUGG).ogg.at(20 + i).colore = {1 -ridotto, 1, 1, 1 -ridotto};
						finestre.at(FIN_SUGG).ogg.at(20 + i).testo = suggerimenti.at(s).lettera;					finestre.at(FIN_SUGG).ogg.at(35 + i).colore = {1 -ridotto, 1, 1, 1 -ridotto};
						finestre.at(FIN_SUGG).ogg.at(50 + i).testo = "+" + to_string( suggerimenti.at(s).punti );	finestre.at(FIN_SUGG).ogg.at(50 + i).colore = {1 -ridotto, 1, 1, 1 -ridotto};
						i++;
					}
			
			///// IN CASO MOSTRO LA CONFIGURAZIONE PRESCELTA
			int sel = -1;
			static int sel_old = -1;
			for(int s = 0, i = 0; s < suggerimenti.size(); s++)
				if(i < 15)
					if(to_string( suggerimenti.at(s).punti ) != "0"){
						if(finestre.at(FIN_SUGG).ogg.at(5 + i).active == 1 || finestre.at(FIN_SUGG).ogg.at(20 + i).active == 1 || finestre.at(FIN_SUGG).ogg.at(35 + i).active == 1 || finestre.at(FIN_SUGG).ogg.at(50 + i).active == 1){
							sel = s;
							break;
						}
						i++;
					}
			if(sel_old != sel)	
				if(sel != -1){
					if(suggerimenti.size() > sel)
						if(to_string( suggerimenti.at(sel).punti ) != "0")
							tessere = suggerimenti.at(sel).tess;
				}else
					tessere = tessere_back;
			sel_old = sel;
					
		}
			
		///// SE SI STA CHIUDENDO LA FINESTRA SUGGERIMENTI
		if(stato == FIN_PARTITA && stato_corrente == FIN_SUGG){
			if(tessere_back.size() == 100)
				tessere = tessere_back;
				
			glutSetCursor(GLUT_CURSOR_INHERIT);
		}
		
		if(stato < FIN_PARTITA){
			///// BLOCCO IL SUGGERIMENTO (SE IN ESECUZIONE)
			suggerendo.vero = false;
		}
			
		
			
				
		///// AGGIORNO STATO IDLE
		stato_corrente = stato;
		
		
	}
	
	
	glutPostRedisplay();
}


	
/*////////////////////////////////////////////////////////////////////////////////
//			FUNIONE DI INIZIALIZZAZIONE AMBIENTE, CALCOLI E VARIABILI			//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

static void 
init_pre_wind(void)
{
	///// INIZIALIZZAZIONE RAND()
	srand ( time (0) );
		
	///// OTTENGO LA CARTELLA %APPDATA%
	loc = getPath( CSIDL_APPDATA ) + "\\" + nome_programma;
	loc_impostazioni = loc + "\\impostazioni.dat";
	loc_partita = loc + "\\partita.dat";
		
	///// SE NON ESISTE, CREO LA CARTELLA PRINCIPALE
	CreateDirectory(loc.c_str(), NULL);
	
	///// CARICO IMPOSTAZIONI SALVATE
	// [..]
	
}



/*////////////////////////////////////////////////////////////////////////////////
//			FUNIONE DI INIZIALIZZAZIONE SVOLTA A PROGRAMMA AVVIATO (thread)		//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

static void 
init_thread(void)
{
	///// SETTO LA VARIABILE DI ATTESA
	wait_thread = true;
	
	///// INIZIALIZZAZIONE RAND()
	srand ( time (0) );
	
	///// AGGIORNAMENTO INFORMAZIONI DI CARICAMENTO
	finestre_wait.at(0).ogg.at(1).testo = "Caricamento Oggetti...";

	Sleep(1000);
   	
	///// INIZIALIZZAZIONE TRIANGOLI DI BACKGROUND
	for(int s=0; s<max_triangoli; s++){
		
		if(!(rand()%10)){
			triangoli[s].colore.r		= 0.5 + (float)( rand () % 128 ) / 255;
			triangoli[s].colore.g		= 0.5 + (float)( rand () % 128 ) / 255;
			triangoli[s].colore.b		= 1;
			triangoli[s].colore.a		= 0.5 + (float)( rand () % 128 ) / 255;
		}else{
			triangoli[s].colore.r		= 0;
			triangoli[s].colore.g		= 0.25 + (float)( rand () % 128 ) / 255;
			triangoli[s].colore.b		= 0.5 + (float)( rand () % 128 ) / 255;
			triangoli[s].colore.a		= 0.5 + (float)( rand () % 128 ) / 255;
		}
		
		triangoli[s].posizione.x	= -0.5 + (float)( rand () % 1000 ) / 1000;
		triangoli[s].posizione.y	= -0.5 + (float)( rand () % 1000 ) / 1000;
		triangoli[s].posizione.z	= -0.75 + (float)( rand () % 1000 ) / 1000;
		
		triangoli[s].direzione.x	= -0.5 + (float)( rand () % 1000 ) / 1000;
		triangoli[s].direzione.y	= -0.5 + (float)( rand () % 1000 ) / 1000;
		triangoli[s].direzione.z	= -0.75 + (float)( rand () % 1000 ) / 1000;
		
		triangoli[s].rotazione.x	= 0.0 + (float)( rand () % 1000 ) / 1000;
		triangoli[s].rotazione.y	= 0.0 + (float)( rand () % 1000 ) / 1000;
		triangoli[s].rotazione.z	= 0.0 + (float)( rand () % 1000 ) / 1000;
		triangoli[s].rotazione.vel	= 0.0 + (float)( rand () % 1000 ) / 1000;
		
	}
		
	///// SETTO IMPOSTAZIONI SCACCHIERA
	table.active = 0;
	table.visible = 0;
	for(int s = 0; s < 100; s++){
		table.cell.push_back({});
		table.cell.at(table.cell.size()-1).active = 0;
		table.cell.at(table.cell.size()-1).selected = 0;
	}
	
	///// SETTO IMPOSTAZIONI TESSERE
	for(int s = 0; s < 100; s++){
		tessere.push_back({});
		tessere.at(tessere.size()-1).lettera = lettere[s];
		tessere.at(tessere.size()-1).xpos = 0;
		tessere.at(tessere.size()-1).ypos = 0;
		tessere.at(tessere.size()-1).zpos = 0;
		tessere.at(tessere.size()-1).posizionata = POS_NULLA;
		tessere.at(tessere.size()-1).active = 0;
		tessere.at(tessere.size()-1).selected = 0;
	}
	for(int s = 0; s < rand()%10; s++) random_shuffle(tessere.begin(),tessere.end());
	
	
	///// AGGIORNAMENTO INFORMAZIONI DI CARICAMENTO
	finestre_wait.at(0).ogg.at(1).testo = "Caricamento Vocabolario...";

	Sleep(1000);
	
	///// CARICO IN MEMORIA IL VOCABOLARIO
	caricaVocabolario(vocabolario);
	
	
	
	///// AGGIORNAMENTO INFORMAZIONI DI CARICAMENTO
	finestre_wait.at(0).ogg.at(1).testo = "Caricamento Finestre & Testi...";

	Sleep(1000);
	
	///// CREO STRUTTURE PER LE FINESTRE E SOTTOSTRUTTURE PER GLI ELEMENTI
	
	AggiungiFinestra(finestre, 400, 225, -400, -225, titolo + " > Uscita", IDI_BACK1, FIN_BENVENUTO, true, 1000);
		AggiungiElemento(finestre, +100, 100+50, -100, 100-50, BUTTON, 1, 1, 1, 0.75, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Torna", FIN_BENVENUTO);
		AggiungiElemento(finestre, +100, -100+50, -100, -100-50, BUTTON, 1, 0, 0, 0.75, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Esci", CHIUSURA);
		
	AggiungiFinestra(finestre, 720, 405, -720, -405, "Benvenuto in " + titolo, IDI_BACK2, FIN_USCITA);
		
		//AggiungiElemento(finestre, -230, -50, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Il Gioco da Tavolo Tridimensionale!", -1);		
		
		AggiungiElemento(finestre, 250+100, -175+50, 250-100, -175-50, BUTTON, 1, 1, 1, 0.75, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Istruzioni", FIN_ISTRUZIONI1);
		AggiungiElemento(finestre, 550+100, -175+50, 550-100, -175-50, BUTTON, 0.75, 1, 1, 0.75, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Gioca", FIN_NUMERO);
	
		AggiungiElemento(finestre, -230, 0, 0, 0, TSTROK, 1, 1, 1, 0.6, 20, 1, 0, 1, GLUT_STROKE_ROMAN, "", -1);
		
		AggiungiElemento(finestre, -700, -80, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "L'Oggetto :", -1);
		AggiungiElemento(finestre, -450, -80, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "UpWords!  -  Il Gioco da Tavolo Tridimensionale!", -1);
		AggiungiElemento(finestre, -700, -120, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "La Committenza :", -1);
		AggiungiElemento(finestre, -450, -120, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "Politecnico di Milano  -  Polo di Como (2017-2018)", -1);
		AggiungiElemento(finestre, -450, -140, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "Elaborato per Fondamenti di Informatica", -1);
		AggiungiElemento(finestre, -700, -180, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "La Lavorazione :", -1);
		AggiungiElemento(finestre, -450, -180, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "Riccardo Campi", -1);
		AggiungiElemento(finestre, -700, -220, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "I Crediti :", -1);
		AggiungiElemento(finestre, -450, -220, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "OpenGl  -  Open Graphics Library", -1);
		AggiungiElemento(finestre, -450, -240, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "FreeGlut  -  Free OpenGl Utility Tookit", -1);
		AggiungiElemento(finestre, -450, -260, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "Milton Bradley Company  -  Proprietario Marchio UpWords (1997)", -1);
		
		
	AggiungiFinestra(finestre, 720, 405, -720, -405, titolo + " > Istruzioni #1", IDI_BACK3, FIN_BENVENUTO);
		AggiungiElemento(finestre, -700, 320, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "I Giocatori", -1);
		AggiungiElemento(finestre, -690, 300, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "Tutti possono giocare, da 2 a 4 giocatori.", -1);
		
		AggiungiElemento(finestre, -700, 260, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Lo Scopo", -1);
		AggiungiElemento(finestre, -690, 240, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "Il gioco consiste nel comporre parole con tessere impilabili sullo speciale tabellone al fine di ottenere punti. Si possono costruire parole componendo le lettere", -1);
		AggiungiElemento(finestre, -690, 220, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "in verticale o in orizzontale, o sovrapponendole su altre lettere gia' posizionate. Si ottengono punti per ogni tessera nella parola composta e per le tessere", -1);
		AggiungiElemento(finestre, -690, 200, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "sotto ogni lettera della stessa. Le lettere infatti possono essere impilate fino ad un'altezza di 5 tessere, cosi' il punteggio potra' aumentare velocemente.", -1);
		
		AggiungiElemento(finestre, -700, 160, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "La Vittoria", -1);
		AggiungiElemento(finestre, -690, 140, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "Il giocatore che ha totalizzato piu' punti vince, seguito dal secondo, (terzo) e (quarto), man mano che i punti diminuiscono.", -1);
		
		AggiungiElemento(finestre, -700, 100, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "L'Inizio", -1);
		AggiungiElemento(finestre, -690,  80, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "Il primo giocatore deve formare una parola di 2 o piu' lettere che copra almeno uno dei 4 quadrati di gioco nel centro del tabellone e poi collegarsi ad esse.", -1);
		
		AggiungiElemento(finestre, -700,  40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Il Gioco", -1);
		AggiungiElemento(finestre, -690,  20, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "Durante il turno si devono giocare una o piu' tessere per formare una parola o per cambiarne una gia' esistente sul tabellone. Tutte le lettere giocate durante", -1);
		AggiungiElemento(finestre, -690,   0, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "il turno devono seguire la stessa direzione di gioco e devono unirsi ad altre gia' presenti. Una volta calcolato il punteggio, le lettere giocate verranno sostituite.", -1);
		
		AggiungiElemento(finestre, -700, -40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Il Turno Saltato", -1);
		AggiungiElemento(finestre, -690, -60, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "Si puo' saltare un turno in ogni momento. Qualche volta puo' essere vantaggioso, specie verso la fine del gioco, per realizzare un punteggio migliore.", -1);
		
		AggiungiElemento(finestre, -700,-100, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Lo Scambio di Lettere", -1);
		AggiungiElemento(finestre, -690,-120, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "Durante un turno si puo' scambiare una delle tessere per una nuova, presa dalle rimanenti. Per fare questo come penalita' si perde il turno.", -1);
		
		AggiungiElemento(finestre, -700,-160, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "[...]", -1);
		
		AggiungiElemento(finestre, 550+100, -275+50, 550-100, -275-50, BUTTON, 1, 1, 1, 0.75, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Avanti", FIN_ISTRUZIONI2);
		
		
	AggiungiFinestra(finestre, 720, 405, -720, -405, titolo + " > Istruzioni #2", IDI_BACK3, FIN_BENVENUTO);
		AggiungiElemento(finestre, -700, 320, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "[...]", -1);
		
		AggiungiElemento(finestre, -700, 280, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Le Lettere Impilabili", -1);
		AggiungiElemento(finestre, -690, 260, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "Si possono sovrapporre lettere in cima ad altre (gia' presenti) per cambiare una parola in un'altra diversa. Non e' invece possibile sovrapporre piu' di una lettera", -1);
		AggiungiElemento(finestre, -690, 240, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "sulla stessa pila durante lo stesso turno, e non si possono impilare due lettere uguali. Il numero di lettere impilate puo' arrivare ad un massimo di 5.", -1);
		AggiungiElemento(finestre, -690, 220, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "Non si puo' coprire l'intera vecchia parola; almeno una lettera deve rimanere scoperta ed essere usata.", -1);
		
		AggiungiElemento(finestre, -700, 180, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "La Validita'", -1);
		AggiungiElemento(finestre, -690, 160, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "Una parola NON e' valida se NON e' presente nel dizionario del gioco.", -1);
		AggiungiElemento(finestre, -690, 140, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "Inoltre non e' valida se gia' e' stata usata, se e' composta, se richiede un apostrofo, se e' un prefix o suffix senza significato o se è' straniera.", -1);
		
		AggiungiElemento(finestre, -700, 100, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "I Punteggi", -1);
		AggiungiElemento(finestre, -690,  80, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "- 2 punti a tessera per ogni parola formata con nessuna lettera impilata sulle altre.", -1);
		AggiungiElemento(finestre, -690,  60, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "- 1 punto a tessera per ogni parola formata che contenga alcune lettere sovrapposte + 1 punto per ogni tessera sottostante.", -1);
		AggiungiElemento(finestre, -690,  40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "- 2 punti extra se si usa la tessera 'Q' nelle parole formate senza sovrapposizioni di lettere.", -1);
		AggiungiElemento(finestre, -690,  20, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "- 20 punti extra bonus se si usano tutte e 7 le tessere in un solo turno.", -1);
		AggiungiElemento(finestre, -690,   0, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "- Se si formano o cambiano 2 o piu' parole nello stesso turno, ogni parola da' un punteggio. Lettere condivise tra parole daranno punteggi per entrambe.", -1);
		AggiungiElemento(finestre, -690, -20, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "- Alla fine vengono sottratti 5 punti dal punteggio totale per ogni tessera non giocata.", -1);
		
		AggiungiElemento(finestre, -700, -60, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "La Fine", -1);
		AggiungiElemento(finestre, -690, -80, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "Il gioco termina quando tutte le tessere sono state giocate, quando nessuno dei giocatori puo' formare una parola sul tabellone con le tessere rimaste", -1);
		AggiungiElemento(finestre, -690,-100, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "o quando tutti i giocatori passano il loro turno consecutivamente.", -1);
		AggiungiElemento(finestre, -690,-120, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "Al termine del gioco, verificati i punteggi, si decreta il vincitore!", -1);
		
		AggiungiElemento(finestre, -700,-160, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Buon Gioco!", -1);
		
		AggiungiElemento(finestre, -550+100, -275+50, -550-100, -275-50, BUTTON, 1, 1, 1, 0.75, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Indietro", FIN_ISTRUZIONI1);
		
	AggiungiFinestra(finestre, 720, 405, -720, -405, titolo + " > Giocatori", IDI_BACK4, FIN_BENVENUTO);
		AggiungiElemento(finestre, -500+100, 200+25, -500-100, 200-25, LISTBX, 0.75, 1, 1, 0.75, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "2", -1);
		AggiungiElemento(finestre, -500+300, 50+25, -500-100, 50-25, TEXTBX, 0.75, 1, 1, 0.75, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Giocatore 1", -1);
		AggiungiElemento(finestre, -500+300, -50+25, -500-100, -50-25, TEXTBX, 1, 1, 1, 0.75, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Giocatore 2", -1);
		AggiungiElemento(finestre, -500+300, -150+25, -500-100, -150-25, TEXTBX, 0.75, 1, 1, 0.75, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Giocatore 3", -1);
		AggiungiElemento(finestre, -500+300, -250+25, -500-100, -250-25, TEXTBX, 1, 1, 1, 0.75, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Giocatore 4", -1);
		
		AggiungiElemento(finestre, -70+100, -275+50, -70-100, -275-50, BUTTON, 1, 1, 1, 0.75, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Inizia", FIN_PARTITA);
		AggiungiElemento(finestre, 550+100, -275+50, 550-100, -275-50, BUTTON, 1, 1, 0.75, 0.75, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Riprendi", FIN_PARTITA);
		
		AggiungiElemento(finestre, 210, 250, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Esiste una Partita Salvata:", -1);
		AggiungiElemento(finestre, 210, 210, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Giocatore 1", -1);
		AggiungiElemento(finestre, 210, 190, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Giocatore 2", -1);
		AggiungiElemento(finestre, 210, 170, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Giocatore 3", -1);
		AggiungiElemento(finestre, 210, 150, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Giocatore 4", -1);
		AggiungiElemento(finestre, 210+300, 210, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "0", -1);
		AggiungiElemento(finestre, 210+300, 190, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "0", -1);
		AggiungiElemento(finestre, 210+300, 170, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "0", -1);
		AggiungiElemento(finestre, 210+300, 150, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "0", -1);
		
		AggiungiElemento(finestre, 100, 350, 100, -350, LINEA, 1, 1, 1, 0.75, 2, 0, 0, 0, 0, "", -1);
		
		AggiungiElemento(finestre, -610, 250, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Il Numero di Giocatori", -1);
		AggiungiElemento(finestre, -610, 100, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Il Nome dei Giocatori", -1);
		
	AggiungiFinestra(finestre, 720, -225, -720, -425, titolo + " > Partita", IDI_BACK5, FIN_PAUSA);
		float e=7;
		AggiungiElemento(finestre, -720 + (1440/e)*2 + (1440/e)/2 + 100, -340+50, -720 + (1440/e)*2 + (1440/e)/2 - 100, -340-50, BUTTON, 1, 1, 1, 0.75, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Randomizza", -1);
		AggiungiElemento(finestre, -720 + (1440/e)*3 + (1440/e)/2 + 100, -340+50, -720 + (1440/e)*3 + (1440/e)/2 - 100, -340-50, BUTTON, 0.75, 1, 0.75, 0.75, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Sostituisci", -1);
		AggiungiElemento(finestre, -720 + (1440/e)*4 + (1440/e)/2 + 100, -340+50, -720 + (1440/e)*4 + (1440/e)/2 - 100, -340-50, BUTTON, 1, 1, 1, 0.75, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Richiama", -1);
		AggiungiElemento(finestre, -720 + (1440/e)*5 + (1440/e)/2 + 100, -340+50, -720 + (1440/e)*5 + (1440/e)/2 - 100, -340-50, BUTTON, 0.75, 1, 1, 0.75, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Spunti", FIN_SUGG);
		AggiungiElemento(finestre, -720 + (1440/e)*6 + (1440/e)/2 + 100, -340+50, -720 + (1440/e)*6 + (1440/e)/2 - 100, -340-50, BUTTON, 1, 1, 1, 0.75, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Passa", -1);

		AggiungiElemento(finestre, 10 -720 + (1440/e)*0 + (1440/e)/2 - 100, -260-20, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "", -1);
		AggiungiElemento(finestre, 10 -720 + (1440/e)*0 + (1440/e)/2 - 100, -260-40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "", -1);
		AggiungiElemento(finestre, 10 -720 + (1440/e)*0 + (1440/e)/2 - 100, -260-60, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "", -1);
		AggiungiElemento(finestre, 10 -720 + (1440/e)*0 + (1440/e)/2 - 100, -260-80, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "", -1);
		
		AggiungiElemento(finestre, -420 + (1440/e)*0 + (1440/e)/2 - 100, -260-20, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "", -1);
		AggiungiElemento(finestre, -420 + (1440/e)*0 + (1440/e)/2 - 100, -260-40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "", -1);
		AggiungiElemento(finestre, -420 + (1440/e)*0 + (1440/e)/2 - 100, -260-60, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "", -1);
		AggiungiElemento(finestre, -420 + (1440/e)*0 + (1440/e)/2 - 100, -260-80, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "", -1);
	
	AggiungiFinestra(finestre, 400, 225, -400, -225, titolo + " > Partita > Pausa", IDI_BACK6, FIN_PARTITA);
		AggiungiElemento(finestre, +100, 100+50, -100, 100-50, BUTTON, 1, 1, 1, 0.75, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Continua", FIN_PARTITA);
		AggiungiElemento(finestre, -50, -100+50, -250, -100-50, BUTTON, 1, 0, 0, 0.75, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Abbandona", FIN_BENVENUTO);
		AggiungiElemento(finestre, +250, -100+50, 50, -100-50, BUTTON, 0.75, 1, 1, 0.75, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Salva", FIN_BENVENUTO);
	
	AggiungiFinestra(finestre, 720, 405, -720, -405, titolo + " > Partita > Spunti", IDI_BACK10, FIN_PARTITA);
		
		AggiungiElemento(finestre, -700, 300, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Gli Spunti", -1);
		
		AggiungiElemento(finestre, 10 -700, -80+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "#", -1);
		AggiungiElemento(finestre, 10 -600, -80+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Le Lettere Utilizzate", -1);
		AggiungiElemento(finestre, 10 -200, -80+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Le Parole Formate", -1);
		AggiungiElemento(finestre, 10+ 300, -80+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "I Punti", -1);
		
		AggiungiElemento(finestre, 10 -700, -120+340, 0, 0, TBITMA, 1, 0.6, 0, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "I", -1);
		AggiungiElemento(finestre, 10 -700, -140+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "II", -1);
		AggiungiElemento(finestre, 10 -700, -160+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "III", -1);
		AggiungiElemento(finestre, 10 -700, -180+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "IV", -1);
		AggiungiElemento(finestre, 10 -700, -200+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "V", -1);
		AggiungiElemento(finestre, 10 -700, -220+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "VI", -1);
		AggiungiElemento(finestre, 10 -700, -240+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "VII", -1);
		AggiungiElemento(finestre, 10 -700, -260+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "VIII", -1);
		AggiungiElemento(finestre, 10 -700, -280+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "IX", -1);
		AggiungiElemento(finestre, 10 -700, -300+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "X", -1);
		AggiungiElemento(finestre, 10 -700, -320+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "XI", -1);
		AggiungiElemento(finestre, 10 -700, -340+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "XII", -1);
		AggiungiElemento(finestre, 10 -700, -360+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "XIII", -1);
		AggiungiElemento(finestre, 10 -700, -380+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "XIV", -1);
		AggiungiElemento(finestre, 10 -700, -400+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "XV", -1);
		
		AggiungiElemento(finestre, 10 -600, -120+340, 0, 0, TBITMA, 1, 0.6, 0, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Parola 1, Parola 2", -1);
		AggiungiElemento(finestre, 10 -600, -140+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Parola 1, Parola 2", -1);
		AggiungiElemento(finestre, 10 -600, -160+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Parola 1, Parola 2", -1);
		AggiungiElemento(finestre, 10 -600, -180+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Parola 1, Parola 2", -1);
		AggiungiElemento(finestre, 10 -600, -200+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Parola 1, Parola 2", -1);
		AggiungiElemento(finestre, 10 -600, -220+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Parola 1, Parola 2", -1);
		AggiungiElemento(finestre, 10 -600, -240+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Parola 1, Parola 2", -1);
		AggiungiElemento(finestre, 10 -600, -260+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Parola 1, Parola 2", -1);
		AggiungiElemento(finestre, 10 -600, -280+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Parola 1, Parola 2", -1);
		AggiungiElemento(finestre, 10 -600, -300+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Parola 1, Parola 2", -1);
		AggiungiElemento(finestre, 10 -600, -320+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Parola 1, Parola 2", -1);
		AggiungiElemento(finestre, 10 -600, -340+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Parola 1, Parola 2", -1);
		AggiungiElemento(finestre, 10 -600, -360+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Parola 1, Parola 2", -1);
		AggiungiElemento(finestre, 10 -600, -380+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Parola 1, Parola 2", -1);
		AggiungiElemento(finestre, 10 -600, -400+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Parola 1, Parola 2", -1);
		
		AggiungiElemento(finestre, 10 -200, -120+340, 0, 0, TBITMA, 1, 0.6, 0, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "A, B, C, D, E, F, E", -1);
		AggiungiElemento(finestre, 10 -200, -140+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "A, B, C, D, E, F, E", -1);
		AggiungiElemento(finestre, 10 -200, -160+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "A, B, C, D, E, F, E", -1);
		AggiungiElemento(finestre, 10 -200, -180+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "A, B, C, D, E, F, E", -1);
		AggiungiElemento(finestre, 10 -200, -200+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "A, B, C, D, E, F, E", -1);
		AggiungiElemento(finestre, 10 -200, -220+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "A, B, C, D, E, F, E", -1);
		AggiungiElemento(finestre, 10 -200, -240+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "A, B, C, D, E, F, E", -1);
		AggiungiElemento(finestre, 10 -200, -260+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "A, B, C, D, E, F, E", -1);
		AggiungiElemento(finestre, 10 -200, -280+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "A, B, C, D, E, F, E", -1);
		AggiungiElemento(finestre, 10 -200, -300+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "A, B, C, D, E, F, E", -1);
		AggiungiElemento(finestre, 10 -200, -320+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "A, B, C, D, E, F, E", -1);
		AggiungiElemento(finestre, 10 -200, -340+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "A, B, C, D, E, F, E", -1);
		AggiungiElemento(finestre, 10 -200, -360+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "A, B, C, D, E, F, E", -1);
		AggiungiElemento(finestre, 10 -200, -380+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "A, B, C, D, E, F, E", -1);
		AggiungiElemento(finestre, 10 -200, -400+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "A, B, C, D, E, F, E", -1);
		
		AggiungiElemento(finestre, 10+ 300, -120+340, 0, 0, TBITMA, 1, 0.6, 0, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "+50", -1);
		AggiungiElemento(finestre, 10+ 300, -140+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "+50", -1);
		AggiungiElemento(finestre, 10+ 300, -160+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "+50", -1);
		AggiungiElemento(finestre, 10+ 300, -180+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "+50", -1);
		AggiungiElemento(finestre, 10+ 300, -200+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "+50", -1);
		AggiungiElemento(finestre, 10+ 300, -220+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "+50", -1);
		AggiungiElemento(finestre, 10+ 300, -240+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "+50", -1);
		AggiungiElemento(finestre, 10+ 300, -260+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "+50", -1);
		AggiungiElemento(finestre, 10+ 300, -280+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "+50", -1);
		AggiungiElemento(finestre, 10+ 300, -300+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "+50", -1);
		AggiungiElemento(finestre, 10+ 300, -320+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "+50", -1);
		AggiungiElemento(finestre, 10+ 300, -340+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "+50", -1);
		AggiungiElemento(finestre, 10+ 300, -360+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "+50", -1);
		AggiungiElemento(finestre, 10+ 300, -380+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "+50", -1);
		AggiungiElemento(finestre, 10+ 300, -400+340, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "+50", -1);
		
		
		
		AggiungiElemento(finestre, -(550/2)+100, -275+50, -(550/2)-100, -275-50, BUTTON, 1, 1, 1, 0.75, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Torna", FIN_PARTITA);
	
	AggiungiFinestra(finestre, 720, 405, -720, -405, titolo + " > Termine", IDI_BACK9, FIN_BENVENUTO);
	
		AggiungiElemento(finestre, -230, 0, 0, 0, TSTROK, 1, 1, 1, 0.6, 20, 1, 0, 1, GLUT_STROKE_ROMAN, "", -1);
		
		AggiungiElemento(finestre, -700, -40 +40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Le Statistiche", -1);
		
		AggiungiElemento(finestre, 10 -700, -80 +40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "#", -1);
		AggiungiElemento(finestre, 10 -600, -80 +40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "I Giocatori", -1);
		AggiungiElemento(finestre, 10 -300, -80 +40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "I Punti", -1);
		AggiungiElemento(finestre, 10 -200, -80 +40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Le Parole Giocate", -1);
		AggiungiElemento(finestre, 10+ 075, -80 +40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "La Lunghezza Media", -1);
		AggiungiElemento(finestre, 10+ 350, -80 +40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "I Punti per Parola", -1);
		
		AggiungiElemento(finestre, 10 -700, -120 +40, 0, 0, TBITMA, 1, 0.6, 0, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "I", -1);
		AggiungiElemento(finestre, 10 -700, -140 +40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "II", -1);
		AggiungiElemento(finestre, 10 -700, -160 +40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "III", -1);
		AggiungiElemento(finestre, 10 -700, -180 +40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "IV", -1);
		
		AggiungiElemento(finestre, 10 -600, -120 +40, 0, 0, TBITMA, 1, 0.6, 0, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Giocatore 1", -1);
		AggiungiElemento(finestre, 10 -600, -140 +40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Giocatore 2", -1);
		AggiungiElemento(finestre, 10 -600, -160 +40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Giocatore 3", -1);
		AggiungiElemento(finestre, 10 -600, -180 +40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Giocatore 4", -1);
		
		AggiungiElemento(finestre, 10 -300, -120 +40, 0, 0, TBITMA, 1, 0.6, 0, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "0", -1);
		AggiungiElemento(finestre, 10 -300, -140 +40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "0", -1);
		AggiungiElemento(finestre, 10 -300, -160 +40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "0", -1);
		AggiungiElemento(finestre, 10 -300, -180 +40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "0", -1);
		
		AggiungiElemento(finestre, 10 -200, -120 +40, 0, 0, TBITMA, 1, 0.6, 0, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "0", -1);
		AggiungiElemento(finestre, 10 -200, -140 +40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "0", -1);
		AggiungiElemento(finestre, 10 -200, -160 +40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "0", -1);
		AggiungiElemento(finestre, 10 -200, -180 +40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "0", -1);
		
		AggiungiElemento(finestre, 10+ 075, -120 +40, 0, 0, TBITMA, 1, 0.6, 0, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "0", -1);
		AggiungiElemento(finestre, 10+ 075, -140 +40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "0", -1);
		AggiungiElemento(finestre, 10+ 075, -160 +40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "0", -1);
		AggiungiElemento(finestre, 10+ 075, -180 +40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "0", -1);
		
		AggiungiElemento(finestre, 10+ 350, -120 +40, 0, 0, TBITMA, 1, 0.6, 0, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "0", -1);
		AggiungiElemento(finestre, 10+ 350, -140 +40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "0", -1);
		AggiungiElemento(finestre, 10+ 350, -160 +40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "0", -1);
		AggiungiElemento(finestre, 10+ 350, -180 +40, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "0", -1);
		
		AggiungiElemento(finestre, 550+100, -275+50, 550-100, -275-50, BUTTON, 1, 1, 1, 0.75, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Avanti", FIN_BENVENUTO);
		
		
	errori.push_back({"", ""});
	errori.push_back({"Mossa non Valida", "La pila ha raggiunto l'altezza massima."});
	errori.push_back({"Mossa non Valida", "La lettera non puo' essere posizionata su una lettera uguale."});
	errori.push_back({"Mossa non Valida", "Impossibile spostare una tessera posizionata al di sotto di un'altra."});
	errori.push_back({"Mossa non Valida", "Impossibile spostare una tessera nella stessa posizione di partenza."});
	errori.push_back({"Mossa non Valida", "La tessera non puo' essere posizionata su una tessera da validare."});
	errori.push_back({"Mossa non Valida", "Impossibile spostare una tessera su una cella gia' occupata."});
	errori.push_back({"Parola non Valida", "Una delle parole inserite non e' stata riconosciuta."});
	errori.push_back({"Parola troppo corta", "Una delle parole e' troppo corta."});
	errori.push_back({"Gap tra parole", "E' stato trovato un gap tra due parole."});
	errori.push_back({"Parole Isolate", "Sono state trovate alcune parole isolate."});
	errori.push_back({"Celle Centrali", "Almeno una parola deve trovarsi sulle 4 celle centrali."});
	errori.push_back({"Direzione Tessere", "Le nuove tessere devono trovarsi tutte nella stessa riga / colonna."});
	errori.push_back({"Parola Coperta", "Le nuove tessere non possono coprire interamente una vecchia parola."});
   	
	Sleep(1000);
	
	///// SETTO LA VARIABILE DI ATTESA
	wait_thread = false;
}



/*////////////////////////////////////////////////////////////////////////////////
//			FUNIONE DI INIZIALIZZAZIONE CHIAMATA A OPENGL ATTIVO				//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

int init_running(int init_operation_number)
{
	int ok = 0;
	int count = 0;
	
	///// CARICO IN MEMORIA LE IMMAGINI BITMAP PER LE TEXTURES
	for(int res = 0; res < NUMERO_WIND; res++, count++) if(count == init_operation_number){
		///// AGGIORNAMENTO INFORMAZIONI DI CARICAMENTO
		finestre_wait.at(0).ogg.at(0).testo = "Caricamento Texture #" + to_string(IDI_WIND1 + res) + "...";
		Sleep(100);
		LoadBitmapTextureRC(IDI_WIND1 + res, IDI_WIND1 + res, hinstance);
		ok=1;
	}
	for(int res = 0; res < NUMERO_BACK; res++, count++) if(count == init_operation_number){
		///// AGGIORNAMENTO INFORMAZIONI DI CARICAMENTO
		finestre_wait.at(0).ogg.at(0).testo = "Caricamento Texture #" + to_string(IDI_BACK1 + res) + "...";
		Sleep(100);
		LoadBitmapTextureRC(IDI_BACK1 + res, IDI_BACK1 + res, hinstance);
		ok=1;
	}
	for(int res = 0; res < NUMERO_TEX; res++, count++) if(count == init_operation_number){
		///// AGGIORNAMENTO INFORMAZIONI DI CARICAMENTO
		finestre_wait.at(0).ogg.at(0).testo = "Caricamento Texture #" + to_string(IDI_TEX1 + res) + "...";
		Sleep(100);
		LoadBitmapTextureRC(IDI_TEX1 + res, IDI_TEX1 + res, hinstance);
		ok=1;
	}
		
	return ok;
		
}



/*////////////////////////////////////////////////////////////////////////////////
//				FUNIONE DI INIZIALIZZAZIONE FINESTRA DI WINDOWS					//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

static void 
init_wind(void)
{
	///// CHIEDO L'HINSTANCE
	hinstance = GetModuleHandle(NULL);
	
	///// OTTENGO L'HWND DELLA FINESTRA
	HWND hwnd=0, hwnd2=0;
	do{
		hwnd = GetProcessRunningHWND("UpWords.exe");
		hwnd2 = FindWindow(NULL, titolo.c_str() );
	}while(hwnd != hwnd2 || hwnd == 0 || hwnd2 == 0);
	
	///// CAMBIO ALCUNI STILI DELLA FINESTRA
	long dwStyle = GetWindowLong(hwnd, GWL_STYLE);
	//dwStyle &=~ WS_MAXIMIZEBOX;
	dwStyle &=~ WS_SIZEBOX;
	dwStyle &=~ WS_SYSMENU;
	SetWindowLong(hwnd, GWL_STYLE, dwStyle);
 	//EnableMenuItem(GetSystemMenu(hwnd, FALSE), SC_CLOSE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	//ShowWindow(hwnd, SW_MAXIMIZE);
	
	///// SETTO L'ICONA DELLA FINESTRA
	HICON hIcon;
	hIcon = (HICON)LoadImage(hinstance, MAKEINTRESOURCE(IDI_MAIN), IMAGE_ICON, 128, 128, 0);
	if(hIcon) SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
	
	///// SE SERVE, SETTO IN FULLSCREEN
	if(fullScreen) glutFullScreen();
	
	///// CARICO TEXTURE INDISPENSABILI
	for(int res = 0; res < NUMERO_ATT; res++)
		LoadBitmapTextureRC(IDI_ATT1 + res, IDI_ATT1 + res, hinstance);
	
	///// CREO STRUTTURE PER LE FINESTRE DI ATTESA E SOTTOSTRUTTURE PER GLI ELEMENTI
	AggiungiFinestra(finestre_wait, 768, 295, -768, -295, titolo + " > Inizializzazione", IDI_ATT1, -1, 0, -100);
		AggiungiElemento(finestre_wait, 100, -215, 0, 0, TBITMA, 1.0, 1.0, 1.0, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Caricamento...", -1);
		AggiungiElemento(finestre_wait, 100, -235, 0, 0, TBITMA, 1.0, 1.0, 1.0, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Caricamento...", -1);
		AggiungiElemento(finestre_wait, 100, -195, 0, 0, TBITMA, 1, 1, 1, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "UpWords!  -  Il Gioco da Tavolo Tridimensionale!", -1);
		AggiungiElemento(finestre_wait, -100+100, -220+50, -100-100, -220-50, BUTTON, 1, 1, 1, 0.75, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Inizializzazione", -1);
		
	AggiungiFinestra(finestre_wait, 600, 337, -600, -337, titolo + " > Attendi", IDI_BACK1, -1, 0, 100);
		AggiungiElemento(finestre_wait, +100, 0+50, -100, 0-50, BUTTON, 1, 1, 1, 0.75, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "Attendi..", -1);
		
	AggiungiFinestra(finestre_wait, 600/2, 337/2, -600/2, -337/2, "", IDI_BACK1, -1, 0, 100);
		AggiungiElemento(finestre_wait, -250, 10, 0, 0, TBITMA, 1.0, 1.0, 1.0, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_18, "", -1);
		AggiungiElemento(finestre_wait, -250, -10, 0, 0, TBITMA, 1.0, 1.0, 1.0, 1, 0, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, "", -1);
	
}



/*////////////////////////////////////////////////////////////////////////////////
//									FUNZIONE MAIN								//
//									Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/



int 
main(int argc, char *argv[])
{	
	//////// SE ESISTE UN ALTRO PROCESSO DELLO STESSO PROGRAMMA
	if (ProcessRunning("UpWords.exe") > 1) exit(0);
	
	///// INIZIALIZZAZIONE PROGRAMMA
	init_pre_wind();

	///// INIZIALIZZAZIONE LIBRERIA GLUT / FREEGLUT
	glutInit(&argc, argv);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(10 ,10);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutSetOption(GLUT_MULTISAMPLE, max_multisample);
	
	///// CREAZIONE FINESTRA GLUT / FREEGLUT
	glutCreateWindow(titolo.c_str());
	
	///// INIZIALIZZAZIONE FINESTRA 
	init_wind();
	
	///// INIZIALIZZAZIONE CALLBACKS GLUT / FREEGLUT
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(mouseMove);
	
	///// ENTRATA NEL CICLO DI GESTIONE GLUT / FREEGLUT
	glutMainLoop();

	return 0;
}



/*////////////////////////////////////////////////////////////////////////////////
//																				//
//									UpWords										//
//																				//
//		SCRITTO DA		:	© Riccardo Campi									//
//																				//
//		DATA INIZIO		:	03/12/2017											//
//																				//
//		DATA FINE		:	00/00/2017											//
//																				//
//		LIBRERIE		:	OpenGl - Open Graphics Library						//
//							FreeGlut - Free OpenGl Utility Tookit				//
//							M.B. Comp. - Proprietario Marchio UpWords (1997)	//
//																				//
////////////////////////////////////////////////////////////////////////////////*/



