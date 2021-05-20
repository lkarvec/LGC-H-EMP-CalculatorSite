//------------------------------------------------------------------
// HempSimClass.h
//------------------------------------------------------------------
#ifndef _HEMP_SIM_CLASS_H
#define _HEMP_SIM_CLASS_H

#include <string>
#include <vector>
#include <cmath>

#define VERSION "1.0.0"

#define TSHAKE_FACTOR 100000000.0


namespace hemp_sim
{

typedef struct HempSimParams
{
	double x;  //1
	double y;  //2
	double z;  //3
	double hob; //4
	double gamyld; //5
	double bfield; //6
	double bangle; //7
	unsigned short ndelr; //8
	unsigned short oux; //9
	unsigned short iter; //10
	double ap; //11
	double bp; //12
	double rnp; //13
	double top; //14
}HempSimParams_t;

//EFUN(R,E)=-(1./R+C*RMUO*SIGMA/2.)*E-COMPTJ*C*RMUO/2
#define EFUN(r,e,sigma,comptj,c,rmuo)  (-(1.0/r + c * rmuo * sigma/2.0) * e - comptj * c * rmuo/2.0)

class hemp_sim
{
public:
	hemp_sim(HempSimParams_t * hPtr);
	~hemp_sim() {};

	void run_sim();

private:

	double g_X;
	double g_Y;
	double g_Z;
	double g_HOB;
	double g_GAMYLD;
	double g_BFIELD;
	double g_BANGLE;
	unsigned short g_NDELR;
	unsigned short g_OUX;
    unsigned short g_ITER;
	double g_AP;
	double g_BP;
	double g_RNP;
	double g_TOP;


    //DIMENSION E(192),TIMX(192),STORE2(500)
    double g_E[195];
    double g_TIMX[195];
    double g_STORE2[505];

	void subroutine_EFIELD(double * e,double * timx,double * rmin,double * rmax, unsigned short * ndelr,
			               double * hob, double * a, double * theta, double * omega, double * gamyld,
			               double * store2, unsigned short * nmax);
	void subroutine_CONDCT(double * sigma, double * pri, double * dtp, double * dt, double * hob,
                           double * r, double * a, double * store1, double * store2, unsigned short * k,
						   unsigned short * ndelr, double * pri2);
	void subroutine_COMPTN(double * jtheta, double *jphi, double *t, double *r, double *a,
                           double * theta, double * omega, double  *hob, double * gamyld,
			               double * tp, double * pri,  double * pri2);
	void subroutine_RNGKUT(double *e1, double *e, double *r, double *h,double *sigma,double *comptj);

	double function_CMPHI(double * hob,double * r,double * a,double * theta,double * omega,
			              double * path,double * t,double * tprime,double * gamyld);
	double function_CMTHET(double * hob,double * r,double * a,double * theta,
			               double * omega,double * path,double * t,double * tprime,double * gamyld);
	double function_RKCMTN(double * theta,double * omega,double * tp,double * tprime);
	double function_GOFR(double * r,double * a,double * hob,double * path,double * gamyld);
	double function_CLIFE(double * r,double * a,double * hob);
	double function_TOFT(double * t,double * tprime,double * theta,double * omega);
	double function_FOFT(double * t);
};

}


#endif
