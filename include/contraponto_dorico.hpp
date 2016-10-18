// Classe para contrucao e execucao de contraponto - composicao dorica

#ifndef MUM_CONTRAPONTO_H_
#define MUM_CONTRAPONTO_H_

#include "regras.hpp"

class ContrapontoDorico
{
  public:
    ContrapontoDorico();
    void Run();

  protected:
    vector<int> InitCantusFirmus();
    vector<int> SopranoRange();
    void ShowNotesOnScreen(string text, vector<int> notes);
    vector<int> ApllyRules(vector<int> possible_notes, int indice_cantus_firmus,
                            vector<int> cantus_firmus, vector<int> melodic_line);
    vector<int> ApllyFirstNoteRule(vector<int> possible_notes);
    vector<int> ApllyRule5(vector<int> melodic_line, vector<int> possible_notes);
    vector<int> BuildMelodicLine(vector<int> cantus_firmus);
    int RecursiveMelodicLine(vector<vector<int> > &possible_notes, int actual_melodic_note_index,
                              vector<int> cantus_firmus, vector<int> &melodic_line);

    //criar classe MuMiteis pra colocar esses metodos
    MuNote NewNote(int instr, float start, float dur, int pitch, float amp);
    MuMaterial NewMaterial(vector<int> notes);
};

#endif  // MUM_CONTRAPONTO_H_