#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


double poisson(double mu, int k) {
  return (pow(mu, k) * exp(-mu)) / tgamma(k + 1);
}

int main() {
    using namespace std;
    const double mu = 3.11538;
    vector<int> zaehler(11);

    ifstream fin("datensumme.txt");
    int n_i;
    int dataSize = 0;
    while(fin >> n_i) {
        zaehler[n_i]++;
        dataSize++;
    }
    fin.close();

    ofstream outhist("hist.txt");
    ofstream outhistpoi("histpoi.txt");
    for(unsigned int k = 0; k < zaehler.size(); k++){
      cout << k << ":" << zaehler[k] << endl;
      outhist << k << " " << zaehler[k] << endl;
      outhistpoi << k << " " << zaehler[k] << " " << dataSize*poisson(mu, k) << endl;
    }
    outhist.close();
    outhistpoi.close();
}