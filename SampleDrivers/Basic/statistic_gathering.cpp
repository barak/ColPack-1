

#include "ColPackHeaders.h"
#include "stat.h"

using namespace ColPack;
using namespace std;

#ifndef TOP_DIR
#define TOP_DIR "."
#endif

// baseDir should point to the directory (folder) containing the input file
string baseDir=TOP_DIR;

int f (string s_InputFile);

//*	A SHORT VERSION
int main(int argc, char ** argv) {

	// s_InputFile = baseDir + <name of the input file>
	string s_InputFile; //path of the input file
	s_InputFile = "/home/nguyend/Desktop/Working_U/research_Assefaw/ColPack/Graphs/bcsstk01.mtx";

	// Step 1: Determine sparsity structure of the Jacobian.
	// This step is done by an AD tool. For the purpose of illustration here, we read the structure from a file,
	// and store the structure in a Compressed Row Format.
	unsigned int *** uip3_SparsityPattern = new unsigned int **;
	double*** dp3_Value = new double**;
	int rowCount, columnCount;
	ConvertMatrixMarketFormatToRowCompressedFormat(s_InputFile, uip3_SparsityPattern, dp3_Value,rowCount, columnCount);

	cout<<"just for debugging purpose, display the 2 matrices: the matrix with SparsityPattern only and the matrix with Value"<<endl;
	cout<<fixed<<showpoint<<setprecision(2); //formatting output
	cout<<"(*uip3_SparsityPattern)"<<endl;
	displayCompressedRowMatrix((*uip3_SparsityPattern),rowCount);
	cout<<"(*dp3_Value)"<<endl;
	displayCompressedRowMatrix((*dp3_Value),rowCount);
	cout<<"Finish ConvertMatrixMarketFormatToRowCompressedFormat()"<<endl;
	Pause();

	//Step 2: Obtain the seed matrix via coloring.
	double*** dp3_Seed = new double**;
	int *ip1_SeedRowCount = new int;
	int *ip1_SeedColumnCount = new int;
	int *ip1_ColorCount = new int; //The number of distinct colors used to color the graph

	//Step 2.1: Read the sparsity pattern of the given Jacobian matrix (compressed sparse rows format)
	//and create the corresponding bipartite graph
	BipartiteGraphPartialColoringInterface *g = new BipartiteGraphPartialColoringInterface(SRC_MEM_ADOLC, *uip3_SparsityPattern, rowCount, columnCount);

	//Step 2.2: Do Partial-Distance-Two-Coloring the bipartite graph with the specified ordering
	g->PartialDistanceTwoColoring("SMALLEST_LAST", "ROW_PARTIAL_DISTANCE_TWO");

	//Step 2.3 (Option 1): From the coloring information, create and return the seed matrix
	(*dp3_Seed) = g->GetSeedMatrix_unmanaged(ip1_SeedRowCount, ip1_SeedColumnCount);
	/* Notes:
	Step 2.3 (Option 2): From the coloring information, you can also get the vector of colorIDs of left or right vertices (depend on the s_ColoringVariant that you choose)
		vector<int> vi_VertexPartialColors;
		g->GetVertexPartialColors(vi_VertexPartialColors);
	*/
	cout<<"Finish GenerateSeed()"<<endl;
	*ip1_ColorCount = *ip1_SeedRowCount;

	//Display results of step 2
	printf(" dp3_Seed %d x %d", *ip1_SeedRowCount, *ip1_SeedColumnCount);
	displayMatrix(*dp3_Seed, *ip1_SeedRowCount, *ip1_SeedColumnCount);
	Pause();

	// Step 3: Obtain the seed-Jacobian matrix product.
	// This step will also be done by an AD tool. For the purpose of illustration here, the seed matrix S
	// is multiplied with the orginial matrix V (for Values). The resulting matrix is stored in dp3_CompressedMatrix.
	double*** dp3_CompressedMatrix = new double**;
	cout<<"Start MatrixMultiplication()"<<endl;
	MatrixMultiplication_SxV(*uip3_SparsityPattern, *dp3_Value, rowCount, columnCount, *dp3_Seed, *ip1_ColorCount, dp3_CompressedMatrix);
	cout<<"Finish MatrixMultiplication()"<<endl;

	displayMatrix(*dp3_CompressedMatrix,*ip1_ColorCount,columnCount);
	Pause();

	//Step 4: Recover the numerical values of the original matrix from the compressed representation.
	// The new values are store in "dp3_NewValue"
	double*** dp3_NewValue = new double**;
	JacobianRecovery1D* jr1d = new JacobianRecovery1D;
	jr1d->RecoverD2Row_RowCompressedFormat(g, *dp3_CompressedMatrix, *uip3_SparsityPattern, dp3_NewValue);
	cout<<"Finish Recover()"<<endl;

	displayCompressedRowMatrix(*dp3_NewValue,rowCount);
	Pause();

	//Check for consistency, make sure the values in the 2 matrices are the same.
	if (CompressedRowMatricesREqual(*dp3_Value, *dp3_NewValue, rowCount,0)) cout<< "*dp3_Value == dp3_NewValue"<<endl;
	else cout<< "*dp3_Value != dp3_NewValue"<<endl;

	Pause();

	//Deallocate memory using functions in Utilities/MatrixDeallocation.h

	free_2DMatrix( (*dp3_Seed), (*ip1_SeedRowCount) );

	free_2DMatrix(uip3_SparsityPattern, rowCount);
	uip3_SparsityPattern=NULL;

	free_2DMatrix(dp3_Value, rowCount);
	dp3_Value=NULL;

	delete dp3_Seed;
	dp3_Seed = NULL;

	delete ip1_SeedRowCount;
	ip1_SeedRowCount=NULL;

	delete ip1_SeedColumnCount;
	ip1_SeedColumnCount = NULL;

	free_2DMatrix(dp3_CompressedMatrix, *ip1_ColorCount);
	dp3_CompressedMatrix = NULL;

	delete ip1_ColorCount;
	ip1_ColorCount = NULL;

	delete jr1d;
	jr1d = NULL;

	delete dp3_NewValue;
	dp3_NewValue = NULL;

	delete g;
	g=NULL;

	return 0;


  /************************************************/
  /*
  map<string, bool> stat_flags;
  stat_flags["NumberOfColors"] = 1;
  stat_flags["Time"] = 1;
  stat_flags["MaxBackDegree"] = 1;
  stat_flags["Graph_Stat"] = 1;
  stat_flags["output_append"] = 0;
  stat_flags["refresh_list"] = 0;
  
  vector<string> Orderings, Colorings;
  Orderings.push_back("NATURAL");
  Orderings.push_back("LARGEST_FIRST");
  Orderings.push_back("SMALLEST_LAST");
  Orderings.push_back("INCIDENCE_DEGREE");
  //Orderings.push_back("DYNAMIC_LARGEST_FIRST");
  Orderings.push_back("RANDOM");
  //Orderings.push_back("DISTANCE_TWO_LARGEST_FIRST");
  //Orderings.push_back("DISTANCE_TWO_SMALLEST_LAST");
  //Orderings.push_back("DISTANCE_TWO_INCIDENCE_DEGREE");

  //Colorings.push_back("DISTANCE_ONE");
  //Colorings.push_back("ACYCLIC");
  Colorings.push_back("STAR");
  //Colorings.push_back("RESTRICTED_STAR");
  //Colorings.push_back("DISTANCE_TWO");
  
  //toFileC("/home/nguyend/Desktop/Working_U/research_Assefaw/", "-toFileC-bozdagd-synthetic", Orderings, Colorings, stat_flags);
  
  Colorings.clear();
  Colorings.push_back("IMPLICIT_COVERING__STAR_BICOLORING");
  Colorings.push_back("EXPLICIT_COVERING__STAR_BICOLORING");
  Colorings.push_back("EXPLICIT_COVERING__MODIFIED_STAR_BICOLORING");
  Colorings.push_back("IMPLICIT_COVERING__GREEDY_STAR_BICOLORING");
  
  toFileBiC("/home/nguyend/Desktop/Working_U/research_Assefaw/","-toFileBiC", Orderings, Colorings, stat_flags);

  
  Colorings.clear();
  Colorings.push_back("COLUMN_PARTIAL_DISTANCE_TWO");
  Colorings.push_back("ROW_PARTIAL_DISTANCE_TWO");
  
  toFileBiPC("/home/nguyend/Desktop/Working_U/research_Assefaw/","-toFileBiPC", Orderings, Colorings, stat_flags);

  //toFileC_forColoringBasedOrdering("/home/nguyend/Desktop/Working_U/research_Assefaw/","-toFileC_forColoringBasedOrdering");
  //toFileStatisticForGraph("/home/nguyend/Desktop/Working_U/research_Assefaw/","-toFileStatisticForGraph"); //i.e. Symmetric Matrix, Hessian
  //toFileStatisticForBipartiteGraph("/home/nguyend/Desktop/Working_U/research_Assefaw/","-toFileStatisticForBipartiteGraph"); //i.e. Matrix, Jacobian
  
  //*/

  /************************************************/
  /*
	string s_InputFile; //path of the input file. PICK A SYMMETRIC MATRIX!!!
  
  	s_InputFile = "/home/nguyend/Desktop/Duck/Research/Prog/graph/bozdagd/application/pkustk10.psa.graph";
	//Generate and color the graph
	BipartiteGraphBicoloringInterface * g1 = new BipartiteGraphBicoloringInterface(SRC_FILE, s_InputFile.c_str(), "AUTO_DETECTED");
  
  	s_InputFile = "/home/nguyend/Desktop/Duck/Research/Prog/graph/bozdagd/application/pkustk11.psa.graph";
	//Generate and color the graph
	BipartiteGraphPartialColoringInterface * g2 = new BipartiteGraphPartialColoringInterface(SRC_FILE, s_InputFile.c_str(), "AUTO_DETECTED");
	
	if(*g1 == *g2) cout<<"g1 == g2"<<endl;
	else cout<<"g1 != g2"<<endl;
	//*/

  /************************************************/
  //toFile("/home/nguyend/Desktop/Working_U/research_Assefaw/");
  
  
  /************************************************/
  /*
	vector <string> listOfGraphs = getListOfGraphs("/home/nguyend/Desktop/Working_U/research_Assefaw/listOfGraphs.txt");
	for(unsigned int i=0;i < listOfGraphs.size(); i++){
		cout<<"Graph: "<<listOfGraphs[i]<<endl<<endl;
		
		f(listOfGraphs[i]);
	}
	//*/

}
/*
{
	// s_InputFile = baseDir + <name of the input file>
	string s_InputFile; //path of the input file. PICK A SYMMETRIC MATRIX!!!
	s_InputFile = baseDir;
	s_InputFile += DIR_SEPARATOR; s_InputFile += "Graphs"; s_InputFile += DIR_SEPARATOR; s_InputFile += "mtx-spear-head.mtx";
	s_InputFile = "/home/nguyend/Desktop/Duck/Research/Prog/graph/bozdagd/application/ldoor.rsa.graph";

	//Generate and color the graph
	GraphColoringInterface * g = new GraphColoringInterface(SRC_FILE, s_InputFile.c_str(), "AUTO_DETECTED");
	
	g->PrintVertexDegrees();

	//Color the bipartite graph with the specified ordering
	g->Coloring("LARGEST_FIRST", "DISTANCE_TWO");

	/*Done with coloring. Below are possible things that you may
	want to do after coloring:
	//*/

	/* 1. Check DISTANCE_TWO coloring result
	cout<<"Check DISTANCE_TWO coloring result"<<endl;
	g->CheckDistanceTwoColoring();
	Pause();
	//*-/

	//* 2. Print coloring results
	g->PrintVertexColoringMetrics();
	Pause();
	//*-/

	//* 3. Get the list of colorID of vertices
	vector<int> vi_VertexColors;
	g->GetVertexColors(vi_VertexColors);

	//Display vector of VertexColors
	printf("vector of VertexColors (size %d) \n", vi_VertexColors.size());
	displayVector(&vi_VertexColors[0], vi_VertexColors.size(), 1);
	Pause();
	//*/

	/* 4. Get seed matrix
	int i_SeedRowCount = 0;
	int i_SeedColumnCount = 0;
	double** Seed = g->GetSeedMatrix(&i_SeedRowCount, &i_SeedColumnCount);

	//Display Seed
	printf("Seed matrix %d x %d \n", i_SeedRowCount, i_SeedColumnCount);
	displayMatrix(Seed, i_SeedRowCount, i_SeedColumnCount, 1);
	Pause();
	//*-/

	delete g;
	return 0;
}
//*/


int f (string s_InputFile) {
  /************************************************/
  /*
  GraphColoringInterface gci(SRC_WAIT), gci2(SRC_WAIT);
  gci.ReadMeTiSAdjacencyGraph(s_InputFile);
  gci2.ReadMeTiSAdjacencyGraph2(s_InputFile);
  
  if(gci == gci2)  cout<<endl<<endl<<"**** gci == gci2"<<endl<<endl;
  else {
    //gci.PrintGraph();
    //gci2.PrintGraph();
    cout<<"gci.GetVertexCount() = "<<gci.GetVertexCount()<<"; gci.GetEdgeCount() = "<<gci.GetEdgeCount()<<endl;
    cout<<"gci2.GetVertexCount() = "<<gci2.GetVertexCount()<<"; gci2.GetEdgeCount() = "<<gci2.GetEdgeCount()<<endl;
    vector<int> gci_vertices, gci_edges, gci2_vertices, gci2_edges;

    gci.GetVertices(gci_vertices);
    gci2.GetVertices(gci2_vertices);
    diffVectors(gci_vertices, gci2_vertices);

    gci.GetEdges(gci_edges);
    gci2.GetEdges(gci2_edges);
    diffVectors(gci_edges, gci2_edges, 1, 1);

    gci.PrintVertexD1Neighbor(124608,-5);
    gci2.PrintVertexD1Neighbor(124608,-5);
    cout<<endl<<endl<<"**** gci != gci2"<<endl<<endl;
    exit(1);
  }
  //*/
  
  /************************************************/
  /*
  cout<<endl<<endl<<"****GraphColoringInterface"<<endl;
  GraphColoringInterface gci(SRC_FILE, s_InputFile.c_str(), "AUTO_DETECTED");

  //cout<<endl<<endl<<"****BipartiteGraphPartialColoringInterface"<<endl;
  //BipartiteGraphPartialColoringInterface bgpci (SRC_FILE, s_InputFile.c_str(), "AUTO_DETECTED");

  cout<<endl<<endl<<"****ConvertMatrixMarketFormatToRowCompressedFormat"<<endl;
  unsigned int *** uip3_SparsityPattern = new unsigned int **;	//uip3_ means triple pointers of type unsigned int
  double*** dp3_Value = new double**;	//dp3_ means double pointers of type double. Other prefixes follow the same notation
  int rowCount, columnCount;
  ConvertMatrixMarketFormatToRowCompressedFormat(s_InputFile, uip3_SparsityPattern, dp3_Value,rowCount, columnCount);
    //displayCompressedRowMatrix(*uip3_SparsityPattern,rowCount);
  //BipartiteGraphBicoloringInterface bgbci (SRC_MEM_ADOLC, *uip3_SparsityPattern, rowCount, columnCount);
  GraphColoringInterface gci2 (SRC_MEM_ADOLC, *uip3_SparsityPattern, rowCount, columnCount);
  
  
  if(gci.areEqual(gci2)) cout<<endl<<endl<<"**** g1 == g2"<<endl<<endl;
  else {
    gci.PrintGraph();
    gci2.PrintGraph();
    displayCompressedRowMatrix(*uip3_SparsityPattern,rowCount);
    cout<<endl<<endl<<"**** g1 != g2"<<endl<<endl;
    Pause();
  }
  //*/
  
  /************************************************/
  /*
  cout<<endl<<endl<<"****GraphColoringInterface"<<endl;
  GraphColoringInterface gci(SRC_FILE, s_InputFile.c_str(), "AUTO_DETECTED");
  gci.PrintGraph();5
  Pause();

  cout<<endl<<endl<<"****BipartiteGraphBicoloringInterface"<<endl;
  BipartiteGraphBicoloringInterface bgbci (SRC_FILE, s_InputFile.c_str(), "AUTO_DETECTED");
  bgbci.PrintBipartiteGraph();

//*/
  //*
  cout<<endl<<endl<<"****GraphColoringInterface"<<endl;
  GraphColoringInterface gci(SRC_FILE, "/home/nguyend/Desktop/Working_U/research_Assefaw/ColPack/Graphs/bcsstk01.mtx", "AUTO_DETECTED");
  gci.PrintGraph();
  //Pause();

  cout<<endl<<endl<<"****GraphColoringInterface2"<<endl;
  GraphColoringInterface gci2(SRC_FILE, "/home/nguyend/Desktop/Working_U/research_Assefaw/ColPack/Graphs/bcsstk01.rsa", "AUTO_DETECTED");
  gci2.PrintGraph();
  //Pause();
  
  if(gci == gci2)  cout<<endl<<endl<<"**** gci == gci2"<<endl<<endl;
  else {
    //gci.PrintGraph();
    //gci2.PrintGraph();
    cout<<"gci.GetVertexCount() = "<<gci.GetVertexCount()<<"; gci.GetEdgeCount() = "<<gci.GetEdgeCount()<<endl;
    cout<<"gci2.GetVertexCount() = "<<gci2.GetVertexCount()<<"; gci2.GetEdgeCount() = "<<gci2.GetEdgeCount()<<endl;
    vector<int> gci_vertices, gci_edges, gci2_vertices, gci2_edges;

    gci.GetVertices(gci_vertices);
    gci2.GetVertices(gci2_vertices);
    diffVectors(gci_vertices, gci2_vertices);

    gci.GetEdges(gci_edges);
    gci2.GetEdges(gci2_edges);
    diffVectors(gci_edges, gci2_edges, 1, 1);

    gci.PrintVertexD1Neighbor(124608,-5);
    gci2.PrintVertexD1Neighbor(124608,-5);
    cout<<endl<<endl<<"**** gci != gci2"<<endl<<endl;
    exit(1);
  }
//*/
 
  Pause();

}

/* A LONGER VERSION showing steps actually executed by the constructor.
int main(int argc, char ** argv)
{
	// s_InputFile = baseDir + <name of the input file>
	string s_InputFile; //path of the input file. PICK A SYMMETRIC MATRIX!!!
	s_InputFile = baseDir + "bcsstk01_symmetric\\bcsstk01_symmetric.mtx";
	GraphColoringInterface * g = new GraphColoringInterface();

	//Read a matrix from an input file and generate a corresponding graph.
	//The input format will be determined based on the file extension and a correct reading routine will be used to read the file.
	//Note: the input matrix MUST be SYMMETRIC in order for a graph to be generated correctly
	//		If you are new to COLPACK, pick either a .graph file (MeTiS format) or a symmetric .mtx (Matrix Market format)
	if ( g->ReadAdjacencyGraph(s_InputFile) == _FALSE) {
		cout<<"ReadAdjacencyGraph() Failed!!!"<<endl;
		return _FALSE;
	}
	cout<<"Done with ReadAdjacencyGraph()"<<endl;
	//Pause();

	//(Distance-2)Color the graph using "LARGEST_FIRST" Ordering. Other coloring and ordering can also be used.
	g->Coloring("DISTANCE_TWO", "LARGEST_FIRST");
	cout<<"Done with Coloring()"<<endl;
	//Pause();

	//Print coloring results
	g->PrintVertexColoringMetrics();
	cout<<"Done with PrintVertexColoringMetrics()"<<endl;
	delete g;
	//Pause();

	return _TRUE;
}
//*/
