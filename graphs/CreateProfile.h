#ifndef CREATEPROFILE_H_
#define CREATEPROFILE_H_

#include <string>
#include <vector>
#include <ctime>
#include <time.h>
#include <unordered_map>

#include <seqan/sequence.h>
#include <seqan/seq_io.h>
#include <seqan/file.h>
#include <seqan/translation.h> 

#include "Utils.h"

#include "ReferenceMap.h"
#include "CanonicalAntibodyGraph.h"
#include "ColorProfileMatrix.h"

#include "tests/TestCreateProfile.h"

#ifdef DEBUG
#define CREATEPROFILE_DEBUG_PRINT(EXPR) DEBUG_PRINT("[CREATE_PROFILE]", EXPR)
#else
#define CREATEPROFILE_DEBUG_PRINT(x) do {} while (0)
#endif


using namespace std;

class CreateProfile {
public:
    CreateProfile();
    CreateProfile(CanonicalAntibodyGraph *cab);
    CreateProfile(CanonicalAntibodyGraph *cab, int max_n);
    
    ColorProfileMatrix getColorProfile(string seq);

    int getProfileSize();
    //
    vector<double> getVScores() { return v_scores_; }
    vector<double> getDScores() { return d_scores_; }
    vector<double> getJScores() { return j_scores_; }
    //
    vector<string> getPredictedV();
    vector<string> getPredictedD();
    vector<string> getPredictedJ();
    //
    vector<double> getPredictedVScores();
    vector<double> getPredictedDScores();
    vector<double> getPredictedJScores();
    //
    vector<string> getVRefVect() { return (*cab_).getVRefs(); }
    vector<string> getDRefVect() { return (*cab_).getDRefs(); }
    vector<string> getJRefVect() { return (*cab_).getJRefs(); }
    //
    string getCDR3(string seq, ColorProfileMatrix &cp_mat);
    //
    pair<int,int> getPartitionV();
    pair<int,int> getPartitionD();
    pair<int,int> getPartitionJ();
    
    friend ostream& operator<< (ostream &out, CreateProfile &cp);
    
    friend class TestCreateProfile; // for unit testing

private:
    void init();

    int fillProfile(vector<string> ref_ids,
		    string seq,			       
		    int index,
		    Segment seg,
		    ColorProfileMatrix *cp);
    
    vector<string> getTopPredicted_old(int num_ret, vector<double> v, Segment seg);
    vector<string> getTopPredicted(int num_ret, vector<double> v, Segment seg);

    vector<int> getNMaxIndex(int num_ret, vector<double> &v);

    vector<double> getPredScores(int num_pred, vector<int> max_inds, vector<double> score_v);

    int n_;
    int max_report_;

    CanonicalAntibodyGraph *cab_;
    // all scores
    vector<double> v_scores_;
    vector<double> d_scores_;
    vector<double> j_scores_;
    // predicted (i.e., num_pred) scores
    vector<double> v_pred_scores_;
    vector<double> d_pred_scores_;
    vector<double> j_pred_scores_;
    // 
    vector<int> v_max_ind_;
    vector<int> d_max_ind_;
    vector<int> j_max_ind_;
};

#endif
