// An example for using GraphColoringInterface to color Graph
/*
How to compile this driver manually:
	Please make sure that "baseDir" point to the directory (folder) containing the input matrix file, and
		s_InputFile should point to the input file that you want to use
	To compile the code, replace the Main.cpp file in Main directory with this file
		and run "make" in ColPack installation directory. Make will generate "ColPack.exe" executable
	Run "ColPack.exe"

Note: If you got "symbol lookup error ... undefined symbol "
  Please make sure that your LD_LIBRARY_PATH contains libColPack.so

Any time you have trouble understanding what a routine does, how to use a routine, or what are the accepted values for a parameter,
please reference the COLPACK's online documentation (temporarily located at
http://www.cscapes.org/dox/ColPack/html/ ).

For more information, please visit our webpage http://www.cscapes.org/coloringpage/
//*/

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
  return 0;
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
  //*
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
 
  //Pause();

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
