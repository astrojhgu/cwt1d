#include <iostream>
#include <fstream>
#include <fio.h>
#include "cwt1d.hpp"
#include "cwt1d_wavelets.hpp"
#include <cstdlib>
using namespace std;
using namespace cwt1d;
using namespace fftw_blitz;
int main()
{
  //dog<float> d(6);
  //hermitian_hat<float> d;
  //morlet<float> d(15);
  paul<float> d;
  cout<<d.cone_of_influence_factor()<<endl; 
  blitz::Array<float,1> signal(1024);
  ofstream ofs("a.dat");
  for(int i=0;i<signal.extent(0);++i)
    {
      //signal(i)=rand()/(float)RAND_MAX-.5;
      signal(i)=i==signal.extent(0)/2;
      ofs<<signal(i)<<endl;
      //signal(i)=cos(i/16.);
      //signal(i)=2*i;
      //signal(i)=exp(-(i-240)*(i-240)/15./15./2.);
    }
  
  blitz::Array<float,1> scales(1024);

  for(int i=0;i<scales.extent(0);++i)
    {
      scales(i)=pow(2.,log(1024.)/log(2)*i/scales.extent(0))/2;
      //scales(i)=(i+1)/32.;
    }
  blitz::Array<complex<float>,2> signal_cwt(cwt(signal,scales,d));
  blitz::Array<float,1> signal_rec(icwt(signal_cwt,scales,d));
  float norm=calc_norm(signal.extent(0),scales,d);
  for(int i=0;i<signal.extent(0);++i)
    {
      //cout<<i<<"\t"<<signal(i)<<"\t"<<signal_rec(i)/norm<<endl;
    }

  blitz::Array<float,2> mx(signal_cwt.shape());
  for(int i=0;i<mx.extent(0);++i)
    {
      for(int j=0;j<mx.extent(1);++j)
	{
	  mx(i,j)=abs(signal_cwt(i,j));
	  //mx(i,j)=(signal_cwt(i,j).real());
	}
    }
  cfitsfile ff;
  ff.create("a.fits");
  ff<<mx;
}
