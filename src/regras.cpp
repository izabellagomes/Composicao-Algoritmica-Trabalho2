//	Classe com regras para contraponto - composicao dorica
//	cantus firmus: contralto
//	contraponto: soprano

#include "regras.hpp"

Regras::Regras()
{
}

vector<int> Regras::Regra1(vector<int> NotasPossiveis, int NotaPosterior)
{
	int IntervalosPossiveis[9] = {0, 1, 2, 3, 4, 5, 7, 8, 12};
	bool igual = false;

	for (unsigned int i = 0; i < NotasPossiveis.size() ; i++)
	{
		igual = false;
		for (unsigned int j = 0; j < 9; j++)
		{
			int aux = NotaPosterior - NotasPossiveis[i];
			if(aux < 0)
				aux *= -1;
			if(aux == IntervalosPossiveis[j])
			{
				igual = true;
				if (NotaPosterior - NotasPossiveis[i] == -8)
				{
					igual = false;
				}
			}
		}
		if (!igual)
		{
			NotasPossiveis.erase(NotasPossiveis.begin()+i);
			i--;
		}
	}
	return NotasPossiveis;
}

vector<int> Regras::Regra2(vector<int> NotasPossiveis, int NotaCantusFirmus)
{
	int IntervalosPossiveis[7] = {3, 4, 7, 8, 9, 12};
	bool igual = false;

	for (unsigned int i = 0; i < NotasPossiveis.size() ; ++i)
	{
		igual = false;
		for (int j = 0; j < 6; ++j)
		{
			if(NotasPossiveis[i] - NotaCantusFirmus == IntervalosPossiveis[j])
			{
				igual = true;
			}
		}
		if (!igual)
		{
			NotasPossiveis.erase(NotasPossiveis.begin()+i);
			i--;
		}
	}

	return NotasPossiveis;
}

vector<int> Regras::Regra3 (vector<int> NotasPossiveis, vector<int> LinhaMelodica,
	vector<int> CantusFirmus, int indice_cantus_firmus)
{
	bool igual = true;
	vector<int> Intervalo;

	Intervalo.push_back(-1);
	Intervalo.push_back(LinhaMelodica[indice_cantus_firmus + 1] - CantusFirmus[indice_cantus_firmus + 1]);
	Intervalo.push_back(LinhaMelodica[indice_cantus_firmus + 2] - CantusFirmus[indice_cantus_firmus + 2]);
	if(LinhaMelodica.size() > 2)
		Intervalo.push_back(LinhaMelodica[indice_cantus_firmus + 3] - CantusFirmus[indice_cantus_firmus + 3]);

	for (unsigned int i = 0; i != NotasPossiveis.size(); i++)
	{
		igual = true;
		Intervalo[0] = NotasPossiveis[i] - CantusFirmus[indice_cantus_firmus] + 1;
		if (Intervalo[1] == Intervalo[0])
		{
			if (Intervalo[0] == 7 || Intervalo[0] == 12) //7: quinta justa e 12: oitava justa
				igual = false;
			else if (Intervalo[1] == Intervalo[2])
			{
				if(Intervalo.size() > 3)
				{
					if(Intervalo[2] == Intervalo[3])
						igual = false;
				}
			}
		}
		if (!igual)
		{
			NotasPossiveis.erase(NotasPossiveis.begin()+i);
			i--;
		}
	}
	return NotasPossiveis;
}

vector<int> Regras::Regra4(vector<int> NotasPossiveis, int NotaCantusFirmus)
{
	for(unsigned int i = 0; i < NotasPossiveis.size(); i++)
	{
		if(NotasPossiveis[i] == 71 && NotaCantusFirmus != 65)
		{
			NotasPossiveis.erase(NotasPossiveis.begin()+i);
			i--;
		}
	}
	return NotasPossiveis;
}

vector<int> Regras::Regra5(vector<int> NotasPossiveis, vector<int> LinhaMelodica)
{
	for(unsigned int i = 0; i < NotasPossiveis.size(); i++)
    {
        if (NotasPossiveis[i] == 71)
        {
            int NumberofB = 0; //numero de vezes em que a nota característica apareceu
                              //nas ultimas 3 notas da melodia
            for(unsigned int i = 0; i < 3; i++)
            {
                if(LinhaMelodica[i] == 71)
                    NumberofB++;
            }
            if (NumberofB == 0)
            {
                for(unsigned int i = 0; i < NotasPossiveis.size(); i++)
                {
                    if(NotasPossiveis[i] != 71)
                    {
                        NotasPossiveis.erase(NotasPossiveis.begin()+i);
                        i--;
                    }
                }
            }
        }
    }
	return NotasPossiveis;
}

vector<int> Regras::RegraNotaInicio(vector<int> NotasPossiveis)
{
	cout << "entrou aqui" << endl;
	for(unsigned int i = 0; i < NotasPossiveis.size(); i++)
	{
		if(NotasPossiveis[i] != 62 && NotasPossiveis[i] != 65 && NotasPossiveis[i] != 69 && NotasPossiveis[i] != 74
			&& NotasPossiveis[i] != 77)
		{
			NotasPossiveis.erase(NotasPossiveis.begin()+i);
			i--;
		}
	}
	return NotasPossiveis;
}
