//

#include "contraponto_dorico.hpp"

int main()
{
	MuInit();
	
	ContrapontoDorico contraponto;

	contraponto.Run();

	return 0;

}

ContrapontoDorico::ContrapontoDorico()
{
}

void ContrapontoDorico::Run()
{

	vector<int> cantus_firmus = InitCantusFirmus();
	vector<int> melodic_line = BuildMelodicLine(cantus_firmus);

	ShowNotesOnScreen("cantus_firmus", cantus_firmus);
	ShowNotesOnScreen("melodic_line", melodic_line);

	MuMaterial cantus_firmus_material = NewMaterial(cantus_firmus);
	MuMaterial melodic_line_material = NewMaterial(melodic_line);

    MuMaterial final_material = cantus_firmus_material*melodic_line_material;
	final_material.PlaybackWithCsound("out");
}

vector<int> ContrapontoDorico::InitCantusFirmus()
{
	static const int arr[] = {62, 65, 64, 62, 67, 65, 69, 67, 65, 64, 62};
	vector<int> cantus_firmus (arr, arr + sizeof(arr) / sizeof(arr[0]) );

	return cantus_firmus;
}

vector<int> ContrapontoDorico::SopranoRange()
{
	static const int arr1[] = {60, 62, 64, 65, 67, 69, 70, 71, 72, 74, 76, 77, 79}; // extensao de notas do soprano
	vector<int> soprano_range(arr1, arr1 + sizeof(arr1) / sizeof(arr1[0]) );

	return soprano_range;
}

void ContrapontoDorico::ShowNotesOnScreen(string text, vector<int> notes)
{
	cout << endl << text << ": ";
	for (unsigned int i = 0; i < notes.size(); ++i)
		cout << notes[i] << "\t";
	cout << endl;
}

vector<int> ContrapontoDorico::ApllyRules(vector<int> possible_notes, int indice_cantus_firmus,
											vector<int> cantus_firmus, vector<int> melodic_line)
{
	Regras regras;

	possible_notes = regras.Regra1(possible_notes, melodic_line.at(0));
	possible_notes = regras.Regra2(possible_notes, cantus_firmus[indice_cantus_firmus]);
	possible_notes = regras.Regra3(possible_notes, melodic_line, cantus_firmus, indice_cantus_firmus);
	possible_notes = regras.Regra4(possible_notes, cantus_firmus[indice_cantus_firmus]);

	return possible_notes;
}

vector<int> ContrapontoDorico::ApllyFirstNoteRule(vector<int> possible_notes)
{
	Regras regras;
	cout << "ApllyFirstNoteRule" << endl;
	possible_notes = regras.RegraNotaInicio(possible_notes);
	return possible_notes;
}

vector<int> ContrapontoDorico::ApllyRule5(vector<int> melodic_line, vector<int> possible_notes)
{
	Regras regras;

	return regras.Regra5(possible_notes, melodic_line);
}

vector<int> ContrapontoDorico::BuildMelodicLine(vector<int> cantus_firmus)
{
	vector<int> melodic_line;
	vector<int> new_melodic_note;

	melodic_line.insert (melodic_line.begin(), 74);
	melodic_line.insert (melodic_line.begin(), 73);

	int actual_melodic_note_index = cantus_firmus.size()-3;
	int recursive_return;

	vector<vector<int> > possible_notes;

	for(unsigned int i = 0; i < cantus_firmus.size()-2; i++)
		possible_notes.push_back(SopranoRange());

	recursive_return = RecursiveMelodicLine(possible_notes, actual_melodic_note_index, cantus_firmus, melodic_line);
	if(!recursive_return)
	{
		cout << endl << "Nao foi possivel gerar um contraponto dorico para este cantus firmus" << endl;
		melodic_line.clear();
	}
	else
		cout << endl << "Contraponto dórico gerado com sucesso" << endl;

	return melodic_line;
}

int ContrapontoDorico::RecursiveMelodicLine(vector<vector<int> > &possible_notes, int actual_melodic_note_index,
											vector<int> cantus_firmus, vector<int> &melodic_line)
{
	unsigned int i = 0;
	if(actual_melodic_note_index == 0)
	{
		if(possible_notes[actual_melodic_note_index].empty())
		{
			actual_melodic_note_index++;
			while(i < possible_notes[actual_melodic_note_index].size()
					&& possible_notes[actual_melodic_note_index].at(i) != melodic_line.at(0))
				i++;
			if(i < possible_notes[actual_melodic_note_index].size())
				possible_notes[actual_melodic_note_index].erase(possible_notes[actual_melodic_note_index].begin()+i);
			melodic_line.erase(melodic_line.begin());
			return RecursiveMelodicLine(possible_notes, actual_melodic_note_index, cantus_firmus, melodic_line);
		}
		else
		{
			possible_notes[actual_melodic_note_index] = ApllyRules(possible_notes[actual_melodic_note_index],
														actual_melodic_note_index, cantus_firmus, melodic_line);
			if(possible_notes[actual_melodic_note_index].empty())
			{
				actual_melodic_note_index++;
				while(i < possible_notes[actual_melodic_note_index].size()
						&& possible_notes[actual_melodic_note_index].at(i) != melodic_line.at(0))
					i++;
				if(i < possible_notes[actual_melodic_note_index].size())
					possible_notes[actual_melodic_note_index].erase(possible_notes[actual_melodic_note_index].begin()+i);
				melodic_line.erase(melodic_line.begin());
				return RecursiveMelodicLine(possible_notes, actual_melodic_note_index, cantus_firmus, melodic_line);
			}
			else
			{
				possible_notes[actual_melodic_note_index] = ApllyFirstNoteRule(possible_notes[actual_melodic_note_index]);
				if (possible_notes[actual_melodic_note_index].empty())
				{
					actual_melodic_note_index++;
					while(i < possible_notes[actual_melodic_note_index].size()
							&& possible_notes[actual_melodic_note_index].at(i)!= melodic_line.at(0))
						i++;
					if(i < possible_notes[actual_melodic_note_index].size())
						possible_notes[actual_melodic_note_index].erase(possible_notes[actual_melodic_note_index].begin()+i);
					melodic_line.erase(melodic_line.begin());
					return RecursiveMelodicLine(possible_notes, actual_melodic_note_index, cantus_firmus, melodic_line);
				}
				else
				{
					melodic_line.insert (melodic_line.begin(), possible_notes[actual_melodic_note_index]
															[Between(0,possible_notes[actual_melodic_note_index].size()-1)]);
					return 1;
				}
			}
		}
	}
	else
	{
		if(actual_melodic_note_index == 8 && possible_notes[actual_melodic_note_index].empty())
		{
			return 0;
		}
		else if(possible_notes[actual_melodic_note_index].empty())
		{
			possible_notes[actual_melodic_note_index] = SopranoRange();
			actual_melodic_note_index++;
			while(i < possible_notes[actual_melodic_note_index].size()
					&& possible_notes[actual_melodic_note_index].at(i) != melodic_line.at(0))
				i++;
			if(i < possible_notes[actual_melodic_note_index].size())
				possible_notes[actual_melodic_note_index].erase(possible_notes[actual_melodic_note_index].begin()+i);
			melodic_line.erase(melodic_line.begin());
			return RecursiveMelodicLine(possible_notes, actual_melodic_note_index, cantus_firmus,
														melodic_line);
		}
		else
		{
			possible_notes[actual_melodic_note_index] = ApllyRules(possible_notes[actual_melodic_note_index],
														actual_melodic_note_index, cantus_firmus, melodic_line);
			if(actual_melodic_note_index < 8)
				possible_notes[actual_melodic_note_index] = ApllyRule5(melodic_line, possible_notes[actual_melodic_note_index]);
			if(possible_notes[actual_melodic_note_index].empty())
			{
				possible_notes[actual_melodic_note_index] = SopranoRange();
				actual_melodic_note_index++;
				i = 0;
				while(i < possible_notes[actual_melodic_note_index].size()
						&& possible_notes[actual_melodic_note_index].at(i) != melodic_line.at(0))
					i++;
				if(i < possible_notes[actual_melodic_note_index].size())
					possible_notes[actual_melodic_note_index].erase(possible_notes[actual_melodic_note_index].begin()+i);
				melodic_line.erase(melodic_line.begin());
				return RecursiveMelodicLine(possible_notes, actual_melodic_note_index, cantus_firmus,
														melodic_line);
			}
			else
			{
				melodic_line.insert (melodic_line.begin(), possible_notes[actual_melodic_note_index]
														[Between(0,possible_notes[actual_melodic_note_index].size()-1)]);
				actual_melodic_note_index--;
				return RecursiveMelodicLine(possible_notes, actual_melodic_note_index, cantus_firmus, melodic_line);
			}
		}
	}
}

MuNote ContrapontoDorico::NewNote(int instr, float start, float dur, int pitch, float amp)
{
	MuNote note;

	note.SetInstr(instr);
	note.SetStart(start);
	note.SetDur(dur);
	note.SetPitch(pitch);
	note.SetAmp(amp);

	return note;
}

MuMaterial ContrapontoDorico::NewMaterial(vector<int> notes)
{
	MuMaterial material;

	material.Clear();

	for (unsigned int i = 0; i < notes.size(); i++)
	{
		material += NewNote(1, i * 1.2, 1.2, notes[i], 0.7);
	}
	return material;
}
