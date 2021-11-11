#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

double Poisson(double mu, int k) {
  return pow(mu, k) * exp(-mu) / tgamma(k + 1);
}

double Prob(vector<int> daten, double mu) {
  double likelihood = 1;
  for(int k : daten) {
    likelihood *= pow(mu, daten[k]) * exp(-mu) / tgamma(daten[k] + 1);
  }
  return likelihood;
}

void GenerateData(vector<int> &data) {
  ifstream fin("datensumme.txt");
    int n_i;
    while(fin >> n_i) {
        data[n_i]++;
    }
    fin.close();
}

void GenerateHistos(vector<int> &data, double mu, int N) {
  ofstream outhist("hist.txt");
  ofstream outhistpoi("histpoi.txt");
  for(unsigned int k = 0; k < data.size(); k++){
    cout << k << ":" << data[k] << endl;
    outhist << k << " " << data[k] << endl;
    outhistpoi << k << " " << data[k] << " " << N * Poisson(mu, k) << endl;
  }
  outhist.close();
  outhistpoi.close();
}

int main() {
  const double kMu = 3.11538;
  const int kN = 234;

  vector<int> zaehler(11);
  GenerateData(zaehler);
  GenerateHistos(zaehler, kmu, kN);

  vector<int> daten;
  ifstream fin("datensumme.txt");
  int x;
  while(fin >> x) {
      daten.push_back(x);
  }
  fin.close();
  
  cout << Prob(daten, kmu) << endl;

  ofstream outprob("likelihood.txt");
  for(double mu = 0; mu <= 6; mu += 0.1) {
    outprob << mu << " " << Prob(daten, mu) << endl;
  }
  outprob.close();
}