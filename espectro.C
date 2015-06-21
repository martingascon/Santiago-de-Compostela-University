{
gROOT->Reset();

#define N 8192 				       // Número máximo de Datos por Canal
//TRoot *MyRoot = new TRoot();                                                        // Número de fichero inicial
TF1 *g1 = new TF1("g1","gaus",3499,3799);                           
Float_t mean,sigma,newtrigger, dmean,dsigma,deltar,r,datos[N],x[N],y[N]; 		      
Float_t integral=0;
Int_t i,j,k,l,xini,tim,oldtim,m,m2;  
char ar[100],arch[100],title[150];
TCanvas *c = new TCanvas("c","Graph2D example",0,0,800,600);
c->Divide(1,1);
// Lectura de los archivos ***********************************************************************
m=sprintf(arch,"Cs137Co60_397V_4s_70g_120606adn.txt");  
TH1I *H = new TH1I("H",arch,8192,0,8191); 
ifstream *in = new ifstream(arch);
if(!*in) 
	{cout << " ERROR OPENING FILE " <<  arch << endl; 
	return 1;
	}
else    {i=0; 
	for (i=0;i<N;i++)
		{
		*in >> datos[i];                  
		}    
	delete in;   
	}
for (k=0;k<N;k++)
	{
	x[k]=k;                 
	y[k]=datos[k];
	H->Fill(x[k],y[k]);
	}
m2=sprintf(title,"%s",arch);
H->Rebin(8);
H->SetMarkerColor(7);
//H->SetFillColor(2);
H->SetLineColor(2);
H->SetLineWidth(1);
H->SetMarkerStyle(8);
H->SetMarkerSize(0.1);
H->SetTitle(title);
H->GetXaxis()->SetTitle("Channel");
H->GetYaxis()->SetTitle(" Counts ");
c->cd(1);
H->Fit(g1,"R");                				// fit del pico del Cesio
gStyle->SetOptFit(11);              		        // muestro los datos del Fit
mean = g1->GetParameter(1);       			// obtengo el valor x del pico
dmean =g1->GetParError(1);
sigma = g1->GetParameter(2);       			// obtengo el sigma
dsigma =g1->GetParError(2);
r = 100*(sigma*2.35/mean);        			// calculo la resolución
deltar=((235/mean)*(235/mean)*dsigma*dsigma+(235*sigma/(mean*mean))*(235*sigma/(mean*mean))*dmean*dmean);
deltar= sqrt(deltar);
TLegend *legend=new TLegend(0.64,0.61,0.99,0.66);
legend->SetTextFont(72);
legend->SetTextSize(0.03);
m=sprintf(ar,"R = (%2.2f #pm %2.2f) %%",r,deltar);  
legend->AddEntry(ar,ar,"p");
H->Draw();
legend->Draw();
return 0;
}
