// A simnple reader for triangle ply files. Includes an opengl renderer.
// Load and Draw are really the only methods you need to call.
// I think this has memory leaks.



class Model_PLY{
public:
	Model_PLY();
	//~Model_PLY();
	void Draw();
	
	float* calculateNormal( float *coord1, float *coord2, float *coord3 );   
  float* Faces_Triangles;
  float* Faces_Quads;
	float* Vertex_Buffer;
	float* Normals;
	
  int Load(char *filename); // load the ply file given by filename  
	int TotalConnectedTriangles;
	int TotalConnectedQuads;
	int TotalConnectedPoints;
	int TotalFaces;
       
};


