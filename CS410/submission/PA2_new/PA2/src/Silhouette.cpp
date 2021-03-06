/*
 * Silhouette.cpp
 *
 *  Created on: Oct 10, 2015
 *      Author: prashantm
 */

#include <Silhouette.h>



Silhouette::Silhouette(int argc, char **argv) {
	// TODO Auto-generated constructor stub

	this->number_of_models = 0;
	this->ParseArguments(argc, argv);

	pixel_colors.clear();

	// Test Code
	/*
	cout << "Test string" << endl;
	cout << "Camera filename - " << camera_filename << endl;
	for (int i = 0; i < number_of_models; i++) {
		cout << input_models.at(i) << endl;
	}
	cout << "Output ppm file is - " << output_filename << endl;
	*/

	this->parse_camera_model = new ParseCameraModel(camera_filename.c_str());
	this->vup_vector = this->parse_camera_model->GetVupVector();
	this->focal_point = this->parse_camera_model->GetFocalPoint();
	this->focal_length = this->parse_camera_model->GetFocalLength();
	this->look_at_point = this->parse_camera_model->GetLookAtPoint();
	uMin = this->parse_camera_model->GetImageSizeuMin();
	vMin = this->parse_camera_model->GetImageSizevMin();
	uMax = this->parse_camera_model->GetImageSizeuMax();
	vMax = this->parse_camera_model->GetImageSizevMax();
	uSize = this->parse_camera_model->GetImageSizeU();
	vSize = this->parse_camera_model->GetImageSizeV();

	// this->parse_camera_model->PrintAllCameraProperties();

	pixel_colors.resize(uSize*vSize);

	// Calculate projection matrix
	this->projection_matrix = new ProjectionMatrix(*this->focal_point, *this->look_at_point,
			*this->vup_vector, this->focal_length);
	this->uVec = this->projection_matrix->GetuVector();
	this->vVec = this->projection_matrix->GetvVector();
	this->nVec = this->projection_matrix->GetnVector();

	// Test vectors
	//this->uVec->PrintVertex();
	//this->vVec->PrintVertex();
	//this->nVec->PrintVertex();

	this->matrix_operations = new MatrixOperations;
	this->vector_operations = new VectorOperations;

	// Calculate fp + dn
	fpPlusdn.x_coordinate = this->focal_point->x_coordinate + (this->focal_length*this->nVec->x_coordinate);
	fpPlusdn.y_coordinate = this->focal_point->y_coordinate + (this->focal_length*this->nVec->y_coordinate);
	fpPlusdn.z_coordinate = this->focal_point->z_coordinate + (this->focal_length*this->nVec->z_coordinate);

	// Generate Silhouette for each model
	for (int model_index = 0; model_index < this->number_of_models; model_index++) {

		cout << "Processing input model - " << model_index + 1 << endl;
		this->SilhouetteForModel(this->input_models.at(model_index).c_str());
	}

	// this->matrix_operations->PrintMatrix(this->projection_matrix->GetProjectionMatrix());

	write_ppm = new WritePpm(output_filename.c_str(), uSize, vSize, pixel_colors);

	delete write_ppm;
	delete this->uVec;
	delete this->vVec;
	delete this->nVec;
	delete this->matrix_operations;
	delete this->vector_operations;
}


void Silhouette::ParseArguments(int argc, char **argv) {
	for (int i = 1; i <= argc - 1; i++ ) {
		if (i == 1)
			camera_filename = argv[1];
		else if (i == argc - 1) {

			output_filename = argv[i];
		}
		else {
			input_models.push_back(argv[i]);
			this->number_of_models++;
		}
	}
}


// This function is to generate silhouette for each model
void Silhouette::SilhouetteForModel(const char * inputfile) {
	this->parse_ply = new ParsePly(inputfile);

	this->parse_ply->ParseAllVertices("vertices.txt");
	this->mean_vertex = *this->parse_ply->GetMeanVertex();

	// Get faces and convert them into triangles
	this->parse_ply->ParseFaces("faces.txt");
	//this->parse_ply->PrintPlyAttributes();

	vector<Face> triangles;

	if (this->parse_ply->all_triangles != true) {

		this->create_triangles = new CreateTriangles(this->parse_ply->GetParsedFaces());

		triangles = this->create_triangles->GetTriangles();
	}
	else{
		triangles = this->parse_ply->GetParsedFaces();
	}

	// Test triangles
	// this->write_ply = new WritePly("triangles.txt");
	// this->write_ply->WriteFacesFromVector(triangles);
	// this->write_ply->CloseWriteFile();

	uint64_t num_triangles = triangles.size();

	//cout << "Mean vertex is" << endl;
	//this->mean_vertex.PrintVertex();


	radius = this->parse_ply->GetRadius();
	radiusSquare = radius * radius;
	//cout << "Radius is " << radius << endl;




	// Calculate c = (mean - fp) and csquare
	c = this->vector_operations->Distance(this->focal_point, &this->mean_vertex);
	cSquare = c * c;

	Vertex L, LminusE, OminusE;
	Vertex A, B, C;
	Vertex T;

	float d, dSquare, s, s1, s2,  UdotT, UdotTSquare, Tsquare;


	// For storing beta, gamma and t after solving for system of linear equations
	float *solution = new float[3];

	// For every pixel
	for ( int a = uMin; a <= uMax; a++) {
		for ( int b = vMin; b <= vMax; b++) {

			if ((pixel_colors.at((a-uMin)*vSize + (b-vMin)).GetR() == 255) &&
					(pixel_colors.at((a-uMin)*vSize + (b-vMin)).GetG() == 255) &&
					(pixel_colors.at((a-uMin)*vSize + (b-vMin)).GetB() == 255) ) {
				// Pixel is already white. So continue
				cout << "Pixel is already white. So continue" << endl;
				continue;
			}

			// Ray - sphere intersection code

			// Step 1: Calculate location of pixel[a,b] in 3-D fp + dn + au + by
			L.x_coordinate = fpPlusdn.x_coordinate + (a * this->uVec->x_coordinate) + (b * this->vVec->x_coordinate);
			L.y_coordinate = fpPlusdn.y_coordinate + (a * this->uVec->y_coordinate) + (b * this->vVec->y_coordinate);
			L.z_coordinate = fpPlusdn.z_coordinate + (a * this->uVec->z_coordinate) + (b * this->vVec->z_coordinate);

			// Calculate U - Normalized (L - fp)
			LminusE.x_coordinate = L.x_coordinate - this->focal_point->x_coordinate;
			LminusE.y_coordinate = L.y_coordinate - this->focal_point->y_coordinate;
			LminusE.z_coordinate = L.z_coordinate - this->focal_point->z_coordinate;

			U = this->vector_operations->Normalize(&LminusE);

			// Calculate v = (O - E).U
			OminusE.x_coordinate = this->mean_vertex.x_coordinate - this->focal_point->x_coordinate;
			OminusE.y_coordinate = this->mean_vertex.y_coordinate - this->focal_point->y_coordinate;
			OminusE.z_coordinate = this->mean_vertex.z_coordinate - this->focal_point->z_coordinate;
			v = this->vector_operations->DotProduct(&OminusE, U);

			// cout << "v is " << v << endl;
			vSquare = v*v;


			dSquare = radiusSquare - cSquare + vSquare;

			if (dSquare < -0.000001 || (radiusSquare < (cSquare - vSquare))) {
				// cout << "dSqaure negative" << endl;
				continue;
			}

			d = sqrtf(dSquare);


			if (cSquare > radiusSquare) {
				s = v - d;
			}
			else
				s = v + d;

			// cout << "r^2 is " << radiusSquare << " c^2 is " << cSquare << " v^2 is " << vSquare << endl;

/*
			T.x_coordinate = this->mean_vertex.x_coordinate - L.x_coordinate;
			T.y_coordinate = this->mean_vertex.y_coordinate - L.y_coordinate;
			T.z_coordinate = this->mean_vertex.z_coordinate - L.z_coordinate;

			UdotT = this->vector_operations->DotProduct(U, &T);

			UdotTSquare  = UdotT*UdotT;
			Tsquare = this->vector_operations->DotProduct(&T, &T);

			if (UdotTSquare < Tsquare - radiusSquare) {
			// s will be a imaginary number

				s = -1;
			}

			else {

			s1 = UdotT + sqrtf( UdotTSquare - Tsquare + radiusSquare );
			s2 = UdotT - sqrtf( UdotTSquare - Tsquare + radiusSquare );

			if (s1 < 0.000001 && s2 > 0.000001) {
				s = s2;
			}
			else if (s2 < 0.000001 && s1 > 0.000001) {
				s = s1;
			}
			else
				s = min(s1, s2);



			}

			 // cout << "s1 is " << s1 << " s2 is" << s2 << endl;
*/
			// cout << "s is " << s << endl;
			//
			if (s > 0.00001) {
				// cout << "r^2 is " << radiusSquare << " c^2 is " << cSquare << " v^2 is " << vSquare << endl;
				// Only if this is true then go for checking if the ray intersects each face


				// Coloring at sphere intersection
				// pixel_colors.at((a-uMin)*vSize + (b-vMin)).SetR(255);
				// pixel_colors.at((a-uMin)*vSize + (b-vMin)).SetG(255);
				// pixel_colors.at((a-uMin)*vSize + (b-vMin)).SetB(255);
				// cout << "Coloring pixel " << endl;
				for (int k = 0; k < num_triangles; k++) {
					A = triangles.at(k).getVertexFromFace(0);
					B = triangles.at(k).getVertexFromFace(1);
					C = triangles.at(k).getVertexFromFace(2);
					// cout << "going into solve intersection" << endl;
					solution = this->vector_operations->SolveForIntersection(L, A, B, C, *U);
					// cout << "out of solve intersection" << endl;

					// cout << "beta is " << solution[0] << " gamma is " << solution[1] <<
						//	" and t is " << solution[2]<< endl;

					if (this->vector_operations->no_solution == true) continue;

					if (( (solution[0] > -0.00001) && (solution[1] > -0.00001) &&
							(solution[0]+solution[1] <= 1.000001) && (solution[2] > 0.00001)) /* ||
							(fabs(solution[0]) < 0.00001) || (fabs(solution[1]) < 0.00001) ||
							(fabs(solution[0]+solution[1]-1.00001) < 0.00001 )*/){
						//cout << "Coloring pixel " << endl;
						pixel_colors.at((a-uMin)*vSize + (b-vMin)).SetR(255);
						pixel_colors.at((a-uMin)*vSize + (b-vMin)).SetG(255);
						pixel_colors.at((a-uMin)*vSize + (b-vMin)).SetB(255);

					}

                    delete solution;


				}

			}

		}
	}

	// cout << "going to write ppm" << endl;


	delete this->parse_ply;
	delete this->create_triangles;
}

