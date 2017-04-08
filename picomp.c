#include "stdio.h"
#include "math.h"

double fat (int n)
{int i;
 double ff=1;

  for (i=2; i<=n; i++)
    ff = ff*i;
  return(ff);
}

double hfat (int n)
{int i;
 double ff=n;

  for (i=n-1; i>n/2; i--)
    ff = ff*i;
  return(ff);
}

double nilak(int n, double pi)
{double term, signal;

  term = 2*(n+1); if (n%2) signal = -4; else signal = +4;
  pi = pi + signal/(term*(term+1)*(term+2));
//  printf("after %ld pi is %.15lf\n",n,pi);
  return (pi);
}

double leib(int n, double pi)
{double term, signal;

  term = 2*n+1; if (n%2) signal = -4; else signal = +4;
  pi = pi + signal/term;
  return (pi);
}


double newt(int n, double pi)
{double term, signal;

//  term = hfat(2*n)/(fat(n)*(2*n-1)*(2*n+3)*pow(2,4*n+2));
  term = fat(2*n)/(fat(n)*fat(n)*(2*n-1)*(2*n+3)*pow(2,4*n+2));
  pi = pi - 24*term;
  return (pi);
}

main()
{double pileib=0, pinewt, pinila=3;
 long int i;
 
  pinewt = 0.75*sqrt(3);
  puts(" Iter |     Leibnitz      |      Newton      |     Nilakantha ");
  for (i=0; i<21; i++)
  { pileib = leib(i,pileib);
    pinewt = newt(i,pinewt);
    pinila = nilak(i,pinila);
    printf("  %2ld  | %.15lf | %.15lf | %.15lf\n",i,pileib,pinewt,pinila);
  }
//  printf("pi is %.15lf\n",pi);
}


