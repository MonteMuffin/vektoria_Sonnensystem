#include "Game.h"

CGame::CGame(void)
{
}

CGame::~CGame(void)
{
}

void CGame::Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash)
{
	//---------------------------------
	// Initialisiere die Knotenobjekte:
	//---------------------------------

	m_zr.Init(psplash);
	m_zc.Init(QUARTERPI);
	m_zf.Init(hwnd, procOS);
	m_zc.Init(2.094F);
	m_zv.InitFull(&m_zc);

	m_zl.Init(CHVector(1.0f, 1.0f, -10.0f),
		CColor(1.0f, 1.0f, 1.0f));
	m_ziPfeil.Init("textures\\Raumschiff.png");
	m_ziHand.Init("textures\\Astronaut.png");

	m_zoPfeil.Init(&m_ziPfeil,
		C2dRect(0.05f, 0.1f), true);
	m_zoHand.Init(&m_ziHand,
		C2dRect(0.05f, 0.1f), true);
	m_zoPfeil.SetLayer(0.1f);
	m_zoHand.SetLayer(0.1f);

	//Stolarsystem sizes
	m_zgSphere_star.Init(30.f, &m_zm_star, 50, 50);
	m_zgSphere_Sun.Init(1.f, &m_zm_Sun, 50, 50);
	m_zgSphere_Mercury.Init(0.4f, &m_zm_Mercury, 50, 50);
	m_zgSphere_Venus.Init(0.4f, &m_zm_Venus, 50, 50);
	m_zgSphere_earthcore.Init(0.1f, &m_zm_earthcore, 50, 50);
	m_zgSphere_earth.Init(0.5f, &m_zm_earth, 50, 50);
	m_zgSphere_Cloud.Init(0.51f, &m_zm_Cloud, 50, 50);
	m_zgSphere_Moon.Init(0.2f, &m_zm_Moon, 50, 50);
	m_zgSphere_Mooncore.Init(0.1f, &m_zm_Moon, 50, 50);
	m_zgSphere_Mars.Init(0.6f, &m_zm_Mars, 50, 50);
	m_zgSphere_Jupiter.Init(0.7f, &m_zm_Jupiter, 50, 50);
	m_zgSphere_Saturn.Init(0.8f, &m_zm_Saturn, 50, 50);
	//m_zgCylinder_Saturnring.Init(1.2f, 0.01f, &m_zmSaturnring, 50, 50);
	m_zgSphere_Uranus.Init(0.5f, &m_zm_Uranus, 50, 50);
	m_zgSphere_Neptune.Init(0.3f, &m_zm_Neptune, 50, 50);
	m_zgSphere_Pluto.Init(0.1f, &m_zm_Pluto, 50, 50);

	m_zgCone_rokettip.Init(0.05f, 0.1f, &m_zm_rokettip, 50, 50);
	m_zgCylinder_roketbod.Init(0.05f, 0.2f, &m_zm_roketbod, 50, 50);
	m_zgCone_roketbott.Init(0.1f, 0.1f, &m_zm_roketbott, 50, 50);

	m_zgSphere_Deathstar.Init(0.2f, &m_zm_Deathstar, 50, 50);
	
	
	m_zgStone.Init(0.03f, &m_zmStone);
	m_zmStone.MakeTextureBillboard("textures\\asteroid.png");
	m_zmStone.SetChromaKeyingOn();

	//Viewport?
	m_zr.AddFrame(&m_zf);
	m_zf.AddDeviceKeyboard(&m_zdk);
	m_zf.AddViewport(&m_zv);
	m_zf.AddViewport(&m_zvLeft);
	m_zf.AddViewport(&m_zvRight);
	m_zr.AddScene(&m_zs);
	m_zs.AddLightParallel(&m_zl);
	m_zs.AddPlacement(&m_zpCamera);


	m_zs.AddPlacement(&m_zpEnemy);
	m_zpCamera.AddCamera(&m_zc);
	m_zpCamera.AddCamera(&m_zcLeft);
	m_zpEnemy.AddCamera(&m_zcRight);

	
	m_zf.AddDeviceCursor(&m_zdc);
	m_zv.AddOverlay(&m_zoPfeil);
	m_zv.AddOverlay(&m_zoHand);
	
	m_zs.AddPlacement(&m_zpSphere_star);
	m_zs.AddPlacement(&m_zpSphere_Sun);
	
	//Sun <-Earth <-Moon
	m_zpEMS.AddPlacement(&m_zpSphere_earthcore);
	m_zpEMS.AddPlacement(&m_zpSphere_earth);
	m_zpEMS.AddPlacement(&m_zpSphere_Cloud);
	m_zpSphere_earthcore.AddPlacement(&m_zpSphere_Moon);
	m_zpSphere_earthcore.AddPlacement(&m_zpSphere_Mooncore);
	m_zpSphere_Sun.AddPlacement(&m_zpEMS);

	//Moon <-Roket
	m_zpSphere_Mooncore.AddPlacement(&m_zpCone_rokettip);
	m_zpSphere_Mooncore.AddPlacement(&m_zpCylinder_roketbod);
	m_zpSphere_Mooncore.AddPlacement(&m_zpCone_roketbott);

	//Sun <-Deathstar
	m_zpSphere_Sun.AddPlacement(&m_zpSphere_Deathstar);

	//Sun <-Planets
	m_zpPS.AddPlacement(&m_zpSphere_Mercury);
	m_zpPS.AddPlacement(&m_zpSphere_Venus);
	m_zpPS.AddPlacement(&m_zpSphere_Mars);
	m_zpPS.AddPlacement(&m_zpSphere_Jupiter);
	m_zpPS.AddPlacement(&m_zpSphere_Saturn);
	//m_zpSphere_Saturn.AddPlacement(&m_zpCylinder_Saturnring);
	m_zpPS.AddPlacement(&m_zpSphere_Uranus);
	m_zpPS.AddPlacement(&m_zpSphere_Neptune);
	m_zpPS.AddPlacement(&m_zpSphere_Pluto);
	m_zpSphere_Sun.AddPlacement(&m_zpPS);

	

	//Geo
	m_zgSphere_star.Flip();
	m_zpSphere_star.AddGeo(&m_zgSphere_star);
	m_zpSphere_Sun.AddGeo(&m_zgSphere_Sun);
	m_zpSphere_Mercury.AddGeo(&m_zgSphere_Mercury);
	m_zpSphere_Venus.AddGeo(&m_zgSphere_Venus);
	m_zpSphere_earthcore.AddGeo(&m_zgSphere_earthcore);
	m_zpSphere_earth.AddGeo(&m_zgSphere_earth);
	m_zpSphere_Cloud.AddGeo(&m_zgSphere_Cloud);
	m_zpSphere_Moon.AddGeo(&m_zgSphere_Moon);
	m_zpSphere_Moon.AddGeo(&m_zgSphere_Mooncore);
	m_zpSphere_Mars.AddGeo(&m_zgSphere_Mars);
	m_zpSphere_Jupiter.AddGeo(&m_zgSphere_Jupiter);
	m_zpSphere_Saturn.AddGeo(&m_zgSphere_Saturn);
	//m_zpCylinder_Saturnring.AddGeo(&m_zgCylinder_Saturnring);
	m_zpSphere_Uranus.AddGeo(&m_zgSphere_Uranus);
	m_zpSphere_Neptune.AddGeo(&m_zgSphere_Neptune);
	m_zpSphere_Pluto.AddGeo(&m_zgSphere_Pluto);

	m_zpCone_rokettip.AddGeo(&m_zgCone_rokettip);
	m_zpCylinder_roketbod.AddGeo(&m_zgCylinder_roketbod);
	m_zpCone_roketbott.AddGeo(&m_zgCone_roketbott);

	m_zpSphere_Deathstar.AddGeo(&m_zgSphere_Deathstar);

	//Textures
	m_zm_star.MakeTextureSky("textures\\stars.jpg");

	m_zm_Sun.MakeTextureGlow("textures\\Sun_image.jpg");
	//m_zm_Sun.MakeTextureDiffuse("textures\\Sun_image.jpg");
	m_zm_Sun.MakeTextureSky("textures\\Sun_image.jpg");

	m_zm_Mercury.MakeTextureDiffuse("textures\\merkur_image.jpg");
	m_zm_Mercury.MakeTextureGlow("textures\\merkur_image.jpg");

	m_zm_Venus.MakeTextureDiffuse("textures\\venus_image.jpg");
	m_zm_Venus.MakeTextureGlow("textures\\venus_image.jpg");

	m_zm_earth.MakeTextureDiffuse("textures\\earth_image.jpg");
	m_zm_earth.MakeTextureGlow("textures\\earth_glow.jpg");
	//m_zm1.MakeTextureSpecular("texture\\earth_reflection.jpg");
	m_zm_earth.MakeTextureBump("textures\\earth_bump.jpg");
	//m_zm1.SetSpecularStrength(0.3);
	m_zm_earth.MakeTextureGlow("textures\\earth_image.jpg");
	

	m_zm_Cloud.MakeTextureSky("textures\\clouds_alpha_l1.gif");
	
	m_zm_Moon.MakeTextureDiffuse("textures\\Moon_Image.jpg");
	m_zm_Moon.MakeTextureBump("textures\\moon_bump.jpg");
	m_zm_Moon.MakeTextureGlow("textures\\Moon_image.jpg");

	m_zm_Mars.MakeTextureDiffuse("textures\\mars_image.jpg");
	m_zm_Mars.MakeTextureGlow("textures\\mars_image.jpg");

	m_zm_Jupiter.MakeTextureDiffuse("textures\\jupiter_image.jpg");
	m_zm_Jupiter.MakeTextureGlow("textures\\jupiter_image.jpg");

	m_zm_Saturn.MakeTextureDiffuse("textures\\saturn_image.jpg");
	//m_zmSaturnring.MakeTextureDiffuse("textures\\saturnringe_image.png");
	m_zm_Saturn.MakeTextureGlow("textures\\saturn_image.jpg");
	//m_zmSaturnring.MakeTextureGlow("textures\\saturnringe_image.png");

	m_zm_Uranus.MakeTextureDiffuse("textures\\uranus_image.jpg");
	m_zm_Uranus.MakeTextureGlow("textures\\uranus_image.jpg");

	m_zm_Neptune.MakeTextureDiffuse("textures\\neptune_image.jpg");
	m_zm_Neptune.MakeTextureGlow("textures\\neptune_image.jpg");

	m_zm_Pluto.MakeTextureDiffuse("textures\\pluto_image.jpg");
	m_zm_Pluto.MakeTextureGlow("textures\\pluto_image.jpg");

	m_zm_rokettip.MakeTextureDiffuse("textures\\red_image.jpg");
	m_zm_roketbod.MakeTextureDiffuse("textures\\white_image.jpg");
	m_zm_roketbott.MakeTextureDiffuse("textures\\red_image.jpg");
	m_zm_rokettip.MakeTextureGlow("textures\\red_image.jpg");
	m_zm_roketbod.MakeTextureGlow("textures\\white_image.jpg");
	m_zm_roketbott.MakeTextureGlow("textures\\red_image.jpg");

	m_zm_Deathstar.MakeTextureDiffuse("textures\\todesstern.jpg");
	m_zm_Deathstar.MakeTextureGlow("textures\\todesstern.jpg");
	m_zm_Deathstar.MakeTextureBump("textures\\Todesstern_bump.jpg");
	//m_zr.AddMaterial(&m_zm_Deathstar);
	
	//Viewport
	m_zc.Init(UM_DEG2RAD(40));
	m_zcLeft.Init(UM_DEG2RAD(30));
	m_zcRight.Init(UM_DEG2RAD(30));

	// Initialisiere das Viewport auf die volle Größe des Frames:
	m_zv.InitFull(&m_zc);

	// Initiealisiere auch die beiden Viewports für den Split-Screen-Modus:
	m_zvLeft.InitHalfLeft(&m_zcLeft);
	m_zvRight.InitHalfRight(&m_zcRight);


	//Saturnring
	for (int i = 0; i < NR_OF_STONES; i++) {
		m_zpSphere_Saturn.AddPlacement(&m_azpStones[i]);
		m_azpStones[i].SetBillboard(eBillboardType_Parallel);
		int iRandHit = rand() % 5;
		m_azpStones[i].AddGeo(&m_zgStone);
		float fRadius;
		float fHeight;
		float fa = rand() % 10000 / 10000.0f * TWOPI;
		if (rand() % 2)
			fRadius = 0.3f + 1.0f / (rand() % 100 + 1);
		else
			fRadius = 0.3f - 1.0f / (rand() % 100 + 1);

		if (rand() % 2)
			fHeight = +0.5f / (rand() % 100 + 1);
		else
			fHeight = -0.5f / (rand() % 100 + 1);
		fRadius *= 4.0f;
			
		m_avStoneRandome[i]=CHVector(sinf(fa) * fRadius, fHeight, cosf(fa) * fRadius, 0.1f/fRadius);
		m_azpStones[i].SetBillboardAngle((rand() % 3600) / 1000.0f);
		m_azpStones[i].SetBillboardScaling(0.2f + (rand() % 1000) / 1000.0f);

	}

	//Homescreen
	m_zoHomescreen.InitFull("textures//Homescreen.png");
	m_zv.AddOverlay(&m_zoHomescreen);
	m_zoHomescreen.SetLayer(0.9f);

	m_zoMultiplayer.Init("textures//Multiplayer.png", C2dRect(0.2f, 0.2f, 0.7f, 0.7f));
	m_zoHomescreen.AddOverlay(&m_zoMultiplayer);
	m_zoMultiplayer.SetLayer(0.4f);
	m_zoSingleplayer.Init("textures//Singleplayer.png", C2dRect(0.2f, 0.2f, 0.1f, 0.7f));
	m_zoHomescreen.AddOverlay(&m_zoSingleplayer);
	m_zoSingleplayer.SetLayer(0.4f);

	m_zoBackToStart.Init("textures//BackToStart.png",
		C2dRect(0.08f, 0.05f, 0.9f, 0.9f));
	m_zv.AddOverlay(&m_zoBackToStart);

	m_zoBackToStart2.Init("textures//BackToStart2.png",
		C2dRect(0.08f, 0.05f, 0.9f, 0.9f));
	m_zvLeft.AddOverlay(&m_zoBackToStart2);


	m_zoBackToStart.SetLayer(0.95f);
	m_zoBackToStart2.SetLayer(0.95f);
	//m_zoOutOfOrder.SetLayer(0.94f);

	m_zos.Add(&m_zoSingleplayer);
	m_zos.Add(&m_zoMultiplayer);
	m_zosInGame.Add(&m_zoBackToStart);
	m_zosInGame.Add(&m_zoBackToStart2);
	//m_zosInGame.Add(&m_zoOutOfOrder);

	//Nebula
	m_zgNebula.Init(0.5f, & m_zmNebula);
	m_zs.AddPlacement(&m_azpNebula[0]);
	m_zmNebula.MakeTextureBillboard("textures\\nebula.tif");
	m_zmNebula.SetTransparencyOn();
	m_azpNebula[0].SetBillboard();
	m_azpNebula[0].TranslateY(4.0f);
	for (int i = 1; i < 5; i++)
	{
		m_azpNebula[0].AddPlacement(&m_azpNebula[i]);
		m_azpNebula[i].AddGeo(&m_zgNebula);
		m_azpNebula[i].TranslateZ(i/50);
	}

	//if click on deathstar
	m_zr.AddMaterial(&m_zm_Deathstar_red);
	m_zm_Deathstar_red.LoadPreset("Blood");
	m_zgsPreselect.Add(&m_zgSphere_Deathstar);

	//cameraposition start
	m_zpCamera.TranslateZ(10.0f);
	m_zpCamera.SetTranslationSensitivity(10.0f);
	m_zpCamera.SetRotationSensitivity(0.8);
	
	// Setze die Physik auf Weltallphysik um (keine Erdgravitation, keine Atmosphäre, etc. )
	m_zs.SetPhysicsSpace();

	// Erzeuge die Blaupausen-Bullet: 
	m_zmBullet.LoadPreset("MetalRustyFlaking");
	m_zgBullet.SetAxis(eAxisZ);
	m_zgBullet.Init(0.1, 1.0f, &m_zmBullet);
	m_zpBullet.AddGeo(&m_zgBullet);
	m_zpBullet.SetPhysics(2.0f, 0.1f, 0.0f, 2000000.0f, true);
	m_zpBullet.SwitchOff();
	m_zs.AddPlacement(&m_zpBullet);

	// Initialisiere unseren Schalt-Ringbuffer: 
	m_zpsBullets.RingMake(NR_OF_BULLETS, m_zpBullet);
	m_zs.AddPlacements(m_zpsBullets);

	for (int i = 0; i < NR_OF_BULLETS; i++)
	{
		m_zs.AddAudio(&m_azaGun[i]);
		m_azaGun[i].Init("sounds//gun.wav");
	}

	//Spaceship
	m_pzgImported = m_filewavefront.LoadGeoTriangleTable("models\\spaceship.obj");
	m_zpCamera.AddPlacement(&m_zpSpaceship);
	m_zpSpaceship.AddGeo(m_pzgImported);
	//m_zpSpaceship.TranslateZ(10);
	m_zmSpaceship.MakeTextureDiffuse("models\\spaceship2.png");
	m_pzgImported->SetMaterial(&m_zmSpaceship);

	//Enemy Spaceship
	m_pzgImported2 = m_filewavefront2.LoadGeoTriangleTable("models\\spaceship.obj");
	m_zpEnemy.AddPlacement(&m_zpSpaceship2);
	m_zpSpaceship2.AddGeo(m_pzgImported2);
	m_zmSpaceship2.MakeTextureDiffuse("models\\spaceship2.png");
	m_pzgImported2->SetMaterial(&m_zmSpaceship2);

	//Muic
	m_zaMusic.Init("sounds//Music.wav");
	m_zs.AddAudio(&m_zaMusic);
	m_zaMusic.Loop();
	m_zaMusic.SetVolume(0.9f);

	CHMat mRot;
	mRot.RotateY(HALFPI);
	m_pzgImported->Transform(mRot);

	/*m_zwf.loadPreset("OCRAExtendedWhite");
	m_zwPoints.Init(C2dRect(015f, 0.03f, 0.05f, 0.1f), 5, &m_zwf);
	m_zv.AddOverlay(fm_zwPoints);
	m_zwf.SetChromakingOn();
	m_zwPoints.Setlayer(0.94f);
	m_zr.AddMaterial(fm_zwf);
	m_zwPoints.SwitchesOff();*/

}

void CGame::Tick(float fTime, float fTimeDelta)
{
	//-------------------------------------------
	// Veränderungen während der Simulationszeit:
	//-------------------------------------------

	//Rotation
	m_zpSphere_Sun.RotateY(fTime / 28);
	m_zpSphere_Mercury.RotateY(fTime / 2);
	m_zpSphere_Venus.RotateY(fTime / 2);
	m_zpSphere_earthcore.RotateY(fTime / 2);
	m_zpSphere_earth.RotateY(fTime / 2);
	m_zpSphere_Cloud.RotateY(-fTime / 0.5);
	m_zpSphere_Moon.RotateY(fTime / 2);
	m_zpSphere_Mooncore.RotateZ(fTime / 2);
	m_zpSphere_Mars.RotateY(fTime / 2);
	m_zpSphere_Jupiter.RotateY(fTime / 2);
	m_zpSphere_Saturn.RotateY(fTime / 2);
	//m_zpCylinder_Saturnring.RotateY(fTime / 2);
	m_zpSphere_Uranus.RotateY(fTime / 2);
	m_zpSphere_Neptune.RotateY(fTime / 2);
	m_zpSphere_Pluto.RotateY(fTime / 2);
	m_zpEMS.RotateY(fTime / 28);
	m_zpPS.RotateY(fTime / 28);
	
	m_zpCone_rokettip.RotateY(fTime / 2);
	m_zpCylinder_roketbod.RotateY(fTime / 2);
	m_zpCone_roketbott.RotateY(fTime / 2);
	m_zpSphere_Deathstar.RotateY(fTime / 2);

	//Placement in the "Universe"
	m_zpSphere_Mercury.TranslateDelta(CHVector(0, 0, -3));
	m_zpSphere_Venus.TranslateDelta(CHVector(0, 0, -5));
	m_zpSphere_earthcore.TranslateDelta(CHVector(0, 0, -7));
	m_zpSphere_earth.TranslateDelta(CHVector(0, 0, -7));
	m_zpSphere_Cloud.TranslateDelta(CHVector(0, 0, -7));
	m_zpSphere_earth.RotateZDelta(UM_DEG2RAD(24)); //Tilting of the earth
	m_zpSphere_Moon.TranslateDelta(CHVector(0, 0, -1));
	m_zpSphere_Mooncore.TranslateDelta(CHVector(0, 0, -1));
	m_zpSphere_Mars.TranslateDelta(CHVector(0, 0, -9));
	m_zpSphere_Jupiter.TranslateDelta(CHVector(0, 0, -11));
	m_zpSphere_Saturn.TranslateDelta(CHVector(0, 0, -13));
	//m_zpCylinder_Saturnring.RotateZDelta(UM_DEG2RAD(24));
	m_zpSphere_Uranus.TranslateDelta(CHVector(0, 0, -15));
	m_zpSphere_Neptune.TranslateDelta(CHVector(0, 0, -17));
	m_zpSphere_Pluto.TranslateDelta(CHVector(0, 0, -19));

	m_zpCone_rokettip.Translate(CHVector(0, -0.5, 0));
	m_zpCylinder_roketbod.Translate(CHVector(0, -0.7, 0));
	m_zpCone_roketbott.Translate(CHVector(0, -0.75, 0));

	m_zpSphere_Deathstar.Translate(CHVector(0, 0, 3));

	//Nebula and Stone conditions
	for (int i = 1; i < 5; i++)
	{
		m_azpNebula[i].SetBillboardAngle(fTime * i * 0.5f);
		m_azpNebula[i].SetBillboardScaling(1.0f + sin(fTime * i * 0.5f), 0.1f + sin(fTime * i * 0.5f));
	}
	m_zdk.PlaceWASD(m_zpCamera, fTimeDelta);

	for (int i = 0; i < NR_OF_STONES; i++) {
		m_azpStones[i].Translate(m_avStoneRandome[i]);
		m_azpStones[i].RotateYDelta(m_avStoneRandome[i].w * fTime);
		m_azpStones[i].RotateZDelta(UM_DEG2RAD(32));
	}

	//Conditons for Cursor
	float fx, fy;
	m_zdc.GetFractional(fx, fy, true);
	if (m_zdc.ButtonPressedLeft())
	{

		m_zoPfeil.SwitchOff(); m_zoHand.SwitchOn();
		m_zoHand.SetPos(fx - 0.01f, fy - 0.01f);
	}
	else
	{
		m_zoPfeil.SwitchOn(); m_zoHand.SwitchOff();
		m_zoPfeil.SetPos(fx - 0.01f, fy - 0.01f);
	}

	//Deathstar Conditons
	float fx2, fy2;
	m_zdc.GetFractional(fx2, fy2, true);
	if (m_zdc.ButtonUpLeft()) {
		if (m_zdc.PickGeoPreselected(m_zgsPreselect) != nullptr) {
			if (iCounter_Mat_Deathstar % 2 == 0) {
				m_zgSphere_Deathstar.SetMaterial(&m_zm_Deathstar_red);
			}
			else {
				m_zgSphere_Deathstar.SetMaterial(&m_zm_Deathstar);
			}
			iCounter_Mat_Deathstar++;

		}
	}

	//Homescreen
		if (!inGame)
		{
			COverlay* pzo = m_zdc.PickOverlayPreselected(m_zos);
			if (pzo == &m_zoSingleplayer && m_zdc.ButtonPressed(0))
			{
				m_zoHomescreen.SwitchOff();
				m_zoSingleplayer.SwitchOff();
				m_zoMultiplayer.SwitchOff();
				m_zoBackToStart.SwitchOn();
				m_zpEnemy.SwitchOff();
				isMulti = false;
				inGame = true;
				m_zvLeft.SwitchOff();
				m_zvRight.SwitchOff();
				m_zv.SwitchOn();
			}
			if (pzo == &m_zoMultiplayer && m_zdc.ButtonPressed(0))
			{
				m_zoHomescreen.SwitchOff();
				m_zoSingleplayer.SwitchOff();
				m_zoMultiplayer.SwitchOff();
				m_zoBackToStart2.SwitchOn();
				isMulti = true;
				inGame = true;
				m_zvLeft.SwitchOn();
				m_zvRight.SwitchOn();
				m_zv.SwitchOff();
				m_zpEnemy.SwitchOn();
			}
		}
		if (inGame)
		{
			COverlay* pzo = m_zdc.PickOverlayPreselected(m_zosInGame);
			if (pzo == &m_zoBackToStart && m_zdc.ButtonPressed(0))
			{
				m_zoHomescreen.SwitchOn();
				m_zoSingleplayer.SwitchOn();
				m_zoMultiplayer.SwitchOn();
				m_zoBackToStart.SwitchOff();
				inGame = false;
			}
			if (pzo == &m_zoBackToStart2 && m_zdc.ButtonPressed(0))
			{
				m_zoHomescreen.SwitchOn();
				m_zoSingleplayer.SwitchOn();
				m_zoMultiplayer.SwitchOn();
				m_zoBackToStart2.SwitchOff();
				inGame = false;
			}
		}
	// WASD-Steuerung: 
	m_zdk.PlaceWASD(m_zpCamera, fTimeDelta, false);

	for (int i = 0; i < NR_OF_BULLETS; i++)
	{
		if (m_zpsBullets.m_applacement[i]->IsOn())
		{
			m_avBulletLastPos[i] = m_zpsBullets.m_applacement[i]->GetPosGlobal();
		}
	}

	// Wenn die Leertaste gedrückt wird ...
	if (m_zdk.KeyDown(DIK_SPACE))
	{
		// ...und wenn noch Platz im Ringbuffer ist ...
		if (m_zpsBullets.RingIsNotFull())
		{
			//...dann schieße die nächste Kugel weg
			// = wir inkrementieren die Größe des aktiven Ringbereichs:
			CPlacement* pzp = m_zpsBullets.RingInc();
			CPlacement* pzp2 = m_zpsBullets.RingInc();
			// Wir kopieren die globale homogene Matrix der Camera
			// in unsere neue Bullet,  
			// d.h. die Bullet hat danach die gleiche Position und Orientierung 
			// wie die Kamera (=unsere Rakete): 
			pzp->SetMat(m_zpCamera.GetMatGlobal());
			pzp2->SetMat(m_zpSphere_Deathstar.GetMatGlobal());//muss noch randomized werden

			// Wir stellen die Schussrichtung in Richtung unserer Kamerarichtung: 
			CHVector vDir(m_zpCamera.GetDirectionGlobal());
			CHVector vDir2(m_zpSpaceship.GetDirectionGlobal());//richtung anpassen

			// wir normalisieren den Vektor, sicher ist sicher:
			vDir.Normal();
			vDir2.Normal();

			// wir kicken die Bullet weg: 
			pzp->SetPhysicsVelocity(vDir * 10.0f);
			m_azaGun[m_zpsBullets.m_uRingStart].Start();
			pzp2->SetPhysicsVelocity(vDir2 * 1.0f);
			m_azaGun[m_zpsBullets.m_uRingStart].Start();
		}
		// ---------------------------------------------
	// Zerstöre die Bullets, die Lost in Space sind:
	// ---------------------------------------------

	// Hole dir den ältesten Bullet aus dem aktiven Bereich: 
		CPlacement* pzpOldestBullet = m_zpsBullets.RingAskLast();
		// gibt es überhaupt einen Ältesten?:
		if (pzpOldestBullet)
		{
			// Wenn die Bulllet sehr weit weg von der Kamera ist (>100 Einheiten) ...
			if ((pzpOldestBullet->GetPosGlobal() - m_zpCamera.GetPosGlobal()).Length() > 100.0f)
			{
				// ... verkleinere den aktiven Bereich des Ringbuffers und schläfere damit 
				// die älteste Bullet wieder ein: 
				m_zpsBullets.RingDec();
			}
		}
		// Schaue, ob die Bullets die Erde getroffen haben: 
		for (int i = 0; i < NR_OF_BULLETS; i++)
		{
			if (m_zpsBullets.m_applacement[i]->IsOn())
			{
				CRay r;
				r.InitFromTo(m_avBulletLastPos[i], m_zpsBullets.m_applacement[i]->GetPosGlobal());

				CHitPoint hitpoint;
				if (m_zgSphere_earth.Intersects(r, hitpoint))
				{
					m_zgSphere_earth.SwitchOff();
				}
				//m_iPoints += 10;

			}
			//m_zwPoints.PrintF("%", m_iPoints);
		}
	}
	// Animiere den Ring: 
	for (int i = 0; i < NR_OF_STONES; i++)
	{
		m_azpStones[i].Translate(m_avStoneRandome[i]);
		m_azpStones[i].RotateYDelta(m_avStoneRandome[i].w * fTime);
		m_azpStones[i].RotateZDelta(UM_DEG2RAD(24));
	}

	//Flying Spaceship
	if (m_zdk.KeyPressed(DIK_A)) {
		m_zpSpaceship.RotateZ(UM_DEG2RAD(10));
		m_zpSpaceship.RotateYDelta(UM_DEG2RAD(110));
		m_zpSpaceship.TranslateZDelta(-3);
		m_zpSpaceship.TranslateYDelta(-0.4);
	}
	else if (m_zdk.KeyPressed(DIK_D)) {
		m_zpSpaceship.RotateZ(UM_DEG2RAD(10));
		m_zpSpaceship.RotateYDelta(UM_DEG2RAD(70));
		m_zpSpaceship.TranslateZDelta(-3);
		m_zpSpaceship.TranslateYDelta(-0.4);
	}
	else
	{
		m_zpSpaceship.RotateZ(UM_DEG2RAD(10));
		m_zpSpaceship.RotateY(UM_DEG2RAD(90));
		m_zpSpaceship.TranslateZDelta(-3);
		m_zpSpaceship.TranslateYDelta(-0.4);
	}

	//Enemy Spaceship aka Player2
	if (m_zdk.KeyPressed(DIK_L)) {
		m_zpSpaceship2.RotateZ(UM_DEG2RAD(10));
		m_zpSpaceship2.RotateYDelta(UM_DEG2RAD(200));
		m_zpSpaceship2.TranslateZDelta(-3);
		m_zpSpaceship2.TranslateYDelta(-0.4);
	}
	else if (m_zdk.KeyPressed(DIK_J)) {
		m_zpSpaceship2.RotateZ(UM_DEG2RAD(10));
		m_zpSpaceship2.RotateYDelta(UM_DEG2RAD(160));
		m_zpSpaceship2.TranslateZDelta(-3);
		m_zpSpaceship2.TranslateYDelta(-0.4);
	}
	else
	{
		m_zpSpaceship2.RotateZ(UM_DEG2RAD(10));
		m_zpSpaceship2.RotateY(UM_DEG2RAD(180));
		m_zpSpaceship2.TranslateZDelta(-3);
		m_zpSpaceship2.TranslateYDelta(-0.4);
	}
	// Traversiere am Schluss den Szenengraf und rendere:
	m_zr.Tick(fTimeDelta);

}

	void CGame::Fini()
{
	//-------------------------------
	// Finalisiere die Knotenobjekte:
	//-------------------------------

	// Hier die Finalisierung Deiner Vektoria-Objekte einfügen:

	// Auch die Root sollte finalisiert werden:   
	m_zr.Fini();
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
	m_zf.ReSize(iNewWidth, iNewHeight);
	// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergröße verändert wurde.
	// Hier kannst Du dann die Auflösung des Viewports neu einstellen:
	// z.B. mittels: m_zf.ReSize(iNewWidth, iNewHeight);
}
float CGame::GetTimeDeltaMin()
{
	return m_zr.GetTimeDeltaMin();
}

float CGame::GetVersion()
{
	return m_zr.GetVersion();
}



