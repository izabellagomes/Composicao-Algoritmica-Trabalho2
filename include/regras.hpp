// Classe com regras para contraponto - composicao dorica

#ifndef MUM_REGRAS_H_
#define MUM_REGRAS_H_

#include "MuMaterial.hpp"
#include "conversor.hpp"

class Regras
{
  public:
  	Regras();
  	vector<int> Regra1(vector<int> NotasPossiveis, int NotaPosterior);
  	vector<int> Regra2(vector<int> NotasPossiveis, int NotaCantusFirmus);
  	vector<int> Regra3 (vector<int> NotasPossiveis, vector<int> LinhaMelodica, vector<int> CantusFirmus,
                        int indice_cantus_firmus);
  	vector<int> Regra4(vector<int> NotasPossiveis, int NotaCantusFirmus);
    vector<int> Regra5(vector<int> NotasPossiveis, vector<int> LinhaMelodica);
  	vector<int> RegraNotaInicio(vector<int> NotasPossiveis);

  protected:
  	
};

#endif  // MUM_REGRAS_H_