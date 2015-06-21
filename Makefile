#--------------------------------------Makefile de Martin ----------------------------------------
#----------------------------------------------- declaración de variables------------------------------------------------------------
20xygrafwerr = 20xygrafwerr.cc
4xgraf = 4xgraf.cc
ajurepresent2 = ajurepresent2.cc
ajurepresent = ajurepresent.cc
bin2asc = bin2asc.cc
browser = browser.cc
chToHV = chToHV.cc
5xchToHV = 5xchToHV.cc
5xchToR = 5xchToR.cc
5xshapToR = 5xshapToR.cc
5xenerToR = 5xenerToR.cc
5xenerToR2 = 5xenerToR2.cc
calibration = calibration.cc
chToR = chToR.cc
chToR3 = chToR3.cc
chToTi = chToTi.cc
dxygraf2 = dxygraf2.cc
dxygraf = dxygraf.cc
dxygrafwerr = dxygrafwerr.cc
enerToR = enerToR.cc
espectro = espectro.cc
espectro_lu = espectro_lu.cc
espectro_lar = espectro_lar.cc
espectrop = espectrop.cc
espectro_m = espectro_m.cc
espectro2 = espectro2.cc
espectromult = espectromult.cc
espectro2mult = espectro2mult.cc
espectro3 = espectro3.cc
espectro4 = espectro4.cc
espectro5 = espectro5.cc
espectro6 = espectro6.cc
espectro3x = espectro3x.cc
gainToCH = gainToCH.cc
gainToR = gainToR.cc
graf = graf.cc
juntar = juntar.cc
ivshv4x = ivshv4x.cc
mca_gaus = mca_gaus.cc
mca_lineal = mca_lineal.cc
mca_expo = mca_expo.cc
mca_expo2 = mca_expo2.cc
mca_expo3 = mca_expo3.cc
nonUnifR = nonUnifR.cc
nonUnif = nonUnif.cc
nonUnifCH = nonUnifCH.cc
nonUnifCH3se = nonUnifCH3se.cc
nrepresent = nrepresent.cc
nseries = nseries.cc
rangoDin = rangoDin.cc
represent = represent.cc
resta = resta.cc
shapToR = shapToR.cc
suma2 = suma2.cc
suma = suma.cc
sumar = sumar.cc
sumarSi2 = sumarSi2.cc
sumarSi = sumarSi.cc
spectrum = spectrum.cc
spectrumx4 = spectrumx4.cc
spectrum12 = spectrum12.cc
temp = temp.cc
temp2 = temp2.cc
timeToR = timeToR.cc
tree = tree.cc
txygraf = txygraf.cc
txygrafwerr = txygrafwerr.cc
xgraf = xgraf.cc
xygraf = xygraf.cc
xygraf2 = xygraf2.cc
xygrafwerr2 = xygrafwerr2.cc
xygrafwerr = xygrafwerr.cc
yoko_hist2x_co = yoko_hist2x_co.cc
yoko_csv2txt1x = yoko_csv2txt1x.cc
yoko_csv2txt2x = yoko_csv2txt2x.cc
yoko_csv2txt3x = yoko_csv2txt3x.cc
yoko_csv2txt4x = yoko_csv2txt4x.cc
yoko_histo1x = yoko_histo1x.cc
yoko_histo2x = yoko_histo2x.cc
yoko_histo2xsi = yoko_histo2xsi.cc
yoko_histo4x = yoko_histo4x.cc
yoko_pulso2x = yoko_pulso2x.cc
yoko_pulso2xb = yoko_pulso2xb.cc
yoko_pulso4x = yoko_pulso4x.cc
yoko_xFIR2x = yoko_xFIR2x.cc
yoko_xFIR2xsim = yoko_xFIR2xsim.cc
yoko_xFIR4x = yoko_xFIR4x.cc

#FLAGS = -O2 -Wall -fPIC -pthread  -I/home/martin/root/include -L/home/martin/root/lib -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -#lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lGui -pthread -lm -ldl -rdynamic

#*************************************************** FLAG DEFINITION ****************************************
LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
   # do 64 bit stuff here, like set some CFLAGS
FLAGS = -O2 -Wall -fPIC -pthread  -I/usr/local/root/new/include -L/usr/local/root/new/lib -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lGui -pthread -lm -ldl -rdynamic 
else
   # do 32 bit stuff here
FLAGS = -O2 -Wall -fPIC -pthread  -I/usr/local/root/new/include -L/usr/local/root/new/lib -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lGui -pthread -lm -ldl -rdynamic 
endif
#*************************************************** Compilation ****************************************



#----------------------------------------------- procesos  ------------------------------------------------------------


all:           20xygrafwerr dxygraf graf shapToR txygraf ajurepresent2 dxygrafwerr juntar suma2 txygrafwerr ajurepresent\
               espectro2 suma xgraf bin2asc espectro3 sumar xygraf chToR2 sumarSi2 xygrafwerr2 chToR3 espectro nonUnif\
	       sumarSi xygrafwerr chToTi gainToCH nrepresent timeToR3 dxygraf2 gainToR represent tree 


20xygrafwerr:  $(20xygrafwerr) 
		g++  $(FLAGS) -o ../20xygrafwerr $(20xygrafwerr) 

4xgraf:  $(4xgraf) 
		g++  $(FLAGS) -o ../4xgraf $(4xgraf) 

ajurepresent2:	$(ajurepresent2)
		g++ $(FLAGS) -o ../ajurepresent2 $(ajurepresent2)


ajurepresent:	$(ajurepresent)
		g++ $(FLAGS) -o ../2ajurepresent $(ajurepresent)


bin2asc:	$(bin2asc)
		g++ $(FLAGS) -o ../bin2asc $(bin2asc)

browser:	$(browser)
		g++ $(FLAGS) -o ../browser $(browser)

chToHV:		$(chToHV)
		g++ $(FLAGS) -o ../chToHV $(chToHV)

5xchToHV:	$(5xchToHV)
		g++ $(FLAGS) -o ../5xchToHV $(5xchToHV)

5xchToR:	$(5xchToR)
		g++ $(FLAGS) -o ../5xchToR $(5xchToR)

5xshapToR:	$(5xshapToR)
		g++ $(FLAGS) -o ../5xshapToR $(5xshapToR)


5xenerToR:	$(5xenerToR)
		g++ $(FLAGS) -o ../5xenerToR $(5xenerToR)

5xenerToR2:	$(5xenerToR2)
		g++ $(FLAGS) -o ../5xenerToR2 $(5xenerToR2)

calibration:	$(calibration)
		g++ $(FLAGS) -o ../calibration $(calibration)

chToR:		$(chToR)
		g++ $(FLAGS) -o ../chToR $(chToR)

chToR3:		$(chToR3)
		g++ $(FLAGS) -o ../chToR3 $(chToR3)


chToTi:		$(chToTi)
		g++ $(FLAGS) -o ../chToTi $(chToTi)


dxygraf2:	$(dxygraf2)
		g++ $(FLAGS) -o ../dxygraf2 $(dxygraf2)


dxygraf:	$(dxygraf)
		g++ $(FLAGS) -o ../dxygraf $(dxygraf)

dxygrafwerr:	$(dxygrafwerr)
		g++ $(FLAGS) -o ../dxygrafwerr $(dxygrafwerr)

enerToR:	$(enerToR)
		g++ $(FLAGS) -o ../enerToR $(enerToR)

espectro:	$(espectro)
		g++ $(FLAGS) -o ../espectro $(espectro)

espectro_lu:	$(espectro_lu)
		g++ $(FLAGS) -o ../espectro_lu $(espectro_lu)

espectro_lar:	$(espectro_lar)
		g++ $(FLAGS) -o ../espectro_lar $(espectro_lar)

espectrop:	$(espectrop)
		g++ $(FLAGS) -o ../espectrop $(espectrop)


espectro_m:	$(espectro_m)
		g++ $(FLAGS) -o ../espectro_m $(espectro_m)

espectro2:	$(espectro2)
		g++ $(FLAGS) -o ../espectro2 $(espectro2)

espectromult:	$(espectromult)
		g++ $(FLAGS) -o ../espectromult $(espectromult)

espectro2mult:	$(espectro2mult)
		g++ $(FLAGS) -o ../espectro2mult $(espectro2mult)

espectro3:	$(espectro3)
		g++ $(FLAGS) -o ../espectro3 $(espectro3)

espectro3x:	$(espectro3x)
		g++ $(FLAGS) -o ../espectro3x $(espectro3x)

espectro4:	$(espectro4)
		g++ $(FLAGS) -o ../espectro4 $(espectro4)


espectro5:	$(espectro5)
		g++ $(FLAGS) -o ../espectro5 $(espectro5)

espectro6:	$(espectro6)
		g++ $(FLAGS) -o ../espectro6 $(espectro6)


gainToCH:	$(gainToCH)
		g++ $(FLAGS) -o ../gainToCH $(gainToCH)

gainToR:	$(gainToR)
		g++ $(FLAGS) -o ../gainToR $(gainToR)


graf:		$(graf)
		g++ $(FLAGS) -o ../graf $(graf)

juntar:		$(juntar)
		g++ $(FLAGS) -o ../juntar $(juntar)

ivshv4x:	$(ivshv4x)
		g++ $(FLAGS) -o ../ivshv4x $(ivshv4x)

mca_gaus:	$(mca_gaus)
		g++ $(FLAGS) -o ../mca_gaus $(mca_gaus)

mca_lineal:	$(mca_lineal)
		g++ $(FLAGS) -o ../mca_lineal $(mca_lineal)

mca_expo:	$(mca_expo)
		g++ $(FLAGS) -o ../mca_expo $(mca_expo)

mca_expo2:	$(mca_expo2)
		g++ $(FLAGS) -o ../mca_expo2 $(mca_expo2)

mca_expo3:	$(mca_expo3)
		g++ $(FLAGS) -o ../mca_expo3 $(mca_expo3)

nonUnifR:	$(nonUnifR)
		g++ $(FLAGS) -o ../nonUnifR $(nonUnifR)

nonUnif:	$(nonUnif)
		g++ $(FLAGS) -o ../nonUnif $(nonUnif)

nonUnifCH:	$(nonUnifCH)
		g++ $(FLAGS) -o ../nonUnifCH $(nonUnifCH)

nonUnifCH3se:	$(nonUnifCH3se)
		g++ $(FLAGS) -o ../nonUnifCH3se $(nonUnifCH3se)

nrepresent:	$(nrepresent)
		g++ $(FLAGS) -o ../nrepresent $(nrepresent)

nseries:	$(nseries)
		g++ $(FLAGS) -o ../nseries $(nseries)

rangoDin:	$(rangoDin)
		g++ $(FLAGS) -o ../rangoDin $(rangoDin)

represent:	$(represent)
		g++ $(FLAGS) -o ../represent $(represent)

resta:		$(resta)
		g++ $(FLAGS) -o ../resta $(resta)

spectrum:	$(spectrum)
		g++ $(FLAGS) -o ../spectrum $(spectrum)

spectrumx4:	$(spectrumx4)
		g++ $(FLAGS) -o ../spectrumx4 $(spectrumx4)

spectrum12:	$(spectrum12)
		g++ $(FLAGS) -o ../spectrum12 $(spectrum12)

shapToR:	$(shapToR)
		g++ $(FLAGS) -o ../shapToR $(shapToR)

suma2:		$(suma2)
		g++ $(FLAGS) -o ../suma2 $(suma2)

suma:		$(suma)
		g++ $(FLAGS) -o ../suma $(suma)

sumar:		$(sumar)
		g++ $(FLAGS) -o ../sumar $(sumar)

sumarSi2:	$(sumarSi2)
		g++ $(FLAGS) -o ../sumarSi2 $(sumarSi2)

sumarSi:	$(sumarSi)
		g++ $(FLAGS) -o ../sumarSi $(sumarSi)

spectrum:	$(spectrum)
		g++ $(FLAGS) -o ../spectrum $(spectrum)

spectrumx4:	$(spectrumx4)
		g++ $(FLAGS) -o ../spectrumx4 $(spectrumx4)


spectrumxn:	$(spectrumxn)
		g++ $(FLAGS) -o ../spectrumxn $(spectrumxn)

temp:		$(temp)
		g++ $(FLAGS) -o ../temp $(temp)

temp2:		$(temp2)
		g++ $(FLAGS) -o ../temp2 $(temp2)

timeToR:	$(timeToR)
		g++ $(FLAGS) -o ../timeToR $(timeToR)


tree:		$(tree)
		g++ $(FLAGS) -o ../tree $(tree)

txygraf:	$(txygraf)
		g++ $(FLAGS) -o ../txygraf $(txygraf)

txygrafwerr:	$(txygrafwerr)
		g++ $(FLAGS) -o ../txygrafwerr $(txygrafwerr)

xgraf:		$(xgraf)
		g++ $(FLAGS) -o ../xgraf $(xgraf)

xygraf:		$(xygraf)
		g++ $(FLAGS) -o ../xygraf $(xygraf)


xygraf2:	$(xygraf2)
		g++ $(FLAGS) -o ../xygraf2 $(xygraf2)

xygrafwerr2:	$(xygrafwerr2)
		g++ $(FLAGS) -o ../xygrafwerr2 $(xygrafwerr2)

xygrafwerr:	$(xygrafwerr)
		g++ $(FLAGS) -o ../xygrafwerr $(xygrafwerr)

yoko_hist2x_co:	$(yoko_hist2x_co)
		g++ $(FLAGS) -o ../yoko_hist2x_co $(yoko_hist2x_co)	

yoko_csv2txt1x:	$(yoko_cs2vtxt1x)
		g++ $(FLAGS) -o ../yoko_csv2txt1x $(yoko_csv2txt1x)		

yoko_csv2txt2x:	$(yoko_cs2vtxt2x)
		g++ $(FLAGS) -o ../yoko_csv2txt2x $(yoko_csv2txt2x)

yoko_csv2txt3x:	$(yoko_cs2vtxt3x)
		g++ $(FLAGS) -o ../yoko_csv2txt3x $(yoko_csv2txt3x)

yoko_csv2txt4x:	$(yoko_cs2vtxt4x)
		g++ $(FLAGS) -o ../yoko_csv2txt4x $(yoko_csv2txt4x)

yoko_histo1x:	$(yoko_histo1x)
		g++ $(FLAGS) -o ../yoko_histo1x $(yoko_histo1x)

yoko_histo2x:	$(yoko_histo2x)
		g++ $(FLAGS) -o ../yoko_histo2x $(yoko_histo2x)

yoko_histo2xsi:	$(yoko_histo2xsi)
		g++ $(FLAGS) -o ../yoko_histo2xsi $(yoko_histo2xsi)

yoko_histo4x:	$(yoko_histo4x)
		g++ $(FLAGS) -o ../yoko_histo4x $(yoko_histo4x)

yoko_pulso2x:	$(yoko_pulso2x)
		g++ $(FLAGS) -o ../yoko_pulso2x $(yoko_pulso2x)

yoko_pulso2xb:	$(yoko_pulso2xb)
		g++ $(FLAGS) -o ../yoko_pulso2xb $(yoko_pulso2xb)

yoko_pulso4x:	$(yoko_pulso4x)
		g++ $(FLAGS) -o ../yoko_pulso4x $(yoko_pulso4x)

yoko_xFIR2x:	$(yoko_xFIR2x)
		g++ $(FLAGS) -o ../yoko_xFIR2x $(yoko_xFIR2x)

yoko_xFIR2xsim:	$(yoko_xFIR2xsim)
		g++ $(FLAGS) -o ../yoko_xFIR2xsim $(yoko_xFIR2xsim)

yoko_xFIR4x:	$(yoko_xFIR4x)
		g++ $(FLAGS) -o ../yoko_xFIR4x $(yoko_xFIR4x)

#--------aqui se agregarán nuevos procesos --------------- fin: Nota: La proxima vez, no hacer caso a David.....
























