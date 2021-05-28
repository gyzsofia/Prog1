// frakszal.cpp
//
// Mandelbrot halmaz rajzol
// Programoz Pternoszter
//
// Copyright (C) 2011, Btfai Norbert, nbatfai@inf.unideb.hu, nbatfai@gmail.com
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// Ez a program szabad szoftver; terjeszthet illetve mdosthat a
// Free Software Foundation ltal kiadott GNU General Public License
// dokumentumban lertak; akr a licenc 3-as, akr (tetszleges) ksbbi
// vltozata szerint.
//
// Ez a program abban a remnyben kerl kzreadsra, hogy hasznos lesz,
// de minden egyb GARANCIA NLKL, az ELADHATSGRA vagy VALAMELY CLRA
// VAL ALKALMAZHATSGRA val szrmaztatott garancit is belertve.
// Tovbbi rszleteket a GNU General Public License tartalmaz.
//
// A felhasznlnak a programmal egytt meg kell kapnia a GNU General
// Public License egy pldnyt; ha mgsem kapta meg, akkor
// tekintse meg a <http://www.gnu.org/licenses/> oldalon.
//
//
// Version history:
//
// 0.0.1    Br a Nokia Qt SDK ppen tartalmaz egy Mandelbrotos pldt, de
// ezt nem tartottam megfelelnek els Qt programknt ajnlani, mert elg
// bonyolult: hasznl klcsns kizrst stb. Ezrt "from scratch" megrtam
// egy sajtot a Javt tantokhoz rt dallamra:
// http://www.tankonyvtar.hu/informatika/javat-tanitok-2-2-080904-1
//

#include "frakszal.h"

FrakSzal::FrakSzal(double a, double b, double c, double d,
                   int szelesseg, int magassag, int iteraciosHatar, FrakAblak *frakAblak)
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    this->szelesseg = szelesseg;
    this->iteraciosHatar = iteraciosHatar;
    this->frakAblak = frakAblak;
    this->magassag = magassag;

    egySor = new int[szelesseg];
}

FrakSzal::~FrakSzal()
{
    delete[] egySor;
}

// A szl kdjt a Javt tantokhoz rt Java kdombl vettem t
// http://www.tankonyvtar.hu/informatika/javat-tanitok-2-2-080904-1
// mivel itt az algoritmust is lertam/lerajzoltam, gy meghagytam
// a kommenteket, hogy a hallgat knnyen hozzolvashassa az "elmletet",
// ha rdekli.
void FrakSzal::run()
{
    // A [a,b]x[c,d] tartomnyon milyen sr a
    // megadott szlessg, magassg hl:
    double dx = (b-a)/szelesseg;
    double dy = (d-c)/magassag;
    double reC, imC, reZ, imZ, ujreZ, ujimZ;
    // Hny itercit csinltunk?
    int iteracio = 0;
    // Vgigzongorzzuk a szlessg x magassg hlt:
    for(int j=0; j<magassag; ++j) {
        //sor = j;
        for(int k=0; k<szelesseg; ++k) {
            // c = (reC, imC) a hl rcspontjainak
            // megfelel komplex szm
            reC = a+k*dx;
            imC = d-j*dy;
            // z_0 = 0 = (reZ, imZ)
	    std::complex<double> c(reC, imC);
	    
            reZ = 0;
            imZ = 0;	    
	    std::complex<double> z_n(reZ, imZ);
            iteracio = 0;
            // z_{n+1} = z_n * z_n + c itercik
            // szmtsa, amg |z_n| < 2 vagy mg
            // nem rtk el a 255 itercit, ha
            // viszont elrtk, akkor gy vesszk,
            // hogy a kiindulci c komplex szmra
            // az iterci konvergens, azaz a c a
            // Mandelbrot halmaz eleme
	    /*
            while(reZ*reZ + imZ*imZ < 4 && iteracio < iteraciosHatar) {
                // z_{n+1} = z_n * z_n + c

	      ujreZ = reZ*reZ+ std::atan(reZ*reZ - imZ*imZ) + std::sqrt(reC);
	      ujimZ = 2*reZ*imZ+std::atan(2*reZ*imZ) + imC;

                reZ = ujreZ;
                imZ = ujimZ;

                ++iteracio;

            }
            */
	    while( std::abs(z_n) < 4 && iteracio < iteraciosHatar) {
	      z_n = z_n  * z_n + c;
	      
	      ++iteracio;
	    }  
	      
            // ha a < 4 felttel nem teljeslt s a
            // iterci < itercisHatr srlsvel lpett ki, azaz
            // feltesszk a c-rl, hogy itt a z_{n+1} = z_n * z_n + c
            // sorozat konvergens, azaz iterci = itercisHatr
            // ekkor az iterci %= 256 egyenl 255, mert az esetleges
            // nagytasok sorn az iterci = valahny * 256 + 255

            iteracio %= 256;

            //a sznezst viszont mr majd a FrakAblak osztlyban lesz
            egySor[k] = iteracio;
        }
        // brzolsra tadjuk a kiszmolt sort a FrakAblak-nak.
        frakAblak->vissza(j, egySor, szelesseg);
    }
    frakAblak->vissza();

}

