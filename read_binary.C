//Program for analysis of RPC signals
Int_t main()
{
  //Scope Parameters read from WFD file
  //Float_t xzero=1.433e-9;
  Float_t xzero=0;
  //Float_t xinc=2.0e-9;
  Float_t xinc=1;
  //Float_t pt_of=1920;
  Float_t pt_of=0;
  //Float_t yzero=0.;
  Float_t yzero=0.;
  //Float_t ymult=20e-3;
  //Float_t y_of=50.0;
  Float_t ymult=1;
  Float_t y_of=0;
  //X and Y values
  Float_t X=0;
  Float_t Y=0;
  ifstream *f = new ifstream("datos.dat",
			     ios::in | ios::binary);  
  Int_t n = readHeader(f);
  TH1F *signal = new TH1F("signal","RPC signal",n,CalculateX(xzero,xinc,pt_of,0),CalculateX(xzero,xinc,pt_of,n));
  cout <<n<<" points in scope"<<endl;
  Char_t *buf = new Char_t[n];
  f->read(buf,n);
  Int_t dummy=0;
  for(Int_t j=0;j<n;j++)
    {
      X=CalculateX(xzero,xinc,pt_of,j);
      dummy = *(buf+j);
      Y=CalculateY(yzero,ymult,y_of,dummy);
      //signal->Fill(X,Y);
      signal->Fill(X,dummy);
      cout<<X<<"\t"<<dummy<<endl;
    }
  signal->Draw();
  return 0;
}
Int_t readHeader(ifstream* file)
{
  Int_t j;
  char dumm;
  //cout << "DeCODING 2   " << endl;
  *file >> dumm;	//cout << dumm;
  
  *file >> dumm;	//cout << dumm;
  
  Int_t trueNum= atoi(&dumm);
  
  char* laenge = new char[trueNum];
  for(j=0; j<trueNum; j++)
    {
      *file >> dumm;
      //cout << dumm;
      laenge[j]=dumm;
    }
  laenge[j+1]=(char) '\0';
  
  int numbertoread = atoi(laenge);
  
  //  cout << "   DeCODING 2" << endl;
 
  return numbertoread;
  
}
Float_t CalculateX(Float_t XZEro,Float_t XINcr,Float_t PT_OFf,Int_t n)
{
  Float_t X = XZEro+XINcr*(n-PT_OFf);
  return X;
}
Float_t CalculateY(Float_t YZEro,Float_t YMUlty,Float_t YOFf,Char_t y)
{
  Float_t Y = YZEro+YMUlty*(y-YOFf);
  return Y;
}
