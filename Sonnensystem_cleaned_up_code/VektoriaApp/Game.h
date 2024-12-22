#pragma once
//-----------------------------------------------------------------------
// CGame
// 
// Erklärung : Eine weitestgehend leere Klasse, 
//             sinnfällig in eine Windows-Applikation eingebettet,
//             um ein Spiel bzw. eine 3D-Simulation zu erzeugen
// Autor     : Prof. Dr. Tobias Breiner
// Ort       : Pfungstadt
// Zeit      : seit Aug. 2011 (mit seitdem ständigen Verbesserungs-Updates)
// Copyright : Tobias Breiner  
// Disclaimer: Nutzung auf eigene Gefahr, keine Gewähr, no warranty!
//------------------------------------------------------------------------


#ifdef _WIN64
#ifdef _DEBUG
#pragma comment (lib, "Vektoria_Debug64.lib")
#pragma comment (lib, "VektoriaMath_Debug64.lib")
#else
#pragma comment (lib, "Vektoria_Release64.lib")
#pragma comment (lib, "VektoriaMath_Release64.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment (lib, "Vektoria_Debug.lib")
#pragma comment (lib, "VektoriaMath_Debug.lib")
#else
#pragma comment (lib, "Vektoria_Release.lib")
#pragma comment (lib, "VektoriaMath_Release.lib")
#endif
#endif
#define NR_OF_STONES 1000
#define NR_OF_BULLETS 30

#include "Vektoria\Root.h"

using namespace Vektoria;


class CGame
{
public:
	// Wird vor Begin einmal aufgerufen (Konstruktor):
	CGame(void);																				

	// Wird nach Ende einmal aufgerufen (Destruktor):
	~CGame(void);																				

	// Wird zu Begin einmal aufgerufen:
	void Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash);	

	// Wird während der Laufzeit bei jedem Bildaufbau aufgerufen:
	void Tick(float fTime, float fTimeDelta);						

	// Wird am Ende einmal aufgerufen:
	void Fini();																				

	// Wird immer dann aufgerufen, wenn der Benutzer die Fenstergröße verändert hat:
	void WindowReSize(int iNewWidth, int iNewHeight);											

	// Holt das minimale Zeitdelta zur eventuellen Frame-Rate-Beschränkung:
	float GetTimeDeltaMin();																	

	// Holt die Versionsnummer:
	float GetVersion();

	void Init(CHVector vDirection, CColor color);

private:

	// Die Wurzel des Szenengrafen: 
	CRoot m_zr;
	CScene m_zs;

	// Der Renderbereich für den Singleplayer-Modus:
	CViewport m_zv;

	// Die beiden Renderbereiche für den Multiplayer-Splitscreen-Modus:
	CViewport m_zvLeft;
	CViewport m_zvRight;

	CPlacement m_zpCamera;
	CPlacement m_zpEnemy;

	// Die Kameras, einen für sich und einen für den 2. Gegner im Multiplayer-Mode: 
	CCamera m_zc;
	CCamera m_zcLeft;
	CCamera m_zcRight;

	//Sonnensystem
	
	CPlacement m_zpSphere_star;
	CGeoSphere m_zgSphere_star;

	CPlacement m_zpSphere_Sun;
	CGeoSphere m_zgSphere_Sun;

	CPlacement m_zpSphere_Mercury;
	CGeoSphere m_zgSphere_Mercury;

	CPlacement m_zpSphere_Venus;
	CGeoSphere m_zgSphere_Venus;

	CPlacement m_zpSphere_earthcore;
	CGeoSphere m_zgSphere_earthcore;
	CPlacement m_zpSphere_earth;
	CGeoSphere m_zgSphere_earth;
	CPlacement m_zpSphere_Cloud;
	CGeoSphere m_zgSphere_Cloud;

	CPlacement m_zpSphere_Moon;
	CGeoSphere m_zgSphere_Moon;
	CPlacement m_zpSphere_Mooncore;
	CGeoSphere m_zgSphere_Mooncore;

	CPlacement m_zpSphere_Mars;
	CGeoSphere m_zgSphere_Mars;

	CPlacement m_zpSphere_Jupiter;
	CGeoSphere m_zgSphere_Jupiter;

	CPlacement m_zpSphere_Saturn;
	CGeoSphere m_zgSphere_Saturn;
	//CPlacement m_zpCylinder_Saturnring;
	//CGeoCylinder m_zgCylinder_Saturnring;

	//More realistc Saturnrings
	CPlacement m_azpStones[NR_OF_STONES];
	CGeoQuad m_zgStone;
	CHVector m_avStoneRandome[NR_OF_STONES];

	CPlacement m_zpSphere_Uranus;
	CGeoSphere m_zgSphere_Uranus;

	CPlacement m_zpSphere_Neptune;
	CGeoSphere m_zgSphere_Neptune;

	CPlacement m_zpSphere_Pluto;
	CGeoSphere m_zgSphere_Pluto;

	//Roket orbiting
	CPlacement m_zpCone_rokettip;
	CGeoCone m_zgCone_rokettip;
	CPlacement m_zpCylinder_roketbod;
	CGeoCylinder m_zgCylinder_roketbod;
	CPlacement m_zpCone_roketbott;
	CGeoCone m_zgCone_roketbott;

	//Deathstar
	CPlacement m_zpSphere_Deathstar;
	CGeoSphere m_zgSphere_Deathstar;

	//Hiarchy
	CPlacement m_zpEMS;
	CPlacement m_zpPS;

	CFrame m_zf;
	CLightParallel m_zl;

	//Materials
	CMaterial m_zm_star;
	CMaterial m_zm_Sun;
	CMaterial m_zm_Mercury;
	CMaterial m_zm_Venus;
	CMaterial m_zm_earthcore;
	CMaterial m_zm_earth;
	CMaterial m_zm_Cloud;
	CMaterial m_zm_Moon;
	CMaterial m_zm_Mars;
	CMaterial m_zm_Jupiter;
	CMaterial m_zm_Saturn;
	//CMaterial m_zmSaturnring;
	CMaterial m_zmStone;
	CMaterial m_zm_Uranus;
	CMaterial m_zm_Neptune;
	CMaterial m_zm_Pluto;

	CMaterial m_zm_rokettip;
	CMaterial m_zm_roketbod;
	CMaterial m_zm_roketbott;

	CMaterial m_zm_Deathstar;
	

	CDeviceKeyboard m_zdk;
	CDeviceCursor m_zdc;
	CImage m_ziPfeil;
	CImage m_ziHand;
	COverlay m_zoPfeil;
	COverlay m_zoHand;

	CGeos m_zgsPreselect;
	unsigned int iCounter_Mat_Deathstar = 0;
	CMaterial m_zm_Deathstar_red;

	CImage m_ziHomescreen;
	COverlay m_zoHomescreen;
	COverlay m_zoSingleplayer;
	COverlay m_zoMultiplayer;

	COverlays m_zos;
	bool isMulti = false;

	COverlay m_zoBackToStart;
	COverlay m_zoBackToStart2;
	COverlays m_zosInGame;
	bool inGame = false;

	CPlacement m_azpNebula[5];
	CGeoQuad m_zgNebula;
	CMaterial m_zmNebula;

	// Der Ringbuffer: 
	CPlacements m_zpsBullets;
	CHVector m_avBulletLastPos[NR_OF_BULLETS];
	CAudio m_azaGun[NR_OF_BULLETS];

	// Das Blaupausen-Bullet: 
	CPlacement m_zpBullet;
	CGeoCylinder m_zgBullet;
	CMaterial m_zmBullet;

	//Spaceship
	CFileWavefront m_filewavefront;
	CGeoTriangleTable * m_pzgImported = nullptr;
	CPlacement m_zpSpaceship;
	CMaterial m_zmSpaceship;

	//Enemy Spaceship
	CFileWavefront m_filewavefront2;
	CGeoTriangleTable* m_pzgImported2 = nullptr;
	CPlacement m_zpSpaceship2;
	CMaterial m_zmSpaceship2;

	// Die Hardtech-Mucke: 
	CAudio m_zaMusic;
	
	/*CWritingFront m_zwf;
	CWriting m_zw_Points;
	int m_iPoints = 0;*/

};


