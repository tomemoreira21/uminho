int fact(int n) { 
  int r = 1;

  while (n != 0) r*= n--;

  return r;
}

double pot(double x, int n) {
  double p = 1;
  
  for (int i = 0; i < n; i++) p *= x;
  
  return p;
}

double serie(double x, int n) {
  double r = 0,valor; 

  for (int i = 0; i <= n; i++) {
      valor = (fact (2*i) / (pot (4,i) * (pot (fact (i),2)) * (2*i+1))) * pot (x,2*i+1);
      r += valor; 
  }

  return r;
 }

// Resposta à penúltima do Guião
/*
Expansão em série de Taylor da função arcsen(x) 

A tolerância muda porque a precisão da série varia com xx e o número de termos usados.
Pequenos valores de x convergem rápido → tolerância menor (mais precisa).
Grandes valores de x convergem mais devagar → tolerância maior (mais erro).
*/
