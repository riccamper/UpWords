


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

///// ICONA DEL PROGRAMMA
#define			IDI_MAIN		0				// ID ICONA PRINCIPALE DEL GIOCO (PER RESOURCES E IDENTIFICAZIONE)

///// COSTANTI PER IDENTIFICARE LE ATTESE
#define			ATT_COMPLETA	0				// E' PREVISTA UN'ELABORAZIONE COMPLESSA, QUINDI SONO BLOCCATI INPUT E RENDERING (ES. DURANTE L'INIZIALIZZAZIONE)
#define			ATT_SEMPLICE	1				// E' PREVISTA UN'ATTESA SEMPLICE, GLI INPUT SONO BLOCCATI MA FINESTRE ED ELEMENTI SONO VISIBILI
#define			ATT_INFO		2				// E' PREVISTA UNA MESSAGEBOX A CHIUSURA AUTOMATICA, GLI INPUT SONO BLOCCATI MA FINESTRE ED ELEMENTI SONO VISIBILI
#define			ATT_NO			3				// NON E' PREVISTA UN'ATTESA, QUINDI LA FINESTRA DI ATTESA E' NASCOSTA

///// COSTANTI IDENTIFICAZIONE FINESTRE
#define			FIN_USCITA		0				// ID FINESTRA CONFERMA USCITA (SECONDO LA STRUTTURA DEVE ESSERE L'ULTIMA)
#define			FIN_BENVENUTO	1				// ID FINESTRA DI BENVENUTO (E' LA PRIMA AD ESSERE MOSTRATA)
#define			FIN_ISTRUZIONI1	2				// ID FINESTRA ISTRUZIONI #1
#define			FIN_ISTRUZIONI2	3				// ID FINESTRA ISTRUZIONI #1
#define			FIN_NUMERO		4				// ID FINESTRA SCELTA NUMERO E NOME GIOCATORI
#define			FIN_PARTITA		5				// ID FINESTRA VISIBILE DURANTE IL GIOCO
#define			FIN_PAUSA		6				// ID FINESTRA DI PAUSA DEL GIOCO
#define			FIN_SUGG		7				// ID FINESTRA PER MOSTRARE UN SUGGERIMENTO DURANTE IL GIOCO
#define			FIN_TERMINE		8				// ID FINESTRA DI TERMINE GIOCO
#define			CHIUSURA		-2				// ID PER USCIRE DAL GIOCO

///// TEXTURES DI SFONDO TITOLO
#define			NUMERO_WIND		3				// NUMERO TEXTURES PER BARRA DEL TITOLO (PER RESOURCES E IDENTIFICAZIONE)

#define			IDI_WIND1		1
#define			IDI_WIND2		2
#define			IDI_WIND3		3

///// TEXTURES DI SFONDO FINESTRA
#define			NUMERO_BACK		10				// NUMERO TEXTURES PER SFONDO FINESTRE (PER RESOURCES E IDENTIFICAZIONE)

#define			IDI_BACK1		4
#define			IDI_BACK2		5
#define			IDI_BACK3		6
#define			IDI_BACK4		7
#define			IDI_BACK5		8
#define			IDI_BACK6		9
#define			IDI_BACK7		10
#define			IDI_BACK8		11
#define			IDI_BACK9		12
#define			IDI_BACK10		13

///// TEXTURES DI SFONDO FINESTRA
#define			NUMERO_ATT		1				// NUMERO TEXTURES PER SFONDO FINESTRE DI ATTESA, DA CARICARE INDISPENSABILMENTE (PER RESOURCES E IDENTIFICAZIONE)

#define			IDI_ATT1		14

///// TEXTURES DI SFONDO FINESTRA
#define			NUMERO_TEX		6				// NUMERO TEXTURES PER COLORAZIONE SCACCHIERA, RASTRELLIERE E TESSERE (PER RESOURCES E IDENTIFICAZIONE)

#define			IDI_TEX1		15
#define			IDI_TEX2		16
#define			IDI_TEX3		17
#define			IDI_TEX4		18
#define			IDI_TEX5		19
#define			IDI_TEX6		20

///// VOCABOLARIO
#define			IDI_VOCABOLARIO	21				// ID VOLCABOLARIO (PER RESOURCES E IDENTIFICAZIONE)

///// SUONI WAV
#define			NUMERO_WAV		2				// NUMERO SUONI .WAV (PER RESOURCES E IDENTIFICAZIONE)

#define			IDI_WAV1		22
#define			IDI_WAV2		23

///// COSTANTI ELEMENTI
#define			BUTTON			0				// OGGETTO "BOTTONE", CLICCABILE, COLORABILE, CON LINK
#define			TBITMA			1				// OGGETTO TESTO SEMPLCE, COLORABILE
#define			TSTROK			2				// OGGETTO TESTO 3D, SUPPORTA ANCHE LA ROTAZIONE
#define			LISTBX			3				// OGGETTO LISTBOX NUMERICA, CON FRECCIE PER INCREMENTARE O DECREMENTARE IL NUMERO
#define			TEXTBX			4				// CAMPO DI TESTO SCRIVIBILE
#define			LINEA			5				// LINEA DECORATIVA

///// COSTANTI OPERAZIONI
#define			SOMMA			0				// OPERAZIONE SOMMA OGGETTO "LISTBX"
#define			SOTTRAZIONE		1				// OPERAZIONE SOMMA OGGETTO "LISTBX"

///// COSTANTI PER IDENTIFICAZIONE OGGETTI 3D (GLUT STENCIL)
#define			CELLE			10				// ID IDENTIFICAZIONE CELLE SCACCHIERA					(10	 ~ 109)
#define			TESSERE			110				// ID IDENTIFICAZIONE TESSERE							(110 ~ 209)
#define			RASTR_1			210				// ID IDENTIFICAZIONE CELLE RASTRELLIERA GIOCATORE #1	(210 ~ 216)
#define			RASTR_2			210+7			// ID IDENTIFICAZIONE CELLE RASTRELLIERA GIOCATORE #2	(217 ~ 223)
#define			RASTR_3			210+7+7			// ID IDENTIFICAZIONE CELLE RASTRELLIERA GIOCATORE #3	(224 ~ 230)
#define			RASTR_4			210+7+7+7		// ID IDENTIFICAZIONE CELLE RASTRELLIERA GIOCATORE #4	(231 ~ 237)

///// COSTANTI IDENTIFICAZIONE POSIZIONI TESSERE
#define			POS_NULLA		0				// ID TESSERA ANCORA DA PESCARE (NEL "MUCCHIO")
#define			POS_GIOCATORE	1				// ID TESSERA ASSEGNATA AD UN GIOCATORE (PREVISTO ANCHE IL NUMERO DI GIOCATORE E LA POSIZIONE NELLA RASTRELLIERA)
#define			POS_SCACC		2				// ID TESSERA NELLA SCACCHIERA, DEFINITIVAMENTE (PREVISTE LE COORD X, Y, Z DELLA TESSERA NELLA SCACCHIERA)
#define			POS_SCACC_MOB	3				// ID TESSERA NELLA SCACCHIERA, MA NON DEFINITIVAMENTE (PREVISTE LE COORD X, Y, Z DELLA TESSERA NELLA SCACCHIERA)

///// COSTANTI IDENTIFICAZIONE DIREZIONE (PER ESEMPIO DI UNA PAROLA)
#define			ORIZZONTALE		0
#define			VERTICALE		1
#define			INDEFINITO		2

///// COSTANTI GRAFICHE
#define			MAX_TRIANGLES	500
#define			MAX_MULTISAMPLE	6

///// COSTANTI ERRORI
#define			ERR_NO				0
#define			ERR_PILA_COMPLETA	1
#define			ERR_LETTERA_UGUALE	2
#define			ERR_TESSERA_SOTTO	3
#define			ERR_CELLA_UGUALE	4
#define			ERR_TESS_GIA_MOBILE	5
#define			ERR_CELL_RASTR_OCC	6
#define			ERR_PAROLA_NON_ESI	7
#define			ERR_PAROLA_CORTA	8
#define			ERR_PAROLA_INCOMPL	9
#define			ERR_PAROLE_ISOLATE	10
#define			ERR_CELLE_CENTRALI	11
#define			ERR_TESSERE_DIREZI	12
#define			ERR_PAROLA_COPERTA	13

using namespace std;
 
 

/*////////////////////////////////////////////////////////////////////////////////
//								DEFINIZIONI STRUCT								//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

	///// STRUTTURE TRIANGOLI IN BACKGROUND
	struct coord{
		float x;	// COORDINATA X DI UN OGGETTO
		float y;	// COORDINATA Y DI UN OGGETTO
		float z;	// COORDINATA Z DI UN OGGETTO
	};
	
	struct dir{
		float x;	// DIREZIONE X DI UN OGGETTO
		float y;	// DIREZIONE Y DI UN OGGETTO
		float z;	// DIREZIONE Z DI UN OGGETTO
	};
	
	struct rot{
		float x;	// ROTAZIONE X DI UN OGGETTO
		float y;	// ROTAZIONE Y DI UN OGGETTO
		float z;	// ROTAZIONE Z DI UN OGGETTO
		float vel;	// VELOCITA' ROTAZIONE DI UN OGGETTO
	};
	
	struct color{
		float r;	// COLORE ROSSO (RGBA) DI UN OGGETTO
		float g;	// COLORE VERDE (RGBA) DI UN OGGETTO
		float b;	// COLORE BLU (RGBA) DI UN OGGETTO
		float a;	// TRASPARENZA (RGBA) DI UN OGGETTO
	};
	
	struct triangles{
		coord cordinata;		// STRUTTURA COORDINATE PIRAMIDE "COORD", DOVE SI TROVA
		coord posizione;		// STRUTTURA COORDINATE PIRAMIDE "COORD", DOVE SI TROVA INIZIALMENTE
		rot rotazione;			// STRUTTURA ROTAZIONE PIRAMIDE "ROT", QUANTO DEVE ROTARE
		dir direzione;			// STRUTTURA DIREZIONE PIRAMIDE "DIR", DOVE ANDRA'
		color colore;			// STRUTTURA COLORE PIRAMIDE "COLOR"
	};
	
	///// STRUTTURE DISEGNO FINESTRE
	struct oggetto{
		coord top;				// STRUTTURA PER LE COORDINATE POSITIVE (SOLO X, Y) OGGETTO
		coord bot;				// STRUTTURA PER LE COORDINATE NEGATIVE (SOLO X, Y) OGGETTO
		rot rotazione;			// STRUTTURA PER LA ROTAZIONE OGGETTO
		color colore;			// STRUTTURA PER IL COLORE PRINCIPALE OGGETTO
		void* font;				// VARIABILE FONT (GLUT FONTS)
		int tipo;				// TIPO DELL'OGGETTO (BUTTON, TBITMA, TSTROK, LISTBX, TEXTBX, ECC..)
		string testo;			// TESTO DELL'OGGETTO
		int active;				// SE L'OGGETTO E' ATTIVO (IL MOUSE SOPRA)
		int target;				// ID FINESTRA A CUI "LINKA" L'OGGETTO
		int hidden;				// SE L'OGGETTO DEVE ESSERE NASCOSTO
	};

	struct finestra{
		coord top;				// STRUTTURA PER LE COORDINATE POSITIVE (SOLO X, Y)
		coord bot;				// STRUTTURA PER LE COORDINATE NEGATIVE (SOLO X, Y)
		string titolo;			// TITOLO DELLA FINESTRA
		vector <oggetto> ogg;	// VETTORE DI STRUTTURE "OGGETTO" PER GLI OGGETTI DI OGNI FINESTRA (BOTTONI, SCRITTE, ECC..)
		int xactive;			// SE IL BOTTONE "X" DI CHIUSURA E' ATTIVO (IL MOUSE SOPRA)
		int factive;			// SE IL BOTTONE DEL FULLSCREEN E' ATTIVO (IL MOUSE SOPRA)
		float posx;				// VARIABILE PER "ANIMARE" LA FINESTRA
		int tipo;				// RISERVATO
		bool buttons;			// SE LA FINESTRA HA O NO I BOTTONI "X" E FULLSCREEN
		int child;				// ID DELLA FINESTRA "PADRE"
		int wind;				// ID DELLA TEXTURE DI SFONDO DELLA BARRA IN ALTO
		int sfondo;				// ID DELLA TESTURE DI SFONDO
	};
	
	///// STRUTTURE DISEGNO SCACCHIERA	
	struct cella{
		int active;				// SE LA CELLA E' ATTIVA (IL MOUSE SOPRA)
		int selected;			// SE LA CELLA E' SELEZIONATA
	};
	
	struct scacchiera{
		vector <cella> cell;	// VETTORE DI STRUTTURE DI "CELLA" PER LA SCACCHIERA (10x10)
		int visible;			// SE LA SCACCHIERA E' VISIBILE
		int active;				// SE LA SCACCHIERA E' CLICCABILE
		float posx;				// VARIABILE PER "ANIMARE" LA SCACCHIERA
		float posxx;				// VARIABILE PER "ANIMARE" LA SCACCHIERA
	};
	
	struct tessera{
		char lettera;			// LETTERA
		int posizionata;		// POSIZIONE DELLA TESSERA (GIOCATORE, SCACCHIERA, NULLA, ECC..)
		int giocatore;			// GIOCATORE A CUI E' ASSEGNATA LA TESSERA (SOLO SE E' SULLA RASTRELLIERA)
		int pos;				// POSIZIONE DELLA TESSERA (SOLO SE E' SULLA RASTRELLIERA, DA 0 A 6)
		int xpos;				// POSIZIONE X DELLA TESSERA (SOLO SE E' SULLA SCACCHIERA)
		int ypos;				// POSIZIONE Y DELLA TESSERA (SOLO SE E' SULLA SCACCHIERA)
		int zpos;				// POSIZIONE Z DELLA TESSERA (SOLO SE E' SULLA SCACCHIERA)
		int active;				// SE LA TESSERA E' ATTIVA (IL MOUSE E' SOPRA)
		int selected;			// SE LA TESSERA E' SELEZIONATA
	};
	
///// STRUTTURE DI GIOCO
	struct giocatore{
		int punti;				// PUNTI ASSEGNATI AL GIOCATORE
		string nome;			// NOME ASSEGNATO AL GIOCATORE
		int turno;				// TURNO (0 SE NON E' IL SUO, UNO VICEVERSA)
		int numero_parole;		// NUMERO DELLE PAROLE GIOCATE DAL GIOCATORE IN TUTTA LA PARTITA
		int numero_lettere;	// NUMERO DI LETTERE UTILIZZATE DAL GIOCATORE
		vector <cella> cell;	// VETTORE DI STRUTTURE DI "CELLA" PER LA RASTRELLIERA (7)
	};
	
	struct parola{
		string parola;
		coord pos;				// STRUTTURA PER LE COORDINATE (SOLO X, Y) PAROLA
		int direzione;			// DIREZIONE DELLA PAROLA (ES: ORIZZ. O VERT.)
		bool verificata;		// SE LA PAROLA ESISTE NEL VOCABOLARIO
	};
	
	struct sugg{
		string parola;
		string lettera;
		int punti;
		vector <tessera> tess;
	};
	
	struct suggerim{
		bool vero;
		int percentuale;
	};
	
///// STRUTTURA PER FUNZIONE INFOBOX
	struct InfoBox{
		vector <finestra> &finestre_wait;
		string title;
		string nome;
		string testo;
		int sfondo;
		int millisec;
		int &wait;
	};


extern vector <string> vocabolario;
extern int turni_passati;
extern vector <sugg> suggerimenti;
extern vector <tessera> tessere_back;
 

/*////////////////////////////////////////////////////////////////////////////////
//						DEFINIZIONI FUNZIONI ESTERNE							//
//								© Riccardo Campi								//
////////////////////////////////////////////////////////////////////////////////*/

static void init_pre_wind();
static void init_thread();
static void init_wind();
int init_running(int init_operation_number);

int DisegnaFinestra(vector <finestra> finestre, int ID, float parametro1, float parametro2, float parametro3);
int DisegnaScacchiera(scacchiera table, vector <tessera> tessere, float parametro1, float parametro2, float parametro3);
int DisegnaTessere(scacchiera table, vector <tessera> tessere, float parametro1, float parametro2, float parametro3);
int DisegnaRastrelliere(scacchiera table, vector <tessera> tessere, vector <giocatore> giocatori, float parametro1, float parametro2, float parametro3);
void drawBitmapText(void* font, string str,float x,float y);
void drawStrokeText(void* font, string str);
string intRomano(int a);

int AggiungiFinestra(vector <finestra> &finestre, float xtop, float ytop, float xbot, float ybot, string title, int sfondo, int child);
int AggiungiFinestra(vector <finestra> &finestre, float xtop, float ytop, float xbot, float ybot, string title, int sfondo, int child, bool buttons, float posx);
int AggiungiElemento(vector <finestra> &finestre, float xtop, float ytop, float xbot, float ybot, int tipo, float colr, float colg, float colb, float cola, float rotvel, float rotx, float roty, float rotz, void* font, string title, int target);
int AttivaElemento(vector <finestra> & finestre, float x, float y, int ID);
string modListbx(string title, int operazione);

float accomodaRisoluzione(int pixel);
float pixelToUnitX(int pixel);
float pixelToUnitY(int pixel);
HBITMAP LoadImageFromResource(int rc, HINSTANCE hInst);
int LoadBitmapTextureRC(int rc, int id, HINSTANCE hInst);
BOOL CALLBACK EnumProc( HWND hWnd, LPARAM lParam );
HWND FindWindowFromProcessId( DWORD dwProcessId );
int ProcessRunning( string name );
HWND GetProcessRunningHWND( string name );

vector <parola> identificaNuoveParole(vector <parola> vecchie, vector <parola> nuove);
vector <parola> identificaParole(vector <tessera> tessere, vector <string> vocabolario, int tipoControllo);
void vagliaParole(bool &prosegui, vector <tessera> tessere, vector <string> vocabolario, int &wait, vector <vector <string>> errori, vector <finestra> &finestre_wait, string title, int sfondo, int millisec);
void fineTurno(InfoBox infobox, vector <tessera> &tessere, vector <giocatore> &giocatori, int &stato, bool cambio_tessera = false);
int controlloInserimento(vector <tessera> tessere, scacchiera table, int x, int y, int z, int seltess, int selcell);

void caricaVocabolario(vector <string> &vocabolario);
string getPath(int csidl);
bool leggi(string file, vector <tessera> &tessere, vector <giocatore> &giocatori);
void scrivi(string file, vector <tessera> tessere, vector <giocatore> giocatori);
bool sePartitaSalvata(string file);
string nomePartitaSalvata(string file, int par);
int puntiPartitaSalvata(string file, int par);
bool turnoPartitaSalvata(string file, int par);

void mostraSuggerimento(suggerim &suggerendo, InfoBox infobox, vector <tessera> tessere, vector <giocatore> giocatori, vector <string> &vocabolario);
//vector <string> suggerimento(vector <tessera> tessere, vector <giocatore> giocatori, vector <string> &vocabolario);


void infoBox(InfoBox infobox);



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



