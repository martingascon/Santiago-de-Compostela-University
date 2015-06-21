//Macro for plotting signals from Yokogawa scope

void macro(Char_t *file_name){
  Float_t y0;
  Float_t y1; 
  ifstream *input=new ifstream(file_name);
  TH1F *h1=new TH1F("h1","Ch1",2500,0,2500);
  TH1F *h2=new TH1F("h2","Ch2",2500,0,2500);
  Char_t buf[256];
  //*input>>buf;
  input->getline(buf,256);
  cout<<buf<<endl;
  //Int_t j=0;
  for(Int_t j=0;j<2500;j++){
    //  while(!input->eof()){
    *input>>y0>>y1;
    //cout<<y0<<endl;
    h1->SetBinContent(j,y0);
    h2->SetBinContent(j,y1);
    //j++;
  }
  input->getline(buf,256);
  cout<<buf<<endl;
  h1->Draw();
  h2->SetLineColor(2);
  h2->Draw("same");
  return;
}
