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

#include "ColPackHeaders.h"

using namespace std;

namespace ColPack
{

	int JacobianRecovery1D::RecoverD2Row_RowCompressedFormat(BipartiteGraphPartialColoringInterface* g, double** dp2_CompressedMatrix, unsigned int ** uip2_JacobianSparsityPattern, double*** dp3_JacobianValue) {
		if(g==NULL) {
			cerr<<"g==NULL"<<endl;
			return _FALSE;
		}

		if(AF_available) reset();

		int rowCount = g->GetRowVertexCount();
		vector<int> vi_LeftVertexColors;
		g->GetLeftVertexColors(vi_LeftVertexColors);
		unsigned int numOfNonZeros = 0;

		//allocate memory for *dp3_JacobianValue. The dp3_JacobianValue and uip2_JacobianSparsityPattern matrices should have the same size
		*dp3_JacobianValue = new double*[rowCount];
		for(unsigned int i=0; i < (unsigned int)rowCount; i++) {
			numOfNonZeros = uip2_JacobianSparsityPattern[i][0];
			(*dp3_JacobianValue)[i] = new double[numOfNonZeros+1];
			(*dp3_JacobianValue)[i][0] = numOfNonZeros; //initialize value of the 1st entry
			for(int j=1; j <= numOfNonZeros; j++) (*dp3_JacobianValue)[i][j] = 0.; //initialize value of other entries
		}

		//Recover value of the Jacobian
		for(unsigned int i=0; i < (unsigned int)rowCount; i++) {
			numOfNonZeros = uip2_JacobianSparsityPattern[i][0];
			for(int j=1; j <= numOfNonZeros; j++) {
				(*dp3_JacobianValue)[i][j] = dp2_CompressedMatrix[vi_LeftVertexColors[i]][uip2_JacobianSparsityPattern[i][j]];
			}

		}

		AF_available = true;
		i_AF_rowCount = rowCount;
		dp2_AF_Value = *dp3_JacobianValue;

		return _TRUE;
	}

	int JacobianRecovery1D::RecoverD2Row_SparseSolversFormat(BipartiteGraphPartialColoringInterface* g, double** dp2_CompressedMatrix, unsigned int ** uip2_JacobianSparsityPattern, unsigned int** ip2_RowIndex, unsigned int** ip2_ColumnIndex, double** dp2_JacobianValue) {
		if(g==NULL) {
			cerr<<"g==NULL"<<endl;
			return _FALSE;
		}

		if(SSF_available) reset();

		int rowCount = g->GetRowVertexCount();
		vector<int> vi_LeftVertexColors;
		g->GetLeftVertexColors(vi_LeftVertexColors);
		unsigned int numOfNonZeros = 0;

		// Allocate memory and populate ip2_RowIndex and ip2_ColumnIndex
		g->GetRowVertices(ip2_RowIndex);
		numOfNonZeros = g->GetColumnIndices(ip2_ColumnIndex);

		//cout<<"allocate memory for *dp2_JacobianValue rowCount="<<rowCount<<endl;
		//printf("i=%d\tnumOfNonZeros=%d \n", i, numOfNonZeros);
		(*dp2_JacobianValue) = new double[numOfNonZeros]; //allocate memory for *dp2_JacobianValue.
		for(unsigned int i=0; i < numOfNonZeros; i++) (*dp2_JacobianValue)[i] = 0.; //initialize value of other entries

		//Recover value of the Jacobian
		unsigned int numOfNonZerosInEachRow = 0;
		for(unsigned int i=0; i < (unsigned int)rowCount; i++) {
			numOfNonZerosInEachRow = uip2_JacobianSparsityPattern[i][0];
			for(int j=1; j <= numOfNonZerosInEachRow; j++) {
				(*dp2_JacobianValue)[(*ip2_RowIndex)[i]+j-1] = dp2_CompressedMatrix[vi_LeftVertexColors[i]][uip2_JacobianSparsityPattern[i][j]];
			}

		}

		//Making the array indices to start at 1 instead of 0 to conform with theIntel MKL sparse storage scheme for the direct sparse solvers
		for(unsigned int i=0; i <= (unsigned int)rowCount; i++) {
		  (*ip2_RowIndex)[i]++;
		}
		for(unsigned int i=0; i < numOfNonZeros; i++) {
		  (*ip2_ColumnIndex)[i]++;
		}

		SSF_available = true;
		i_SSF_rowCount = rowCount;
		ip_SSF_RowIndex = *ip2_RowIndex;
		ip_SSF_ColumnIndex = *ip2_ColumnIndex;
		dp_SSF_Value = *dp2_JacobianValue;

		return _TRUE;
	}

	int JacobianRecovery1D::RecoverD2Row_CoordinateFormat(BipartiteGraphPartialColoringInterface* g, double** dp2_CompressedMatrix, unsigned int ** uip2_JacobianSparsityPattern, unsigned int** ip2_RowIndex, unsigned int** ip2_ColumnIndex, double** dp2_JacobianValue) {
		if(g==NULL) {
			cerr<<"g==NULL"<<endl;
			return _FALSE;
		}

		if(CF_available) reset();

		int rowCount = g->GetRowVertexCount();
		vector<int> vi_LeftVertexColors;
		g->GetLeftVertexColors(vi_LeftVertexColors);
		unsigned int numOfNonZeros = 0;

		numOfNonZeros = g->GetEdgeCount();
		(*ip2_RowIndex) = new unsigned int[numOfNonZeros];
		(*ip2_ColumnIndex) = new unsigned int[numOfNonZeros];
		(*dp2_JacobianValue) = new double[numOfNonZeros]; //allocate memory for *dp2_JacobianValue.

		//Recover value of the Jacobian
		unsigned int numOfNonZeros_count = 0;
		for(unsigned int i=0; i < (unsigned int)rowCount; i++) {
			numOfNonZeros = uip2_JacobianSparsityPattern[i][0];
			for(int j=1; j <= numOfNonZeros; j++) {
				(*dp2_JacobianValue)[numOfNonZeros_count] = dp2_CompressedMatrix[vi_LeftVertexColors[i]][uip2_JacobianSparsityPattern[i][j]];
				(*ip2_RowIndex)[numOfNonZeros_count] = i;
				(*ip2_ColumnIndex)[numOfNonZeros_count] = uip2_JacobianSparsityPattern[i][j];
				numOfNonZeros_count++;
			}
		}
		/*
		if(numOfNonZeros_count != g->GetEdgeCount()) {
			cout<<"**Something fishing going on"<<endl;
			cout<<"numOfNonZeros_count="<<numOfNonZeros_count<<endl;
			cout<<"numOfNonZeros="<<numOfNonZeros<<endl;
		}
		else cout<<"**Good!!!"<<endl;
		Pause();
		//*/

		CF_available = true;
		i_CF_rowCount = rowCount;
		ip_CF_RowIndex = *ip2_RowIndex;
		ip_CF_ColumnIndex = *ip2_ColumnIndex;
		dp_CF_Value = *dp2_JacobianValue;

		return _TRUE;
	}

	int JacobianRecovery1D::RecoverD2Cln_RowCompressedFormat(BipartiteGraphPartialColoringInterface* g, double** dp2_CompressedMatrix, unsigned int ** uip2_JacobianSparsityPattern, double*** dp3_JacobianValue) {
		if(g==NULL) {
			cerr<<"g==NULL"<<endl;
			return _FALSE;
		}

		if(AF_available) reset();

		int rowCount = g->GetRowVertexCount();
		vector<int> vi_RightVertexColors;
		g->GetRightVertexColors(vi_RightVertexColors);
		unsigned int numOfNonZeros = 0;

		//allocate memory for *dp3_JacobianValue. The dp3_JacobianValue and uip2_JacobianSparsityPattern matrices should have the same size
		//cout<<"allocate memory for *dp3_JacobianValue rowCount="<<rowCount<<endl;
		*dp3_JacobianValue = new double*[rowCount];
		for(unsigned int i=0; i < (unsigned int)rowCount; i++) {
			numOfNonZeros = uip2_JacobianSparsityPattern[i][0];
			//printf("i=%d\tnumOfNonZeros=%d \n", i, numOfNonZeros);
			(*dp3_JacobianValue)[i] = new double[numOfNonZeros+1];
			(*dp3_JacobianValue)[i][0] = numOfNonZeros; //initialize value of the 1st entry
			for(unsigned int j=1; j <= numOfNonZeros; j++) (*dp3_JacobianValue)[i][j] = 0.; //initialize value of other entries
		}

		//Recover value of the Jacobian
		//cout<<"Recover value of the Jacobian"<<endl;
		for(unsigned int i=0; i < (unsigned int)rowCount; i++) {
			numOfNonZeros = uip2_JacobianSparsityPattern[i][0];
			for(unsigned int j=1; j <= numOfNonZeros; j++) {
				(*dp3_JacobianValue)[i][j] = dp2_CompressedMatrix[i][vi_RightVertexColors[uip2_JacobianSparsityPattern[i][j]]];
			}

		}

		AF_available = true;
		i_AF_rowCount = rowCount;
		dp2_AF_Value = *dp3_JacobianValue;

		return _TRUE;
	}

	int JacobianRecovery1D::RecoverD2Cln_SparseSolversFormat(BipartiteGraphPartialColoringInterface* g, double** dp2_CompressedMatrix, unsigned int ** uip2_JacobianSparsityPattern, unsigned int** ip2_RowIndex, unsigned int** ip2_ColumnIndex, double** dp2_JacobianValue) {
		if(g==NULL) {
			cerr<<"g==NULL"<<endl;
			return _FALSE;
		}

		if(SSF_available) reset();

		int rowCount = g->GetRowVertexCount();
		vector<int> vi_RightVertexColors;
		g->GetRightVertexColors(vi_RightVertexColors);
		unsigned int numOfNonZeros = 0;

		// Allocate memory and populate ip2_RowIndex and ip2_ColumnIndex
		g->GetRowVertices(ip2_RowIndex);
		numOfNonZeros = g->GetColumnIndices(ip2_ColumnIndex);

		//cout<<"allocate memory for *dp2_JacobianValue rowCount="<<rowCount<<endl;
		//printf("i=%d\tnumOfNonZeros=%d \n", i, numOfNonZeros);
		(*dp2_JacobianValue) = new double[numOfNonZeros]; //allocate memory for *dp2_JacobianValue.
		for(unsigned int i=0; i < numOfNonZeros; i++) (*dp2_JacobianValue)[i] = 0.; //initialize value of other entries

		//Recover value of the Jacobian
		//cout<<"Recover value of the Jacobian"<<endl;
		unsigned int numOfNonZerosInEachRow = 0;
		for(unsigned int i=0; i < (unsigned int)rowCount; i++) {
			numOfNonZerosInEachRow = uip2_JacobianSparsityPattern[i][0];
			for(unsigned int j=1; j <= numOfNonZerosInEachRow; j++) {
				(*dp2_JacobianValue)[(*ip2_RowIndex)[i]+j-1] = dp2_CompressedMatrix[i][vi_RightVertexColors[uip2_JacobianSparsityPattern[i][j]]];
			}
		}


		//Making the array indices to start at 1 instead of 0 to conform with theIntel MKL sparse storage scheme for the direct sparse solvers
		for(unsigned int i=0; i <= (unsigned int)rowCount; i++) {
		  (*ip2_RowIndex)[i]++;
		}
		for(unsigned int i=0; i < numOfNonZeros; i++) {
		  (*ip2_ColumnIndex)[i]++;
		}


		SSF_available = true;
		i_SSF_rowCount = rowCount;
		ip_SSF_RowIndex = *ip2_RowIndex;
		ip_SSF_ColumnIndex = *ip2_ColumnIndex;
		dp_SSF_Value = *dp2_JacobianValue;

		return _TRUE;
	}

	int JacobianRecovery1D::RecoverD2Cln_CoordinateFormat(BipartiteGraphPartialColoringInterface* g, double** dp2_CompressedMatrix, unsigned int ** uip2_JacobianSparsityPattern, unsigned int** ip2_RowIndex, unsigned int** ip2_ColumnIndex, double** dp2_JacobianValue) {
		if(g==NULL) {
			cerr<<"g==NULL"<<endl;
			return _FALSE;
		}

		if(CF_available) reset();

		int rowCount = g->GetRowVertexCount();
		vector<int> vi_RightVertexColors;
		g->GetRightVertexColors(vi_RightVertexColors);
		unsigned int numOfNonZeros = 0;

		numOfNonZeros = g->GetEdgeCount();
		(*ip2_RowIndex) = new unsigned int[numOfNonZeros];
		(*ip2_ColumnIndex) = new unsigned int[numOfNonZeros];
		(*dp2_JacobianValue) = new double[numOfNonZeros]; //allocate memory for *dp2_JacobianValue.

		//Recover value of the Jacobian
		//cout<<"Recover value of the Jacobian"<<endl;
		unsigned int numOfNonZeros_count = 0;
		for(unsigned int i=0; i < (unsigned int)rowCount; i++) {
			numOfNonZeros = uip2_JacobianSparsityPattern[i][0];
			for(unsigned int j=1; j <= numOfNonZeros; j++) {
				(*dp2_JacobianValue)[numOfNonZeros_count] = dp2_CompressedMatrix[i][vi_RightVertexColors[uip2_JacobianSparsityPattern[i][j]]];
				(*ip2_RowIndex)[numOfNonZeros_count] = i;
				(*ip2_ColumnIndex)[numOfNonZeros_count] = uip2_JacobianSparsityPattern[i][j];
				numOfNonZeros_count++;
			}
		}
		/*
		if(numOfNonZeros_count != g->GetEdgeCount()) {
			cout<<"**Something fishing going on"<<endl;
			cout<<"numOfNonZeros_count="<<numOfNonZeros_count<<endl;
			cout<<"numOfNonZeros="<<numOfNonZeros<<endl;
		}
		else cout<<"**Good!!!"<<endl;
		Pause();
		//*/

		CF_available = true;
		i_CF_rowCount = rowCount;
		ip_CF_RowIndex = *ip2_RowIndex;
		ip_CF_ColumnIndex = *ip2_ColumnIndex;
		dp_CF_Value = *dp2_JacobianValue;

		return _TRUE;
	}
}
