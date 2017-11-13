#include "WeightedGraph.h"

WeightedGraph::WeightedGraph ( int maxNumber ) {

    vertexList = new Vertex[maxNumber];
    maxSize = maxNumber;
    size = 0;
    adjMatrix = new int[maxNumber * maxNumber];

    for(int i = 0; i < maxNumber * maxNumber; ++i) {

        adjMatrix[i] = INT_MAX;
    }
}

WeightedGraph::WeightedGraph ( const WeightedGraph& other ) {

    (*this) = other;
}

WeightedGraph& WeightedGraph::operator = ( const WeightedGraph& other ) {

    if(this == &other) 
        return (*this);

    delete [] vertexList;
    delete [] adjMatrix;

    vertexList = new Vertex[other.maxSize];

    for(int i = 0; i < other.size; ++i) {

        vertexList[i] = other.vertexList[i];
    }

    maxSize = other.maxSize;
    size = other.size;
    adjMatrix = new int[other.maxSize * other.maxSize];

    for(int i = 0; i < other.maxSize * other.maxSize; ++i) {

        adjMatrix[i] = other.adjMatrix[i];
    }

    return (*this);
}

WeightedGraph::~WeightedGraph () {

    delete [] vertexList;
    delete [] adjMatrix;
}

void WeightedGraph::insertVertex ( const Vertex& newVertex ) throw ( logic_error ) {

    if(isFull()) 
        throw(logic_error("insertVertex() full graph."));

    bool replaced = false;

    for (int i = 0; i < size; ++i) {

        if(vertexList[i].getLabel() == newVertex.getLabel()) { 
            vertexList[i] = newVertex;
            replaced = true;
        }
    }

    if(!replaced) {
        vertexList[size] = newVertex;
        ++size;
    }
}

void WeightedGraph::insertEdge ( const string& v1, const string& v2, int wt ) throw ( logic_error ) {

    int v1Index = getIndex(v1), v2Index = getIndex(v2);

    if(v1Index == -1 || v2Index == -1) 
        throw(logic_error("insertEdge() vertcies not found."));

    adjMatrix[v1Index * maxSize + v2Index] = wt;
}

bool WeightedGraph::retrieveVertex ( const string& v, Vertex& vData ) const {

    int i = getIndex(v);

    if(i == -1) 
        return false;
    else {

        vData = vertexList[i];
        return true;
    }
}

bool WeightedGraph::getEdgeWeight ( const string& v1, const string& v2, int& wt ) const throw ( logic_error ) {

    int v1Index = getIndex(v1), v2Index = getIndex(v2);

    if(v1Index == -1 || v2Index == -1) 
        throw(logic_error("getEdgeWeight() couldn't find vertcies."));

    if(adjMatrix[v1Index * maxSize + v2Index] != 0) 
        wt = adjMatrix[v1Index * maxSize + v2Index];
    else 
        throw(logic_error("getEdgeWeight() weight does not exist."));
}   

void WeightedGraph::removeVertex ( const string& v ) throw ( logic_error ) {

    if(isEmpty())
        throw(logic_error("removeVertex() empty graph."));

    int index = getIndex(v);

    if(index == -1) 
        throw(logic_error("removeVertex() vertex not found."));

    for(int i = index; i < size - 1; ++i) {

        vertexList[i] = vertexList[i + 1];
    }

    for(int i = 0; i < size; ++i) {

        for(int j = 0; j < size; ++j) {

            if(j >= index && j < size - 1)
                adjMatrix[i * maxSize + j] = adjMatrix[i * maxSize + j + 1];
            if(i >= index && i < size - 1)
                adjMatrix[i * maxSize + j] = adjMatrix[(i + 1) * maxSize + j];
        }
    }  

    --size;  
}

void WeightedGraph::removeEdge ( const string& v1, const string& v2 ) throw ( logic_error ) {

    int v1Index = getIndex(v1), v2Index = getIndex(v2);

    if(v1Index == -1 || v2Index == -1) 
        throw(logic_error("removeEdge() vertcies not found."));

    adjMatrix[v1Index * maxSize + v2Index] = 0;
}

void WeightedGraph::clear () {

    size = 0;
}

inline bool WeightedGraph::isEmpty () const {

    if(size == 0) return true;
    else return false;
}

inline bool WeightedGraph::isFull () const {

    if(size >= maxSize) return true;
    else return false;
}

void WeightedGraph::showStructure () const

// Outputs a graph's vertex list and adjacency matrix. This operation
// is intended for testing/debugging purposes only.

{
    if ( size == 0 ) {
     cout << "Empty graph" << endl;
 } else {
     cout << endl << "Vertex list : " << endl;
     for ( int row = 0 ; row < size ; row++ )
         cout << row << '\t' << vertexList[row].getLabel()
#if LAB12_TEST2
     << vertexList[row].color
#endif
     << endl;

     cout << endl << "Edge matrix : " << endl << '\t';
     for ( int col = 0 ; col < size ; col++ )
         cout << col << '\t';
     cout << endl;
     for ( int row = 0 ; row < size ; row++ )
     {
         cout << row << '\t';
         for ( int col = 0 ; col < size ; col++ )
         {
             int wt = getEdge(row,col);
             if ( wt == INFINITE_EDGE_WT )
              cout << "- \t";
          else
              cout << wt << '\t';
      }
      cout << endl;
  }
}
}

void WeightedGraph::showShortestPaths () const {


}

bool WeightedGraph::hasProperColoring() const {


}

bool WeightedGraph::areAllEven () const {


}

int WeightedGraph::getIndex ( const string& v ) const {

    for(int i = 0; i < size; ++i) {

        if(vertexList[i].getLabel() == v)
            return i;
    }

    return -1;
}

int WeightedGraph::getEdge ( int row, int col ) const {

    return adjMatrix[row * maxSize + col];
}

void WeightedGraph::setEdge ( int row, int col, int wt) {


}