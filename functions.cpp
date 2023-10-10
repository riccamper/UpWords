


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
#include <conio.h>
#define PI 3.14159265

#define FREEGLUT_STATIC
#include "GL/freeglut.h"
#include "GL/glext.h"

#include "header.h"

using namespace std;



/*////////////////////////////////////////////////////////////////////////////////
//			FUNZIONI CHE AGGIUNGONO FINESTRE O ELEMENTI ALLE STESSE				//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

int AggiungiFinestra(vector <finestra> &finestre, float xtop, float ytop, float xbot, float ybot, string title, int sfondo, int child){
	
	///// CREO UNA STRUTTURA PER LA FINESTRA
	finestre.push_back({0});
	///// AGGIORNO I VALORI DELLA STRUTTURA APPENA CREATA
	finestre.at(finestre.size()-1).top.x = xtop;
	finestre.at(finestre.size()-1).top.y = ytop;
	finestre.at(finestre.size()-1).bot.x = xbot;
	finestre.at(finestre.size()-1).bot.y = ybot;
	finestre.at(finestre.size()-1).sfondo = sfondo;
	finestre.at(finestre.size()-1).titolo = title;
	finestre.at(finestre.size()-1).buttons = 1;
	
	finestre.at(finestre.size()-1).posx = -1000;
	finestre.at(finestre.size()-1).xactive = 0;
	finestre.at(finestre.size()-1).factive = 0;
	
	finestre.at(finestre.size()-1).child = child;
	
	finestre.at(finestre.size()-1).wind = IDI_WIND1 + rand()%NUMERO_WIND;
	
}

///// OVERLOAD DELLA FUNZIONE PRECEDENTE PER CONSENTIRE DI SCEGLIERE LA POSIZIONE E I BOTTONI SULLA BARRA DEL TITOLO
int AggiungiFinestra(vector <finestra> &finestre, float xtop, float ytop, float xbot, float ybot, string title, int sfondo, int child, bool buttons, float posx){
	
	///// CREO UNA STRUTTURA PER LA FINESTRA
	finestre.push_back({0});
	///// AGGIORNO I VALORI DELLA STRUTTURA APPENA CREATA
	finestre.at(finestre.size()-1).top.x = xtop;
	finestre.at(finestre.size()-1).top.y = ytop;
	finestre.at(finestre.size()-1).bot.x = xbot;
	finestre.at(finestre.size()-1).bot.y = ybot;
	finestre.at(finestre.size()-1).sfondo = sfondo;
	finestre.at(finestre.size()-1).titolo = title;
	finestre.at(finestre.size()-1).buttons = buttons;
	
	finestre.at(finestre.size()-1).posx = posx;
	finestre.at(finestre.size()-1).xactive = 0;
	finestre.at(finestre.size()-1).factive = 0;
	
	finestre.at(finestre.size()-1).child = child;
	
	finestre.at(finestre.size()-1).wind = IDI_WIND1 + rand()%NUMERO_WIND;
	
}

int AggiungiElemento(vector <finestra> &finestre, float xtop, float ytop, float xbot, float ybot, int tipo, float colr, float colg, float colb, float cola, float rotvel, float rotx, float roty, float rotz, void* font, string title, int target){
	
	///// CREO UNA STRUTTURA DENTRO LA STRUTTURA FINESTRE PER L'ELEMENTO
	finestre.at(finestre.size()-1).ogg.push_back({0});
	///// AGGIORNO I VALORI DELLA STRUTTURA APPENA CREATA
	finestre.at(finestre.size()-1).ogg.at(finestre.at(finestre.size()-1).ogg.size()-1).top.x = xtop;
	finestre.at(finestre.size()-1).ogg.at(finestre.at(finestre.size()-1).ogg.size()-1).top.y = ytop;
	finestre.at(finestre.size()-1).ogg.at(finestre.at(finestre.size()-1).ogg.size()-1).bot.x = xbot;
	finestre.at(finestre.size()-1).ogg.at(finestre.at(finestre.size()-1).ogg.size()-1).bot.y = ybot;
	finestre.at(finestre.size()-1).ogg.at(finestre.at(finestre.size()-1).ogg.size()-1).rotazione.vel = rotvel;
	finestre.at(finestre.size()-1).ogg.at(finestre.at(finestre.size()-1).ogg.size()-1).rotazione.x = rotx;
	finestre.at(finestre.size()-1).ogg.at(finestre.at(finestre.size()-1).ogg.size()-1).rotazione.y = roty;
	finestre.at(finestre.size()-1).ogg.at(finestre.at(finestre.size()-1).ogg.size()-1).rotazione.z = rotz;
	finestre.at(finestre.size()-1).ogg.at(finestre.at(finestre.size()-1).ogg.size()-1).tipo = tipo;
	finestre.at(finestre.size()-1).ogg.at(finestre.at(finestre.size()-1).ogg.size()-1).colore.r = colr;
	finestre.at(finestre.size()-1).ogg.at(finestre.at(finestre.size()-1).ogg.size()-1).colore.g = colg;
	finestre.at(finestre.size()-1).ogg.at(finestre.at(finestre.size()-1).ogg.size()-1).colore.b = colb;
	finestre.at(finestre.size()-1).ogg.at(finestre.at(finestre.size()-1).ogg.size()-1).colore.a = cola;
	finestre.at(finestre.size()-1).ogg.at(finestre.at(finestre.size()-1).ogg.size()-1).testo = title;
	finestre.at(finestre.size()-1).ogg.at(finestre.at(finestre.size()-1).ogg.size()-1).font = font;
	finestre.at(finestre.size()-1).ogg.at(finestre.at(finestre.size()-1).ogg.size()-1).target = target;
	
	finestre.at(finestre.size()-1).ogg.at(finestre.at(finestre.size()-1).ogg.size()-1).active = 0;
	finestre.at(finestre.size()-1).ogg.at(finestre.at(finestre.size()-1).ogg.size()-1).hidden = 0;
	
	///// SE IL TIPO E' "TBITMA" RICAVO LE DIMENSIONI BOTTOM, CHE DI DEFAULT NON DEVONO ESSERE FORNITE
	if(tipo == TBITMA){
		float xcharsum = 0;
		for(int s=0;s< title.length() ;s++) xcharsum += glutBitmapWidth(font, title[s]);
		float ycharsum = 0;
		ycharsum = glutBitmapHeight (font);
		finestre.at(finestre.size()-1).ogg.at(finestre.at(finestre.size()-1).ogg.size()-1).bot.x = xtop + (xcharsum);
		finestre.at(finestre.size()-1).ogg.at(finestre.at(finestre.size()-1).ogg.size()-1).bot.y = ytop + (ycharsum);
	}
	
}



/*////////////////////////////////////////////////////////////////////////////////
//			FUNZIONE ATTIVAZIONE TASTI ED ELEMENTI DI UNA FINESTRA				//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

int AttivaElemento(vector <finestra> &finestre, float x, float y, int ID){
	
	///// ITERO LE FINESTRE
	for (int count = 0; count < finestre.size(); count++)
		if(count == ID){
			///// ATTIVAZIONE TASTO DI CHIUSURA FINESTRA
	  		if(	x>=finestre.at(count).top.x - 30 &&
			  	x<=finestre.at(count).top.x &&
				y>=finestre.at(count).top.y -30 &&
				y<=finestre.at(count).top.y	){ finestre.at(count).xactive =1; }else finestre.at(count).xactive =0;
			///// ATTIVAZIONE TASTO DI RIDIMENSIONAMENTO
	  		if(	x>=finestre.at(count).top.x - 60 &&
			  	x<=finestre.at(count).top.x - 30 &&
				y>=finestre.at(count).top.y -30 &&
				y<=finestre.at(count).top.y	){ finestre.at(count).factive =1; }else finestre.at(count).factive =0;
				
				
			///// ITERO GLI OGGETTI ALL'INTERNO DELLA FINESTRA
			for (int count2 = 0; count2 < finestre.at(count).ogg.size(); count2++){
				
				if(finestre.at(count).ogg.at(count2).tipo == BUTTON)
			  		if(	x>=finestre.at(count).ogg.at(count2).bot.x &&
					  	x<=finestre.at(count).ogg.at(count2).top.x &&
						y>=finestre.at(count).ogg.at(count2).bot.y &&
						y<=finestre.at(count).ogg.at(count2).top.y	){ finestre.at(count).ogg.at(count2).active =1; }else finestre.at(count).ogg.at(count2).active =0;
				
				if(finestre.at(count).ogg.at(count2).tipo == TEXTBX && finestre.at(count).ogg.at(count2).hidden == 0)
			  		if(	x>=finestre.at(count).ogg.at(count2).bot.x &&
					  	x<=finestre.at(count).ogg.at(count2).top.x &&
						y>=finestre.at(count).ogg.at(count2).bot.y &&
						y<=finestre.at(count).ogg.at(count2).top.y	){ finestre.at(count).ogg.at(count2).active =1; }else finestre.at(count).ogg.at(count2).active =0;
				
				if(finestre.at(count).ogg.at(count2).tipo == TBITMA)
			  		if(	x>=finestre.at(count).ogg.at(count2).top.x &&
					  	x<=finestre.at(count).ogg.at(count2).top.x + pixelToUnitX( finestre.at(count).ogg.at(count2).bot.x - finestre.at(count).ogg.at(count2).top.x ) &&
						y>=finestre.at(count).ogg.at(count2).top.y &&
						y<=finestre.at(count).ogg.at(count2).top.y + pixelToUnitY( finestre.at(count).ogg.at(count2).bot.y - finestre.at(count).ogg.at(count2).top.y ) ){ finestre.at(count).ogg.at(count2).active =1; }else finestre.at(count).ogg.at(count2).active =0;
				
				if(finestre.at(count).ogg.at(count2).tipo == LISTBX)
			  		if(	x>=finestre.at(count).ogg.at(count2).bot.x &&
					  	x<=finestre.at(count).ogg.at(count2).bot.x + finestre.at(count).ogg.at(count2).top.y - finestre.at(count).ogg.at(count2).bot.y &&
						y>=finestre.at(count).ogg.at(count2).bot.y &&
						y<=finestre.at(count).ogg.at(count2).top.y	){ finestre.at(count).ogg.at(count2).active =1; }
					else
				  		if(	x>=finestre.at(count).ogg.at(count2).top.x - (finestre.at(count).ogg.at(count2).top.y - finestre.at(count).ogg.at(count2).bot.y) &&
						  	x<=finestre.at(count).ogg.at(count2).top.x &&
							y>=finestre.at(count).ogg.at(count2).bot.y &&
							y<=finestre.at(count).ogg.at(count2).top.y	){ finestre.at(count).ogg.at(count2).active =2; }else finestre.at(count).ogg.at(count2).active =0;
						
			}
			
	}else{
		///// SE NON E' LA FINESTRA CORRENTE ANNULLO LE ATTIVAZIONI DEI BOTTONI DEL TITOLO
		finestre.at(count).xactive =0;
		finestre.at(count).factive =0;
		///// ITERO GLI OGGETTI ALL'INTERNO DELLA FINESTRA
		for (int count2 = 0; count2 < finestre.at(count).ogg.size(); count2++){
	 		finestre.at(count).ogg.at(count2).active =0;
		}
	}
	
}



/*////////////////////////////////////////////////////////////////////////////////
//					FUNZIONI CHE DISEGNANO TESTO IN TBITMA						//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

void drawBitmapText(void* font, string str,float x,float y){
	///// SETTO LE COORDINATE
	glRasterPos2f(x, y);
	///// ITERO I CARATTERI
	for(char& c : str) {
		glutBitmapCharacter(font, c);
	}
	
}

void drawStrokeText(void* font, string str){
	///// ITERO I CARATTERI
	for(char& c : str) {
		glutStrokeCharacter(font, c);
	}
	
}



/*////////////////////////////////////////////////////////////////////////////////
//						FUNZIONE CHE DISEGNA FINESTRE							//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

int DisegnaFinestra(vector <finestra> finestre, int ID, float parametro1, float parametro2, float parametro3){
	
	///// OTTENGO IL TEMPO DI ESECUZIONE (SERVE PER FAR "BLINKARE")
	const int t = glutGet(GLUT_ELAPSED_TIME) / 200.0;
	
	///// VALORE ASSOLUTO DEL PARAMETRO DI ANIMAZIONE
	parametro1 += fabs( finestre.at(ID).posx );
	
	///// OTTENGO I VALORI PRINCIPALI DELLA FINESTRA
	float posx = finestre.at(ID).posx;
	
	float xtop = finestre.at(ID).top.x;
	float ytop = finestre.at(ID).top.y + posx*100;  ///// 500 PER SINCRONIA ELEMENTI-FINESTRA, MINORE PER FAR "ARRIVARE" GLI ELEMENTI SUCCESSIVAMENTE ALLA FINESTRA
	float xbot = finestre.at(ID).bot.x;
	float ybot = finestre.at(ID).bot.y + posx*100;  ///// 500 PER SINCRONIA ELEMENTI-FINESTRA, MINORE PER FAR "ARRIVARE" GLI ELEMENTI SUCCESSIVAMENTE ALLA FINESTRA
	int sfondo = finestre.at(ID).sfondo;
	string titolo = finestre.at(ID).titolo;
	
	int xactive = finestre.at(ID).xactive;
	int factive = finestre.at(ID).factive;
	
	vector <oggetto> ogg = finestre.at(ID).ogg;
	
	float line = parametro1 +1;
	
	///// DISEGNO LINEE CONTENITIVE & FINESTRA
	glLineWidth(line);
	glPushMatrix();
	if(finestre.at(ID).buttons){
		///// SFONDO BARRA DEL TITOLO
	  	glEnable( GL_TEXTURE_2D );
	  	glBindTexture( GL_TEXTURE_2D, finestre.at(ID).wind);
		glColor4f(1.0, 1.0, 1.0, 0.0 + (3/ ( parametro1 +4 ) ) );
	  	glBegin(GL_QUADS);
			glTexCoord2f(0.0,0.0);		glVertex2f((xbot) * (1/ ( parametro1 +1 ) ) , (ytop));
			glTexCoord2f(1.0,0.0);		glVertex2f((xtop-60) * (1/ ( parametro1 +1 ) ) , (ytop));
			glTexCoord2f(1.0,1.0);		glVertex2f((xtop-60) * (1/ ( parametro1 +1 ) ) , (ytop-30));
			glTexCoord2f(0.0,1.0);		glVertex2f((xbot) * (1/ ( parametro1 +1 ) ) , (ytop-30));
		glEnd();
		glDisable( GL_TEXTURE_2D );
		///// SFONDO RIQUADRO IN ALTO A DESTRA
		if(xactive) glColor4f(1.0, 0.0, 0.0, 0.0 + (1/ ( parametro1 +1 ) ) );
		else glColor4f(1.0, 0.0, 0.0, 0.0 + (1/ ( parametro1 +2 ) ) );
	  	glBegin(GL_QUADS);
			glVertex2f((xtop-30) * (1/ ( parametro1 +1 ) ) , (ytop));
			glVertex2f((xtop) * (1/ ( parametro1 +1 ) ) , (ytop));
			glVertex2f((xtop) * (1/ ( parametro1 +1 ) ) , (ytop-30));
			glVertex2f((xtop-30) * (1/ ( parametro1 +1 ) ) , (ytop-30));
		glEnd();
		///// SFONDO RIQUADRO IN ALTO A DESTRA CENTRALE
		if(factive) glColor4f(0.0, 0.5, 1.0, 0.0 + (1/ ( parametro1 +1 ) ) );
		else glColor4f(0.0, 0.5, 1.0, 0.0 + (1/ ( parametro1 +2 ) ) );
	  	glBegin(GL_QUADS);
			glVertex2f((xtop-60) * (1/ ( parametro1 +1 ) ) , (ytop));
			glVertex2f((xtop-30) * (1/ ( parametro1 +1 ) ) , (ytop));
			glVertex2f((xtop-30) * (1/ ( parametro1 +1 ) ) , (ytop-30));
			glVertex2f((xtop-60) * (1/ ( parametro1 +1 ) ) , (ytop-30));
		glEnd();
		///// SFONDO FINESTRA
	  	glEnable( GL_TEXTURE_2D );
	  	glBindTexture( GL_TEXTURE_2D, sfondo );
		glColor4f(1.0, 1.0, 1.0, 0.0 + (3/ ( parametro1 +4 ) ) );
	  	glBegin(GL_QUADS);
			glTexCoord2f(0.0,0.0);		glVertex2f((xbot) * (1/ ( parametro1 +1 ) ) , (ybot));
			glTexCoord2f(1.0,0.0);		glVertex2f((xtop) * (1/ ( parametro1 +1 ) ) , (ybot));
			glTexCoord2f(1.0,1.0);		glVertex2f((xtop) * (1/ ( parametro1 +1 ) ) , (ytop-30));
			glTexCoord2f(0.0,1.0);		glVertex2f((xbot) * (1/ ( parametro1 +1 ) ) , (ytop-30));
		glEnd();
		glDisable( GL_TEXTURE_2D );
	}else{
		///// SFONDO BARRA DEL TITOLO
	  	glEnable( GL_TEXTURE_2D );
	  	glBindTexture( GL_TEXTURE_2D, finestre.at(ID).wind);
		if(ID==0) glColor4f(0.2, 0.5, 0.75, 0.0 + (3/ ( parametro1 +4 ) ) );
		else glColor4f(1, 1, 1, 0.0 + (3/ ( parametro1 +4 ) ) );
	  	glBegin(GL_QUADS);
			glTexCoord2f(0.0,0.0);		glVertex2f((xbot) * (1/ ( parametro1 +1 ) ) , (ytop));
			glTexCoord2f(1.0,0.0);		glVertex2f((xtop) * (1/ ( parametro1 +1 ) ) , (ytop));
			glTexCoord2f(1.0,1.0);		glVertex2f((xtop) * (1/ ( parametro1 +1 ) ) , (ytop-30));
			glTexCoord2f(0.0,1.0);		glVertex2f((xbot) * (1/ ( parametro1 +1 ) ) , (ytop-30));
		glEnd();
		glDisable( GL_TEXTURE_2D );
		///// SFONDO FINESTRA
	  	glEnable( GL_TEXTURE_2D );
	  	glBindTexture( GL_TEXTURE_2D, sfondo );
		glColor4f(1.0, 1.0, 1.0, 0.0 + (3/ ( parametro1 +4 ) ) );
	  	glBegin(GL_QUADS);
			glTexCoord2f(0.0,0.0);		glVertex2f((xbot) * (1/ ( parametro1 +1 ) ) , (ybot));
			glTexCoord2f(1.0,0.0);		glVertex2f((xtop) * (1/ ( parametro1 +1 ) ) , (ybot));
			glTexCoord2f(1.0,1.0);		glVertex2f((xtop) * (1/ ( parametro1 +1 ) ) , (ytop-30));
			glTexCoord2f(0.0,1.0);		glVertex2f((xbot) * (1/ ( parametro1 +1 ) ) , (ytop-30));
		glEnd();
		glDisable( GL_TEXTURE_2D );
	}
		if(finestre.at(ID).buttons){
			///// SE LA FINESTRA E' L'ULTIMA
			if(ID==FIN_BENVENUTO){
				///// 'X' RIQUADRO IN ALTO A DESTRA
				glLineWidth(2);
				glColor4f(1.0, 1.0, 1.0, 0.0 + (1/ ( parametro1 +1 ) ) );
			  	glBegin(GL_LINES);
					glVertex2f((xtop-20) * (1/ ( parametro1 +1 ) ) , (ytop-20));
					glVertex2f((xtop-10) * (1/ ( parametro1 +1 ) ) , (ytop-10));
				glEnd();
			  	glBegin(GL_LINES);
					glVertex2f((xtop-20) * (1/ ( parametro1 +1 ) ) , (ytop-10));
					glVertex2f((xtop-10) * (1/ ( parametro1 +1 ) ) , (ytop-20));
				glEnd();
				glLineWidth(line);
			}else{
			///// SE LA FINESTRA NON E' L'ULTIMA
				///// 'FRECCIA' RIQUADRO IN ALTO A DESTRA
				glLineWidth(2);
				glColor4f(1.0, 1.0, 1.0, 0.0 + (1/ ( parametro1 +1 ) ) );
			  	glBegin(GL_LINES);
					glVertex2f((xtop-20) * (1/ ( parametro1 +1 ) ) , (ytop-15));
					glVertex2f((xtop-10) * (1/ ( parametro1 +1 ) ) , (ytop-15));
				glEnd();
			  	glBegin(GL_LINES);
					glVertex2f((xtop-20) * (1/ ( parametro1 +1 ) ) , (ytop-15));
					glVertex2f((xtop-15) * (1/ ( parametro1 +1 ) ) , (ytop-20));
				glEnd();
			  	glBegin(GL_LINES);
					glVertex2f((xtop-20) * (1/ ( parametro1 +1 ) ) , (ytop-15));
					glVertex2f((xtop-15) * (1/ ( parametro1 +1 ) ) , (ytop-10));
				glEnd();
				glLineWidth(line);
			}
			///// 'FRECCIA' FULLSCREEN RIQUADRO IN ALTO A DESTRA CENTRALE
			glLineWidth(2);
			glColor4f(1.0, 1.0, 1.0, 0.0 + (1/ ( parametro1 +1 ) ) );
		  	glBegin(GL_LINES);
				glVertex2f((xtop-30-20) * (1/ ( parametro1 +1 ) ) , (ytop-20));
				glVertex2f((xtop-30-10) * (1/ ( parametro1 +1 ) ) , (ytop-10));
			glEnd();
		  	glBegin(GL_LINES);
				glVertex2f((xtop-30-20) * (1/ ( parametro1 +1 ) ) , (ytop-20));
				glVertex2f((xtop-30-20) * (1/ ( parametro1 +1 ) ) , (ytop-15));
			glEnd();
		  	glBegin(GL_LINES);
				glVertex2f((xtop-30-20) * (1/ ( parametro1 +1 ) ) , (ytop-20));
				glVertex2f((xtop-30-15) * (1/ ( parametro1 +1 ) ) , (ytop-20));
			glEnd();
		  	glBegin(GL_LINES);
				glVertex2f((xtop-30-10) * (1/ ( parametro1 +1 ) ) , (ytop-10));
				glVertex2f((xtop-30-15) * (1/ ( parametro1 +1 ) ) , (ytop-10));
			glEnd();
		  	glBegin(GL_LINES);
				glVertex2f((xtop-30-10) * (1/ ( parametro1 +1 ) ) , (ytop-10));
				glVertex2f((xtop-30-10) * (1/ ( parametro1 +1 ) ) , (ytop-15));
			glEnd();
			glLineWidth(line);
		}
		///// TITOLO FINESTRA
		glColor4f(1.0, 1.0, 1.0, 0.0 + (1/ ( parametro1 +1 ) ) );
		drawBitmapText(GLUT_BITMAP_HELVETICA_18, titolo, (xbot+15) * (1/ ( parametro1 +1 ) ), (ytop - 9 - pixelToUnitY( glutBitmapHeight(GLUT_BITMAP_HELVETICA_18) )/2 ) );
		
		///// MOSTRO GLI OGGETTI ALL'INTERNO DELLA FINESTRA
		for (int count = 0; count < ogg.size(); count++)
			{
				ogg.at(count).top.y += posx*500;
				ogg.at(count).bot.y += posx*500;
				
				if(ogg.at(count).tipo == TBITMA){
					///// SE L'OGGETTO E' UN TIPO TESTO TBITMA
					if(!ogg.at(count).active)
						glColor4f(	ogg.at(count).colore.r,
									ogg.at(count).colore.g,
									ogg.at(count).colore.b,
									0 + (1/ ( parametro1 +(1/ogg.at(count).colore.a) ) ) );
					else
						glColor4f(	ogg.at(count).colore.r,
									ogg.at(count).colore.g,
									ogg.at(count).colore.b,
									0 + (1/ ( parametro1 +(1/ogg.at(count).colore.a) +1 ) ) );
					drawBitmapText(ogg.at(count).font, ogg.at(count).testo, ogg.at(count).top.x * (1/ ( parametro1 +1 ) ), ogg.at(count).top.y );
				}else if(ogg.at(count).tipo == TSTROK){
					///// SE L'OGGETTO E' UN TIPO TESTO TSTROK				
					glLineWidth(14);
					glPushMatrix();
						glColor4f(	ogg.at(count).colore.r,
									ogg.at(count).colore.g,
									ogg.at(count).colore.b,
									0 + (1/ ( parametro1 +(1/ogg.at(count).colore.a) ) ) );	
						glTranslatef(ogg.at(count).top.x * (1/ ( parametro1 +1 ) ), ogg.at(count).top.y, 0);
						glRotatef(	ogg.at(count).rotazione.vel,
									ogg.at(count).rotazione.x * parametro1,
									ogg.at(count).rotazione.y,
									ogg.at(count).rotazione.z);
						drawStrokeText(ogg.at(count).font, ogg.at(count).testo);
					glPopMatrix();
				}else if(ogg.at(count).tipo == BUTTON){
					///// SE L'OGGETTO E' UN TIPO BUTTON
					if(!ogg.at(count).hidden)
						if(!ogg.at(count).active)
							glColor4f(	ogg.at(count).colore.r,
										ogg.at(count).colore.g,
										ogg.at(count).colore.b,
										0 + (1/ ( parametro1 +(1/ogg.at(count).colore.a) ) ) );
						else
							glColor4f(	fabs( ogg.at(count).colore.r -0.5),
										fabs( ogg.at(count).colore.g -0.5),
										fabs( ogg.at(count).colore.b -0.5),
										0 + (1/ ( parametro1 +(1/ogg.at(count).colore.a) ) ) );
					else
						glColor4f(	ogg.at(count).colore.r,
									ogg.at(count).colore.g,
									ogg.at(count).colore.b,
									0 + (1/ ( parametro1 +(3/ogg.at(count).colore.a) ) ) );
				  	glBegin(GL_POLYGON);
						glVertex2f((ogg.at(count).bot.x + 30) * (1/ ( parametro1 +1 ) ) , (ogg.at(count).top.y));
						glVertex2f((ogg.at(count).top.x - 30) * (1/ ( parametro1 +1 ) ) , (ogg.at(count).top.y));
						glVertex2f((ogg.at(count).top.x) * (1/ ( parametro1 +1 ) ) , ogg.at(count).bot.y + (ogg.at(count).top.y - ogg.at(count).bot.y)/2 );
						glVertex2f((ogg.at(count).top.x - 30) * (1/ ( parametro1 +1 ) ) , (ogg.at(count).bot.y));
						glVertex2f((ogg.at(count).bot.x + 30) * (1/ ( parametro1 +1 ) ) , (ogg.at(count).bot.y));
						glVertex2f((ogg.at(count).bot.x) * (1/ ( parametro1 +1 ) ) , ogg.at(count).bot.y + (ogg.at(count).top.y - ogg.at(count).bot.y)/2 );
					glEnd();
					///// SCRIVO IL TESTO DEL BUTTON
					if(!ogg.at(count).hidden)
						if(ogg.at(count).active)
							glColor4f(	ogg.at(count).colore.r,
										ogg.at(count).colore.g,
										ogg.at(count).colore.b,
										0 + (1/ ( parametro1 +(1/ogg.at(count).colore.a) ) ) );
						else
							glColor4f(	fabs( ogg.at(count).colore.r -1),
										fabs( ogg.at(count).colore.g -1),
										fabs( ogg.at(count).colore.b -1),
										0 + (1/ ( parametro1 +(1/ogg.at(count).colore.a) ) ) );
					else
						glColor4f(	fabs( ogg.at(count).colore.r -1),
									fabs( ogg.at(count).colore.g -1),
									fabs( ogg.at(count).colore.b -1),
									0 + (1/ ( parametro1 +(3/ogg.at(count).colore.a) ) ) );
					float charsum=0;
					for(int s=0;s< ogg.at(count).testo.size() ;s++) charsum+=glutBitmapWidth(ogg.at(count).font, ogg.at(count).testo[s]);
					drawBitmapText(ogg.at(count).font, ogg.at(count).testo, ( ogg.at(count).top.x + ( ogg.at(count).bot.x - ogg.at(count).top.x )/2 - (pixelToUnitX(charsum))/2 ) * (1/ ( parametro1 +1 ) ), ogg.at(count).top.y + ( ogg.at(count).bot.y - ogg.at(count).top.y )/2 - pixelToUnitY((float)glutBitmapHeight(ogg.at(count).font))/3 );
				}else if(ogg.at(count).tipo == TEXTBX && ogg.at(count).hidden == 0){
					///// SE L'OGGETTO E' UN TIPO TEXTBX
					if(!ogg.at(count).active)
						glColor4f(	ogg.at(count).colore.r,
									ogg.at(count).colore.g,
									ogg.at(count).colore.b,
									0 + (1/ ( parametro1 +(1/ogg.at(count).colore.a) ) ) );
					else
						glColor4f(	fabs( ogg.at(count).colore.r -0.5),
									fabs( ogg.at(count).colore.g -0.5),
									fabs( ogg.at(count).colore.b -0.5),
									0 + (1/ ( parametro1 +(1/ogg.at(count).colore.a) ) ) );
				  	glBegin(GL_POLYGON);
						glVertex2f((ogg.at(count).bot.x) * (1/ ( parametro1 +1 ) ) , (ogg.at(count).top.y));
						glVertex2f((ogg.at(count).top.x) * (1/ ( parametro1 +1 ) ) , (ogg.at(count).top.y));
						glVertex2f((ogg.at(count).top.x) * (1/ ( parametro1 +1 ) ) , (ogg.at(count).bot.y));
						glVertex2f((ogg.at(count).bot.x) * (1/ ( parametro1 +1 ) ) , (ogg.at(count).bot.y));
					glEnd();
					///// SCRIVO IL TESTO DEL TEXTBX
					if(ogg.at(count).active)
						glColor4f(	ogg.at(count).colore.r,
									ogg.at(count).colore.g,
									ogg.at(count).colore.b,
									0 + (1/ ( parametro1 +(1/ogg.at(count).colore.a) ) ) );
					else
						glColor4f(	fabs( ogg.at(count).colore.r -1),
									fabs( ogg.at(count).colore.g -1),
									fabs( ogg.at(count).colore.b -1),
									0 + (1/ ( parametro1 +(1/ogg.at(count).colore.a) ) ) );
					float charsum=0;
					for(int s=0;s< ogg.at(count).testo.length() ;s++) charsum+=glutBitmapWidth(ogg.at(count).font, ogg.at(count).testo[s]);
					
					if(ogg.at(count).active && t%2)
						ogg.at(count).testo += "_";
					
					drawBitmapText(ogg.at(count).font, ogg.at(count).testo, ( ogg.at(count).top.x + ( ogg.at(count).bot.x - ogg.at(count).top.x )/2 - pixelToUnitX(charsum)/2 ) * (1/ ( parametro1 +1 ) ), ogg.at(count).top.y + ( ogg.at(count).bot.y - ogg.at(count).top.y )/2 -5 );
				}else if(ogg.at(count).tipo == LISTBX){
					///// SE L'OGGETTO E' UN TIPO LISTBX
					glColor4f(	ogg.at(count).colore.r,
								ogg.at(count).colore.g,
								ogg.at(count).colore.b,
								0 + (1/ ( parametro1 +(1/ogg.at(count).colore.a) ) ) );
				  	glBegin(GL_QUADS);
						glVertex2f((ogg.at(count).bot.x) * (1/ ( parametro1 +1 ) ) , (ogg.at(count).top.y));
						glVertex2f((ogg.at(count).top.x) * (1/ ( parametro1 +1 ) ) , (ogg.at(count).top.y));
						glVertex2f((ogg.at(count).top.x) * (1/ ( parametro1 +1 ) ) , (ogg.at(count).bot.y));
						glVertex2f((ogg.at(count).bot.x) * (1/ ( parametro1 +1 ) ) , (ogg.at(count).bot.y));
					glEnd();
					if(ogg.at(count).active == 1)
						glColor4f(	fabs( ogg.at(count).colore.r -0.5),
									fabs( ogg.at(count).colore.g -0.5),
									fabs( ogg.at(count).colore.b -0.5),
									0 + (1/ ( parametro1 +(1/ogg.at(count).colore.a) ) ) );
					else
						glColor4f(	ogg.at(count).colore.r,
									ogg.at(count).colore.g,
									ogg.at(count).colore.b,
									0 + (1/ ( parametro1 +(1/ogg.at(count).colore.a) ) ) );
				  	glBegin(GL_QUADS);
						glVertex2f((ogg.at(count).bot.x) * (1/ ( parametro1 +1 ) ) , (ogg.at(count).top.y));
						glVertex2f((ogg.at(count).bot.x + ogg.at(count).top.y - ogg.at(count).bot.y) * (1/ ( parametro1 +1 ) ) , (ogg.at(count).top.y));
						glVertex2f((ogg.at(count).bot.x + ogg.at(count).top.y - ogg.at(count).bot.y) * (1/ ( parametro1 +1 ) ) , (ogg.at(count).bot.y));
						glVertex2f((ogg.at(count).bot.x) * (1/ ( parametro1 +1 ) ) , (ogg.at(count).bot.y));
					glEnd();
					if(ogg.at(count).active == 2)
						glColor4f(	fabs( ogg.at(count).colore.r -0.5),
									fabs( ogg.at(count).colore.g -0.5),
									fabs( ogg.at(count).colore.b -0.5),
									0 + (1/ ( parametro1 +(1/ogg.at(count).colore.a) ) ) );
					else
						glColor4f(	ogg.at(count).colore.r,
									ogg.at(count).colore.g,
									ogg.at(count).colore.b,
									0 + (1/ ( parametro1 +(1/ogg.at(count).colore.a) ) ) );
				  	glBegin(GL_QUADS);
						glVertex2f((ogg.at(count).top.x - (ogg.at(count).top.y - ogg.at(count).bot.y) ) * (1/ ( parametro1 +1 ) ) , (ogg.at(count).top.y));
						glVertex2f((ogg.at(count).top.x) * (1/ ( parametro1 +1 ) ) , (ogg.at(count).top.y));
						glVertex2f((ogg.at(count).top.x) * (1/ ( parametro1 +1 ) ) , (ogg.at(count).bot.y));
						glVertex2f((ogg.at(count).top.x - (ogg.at(count).top.y - ogg.at(count).bot.y) ) * (1/ ( parametro1 +1 ) ) , (ogg.at(count).bot.y));
					glEnd();
					///// 'FRECCIA' RIQUADRO SINISTRA
					if(ogg.at(count).active == 1)
						glColor4f(	ogg.at(count).colore.r,
									ogg.at(count).colore.g,
									ogg.at(count).colore.b,
									0 + (1/ ( parametro1 +(1/ogg.at(count).colore.a) ) ) );
					else
						glColor4f(	fabs( ogg.at(count).colore.r -1),
									fabs( ogg.at(count).colore.g -1),
									fabs( ogg.at(count).colore.b -1),
									0 + (1/ ( parametro1 +(1/ogg.at(count).colore.a) ) ) );
				  	glBegin(GL_TRIANGLES);
						glVertex2f((ogg.at(count).bot.x) * (1/ ( parametro1 +1 ) ) +17 , ogg.at(count).bot.y + (ogg.at(count).top.y - ogg.at(count).bot.y)/2 );
						glVertex2f((ogg.at(count).bot.x + ogg.at(count).top.y - ogg.at(count).bot.y) * (1/ ( parametro1 +1 ) ) -17 , (ogg.at(count).top.y) -17);
						glVertex2f((ogg.at(count).bot.x + ogg.at(count).top.y - ogg.at(count).bot.y) * (1/ ( parametro1 +1 ) ) -17 , (ogg.at(count).bot.y) +17);
					glEnd();
					///// 'FRECCIA' RIQUADRO DESTRA
					if(ogg.at(count).active == 2)
						glColor4f(	ogg.at(count).colore.r,
									ogg.at(count).colore.g,
									ogg.at(count).colore.b,
									0 + (1/ ( parametro1 +(1/ogg.at(count).colore.a) ) ) );
					else
						glColor4f(	fabs( ogg.at(count).colore.r -1),
									fabs( ogg.at(count).colore.g -1),
									fabs( ogg.at(count).colore.b -1),
									0 + (1/ ( parametro1 +(1/ogg.at(count).colore.a) ) ) );
				  	glBegin(GL_TRIANGLES);
						glVertex2f((ogg.at(count).top.x) * (1/ ( parametro1 +1 ) ) -17 , ogg.at(count).bot.y + (ogg.at(count).top.y - ogg.at(count).bot.y)/2 );
						glVertex2f((ogg.at(count).top.x - (ogg.at(count).top.y - ogg.at(count).bot.y) ) * (1/ ( parametro1 +1 ) ) +17 , (ogg.at(count).top.y) -17);
						glVertex2f((ogg.at(count).top.x - (ogg.at(count).top.y - ogg.at(count).bot.y) ) * (1/ ( parametro1 +1 ) ) +17 , (ogg.at(count).bot.y) +17);
					glEnd();
					///// SCRIVO IL CONTENUTO DELLA LISTBX
					glColor4f(	fabs( ogg.at(count).colore.r -1),
								fabs( ogg.at(count).colore.g -1),
								fabs( ogg.at(count).colore.b -1),
								0 + (1/ ( parametro1 +(1/ogg.at(count).colore.a) ) ) );
					float charsum=0;
					for(int s=0;s< ogg.at(count).testo.length() ;s++) charsum+=glutBitmapWidth(ogg.at(count).font, ogg.at(count).testo[s]);
					drawBitmapText(ogg.at(count).font, ogg.at(count).testo, ( ogg.at(count).top.x + ( ogg.at(count).bot.x - ogg.at(count).top.x )/2 - pixelToUnitX(charsum) ) * (1/ ( parametro1 +1 ) ), ogg.at(count).top.y + ( ogg.at(count).bot.y - ogg.at(count).top.y )/2 -5 );
				}else if(ogg.at(count).tipo == LINEA){
					///// SE L'OGGETTO E' UN TIPO LINEA
					glLineWidth(ogg.at(count).rotazione.vel);
							glColor4f(	ogg.at(count).colore.r,
										ogg.at(count).colore.g,
										ogg.at(count).colore.b,
										0 + (1/ ( parametro1 +(1/ogg.at(count).colore.a) ) ) );
						  	glBegin(GL_LINES);
								glVertex2f((ogg.at(count).top.x) * (1/ ( parametro1 +1 ) ) , (ogg.at(count).top.y));
								glVertex2f((ogg.at(count).bot.x) * (1/ ( parametro1 +1 ) ) , (ogg.at(count).bot.y));
							glEnd();
					glLineWidth(line);
				}
			}

}



/*////////////////////////////////////////////////////////////////////////////////
//				FUNZIONE CHE DISEGNA SCACCHIERA E TESSERE						//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

int DisegnaScacchiera(scacchiera table, vector <tessera> tessere, float parametro1, float parametro2, float parametro3){
	
	///// IMPOSTO I VALORI DI SPAZIO E ROTAZIONE
	float posx=0;
	float posy=6.5;
	float posz=-34.0 - parametro1;
	float rotx=-37.5 - parametro1/2 + parametro2*2;
	float roty=0;
	float rotz=0;
	
	///// SE LA SCACCHIERA DEVE ESSERE VISIBILE
	if(table.visible!=0){

		glPushMatrix();
		
		///// DISEGNO LA SUPERFICIE DELLE CELLE DELLA SCACCHIERA
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, IDI_TEX2 );
		glColor4f(1.0, 1.0, 1.0, 1.0 );
		glTranslatef(0.0 + posx, 0.0 + posy, 0.0 + posz);
		glRotated(rotx,1,0,0);
		glRotated(roty,0,1,0);
		glRotated(rotz,0,0,1);
		for(int s=0;s<10;s++)
			for(int i=0;i<10;i++){
				
				int pos = s*10 + i;
				glStencilFunc(GL_ALWAYS, CELLE + pos, -1);		///// ASSEGNO ALLA CELLA UN IDENTIFICATIVO, RECUPERABILE DALLA FUNZIONE MOUSE
				glBegin(GL_QUADS);
				if(table.cell.at(pos).selected != 0 && table.cell.at(pos).active != 0) glColor4f(0.25, 0.75, 1.0, 1.0 );
				else if(table.cell.at(pos).selected != 0) glColor4f(0.0, 0.5, 1.0, 1.0 );
				else if(table.cell.at(pos).active != 0) glColor4f(0.25, 0.25, 0.25, 1.0 );
				else if(pos == 44 || pos == 45 || pos == 54 || pos == 55) glColor4f(0.0, 0.25, 1.0, 1.0 );		// COLORE CELLE CENTRALI (INIZIO GIOCO)
				else glColor4f(1.0, 1.0, 1.0, 1.0 );
					glTexCoord2f(0.0,0.0);		glVertex3f(-9 + 0.9f + i*2,-9 + 0.9f + s*2, 1.0f);
					glTexCoord2f(1.0,0.0);		glVertex3f(-9  -0.9f + i*2,-9 + 0.9f + s*2, 1.0f);
					glTexCoord2f(1.0,1.0);		glVertex3f(-9  -0.9f + i*2,-9  -0.9f + s*2, 1.0f);
					glTexCoord2f(0.0,1.0);		glVertex3f(-9 + 0.9f + i*2,-9  -0.9f + s*2, 1.0f);
	  			glEnd();
			}
		glDisable( GL_TEXTURE_2D );
		
		glStencilFunc(GL_ALWAYS, 0, -1);		///// RESETTO L'IDENTIFICATIVO
		
		///// DISEGNO GLI ORNAMENTI DELLA SCACCHIERA
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, IDI_TEX1 );
		glColor4f(0.5f, 0.5f, 0.5f, 1.0f );
		glBegin(GL_QUADS);
		for(int s=0;s<10;s++)
			for(int i=0;i<10-1;i++){
				glTexCoord2f(0.0,0.0);		glVertex3f(-9 + 1.0f + i*2,-9 + 1.0f + s*2, 0.5f);
				glTexCoord2f(1.0,0.0);		glVertex3f(-9 + 0.9f + i*2,-9 + 0.9f + s*2, 1.0f);
				glTexCoord2f(1.0,1.0);		glVertex3f(-9 + 0.9f + i*2,-9  -0.9f + s*2, 1.0f);
				glTexCoord2f(0.0,1.0);		glVertex3f(-9 + 1.0f + i*2,-9  -1.0f + s*2, 0.5f);
				
				glTexCoord2f(0.0,0.0);		glVertex3f(-9 + 1.1f + i*2,-9 + 0.9f + s*2, 1.0f);
				glTexCoord2f(1.0,0.0);		glVertex3f(-9 + 1.0f + i*2,-9 + 1.0f + s*2, 0.5f);
				glTexCoord2f(1.0,1.0);		glVertex3f(-9 + 1.0f + i*2,-9  -1.0f + s*2, 0.5f);
				glTexCoord2f(0.0,1.0);		glVertex3f(-9 + 1.1f + i*2,-9  -0.9f + s*2, 1.0f);
			}
	  	glEnd();
		glDisable( GL_TEXTURE_2D );
	  	
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, IDI_TEX1 );
		glColor4f(0.5f, 0.5f, 0.5f, 1.0f );
		glBegin(GL_QUADS);
		for(int s=0;s<10-1;s++)
			for(int i=0;i<10;i++){
				glTexCoord2f(0.0,0.0);		glVertex3f(-9 + 1.0f + i*2,-9 + 1.0f + s*2, 0.5f);
				glTexCoord2f(1.0,0.0);		glVertex3f(-9  -1.0f + i*2,-9 + 1.0f + s*2, 0.5f);
				glTexCoord2f(1.0,1.0);		glVertex3f(-9  -0.9f + i*2,-9 + 0.9f + s*2, 1.0f);
				glTexCoord2f(0.0,1.0);		glVertex3f(-9 + 0.9f + i*2,-9 + 0.9f + s*2, 1.0f);
				
				glTexCoord2f(0.0,0.0);		glVertex3f(-9 + 0.9f + i*2,-9 + 1.1f + s*2, 1.0f);
				glTexCoord2f(1.0,0.0);		glVertex3f(-9  -0.9f + i*2,-9 + 1.1f + s*2, 1.0f);
				glTexCoord2f(1.0,1.0);		glVertex3f(-9  -1.0f + i*2,-9 + 1.0f + s*2, 0.5f);
				glTexCoord2f(0.0,1.0);		glVertex3f(-9 + 1.0f + i*2,-9 + 1.0f + s*2, 0.5f);
			}
	  	glEnd();
		glDisable( GL_TEXTURE_2D );
	  	
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, IDI_TEX1 );
		glColor4f(0.5f, 0.5f, 0.5f, 1.0f );
		glBegin(GL_QUADS);
		for(int i=0;i<10;i++){
			glTexCoord2f(0.0,0.0);		glVertex3f(-9  -1.0f + i*2, -10 , 0.5f);
			glTexCoord2f(1.0,0.0);		glVertex3f(-9 + 1.0f + i*2, -10 , 0.5f);
			glTexCoord2f(1.0,1.0);		glVertex3f(-9 + 0.9f + i*2, -9.9 , 1.0f);
			glTexCoord2f(0.0,1.0);		glVertex3f(-9  -0.9f + i*2, -9.9 , 1.0f);
			
			glTexCoord2f(0.0,0.0);		glVertex3f(-9  -1.0f + i*2, -10 , -0.5f);
			glTexCoord2f(1.0,0.0);		glVertex3f(-9 + 1.0f + i*2, -10 , -0.5f);
			glTexCoord2f(1.0,1.0);		glVertex3f(-9 + 1.0f + i*2, -10 , 0.5f);
			glTexCoord2f(0.0,1.0);		glVertex3f(-9  -1.0f + i*2, -10 , 0.5f);
		}
	  	glEnd();
		glDisable( GL_TEXTURE_2D );
		
	  	glPopMatrix();
	
	
		glPushMatrix();
		///// DISEGNO LE TESSERE, SOLO SE SI TROVANO IN POSIZIONE "POS_SCACC" O "POS_SCACC_MOB"
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, IDI_TEX4 );
		glColor4f(1.0, 1.0, 1.0, 1.0 );
		glTranslatef(0.0 + posx, 0.0 + posy, 0.0 + posz);
		glRotated(rotx,1,0,0);
		glRotated(roty,0,1,0);
		glRotated(rotz,0,0,1);
		for(int k=0;k<5;k++)
			for(int s=0;s<10;s++)
				for(int i=0;i<10;i++){
				
					int pos = s*10 + i;
					int ok=-1;
					for(int j=0;j<100;j++) if(tessere.at(j).xpos == i && tessere.at(j).ypos == s && tessere.at(j).zpos == k && ( tessere.at(j).posizionata == POS_SCACC || tessere.at(j).posizionata == POS_SCACC_MOB ) ) ok = j;
					
					if(ok!=-1){
					
						glStencilFunc(GL_ALWAYS, TESSERE + ok, -1);		///// ASSEGNO ALLE TESSERE UN IDENTIFICATIVO, RECUPERABILE DALLA FUNZIONE MOUSE
						glBegin(GL_QUADS);
						if(tessere.at(ok).selected != 0 && tessere.at(ok).active != 0) glColor4f(0.25, 0.75, 1.0, 1.0 );
						else if(tessere.at(ok).selected != 0) glColor4f(0.0, 0.5, 1.0, 1.0 );
						else if(tessere.at(ok).active != 0) glColor4f(0.25, 0.25, 0.25, 1.0 );
						else if(tessere.at(ok).posizionata == POS_SCACC_MOB) glColor4f(0.1, 1.0, 0.1, 1.0 );
						else glColor4f(1.0, 1.0, 1.0, 1.0 );
							glTexCoord2f(0.0,0.0);		glVertex3f(-9 + 0.6f + i*2,-9 + 0.6f + s*2, 1.15f + k*0.15);
							glTexCoord2f(1.0,0.0);		glVertex3f(-9  -0.6f + i*2,-9 + 0.6f + s*2, 1.15f + k*0.15);
							glTexCoord2f(1.0,1.0);		glVertex3f(-9  -0.6f + i*2,-9  -0.6f + s*2, 1.15f + k*0.15);
							glTexCoord2f(0.0,1.0);		glVertex3f(-9 + 0.6f + i*2,-9  -0.6f + s*2, 1.15f + k*0.15);
		  				glEnd();
		  			}
				}
		glDisable( GL_TEXTURE_2D );
		
		glStencilFunc(GL_ALWAYS, 0, -1);		///// RESETTO L'IDENTIFICATIVO
		
		///// DISEGNO I BORDI DELLE TESSERE, SOLO SE SI TROVANO IN POSIZIONE "POS_SCACC" O "POS_SCACC_MOB"
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, IDI_TEX6 );
		glColor4f(1.0, 1.0, 1.0, 1.0 );
		for(int k=0;k<5;k++)
			for(int s=0;s<10;s++)
				for(int i=0;i<10;i++){
				
					int pos = s*10 + i;
					int ok=-1;
					for(int j=0;j<100;j++) if(tessere.at(j).xpos == i && tessere.at(j).ypos == s && tessere.at(j).zpos == k && ( tessere.at(j).posizionata == POS_SCACC || tessere.at(j).posizionata == POS_SCACC_MOB ) ) ok = j;
					
					if(ok!=-1){
					
						glStencilFunc(GL_ALWAYS, TESSERE + ok, -1);		///// ASSEGNO AI BORDI DELLE TESSERE UN IDENTIFICATIVO, RECUPERABILE DALLA FUNZIONE MOUSE
						glBegin(GL_QUADS);
							glTexCoord2f(0.0,0.0);		glVertex3f(-9 + 0.6f + i*2,-9  -0.6f + s*2, 1.15f + k*0.15);
							glTexCoord2f(1.0,0.0);		glVertex3f(-9  -0.6f + i*2,-9  -0.6f + s*2, 1.15f + k*0.15);
							glTexCoord2f(1.0,1.0);		glVertex3f(-9  -0.6f + i*2,-9  -0.6f + s*2, 1.05f + k*0.15);
							glTexCoord2f(0.0,1.0);		glVertex3f(-9 + 0.6f + i*2,-9  -0.6f + s*2, 1.05f + k*0.15);
							
							glTexCoord2f(0.0,0.0);		glVertex3f(-9 + 0.6f + i*2,-9 + 0.6f + s*2, 1.15f + k*0.15);
							glTexCoord2f(1.0,0.0);		glVertex3f(-9 + 0.6f + i*2,-9  -0.6f + s*2, 1.15f + k*0.15);
							glTexCoord2f(1.0,1.0);		glVertex3f(-9 + 0.6f + i*2,-9  -0.6f + s*2, 1.05f + k*0.15);
							glTexCoord2f(0.0,1.0);		glVertex3f(-9 + 0.6f + i*2,-9 + 0.6f + s*2, 1.05f + k*0.15);
							
							glTexCoord2f(0.0,0.0);		glVertex3f(-9 - 0.6f + i*2,-9  -0.6f + s*2, 1.15f + k*0.15);
							glTexCoord2f(1.0,0.0);		glVertex3f(-9 - 0.6f + i*2,-9 + 0.6f + s*2, 1.15f + k*0.15);
							glTexCoord2f(1.0,1.0);		glVertex3f(-9 - 0.6f + i*2,-9 + 0.6f + s*2, 1.05f + k*0.15);
							glTexCoord2f(0.0,1.0);		glVertex3f(-9 - 0.6f + i*2,-9 - 0.6f + s*2, 1.05f + k*0.15);
		  				glEnd();
		  			}
				}
		glDisable( GL_TEXTURE_2D );
		
		glStencilFunc(GL_ALWAYS, 0, -1);		///// RESETTO L'IDENTIFICATIVO
		
		glPopMatrix();
	
	
		///// SCRIVO LE LETTERE DELLE TESSERE, SOLO SE SI TROVANO IN POSIZIONE "POS_SCACC" O "POS_SCACC_MOB"
		for(int k=0;k<5;k++)
			for(int s=0;s<10;s++)
				for(int i=0;i<10;i++){
					
					int pos = s*10 + i;
					int ok=-1;
					for(int j=0;j<100;j++) if(tessere.at(j).xpos == i && tessere.at(j).ypos == s && tessere.at(j).zpos == k && ( tessere.at(j).posizionata == POS_SCACC || tessere.at(j).posizionata == POS_SCACC_MOB ) ) ok = j;
					
					if(ok!=-1){
					
						glPushMatrix();
						glTranslatef(0.0 + posx, 0.0 + posy, 0.0 + posz);
						glRotated(rotx,1,0,0);
						glRotated(roty,0,1,0);
						glRotated(rotz,0,0,1);
						glLineWidth(2);
						
						glColor4f(0.0, 0.0, 0.0, 1.0 );
						glTranslatef(-9  -0.5f + i*2,-9  -0.4f + s*2, 1.16f + k*0.15);
						
						glScalef(1/132.38, 1/132.38, 1/1);
						string ss (1, tessere.at(ok).lettera  );
					
						glStencilFunc(GL_ALWAYS, TESSERE + ok, -1);		///// ASSEGNO ALLE LETTERE (I PIXEL OCCUPATI DAL TESTO) UN IDENTIFICATIVO, RECUPERABILE DALLA FUNZIONE MOUSE
						drawStrokeText(GLUT_STROKE_ROMAN, "" + ss );
						glStencilFunc(GL_ALWAYS, 0, -1);		///// RESETTO L'IDENTIFICATIVO
						
						glPopMatrix();
					}
				}
	
	}
	
}



/*////////////////////////////////////////////////////////////////////////////////
//				FUNZIONE CHE DISEGNA RASTRELLIERE E TESSERE						//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

int DisegnaRastrelliere(scacchiera table, vector <tessera> tessere, vector <giocatore> giocatori, float parametro1, float parametro2, float parametro3){

	///// IMPOSTO I VALORI DI SPAZIO E ROTAZIONE
	float posx=0;
	float posy=4 - parametro2/4;
	float posz=-40.0 - parametro1;
	float rotx=-25.5 - parametro1/2 + parametro2;
	float roty=0;
	float rotz=0;
	
	///// SE LA SCACCHIERA DEVE ESSERE VISIBILE
	if(table.visible!=0)
		/////IL CODICE VIENE ESEGUITO SOLO PER IL GIOCATORE DI TURNO
		for(int g=0;g<giocatori.size();g++) if(giocatori.at(g).turno){

		glPushMatrix();
		
		///// DISEGNO LE CELLE DELLA RASTRELLIERA (TEORICAMENTE) DI OGNI GIOCATORE
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, IDI_TEX2 );
		glColor4f(1.0, 1.0, 1.0, 1.0 );
		glTranslatef(0.0 + posx, 0.0 + posy, 0.0 + posz);
		glRotated(rotx,1,0,0);
		glRotated(roty,0,1,0);
		glRotated(rotz,0,0,1);
		for(int s=0;s<1;s++)
			for(int i=0;i<7;i++){
				
				int pos = s*10 + i;
				glStencilFunc(GL_ALWAYS, RASTR_1 + g*7 + pos, -1);		///// ASSEGNO ALLE CELLE DELLA RASTRELLIERA UN IDENTIFICATIVO, RECUPERABILE DALLA FUNZIONE MOUSE
				glBegin(GL_QUADS);
				if(giocatori.at(g).cell.at(pos).selected != 0 && giocatori.at(g).cell.at(pos).active != 0) glColor4f(0.25, 0.75, 1.0, 1.0 );
				else if(giocatori.at(g).cell.at(pos).selected != 0) glColor4f(0.0, 0.5, 1.0, 1.0 );
				else if(giocatori.at(g).cell.at(pos).active != 0) glColor4f(0.25, 0.25, 0.25, 1.0 );
				else glColor4f(1.0, 1.0, 1.0, 1.0 );
					glTexCoord2f(0.0,0.0);		glVertex3f(-9 + 0.9f + i*2 + 3,-9 + 0.9f + s*2, 1.0f);
					glTexCoord2f(1.0,0.0);		glVertex3f(-9  -0.9f + i*2 + 3,-9 + 0.9f + s*2, 1.0f);
					glTexCoord2f(1.0,1.0);		glVertex3f(-9  -0.9f + i*2 + 3,-9  -0.9f + s*2, 1.0f);
					glTexCoord2f(0.0,1.0);		glVertex3f(-9 + 0.9f + i*2 + 3,-9  -0.9f + s*2, 1.0f);
	  			glEnd();
			}
		glDisable( GL_TEXTURE_2D );
		
		glStencilFunc(GL_ALWAYS, 0, -1);		///// RESETTO L'IDENTIFICATIVO
		
		///// DISEGNO GLI ORNAMENTI DELLA SCACCHIERA
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, IDI_TEX1 );
		glColor4f(0.5f, 0.5f, 0.5f, 1.0f );
		glBegin(GL_QUADS);
		for(int i=0;i<7-1;i++){
			glTexCoord2f(0.0,0.0);		glVertex3f(-9 + 1.0f + i*2 + 3,-9 + 1.0f, 0.5f);
			glTexCoord2f(1.0,0.0);		glVertex3f(-9 + 0.9f + i*2 + 3,-9 + 0.9f, 1.0f);
			glTexCoord2f(1.0,1.0);		glVertex3f(-9 + 0.9f + i*2 + 3,-9  -0.9f, 1.0f);
			glTexCoord2f(0.0,1.0);		glVertex3f(-9 + 1.0f + i*2 + 3,-9  -1.0f, 0.5f);
			
			glTexCoord2f(0.0,0.0);		glVertex3f(-9 + 1.1f + i*2 + 3,-9 + 0.9f, 1.0f);
			glTexCoord2f(1.0,0.0);		glVertex3f(-9 + 1.0f + i*2 + 3,-9 + 1.0f, 0.5f);
			glTexCoord2f(1.0,1.0);		glVertex3f(-9 + 1.0f + i*2 + 3,-9  -1.0f, 0.5f);
			glTexCoord2f(0.0,1.0);		glVertex3f(-9 + 1.1f + i*2 + 3,-9  -0.9f, 1.0f);
		}
	  	glEnd();
		glDisable( GL_TEXTURE_2D );
		
	  	
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, IDI_TEX1 );
		glColor4f(0.5f, 0.5f, 0.5f, 1.0f );
		glBegin(GL_QUADS);
		for(int i=0;i<7;i++){
			glTexCoord2f(0.0,0.0);		glVertex3f(-9  -1.0f + i*2 + 3, -10 , 0.5f);
			glTexCoord2f(1.0,0.0);		glVertex3f(-9 + 1.0f + i*2 + 3, -10 , 0.5f);
			glTexCoord2f(1.0,1.0);		glVertex3f(-9 + 0.9f + i*2 + 3, -9.9 , 1.0f);
			glTexCoord2f(0.0,1.0);		glVertex3f(-9  -0.9f + i*2 + 3, -9.9 , 1.0f);
			
			glTexCoord2f(0.0,0.0);		glVertex3f(-9  -1.0f + i*2 + 3, -10 , -0.5f);
			glTexCoord2f(1.0,0.0);		glVertex3f(-9 + 1.0f + i*2 + 3, -10 , -0.5f);
			glTexCoord2f(1.0,1.0);		glVertex3f(-9 + 1.0f + i*2 + 3, -10 , 0.5f);
			glTexCoord2f(0.0,1.0);		glVertex3f(-9  -1.0f + i*2 + 3, -10 , 0.5f);
		}
	  	glEnd();
		glDisable( GL_TEXTURE_2D );
		
	  	glPopMatrix();
	
	
		glPushMatrix();
		
		///// DISEGNO LE TESSERE, SOLO SE SI TROVANO IN POSIZIONE "POS_GIOCATORE"
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, IDI_TEX4 );
		glColor4f(1.0, 1.0, 1.0, 1.0 );
		glTranslatef(0.0 + posx, 0.0 + posy, 0.0 + posz);
		glRotated(rotx,1,0,0);
		glRotated(roty,0,1,0);
		glRotated(rotz,0,0,1);
		for(int k=0;k<1;k++)
			for(int s=0;s<1;s++)
				for(int i=0;i<7;i++){
				
					int pos = s*10 + i;
					int ok=-1;
					for(int j=0;j<100;j++) if(tessere.at(j).giocatore == g && tessere.at(j).pos == i && tessere.at(j).posizionata == POS_GIOCATORE) ok = j;
					
					if(ok!=-1){
					
						glStencilFunc(GL_ALWAYS, TESSERE + ok, -1);		///// ASSEGNO ALLE TESSERE UN IDENTIFICATIVO, RECUPERABILE DALLA FUNZIONE MOUSE
						glBegin(GL_QUADS);
						if(tessere.at(ok).selected != 0 && tessere.at(ok).active != 0) glColor4f(0.25, 0.75, 1.0, 1.0 );
						else if(tessere.at(ok).selected != 0) glColor4f(0.0, 0.5, 1.0, 1.0 );
						else if(tessere.at(ok).active != 0) glColor4f(0.25, 0.25, 0.25, 1.0 );
						else glColor4f(1.0, 1.0, 1.0, 1.0 );
							glTexCoord2f(0.0,0.0);		glVertex3f(-9 + 0.7f + i*2 + 3,-9 + 0.7f + s*2, 1.15f + k*0.15);
							glTexCoord2f(1.0,0.0);		glVertex3f(-9  -0.7f + i*2 + 3,-9 + 0.7f + s*2, 1.15f + k*0.15);
							glTexCoord2f(1.0,1.0);		glVertex3f(-9  -0.7f + i*2 + 3,-9  -0.7f + s*2, 1.15f + k*0.15);
							glTexCoord2f(0.0,1.0);		glVertex3f(-9 + 0.7f + i*2 + 3,-9  -0.7f + s*2, 1.15f + k*0.15);
		  				glEnd();
		  			}
				}
		glDisable( GL_TEXTURE_2D );
		
		glStencilFunc(GL_ALWAYS, 0, -1);		///// RESETTO L'IDENTIFICATIVO
		
		///// DISEGNO I BORDI DELLE TESSERE, SOLO SE SI TROVANO IN POSIZIONE "POS_GIOCATORE"
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, IDI_TEX6 );
		glColor4f(1.0, 1.0, 1.0, 1.0 );
		for(int k=0;k<1;k++)
			for(int s=0;s<1;s++)
				for(int i=0;i<7;i++){
				
					int pos = s*10 + i;
					int ok=-1;
					for(int j=0;j<100;j++) if(tessere.at(j).giocatore == g && tessere.at(j).pos == i && tessere.at(j).posizionata == POS_GIOCATORE) ok = j;
					
					if(ok!=-1){
					
						glStencilFunc(GL_ALWAYS, TESSERE + ok, -1);		///// ASSEGNO AI BORDI DELLE TESSERE UN IDENTIFICATIVO, RECUPERABILE DALLA FUNZIONE MOUSE
						glBegin(GL_QUADS);
							glTexCoord2f(0.0,0.0);		glVertex3f(-9 + 0.7f + i*2 + 3,-9  -0.7f + s*2, 1.15f + k*0.15);
							glTexCoord2f(1.0,0.0);		glVertex3f(-9  -0.7f + i*2 + 3,-9  -0.7f + s*2, 1.15f + k*0.15);
							glTexCoord2f(1.0,1.0);		glVertex3f(-9  -0.7f + i*2 + 3,-9  -0.7f + s*2, 1.05f + k*0.15);
							glTexCoord2f(0.0,1.0);		glVertex3f(-9 + 0.7f + i*2 + 3,-9  -0.7f + s*2, 1.05f + k*0.15);
							
							glTexCoord2f(0.0,0.0);		glVertex3f(-9 + 0.7f + i*2 + 3,-9 + 0.7f + s*2, 1.15f + k*0.15);
							glTexCoord2f(1.0,0.0);		glVertex3f(-9 + 0.7f + i*2 + 3,-9  -0.7f + s*2, 1.15f + k*0.15);
							glTexCoord2f(1.0,1.0);		glVertex3f(-9 + 0.7f + i*2 + 3,-9  -0.7f + s*2, 1.05f + k*0.15);
							glTexCoord2f(0.0,1.0);		glVertex3f(-9 + 0.7f + i*2 + 3,-9 + 0.7f + s*2, 1.05f + k*0.15);
							
							glTexCoord2f(0.0,0.0);		glVertex3f(-9 - 0.7f + i*2 + 3,-9  -0.7f + s*2, 1.15f + k*0.15);
							glTexCoord2f(1.0,0.0);		glVertex3f(-9 - 0.7f + i*2 + 3,-9 + 0.7f + s*2, 1.15f + k*0.15);
							glTexCoord2f(1.0,1.0);		glVertex3f(-9 - 0.7f + i*2 + 3,-9 + 0.7f + s*2, 1.05f + k*0.15);
							glTexCoord2f(0.0,1.0);		glVertex3f(-9 - 0.7f + i*2 + 3,-9 - 0.7f + s*2, 1.05f + k*0.15);
		  				glEnd();
		  			}
				}
		glDisable( GL_TEXTURE_2D );
		
		glStencilFunc(GL_ALWAYS, 0, -1);		///// RESETTO L'IDENTIFICATIVO
		
		glPopMatrix();
		
		///// SCRIVO LE LETTERE DELLE TESSERE, SOLO SE SI TROVANO IN POSIZIONE "POS_GIOCATORE"
		for(int k=0;k<1;k++)
			for(int s=0;s<1;s++)
				for(int i=0;i<7;i++){
					
					int pos = s*10 + i;
					int ok=-1;
					for(int j=0;j<100;j++) if(tessere.at(j).giocatore == g && tessere.at(j).pos == i && tessere.at(j).posizionata == POS_GIOCATORE) ok = j;
					
					if(ok!=-1){
					
						glPushMatrix();
						glTranslatef(0.0 + posx, 0.0 + posy, 0.0 + posz);
						glRotated(rotx,1,0,0);
						glRotated(roty,0,1,0);
						glRotated(rotz,0,0,1);
						glLineWidth(2);
						
						glColor4f(0.0, 0.0, 0.0, 1.0 );
						glTranslatef(-9  -0.5f + i*2 + 3,-9  -0.4f + s*2, 1.16f + k*0.15);
						
						glScalef(1/132.38, 1/132.38, 1/1);
						string ss (1, tessere.at(ok).lettera  );
					
						glStencilFunc(GL_ALWAYS, TESSERE + ok, -1);		///// ASSEGNO ALLE LETTERE (I PIXEL OCCUPATI DAL TESTO) UN IDENTIFICATIVO, RECUPERABILE DALLA FUNZIONE MOUSE
						drawStrokeText(GLUT_STROKE_ROMAN, "" + ss );
						glStencilFunc(GL_ALWAYS, 0, -1);		///// RESETTO L'IDENTIFICATIVO
						
						glPopMatrix();
					}
				}
	
	}
	
}



/*////////////////////////////////////////////////////////////////////////////////
//			FUNZIONI CHE RICHIAMA LA FINESTRA "INFO" CON wait = ATT_INFO		//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/




void threadInfoBox(int millisec, int &wait){
	///// ASPETTO I MILLISECONDI DESIDERATI
	Sleep(millisec);
	///// DOPODICHE' SETTO COME "NON ATTESA" LA VARIABILE APPOSITA
	wait = ATT_NO;
}

void infoBox(InfoBox infobox){
	
	///// RECUPERO PARAMETRI DALLA STRUCT
	vector <finestra> &finestre_wait = infobox.finestre_wait;
	string title = infobox.title;
	string nome = infobox.nome;
	string testo = infobox.testo;
	int sfondo = infobox.sfondo;
	int millisec = infobox.millisec;
	int &wait = infobox.wait;
	
	///// VARIABILE PER CALCOLARE IL CENTRO DEL TESTO
	float xcharsum = 0;
	
	///// SCRIVO LE INFORMAZIONI NELLA STRUCT DELLA FINESTRA INFO
	finestre_wait.at(ATT_INFO).titolo = title;
	finestre_wait.at(ATT_INFO).sfondo = sfondo;
	
	finestre_wait.at(ATT_INFO).ogg.at(0).testo = nome;
	xcharsum = 0;
	for(int s=0;s< nome.length() ;s++) xcharsum += pixelToUnitX( glutBitmapWidth( finestre_wait.at(ATT_INFO).ogg.at(0).font , nome[s]) );
	finestre_wait.at(ATT_INFO).ogg.at(0).top.x = 0 - (xcharsum)/2;
	
	finestre_wait.at(ATT_INFO).ogg.at(1).testo = testo;
	xcharsum = 0;
	for(int s=0;s< testo.length() ;s++) xcharsum += pixelToUnitX( glutBitmapWidth( finestre_wait.at(ATT_INFO).ogg.at(1).font , testo[s]) );
	finestre_wait.at(ATT_INFO).ogg.at(1).top.x = 0 - (xcharsum)/2;
	
	///// SETTO COME "IN ATTESA PER FINESTRA DI INFORMAZIONI" LA VARIABILE APPOSITA
	wait = ATT_INFO;
	
	///// CHIAMO THREAD NON BLOCCANTE CHE ASPETTA IL TEMPO DESIDERATO E RIPRISTINA LA VARIABILE "WAIT"
	thread infobox_thread = thread (threadInfoBox, millisec, ref(wait));
	infobox_thread.detach();
	
}



/*////////////////////////////////////////////////////////////////////////////////
//		FUNZIONI CHE IDENTIFICANO LETTERE INSERIMENTI NELLA SCACCHIERA			//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

///// RESTITUISCO VERO O FALSO IN BASE ALLA POSIZIONE DELLE TESSERE E ALLA RICHIESTA
bool controllaScacc(int posizionata, int tipoControllo){
	if(tipoControllo == 0)
		if(posizionata == POS_SCACC)
			return true;
		else
			return false;
	else if(tipoControllo == 1)
		if(posizionata == POS_SCACC_MOB || posizionata == POS_SCACC)
			return true;
		else
			return false;
	else
		if(posizionata == POS_SCACC_MOB)
			return true;
		else
			return false;
}

///// CONTROLLO LA DIREZIONE DELLE NUOVE TESSERE
int direzioneTessere(vector <tessera> tessere){
	
	///// CONTROLLO IN ORIZZONTALE
	bool ok_orizz = true;
	int orizz = -1;
	for(int y = 10; y >= 0; y--){
		for(int x = 0; x < 10; x++){
			for(int t = 0; t < 100; t++){
			if(controllaScacc(tessere.at(t).posizionata, 2))
				if(tessere.at(t).xpos == x && tessere.at(t).ypos == y){
					if(orizz == -1 || orizz == y)
						orizz = y;
					else ok_orizz = false;
				}
			}
		}
	}
		
	///// CONTROLLO IN VERTICALE
	bool ok_vert = true;
	int vert = -1;
	for(int x = 0; x < 10; x++){
		for(int y = 10; y >= 0; y--){
			for(int t = 0; t < 100; t++){
			if(controllaScacc(tessere.at(t).posizionata, 2))
				if(tessere.at(t).xpos == x && tessere.at(t).ypos == y){
					if(vert == -1 || vert == x)
						vert = x;
					else ok_vert = false;
				}
			}
		}
	}
	
	if((!ok_orizz) && (!ok_vert)) return -1;
	else if((ok_orizz) && (ok_vert)) return INDEFINITO;
	else if((ok_orizz) && (!ok_vert)) return ORIZZONTALE;
	else if((!ok_orizz) && (ok_vert)) return VERTICALE;
}

///// SE ALMENO UNA PAROLA CONTIENE TUTTE LE LETTERE NUOVE
bool tesserePresentiParole(vector <tessera> tessere, vector <parola> nuove){
	
	bool okk = false;
	
	if(nuove.size() == 0) okk = true;
	
	///// CONTROLLO INCROCIATO PAROLE / TESSERE (SE LE TESSERE NUOVE NON SONO CONTENUTE TUTTE IN ALMENO UNA PAROLA => ERRORE)
	for(int p = 0; p < nuove.size(); p++){
		bool ok = true;
		for(int t = 0; t < 100; t++){
			if(controllaScacc(tessere.at(t).posizionata, 2)){
				if(nuove.at(p).direzione == ORIZZONTALE)
					if(ok && tessere.at(t).ypos == nuove.at(p).pos.y && ( tessere.at(t).xpos >= nuove.at(p).pos.x && tessere.at(t).xpos <= nuove.at(p).pos.x + nuove.at(p).parola.size() ) ) ok = true;
					else ok = false;
				else if(nuove.at(p).direzione == VERTICALE)
					if(ok && tessere.at(t).xpos == nuove.at(p).pos.x && ( tessere.at(t).ypos >= nuove.at(p).pos.y - nuove.at(p).parola.size() && tessere.at(t).ypos <= nuove.at(p).pos.y ) ) ok = true;
					else ok = false;
			}
		}
		if(ok) okk = true;
	}
	
	return okk;
}

///// SE LE TESSERE COPRONO UN'INTERA PAROLA
bool tessereCopertoParole(vector <tessera> tessere, vector <parola> vecchio){
	
	bool okk = false;
	bool ok = false;
	
	///// CONTROLLO INCROCIATO PAROLE / TESSERE (SE LE TESSERE NUOVE COPRONO UN'INTERA PAROLA VECCHIA => ERRORE)
	for(int p = 0; p < vecchio.size(); p++){
		okk = false;
		for(int l = 0; l < vecchio.at(p).parola.size(); l++){
			ok = false;
			for(int t = 0; t < 100; t++)
				if(controllaScacc(tessere.at(t).posizionata, 2)){
					if(vecchio.at(p).direzione == ORIZZONTALE)
						if(tessere.at(t).ypos == vecchio.at(p).pos.y && tessere.at(t).xpos == vecchio.at(p).pos.x + l ) ok = true;
					else if(vecchio.at(p).direzione == VERTICALE)
						if(tessere.at(t).xpos == vecchio.at(p).pos.x && tessere.at(t).ypos == vecchio.at(p).pos.y - l ) ok = true;
				}
				
			if(!ok) okk = true;
		}
		if(!okk) return false;
	}
	
	return true;
}

///// "FOTOGRAFO" LA SITUAZIONE DELLA SCACCHIERA; RESTITUENDO LA LISTA DI PAROLE
vector <parola> identificaParole(vector <tessera> tessere, vector <string> vocabolario, int tipoControllo){
		
	vector <parola> ret;
	vector <parola> ret2;
	
	string par="";
	coord pos = {0, 0, 0};
	
	///// CONTROLLO IN ORIZZONTALE
	for(int y = 10; y >= 0; y--){
		for(int x = 0; x < 10; x++){
			char tr = '\0';
			for(int z = 0; z < 5; z++){
				for(int t = 0; t < 100; t++){
					if(controllaScacc(tessere.at(t).posizionata, tipoControllo))
						if(tessere.at(t).xpos == x && tessere.at(t).ypos == y && tessere.at(t).zpos == z){
							if(tr == '\0') pos = {x, y, 0};
							tr = tessere.at(t).lettera;
						}
					}
				}
		if(tr!='\0')
			par+= tr;
		else
			if(par!=""){
				if(par.size() > 0){
					transform(par.begin(), par.end(), par.begin(), ::tolower);
					ret.push_back({par, pos, ORIZZONTALE, false});
				}
				par="";
			}
		}
		if(par.size() > 0){
			transform(par.begin(), par.end(), par.begin(), ::tolower);
					ret.push_back({par, pos, ORIZZONTALE, false});
		}
		par="";
	}
		
	///// CONTROLLO IN VERTICALE
	for(int x = 0; x < 10; x++){
		for(int y = 10; y >= 0; y--){
			char tr = '\0';
			for(int z = 0; z < 5; z++){
				for(int t = 0; t < 100; t++){
					if(controllaScacc(tessere.at(t).posizionata, tipoControllo))
						if(tessere.at(t).xpos == x && tessere.at(t).ypos == y && tessere.at(t).zpos == z){
							if(tr == '\0') pos = {x, y, 0};
							tr = tessere.at(t).lettera;
						}
					}
				}
		if(tr!='\0')
			par+= tr;
		else
			if(par!=""){
				if(par.size() > 0){
					transform(par.begin(), par.end(), par.begin(), ::tolower);
					ret.push_back({par, pos, VERTICALE, false});
				}
				par="";
			}
		}
		if(par.size() > 0){
			transform(par.begin(), par.end(), par.begin(), ::tolower);
			ret.push_back({par, pos, VERTICALE, false});
		}
		par="";
	}
	
	///// AGGIUSTO LA POSIZIONE IN BASE ALLA DIREZIONE
	for(int p = 0; p < ret.size(); p++){
		if(ret.at(p).direzione == ORIZZONTALE)
			ret.at(p).pos.x -= ret.at(p).parola.size() - 1;
		if(ret.at(p).direzione == VERTICALE)
			ret.at(p).pos.y += ret.at(p).parola.size() - 1;
	}
	
	///// ELIMINO LE LETTERE SINGOLE GIA' COMPONENTI ALTRE PAROLE
	for(int p = 0; p < ret.size(); p++){
		bool ok = true;
		if(ret.at(p).parola.size() <= 1)
			for(int p2 = 0; p2 < ret.size(); p2++)
				if(ret.at(p2).parola.size() > 1)
					for(int p3 = 0; p3 < ret.at(p2).parola.size(); p3++)
						if(ret.at(p2).direzione == ORIZZONTALE){
							if(ret.at(p).pos.x == ret.at(p2).pos.x + p3 && ret.at(p).pos.y == ret.at(p2).pos.y) ok = false;
						}else{
							if(ret.at(p).pos.x == ret.at(p2).pos.x && ret.at(p).pos.y == ret.at(p2).pos.y - p3) ok = false;
						}
		if(ok) ret2.push_back(ret.at(p));
	}
	
	///// VERIFICO LE STRINGHE TROVATE CON IL VOCABOLARIO
	for(int p = 0; p < ret2.size(); p++){
		for(int v = 0; v < vocabolario.size(); v++){
			if(vocabolario.at(v) == ret2.at(p).parola) ret2.at(p).verificata = true;
		}
	}
	
	return ret2;
}

///// IDENTIFICO LE PAROLE NON IN COMUNE
vector <parola> identificaNuoveParole(vector <parola> vecchie, vector <parola> tutte){
	
	vector <parola> nuove;
	
	///// PAROLE NON IN COMUNE
	for(int n = 0; n < tutte.size(); n++){
		bool ce = false;
		for(int v = 0; v < vecchie.size(); v++)
			if(
			vecchie.at(v).parola == tutte.at(n).parola &&
			vecchie.at(v).direzione == tutte.at(n).direzione &&
			vecchie.at(v).pos.x == tutte.at(n).pos.x &&
			vecchie.at(v).pos.y == tutte.at(n).pos.y &&
			vecchie.at(v).verificata == tutte.at(n).verificata
			)
				ce = true;
		if(!ce)
			if(tutte.at(n).parola.size() > 1) nuove.push_back({tutte.at(n).parola, tutte.at(n).pos, tutte.at(n).direzione, tutte.at(n).verificata});
	}
	return nuove;
}


void vagliaParole(bool &prosegui, vector <tessera> tessere, vector <string> vocabolario, int &wait, vector <vector <string>> errori, vector <finestra> &finestre_wait, string title, int sfondo, int millisec){
	
	///// VARIABILE DI ERRORE
	int err = ERR_NO;
	
	///// OTTENGO LE PAROLE VECCHIE E NUOVE
	vector <parola> vecchie =	identificaParole(tessere, vocabolario, 0);
	vector <parola> tutte =		identificaParole(tessere, vocabolario, 1);
	vector <parola> nuove =		identificaNuoveParole(vecchie, tutte);
	
	
	///// ESEGUO CONTROLLI PER SPAZI TRA PAROLE
	if(!tesserePresentiParole(tessere, nuove)) err = ERR_PAROLA_INCOMPL;
	
	
	///// CONTROLLO VALIDITA' NUOVE PAROLE (SE ESISTONO)
	for(int n = 0; n < nuove.size(); n++){
		if(!nuove.at(n).verificata) err = ERR_PAROLA_NON_ESI;
	}
	
	
	///// CONTROLLO LUNGHEZZA (ALMENO 3)
	for(int n = 0; n < nuove.size(); n++){
		if(nuove.at(n).parola.size() <= 2) err = ERR_PAROLA_CORTA;
	}
	
	
	///// CONTROLLO SE C'E' UN GAP TRA LE PAROLE
	for(int n = 0; n < nuove.size(); n++){
		for(int n2 = 0; n2 < nuove.size(); n2++)
			if(n != n2){
				if(nuove.at(n).direzione == ORIZZONTALE)
					if(nuove.at(n2).direzione == ORIZZONTALE)
						if(nuove.at(n).pos.y == nuove.at(n2).pos.y) err = ERR_PAROLA_INCOMPL;
				if(nuove.at(n).direzione == VERTICALE)
					if(nuove.at(n2).direzione == VERTICALE)
						if(nuove.at(n).pos.x == nuove.at(n2).pos.x) err = ERR_PAROLA_INCOMPL;
			}
	}
	
	
	///// CONTROLLO SE CI SONO PAROLE ISOLATE
	if(tutte.size() > 1)
	for(int n = 0; n < tutte.size(); n++){
		bool ok = false;
		for(int l = 0; l < tutte.at(n).parola.size(); l++)
			for(int n2 = 0; n2 < tutte.size(); n2++)
				for(int l2 = 0; l2 < tutte.at(n2).parola.size(); l2++)
					if(n != n2){
						if(tutte.at(n).direzione == ORIZZONTALE)
							if(tutte.at(n2).direzione == VERTICALE)
								if(tutte.at(n).pos.y == tutte.at(n2).pos.y - l2 && tutte.at(n).pos.x + l == tutte.at(n2).pos.x)
									ok = true;
						if(tutte.at(n).direzione == VERTICALE)
							if(tutte.at(n2).direzione == ORIZZONTALE)
								if(tutte.at(n).pos.y - l == tutte.at(n2).pos.y && tutte.at(n).pos.x == tutte.at(n2).pos.x + l2)
									ok = true;
					}
		if(!ok) err = ERR_PAROLE_ISOLATE;
	}
	
	
	///// CONTROLLO CHE ALMENO UNA PAROLA STIA NELLE CELLE CENTRALI
	bool ok = false;
	for(int n = 0; n < tutte.size(); n++){
		for(int l = 0; l < tutte.at(n).parola.size(); l++){
			if(tutte.at(n).direzione == ORIZZONTALE)
						if(
						tutte.at(n).pos.y == 4 && tutte.at(n).pos.x + l == 4 ||
						tutte.at(n).pos.y == 5 && tutte.at(n).pos.x + l == 4 ||
						tutte.at(n).pos.y == 5 && tutte.at(n).pos.x + l == 5 ||
						tutte.at(n).pos.y == 4 && tutte.at(n).pos.x + l == 5
						)
							ok = true;
			if(tutte.at(n).direzione == VERTICALE)
						if(
						tutte.at(n).pos.y - l == 4 && tutte.at(n).pos.x == 4 ||
						tutte.at(n).pos.y - l == 5 && tutte.at(n).pos.x == 4 ||
						tutte.at(n).pos.y - l == 5 && tutte.at(n).pos.x == 5 ||
						tutte.at(n).pos.y - l == 4 && tutte.at(n).pos.x == 5
						)
							ok = true;
		}
	}
	if((!ok) && tutte.size() > 0) err = ERR_CELLE_CENTRALI;
	
	
	///// CONTROLLO VALIDITA' NUOVE PAROLE (SE NON SONO LETTERE SINGOLE)
	for(int n = 0; n < tutte.size(); n++){
		if(tutte.at(n).parola.size() <= 1) err = ERR_PAROLA_CORTA;
	}
	
	
	///// ESEGUO CONTROLLI SULLE TESSERE (SE NESSUNA PAROLA NUOVA HA DIREZIONE UGUALE A QUELLA DELLE TESSERE NUOVE)
	int dir = direzioneTessere(tessere);
	bool ok_dir = false;
	if(dir == INDEFINITO)
		ok_dir = true;
	else
		for(int s = 0; s < nuove.size(); s++)
			if(dir == nuove.at(s).direzione) ok_dir = true;
	if(!ok_dir) err = ERR_PAROLA_INCOMPL;
	
	
	///// ESEGUO CONTROLLI SULLE TESSERE
	if(dir == -1) err = ERR_TESSERE_DIREZI;
	
	
	///// CONTROLLO PER CAPIRE SE UNA PAROLA E' STATA COMOPLETAMENTE COPERTA
	if(!tessereCopertoParole(tessere, vecchie)) err = ERR_PAROLA_COPERTA;
	
	
	if(err != ERR_NO){
		///// SE CE' UN ERRORE CHIAMO LA FINESTRA DI INFORMAZIONI
		prosegui = false;
		infoBox({finestre_wait, title + " > " + errori.at(err).at(0), errori.at(err).at(0), errori.at(err).at(1), sfondo, millisec, wait});
	}else{
		///// ALTRIMENTI IMPOSTO "NESSUNA ATTESA" E "PUOI CAMBIARE GIOCATORE E ASSEGNARE I PUNTI"
		prosegui = true;
		//wait = ATT_NO;
	}
}



int controlloInserimento(vector <tessera> tessere, scacchiera table, int x, int y, int z, int seltess, int selcell){
	
	///// SETTO COME "NON C'E' ERRORE" LA VARIABILE APPOSITA
	int ok=ERR_NO;
	
	///// SE LA TESSERA STA ESSENDO SPOSTATA SU UNA TESSERA UGUALE ANNULLO IL MOVIMENTO
	if(ok==0){
	for(int k=0;k<100;k++)
		if(k != seltess)
			if(tessere.at(k).xpos == x && tessere.at(k).ypos == y && tessere.at(k).zpos == z-1 && ( tessere.at(k).posizionata == POS_SCACC || tessere.at(k).posizionata == POS_SCACC_MOB ) )
				if(tessere.at(k).lettera == tessere.at(seltess).lettera){ ok = ERR_LETTERA_UGUALE; break; }
	}
	
	///// SE LA TESSERA STA ESSENDO SPOSTATA SU UNA TESSERA CHE E' ANCH'ESSA DA VALIDARE ANNULLO IL MOVIMENTO
	if(ok==0){
	for(int k=0;k<100;k++)
		if(k != seltess)
			if(tessere.at(k).xpos == x && tessere.at(k).ypos == y && tessere.at(k).zpos == z-1 && tessere.at(k).posizionata == POS_SCACC_MOB ){
				ok = ERR_TESS_GIA_MOBILE;
				break;
			}
	}
	
	///// SE SOPRA LA TESSERA NE E' POSIZIONATA UN'ALTRA ANNULLO IL MOVIMENTO
	if(ok==0){
	for(int k=0;k<100;k++)
		if(tessere.at(k).xpos == tessere.at(seltess).xpos && tessere.at(k).ypos == tessere.at(seltess).ypos && ( tessere.at(k).posizionata == POS_SCACC || tessere.at(k).posizionata == POS_SCACC_MOB ) && ( tessere.at(seltess).posizionata == POS_SCACC || tessere.at(seltess).posizionata == POS_SCACC_MOB ) )
			if(tessere.at(k).zpos > tessere.at(seltess).zpos){ ok = ERR_TESSERA_SOTTO; break; }
	}
	
	///// SE LA PILA DI TESSERE E' MAGGIORE DI 5 ELEMENTI ANNULLO IL MOVIMENTO
	if(ok==0) if(z>4) ok = ERR_PILA_COMPLETA;
	
	///// SE LA TESSERA STA ESSENDO SPOSTATA SULLA STESSA CELLA DOVE SI TROVA ATTUALMENTE ANNULLO IL MOVIMENTO
	if(ok==0) if( ( tessere.at(seltess).posizionata == POS_SCACC || tessere.at(seltess).posizionata == POS_SCACC_MOB ) && ( tessere.at(seltess).xpos == x && tessere.at(seltess).ypos == y ) ) ok = ERR_CELLA_UGUALE;	
	
	///// RITORNO L'EVENTUALE ERRORE
	return ok;
	
}



/*////////////////////////////////////////////////////////////////////////////////
//				FUNZIONI DI FINE TURNO E DI ASSEGNAZIONE PUNTI					//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

int calcolaPunti(vector <tessera> tessere, vector <parola> nuove){
	
	int punti = 0;
	
	///// SE LA PAROLA HA TUTTE LE TESSERE NON IMPILATE
	for(int p = 0; p < nuove.size(); p++){
		bool multipiano = false;
		///// PER OGNI LETTERA DELLA PAROLA
		for(int l = 0; l < nuove.at(p).parola.size(); l++){
			///// RICAVO COORDINATE OGNI LETTERA DELLA PAROLA
			int xl = -1, yl = -1;
			if(nuove.at(p).direzione == ORIZZONTALE){ xl = nuove.at(p).pos.x + l; yl = nuove.at(p).pos.y; }
			else if(nuove.at(p).direzione == VERTICALE){ xl = nuove.at(p).pos.x; yl = nuove.at(p).pos.y - l; }
			
			///// RITROVO L'ALTEZZA DI OGNI TESSERA
			for(int s = 0; s < 100; s++){
				if(controllaScacc(tessere.at(s).posizionata, 1))
					if(tessere.at(s).xpos == xl && tessere.at(s).ypos == yl)
						if(tessere.at(s).zpos != 0)
							multipiano = true;	
			}
		}
		///// DISTINGUO TRA PAROLE MULTIPIANO E NON
		if(multipiano){
			///// PER OGNI LETTERA DELLA PAROLA
			for(int l = 0; l < nuove.at(p).parola.size(); l++){
				///// RICAVO COORDINATE OGNI LETTERA DELLA PAROLA
				int xl = -1, yl = -1;
				if(nuove.at(p).direzione == ORIZZONTALE){ xl = nuove.at(p).pos.x + l; yl = nuove.at(p).pos.y; }
				else if(nuove.at(p).direzione == VERTICALE){ xl = nuove.at(p).pos.x; yl = nuove.at(p).pos.y - l; }
				
				///// CONTO QUANTE TESSERE SONO IMPILATE IN UNA CELLA
				for(int s = 0; s < 100; s++){
					if(controllaScacc(tessere.at(s).posizionata, 1))
						if(tessere.at(s).xpos == xl && tessere.at(s).ypos == yl)
							punti++;
				}
			}
		}else{
			///// ASSEGNO N PUNTO A LETTERA
			punti += 2 * nuove.at(p).parola.size();
		}
		
		///// ASSEGNO 2 PUNTI BONUS PER LETTERA Q
		if(!multipiano)
			for(int s = 0; s < 100; s++)
				if(controllaScacc(tessere.at(s).posizionata, 2))
					if(tessere.at(s).lettera == 'Q')
						punti += 2;
						
	}
	
	///// ASSEGNO 20 PUNTI BONUS PER USO DI TUTTE LE LETTERE
	int tessere_usate = 0;
	for(int s = 0; s < 100; s++)
		if(controllaScacc(tessere.at(s).posizionata, 2))
			tessere_usate++;
	if(tessere_usate == 7) punti += 20;
	
	return punti;
	
}

void cambiaGioc(InfoBox infobox, vector <tessera> &tessere, vector <giocatore> &giocatori, int &stato, bool cambio_tessera){

	///// OTTENGO LE PAROLE VECCHIE E NUOVE
	vector <parola> vecchie =	identificaParole(tessere, vocabolario, 0);
	vector <parola> tutte =		identificaParole(tessere, vocabolario, 1);
	vector <parola> nuove =		identificaNuoveParole(vecchie, tutte);
	
	///// CALCOLO PUNTI
	int punti = calcolaPunti(tessere, nuove);
	
	///// AGGIORNO CONTEGGIO DEI TURNI PASSATI CONSECUTIVAMENTE
	if(!cambio_tessera)
		if(punti == 0)
			turni_passati++;
		else
			turni_passati = 0;
	else
		turni_passati = 0;
			
	///// CONTROLLO QUANDO E' IL MOMENTO DI TERMINARE LA PARTITA
	bool termina = false;
	///// SE UN GIOCATORE HA LA RASTRELLIERA VUOTA E IL SACCHETTO E' VUOTO
	for(int g = 0; g < giocatori.size(); g++)
		if(giocatori.at(g).turno == 1){
			termina = true;
			for(int t = 0; t < tessere.size(); t++)
				if(tessere.at(t).posizionata == POS_GIOCATORE && tessere.at(t).giocatore == g)
					termina = false;
			if(termina){
				bool sacchetto = true;
				for(int t = 0; t < tessere.size(); t++)
					if(tessere.at(t).posizionata == POS_NULLA)
						sacchetto = false;
				if(!sacchetto)
					termina = false;
			}
	}
	///// SE SI APPLICO LA PENALITA' AGLI ALTRI GIOCATORI
	if(termina){
		for(int g = 0; g < giocatori.size(); g++)
			if(giocatori.at(g).turno != 1){
				int tessere_rimaste = 0;
				for(int t = 0; t < tessere.size(); t++)
					if(tessere.at(t).posizionata == POS_GIOCATORE && tessere.at(t).giocatore == g)
						tessere_rimaste++;
				giocatori.at(g).punti -= 5 * tessere_rimaste;
		cout<<"giocatore "<<giocatori.at(g).nome<<" meno "<<tessere_rimaste*5<<" punti"<<endl;
			}
	}
	
	///// SE TUTTI I GIOCATORI HANNO PASSATO IL TURNO CONSECUTIVAMENTE TERMINA
	if(turni_passati == giocatori.size())
		termina = true;
	
	///// CHIMAMATA FINESTRA INFORMAZIONI
	string nome_successivo = "";
	string nome_corrente = "";
	for(int g = 0; g < giocatori.size(); g++)
		if(giocatori.at(g).turno == 1){
			nome_successivo = giocatori.at((g+1)%(giocatori.size())).nome;
			nome_corrente = giocatori.at(g).nome;
		}
	if(punti == 0){
		if(termina){
			infobox.sfondo = IDI_BACK4;
			infobox.title += nome_corrente;
			infobox.nome = "Partita Terminata";
			infobox.testo = "La Partita corrente e' Terminata!";
		}else{
			if(cambio_tessera){
				infobox.sfondo = IDI_BACK7;
				infobox.title += nome_corrente;
				infobox.nome = "La tessera Sostituita";
				infobox.testo = "Il turno passa ora a " + nome_successivo + ".";
			}else{
				infobox.sfondo = IDI_BACK7;
				infobox.title += nome_corrente;
				infobox.nome = "Il Turno Saltato";
				infobox.testo = "Il turno passa ora a " + nome_successivo + ".";
			}
		}
	}else{
		if(termina){
			infobox.sfondo = IDI_BACK4;
			infobox.title += nome_corrente;
			infobox.nome = "Partita Terminata";
			string piu_meno = "";
			piu_meno = ((punti >= 0) ? "+" : "-");
			infobox.testo = "Hai totalizzato " + piu_meno + to_string(punti) + " punti. La Partita corrente e' Terminata!";
		}else{
			infobox.sfondo = IDI_BACK7;
			infobox.title += nome_corrente;
			infobox.nome = "Il Turno Giocato";
			string piu_meno = "";
			piu_meno = ((punti >= 0) ? "+" : "-");
			infobox.testo = "Hai totalizzato " + piu_meno + to_string(punti) + " punti.  Il turno passa ora a " + nome_successivo + ".";
		}
	}
	infobox.millisec += 40 * punti;
	infoBox(infobox);
	
	///// SETTAGGIO TESSERE SULLA SCACCHIERA
	for(int s = 0; s < 100; s++)
		if(tessere.at(s).posizionata == POS_SCACC_MOB)
			tessere.at(s).posizionata = POS_SCACC;
	
	///// ATTESA
	Sleep(infobox.millisec / 4);
	
	///// ASSEGNAZIONE PUNTI
	for(int p = 0; p < punti; p++)
		for(int g = 0; g < giocatori.size(); g++)
			if(giocatori.at(g).turno == 1){
				giocatori.at(g).punti++;
				Sleep(20);
				break;
			}
	
	///// ASSEGNAZIONE ALTRE 
	int numero_lettere = 0;
	for(int n = 0; n < nuove.size(); n++)
		numero_lettere += nuove.at(n).parola.size();
	for(int g = 0; g < giocatori.size(); g++)
		if(giocatori.at(g).turno == 1){
			giocatori.at(g).numero_parole += nuove.size();
			giocatori.at(g).numero_lettere = giocatori.at(g).numero_lettere + numero_lettere ;
			break;
		}
	
	///// ATTESA
	Sleep(infobox.millisec / 4);

	///// RICAMBIO TESSERE
	for(int g=0;g<giocatori.size();g++)
		if(giocatori.at(g).turno == 1)
			for(int r=0;r<7;r++){
				int ce = -1;
				for(int s = 0; s < 100; s++)
					if(tessere.at(s).posizionata == POS_GIOCATORE && tessere.at(s).pos == r && tessere.at(s).giocatore == g)
						ce = r;
				if(ce == -1)
					for(int s = 0; s < 100; s++)
						if(tessere.at(s).posizionata == POS_NULLA){
							tessere.at(s).posizionata = POS_GIOCATORE;
							tessere.at(s).giocatore = g;
							tessere.at(s).pos = r;
							break;
						}
			}
	
	
	///// DESELEZIONO CELLE RASTRELLIERA
	for(int g=0;g<giocatori.size();g++)
		for(int s=0;s<7;s++)
			giocatori.at(g).cell.at(s).selected = 0;
	///// DESELEZIONO TESSERE
	for(int s=0;s<100;s++)
		tessere.at(s).selected = 0;
		
	///// CAMBIO DI GIOCATORE
	for(int g = 0; g < giocatori.size(); g++)
		if(giocatori.at(g).turno == 1){
			giocatori.at(g).turno = 0;
			giocatori.at((g+1)%(giocatori.size())).turno = 1;
			break;
		}
	
	if(termina)
		stato = FIN_TERMINE;
	
}

void fineTurno(InfoBox infobox, vector <tessera> &tessere, vector <giocatore> &giocatori, int &stato, bool cambio_tessera){
	
	///// CHIAMO THREAD NON BLOCCANTE CHE ASPETTA IL TEMPO DESIDERATO E AGISCE PER FINIRE IL TURNO
	thread fineturno = thread (cambiaGioc, infobox, ref(tessere), ref(giocatori), ref(stato), cambio_tessera);
	fineturno.detach();
	
}



/*////////////////////////////////////////////////////////////////////////////////
//						CONVERSIONI  PER TESSERE PRESENTI						//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/



///// RICAVA MATRICE "SCACCHIERA" DA VETTORE DI STRUTTURE
/*vector <vector <char>> ricavaMatrice(vector <tessera> tessere){
	
	vector <vector <char>> scacchiera;
	
	for(int y = 10; y >= 0; y--){
		vector <char> riga;
		for(int x = 0; x < 10; x++){
			char trovato = ' ';
			for(int z = 0; z < 5; z++)
				for(int t = 0; t < tessere.size(); t++)
					if(tessere.at(t).posizionata == POS_SCACC)
						if(tessere.at(t).xpos == x && tessere.at(t).ypos == y && tessere.at(t).zpos == z)
							trovato = tolower( tessere.at(t).lettera );
			riga.push_back(trovato);
		}
		scacchiera.push_back(riga);
	}

	return scacchiera;
}*/


///// RICAVO LISTA DI LETTERE PRESENTI SULLA SCACCHIERA
vector <char> ricavaVettore(vector <tessera> tessere){
	
	vector <char> lettere_scacchiera;
	
	for(int y = 10; y >= 0; y--){
		for(int x = 0; x < 10; x++){
			char trovato = ' ';
			for(int z = 0; z < 5; z++)
				for(int t = 0; t < tessere.size(); t++)
					if(tessere.at(t).posizionata == POS_SCACC)
						if(tessere.at(t).xpos == x && tessere.at(t).ypos == y && tessere.at(t).zpos == z)
							trovato = tolower( tessere.at(t).lettera );
			if(trovato != ' ')
				lettere_scacchiera.push_back(trovato);
		}
	}
	
	return lettere_scacchiera;
}



/*////////////////////////////////////////////////////////////////////////////////
//						FUNZIONI CALCOLI & SUGGERIMENTI							//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/


///// FUNZIONE CHE CONTROLLA LA VALIDITA' DELLA CONFIGURAZIONE DELLA SCACCHIERA SIMULATA CON LE PAROLE DEL SUGGERIMENTO
int vagliaParoleSuggerimento(int indiceSugg, vector <tessera> tessere, vector <string> &vocabolario, vector <parola> vecchie){
	
	///// VARIABILE DI ERRORE
	int err = ERR_NO;
	
	///// OTTENGO LE PAROLE VECCHIE E NUOVE
	//vector <parola> vecchie =	identificaParole(tessere, vocabolario, 0);
	vector <parola> tutte =		identificaParole(tessere, vocabolario, 1);
	vector <parola> nuove =		identificaNuoveParole(vecchie, tutte);
	
	
	///// ESEGUO CONTROLLI PER SPAZI TRA PAROLE
	if(!tesserePresentiParole(tessere, nuove)) err = ERR_PAROLA_INCOMPL;
	
	
	///// CONTROLLO VALIDITA' NUOVE PAROLE (SE ESISTONO)
	for(int n = 0; n < nuove.size(); n++){
		if(!nuove.at(n).verificata) err = ERR_PAROLA_NON_ESI;
	}
	
	
	///// CONTROLLO LUNGHEZZA (ALMENO 3)
	for(int n = 0; n < nuove.size(); n++){
		if(nuove.at(n).parola.size() <= 2) err = ERR_PAROLA_CORTA;
	}
	
	
	///// CONTROLLO SE C'E' UN GAP TRA LE PAROLE
	for(int n = 0; n < nuove.size(); n++){
		for(int n2 = 0; n2 < nuove.size(); n2++)
			if(n != n2){
				if(nuove.at(n).direzione == ORIZZONTALE)
					if(nuove.at(n2).direzione == ORIZZONTALE)
						if(nuove.at(n).pos.y == nuove.at(n2).pos.y) err = ERR_PAROLA_INCOMPL;
				if(nuove.at(n).direzione == VERTICALE)
					if(nuove.at(n2).direzione == VERTICALE)
						if(nuove.at(n).pos.x == nuove.at(n2).pos.x) err = ERR_PAROLA_INCOMPL;
			}
	}
	
	
	///// CONTROLLO SE CI SONO PAROLE ISOLATE
	if(tutte.size() > 1)
	for(int n = 0; n < tutte.size(); n++){
		bool ok = false;
		for(int l = 0; l < tutte.at(n).parola.size(); l++)
			for(int n2 = 0; n2 < tutte.size(); n2++)
				for(int l2 = 0; l2 < tutte.at(n2).parola.size(); l2++)
					if(n != n2){
						if(tutte.at(n).direzione == ORIZZONTALE)
							if(tutte.at(n2).direzione == VERTICALE)
								if(tutte.at(n).pos.y == tutte.at(n2).pos.y - l2 && tutte.at(n).pos.x + l == tutte.at(n2).pos.x)
									ok = true;
						if(tutte.at(n).direzione == VERTICALE)
							if(tutte.at(n2).direzione == ORIZZONTALE)
								if(tutte.at(n).pos.y - l == tutte.at(n2).pos.y && tutte.at(n).pos.x == tutte.at(n2).pos.x + l2)
									ok = true;
					}
		if(!ok) err = ERR_PAROLE_ISOLATE;
	}
	
	
	///// CONTROLLO CHE ALMENO UNA PAROLA STIA NELLE CELLE CENTRALI
	bool ok = false;
	for(int n = 0; n < tutte.size(); n++){
		for(int l = 0; l < tutte.at(n).parola.size(); l++){
			if(tutte.at(n).direzione == ORIZZONTALE)
						if(
						tutte.at(n).pos.y == 4 && tutte.at(n).pos.x + l == 4 ||
						tutte.at(n).pos.y == 5 && tutte.at(n).pos.x + l == 4 ||
						tutte.at(n).pos.y == 5 && tutte.at(n).pos.x + l == 5 ||
						tutte.at(n).pos.y == 4 && tutte.at(n).pos.x + l == 5
						)
							ok = true;
			if(tutte.at(n).direzione == VERTICALE)
						if(
						tutte.at(n).pos.y - l == 4 && tutte.at(n).pos.x == 4 ||
						tutte.at(n).pos.y - l == 5 && tutte.at(n).pos.x == 4 ||
						tutte.at(n).pos.y - l == 5 && tutte.at(n).pos.x == 5 ||
						tutte.at(n).pos.y - l == 4 && tutte.at(n).pos.x == 5
						)
							ok = true;
		}
	}
	if((!ok) && tutte.size() > 0) err = ERR_CELLE_CENTRALI;
	
	
	///// CONTROLLO VALIDITA' NUOVE PAROLE (SE NON SONO LETTERE SINGOLE)
	for(int n = 0; n < tutte.size(); n++){
		if(tutte.at(n).parola.size() <= 1) err = ERR_PAROLA_CORTA;
	}
	
	
	///// ESEGUO CONTROLLI SULLE TESSERE (SE NESSUNA PAROLA NUOVA HA DIREZIONE UGUALE A QUELLA DELLE TESSERE NUOVE)
	int dir = direzioneTessere(tessere);
	bool ok_dir = false;
	if(dir == INDEFINITO)
		ok_dir = true;
	else
		for(int s = 0; s < nuove.size(); s++)
			if(dir == nuove.at(s).direzione) ok_dir = true;
	if(!ok_dir) err = ERR_PAROLA_INCOMPL;
	
	
	///// ESEGUO CONTROLLI SULLE TESSERE
	if(dir == -1) err = ERR_TESSERE_DIREZI;
	
	
	///// CONTROLLO PER CAPIRE SE UNA PAROLA E' STATA COMOPLETAMENTE COPERTA
	if(!tessereCopertoParole(tessere, vecchie)) err = ERR_PAROLA_COPERTA;
	
	///// SE LA CONFIGURAZIONE NON CREA PROBLEMI LA AGGIUNGO AL VETTORE DI "SUGGERIMENTI"
	if(err == ERR_NO){
		///// CREO STRINGA PAROLE
		string p = "";
		for(int i = 0; i < nuove.size(); i++)
			if(i == 0)
				p = nuove.at(i).parola;
			else
				p += ", " + nuove.at(i).parola;
		///// CREO STRINGA LETTERE
		string l = "";
		for(int i = 0; i < tessere.size(); i++)
			if(tessere.at(i).posizionata == POS_SCACC_MOB)
				if(l == "")
					l = "" + string(1, tessere.at(i).lettera);
				else
					l += ", " + string(1, tessere.at(i).lettera);
		///// CALCOLO PUNTI
		int punti = calcolaPunti(tessere, nuove);
		
		Sleep(10);
		
		///// AGGIUNGO AL VETTORE
		suggerimenti.at(indiceSugg) = {p, l, punti, tessere};
		
		Sleep(10);
		
		///// RIORDINO IL VETTORE
		//sort( suggerimenti.begin(), suggerimenti.end(), []( sugg a, sugg b ){ return a.punti > b.punti; });
		
		//Sleep(100);
	}
	
	return err;
	
}


///// LA FUNZIONE VERIFICA SE UNA PAROLA FRUTTO DI COMBINAZIONI DI LETTERE E' EFFETTIVAMENTE SOVRAPPONIBILE
bool parolaFattibile(string fissa, string cercata, vector <char> lettere_7, int &differenza){

	///// CERCO UNA CORRISPONDENZA TRA LE DUE PAROLE
	int posizione = 0;
	vector <char> lettere_temp = lettere_7;
	for(; posizione < cercata.size(); posizione++){
		int j=0;
		for(; j < lettere_temp.size(); j++)
			if(cercata.at(posizione)==lettere_temp.at(j)){
				lettere_temp.at(j)='#';
				break;
			}
		if(j == lettere_temp.size()){
			break;
		}
	}

	///// SE NON HO TROVATO ALCUNA CORRISPONDENZA
	if(posizione == cercata.size()){
		bool trovata = false;
		for(posizione = 0; posizione < cercata.size(); posizione++){
			for(int h = 0; h < fissa.size(); h++)
				if(cercata.at(posizione) == fissa.at(h)){
					trovata = true;
					break;
				}
			if(trovata)
				break;
		}
		if(!trovata)
			return false;
	}
	/*
	///// ESCLUDE PAROLE CHE HANNO LETTERE NON USATE E NON COPERTE
	int pos_fissa = 0;
	for(; pos_fissa < fissa.size(); pos_fissa++)
		if(fissa.at(pos_fissa) == cercata.at(posizione))
			if(pos_fissa > posizione || fissa.size() + (posizione - pos_fissa) > cercata.size())
				return false;
			else
				break;
	*/		
			
	///// ESCLUDE PAROLE CHE HANNO LETTERE NON USATE E NON COPERTE
	int pos_fissa = 0;
	int nuova_posizione = 0;
	bool trovata2 = true;
	for(; pos_fissa < fissa.size(); pos_fissa++)
		if(fissa.at(pos_fissa) == cercata.at(posizione))
			if(pos_fissa > posizione || fissa.size() + (posizione - pos_fissa) > cercata.size()){
				trovata2 = false;
				for(; nuova_posizione < cercata.size(); nuova_posizione++){
					if(cercata.at(nuova_posizione) == fissa.at(pos_fissa)){
						trovata2 = true;
						pos_fissa--;
						posizione = nuova_posizione;
						nuova_posizione++;
						break;
					}
				}
				if(!trovata2)
					return false;
			}else
				break;
	/*
	///// ESCLUDE LE PAROLE CHE CONTENGONO LETTERE DELLA SCACCHIERA DA SPOSTARE
	lettere_temp = lettere_7;
	for(int pos_temp = 0; pos_temp < cercata.size(); pos_temp++){
		int a = 0;
		for(; a < lettere_temp.size(); a++)
			if(cercata.at(pos_temp) == lettere_temp.at(a)){
				lettere_temp.at(a) = '#';
				break;
			}

		if(a == lettere_temp.size()){
			if(pos_temp < posizione){
				posizione = pos_temp;
				for(pos_fissa = 0; pos_fissa < fissa.size(); pos_fissa++)
					if(fissa.at(pos_fissa) == cercata.at(posizione))
						if(pos_fissa > posizione || fissa.size() + (posizione - pos_fissa) > cercata.size())
							return false;
						else
							break;
			}
			if(pos_fissa + (pos_temp - posizione) >= fissa.size() || fissa.at(pos_fissa + (pos_temp - posizione)) != cercata.at(pos_temp))
				return false;
		}
	}
	*/
	
	///// ESCLUDE LE PAROLE CHE CONTENGONO LETTERE DELLA SCACCHIERA DA SPOSTARE
	lettere_temp = lettere_7;
	int h = 0;
	for(int pos_temp = 0; pos_temp < cercata.size(); pos_temp++){
		int a = 0;
		for(; a < lettere_temp.size(); a++)
			if(cercata.at(pos_temp) == lettere_temp.at(a)){
			   if(pos_temp != posizione)
					lettere_temp.at(a) = '#';
				break;
			}
		if(pos_temp <= posizione)
			continue;

		if(a == lettere_temp.size()){

			int vecchio_pos_temp = pos_temp;
			for(; h < fissa.size(); h++){
				if(cercata.at(pos_temp) == fissa.at(h)){
					pos_temp = h + posizione - pos_fissa;
					h++;
					break;
				}
			}

			if(pos_fissa + (pos_temp - posizione) >= fissa.size() || fissa.at(pos_fissa + (pos_temp - posizione)) != cercata.at(pos_temp))
				return false;

		   pos_temp = vecchio_pos_temp;
		}
	}

	///// TROVO DIFFERENZA TRA LETTERE IN COMUNE
	differenza = pos_fissa - posizione;
	return true;

}



void suggerimentoTutti(suggerim &suggerendo, vector <tessera> tessere, vector <giocatore> giocatori, vector <string> &vocabolario){
	
	///// OTTENGO LE PAROLE VECCHIE E NUOVE
	vector <parola> vecchie =	identificaParole(tessere, vocabolario, 0);
	
	///// RICAVO LA MATRICE "SEMPLIFICATA" DELLA SCACCHIERA
	//vector <vector <char>> scacchiera = ricavaMatrice(tessere);
	
	///// RICAVO IL VETTORE DI LETTERE USATE SULLA SCACCHIERA
	vector <char> lettere_scacchiera = ricavaVettore(tessere);

	///// ISOLO LE LETTERE DEL GIOCATORE
	vector <char> lettere_7;
	for(int g = 0; g < giocatori.size(); g++)
		if(giocatori.at(g).turno == 1)
			for(int t = 0; t < tessere.size(); t++)
				if(tessere.at(t).posizionata == POS_GIOCATORE && tessere.at(t).giocatore == g)
					lettere_7.push_back( tolower(tessere.at(t).lettera) );
	
	/////////////////////////////////////
	///// CONTROLLO PAROLE "SOVRAPPOSTE"
	/////////////////////////////////////
	
	///// SE LA PAROLA DA COMPORRE E' LA PRIMA
	if(vecchie.size() <= 0){
			
		///// ISOLO LE PAROLE FATTIBILI DAL VOCABOLARIO (IN GENERALE)
		vector <string> vocabolario_nuovo;
		for(int v = 0; v < vocabolario.size(); v++){
			
			suggerendo.percentuale = ( (float)v / (float)vocabolario.size() )*100;
			
			bool aggiungi = true;
			vector <char> lettere_nuove = lettere_7;
			if(aggiungi)
				for(int lv = 0; lv < vocabolario.at(v).size(); lv++){
					bool trovata = false;
					for(int l = 0; l < lettere_nuove.size(); l++){
						if(vocabolario.at(v).at(lv) == lettere_nuove.at(l)){
							lettere_nuove.at(l) = '#';
							trovata = true;
						}
					}
					if(!trovata)
						aggiungi = false;
				}
			if(aggiungi)
				if(vocabolario.at(v).size() >= 3){
					///// CREO STRINGA PAROLE
					string p = vocabolario.at(v);
					///// CREO STRINGA LETTERE
					string l = "";
					for(int i = 0; i < vocabolario.at(v).size(); i++)
						if(i == 0)
							l = "" + string(1, toupper( vocabolario.at(v).at(i) ));
						else
							l += ", " + string(1, toupper( vocabolario.at(v).at(i) ));
					///// CALCOLO PUNTI
					int punti = vocabolario.at(v).size()*2;
					if(vocabolario.at(v).find("q") != std::string::npos)
						punti += 2;
					if(vocabolario.at(v).size() >= 7)
						punti += 20;
					///// AGGIUNGO AL VETTORE
					suggerimenti.push_back({p, l, punti, tessere});
					///// RIORDINO IL VETTORE
					sort( suggerimenti.begin(), suggerimenti.end(), []( sugg a, sugg b ){ return a.punti > b.punti; });
					
				}
				
		}
		
	}else{
		///// ALTRIMENTI
		
		///// OTTENGO LE PAROLE VECCHIE (AL FINE DI VELOCIZZARE I CICLI SUCCESSIVI)
		vector <parola> vecchie =	identificaParole(tessere, vocabolario, 0);
		
		///// ISOLO LE PAROLE FATTIBILI INCROCIANDO PAROLA CORRENTE E LETTERE RASTRELLIERA
		for(int p = 0; p < vecchie.size(); p++){
			
			vector <char> lettere = lettere_7;
			for(int pl = 0; pl < vecchie.at(p).parola.size(); pl++)
				lettere.push_back(vecchie.at(p).parola.at(pl));
				
			for(int v = 0; v < vocabolario.size(); v++){
				suggerendo.percentuale = ( ( (float)p / (float)vecchie.size() )*100 + ( ( (float)v / (float)vocabolario.size() )*100 ) / (float)vecchie.size() )/2;
				
				bool aggiungi = true;
				vector <char> lettere_nuove = lettere;
				if(aggiungi)
					for(int lv = 0; lv < vocabolario.at(v).size(); lv++){
						bool trovata = false;
						for(int l = 0; l < lettere_nuove.size(); l++){
							if(vocabolario.at(v).at(lv) == lettere_nuove.at(l)){
								lettere_nuove.at(l) = '#';
								trovata = true;
								break;
							}
						}
						if(!trovata)
							aggiungi = false;
					}
				
				
				///// SE LA COMBINAZIONE E' VALIDA E SE E' PIU' LUNGA O UGUALE DI QUELLA FISSA
				if(aggiungi && vocabolario.at(v) != vecchie.at(p).parola && vocabolario.at(v).size() >= vecchie.at(p).parola.size()){
					
				
					///// CONTROLLO L'EFFETTIVA FATTIBILITA' DELLA "COMBINAZIONE"
					int differenza = 0;
					if(!parolaFattibile(vecchie.at(p).parola, vocabolario.at(v), lettere_7, differenza) ) continue;
					
					///// VERIFICO CHE LA PAROLA NON FUORIESCA DALLA SCACCHIERA
					if(vecchie.at(p).direzione == ORIZZONTALE){
						if(vecchie.at(p).pos.x + differenza + (vocabolario.at(v).size() - 1) > 9) continue;
						if(vecchie.at(p).pos.x + differenza < 0) continue;
					}else{
						if(vecchie.at(p).pos.y - differenza - (vocabolario.at(v).size() - 1) < 0) continue;
						if(vecchie.at(p).pos.y - differenza > 9) continue;
					}
					
					
					
					///// CREO IL VETTORE DI TESSERE TEMPORANEO
					vector <tessera> tessere_temp = tessere;
					
					///// POSIZIONO LA PAROLA SUGGERITA SULLA SCACCHIERA PER TESTARLA
					for(int lt = 0; lt < vocabolario.at(v).size(); lt++){
						int x = 0, y = 0, z = -1;
						if(vecchie.at(p).direzione == ORIZZONTALE){
							x = vecchie.at(p).pos.x + differenza + lt;
							y = vecchie.at(p).pos.y;
						}else{
							x = vecchie.at(p).pos.x;
							y = vecchie.at(p).pos.y - differenza - lt;
						}
						
						///// SE GIA' E' PRESENTE UNA LETTERA UGUALE
						///// CALCOLO ALTEZZA ULTIMA TESSERA
						for(int zpos = 0; zpos < 5; zpos++)
							for(int g = 0; g < giocatori.size(); g++)
								if(giocatori.at(g).turno == 1)
									for(int ts = 0; ts < tessere_temp.size(); ts++)
										if(tessere_temp.at(ts).posizionata == POS_SCACC && tessere_temp.at(ts).xpos == x && tessere_temp.at(ts).ypos == y && tessere_temp.at(ts).zpos == zpos){
											z = zpos;
										}
						///// SE LA LETTERA DELL'ULTIMA TESSERA E' UGUALE ALLA LETTERA DA POSIZIONARE
						bool ce = false;
						for(int g = 0; g < giocatori.size(); g++)
							if(giocatori.at(g).turno == 1)
								for(int ts = 0; ts < tessere_temp.size(); ts++)
									if(tessere_temp.at(ts).posizionata == POS_SCACC && tessere_temp.at(ts).xpos == x && tessere_temp.at(ts).ypos == y && tessere_temp.at(ts).zpos == z){
										if(tessere_temp.at(ts).lettera == toupper( vocabolario.at(v).at(lt) ))
											ce = true;
									}
						
						///// SE UNA DELLE LETTERE SUPERA IL LIMITE D'ALTEZZA
						if(z >= 4 && !ce) continue;						
						
						///// SE NON E' PRESENTE SPOSTO LA TESSERA DALLA RASTRELLIERA ALLA SCACCHIERA
						if(!ce){
							bool messa = false;
							for(int g = 0; g < giocatori.size(); g++)
								if(giocatori.at(g).turno == 1)
									for(int ts = 0; ts < tessere_temp.size(); ts++)
										if(tessere_temp.at(ts).posizionata == POS_GIOCATORE && tessere_temp.at(ts).giocatore == g)
											if(tessere_temp.at(ts).lettera == toupper( vocabolario.at(v).at(lt) )){
												tessere_temp.at(ts).xpos = x;
												tessere_temp.at(ts).ypos = y;
												tessere_temp.at(ts).zpos = z + 1;
												tessere_temp.at(ts).posizionata = POS_SCACC_MOB;
												messa = true;
												break;
											}
							if(!messa) continue;
						}
						
					}
							
					///// SE NEL FRATTEMPO E' STATA INTERROTTA L'ELABORAZIONE
					if(!suggerendo.vero){
						suggerendo.percentuale = 0;
						return;
					}
					
					suggerimenti.push_back({});
					
					thread vv(vagliaParoleSuggerimento, suggerimenti.size()-1, tessere_temp, ref(vocabolario), vecchie);
					vv.detach();

				}
			}
		}
	}
	
	
	Sleep(2000);
	///// RIORDINO IL VETTORE
	sort( suggerimenti.begin(), suggerimenti.end(), []( sugg a, sugg b ){ return a.punti > b.punti; });
	///// ELIMINO DOPPIONI & VUOTI
	{
		vector <sugg> suggerimenti_temp;
		for(int s = 0; s < suggerimenti.size(); s++){
			bool aggiungi = true;
			for(int i = 0; i < suggerimenti_temp.size(); i++)
				if(suggerimenti.at(s).lettera == suggerimenti_temp.at(i).lettera && suggerimenti.at(s).parola == suggerimenti_temp.at(i).parola && suggerimenti.at(s).punti == suggerimenti_temp.at(i).punti){
					aggiungi = false;
					break;
				}
			if(suggerimenti.at(s).punti == 0)
				aggiungi = false;
			if(aggiungi) suggerimenti_temp.push_back(suggerimenti.at(s));	
		}
		suggerimenti = suggerimenti_temp;
	}
	
	
	////////////////////////////////////////
	///// CONTROLLO PAROLE "PERPENDICOLARI"
	////////////////////////////////////////
	
	
	///// AGISCO SOLO SE ESISTONO PAROLE
	if(vecchie.size() > 0){
		
		///// OTTENGO LE PAROLE VECCHIE (AL FINE DI VELOCIZZARE I CICLI SUCCESSIVI)
		vector <parola> vecchie =	identificaParole(tessere, vocabolario, 0);
		
		///// ISOLO LE PAROLE FATTIBILI INCROCIANDO PAROLA CORRENTE E LETTERE RASTRELLIERA
		for(int p = 0; p < vecchie.size(); p++){
			
			///// PER OGNI LETTERA DI OGNI PAROLA PRESENTE SULLA SCACCHIERA
			for(int let = 0; let < vecchie.at(p).parola.size(); let++){
				
				vector <char> lettere = lettere_7;
					lettere.push_back(vecchie.at(p).parola.at(let));
					
				for(int v = 0; v < vocabolario.size(); v++){
					suggerendo.percentuale = ( ( (float)p / (float)vecchie.size() )*100 + ( ( (float)let / (float)vecchie.at(p).parola.size() )*100 ) / (float)vecchie.size() + ( ( (float)v / (float)vocabolario.size() )*100 ) / ( (float)vecchie.size()*vecchie.at(p).parola.size() ) )/2 + 50;
					
					bool aggiungi = true;
					vector <char> lettere_nuove = lettere;
					if(aggiungi)
						for(int lv = 0; lv < vocabolario.at(v).size(); lv++){
							bool trovata = false;
							for(int l = 0; l < lettere_nuove.size(); l++){
								if(vocabolario.at(v).at(lv) == lettere_nuove.at(l)){
									lettere_nuove.at(l) = '#';
									trovata = true;
									break;
								}
							}
							if(!trovata)
								aggiungi = false;
						}
					
					///// SE LA COMBINAZIONE E' VALIDA E SE E' PIU' LUNGA O UGUALE DI QUELLA FISSA
					if(aggiungi && vocabolario.at(v).size() >= 3){
						
						///// VERIFICO SE LA PAROLA SI POSSA FORMARE IN PIU' MODI E ESCLUDO LE NON FORMABILI
						for(int vv = 0; vv < vocabolario.at(v).size(); vv++) if(vocabolario.at(v).at(vv) == vecchie.at(p).parola.at(let)){
							
							///// VERIFICO CHE LA PAROLA NON FUORIESCA DALLA SCACCHIERA
							if(vecchie.at(p).direzione == ORIZZONTALE){
								if(vecchie.at(p).pos.y + vv > 9) continue;
								if(vecchie.at(p).pos.y + vv - (vocabolario.at(v).size() - 1) < 0) continue;
								
							}else{
								if(vecchie.at(p).pos.x - vv < 0) continue;
								if(vecchie.at(p).pos.x - vv + (vocabolario.at(v).size() - 1) > 9) continue;
							}
							
							///// CREO IL VETTORE DI TESSERE TEMPORANEO
							vector <tessera> tessere_temp = tessere;
							
							///// POSIZIONO LA PAROLA SUGGERITA SULLA SCACCHIERA PER TESTARLA
							for(int lt = 0; lt < vocabolario.at(v).size(); lt++){
								int x = 0, y = 0, z = -1;
								if(vecchie.at(p).direzione == ORIZZONTALE){
									x = vecchie.at(p).pos.x + let;
									y = vecchie.at(p).pos.y + vv - lt;
								}else{
									x = vecchie.at(p).pos.x - vv + lt;
									y = vecchie.at(p).pos.y - let;
								}
								
								///// SE GIA' E' PRESENTE UNA LETTERA UGUALE
								///// CALCOLO ALTEZZA ULTIMA TESSERA
								for(int zpos = 0; zpos < 5; zpos++)
									for(int g = 0; g < giocatori.size(); g++)
										if(giocatori.at(g).turno == 1)
											for(int ts = 0; ts < tessere_temp.size(); ts++)
												if(tessere_temp.at(ts).posizionata == POS_SCACC && tessere_temp.at(ts).xpos == x && tessere_temp.at(ts).ypos == y && tessere_temp.at(ts).zpos == zpos){
													z = zpos;
												}
								///// SE LA LETTERA DELL'ULTIMA TESSERA E' UGUALE ALLA LETTERA DA POSIZIONARE
								bool ce = false;
								for(int g = 0; g < giocatori.size(); g++)
									if(giocatori.at(g).turno == 1)
										for(int ts = 0; ts < tessere_temp.size(); ts++)
											if(tessere_temp.at(ts).posizionata == POS_SCACC && tessere_temp.at(ts).xpos == x && tessere_temp.at(ts).ypos == y && tessere_temp.at(ts).zpos == z){
												if(tessere_temp.at(ts).lettera == toupper( vocabolario.at(v).at(lt) ))
													ce = true;
											}
								
								///// SE UNA DELLE LETTERE SUPERA IL LIMITE D'ALTEZZA
								if(z >= 4 && !ce) continue;						
								
								///// SE NON E' PRESENTE SPOSTO LA TESSERA DALLA RASTRELLIERA ALLA SCACCHIERA
								if(!ce){
									bool messa = false;
									for(int g = 0; g < giocatori.size(); g++)
										if(giocatori.at(g).turno == 1)
											for(int ts = 0; ts < tessere_temp.size(); ts++)
												if(tessere_temp.at(ts).posizionata == POS_GIOCATORE && tessere_temp.at(ts).giocatore == g)
													if(tessere_temp.at(ts).lettera == toupper( vocabolario.at(v).at(lt) )){
														tessere_temp.at(ts).xpos = x;
														tessere_temp.at(ts).ypos = y;
														tessere_temp.at(ts).zpos = z + 1;
														tessere_temp.at(ts).posizionata = POS_SCACC_MOB;
														messa = true;
														break;
													}
									if(!messa) continue;
								}
								
							}
							
							///// SE NEL FRATTEMPO E' STATA INTERROTTA L'ELABORAZIONE
							if(!suggerendo.vero){
								suggerendo.percentuale = 0;
								return;
							}
							
							suggerimenti.push_back({});
					
							thread vv(vagliaParoleSuggerimento, suggerimenti.size()-1, tessere_temp, ref(vocabolario), vecchie);
							vv.detach();
							
						}
					}
				}
			}
		}
	}
	
	suggerendo.percentuale = 100;
	
	Sleep(2000);
	///// RIORDINO IL VETTORE
	sort( suggerimenti.begin(), suggerimenti.end(), []( sugg a, sugg b ){ return a.punti > b.punti; });
	///// ELIMINO DOPPIONI & VUOTI
	{
		vector <sugg> suggerimenti_temp;
		for(int s = 0; s < suggerimenti.size(); s++){
			bool aggiungi = true;
			for(int i = 0; i < suggerimenti_temp.size(); i++)
				if(suggerimenti.at(s).lettera == suggerimenti_temp.at(i).lettera && suggerimenti.at(s).parola == suggerimenti_temp.at(i).parola && suggerimenti.at(s).punti == suggerimenti_temp.at(i).punti){
					aggiungi = false;
					break;
				}
			if(suggerimenti.at(s).punti == 0)
				aggiungi = false;
			if(aggiungi) suggerimenti_temp.push_back(suggerimenti.at(s));	
		}
		suggerimenti = suggerimenti_temp;
	}
	
	suggerendo.vero = false;
	suggerendo.percentuale = 0;

}


///// FUNZIONE CHIAMATA DAL MAIN
void mostraSuggerimento(suggerim &suggerendo, InfoBox infobox, vector <tessera> tessere, vector <giocatore> giocatori, vector <string> &vocabolario){
	
	tessere_back = tessere;
	
	if(!suggerendo.vero){
		
		suggerimenti.clear();
		suggerendo.vero = true;
		suggerendo.percentuale = 0;
		
		infoBox(infobox);
		
		///// CHIAMO THREAD NON BLOCCANTE CHE ASPETTA IL TEMPO DESIDERATO E AGISCE PER FINIRE IL TURNO
		//thread sugg = thread (suggerimentoSovrapposte, ref(suggerendo), ref(suggerimenti), tessere, giocatori, ref(vocabolario));
		thread sugg = thread (suggerimentoTutti, ref(suggerendo), tessere, giocatori, ref(vocabolario));
		sugg.detach();
	}else{
		
		infoBox(infobox);
		
	}
	
}



/*////////////////////////////////////////////////////////////////////////////////
//				FUNZIONE CHE CAMBIA IL NUMERO DI GIOCATORI						//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

string modListbx(string title, int operazione){
	
	///// TRASFORMO LA STRING "NUMERO GIOCATORI" IN UN INTERO
	int num = stoi(title);
	
	///// ESEGUO LE OPERAZIONI RICHIESTE
	if(operazione == SOMMA)
		if(num < 4) num++;
	if(operazione == SOTTRAZIONE)
		if(num > 2) num--;
		
	///// CONVERTO IN NUOVO INTERO IN UNA STRING
	string res = to_string(num);
	///// RITORNO LA NUOVA STRINGA
	return res;
	
}



/*////////////////////////////////////////////////////////////////////////////////
//				FUNZIONI CHE CARICANO IMMAGINI NELLA MEMORIA GRAFICA			//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

HBITMAP LoadImageFromResource(int rc, HINSTANCE hInst)
{
	///// CERCO ED ALLOCO IN MEMORIA GLI SFONDI
	HRSRC   hResInfo	= FindResource(hInst, MAKEINTRESOURCE(rc), RT_RCDATA);
	HGLOBAL hResGlobal	= LoadResource(hInst, hResInfo);
	DWORD   dwSize		= SizeofResource(hInst, hResInfo);
	HGLOBAL hgImage		= GlobalAlloc(GMEM_MOVEABLE, dwSize);
	CopyMemory(GlobalLock(hgImage), LockResource(hResGlobal), dwSize);
	GlobalUnlock(hgImage);
	
	///// CARICO LA ZONA DI MEMORIA ALLOCATA IN UNO STREAM
	IStream *isImage = NULL;
	CreateStreamOnHGlobal(hgImage, TRUE, &isImage);
	if(isImage == NULL){ GlobalFree(hgImage); return NULL; }
	
	///// TRASFORMO LO STREAM IN UNA STRUTTURA ADATTA A TRATTARE LE IMMAGINI
	IPicture* pImage = NULL;
	OleLoadPicture(isImage, dwSize, FALSE, IID_IPicture, (LPVOID *)&pImage);
	isImage->Release();
	if(pImage == NULL) return NULL;
	
	///// TRASFORMO L'IMMAGINE JPG IN UN HBITMAP, PIU' FACILE DA GESTIRE
	HBITMAP hImage = NULL;
	pImage->get_Handle((OLE_HANDLE *)&hImage);
	
	///// TRASFORMO ULTERIORMENTE L'HBITMAP
	HBITMAP hResult = (HBITMAP)CopyImage(hImage, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	pImage->Release();
	
	///// RITORNO L'HBITMAP
	return hResult;
}

int LoadBitmapTextureRC(int rc, int id, HINSTANCE hInst)
{
	///// DICHIARO L'HBITMAP
	HBITMAP hBmp = NULL;
	
	///// CARICO L'HBITMAP
	hBmp = (HBITMAP) LoadImageFromResource(rc, hInst);
	if(!hBmp) return 0;
		
	///// RICHIEDO LE INFORMAZIONI DALL'HBITMAP
	BITMAP BM;
	GetObject(hBmp, sizeof(BM), &BM);


	///// FORNISCO L'ID ALLA TEXTURE
	glBindTexture(GL_TEXTURE_2D, id);
	///// SPECIFICO ALL'OPENGL DI IGNORARE IL PADDING ALLA FINE DELLE COLONNE
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	
	///// PREPARO LE INFORMAZIONI PER L'OPENGL
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	///// FORNISCO L'HBITMAP ALL'OPENGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BM.bmWidth, BM.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BM.bmBits);
	
	///// LIBERO LA MEMORIA
	DeleteObject((HGDIOBJ) hBmp);  //avoid memory leak (Windows)
	
	///// RITORNO POSITIVO
	return 1;
}



/*////////////////////////////////////////////////////////////////////////////////
//					FUNZIONI CHE TROVANO PROCESSI IN ESECUZIONE					//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

///// STRUTTURA PER FAR COMUNICARE LE PROCEDURE
struct EnumData {
	DWORD dwProcessId;
	HWND hWnd;
};

// Application-defined callback for EnumWindows
BOOL CALLBACK EnumProc( HWND hWnd, LPARAM lParam ) {
	// Retrieve storage location for communication data
	EnumData& ed = *(EnumData*)lParam;
	DWORD dwProcessId = 0x0;
	// Query process ID for hWnd
	GetWindowThreadProcessId( hWnd, &dwProcessId );
	// Apply filter - if you want to implement additional restrictions,
	// this is the place to do so.
	if ( ed.dwProcessId == dwProcessId ) {
		// Found a window matching the process ID
		ed.hWnd = hWnd;
		// Report success
		SetLastError( ERROR_SUCCESS );
		// Stop enumeration
		return FALSE;
	}
	// Continue enumeration
	return TRUE;
}

HWND FindWindowFromProcessId( DWORD dwProcessId ) {
	EnumData ed = { dwProcessId };
	if ( !EnumWindows( EnumProc, (LPARAM)&ed ) &&
		 ( GetLastError() == ERROR_SUCCESS ) ) {
		return ed.hWnd;
	}
	return NULL;
}

int ProcessRunning( string name )
{
	
	int ver=0;
	
	HANDLE SnapShot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	
	if( SnapShot == INVALID_HANDLE_VALUE )
		return 0;
	
	PROCESSENTRY32 procEntry;
	procEntry.dwSize = sizeof( PROCESSENTRY32 );
	
	if( !Process32First( SnapShot, &procEntry ) )
		return 0;
	
	do
	{
		if( strcmp( procEntry.szExeFile, name.c_str() ) == 0 ){
			ver++;
			HWND wHandle = FindWindowFromProcessId( procEntry.th32ProcessID );
			ShowWindow(wHandle ,  SW_RESTORE);
		}
	}
	while( Process32Next( SnapShot, &procEntry ) );
	
	if(ver > 0) return ver;
	
	return 0;
}

HWND GetProcessRunningHWND( string name )
{
	
	HWND ret = 0;
	
	HANDLE SnapShot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	
	if( SnapShot == INVALID_HANDLE_VALUE )
		return 0;
	
	PROCESSENTRY32 procEntry;
	procEntry.dwSize = sizeof( PROCESSENTRY32 );
	
	if( !Process32First( SnapShot, &procEntry ) )
		return 0;
	
	do
	{
		if( strcmp( procEntry.szExeFile, name.c_str() ) == 0 ){
			ret = FindWindowFromProcessId( procEntry.th32ProcessID );
		}
	}
	while( Process32Next( SnapShot, &procEntry ) );
	
	return ret;
}



/*////////////////////////////////////////////////////////////////////////////////
//			FUNZIONI DI ACCOMODAMENTO E CONVERSIONE PIXEL E RISOLUZIONI			//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

float accomodaRisoluzione(int pixel){
	
	///// RITORNO IL VALORE DELL'ALTEZZA, ACCOMODATO IN BASE AL RAPPORTO DI LARGHEZZA ED ALTEZZA, NON CAMBIA NULLA IN CASO DI SCREEN RATIO 16:9
	return ( ((float)1600 / ((float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT))) );
	
}


float pixelToUnitX(int pixel){
	
	///// CONVERTO I PIXEL EFFETTIVI DELLO SCHERMO IN PIXEL VIRTUALI DELLA GRAFICA 2D (1600 x 900 IN CASO DI SCREEN RATIO 16:9)
	return ( ((float)pixel * 1600) / (float)glutGet(GLUT_WINDOW_WIDTH) );
	
}


float pixelToUnitY(int pixel){
	
	///// CONVERTO I PIXEL VIRTUALI DELLA GRAFICA 2D (1600 x 900 IN CASO DI SCREEN RATIO 16:9) IN PIXEL EFFETTIVI DELLO SCHERMO
	return ( ((float)pixel * accomodaRisoluzione(1600)) / (float)glutGet(GLUT_WINDOW_HEIGHT) );
	
}



/*////////////////////////////////////////////////////////////////////////////////
//					FUNZIONI CHE CARICANO IN MEMORIA FILES TXT					//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

void caricaVocabolario(vector <string> &vocabolario){
	
	///// STREAM DI STRINGHE PER EVITARE ALLOCAZIONI MANUALI
	stringstream f;
	
	///// TROVO LA RISORSA
	HRSRC hRes = FindResource(0, MAKEINTRESOURCE(IDI_VOCABOLARIO), RT_RCDATA);
	if(NULL != hRes)
	{
		///// PREPARO LA RISORSA
		HGLOBAL hData = LoadResource(0, hRes);
		if(NULL != hData)
		{
			///// RECUPERO LA DIMENSIONE DELLA RISORSA NE COPIO IL TESTO NELLO STRINGSTREAM
			DWORD dataSize = SizeofResource(0, hRes);
			f.str((char*)LockResource(hData));
		}
	}
	
	///// CONVERTO LO STRINGSTREAM IN UN VETTORE DI STRING
	string s;
	while(f){
		getline(f, s);
		if(s!=""){
			vocabolario.push_back(s.substr(0, s.size()-1));
		}
	}
	f.clear();
	
}



/*////////////////////////////////////////////////////////////////////////////////
//				FUNZIONE CHE RESTITUISCE LA CARTELLA %APPDATA%					//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

string getPath(int csidl) {
	
	///// RICHIEDO LA CARTELLA (CSIDL) E, NEL CASO L'OPERAZIONE VADA A BUON FINE, LA RESTITUISCO COME STRING
	char out[MAX_PATH];
	if (SHGetSpecialFolderPathA(NULL, out, csidl, 0))
		return out;
	else
		return "";
		
}



/*////////////////////////////////////////////////////////////////////////////////
//					FUNZIONE CHE CONVERTE IN NUMERO ROMANO						//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

string intRomano(int a){
	string ans;
	string M[] = {"","M","MM","MMM"};
	string C[] = {"","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"};
	string X[] = {"","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"};
	string I[] = {"","I","II","III","IV","V","VI","VII","VIII","IX"};
	ans = M[a/1000]+C[(a%1000)/100]+X[(a%100)/10]+I[(a%10)];
	return ans;
}



/*////////////////////////////////////////////////////////////////////////////////
//				FUNZIONI CHE CARICANO O LEGGONO PARTITE VECCHIE					//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

bool decriptaTessera(string riga, vector <tessera> &tessere){
	
	bool valido = true;
	tessera tessera_provv = {};
	
	///// DECRIPTO LA LINEA
	for(int s = 0; s < riga.size(); s++)
		riga.at(s) -= 127;
	
	///// CREO LO STRINGSTREAM
	stringstream mystream;
	mystream << riga;
	
	///// LEGGO OGNI RIGA DI "riga" DECRIPTATO
	string line = "";
	int count = 0;
	for (; mystream.good() && valido; count++){
		getline(mystream, line);
		///// AGGIUNGO L'ELEMENTO AL VETTORE
		if(count == 0) if(line == "") valido = false;
		else{
			tessera_provv.lettera = line.at(0);
		}else
		if(count == 1) if(line == "") valido = false;
		else{
			tessera_provv.posizionata = stoi(line);
		}else
		if(count == 2) if(line == "") valido = false;
		else{
			tessera_provv.giocatore = stoi(line);
		}else
		if(count == 3) if(line == "") valido = false;
		else{
			tessera_provv.pos = stoi(line);
		}else
		if(count == 4) if(line == "") valido = false;
		else{
			tessera_provv.xpos = stoi(line);
		}else
		if(count == 5) if(line == "") valido = false;
		else{
			tessera_provv.ypos = stoi(line);
		}else
		if(count == 6) if(line == "") valido = false;
		else{
			tessera_provv.zpos = stoi(line);
		}else
		if(count == 7) if(line == "") valido = false;
		else{
			tessera_provv.active = stoi(line);
		}else
		if(count == 8) if(line == "") valido = false;
		else{
			tessera_provv.selected = stoi(line);
		}else valido = false;
	}
	mystream.clear();
	
	if(count < 8) valido = false;
	
	///// SE OK SCRIVO NEL VETTORE
	if(valido) tessere.push_back(tessera_provv);
	
	///// RITORNO IL RESPONSO
	return valido;
}

bool decriptaGiocatore(string riga, vector <giocatore> &giocatori){
	
	bool valido = true;
	giocatore giocatore_provv = {};
	
	///// DECRIPTO LA LINEA
	for(int s = 0; s < riga.size(); s++)
		riga.at(s) -= 127;
	
	///// CREO LO STRINGSTREAM
	stringstream mystream;
	mystream << riga;
	
	///// LEGGO OGNI RIGA DI "riga" DECRIPTATO
	string line = "";
	int count = 0;
	for (; mystream.good() && valido; count++){
		getline(mystream, line);
		///// AGGIUNGO L'ELEMENTO AL VETTORE
		if(count == 0) if(line == "") valido = false;
		else{
			giocatore_provv.punti = stoi(line);
		}else
		if(count == 1) if(line == "") valido = false;
		else{
			giocatore_provv.nome = line;
		}else
		if(count == 2) if(line == "") valido = false;
		else{
			giocatore_provv.turno = stoi(line);
		}else
		if(count == 3) if(line == "") valido = false;
		else{
			giocatore_provv.numero_parole = stoi(line);
		}else
		if(count == 4) if(line == "") valido = false;
		else{
			giocatore_provv.numero_lettere = stoi(line);
		}else
		if(count == 5 || count == 7 || count == 9 || count == 11 || count == 13 || count == 15 || count == 17) if(line == "") valido = false;
		else{
			giocatore_provv.cell.push_back({});
			giocatore_provv.cell.at(giocatore_provv.cell.size()-1).active = stoi(line);
		}else
		if(count == 6 || count == 8 || count == 10 || count == 12 || count == 14 || count == 16 || count == 18) if(line == "") valido = false;
		else{
			giocatore_provv.cell.at(giocatore_provv.cell.size()-1).active = stoi(line);
		}else valido = false;
	}
	mystream.clear();
	
	if(count < 18) valido = false;
	
	///// SE OK SCRIVO NEL VETTORE
	if(valido) giocatori.push_back(giocatore_provv);
	
	///// RITORNO IL RESPONSO
	return valido;
}

bool leggi(string file, vector <tessera> &tessere, vector <giocatore> &giocatori){
	
	///// RESET VETTORI DA RIEMPIRE
	giocatori.clear();
	tessere.clear();
	
	bool valido = true;
	
	///// CICLO DI LETTURA DA FILE
	string line = "";
	int count = 0;
	ifstream myfile (file);
	if (myfile.is_open()){
		for (; myfile.good() && valido; count++){
			getline (myfile,line);
			///// VERIFICO SE IL FILE E' VALIDO
			if(count == 0) if(line != "# Partita Salvata UpWords") valido = false;
			if(count == 1) if(line != "# Non modificare in alcuno modo questo File") valido = false;
			///// SCRIVO LE 100 TESSERE
			if(count >= 2 && count < 102) if(line == "") valido = false;
			else{
				if(!decriptaTessera(line, tessere)) valido = false;
			}
			///// SCRIVO I PRIMI 2 GIOCATORI (OBBLIGATORI)
			if(count >= 102 && count < 104) if(line == "") valido = false;
			else{
				if(!decriptaGiocatore(line, giocatori)) valido = false;
			}
			///// SE CI SONO SCRIVO GLI ALTRI
			if(count >= 104 && count < 106) if(line == "") ;
			else{
				if(!decriptaGiocatore(line, giocatori)) valido = false;
			}
		}
	}else valido = false;
	myfile.close();
	
	if(count < 104) valido = false;
	
	return valido;
}

bool sePartitaSalvata(string file){
	
	///// CREO VETTORI DA RIEMPIRE
	vector <tessera> tessere;
	vector <giocatore> giocatori;
	
	bool valido = true;
	
	///// CICLO DI LETTURA DA FILE
	string line = "";
	int count = 0;
	ifstream myfile (file);
	if (myfile.is_open()){
		for (; myfile.good() && valido; count++){
			getline (myfile,line);
			///// VERIFICO SE IL FILE E' VALIDO
			if(count == 0) if(line != "# Partita Salvata UpWords") valido = false;
			if(count == 1) if(line != "# Non modificare in alcuno modo questo File") valido = false;
			///// SCRIVO LE 100 TESSERE
			if(count >= 2 && count < 102) if(line == "") valido = false;
			else{
				if(!decriptaTessera(line, tessere)) valido = false;
			}
			///// SCRIVO I PRIMI 2 GIOCATORI (OBBLIGATORI)
			if(count >= 102 && count < 104) if(line == "") valido = false;
			else{
				if(!decriptaGiocatore(line, giocatori)) valido = false;
			}
			///// SE CI SONO SCRIVO GLI ALTRI
			if(count >= 104 && count < 106) if(line == "") ;
			else{
				if(!decriptaGiocatore(line, giocatori)) valido = false;
			}
		}
	}else valido = false;
	myfile.close();
	
	if(count < 104) valido = false;
	
	return valido;
}

string cripta(string testo){
	
	///// CICLO DI CRIPTATURA
	for(int s = 0; s < testo.size(); s++)
		testo.at(s) += 127;
	
	return testo;
}

void scrivi(string file, vector <tessera> tessere, vector <giocatore> giocatori){
	
	///// CICLO DI SCRITTORA SU FILE
	ofstream out(file, ios::trunc);
	out << "# Partita Salvata UpWords" << endl;
	out << "# Non modificare in alcuno modo questo File" << endl;
	out.close();
	
	for(int s = 0; s < 100; s++){
		string tess = "";
		
		tess =	string(1, tessere.at(s).lettera) + "\n" +
				to_string(tessere.at(s).posizionata) + "\n" +
				to_string(tessere.at(s).giocatore) + "\n" +
				to_string(tessere.at(s).pos) + "\n" +
				to_string(tessere.at(s).xpos) + "\n" +
				to_string(tessere.at(s).ypos) + "\n" +
				to_string(tessere.at(s).zpos) + "\n" +
				to_string(tessere.at(s).active) + "\n" +
				to_string(tessere.at(s).selected);
		
		ofstream out(file, ios::app);
		out << cripta(tess) << endl;
		out.close();
	}
	
	for(int g = 0; g < giocatori.size(); g++){
		string gioc = "";
		
		gioc =	to_string(giocatori.at(g).punti) + "\n" +
				giocatori.at(g).nome + "\n" +
				to_string(giocatori.at(g).turno) + "\n" +
				to_string(giocatori.at(g).numero_parole) + "\n" +
				to_string(giocatori.at(g).numero_lettere) + "\n" +
				to_string(giocatori.at(g).cell.at(0).active) + "\n" +
				to_string(giocatori.at(g).cell.at(0).selected) + "\n" +
				to_string(giocatori.at(g).cell.at(1).active) + "\n" +
				to_string(giocatori.at(g).cell.at(1).selected) + "\n" +
				to_string(giocatori.at(g).cell.at(2).active) + "\n" +
				to_string(giocatori.at(g).cell.at(2).selected) + "\n" +
				to_string(giocatori.at(g).cell.at(3).active) + "\n" +
				to_string(giocatori.at(g).cell.at(3).selected) + "\n" +
				to_string(giocatori.at(g).cell.at(4).active) + "\n" +
				to_string(giocatori.at(g).cell.at(4).selected) + "\n" +
				to_string(giocatori.at(g).cell.at(5).active) + "\n" +
				to_string(giocatori.at(g).cell.at(5).selected) + "\n" +
				to_string(giocatori.at(g).cell.at(6).active) + "\n" +
				to_string(giocatori.at(g).cell.at(6).selected);
		
		ofstream out(file, ios::app);
		out << cripta(gioc) << endl;
		out.close();
	}
	
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



