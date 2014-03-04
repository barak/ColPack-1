/************************************************************************************
    Copyright (C) 2005-2008 Assefaw H. Gebremedhin, Arijit Tarafdar, Duc Nguyen,
    Alex Pothen

    This file is part of ColPack.

    ColPack is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ColPack is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with ColPack.  If not, see <http://www.gnu.org/licenses/>.
************************************************************************************/

#ifndef GRAPHINPUTOUTPUT_H
#define GRAPHINPUTOUTPUT_H

using namespace std;

namespace ColPack
{
	/** @ingroup group1
	 *  @brief class GraphInputOutput in @link group1@endlink.

	 This class provides the input methods for reading in matrix or graph files in supported
	 formats for generating general graphs. Three input formats are supported by default - Matrix Market,
	 Harwell Boeing and MeTiS.
	 */
	class GraphInputOutput : public GraphCore
	{
	public: //DOCUMENTED

		/// Read the sparsity pattern of a symmetric matrix in the specified file format from the specified filename and build an adjacency  graph.
		/**	This function will
		- 1. Read the name of the matrix file and decide which matrix format the file used (based on the file extension). If the file name has no extension, the user will need to pass the 2nd parameter "fileType" explicitly to tell ColPack which matrix format is used
		- 2. Call the corresponding reading routine to build the graph

		About input parameters:
		- fileName: name of the input file for a symmetric matrix. If the full path is not given, the file is assumed to be in the current directory
		- fileType can be either
			- "AUTO_DETECTED" (default) or "". ColPack will decide the format of the file based on the file extension:
				- ".mtx": symmetric MatrixMarket format
				- ".hb", or any combination of ".<r, c, p><s, u, h, x, r><a, e>": HarwellBoeing format
				- ".graph": MeTiS format
				- If the above extensions are not found, MatrixMarket format will be assumed.
			- "MM" for MatrixMarket format (http://math.nist.gov/MatrixMarket/formats.html#MMformat). Notes:
			  - ColPack only accepts MatrixMarket coordinate format (NO array format)
			  - List of arithmetic fields accepted by ColPack: real, pattern or integer
			  - List of symmetry structures accepted by ColPack: general or symmetric
			  - The first line of the input file should be similar to this: "%%MatrixMarket matrix coordinate real general"
			- "HB" for HarwellBoeing format (http://math.nist.gov/MatrixMarket/formats.html#hb)
			- "MeTiS" for MeTiS format (http://people.sc.fsu.edu/~burkardt/data/metis_graph/metis_graph.html)
		*/
		int ReadAdjacencyGraph(string s_InputFile, string s_fileFormat="AUTO_DETECTED");

		/// Read the sparsity pattern of Hessian matrix represented in ADOLC format (Compressed Sparse Row format) and build a corresponding adjacency graph.
		/**
		Precondition:
		- The Hessian matrix must be stored in Row Compressed Format

		Return value:
		- i_HighestDegree
		*/
		int BuildGraphFromRowCompressedFormat(unsigned int ** uip2_HessianSparsityPattern, int i_RowCount);

		//!!! NEED TO BE FIXED
		/// Read the entries of a symmetric matrix in Matrix Market format and build the corresponding adjacency graph
		/**
		Precondition:
		- s_InputFile should point to the MatrixMarket-format input file (file name usually ends with .mtx)
		- If (b_getStructureOnly == true) only the structure of the matrix is read.
		All the values for the non-zeros in the matrix will be ignored.
		If the input file contains only the graph structure, the value of b_getStructureOnly will be ignored
		*/
		int ReadMatrixMarketAdjacencyGraph(string s_InputFile, bool b_getStructureOnly = false);

	private:

		//Private Function 1201
		int ParseWidth(string FortranFormat);

		//Private Function 1202
		void CalculateVertexDegrees();

	public:

		//Public Constructor 1251
		GraphInputOutput();

		//Public Destructor 1252
		~GraphInputOutput();

		//Virtual Function 1253
		//??? What is the purpose of this function? TO BE IMPLEMENTED
		virtual void Initialize();

		//Virtual Function 1254
		virtual void Clear();

		//Public Function 1255
		string GetInputFile();

		/*
		//Public Function 1256
		int ReadMatrixMarketAdjacencyGraph(string s_InputFile);
		//*/

		//Public Function 1258
		/// Read the entries of symmetric matrix in Harwell Boeing format and build the corresponding adjacency graph.
		int ReadHarwellBoeingAdjacencyGraph(string s_InputFile);

		//Public Function 1259
		/// Read the entries of symmetric matrix in MeTiS format and build the corresponding adjacency graph.
		int ReadMeTiSAdjacencyGraph(string s_InputFile);
		int ReadMeTiSAdjacencyGraph2(string s_InputFile);

		//Public Function 1260
		int PrintGraph();

		//Public Function 1261
		int PrintGraphStructure();

		//Public Function 1262
		int PrintMatrix();

		//Public Function 1263
		int PrintMatrix(vector<int> &, vector<int> &, vector<double> &);

		//Public Function 1264
		void PrintVertexDegrees();
	};
}
#endif

