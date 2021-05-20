//------------------------------------------------------------------
// HempSimClass.cpp
//------------------------------------------------------------------
#include <iostream>

#include "HempSimClass.h"

#define SHOW_SIM_PARAMS 1
#define DEBUG 0

namespace hemp_sim
{
//------------------------------------------------------------------
//hemp_sim::hemp_sim()
//constructor
//------------------------------------------------------------------
hemp_sim::hemp_sim(HempSimParams_t * hPtr)
{
	unsigned short i;

	g_X        = hPtr->x;
	g_Y        = hPtr->y;
	g_Z        = hPtr->z;
	g_HOB      = hPtr->hob;
	g_GAMYLD   = hPtr->gamyld;
	g_BFIELD   = hPtr->bfield;
	g_BANGLE   = hPtr->bangle;
	g_NDELR    = hPtr->ndelr;
	g_OUX      = hPtr->oux;
	g_ITER     = hPtr->iter;
	g_AP       = hPtr->ap;
	g_BP       = hPtr->bp;
	g_RNP      = hPtr->rnp;
	g_TOP      = hPtr->top;

#if SHOW_SIM_PARAMS
	std::cout << "Simulation Parmaters :" << std::endl;
	std::cout << "X =     " << g_X << std::endl;
	std::cout << "Y =      " << g_Y << std::endl;
	std::cout << "Z =      " << g_Z << std::endl;
	std::cout << "HOB =    " << g_HOB << std::endl;
	std::cout << "GAMYLD = " << g_GAMYLD << std::endl;
	std::cout << "BFIELD = " << g_BFIELD << std::endl;
	std::cout << "BANGLE = " << g_BANGLE << std::endl;
	std::cout << "NDELR =  " << g_NDELR << std::endl;
	std::cout << "OUX =    " << g_OUX << std::endl;
	std::cout << "ITER =   " << g_ITER << std::endl;
	std::cout << "AP =     " << g_AP << std::endl;
	std::cout << "BP =     " << g_BP << std::endl;
	std::cout << "RNP =    " << g_RNP << std::endl;
	std::cout << "TOP =    " << g_TOP << std::endl;
#endif
	// Initialize 
	//double g_E[193];
	//double g_TIMX[193];
	//double g_STORE2[501];

	for (i = 0; i < 193; i++)
	{
		g_E[i] = 0.0;
		g_TIMX[i] = 0.0;
	}

	for (i = 0; i < 501; i++)
	{
		g_STORE2[i] = 0.0;
	}
	
}

//------------------------------------------------------------------
//hemp_sim::run_sim()
//Main Simulation Modules
//------------------------------------------------------------------
void hemp_sim::run_sim()
{

    // Run Simulation
	double d_1;

	// Global Variables
	// NDELR  -> g_NDELR
	// HOB    -> g_HOB
	// BFIELD -> g_BFIELD
	// BANGLE -> g_BANGLE
	// GAMYLD -> g_GAMYLD
	// X      -> g_X
	// Y      -> g_Y
	// Z      -> g_Z
	// OUX    -> g_OUX
	// ITER   -> g_ITER
	// AP     -> g_AP
	// BP     -> g_BP
	// RNP    -> g_RNP
	// TOP    -> g_TOP
	// TIMX   -> g_TIMX;

	unsigned short i;
	unsigned short it;
	unsigned short nmax;

	double r;
	double reflct;
	double omega;
	double theta;
	double a;
	double ta;
	double tb;

	double xrmin;
	double xrmax;
	double yrmin;
	double yrmax;
	double zrmin;
	double zrmax;

	double rmin;
	double rmax;

	double * e;
	double big = 0.0;

	// R=SQRT(X*X+Y*Y+(HOB*1000.-Z)**2)
	d_1 = g_HOB * 1000.0 - g_Z;
	r   = sqrt(g_X * g_X + g_Y * g_Y + d_1 * d_1);

	// Print Out the Message
	std::cout << "\n\nTHE BLAST WITH GAMMA YIELD OF " << g_GAMYLD << " KILOTCNS " << std::endl;
	std::cout << "IS AT AN ALTITUDE OF " << g_HOB << " KILOMETERS" << std::endl;
	std::cout << "\n" << std::endl;
	std::cout << "THE TARGET IS AT COORDINATES " << g_X << "  " << g_Y << "  " << g_Z << std::endl;
	std::cout << "WHICH IS " << r << " METERS FROM THE BURST " << std::endl;
	std::cout << "\n\n" << std::endl;
    
	//C
	//C         SET UP DEFAULT VALUES                                         CNTL 370
	//C                                                                       CNTL 380
	//      IF(BANGLE.EQ.0.) BANGLE=40.                                       CNTL 390
	if(g_BANGLE == 0.0) g_BANGLE = 40.0;

	//      IF(BFIELD.EQ.0.) BFIELD=0.00002                                   CNTL 400
	if(g_BFIELD == 0.0) g_BFIELD = 0.00002;

	//      IF(NDELR.EQ.0) NDELR=50                                           CNTL 410
	if(g_NDELR == 0) g_NDELR = 50;

	//C                                                                       CNTL 420
	//C         CONVERT DATA TO MKS UNITS                                     CNTL 430
	//C                                                                       CNTL 440
	//      HOB=HOB*1000.                                                     CNTL 450
	g_HOB = g_HOB * 1000.0;

	//      GAMYLD=2.61625E25*GAMYLD                                          CNTL 460
	g_GAMYLD = 2.61625e25 * g_GAMYLD;

	//      BANGLE=0.017453295*BANGLE                                         CNTL 470
	g_BANGLE = 0.017453295 * g_BANGLE;

	//      OMEGA=1.6E-19*BFIELD/(3.505*9.11E-31)                             CNTL 480
	omega = 1.6e-19 * g_BFIELD/(3.505 * 9.11e-31);

	//C                                                                       CNTL 490
	//C         PRINT TYPE OF CALCULATICh                                     CNTL 500
	//C                                                                       CNTL S10
	//      REFLCT=49000.                                                     CNTL 520
	reflct = 49000.0;

	//      IF(Z.GT.REFLCT) PRINT 2007                                        CNTL 530
	// 2007 FORMAT(5X,"TARGET IS ABOVE ABSORPTION REGION SO REFLECTED WAVE IS CNTL1230
	//     1BEING CALCULATED"/////)                                           CNTL1240
	if(g_Z > reflct)
	{
		std::cout << "*** TARGET IS ABOVE ABSORPTION REGION SO REFLECTED WAVE IS BEING CALCULATED \n\n" << std::endl;
	}

	//      IF(Z.LT.0.0) PRINT 2008                                           CNTL 540
	// 2008 FORMAT(5X,"REFLECTED WAVE IS BEING CALCULATED"/////)              CNTL1220
    if(g_Z < 0.0)
    {
    	std::cout << "*** REFLECTED WAVE IS BEING CALCULATED \n\n" << std::endl;
    }

    //      IF(Z.LE.REFLCT.AND.Z.GE.0.0) PRINT 2009                           CNTL 550
	// 2009 FORMAT(5X,"DIRECT WAVE IS BEING CALCULATED"/////)                 CNTL1210
    if((g_Z <= reflct) && (g_Z >= 0.0))
    {
    	std::cout << "*** DIRECT WAVE IS BEING CALCULATED \n\n" << std::endl;
    }

	//C                                                                       CNTL 560
	//C         REFLECTED WAVE CALCULATICN ASSUMES 100% REFLECTION            CNTL 570
	//C         AND USES MIRROR IMAGE OF TARGET BELOW GROUND                  CNTL 580
	//C         SET Z = -Z IF REFLECIED WAVE IS TO BE USED                    CNTL 590
	//C                                                                       CNTL 600
	//      IF(Z.GT.REFLCT) Z=-Z                                              CNTL 610
    if(g_Z > reflct)
    {
    	g_Z = -g_Z;
    }
	//      IF(Z.GT.HOB-1000.) PRINT 2007                                     CNTL 620
    if(g_Z > g_HOB - 1000.0)
    {
        std::cout << "*** TARGET IS ABOVE ABSORPTION REGION SO REFLECTED WAVE IS BEING CALCULATED \n\n" << std::endl;
        //      IF(Z.GT.HOB-1000.) Z=-Z                                           CNTL 630
        g_Z = -g_Z;
    }



	//C                                                                       CNTL 640
	//C        DETERMINE ANGLES                                               CNTL 650
	//C                                                                       CNTL 660
	//      R=SQRT(X*X+Y*Y+(HOB-Z)**2)                                        CNTL 670
    d_1 = g_HOB - g_Z;
    r   = sqrt(g_X * g_X + g_Y * g_Y + d_1 * d_1);

	//      A=ACOS((HOB-Z)/R)                                 	              CNTL 680
    a = acos(d_1/r);

	//      THETA=ACOS(COS(BANGLE)*Y/R+SIN(BANGLE)*(Z-HOB)/R)                 CNTL 690
    d_1 = g_Z - g_HOB;
    theta = acos(cos(g_BANGLE) * g_Y/r + sin(g_BANGLE) * d_1/r);

	//C                                                                       CNTL 700
	//C          DETERMINE RMIN AND RMAX                                      CNTL 710
	//C                                                                       CNTL 720
	//      ZRMIN=5.E4                                                        CNTL 730
    zrmin = 5.0e4;

	//      IF(HOB.LT.ZRMIN) ZRMIN=HOB                                        CNTL 740
    if(g_HOB < zrmin) zrmin = g_HOB;

	//      TA=(ZRMIN-HOB)/(Z-HOB)                                            CNTL 750
    ta = (zrmin - g_HOB)/(g_Z - g_HOB);

	//      XRMIN=TA*X                                                        CNTL 760
    xrmin = ta * g_X;

	//      YRMIN=TA*Y                                                        CNTL 770
    yrmin = ta * g_Y;

	//      RMIN=SQRT(XRMIN**2+YRMIN**2+(ZRMIN-HOB)**2)                       CNTL 780
    d_1 = zrmin - g_HOB;
    rmin = sqrt(xrmin * xrmin + yrmin * yrmin + d_1 * d_1);

	//      ZRMAX=Z                                                           CNTL 790
    zrmax = g_Z;

	//      IF(Z.LT.2.E4) ZRMAX=2.E4                                          CNTL 800
    if(g_Z < 2.0e4) zrmax = 2.0e4;

	//      TB=(ZRMAX-HOB)/(Z-HOB)                                            CNTL 810
    tb = (zrmax - g_HOB)/(g_Z - g_HOB);

	//      XRMAX=TB*X                                                        CNTL 820
    xrmax = tb * g_X;

	//      YRMAX=TB*Y                                                        CNTL 830
    yrmax = tb * g_Y;

	//      RMAX=SQRT(XRMAX**2+YRMAX**2+(ZRMAX-HOB)**2)                       CNTL 840
    d_1 = zrmax - g_HOB;

    rmax = sqrt(xrmax * xrmax + yrmax * yrmax + d_1 * d_1);

#
	//C                                                                       CNTL 850
	//C         CALCULATE EFIELD AT BOTTOM OF ABSORBTICN REGION               CNTL 860
	//C                                                                       CNTL 870

    //      CALL EFIELD(E,TIMX,RMIN,RMAX,NDELR,HOB,A,THETA,OMEGA,GAMYLD,      CNTL 889
	//     1STORE2,NMAX)                                                      CNTL 891

    subroutine_EFIELD(&g_E[0],&g_TIMX[0],&rmin,&rmax,&g_NDELR,&g_HOB,&a,&theta,&omega,&g_GAMYLD,&g_STORE2[0],&nmax);
	//C                                                                       CNTL 900
	//C          CALCULATE EFIELD AT TARGET                                   CNTL 910
	//C                                                                       CNTL 929
	//       IF(R.LE.RMAX) GOTO 3                                             CNTL 930
	e = &g_E[0];
	big = 0.0;

    if(r > rmax)
    {
	//       DO 1 I=1,190                                                     CNTL 940
    	e = &g_E[0];
		--e;

    	for(i = 1; i <= 190; i++)
    	{
	// 1     E(I)=E(I)*RMAX/R                                                 CNTL 950
    		*(e+i) = *(e+i) * rmax/r;
    	}
    }
    //C                                                                       CNTL 960
    //C          FIND PEAK VALUE OF EFIELD                                    CNTL 970
    //C                          	                                          CNTL 980
    // 3     BIG=E(1)                                                         CNTL 991
    big = *(e+1);

	//       IT=1                                                             CNTL 992
    it = 1;

	//       DO 2 I=2,190                                                     CNTL1001
    for(i = 2; i <= 190; i++)
    {
	//       IF(E(I).LT.BIG) GOTO 2                                           CNTL1011
        if(big <= *(e+i))
        {
	//       BIG=E(I)                                                         CNTL1022
             big = *(e+i);
	//       IT=I                                                             CNTL1023
             it = i;
	// 2     CONTINUE                                                         CNTL1030
        }
    }
	//C                                                                       CNTL1040
	//C          PRINT OUTPUT                                                 CNTL1050
	//C                                                                       CNTL1060
	//      PRINT 2010,TIMX(IT), IT                                           CNTL1071
    std::cout << "\n\nPEAK OCCURRED AT: " << g_TIMX[it] << " SHAKES Step Number : " << it << std::endl;

	//      PRINT 2005,BIG                                                    CNTL1080
	std::cout << "====================================================" << std::endl;
    std::cout << "PEAK EFIELD AT TARGET IS : " << big << "  VOLTS/METER " << std::endl;
	std::cout << "====================================================" << std::endl;

	//      PRINT 2001                                                        CNT11090
    std::cout << "\n\nTIMES USED (IN SHAKES) ARE : " << std::endl;

	//      PRINT 2002,(TIMX(I),I=1,NMAX)                                     CNTL1101
	for (i = 1; i <= nmax; i++)
	{
		std::cout << "I = " << i << " : " << g_TIMX[i] << std::endl;
	}
	
	std::cout << "\n\n" << std::endl;

    // Print out TIMX array
    //std::cout << g_TIMX[i] << "I=1" << "nmax" << std::endl;

	//      PRINT 2003                                                        CNTL1110
    std::cout << "\n\nEFIELD VALUES AT TARGET (IN V/M) ARE " << std::endl;
	for (i = 1; i <= nmax; i++)
	{
		std::cout << "I = " << i << " : " << e[i] << std::endl;
	}
	std::cout << "\n\n" << std::endl;
}

//------------------------------------------------------------------
//hemp_sim::subroutine_EFIELD()
//
//------------------------------------------------------------------
//    SUBROUTINE EFIELD(E,TIMX,RMIN,RMAX,NDELR,HOB,A,THETA,OMEGA,GAMYLD,EFLD  10
//   1STORE2,NMAX)                                                      EFLD  21

void hemp_sim::subroutine_EFIELD(double * e,
		                         double * timx,
								 double * rmin,
								 double * rmax,
								 unsigned short * ndelr,
								 double * hob,
		                         double * a,
								 double * theta,
								 double * omega,
								 double * gamyld,
								 double * store2,
								 unsigned short  * nmax)
{

	unsigned short i, j,k,l;
	unsigned short s_1;
	unsigned short it;
	double d_1, d_2;

    double r, t, dt;
    double tp, dtp, pri, pri2, ethe, ephi, jphi;
    double sigma, delrn, store1;
	double deltar;
	double jtheta;
	double ethenw = 0.0; 
	double ephinw = 0.0;

    bool abnormal_exit = false;

//C                                                                       EFLD  30
//C                                                                       EFLD  40
//C          CALCULATE THE EFIELD IN THE ABSORPTION REGION                EFLD  50
//C                                                                       EFLD  60
//    DIMENSION E(190),TIMX(190),STORE2(500)                            EFLD  71
//    REAL JTHETA,JPHI                                                  EFLD  80
//    INTEGER OUX                                                       EFLD  90
//    COMMON OUX,AP,BP,RNP,TOP                                          EFLD 100
//C                                                                       EFLD 110
//C     ITER IS TIME OF ITERATION IN SHAKES 10<=ITER<=100                 EFLD 120
//C     READ ITER AND CHANGE IT TO NUMBER OF TIME STEPS                   EFLD 130
//C                                                                       EFLD 140
//    READ 100,ITER                                                     EFLD 150
//    g_ITER globalab

//    ITER=100+(ITER-10)                                                ELFD 160
	  g_ITER = 100 + (g_ITER - 10);

//C                                                                       EFLD 170
//C         INITIALIZE ARRAYS AND CONSTANTS                               EFLD 180
//C                                                                       EFLD 190
//    READ 101,AP,BP,RNP,TOP                                            EFLD 200
//101 FORMAT(4F10.0)                                                    EFLD 210
//     g_AP                  global AP read during initialization
//     g_BP                  global BP read during initialization
//     g_RNP                 global RNP read during initialization
//     g_TOP                 global TOP read during initialization

	  // Pointer Adjustment for Fortran C index translation
	  --e;
	  --timx;
	  --store2;

//    DO 61 J=1,100                          //double _r;
		//double _tshake;
	    //double _a;
//                                                                      EFLD 220
	  for(j = 1; j <= 100; j++)
	  {
//    E(J)=0.0                                                          EFLD 230
		  e[j] = 0.0;
//    TIMX(J)=0.1*J                                                     EFLD 231
		  timx[j] = 0.1 * j;
//61  CONTINUE                                                          EFLD 240
	  }

//    DO 71 J=101,190                                                   EFLD 250
	  for(j = 101; j <= 190; j++)
	  {
//    E(J)=0.0                                                          EFLD 260
		  e[j] =  0.0;
//    TIMX(J)=10.+(J-100.)                                              EFLD 261
		  timx[j] = 10.0 + (j - 100);
//71  CONTINUE                                                          EFLD 270
	  }

//    DO 51 L=1,NDELR                                                   ELFD 280
	  for(l = 1; l < *ndelr; l++)
	  {
//    STORE2(L)=0.                                                      EFLD 281
        store2[l] = 0.0;
//51  CONTINUE                                                          EFLD 290
	  }
	  //double _r;
	  //double _tshake;
	  //double _a;

//    ETHE=0.                                                           EFLD 300
	  ethe = 0.0;
//    DELRN=NDELR                                                       EFLD 301
	  delrn = *ndelr;
//    T=0.                                                              EFLD 302
	  t = 0.0;
//    DT=1.0                                                            EabFLD 303
	  dt = 1.0;
//    EPHI=0.                                                           EFLD 304
	  ephi = 0.0;
//    DELTAR=(RMAX-RMIN)/DELRN                                          EFLD 310
	  deltar = (*rmax - *rmin)/delrn;
//    R=RMIN+DELTAR                                                     EFLD 311
	  r = *rmin + deltar;
//    RNP=1.E-8*RNP                                                     EFLD 312
      g_RNP = 1.0e-8 * g_RNP;
#if DEBUG
	  std::cout << "DELTAR " << deltar << std::endl;
	  std::cout << "RMIN " << *rmin << std::endl;
	  std::cout << "RMAX " << *rmax << std::endl;
	  std::cout << "RNP " << g_RNP << std::endl;
#endif

//C                                                                       EFLD 320
//C          START INTEGRATIONS                                           EFLD 330
//C          OUTSIOE LOOP IS FOR CALCULATION IN RETARDED TIME             EFLD 340
//C          INSIDE LOOP IS FOR INTEGRATION IN R AT EACH TIME STEP        EFLD 350
//C                                                                       EFLD 360
//    DO 21 I=1,190                                                     EFLD 370
      for(i = 1; i <= 190; i++)
      {
//    T=T+(1.E-9)*DT                                                    EFLD 371
    	  t = t + (1.0e-9 * dt);
//    TIMX(I)=T*(1.E8)                                                  EFLD 372
          timx[i] = t * 1.0e8;
//    IT=I                                                              EFLD 380
          it = i;
		  
		  //std::cout << "i: " << i << " t: " << t << " timx " << timx[i] << std::endl;

//    IF(I.GT.ITER) GOTO 42                                             EFLD 390
          if(it > g_ITER) break;
//    TP=-DELTAR/2.88E8                                                 EFLD 400
          tp = -deltar/2.88e8;
//    DTP=TP                                                            EFLD 401
          dtp = tp;
//    SIGMA=0.                                                          EFLD 402
          sigma = 0.0;
//    STORE1=0.                                                         EFLD 403
          store1 = 0.0;
//    DO 31 K=1,NDELR                                                   EFLD 410
    	  for(k = 1; k <= *ndelr; k++)
    	  {
//    CALL COMPTN(JTHETA,JPHI,T,R,A,THETA,OMEGA,HOB,GAMYLD,TP,PRI,PRI2) EFLD 420
			  //std::cout << "k: " << k <<  "t: " << t << "tp: " << tp << std::endl;
    		  subroutine_COMPTN(&jtheta, &jphi, &t, &r, a, theta, omega, hob, gamyld, &tp, &pri, &pri2);
			 // std::cout << "jtheta: " << jtheta << " jphi: " << jphi << std::endl;
//    CALL CONDCT(SIGMA,PRI,DTP,DT,HOB,R,A,STORE1,STORE2,K,NDELR,PRI2)  EFLD 430
              subroutine_CONDCT(&sigma, &pri, &dtp, &dt, hob, &r, a, &store1, &store2[1], &k, ndelr, &pri2);

//    CALL RNGKUT(ETHENW,ETHE,R,DELTAR,SIGMA,JTHETA)                    EFLD 440
              subroutine_RNGKUT(&ethenw, &ethe, &r, &deltar, &sigma, &jtheta);

//    CALL RNGKUT(EPHINW,EPHI,R,DELTAR,SIGMA,JPHI)                      EFLD 450
			  subroutine_RNGKUT(&ephinw, &ephi, &r, &deltar, &sigma, &jphi);
//    ETHE=ETHENW                                                       EFLD 460
              ethe = ethenw;
//    EPHI=EPHINW                                                       EFLD 461
              ephi = ephinw;
//    R=R+DELTAR                                                        EFLD 462
              r= r + deltar;
//    TP=TP+DTP                                                         EFLD 470
			  tp = tp + dtp;
//31   CONTINUE                                                          EFLD 480
    	  }
//    NMAX=IT
    	  *nmax = it;
//C                                                                       EFLD 490
//C          FIND MAGNITUDE OF EFIELD                                     EFLD 500
//C                                                                       EFLD 510
//    E(I)=SQRT(ETHE**2+EPHI**2)                                        EFLD 520
    		d_1 = ethe;
    		d_2 = ephi;
    		e[i] = sqrt(d_1 * d_1 + d_2 * d_2);
#if DEBUG0
			std::cout << "ethe " << ethe << " ephi " << ephi << std::endl;
			std::cout << "efield " << i << " = " << e[i] << std::endl;
			break;
#endif
//C                                                                       EFLD 530
//C          CHECK FOR DIVERGENCE OF SOLUTION                             EFLD 540
//C                                                                       EFLD 550
//    IF(E(I) .GT. 1.E15) GOTO 52                                       EFLD 560
    		if(e[i] > 1.0e15)
    		{
    			abnormal_exit = true;
    			break;
    		}
//    IF (I.EQ.100) DT=10.                                              EFLD 570

    		if(i == 100) dt = 10.0;
//    R=RMIN+DELTAR                                                     EFLD 580
    		r = *rmin + deltar;
//C                                                                       EFLD 590
//C         IF DESIRED, PRINT OUTPUT                                      EFLD 600
//C                                                                       EFLD 610
//    IF (OUX-1 .LE. 0) GOTO 21                                         EFLD 620
    		if(g_OUX-1 > 0)
    		{
//     PRINT 5,I,TIMX(I),E(I),SIGMA                                      EFLD 630
//5    FORMAT("   I =",I4,"     TIME =",F6.1," SHAKES     E(T,RMAX) =",  EFLD 820
    			std::cout << "I =" << i << "TIME =" << timx[i] << "SHAKES    E(T,RMAX) =" << e[i] << " VOLTS/METER     SIGMA =" << sigma << " MHO/METER" << std::endl;
//21   CONTINUE                                                          EFLD 640
    		}
      }
//C                                                                       EFLD 650
//C         PRINT MESSAGE AFTER TERMINATION OF TIME LOOP                  EFLD 660
//C                                                                       EFLD 670

      if(abnormal_exit == false)
      {
//42   PRINT 201,TIMX(ITER)                                              EFLD 680
//201  FORMAT(//5X,"ITERATION TERMINATED AFTER",1PE11.4, " SHAKES"//)    EFLD 840
    	  std::cout << "ITERATION TERMINATED AFTER" << timx[g_ITER] << " SHAKES" << std::endl;
//     RETURN                                                            EFLD 690
    	  return;
      }

//C                                                                       EFLD 700
//C          PRINT MESSAGE AFTER ABNORMAL TERMINATICN OF TIME LOOP        EFLD 710
//C                                                                       EFLD 720

//52  PRINT 301                                                         ELFD 730
//301 FORMAT(//15X,"*****"/15X,"***** SOLUTICN HAS GONE UNSTABLE"       EFLD 850
      std::cout << "*****" << "***** SOLUTION HAS GONE UNSTABLE" << std::endl;

//    PRINT 201,TIMX(IT)                                                EFLD 740
//201 FORMAT(//5X,"ITERATION TERMINATED AFTER",1PE11.4, " SHAKES"//)    EFLD 840
      std::cout<< "ITERATION TERMINATED AFTER" << timx[it] << " SHAKES " << std::endl;

//    IF(IT.LT.10)RETURN                                                EFLD 750
      if(it < 10) return;
//C                                                                       EFLD 760
//C         SET LAST 5 VALUES OF EFIELD TO 0.0 TO AVOID INCORRECT PEAK    EFLD 770
//C                                                                       EFLD 780
//    E(IT)=0.0                                                         EFLD 790
      e[i]    = 0.0;
//    E(IT-1)=0.0                                                       EFLD 791
      e[it-1] = 0.0;
//    E(IT-2)=0.0                                                       EFLD 792
      e[it-2] = 0.0;
//    E(IT-3)=0.0                                                       EFLD 793
      e[it-3] = 0.0;
//    E(IT-4)=0.0                                                       EFLD 794
      e[it-4] = 0.0;
//    E(IT-5)=0.0                                                       EFLD 795
      e[it-5] = 0.0;
//    RETURN                                                            EFLD 800
      return;

}

//------------------------------------------------------------------
//hemp_sim::subroutine_CONDCT()
//
//------------------------------------------------------------------
void hemp_sim::subroutine_CONDCT(double * sigma, double * pri, double * dtp, double * dt, double * hob,
		                         double * r, double * a, double * store1, double * store2, unsigned short * k, unsigned short * ndelr, double * pri2)
{
//    SUBROUTINE CONDCT(SIGMA,PRI,DTP,DT,HOB,R,A,STORE1,STORE2,K,NDELR, CNCT  10
//   1PRI2)                                                             CNCT  20
//C                                                                       CNCT  30
//C         CALCULATES SIGMA AFTER FINDING                                CNCT  40
//C         NSECCNOARY FROM NPRIMARV                                      CNCT  50
//C                                                                       CNCT  60
//C         STORE1 CCNTAINS INTEGRAL FOR NEGATIVE TAU                     CNCT  70
//C         STORE2 CCNTAINS INTEGRAL FOR POSITIVE TAU                     CNCT  80
//C                                                                       CNCT  90
//    DIMENSION STORE2(NDELR)                                           CNCT 100

	  double sec,colisn;

	  // Adjust for array index difference
	  --store2;

//    COLISN=4.E12*EXP((R*COS(A)-HOB)/7000.)                            CNCT 110
	  colisn = 4.0e12 * exp((*r * cos(*a) - *hob)/7e3);

//    STORE1=STORE1-PRI*DTP                                             CNCT 120
      *store1 = *store1 - *pri * *dtp;

//    STORE2(K)=STORE2(K)+PRI2*DT*(1.0E-9)                              CNCT 130
      store2[*k] = store2[*k] + *pri2 * *dt * (1.0e-9);

//    SEC=STORE2(K)-STORE1                                              CNCT 140
      sec = store2[*k] - *store1;

//    SIGMA=(1.6E-19**2)*SEC/(COLISN*9.11E-31)                          CNCT 150
      *sigma = (2.5599999999999998e-38) * sec/(colisn * 9.11e-31);

//    RETURN                                                            CNCT 160
      return;
//    END                                                               CNCT 161

}


//------------------------------------------------------------------
//hemp_sim::subroutine_COMPTN()
//
//------------------------------------------------------------------
void hemp_sim::subroutine_COMPTN(double * jtheta, double *jphi, double *t, double *r, double *a,
		                         double * theta, double * omega, double  *hob, double * gamyld,
								 double * tp, double * pri,  double * pri2)
{
//    SUBROUTINE COMPTN(JTHETA,JPHI,T,R,A,THETA,OMEGA,HOB,GAMYLD,TP,PRI,CMTN  10
//   1PRI2)                                                             CMTN  20
//C                                                                       CMTN  30
//C         CALCULATE THE TWO COMPONENTS OF THE                           CMTN  40
//C         COMPTON CURRENT AT GIVEN T AND R                              CMTN  50
//C         CALCULATE NUMBER OF PRINARY ELECTRCNS                         CMTN  60
//C                                                                       CMTN  70
//C         JTHETA IS THETA CONPCNENT CF COMPTON CLRRENT                  CMTN  80
//C         JPHI IS PHI COMPONENT CF COMPTON CURRENT                      CMTN  90
//C         TMAX IS COMPTON LIFETIME                                      CMTN 100
//C         PATH IS ALTITUDE SCALED COMPTON MEAN FREE PATH                CMTN 110
//C         TP IS NEGATIVE RETARDED TIME                                  CHTN 120
//C         T IS POSITIVE RETARDED TIME                                   CHTN 130
//C         PRI IS NUMBER CF PRIMARY ELECTRONS GENERATED DURING TP        CMTN 140
//C         PRI2 IS NUMBER CF PRIMARY ELECTRONS GENERATED DURING T        CMTN 150
//C         TPRIME IS VARIABLE OF INTEGRATION                             CMTN 160
//C                                                                       CMTN 170
//C         INITIALIZE CONSTANTS                                          CMTN 180
//C                                                                       CMTN 190

	  short int k;
	  double tprime;
	  double tmax;

	  double w, dt, rk1, rk2, rk3, rk4, rk5, rk6, rk7, rk8, rp1, rp2,
		     rp3, rp4, rkp1, rkp2, rkp3, rkp4, path;

	  double d_1;

//    REAL JTHETA,JPHI                                                  CMTN 200

//    JTHETA=0.                                                         CMTN 210
	  *jtheta = 0.0;//double _r;
		//double _tshake;
	    //double _a;


//    JPHI=0.                                                           CMTN 211
	  *jphi = 0.0;

//    TPRIME=(5.E-9)                                                    CMTN 212
	  tprime = 5.9e-9;

//    TMAX=CLIFE(R,A,HOB)                                               CMTN 213
	  tmax = function_CLIFE(r,a,hob);

//    PRI=0.                                                            CMTN 214
	  *pri = 0.0;

//    DT=TMAX/10.                                                       CMTN 220
	  dt = tmax/10.0;

//    PATH=309.*EXP((HOB-R*COS(A))/7000.)                               CMTN 221
	  path = 309.0 * exp((*hob - *r  * cos(*a))/7e3);

//    TPRIME=DT                                                         CMTN 222
	  tprime = dt;

//    W=DT/2.                                                           CMTN 223
	  w = dt/2.0;

//    PRI2=0.                                                           CMTN 230
	  *pri2 = 0.0;
//C                                                                       CMTN 240
//C         RUNGE-KUTTA INTEGRATICN CF COMPTON CURRENT                    CMTN 250
//C                                                                       CMTN 260
#if DEBUG0
	  std::cout << "Debug COMPTN1" << std::endl;
	  std::cout << "tprime: " << tprime << " tmax: " << tmax << "path: " << path << std::endl;
	  std::cout << "t " << *t << std::endl;
#endif
//    DO 31 K=1,10                                                      CMTN 270

	  for(k = 1; k <= 10; k++)
	  {
//    RK1=DT*CMTHET(HOB,R,A,THETA,OMEGA,PATH,T,TPRIME,GAMYLD)           CMTN 280
		  rk1 = dt * function_CMTHET(hob,r,a,theta,omega,&path,t,&tprime,gamyld);

//    RK2=DT*CMTHET(HOB,R,A,THETA,OMEGA,PATH,T,TPRIME+W,GAMYLD)         CMTN 290
		  d_1 = tprime + w;
		  rk2 = dt * function_CMTHET(hob,r,a,theta,omega,&path,t,&d_1,gamyld);

//    RK3=RK2                                                           CMTN 300
		  rk3 = rk2;

//    RK4=DT*CMTHET(HOB,R,A,THETA,OMEGA,PATH,T,TPRIME+DT,GAMYLD)        CMTN 310
		  d_1 = tprime + dt;
		  rk4 = dt * function_CMTHET(hob,r,a,theta,omega,&path,t,&d_1,gamyld);

//    JTHETA=JTHETA+(RK1+2.*(RK2+RK3)+RK4)/6.                           CMTN 320
		  *jtheta = *jtheta + (rk1 + 2.0 * (rk2 + rk3) + rk4)/6.0;
#if DEBUG0
		  std::cout << "RK1-4: " << rk1 << ", " << rk2 << ", " << rk4 << ", " << *jtheta << std::endl;
#endif
//    RK5=DT*CMPHI (HOB,R,A,THETA,OMEGA,PATH,T,TPRIME,GAMYLD)           CMTN 330
		  rk5 = dt * function_CMPHI(hob,r,a,theta,omega,&path,t,&tprime,gamyld);


//    RK6=DT*CMPHI (HOB,R,A,THETA,OMEGA,PATH,T,TPRIME+W,GAMYLD)         CMTN 340
		  d_1 = tprime + w;
		  rk6 = dt * function_CMPHI(hob,r,a,theta,omega,&path,t,&d_1,gamyld);

//    RK7=RK6                                                           CMTN 350
		  rk7 = rk6;

//    RK8=DT*CMPHI (HOB,R,A,THETA,OMEGA,PATH,T,TPRIME+DT,GAMYLD)        CMTN 360
		  d_1 = tprime + dt;
		  rk8 = dt * function_CMPHI(hob,r,a,theta,omega,&path,t,&d_1,gamyld);

//    JPHI=JPHI+(RK5+2.*(RK6+RK7)+RK8)/6.                               CMNT 370
		  *jphi = *jphi + (rk5 + 2.0 *(rk6 + rk7) + rk8)/6.0;

#if DEBUG0
		  std::cout << "RK5-8: " << rk5 << ", " << rk6 << ", " << rk8 << ", " << *jphi << std::endl;
#endif

//C                                                                       CMNT 380
//C         RUNGE-KUTTA INTEGRATION OF PRIMARIES                          CMTN 390
//C                                                                       CMTN 400

//    RKP1=DT*RKCMTN(R,THETA,OMEGA,TP,TPRIME)                           CMNT 410
		  rkp1 = dt * function_RKCMTN(theta,omega,tp,&tprime);

//    RKP2=DT*RKCMTN(R,THETA,OMEGA,TP,TPRIME+W)                         CMNT 420
		  d_1 = tprime + w;
		  rkp2 = dt * function_RKCMTN(theta,omega,tp,&d_1);

//    RKP3=RKP2                                                         CMNT 430
		  rkp3 = rkp2;

//    RKP4=DT*RKCMTN(R,THETA,OMEGA,TP,TPRIME+DT)                        CMNT 440
		  d_1 = tprime + dt;
		  rkp4 = dt * function_RKCMTN(theta,omega,tp,&d_1);

//    PRI=PRI+(RKP1+2.*(RKP2+RKP3)+RKP4)/6.                             CMNT 450
		  *pri = *pri + (rkp1 + 2.0 * (rkp2+rkp3) + rkp4)/6.0;
#if DEBUG0
		  std::cout << "RKP1-4: " << rkp1 << ", " << rkp2 << ", " << rkp4 << ", " << *pri << std::endl;
#endif
//    RP1=DT*RKCMTN(R,THETA,OMEGA,T,TPRIME)                             CMNT 460
		  rp1 = dt * function_RKCMTN(theta,omega,t,&tprime);

//    RP2=DT*RKCMTN(R,THETA,OMEGA,T,TPRIME+W)                           CMNT 470
		  d_1 = tprime + w;
		  rp2 = dt * function_RKCMTN(theta,omega,t,&d_1);

//    RP3=RP2                                                           CMNT 480
		  rp3 = rp2;

//    RP4=DT*RKCMTN(R,THETA,OMEGA,T,TPRIME+DT)                          CMNT 490
		  d_1 = tprime + dt;
		  rp4 = dt * function_RKCMTN(theta,omega,t,&d_1);

//    PRI2=PRI2+(RP1+2.*(RP2+RP3)+RP4)/6.                               CMNT 500
		  *pri2 = *pri2 + (rp1 + 2.0 * (rp2 + rp3) + rp4)/6.0;
#if DEBUG0
		  std::cout << "RP1-4: " << rp1 << ", " << rp2 << ", " << rp4 << ", " << *pri2 << std::endl;
#endif
//    TPRIME=TPRIME+DT                                                  CMNT 510
		  tprime = tprime + dt;
#if DEBUG0
		  std::cout << "Debug COMPTN3" << std::endl;
		  std::cout << "k, rkp1, rkp2, rkp3, rkp4" << std::endl;
		  std::cout << k << "," << rkp1 << "," << rkp2 << "," << rkp3 << "," << rkp4 << std::endl;
		  std::cout << "pri :" << *pri << std::endl;
		  std::cout << "rp1, rp2, rp3, rp4 " << std::endl;
		  std::cout << rp1 << ", " << rp2 << ", " << rp3 << ", " << rp4 << std::endl;
		  std::cout << "pri2 :" << *pri2 << std::endl;
#endif

//31   CONTINUE                                                          CMNT 520
	  }
//C                                                                       CMNT 530
//C         MULTIPLY PRIMARIES BY Q*G(R)/TMAX                             CMNT 540
//C         TO OBTAIN RATE OF FRODUCTION OF SECONDARIES                   CMNT 545
//C                                                                       CMNT 550

//    PRI=PRI*5.000E4*GOFR(R,A,HOB,PATH,GAMYLD)/TMAX                    CMNT 560
	  *pri = *pri * 5.0e4 * function_GOFR(r,a,hob,&path,gamyld)/tmax;

//    PRI2=PRI2*5.0E4*GOFR(R,A,HOB,PATH,GAMYLD)/TMAX                    CMNT 570
	  *pri2 = *pri2 * 5.0e4 * function_GOFR(r,a,hob,&path,gamyld)/tmax;

//    RETURN                                                            CMNT 580
	  return;
//    END                                                               CMNT 581

}
  


//------------------------------------------------------------------
//hemp_sim::subroutine_RNGKUT()
//
//------------------------------------------------------------------

//SUBROUTINE RNGKUT (E1,E,R,H,SIGMA,COMPTJ)                         RNKT1010
//C                                                                       RNKT1020
//C         E(I+1) IS CALCULATED FROM E(I)                                RNKT1030
//C         USING THE RUNGE-KUTTA METHOD                                  RNKT1040
//C                                                                       RKKT1050

void hemp_sim::subroutine_RNGKUT(double *e1, double *e, double *r, double *h,double *sigma,double *comptj)
{

	//DATA C/3.0E8/,RMUO/12.56637E-7/                                   RNKT1060
	double c = 3e8;
	double rmuo = 1.256637e-6;

	double d_1, d_2;
	double rk1,rk2,rk3,rk4;
#if DEBUG0
	std::cout << "Debug RNGKUT" << std::endl;
	std::cout << "e1, e, r, h, sigma, comptj" << std::endl;
	std::cout << *e1 << "," << *e << "," << *r << "," << *h << "," << *sigma << "," << *comptj << std::endl;
#endif
	//EFUN(R,E)=-(1./R+C*RMUO*SIGMA/2.)*E-COMPTJ*C*RMUO/2.              RNKT1070
	// See EFUN Macro

	//RK1=H*EFUN(R,E)                                                   RNKT1080
	d_1 = *r;
	d_2 = *e;
	rk1 = *h * EFUN(d_1,d_2,*sigma,*comptj,c,rmuo);

	//RK2=H*EFUN(R+H/2.,E+RK1/2.)                                       RNKT1090
	d_1 = *r + *h/2.0;
	d_2 = *e + rk1/2.0;
	rk2 = *h * EFUN(d_1,d_2,*sigma,*comptj,c,rmuo);

	//RK3=H*EFUN(R+H/2.,E+RK2/2.)                                       RNKT1100
	d_1 = *r + *h/2.0;
	d_2 = *e + rk2/2.0;
	rk3 = *h * EFUN(d_1,d_2,*sigma,*comptj,c,rmuo);

	//RK4=H*EFUN(R+H,E+RK3)                                             RNKT1110
	d_1 = *r + *h;
	d_2 = *e + rk3;
	rk4 = *h * EFUN(d_1,d_2,*sigma,*comptj,c,rmuo);

	//E1=E+(RK1+2.*(RK2+RK3)+RK4)/6.                                    RNKT1120
	*e1 = *e + (rk1 + 2.0 * (rk2 + rk3) + rk4)/6.0;

#if DEBUG0
	std::cout << "Debug RNGKUT" << std::endl;
	std::cout << "rk1, rk2, rk3, rk4, e" << std::endl;
	std::cout << rk1 << ", " << rk2 << ", " << rk3 << ", " << rk4 << ", " << *e << std::endl;
#endif


	//RETURN                                                            RNKT1130
	return;

}

//------------------------------------------------------------------
//hemp_sim::function_CMPHI()
//
//C         CALCULATES F(T,P) FOR RUNGE-KUTTA INTEGRATION                 CMPH1030
//C         OF PHI COMPONENT OF COMPTON CURRENT                           CMPH1040
//C                                                                       CMPH1050
//------------------------------------------------------------------
double hemp_sim::function_CMPHI(double *hob,double *r,double *a,double *theta,double *omega,
                                double *path,double *t,double *tprime,double *gamyld)
{

	double ret_val = 0.0;

	//      SOLVE=TOFT(T,TPRIME,THETA,OMEGA)                                  CMPH1060
	double solve = function_TOFT(t,tprime,theta,omega);
	//      SOLVE=FOFT(SOLVE)                                                 CMPH1070
	solve = function_FOFT(&solve);
	//      SOLVE=SOLVE*(-4.608E-11)*GOFR(R,A,HOB,PATH,GAMYLD)                CMPH1080
	solve = solve * (-4.608e-11) * function_GOFR(r,a,hob,path,gamyld);
	//      CMPHI=SOLVE*SIN(THETA)*SIN(OMEGA*TPRIME)                          CMPH1090
	ret_val = solve * sin(*theta) * sin(*omega * *tprime);
	//      RETURN                                                            CMPH1100
	//      END                                                               CMPH1101
#if DEBUG0
	std::cout << "Debug CMPHI" << std::endl;
	std::cout << "hob, r, a, theta, omega, path" << std::endl;
	std::cout << *hob << ", " << *r << ", " << *a << ", " << *theta << ", " << *omega << ", " << *path << std::endl;
	std::cout << "t, tprime, gamyld" << std::endl;
	std::cout << *t << "," << *tprime << "," << *gamyld << std::endl;
	std::cout << "solve, ret_val" << std::endl;
	std::cout << solve << "," << ret_val << std::endl;
#endif


	return(ret_val);

}

//------------------------------------------------------------------
//hemp_sim::function_CMTHET()
//
//C         CALCULATES F(T,F) FOR RUNGE-KUTTA INTEGRATION                 CMTH1030
//C         OF THETA COMPONENT OF COMPTON CURRENT                         CMTH1040
//      RETURN                                                            CMTH1090
//      END                                                               CMTH1091
//------------------------------------------------------------------
double hemp_sim::function_CMTHET(double *hob,double *r,double *a,double *theta,
                                 double *omega,double *path,double *t,double *tprime,double *gamyld)
{

	double ret_val = 0.0;
	double solve = 0.0;
	
	//      SOLVE=TOFT(T,TPRIME,THETA,OMEGA)                                  CMTH1050
	solve = function_TOFT(t,tprime,theta,omega);

	//      SOLVE=FOFT(SOLVE)                                                 CMTH1060
	solve = function_FOFT(&solve);

	//      SOLVE=SOLVE*(-4.608E-11)*GOFR(R,A,HOB,PATH,GAMYLD)                CMTH1070
	solve = solve * (-4.608e-11) * function_GOFR(r,a,hob,path,gamyld);
	
    //CMTHET=SOLVE*SIN(THETA)*COS(THETA)*(COS(OMEGA*TPRIME)-1.)         CMTH1080
	ret_val = solve * sin(*theta) * cos(*theta) * (cos(*omega * *tprime) - 1.0);
	

#if DEBUG0
	std::cout << "Debug CMTHET" << std::endl;
	std::cout << "hob, r, a, theta, omega, path" << std::endl;
	std::cout << *hob << ", " << *r << ", " << *a << ", " << *theta << ", " << *omega << ", " << *path << std::endl;
	std::cout << "t, tprime, gamyld" << std::endl;
	std::cout << *t << "," << *tprime << "," << *gamyld << std::endl;
	std::cout << "solve, ret_val" << std::endl;
	std::cout <<  solve << "," << ret_val << std::endl;
#endif

	return(ret_val);

}

//------------------------------------------------------------------
//hemp_sim::function_RKCMTN()
//
//C                                                                       RKCM1020
//C          CALCULATES F(T) FOR RUNGA-KUTTA                              RKCM1030
//C          INTEGRATION OF PRIMARY ELECTRONS                             RKCM1040
//C                                                                       RKCM1050
//------------------------------------------------------------------
double hemp_sim::function_RKCMTN(double *theta,double *omega,double *tp,double *tprime)
{

	double ret_val = 0.0;

	//      SOLVE=TOFT(TP,TPRIME,THETA,OMEGA)                                 RKCM1060
	double solve = function_TOFT(tp,tprime,theta,omega);
	//      RKCMTN=FOFT(SOLVE)                                                RKCM1070
	ret_val = function_FOFT(&solve);
	//      RETURN                                                            RKCM1080
	//      END    RKCM1080
#if DEBUG0
	std::cout << "Debug RKCMT" << std::endl;
	std::cout << "theta, omega, tp, tprime, solve, ret_val" << std::endl;
	std::cout << *theta << "," << *omega << "," << *tp << "," << *tprime << "," << solve << "," << ret_val << std::endl;
#endif

	return(ret_val);
}

//------------------------------------------------------------------
//hemp_sim::function_GOFR()
//
//C         SOLVES VIRGIN TRANSPORT AND USES REACTION RATE TO             GOFR1030
//C         CALCULATE THE NUMBER DENSITY OF RADIAL ELECTRONS              GOFR1040
//C                                                                       GOFR1050
//------------------------------------------------------------------
double hemp_sim::function_GOFR(double *r,double *a,double *hob,double *path,double *gamyld)
{

	double ret_val = 0.0;

	//      SOLVE=(.0226275/COS(A))*(-1.+EXP(R*COS(A)/7000.))*EXP(-HOB/7000.) GOFR1060
	double solve = (0.0226275/cos(*a)) * (-1.0 + exp(*r * cos(*a)/7e3)) * exp(-*hob/7e3);
	//      DENOM=12.56637*R*R*PATH*1.5                                       GOFR1070
	double denom = 12.56637 * *r * *r * *path * 1.5;
	//      GOFR=EXP(-SOLVE)*GAMYLD/DENOM                                     GOFF1080
	ret_val = exp(-solve) * *gamyld/denom;
	//      RETURN                                                            GOFR1090
	//      END                                                               GOFR1091
#if DEBUG0
	std::cout << "Debug GOFR" << std::endl;
	std::cout << "r, a, hob, path, gamyld, ret_val" << std::endl;
	std::cout << *r << "," << *a << "," << *hob << "," << *path << "," << *gamyld << "," << ret_val << std::endl;
#endif

	return(ret_val);

}

//------------------------------------------------------------------
//hemp_sim::function_CLIFE()
//
//C                                                                       CLIF1020
//C         CALCULATES COMPTON LIFETIME AT RADIUS = R                     CLIF1030
//C         MAX ACCEPTABLE LIFETIME = 100 SHAKES FOR                      CLIF1040
//C         THE KARZAS-LATTER HIGH FREQUENCY APPROX                       CLIF1050
//C                                                                       CLIF1060
//------------------------------------------------------------------
double hemp_sim::function_CLIFE(double *r,double *a,double *hob)
{
	double ret_val = 0.0;

	//      CLIFE=1.041667E-8*EXP((HOB-R*COS(A))/7000.)                       CLIF1070
	ret_val = 1.041667e-8 * exp((*hob - *r * cos(*a))/7e3);
	//      IF(CLIFE.GT.1.E-6) CLIFE=(1.E-6)                                  CLIF1080
	if(ret_val > 1e-6)
	{
		ret_val = 1e-6;
	}
	//      RETURN                                                            CLIFI090
	//      END                                                               CLIFI091
#if DEBUG0
	std::cout << "Debug CLIFE" << std::endl;
	std::cout << "r, a, hob, omega, ret_val" << std::endl;
	std::cout << *r << "," << *a << "," << *hob << ","  << ret_val << std::endl;
#endif

	return(ret_val);

}

//------------------------------------------------------------------
//hemp_sim::function_TOFT()
//
//C                                                                       TOFT1020
//C         T(T) IS TIME TRANSFORMED TO KARZAS-LATTER FORM                TOFT1030
//C                                                                       TOFT1040
//------------------------------------------------------------------
double hemp_sim::function_TOFT(double *t,double *tprime,double *theta,double *omega)
{

	double ret_val = 0.0;

	//std::cout << "TOFT Start: " << *t << "," << *tprime << "," << *theta << "," << *omega << std::endl;

	//      B=0.958                                                           TOFT1050
    double b = 0.958;
    double d_1 = cos(*theta);
    //      FIRST=T-(1.-B*(COS(THETA)**2))*TPRIME                             TOFT1060
    double first  = *t - (1.0 - b * (d_1 * d_1)) * *tprime;

    d_1 = sin(*theta);
    //      SECOND=B*(SIN(THETA)**2)*SIN(OMEGA*TPRIME)/OMEGA                  TOFT1070
    double second = b * (d_1 * d_1) * sin(*omega * *tprime)/(*omega);
    //      TOFT=FIRST+SECOND                                                 TOFT1080
    ret_val = first + second;
    //      RETURN                                                            TOFT1090
    //      END                                                               TOFT1091
#if DEBUG0
	std::cout << "Debug TOFT" << std::endl;
	std::cout << "t, tprime, theta, omega, first, second" << std::endl;
	std::cout << *t << "," << *tprime << "," << *theta << "," << *omega << "," << first << "," << second << std::endl;
	std::cout << "ret val " << ret_val << std::endl;
#endif

	return(ret_val);

}

//------------------------------------------------------------------
//hemp_sim::function_FOFT()
//C         F(T) IS THE POMRANNING MODEL FOR TIME DEPENDENCE              FOFT1030
//C         OF NUCLEAR WEAPON YIELD IN RETARDED TIME                      FOFT1040
//------------------------------------------------------------------
double hemp_sim::function_FOFT(double *t)
{

	//INTEGER OUX                                                       FOFT1050
	//COMMON OUX,AP,BP,RNP,TOP                                          FOFT1060
	double ret_val = 0.0;
	double denom = 0.0;
	//TSHAKE=1.E8*T                                                     FOFT1070
	double tshake = *t * 1e8;

	//std::cout << "FOFT Start: " << *t << "," << tshake << std::endl;
	//DENOM=(BP+AP*EXP((AP+BP)*(TSHAKE-TOP)))*RNP                       FOFT1080
	denom = (g_BP + g_AP * exp((g_AP + g_BP)*(tshake-g_TOP))) * g_RNP;
	//FOFT=(AP+BP)*EXP(AP*(TSHAKE-TOP))/DENOM                           FOFT1090
	ret_val = (g_AP + g_BP)*exp(g_AP*(tshake-g_TOP))/denom;

#if DEBUG0
	std::cout << "Debug FOFT" << std::endl;
	std::cout << g_AP << ", " << g_BP << ", " << g_RNP << ", " << g_TOP << std::endl;
	std::cout << *t << ", " << tshake << ", " << denom << ", " << ret_val << std::endl;
#endif

	//RETURN                                                            FOFT1100
	//END

	return(ret_val);

}

}

