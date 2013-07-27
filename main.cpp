#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<iostream>

using namespace std;
float x[500000] ,y[500000],rdata[2][500000];
float vectortest[2][2];

    float computeEuclideanDistance(float sequence1[][2], float sequence2[][2]) {
        float sum = 0;
        for (int i=0; i<2; i++) {
            for (int j=0; j<2; j++) {
                sum = sum +pow(( sequence1[i][j]- sequence2[i][j] ),2);
            }
        }
        return sqrt(sum);
    }

float compareab(int fileno){
    int i ,j ,k;
    float meanx ,meany ,varx=0 ,vary=0 ,covarxy=0 ,cov_mat[3][3] ,n ;
	float sumx=0,sumy=0;
	string file;
	file.append("ab/");
	file.append(1,(char)(((int)'0')+fileno));
	file.append(".txt");
    char cfile[11];
    for(j=0;j<10;++j)
    cfile[j]=file[j];
    cout<<endl;
	puts(cfile);
	freopen(cfile,"r",stdin);
	i=0;
	while(scanf("%f %f",&x[i],&y[i])!=EOF)
	{
		sumx+=x[i];
		sumy+=y[i];
		i++;
	}
    fclose (stdin);
	n=(float)i;
	meanx=sumx/n;
	meany=sumy/n;
	for(i=0;i<n;i++)
	{
		x[i]-=meanx;
		rdata[0][i]=x[i];
		y[i]-=meany;
		rdata[1][i]=y[i];
	}

	for(i=0;i<n;i++)
	{
		varx+=x[i]*x[i];
		vary+=y[i]*y[i];
		covarxy+=x[i]*y[i];
	}

	varx/=n-1 , vary/=n-1 ,covarxy/=n-1 ;

	cov_mat[0][0]=varx , cov_mat[0][1]=covarxy;
	cov_mat[1][0]=covarxy , cov_mat[1][1]=vary;

	//printf("\nCovariance matrix\n");
	//printf("%f  %f\n",cov_mat[0][0],cov_mat[0][1]);
	//printf("%f  %f\n",cov_mat[1][0],cov_mat[1][1]);

	float a=1,b,c,eigen1,eigen2;
	b=cov_mat[0][0]+cov_mat[1][1];
	c=(cov_mat[0][0]*cov_mat[1][1])-(cov_mat[0][1]*cov_mat[1][0]);
	eigen1=(b+sqrt((b*b)-4*a*c))/2*a;
	eigen2=(b-sqrt((b*b)-4*a*c))/2*a;
	//printf("\n\nEigen values are : %f %f\n",eigen1,eigen2);

	float a_eigen1[2][2],a_eigen2[2][2];
	for(i=0;i<2;i++)
		for(j=0;j<2;j++)
		{
			a_eigen1[i][j]= i==j ? cov_mat[i][j]-eigen1 : cov_mat[i][j];
			a_eigen2[i][j]= i==j ? cov_mat[i][j]-eigen2 : cov_mat[i][j];
		}

	float rfvector1 [1][2] ,rfvector2[2][2];

	rfvector1[0][0]=sqrt((a_eigen1[0][1]*a_eigen1[0][1])/(a_eigen1[0][0]*a_eigen1[0][0] + a_eigen1[0][1]*a_eigen1[0][1]));
	rfvector1[0][1]=sqrt((a_eigen1[0][0]*a_eigen1[0][0])/(a_eigen1[0][0]*a_eigen1[0][0] + a_eigen1[0][1]*a_eigen1[0][1]));

	rfvector2[0][0]=sqrt((a_eigen1[0][1]*a_eigen1[0][1])/(a_eigen1[0][0]*a_eigen1[0][0] + a_eigen1[0][1]*a_eigen1[0][1]));
	rfvector2[0][1]=sqrt((a_eigen1[0][0]*a_eigen1[0][0])/(a_eigen1[0][0]*a_eigen1[0][0] + a_eigen1[0][1]*a_eigen1[0][1]));
	rfvector2[1][0]=sqrt((a_eigen2[0][1]*a_eigen2[0][1])/(a_eigen2[0][0]*a_eigen2[0][0] + a_eigen2[0][1]*a_eigen2[0][1]));
	rfvector2[1][1]=sqrt((a_eigen2[0][0]*a_eigen2[0][0])/(a_eigen2[0][0]*a_eigen2[0][0] + a_eigen2[0][1]*a_eigen2[0][1]));

	float t1,t2;
	t1=abs(a_eigen1[0][0]*rfvector2[0][0] + a_eigen1[0][1]*rfvector2[0][1]);
	t2=abs(a_eigen1[0][0]*rfvector2[0][0] *(-1.0)+ a_eigen1[0][1]*rfvector2[0][1]);
	if(t1>t2)
	{
		rfvector2[0][0]*=(-1.0);
		rfvector1[0][0]*=(-1.0);
	}
	t1=abs(a_eigen2[0][0]*rfvector2[1][0] + a_eigen2[0][1]*rfvector2[1][1]);
	t2=abs(a_eigen2[0][0]*rfvector2[1][0] *(-1.0)+ a_eigen2[0][1]*rfvector2[1][1]);
	if(t1>t2)  rfvector2[1][0]*=(-1.0);

	//printf("\nrfvector matrix\n");
	/*for(i=0;i<2;i++)
	{        printf("\n");
		for(j=0;j<2;j++) printf("%f  " ,rfvector2[i][j]);
	}*/

	return computeEuclideanDistance(rfvector2,vectortest);
}

void testab(int fileno){
int i ,j ,k;
      float meanx ,meany ,varx=0 ,vary=0 ,covarxy=0 ,cov_mat[3][3] ,n ;
	float sumx=0,sumy=0;
	string file;
	file.append("ab/");
	file.append(1,(char)(((int)'0')+fileno));
	file.append(".txt");
    char cfile[11];
    for(j=0;j<10;++j)
    cfile[j]=file[j];
    cout<<endl;
	puts(cfile);
	//freopen("matlab output.txt","r",stdin);
	freopen(cfile,"r",stdin);
	i=0;
	while(scanf("%f %f",&x[i],&y[i])!=EOF)
	{
		sumx+=x[i];
		sumy+=y[i];
		i++;
	}

	n=(float)i;
	meanx=sumx/n;
	meany=sumy/n;
	for(i=0;i<n;i++)
	{
		x[i]-=meanx;
		rdata[0][i]=x[i];
		//printf("%f ",rdata[0][i]);
		y[i]-=meany;
		rdata[1][i]=y[i];
		//printf("    %f\n",rdata[1][i]);
	}

	for(i=0;i<n;i++)
	{
		varx+=x[i]*x[i];
		vary+=y[i]*y[i];
		covarxy+=x[i]*y[i];
	}

	varx/=n-1 , vary/=n-1 ,covarxy/=n-1 ;

	cov_mat[0][0]=varx , cov_mat[0][1]=covarxy;
	cov_mat[1][0]=covarxy , cov_mat[1][1]=vary;

	//printf("\n\nCovariance matrix\n");
	//printf("%f  %f\n",cov_mat[0][0],cov_mat[0][1]);
	//printf("%f  %f\n",cov_mat[1][0],cov_mat[1][1]);
	float a=1,b,c,eigen1,eigen2;
	b=cov_mat[0][0]+cov_mat[1][1];
	c=(cov_mat[0][0]*cov_mat[1][1])-(cov_mat[0][1]*cov_mat[1][0]);
	eigen1=(b+sqrt((b*b)-4*a*c))/2*a;
	eigen2=(b-sqrt((b*b)-4*a*c))/2*a;
	//printf("\n\nEigen values are : %f %f\n",eigen1,eigen2);

	float a_eigen1[2][2],a_eigen2[2][2];
	for(i=0;i<2;i++)
		for(j=0;j<2;j++)
		{
			a_eigen1[i][j]= i==j ? cov_mat[i][j]-eigen1 : cov_mat[i][j];
			a_eigen2[i][j]= i==j ? cov_mat[i][j]-eigen2 : cov_mat[i][j];
		}

	float rfvector1 [1][2] ,rfvector2[2][2];

	rfvector1[0][0]=sqrt((a_eigen1[0][1]*a_eigen1[0][1])/(a_eigen1[0][0]*a_eigen1[0][0] + a_eigen1[0][1]*a_eigen1[0][1]));
	rfvector1[0][1]=sqrt((a_eigen1[0][0]*a_eigen1[0][0])/(a_eigen1[0][0]*a_eigen1[0][0] + a_eigen1[0][1]*a_eigen1[0][1]));

	rfvector2[0][0]=sqrt((a_eigen1[0][1]*a_eigen1[0][1])/(a_eigen1[0][0]*a_eigen1[0][0] + a_eigen1[0][1]*a_eigen1[0][1]));
	rfvector2[0][1]=sqrt((a_eigen1[0][0]*a_eigen1[0][0])/(a_eigen1[0][0]*a_eigen1[0][0] + a_eigen1[0][1]*a_eigen1[0][1]));
	rfvector2[1][0]=sqrt((a_eigen2[0][1]*a_eigen2[0][1])/(a_eigen2[0][0]*a_eigen2[0][0] + a_eigen2[0][1]*a_eigen2[0][1]));
	rfvector2[1][1]=sqrt((a_eigen2[0][0]*a_eigen2[0][0])/(a_eigen2[0][0]*a_eigen2[0][0] + a_eigen2[0][1]*a_eigen2[0][1]));

	float t1,t2;
	t1=abs(a_eigen1[0][0]*rfvector2[0][0] + a_eigen1[0][1]*rfvector2[0][1]);
	t2=abs(a_eigen1[0][0]*rfvector2[0][0] *(-1.0)+ a_eigen1[0][1]*rfvector2[0][1]);
	if(t1>t2)
	{
		rfvector2[0][0]*=(-1.0);
		rfvector1[0][0]*=(-1.0);
	}
	t1=abs(a_eigen2[0][0]*rfvector2[1][0] + a_eigen2[0][1]*rfvector2[1][1]);
	t2=abs(a_eigen2[0][0]*rfvector2[1][0] *(-1.0)+ a_eigen2[0][1]*rfvector2[1][1]);
	if(t1>t2)  rfvector2[1][0]*=(-1.0);

	for(i=0;i<2;i++)
	{	for(j=0;j<2;j++) {
            vectortest[i][j]=rfvector2[i][j];
		}
	}
}


float comparelb(int fileno){
    int i ,j ,k;
    float meanx ,meany ,varx=0 ,vary=0 ,covarxy=0 ,cov_mat[3][3] ,n ;
	float sumx=0,sumy=0;
	string file;
	file.append("lb/");
	file.append(1,(char)(((int)'0')+fileno));
	file.append(".txt");
    char cfile[11];
    for(j=0;j<10;++j)
    cfile[j]=file[j];
    cout<<endl;
	puts(cfile);
	//freopen("matlab output.txt","r",stdin);
	freopen(cfile,"r",stdin);

	i=0;

	while(scanf("%f %f",&x[i],&y[i])!=EOF)
	{
		sumx+=x[i];
		sumy+=y[i];
		i++;
	}
    fclose (stdin);
	n=(float)i;
	meanx=sumx/n;
	meany=sumy/n;


	//printf("\nmeanx   meany");
	//printf("\n%f %f\n",meanx,meany);
	for(i=0;i<n;i++)
	{
		x[i]-=meanx;
		rdata[0][i]=x[i];
		//printf("%f ",rdata[0][i]);
		y[i]-=meany;
		rdata[1][i]=y[i];
		//printf("    %f\n",rdata[1][i]);
	}

	for(i=0;i<n;i++)
	{
		varx+=x[i]*x[i];
		vary+=y[i]*y[i];
		covarxy+=x[i]*y[i];
	}

	varx/=n-1 , vary/=n-1 ,covarxy/=n-1 ;

	cov_mat[0][0]=varx , cov_mat[0][1]=covarxy;
	cov_mat[1][0]=covarxy , cov_mat[1][1]=vary;

	//printf("\nCovariance matrix\n");
	//printf("%f  %f\n",cov_mat[0][0],cov_mat[0][1]);
	//printf("%f  %f\n",cov_mat[1][0],cov_mat[1][1]);

	float a=1,b,c,eigen1,eigen2;
	b=cov_mat[0][0]+cov_mat[1][1];
	c=(cov_mat[0][0]*cov_mat[1][1])-(cov_mat[0][1]*cov_mat[1][0]);
	eigen1=(b+sqrt((b*b)-4*a*c))/2*a;
	eigen2=(b-sqrt((b*b)-4*a*c))/2*a;
	//printf("\n\nEigen values are : %f %f\n",eigen1,eigen2);

	float a_eigen1[2][2],a_eigen2[2][2];
	for(i=0;i<2;i++)
		for(j=0;j<2;j++)
		{
			a_eigen1[i][j]= i==j ? cov_mat[i][j]-eigen1 : cov_mat[i][j];
			a_eigen2[i][j]= i==j ? cov_mat[i][j]-eigen2 : cov_mat[i][j];
		}

	float rfvector1 [1][2] ,rfvector2[2][2];

	rfvector1[0][0]=sqrt((a_eigen1[0][1]*a_eigen1[0][1])/(a_eigen1[0][0]*a_eigen1[0][0] + a_eigen1[0][1]*a_eigen1[0][1]));
	rfvector1[0][1]=sqrt((a_eigen1[0][0]*a_eigen1[0][0])/(a_eigen1[0][0]*a_eigen1[0][0] + a_eigen1[0][1]*a_eigen1[0][1]));

	rfvector2[0][0]=sqrt((a_eigen1[0][1]*a_eigen1[0][1])/(a_eigen1[0][0]*a_eigen1[0][0] + a_eigen1[0][1]*a_eigen1[0][1]));
	rfvector2[0][1]=sqrt((a_eigen1[0][0]*a_eigen1[0][0])/(a_eigen1[0][0]*a_eigen1[0][0] + a_eigen1[0][1]*a_eigen1[0][1]));
	rfvector2[1][0]=sqrt((a_eigen2[0][1]*a_eigen2[0][1])/(a_eigen2[0][0]*a_eigen2[0][0] + a_eigen2[0][1]*a_eigen2[0][1]));
	rfvector2[1][1]=sqrt((a_eigen2[0][0]*a_eigen2[0][0])/(a_eigen2[0][0]*a_eigen2[0][0] + a_eigen2[0][1]*a_eigen2[0][1]));

	float t1,t2;
	t1=abs(a_eigen1[0][0]*rfvector2[0][0] + a_eigen1[0][1]*rfvector2[0][1]);
	t2=abs(a_eigen1[0][0]*rfvector2[0][0] *(-1.0)+ a_eigen1[0][1]*rfvector2[0][1]);
	if(t1>t2)
	{
		rfvector2[0][0]*=(-1.0);
		rfvector1[0][0]*=(-1.0);
	}
	t1=abs(a_eigen2[0][0]*rfvector2[1][0] + a_eigen2[0][1]*rfvector2[1][1]);
	t2=abs(a_eigen2[0][0]*rfvector2[1][0] *(-1.0)+ a_eigen2[0][1]*rfvector2[1][1]);
	if(t1>t2)  rfvector2[1][0]*=(-1.0);


	//printf("\nrfvector matrix\n");
	/*for(i=0;i<2;i++)
	{        printf("\n");
		for(j=0;j<2;j++) printf("%f  " ,rfvector2[i][j]);
	}*/

	return computeEuclideanDistance(rfvector2,vectortest);
}

void testlb(int fileno){
int i ,j ,k;
      float meanx ,meany ,varx=0 ,vary=0 ,covarxy=0 ,cov_mat[3][3] ,n ;
	float sumx=0,sumy=0;
	string file;
	file.append("lb/");
	file.append(1,(char)(((int)'0')+fileno));
	file.append(".txt");
    char cfile[11];
    for(j=0;j<10;++j)
    cfile[j]=file[j];
    cout<<endl;
	puts(cfile);
	//freopen("matlab output.txt","r",stdin);
	freopen(cfile,"r",stdin);
	i=0;
	while(scanf("%f %f",&x[i],&y[i])!=EOF)
	{
		sumx+=x[i];
		sumy+=y[i];
		i++;
	}

	n=(float)i;
	meanx=sumx/n;
	meany=sumy/n;

	//printf("\nmeanx   meany");
	//printf("\n%f %f\n",meanx,meany);
	for(i=0;i<n;i++)
	{
		x[i]-=meanx;
		rdata[0][i]=x[i];
		//printf("%f ",rdata[0][i]);
		y[i]-=meany;
		rdata[1][i]=y[i];
		//printf("    %f\n",rdata[1][i]);
	}

	for(i=0;i<n;i++)
	{
		varx+=x[i]*x[i];
		vary+=y[i]*y[i];
		covarxy+=x[i]*y[i];
	}

	varx/=n-1 , vary/=n-1 ,covarxy/=n-1 ;

	cov_mat[0][0]=varx , cov_mat[0][1]=covarxy;
	cov_mat[1][0]=covarxy , cov_mat[1][1]=vary;

	//printf("\n\nCovariance matrix\n");
	//printf("%f  %f\n",cov_mat[0][0],cov_mat[0][1]);
	//printf("%f  %f\n",cov_mat[1][0],cov_mat[1][1]);
	float a=1,b,c,eigen1,eigen2;
	b=cov_mat[0][0]+cov_mat[1][1];
	c=(cov_mat[0][0]*cov_mat[1][1])-(cov_mat[0][1]*cov_mat[1][0]);
	eigen1=(b+sqrt((b*b)-4*a*c))/2*a;
	eigen2=(b-sqrt((b*b)-4*a*c))/2*a;
	//printf("\n\nEigen values are : %f %f\n",eigen1,eigen2);

	float a_eigen1[2][2],a_eigen2[2][2];
	for(i=0;i<2;i++)
		for(j=0;j<2;j++)
		{
			a_eigen1[i][j]= i==j ? cov_mat[i][j]-eigen1 : cov_mat[i][j];
			a_eigen2[i][j]= i==j ? cov_mat[i][j]-eigen2 : cov_mat[i][j];
		}

	float rfvector1 [1][2] ,rfvector2[2][2];

	rfvector1[0][0]=sqrt((a_eigen1[0][1]*a_eigen1[0][1])/(a_eigen1[0][0]*a_eigen1[0][0] + a_eigen1[0][1]*a_eigen1[0][1]));
	rfvector1[0][1]=sqrt((a_eigen1[0][0]*a_eigen1[0][0])/(a_eigen1[0][0]*a_eigen1[0][0] + a_eigen1[0][1]*a_eigen1[0][1]));

	rfvector2[0][0]=sqrt((a_eigen1[0][1]*a_eigen1[0][1])/(a_eigen1[0][0]*a_eigen1[0][0] + a_eigen1[0][1]*a_eigen1[0][1]));
	rfvector2[0][1]=sqrt((a_eigen1[0][0]*a_eigen1[0][0])/(a_eigen1[0][0]*a_eigen1[0][0] + a_eigen1[0][1]*a_eigen1[0][1]));
	rfvector2[1][0]=sqrt((a_eigen2[0][1]*a_eigen2[0][1])/(a_eigen2[0][0]*a_eigen2[0][0] + a_eigen2[0][1]*a_eigen2[0][1]));
	rfvector2[1][1]=sqrt((a_eigen2[0][0]*a_eigen2[0][0])/(a_eigen2[0][0]*a_eigen2[0][0] + a_eigen2[0][1]*a_eigen2[0][1]));

	float t1,t2;
	t1=abs(a_eigen1[0][0]*rfvector2[0][0] + a_eigen1[0][1]*rfvector2[0][1]);
	t2=abs(a_eigen1[0][0]*rfvector2[0][0] *(-1.0)+ a_eigen1[0][1]*rfvector2[0][1]);
	if(t1>t2)
	{
		rfvector2[0][0]*=(-1.0);
		rfvector1[0][0]*=(-1.0);
	}
	t1=abs(a_eigen2[0][0]*rfvector2[1][0] + a_eigen2[0][1]*rfvector2[1][1]);
	t2=abs(a_eigen2[0][0]*rfvector2[1][0] *(-1.0)+ a_eigen2[0][1]*rfvector2[1][1]);
	if(t1>t2)  rfvector2[1][0]*=(-1.0);

	for(i=0;i<2;i++)
	{	for(j=0;j<2;j++) {
            vectortest[i][j]=rfvector2[i][j];
		}
	}
}

float comparela(int fileno){
    int i ,j ,k;
    float meanx ,meany ,varx=0 ,vary=0 ,covarxy=0 ,cov_mat[3][3] ,n ;
	float sumx=0,sumy=0;
	string file;
	file.append("la/");
	file.append(1,(char)(((int)'0')+fileno));
	file.append(".txt");
    char cfile[11];
    for(j=0;j<10;++j)
    cfile[j]=file[j];
    cout<<endl;
	puts(cfile);
	//freopen("matlab output.txt","r",stdin);
	freopen(cfile,"r",stdin);

	i=0;

	while(scanf("%f %f",&x[i],&y[i])!=EOF)
	{
		sumx+=x[i];
		sumy+=y[i];
		i++;
	}
    fclose (stdin);
	n=(float)i;
	meanx=sumx/n;
	meany=sumy/n;


	//printf("\nmeanx   meany");
	//printf("\n%f %f\n",meanx,meany);
	for(i=0;i<n;i++)
	{
		x[i]-=meanx;
		rdata[0][i]=x[i];
		//printf("%f ",rdata[0][i]);
		y[i]-=meany;
		rdata[1][i]=y[i];
		//printf("    %f\n",rdata[1][i]);
	}

	for(i=0;i<n;i++)
	{
		varx+=x[i]*x[i];
		vary+=y[i]*y[i];
		covarxy+=x[i]*y[i];
	}

	varx/=n-1 , vary/=n-1 ,covarxy/=n-1 ;

	cov_mat[0][0]=varx , cov_mat[0][1]=covarxy;
	cov_mat[1][0]=covarxy , cov_mat[1][1]=vary;

	//printf("\nCovariance matrix\n");
	//printf("%f  %f\n",cov_mat[0][0],cov_mat[0][1]);
	//printf("%f  %f\n",cov_mat[1][0],cov_mat[1][1]);

	float a=1,b,c,eigen1,eigen2;
	b=cov_mat[0][0]+cov_mat[1][1];
	c=(cov_mat[0][0]*cov_mat[1][1])-(cov_mat[0][1]*cov_mat[1][0]);
	eigen1=(b+sqrt((b*b)-4*a*c))/2*a;
	eigen2=(b-sqrt((b*b)-4*a*c))/2*a;
	//printf("\n\nEigen values are : %f %f\n",eigen1,eigen2);

	float a_eigen1[2][2],a_eigen2[2][2];
	for(i=0;i<2;i++)
		for(j=0;j<2;j++)
		{
			a_eigen1[i][j]= i==j ? cov_mat[i][j]-eigen1 : cov_mat[i][j];
			a_eigen2[i][j]= i==j ? cov_mat[i][j]-eigen2 : cov_mat[i][j];
		}

	float rfvector1 [1][2] ,rfvector2[2][2];

	rfvector1[0][0]=sqrt((a_eigen1[0][1]*a_eigen1[0][1])/(a_eigen1[0][0]*a_eigen1[0][0] + a_eigen1[0][1]*a_eigen1[0][1]));
	rfvector1[0][1]=sqrt((a_eigen1[0][0]*a_eigen1[0][0])/(a_eigen1[0][0]*a_eigen1[0][0] + a_eigen1[0][1]*a_eigen1[0][1]));

	rfvector2[0][0]=sqrt((a_eigen1[0][1]*a_eigen1[0][1])/(a_eigen1[0][0]*a_eigen1[0][0] + a_eigen1[0][1]*a_eigen1[0][1]));
	rfvector2[0][1]=sqrt((a_eigen1[0][0]*a_eigen1[0][0])/(a_eigen1[0][0]*a_eigen1[0][0] + a_eigen1[0][1]*a_eigen1[0][1]));
	rfvector2[1][0]=sqrt((a_eigen2[0][1]*a_eigen2[0][1])/(a_eigen2[0][0]*a_eigen2[0][0] + a_eigen2[0][1]*a_eigen2[0][1]));
	rfvector2[1][1]=sqrt((a_eigen2[0][0]*a_eigen2[0][0])/(a_eigen2[0][0]*a_eigen2[0][0] + a_eigen2[0][1]*a_eigen2[0][1]));

	float t1,t2;
	t1=abs(a_eigen1[0][0]*rfvector2[0][0] + a_eigen1[0][1]*rfvector2[0][1]);
	t2=abs(a_eigen1[0][0]*rfvector2[0][0] *(-1.0)+ a_eigen1[0][1]*rfvector2[0][1]);
	if(t1>t2)
	{
		rfvector2[0][0]*=(-1.0);
		rfvector1[0][0]*=(-1.0);
	}
	t1=abs(a_eigen2[0][0]*rfvector2[1][0] + a_eigen2[0][1]*rfvector2[1][1]);
	t2=abs(a_eigen2[0][0]*rfvector2[1][0] *(-1.0)+ a_eigen2[0][1]*rfvector2[1][1]);
	if(t1>t2)  rfvector2[1][0]*=(-1.0);


	//printf("\nrfvector matrix\n");
	/*for(i=0;i<2;i++)
	{        printf("\n");
		for(j=0;j<2;j++) printf("%f  " ,rfvector2[i][j]);
	}*/

	return computeEuclideanDistance(rfvector2,vectortest);
}

void testla(int fileno){
int i ,j ,k;
      float meanx ,meany ,varx=0 ,vary=0 ,covarxy=0 ,cov_mat[3][3] ,n ;
	float sumx=0,sumy=0;
	string file;
	file.append("la/");
	file.append(1,(char)(((int)'0')+fileno));
	file.append(".txt");
    char cfile[11];
    for(j=0;j<10;++j)
    cfile[j]=file[j];
    cout<<endl;
	puts(cfile);
	//freopen("matlab output.txt","r",stdin);
	freopen(cfile,"r",stdin);
	i=0;
	while(scanf("%f %f",&x[i],&y[i])!=EOF)
	{
		sumx+=x[i];
		sumy+=y[i];
		i++;
	}

	n=(float)i;
	meanx=sumx/n;
	meany=sumy/n;

	//printf("\nmeanx   meany");
	//printf("\n%f %f\n",meanx,meany);
	for(i=0;i<n;i++)
	{
		x[i]-=meanx;
		rdata[0][i]=x[i];
		//printf("%f ",rdata[0][i]);
		y[i]-=meany;
		rdata[1][i]=y[i];
		//printf("    %f\n",rdata[1][i]);
	}

	for(i=0;i<n;i++)
	{
		varx+=x[i]*x[i];
		vary+=y[i]*y[i];
		covarxy+=x[i]*y[i];
	}

	varx/=n-1 , vary/=n-1 ,covarxy/=n-1 ;

	cov_mat[0][0]=varx , cov_mat[0][1]=covarxy;
	cov_mat[1][0]=covarxy , cov_mat[1][1]=vary;

	//printf("\n\nCovariance matrix\n");
	//printf("%f  %f\n",cov_mat[0][0],cov_mat[0][1]);
	//printf("%f  %f\n",cov_mat[1][0],cov_mat[1][1]);
	float a=1,b,c,eigen1,eigen2;
	b=cov_mat[0][0]+cov_mat[1][1];
	c=(cov_mat[0][0]*cov_mat[1][1])-(cov_mat[0][1]*cov_mat[1][0]);
	eigen1=(b+sqrt((b*b)-4*a*c))/2*a;
	eigen2=(b-sqrt((b*b)-4*a*c))/2*a;
	//printf("\n\nEigen values are : %f %f\n",eigen1,eigen2);

	float a_eigen1[2][2],a_eigen2[2][2];
	for(i=0;i<2;i++)
		for(j=0;j<2;j++)
		{
			a_eigen1[i][j]= i==j ? cov_mat[i][j]-eigen1 : cov_mat[i][j];
			a_eigen2[i][j]= i==j ? cov_mat[i][j]-eigen2 : cov_mat[i][j];
		}

	float rfvector1 [1][2] ,rfvector2[2][2];

	rfvector1[0][0]=sqrt((a_eigen1[0][1]*a_eigen1[0][1])/(a_eigen1[0][0]*a_eigen1[0][0] + a_eigen1[0][1]*a_eigen1[0][1]));
	rfvector1[0][1]=sqrt((a_eigen1[0][0]*a_eigen1[0][0])/(a_eigen1[0][0]*a_eigen1[0][0] + a_eigen1[0][1]*a_eigen1[0][1]));

	rfvector2[0][0]=sqrt((a_eigen1[0][1]*a_eigen1[0][1])/(a_eigen1[0][0]*a_eigen1[0][0] + a_eigen1[0][1]*a_eigen1[0][1]));
	rfvector2[0][1]=sqrt((a_eigen1[0][0]*a_eigen1[0][0])/(a_eigen1[0][0]*a_eigen1[0][0] + a_eigen1[0][1]*a_eigen1[0][1]));
	rfvector2[1][0]=sqrt((a_eigen2[0][1]*a_eigen2[0][1])/(a_eigen2[0][0]*a_eigen2[0][0] + a_eigen2[0][1]*a_eigen2[0][1]));
	rfvector2[1][1]=sqrt((a_eigen2[0][0]*a_eigen2[0][0])/(a_eigen2[0][0]*a_eigen2[0][0] + a_eigen2[0][1]*a_eigen2[0][1]));

	float t1,t2;
	t1=abs(a_eigen1[0][0]*rfvector2[0][0] + a_eigen1[0][1]*rfvector2[0][1]);
	t2=abs(a_eigen1[0][0]*rfvector2[0][0] *(-1.0)+ a_eigen1[0][1]*rfvector2[0][1]);
	if(t1>t2)
	{
		rfvector2[0][0]*=(-1.0);
		rfvector1[0][0]*=(-1.0);
	}
	t1=abs(a_eigen2[0][0]*rfvector2[1][0] + a_eigen2[0][1]*rfvector2[1][1]);
	t2=abs(a_eigen2[0][0]*rfvector2[1][0] *(-1.0)+ a_eigen2[0][1]*rfvector2[1][1]);
	if(t1>t2)  rfvector2[1][0]*=(-1.0);

	for(i=0;i<2;i++)
	{	for(j=0;j<2;j++) {
            vectortest[i][j]=rfvector2[i][j];
		}
	}
}

int main()
{
    int i,j,ch;
    float dist,arr[3][10];

    testab(6);
    for(i=0;i<10;i++)
    {
        dist=compareab(i);
        arr[0][i]=dist;
    }

    testlb(6);
    for(i=0;i<10;i++){
        dist=comparelb(i);
        arr[1][i]=dist;
    }

    testla(6);
    for(i=0;i<10;i++){
        dist=comparela(i);
        arr[2][i]=dist;
    }

    cout<<"\nEuclidean Distance:\n";
    cout<<"\n\nAB \t LB \t LA"<<endl;

    for(i=0;i<10;i++)
    {
        for(j=0;j<3;j++)
        {
            cout<<arr[j][i]<<"\t";
        }
        cout<<endl;
    }
    return 0;
}
