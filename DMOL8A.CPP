#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>

const int N=10;      //Fixed number of particles
double dt=0.00001;       //Time precision of the simulation
double tmax=20;

double x[N+2][N+2];   //x-coordinate of the (i,j) particle
double y[N+2][N+2];   //y-coordinate of the (i,j) particle
double vx[N+2][N+2];           //x-axis velocity component of the (i,j) particle
double vy[N+2][N+2];           //y-axis velocity component of the (i,j) particle
double xtemp[N+2][N+2];        //x-coordinate of the (i,j) particle at the time (t-dt)
double ytemp[N+2][N+2];        //y-coordinate of the (i,j) particle at the time (t-dt)
double A[N+2][N+2];
double B[N+2][N+2];



//Function Definition

double latticex()    // This function sets initial random velocities to each particle and fixes them at the lattice points
{
double v2sumx;

randomize();

int rx;
double rrx;
double signx=5;
float cal=100000;   //to calibrate the velocity

int i;
int j;

  for ( i=1; i<N+1;i++)  //to compute the coordinates
	{
	  for ( j=1; j<N+1; j++)
		{
			x[i][j]=j;    //sets the x-coordinate in the lattice 
			y[i][j]=i;    //sets the y-coordinate in the lattice
							  
			rx=rand() % 10;
			rrx=(double)rx;
			rrx=rrx/cal;
					
			if(signx-rrx>0) signx=-1; else signx=1;  //some initial velocities with negative signs 
			
			vx[i][j]=signx*rrx;
			v2sumx+=vx[i][j]*vx[i][j];
			signx=rrx;
		
		}
	}

return(v2sumx);
}                       //end of the function latticex



double latticey()    // This function sets initial random velocities to each particle and fixes them at the lattice points
{

double v2sumy;

randomize();

int ry;
double rry;
double signy=5;
float cal=100000;   //to calibrate the velocity

int i;
int j;

  for ( i=1; i<N+1;i++)  //to compute the coordinates
	{
	  for ( j=1; j<N+1; j++)
		{
			x[i][j]=j;    //sets the x-coordinate in the lattice 
			y[i][j]=i;    //sets the y-coordinate in the lattice
			
			ry=rand() % 10;
			rry=(double)ry;
			rry=rry/cal;
					
			if(signy-rry>0) signy=-1; else signy=1; //some initial velocities with negative signs 

			vy[i][j]=signy*rry;
					
			v2sumy+=vy[i][j]*vy[i][j];
			
			signy=rry;

		}
	}

return(v2sumy);
}                        //end of the function latticex



int temperatura (double v2sumxt,double v2sumyt,double tt)  // to set a temperature for the system of oscillators
{

double scalingx;
double scalingy;
int i;
int j;

	scalingx=tt/v2sumxt/(N*N);
	scalingx=sqrt(scalingx);

	scalingy=tt/v2sumyt/(N*N);
	scalingy=sqrt(scalingy);


		 for ( i=1; i<N+1;i++)  //compute the coordinates
			{
			  for ( j=1; j<N+1; j++)
				 {

					vx[i][j]=vx[i][j]*scalingx;
					vy[i][j]=vy[i][j]*scalingy;
					
				 }
			}

return(0);
}               //end of the function temperature


  


int tanter()   //function to compute the coordinates at t=to-dt
{

int i;
int j;

   for ( i=1; i<N+1;i++)  //compute the coordinates at t-dt
			{
			  for ( j=1; j<N+1; j++)
				 {
					xtemp[i][j]=x[i][j]-dt*vx[i][j];
					ytemp[i][j]=y[i][j]-dt*vy[i][j];				  
				 }
			}

return(0);
}               //end of the function tanter



int esptemp()   // function to specify the temperature
{
int et=2;  // to choose to start at a given temperature or another one
double tte=10000;

if(et==1)
{
 latticex();
 latticey();
}
else
{
 printf(" temperatura \n");
 getch();
 //scanf("%f",&tte);
 //latticex();
 //latticey();
 temperatura(latticex(),latticey(),tte );
}

return(0);
}              //end of the function esptemp



int cfront(char test )  // function to set fixed or periodic boundary conditions
{
int l;

if(test=='p')
  {
     for (l=0; l<N+2; l++)  //periodic boundary conditions
				 {

						 x[0][l]=x[N][l];
						 x[N+1][l]=x[1][l];
						 x[l][0]=x[l][N]-N;
						 x[l][N+1]=x[l][1]+N;
						 y[l][0]=y[l][N];
						 y[l][N+1]=y[l][1];
						 y[0][l]=y[N][l]-N;
						 y[N+1][l]=y[1][l]+N;
						
				 }

  }                      //en of if

else
  {
     for (l=0; l<N+2; l++)  //fixed boundary conditions
				 {

						 x[0][l]=l;    //x[N][l];
						 x[N+1][l]=l;  //x[1][l];
						 x[l][0]=0;     //x[l][N]-N;
						 x[l][N+1]=N+1;//x[l][1]+N;
						 y[l][0]=l;    //y[l][N];
						 y[l][N+1]=l;  //y[l][1];
						 y[0][l]=0;    //y[N][l]-N;
						 y[N+1][l]=N+1;//y[1][l]+N;
						
				 }
  }

return(0);
}                  //end of the function cfront



int calcradios()    //function to compute the factors A and B (distance between nearest neighbors)
{

int k;
int m;
		 for ( k=0; k<N+2; k++)  //to compute the nearest neighbors
			 {
				 for ( m=0; m<N+2; m++)
					{
						 A[k][m]=sqrt((x[k][m+1]-x[k][m])*(x[k][m+1]-x[k][m])+(y[k][m+1]-y[k][m])*(y[k][m+1]-y[k][m]));

						 B[k][m]=sqrt((x[k+1][m]-x[k][m])*(x[k+1][m]-x[k][m])+(y[k+1][m]-y[k][m])*(y[k+1][m]-y[k][m]));

						 if(A[k][m]==0)
						 {
						 printf("two particles coincide at the same x");
						 getch();
						 return(0);
						 }
						 if(B[k][m]==0)
						 {
						 printf("two particles coincide at the same y");
						 getch();
						 return(0);
						 }
						 
					}
					
			 }
return(0);
}                //end of the function calcradios


int calcular()     //computations
{ 

FILE *stream;
stream = fopen("dmout.txt", "w+");

int i;  //These four integer variables are to express sums
int j;
int k;
int m;

double t;              //changing time
double dt2=dt*dt;      //square of the time interval

double tantx[N+2][N+2];
double tanty[N+2][N+2];

// double ax[N+2][N+2];
// double ay[N+2][N+2];

double v2sumx=0;
double v2sumy=0;

double ecin=0; //initial kinetic energy
double u=0;    //initial potential energy
double utotal; //total energy
double uave2=0;
double u2ave=0;
double ecinave=0;
double c;
double virial=0;
double p;
char cf='f';
double z;
float cuenta=1;

tanter();//positions at to-dt

clrscr();

printf("computing...");

  for (t=dt; t<=tmax;  t=dt+t)  //computing the velocities and coordinates
	{
	
		cfront(cf);   //boundary conditions 
		calcradios();

	  for (i=1; i<N+1; i++)    //sum over all particles in the y-axis direction
		{
		 for (j=1; j<N+1; j++) //sum over all particles in the x-axis direction
		  {
			tantx[i][j]=xtemp[i][j];
			tanty[i][j]=ytemp[i][j];

			xtemp[i][j]=x[i][j];		//compute the coordinates
			ytemp[i][j]=y[i][j];
		
		//para utilizar esta forma recordar declarar ax[][] y ay[][]
			// ax[i][j]=(x[i][j+1]-x[i][j])*(1-1/A[i][j]);
			// ax[i][j]=ax[i][j]+(x[i][j]-x[i][j-1])*(1/A[i][j-1]-1);
			// ax[i][j]=ax[i][j]+(x[i+1][j]-x[i][j])*(1-1/B[i][j]);
			// ax[i][j]=ax[i][j]+(x[i][j]-x[i-1][j])*(1/B[i-1][j]-1);
			// if(t>5)    //tiempo de  equilibrio
			// {
			// virial+=(xtemp[i][j]-j)*x[i][j];  //desplazamientos			
			// }
			// x[i][j]=2*xtemp[i][j] - tantx[i][j];
			// x[i][j]=x[i][j]+dt2*ax[i][j];
						
			//here x is the force
			x[i][j]=((x[i][j+1]-x[i][j])*(1-1/A[i][j])+(x[i][j]-x[i][j-1])*(1/A[i][j-1]-1)+(x[i+1][j]-x[i][j])*(1-1/B[i][j])+(x[i][j]-x[i-1][j])*(1/B[i-1][j]-1));
			
			if(t>5)    //equillibrium time
			{
			virial+=(xtemp[i][j])*x[i][j];  //movement			
			}
			
			x[i][j]=2*xtemp[i][j] - tantx[i][j]+ dt2*x[i][j];
			
		//para utilizar esta forma recordar declarar ax[][] y ay[][]							
			// ay[i][j]=(y[i][j+1]-y[i][j])*(1-1/A[i][j]);
			// ay[i][j]=ay[i][j]+(y[i][j]-y[i][j-1])*(1/A[i][j-1]-1);
			// ay[i][j]=ay[i][j]+(y[i+1][j]-y[i][j])*(1-1/B[i][j]);
			// ay[i][j]=ay[i][j]+(y[i][j]-y[i-1][j])*(1/B[i-1][j]-1);;
			// if(t > 5)
			// {
			// virial+=(ytemp[i][j]-i)*y[i][j];  //desplazamientos
			// }
			// y[i][j]=2*ytemp[i][j] - tanty[i][j];
			// y[i][j]=y[i][j]+dt2*ay[i][j];
			
			//here y is the force
			y[i][j]=((y[i][j+1]-y[i][j])*(1-1/A[i][j])+(y[i][j]-y[i][j-1])*(1/A[i][j-1]-1)+(y[i+1][j]-y[i][j])*(1-1/B[i][j])+(y[i][j]-y[i-1][j])*(1/B[i-1][j]-1));
			
			if(t > 5)
			{
			virial+=(ytemp[i][j])*y[i][j];  //movement
			}
			
			y[i][j]=2*ytemp[i][j] - tanty[i][j] + dt2*y[i][j];
			
			
			//potential energy at t-dt anterior						
			u+=((A[i][j]-1)*(A[i][j]-1)+(A[i][j-1]-1)*(A[i][j-1]-1)+(B[i][j]-1)*(B[i][j]-1)+(B[i-1][j]-1)*(B[i-1][j]-1));
			
			//velocities at t-dt
			vx[i][j]=(x[i][j]-tantx[i][j]);
			vx[i][j]=vx[i][j]/2/dt;
			
			vy[i][j]=(y[i][j]-tanty[i][j]);
			vy[i][j]=vy[i][j]/2/dt;
			
			if(t>5)
			{
			v2sumx+=vx[i][j]*vx[i][j];
			v2sumy+=vy[i][j]*vy[i][j];
			}
						
		  }   // sum over j

		}     // sum over i
					
			ecin=v2sumx+v2sumy;
		
			ecin=ecin/2;
			
			if(t>5)
			{
			ecinave+=ecin;
			}
			
			
			u=u/4;
			
			if(t>5)
			{
			uave2+=u;
			u2ave+=u*u;
			}
			 
			// if(t>5)
			// {
			// uave2+=ecin;
			// u2ave+=ecin*ecin;
			// }
			
						
			utotal=ecin+u;
			
			fprintf(stream,"x11= %e \t",x[1][1]);
			fprintf(stream,"vx12= %e \t",vx[1][2]);
			fprintf(stream,"x13= %e \t",x[1][3]);
			fprintf(stream,"u= %e \t",u);
			fprintf(stream,"ecin= %e \t",ecin);
			fprintf(stream,"uto= %e \n",utotal);
			
			u=0;
			v2sumx=0;
			v2sumy=0;
			
			if(t>5)
			{
			cuenta+=1;
			}
			

	}       //sum over time
	
	

virial=virial/(cuenta-1);  
virial/2;

uave2=uave2/(cuenta-1);  //mean in time
uave2=uave2*uave2;
u2ave=u2ave/(cuenta-1);  
ecinave=ecinave/(cuenta-1);  

c=(u2ave-uave2);  
c=1-c/ecinave;
c=N*N/c;  

p=virial+ecinave;
p=p/N/N;

//z=p/ecinave;

clrscr();
printf("the specific heat is %e \n",c);	
printf("the virial term is %e \n",virial);
printf("the mean kinetic energy is %e \n",ecinave);
printf("the compressibility coefficient is %e \n",p);
printf("counting %e",cuenta);
getch();
	

fclose(stream);

return(0);
}            // end of the function computing




int main()
{
esptemp();
calcular();

clrscr();
printf("Hi, I already finished \n");

getch();
return(0);
}

