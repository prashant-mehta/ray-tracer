/*
 * Silhouette.cpp
 *
 *  Created on: Oct 10, 2015
 *      Author: prashantm
 */

#include <Casting.h>

Casting::Casting(int argc, char **argv) {
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

	pixel_colors.resize(uSize * vSize);

	// Calculate projection matrix
	this->projection_matrix = new ProjectionMatrix(*this->focal_point,
			*this->look_at_point, *this->vup_vector, this->focal_length);
	this->uVec = this->projection_matrix->GetuVector();
	this->vVec = this->projection_matrix->GetvVector();
	this->nVec = this->projection_matrix->GetnVector();

	// Test vectors
	// this->uVec->PrintVertex();
	// this->vVec->PrintVertex();
	// this->nVec->PrintVertex();

	this->matrix_operations = new MatrixOperations;
	this->vector_operations = new VectorOperations;

	ZeroVertex = new Vertex();

	// Calculate fp + dn
	fpPlusdn.x_coordinate = this->focal_point->x_coordinate
			+ (this->focal_length * this->nVec->x_coordinate);
	fpPlusdn.y_coordinate = this->focal_point->y_coordinate
			+ (this->focal_length * this->nVec->y_coordinate);
	fpPlusdn.z_coordinate = this->focal_point->z_coordinate
			+ (this->focal_length * this->nVec->z_coordinate);

	min_color = 0;
	max_color = 1;

	/*	// Generate Silhouette for each model
	 for (int model_index = 0; model_index < this->number_of_models; model_index++) {

	 cout << "Processing input model - " << model_index + 1 << endl;
	 this->CastingForModel(this->input_models.at(model_index).c_str(), model_index);
	 }
	 */
	this->CastingForModel();
	// this->matrix_operations->PrintMatrix(this->projection_matrix->GetProjectionMatrix());

	float rV, gV, bV;

	// Find out min and max of all colors
	for (int a = vMin; a <= vMax; a++) {
		for (int b = uMin; b <= uMax; b++) {

			rV = pixel_colors.at((a - vMin) * uSize + (b - uMin)).rValue;
			gV = pixel_colors.at((a - vMin) * uSize + (b - uMin)).gValue;
			bV = pixel_colors.at((a - vMin) * uSize + (b - uMin)).bValue;

			// To make sure colors are not greater than 1 or less than 0
			rV = std::min(rV, (float) 1.0);
			gV = std::min(gV, (float) 1.0);
			bV = std::min(bV, (float) 1.0);

			rV = std::max(rV, (float) 0.0);
			gV = std::max(gV, (float) 0.0);
			bV = std::max(bV, (float) 0.0);

			float minV = std::min(rV, std::min(gV, bV));
			float maxV = std::max(rV, std::max(gV, bV));

			min_color = min(minV, min_color);
			max_color = max(maxV, max_color);
		}
	}

	// Scale all pixels to min and max before writing out
	// For every pixel
	for (int a = vMin; a <= vMax; a++) {
		for (int b = uMin; b <= uMax; b++) {
			pixel_colors.at((a - vMin) * uSize + (b - uMin)).SetScaledPixels(max_color, min_color);

		}
	}

	write_ppm = new WritePpm(output_filename.c_str(), uSize, vSize,	pixel_colors);

	delete write_ppm;
	delete this->uVec;
	delete this->vVec;
	delete this->nVec;
	delete this->matrix_operations;
	delete this->vector_operations;
}

void Casting::ParseArguments(int argc, char **argv) {
	for (int i = 1; i <= argc - 1; i++) {
		if (i == 1) {
			camera_filename = argv[i];
		} else if (i == 2) {
			materials_filename = argv[i];
		} else if (i == argc - 1) {

			output_filename = argv[i];
		} else {
			this->input_models.push_back(argv[i]);
			//cout << argv[i] << endl;
			this->number_of_models++;
		}
	}
}

// This function is to generate silhouette for each model
void Casting::CastingForModel(void) {

	// Distance to intersection from image pixel
	float t;
	uint64_t start_triangle, last_triangle;



	start_triangle = 0;
	last_triangle = 0;



	this->MergeTrianglesFromModels();



	// NdotL -- where N - SurfaceNormal L - UnitLightray


	bool intersectsSphere;

	// For all models
	for (int model_index = 0; model_index < this->number_of_models;
			model_index++) {

		Vertex L;

		Vertex *RayPolygonToFP;







		radiusSquare = radii.at(model_index) * radii.at(model_index);
		//cout << "Radius is " << radius << endl;

		this->mean_vertex = mean_vertices.at(model_index);
		// Calculate c = (mean - fp) and csquare
		c = this->vector_operations->Distance(this->focal_point,
				&this->mean_vertex);
		cSquare = c * c;



		// For every pixel
		for (int a = vMin; a <= vMax; a++) {
			for (int b = uMin; b <= uMax; b++) {




				// Ray - sphere intersection code

				// Step 1: Calculate location of pixel[a,b] in 3-D fp + dn + au + by
				L.x_coordinate = fpPlusdn.x_coordinate
						+ (a * this->vVec->x_coordinate)
						+ (b * this->uVec->x_coordinate);
				L.y_coordinate = fpPlusdn.y_coordinate
						+ (a * this->vVec->y_coordinate)
						+ (b * this->uVec->y_coordinate);
				L.z_coordinate = fpPlusdn.z_coordinate
						+ (a * this->vVec->z_coordinate)
						+ (b * this->uVec->z_coordinate);


				// Check if ray from pixel intersects with the sphere bounding the object
				intersectsSphere = false;
				intersectsSphere = RaySphereIntersection(&L, &RayPolygonToFP);


				if (intersectsSphere) {

					// Only if this is true then go for checking if the ray intersects each face

					Pixel current_pixel;

					current_pixel.distance_closest_intersection = pixel_colors.at((a - vMin) * uSize + (b - uMin)).distance_closest_intersection;
					current_pixel.rValue = pixel_colors.at((a - vMin) * uSize + (b - uMin)).rValue;
					current_pixel.gValue = pixel_colors.at((a - vMin) * uSize + (b - uMin)).gValue;
					current_pixel.bValue = pixel_colors.at((a - vMin) * uSize + (b - uMin)).bValue;

					Reflection(L, *RayPolygonToFP, model_index, &current_pixel);

					pixel_colors.at((a - vMin) * uSize + (b - uMin)).distance_closest_intersection = current_pixel.distance_closest_intersection ;
					pixel_colors.at((a - vMin) * uSize + (b - uMin)).rValue = current_pixel.rValue;
					pixel_colors.at((a - vMin) * uSize + (b - uMin)).gValue = current_pixel.gValue;
					pixel_colors.at((a - vMin) * uSize + (b - uMin)).bValue = current_pixel.bValue;


				}

				delete U;

			}
		}

		// cout << "going to write ppm" << endl;




	}
	delete ZeroVertex;
	delete this->parse_ply;
	delete this->create_triangles;
}

void Casting::Reflection(Vertex L, Vertex RayPolygonToFP, int model_index, Pixel *current_pixel) {
	Vertex A, B, C;

	bool ray_shadowed=false;


	Vertex * LightRay, *UnitLightRay, LightSource;

	uint64_t start_triangle=0;
	uint64_t last_triangle=0;

	Vertex *RayFPToPolygon = this->vector_operations->GetVector(ZeroVertex, &RayPolygonToFP);


	float NdotL, source_point_distance, VdotR;


	float t;

	Vertex *SurfaceNormal;
	Vertex * ReflectedRay;

	Vertex *PointOfIntersection;

	if (model_index != 0) {
		start_triangle += num_triangles_in_model.at(model_index-1);
	}
	last_triangle += num_triangles_in_model.at(model_index);

	// For storing beta, gamma and t after solving for system of linear equations
	float *solution;
	// cout << "Coloring pixel " << endl;
	for (int k = start_triangle; k <last_triangle; k++) {
		A = all_triangles.at(k).getVertexFromFace(0);
		B = all_triangles.at(k).getVertexFromFace(1);
		C = all_triangles.at(k).getVertexFromFace(2);
		// cout << "going into solve intersection" << endl;
		solution = this->vector_operations->SolveForIntersection(L,
				A, B, C, *RayFPToPolygon);
		// cout << "out of solve intersection" << endl;


		if (this->vector_operations->no_solution == true) {
			delete solution;
			continue;

		}

		t = solution[2];

		if (((solution[0] > -EPSILON) && (solution[1] > -EPSILON)
				&& (solution[0] + solution[1] < 1 + EPSILON)
				&& (t > -EPSILON)) /* ||
	 (fabs(solution[0]) < 0.00001) || (fabs(solution[1]) < 0.00001) ||
	 (fabs(solution[0]+solution[1]-1.00001) < 0.00001 )*/) {
			/*
		// For producing silhouette
		//pixel_colors.at((a-uMin)*vSize + (b-vMin)).rValue = 1.0;
		//pixel_colors.at((a-uMin)*vSize + (b-vMin)).gValue = 1.0;
		//pixel_colors.at((a-uMin)*vSize + (b-vMin)).bValue = 1.0;

		pixel_colors.at((a-uMin)*vSize + (b-vMin)).SetR(255);
		pixel_colors.at((a-uMin)*vSize + (b-vMin)).SetG(255);
		pixel_colors.at((a-uMin)*vSize + (b-vMin)).SetB(255);
			 */


			if (t < current_pixel->distance_closest_intersection) {


				// t < all other intersections
				current_pixel->distance_closest_intersection = t;




				// Calculate pixel color from ambient light source
				AmbientReflection(all_triangles.at(k).getDiffuseReflectance(),
						this->parse_materials->light_sources.at(this->parse_materials->ambient_light_source_index), current_pixel);



				// Compute Point of intersection using t
				PointOfIntersection = ComputePointOfIntersection(L, t, *RayFPToPolygon);


				SurfaceNormal = ComputeSurfaceNormal(A, B, C,&RayPolygonToFP);

				// Calculate color -- Main part of ray casting
				// For each source of light (except ambient source)
				for (int curr_light = 0; curr_light	< this->parse_materials->light_sources.size(); curr_light++) {
					// Skip ambient light
					if (this->parse_materials->light_sources.at(
							curr_light).isAmbient != true) {

						LightSource.x_coordinate =
								this->parse_materials->light_sources.at(
										curr_light).x_coordinate;
						LightSource.y_coordinate =
								this->parse_materials->light_sources.at(
										curr_light).y_coordinate;
						LightSource.z_coordinate =
								this->parse_materials->light_sources.at(
										curr_light).z_coordinate;

						// Compute light ray from point of intersection to source
						LightRay =
								this->vector_operations->GetVector(
										&LightSource,
										PointOfIntersection);

						source_point_distance = this->vector_operations->Distance(&LightSource, PointOfIntersection);

						UnitLightRay =
								this->vector_operations->Normalize(
										LightRay);



						// If N.L < 0 --> light and surface normal are in opposite directions, skip current light
						NdotL = this->vector_operations->DotProduct(
								UnitLightRay, SurfaceNormal);

						// Compute Reflected ray R from point of intersection
						ReflectedRay = ComputeReflectedRay(SurfaceNormal, LightRay);

						VdotR = this->vector_operations->DotProduct(&RayPolygonToFP, ReflectedRay);


						if (NdotL < -EPSILON/* || VdotR < -EPSILON*/) {
							delete LightRay;
							delete UnitLightRay;
							delete ReflectedRay;
							break;
						}

						// Intersect ray with all other polygons
						ray_shadowed = false;

						for (uint64_t pIndex = 0; pIndex < all_triangles.size() && pIndex != k; pIndex++) {

							if (RayTriangleIntersection(all_triangles.at(pIndex), *UnitLightRay, *PointOfIntersection, source_point_distance) == true) {
								// Light ray is blocked by some polygon

								ray_shadowed = true;
								break;
							}

						}

						if (ray_shadowed != true) {
							// Compute diffuse and specular reflectance

							DiffuseReflection(all_triangles.at(k).getDiffuseReflectance(), this->parse_materials->light_sources.at(curr_light), NdotL, current_pixel);

							if (VdotR < -EPSILON) {
							SpecularReflection(all_triangles.at(k).getSpecularReflectance(), all_triangles.at(k).getShininessExponent(),
									this->parse_materials->light_sources.at(curr_light), VdotR, current_pixel);

							}

						}
						delete LightRay;
						delete UnitLightRay;
						delete ReflectedRay;

					}

				}

				delete SurfaceNormal;
				delete PointOfIntersection;
			}



		}

		delete solution;

	}


	delete RayFPToPolygon;
}


void Casting::MergeTrianglesFromModels(void) {
	string input_model;

	for (int model_index = 0; model_index < this->number_of_models;
			model_index++) {

		input_model = this->input_models.at(model_index);

		cout << "Processing input model - " << model_index + 1 << input_model << endl;

		this->parse_ply = new ParsePly(input_model);
		this->parse_ply->ParseAllVertices(input_model+ "_vertices.txt");

		// Get faces and convert them into triangles
		this->parse_ply->ParseFaces(
				input_model + "_faces.txt");
		this->parse_ply->PrintPlyAttributes();
		vector<Face> triangles;

		triangles.clear();

		if (this->parse_ply->all_triangles != true) {



			this->create_triangles = new CreateTriangles(
					this->parse_ply->GetParsedFaces());

			triangles = this->create_triangles->GetTriangles();
		} else {
			triangles = this->parse_ply->GetParsedFaces();
		}


		this->mean_vertex = *this->parse_ply->GetMeanVertex();

		this->parse_materials = new ParseMaterials(materials_filename.c_str(),
				triangles, model_index);
		if (model_index == 0) {
			all_triangles = triangles;

			//cout << all_triangles.size() << endl;
		}
		else {
			all_triangles.insert(all_triangles.end(), triangles.begin(),
					triangles.end());
		}

		// Test triangles
		// this->write_ply = new WritePly("triangles.txt");
		// this->write_ply->WriteFacesFromVector(triangles);
		// this->write_ply->CloseWriteFile();

		uint64_t num_triangles = triangles.size();

		//cout << "Mean vertex is" << endl;
		//this->mean_vertex.PrintVertex();

		radius = this->parse_ply->GetRadius();

		radii.push_back(radius);
		mean_vertices.push_back(mean_vertex);
		num_triangles_in_model.push_back(num_triangles);
	}
}


bool Casting::RaySphereIntersection(Vertex *L, Vertex **RayPolygonToFP) {

	Vertex LminusE, OminusE;

	float s, d, dSquare;

	// Calculate U - Normalized (L - fp)
	LminusE.x_coordinate = L->x_coordinate
			- this->focal_point->x_coordinate;
	LminusE.y_coordinate = L->y_coordinate
			- this->focal_point->y_coordinate;
	LminusE.z_coordinate = L->z_coordinate
			- this->focal_point->z_coordinate;

	// U = this->vector_operations->Normalize(&LminusE);

	// U - Vector from fp to pixel
	U = this->vector_operations->GetNormalizedVector(L,
			this->focal_point);

	// V = -U in class slides
	*RayPolygonToFP = this->vector_operations->GetVector(ZeroVertex, U);

	// Calculate v = (O - E).U
	OminusE.x_coordinate = this->mean_vertex.x_coordinate
			- this->focal_point->x_coordinate;
	OminusE.y_coordinate = this->mean_vertex.y_coordinate
			- this->focal_point->y_coordinate;
	OminusE.z_coordinate = this->mean_vertex.z_coordinate
			- this->focal_point->z_coordinate;
	v = this->vector_operations->DotProduct(&OminusE, U);

	// cout << "v is " << v << endl;
	vSquare = v * v;

	//L.PrintVertex();
	//U->PrintVertex();

	dSquare = radiusSquare - cSquare + vSquare;

	if (dSquare < -EPSILON || (radiusSquare < (cSquare - vSquare))) {
		// cout << "dSqaure negative" << endl;
		// continue;
		return false;
	}

	d = sqrt(dSquare);

	if (cSquare > radiusSquare) {
		s = v - d;
	} else
		s = v + d;

	if (s > EPSILON) {
		return true;
	}
	return false;

}

bool Casting::RayTriangleIntersection(Face triangle, Vertex ray, Vertex point, float distance) {

	Vertex A, B, C;
	A = triangle.getVertexFromFace(0);
	B = triangle.getVertexFromFace(1);
	C = triangle.getVertexFromFace(2);


	float *solution = this->vector_operations->SolveForIntersection(point,	A, B, C, ray);

	if (this->vector_operations->no_solution == true) {
		delete solution;
		return false;
	}

	float t = solution[2];
	float beta = solution[1];
	float gamma = solution[0];


	if ((beta > -EPSILON) && (gamma > -EPSILON) && (beta + gamma < 1 + EPSILON) && (t > EPSILON) && (t < distance)) {
		// Light ray intersects polygon
		delete solution;
		return true;
	}

	delete solution;
	return false;
}

Vertex * Casting::ComputeSurfaceNormal(Vertex A, Vertex B, Vertex C,
		Vertex *V) {
	Vertex * N;

	Vertex * Ntemp;
	Vertex *BminusA;
	Vertex *CminusB;
	Vertex BminusAtemp, CminusBtemp;
	BminusAtemp.x_coordinate = B.x_coordinate - A.x_coordinate;
	BminusAtemp.y_coordinate = B.y_coordinate - A.y_coordinate;
	BminusAtemp.z_coordinate = B.z_coordinate - A.z_coordinate;

	CminusBtemp.x_coordinate = C.x_coordinate - B.x_coordinate;
	CminusBtemp.y_coordinate = C.y_coordinate - B.y_coordinate;
	CminusBtemp.z_coordinate = C.z_coordinate - B.z_coordinate;

	BminusA = this->vector_operations->Normalize(&BminusAtemp);
	CminusB = this->vector_operations->Normalize(&CminusBtemp);

	Ntemp = this->vector_operations->CrossProduct(BminusA, CminusB);

	N = this->vector_operations->Normalize(Ntemp);

	// If dot product is negative, V and N are in opposite directions compute the other cross product
	if (this->vector_operations->DotProduct(N, V) < EPSILON) {
		Ntemp = N;
		N = this->vector_operations->GetVector(ZeroVertex, Ntemp);
	}

	delete BminusA;
	delete CminusB;
	delete Ntemp;

	return N;

}

Vertex * Casting::ComputePointOfIntersection(Vertex L, float t, Vertex UnitVector) {
	Vertex * P = new Vertex();

	P->x_coordinate = L.x_coordinate + (t * UnitVector.x_coordinate);
	P->y_coordinate = L.y_coordinate + (t * UnitVector.y_coordinate);
	P->z_coordinate = L.z_coordinate + (t * UnitVector.z_coordinate);

	return P;

}

Vertex * Casting::ComputeReflectedRay(Vertex *N, Vertex *L) {

	Vertex * R;
	Vertex * T;
	Vertex * Nl;

	Vertex * temp;

	// N_l = (L.N), N -> Projection of L onto N
	Nl = this->vector_operations->ScaleVector(N,
			this->vector_operations->DotProduct(L, N));

	// T = N_l - L
	T = this->vector_operations->GetVector(Nl, L);

	// T = 2T
	temp = T;
	T = this->vector_operations->ScaleVector(temp, 2);

	R = this->vector_operations->AddVectors(L, T);

	delete temp;
	delete Nl;
	delete T;

	return R;

}

void Casting::AmbientReflection(float *diffuse_reflectance, LightSource ls, Pixel *current_pixel) {

	float rV, gV, bV;

	rV = diffuse_reflectance[0] * ls.rValue;
	gV = diffuse_reflectance[1] * ls.gValue;
	bV = diffuse_reflectance[2] * ls.bValue;


	current_pixel->rValue = rV;
	current_pixel->gValue = gV;
	current_pixel->bValue = bV;

}

void Casting::DiffuseReflection(float *diffuse_reflectance, LightSource ls, float cosTheta, Pixel *current_pixel) {

	float rV, gV, bV;

	rV = diffuse_reflectance[0] * ls.rValue * cosTheta;
	gV = diffuse_reflectance[0] * ls.gValue * cosTheta;
	bV = diffuse_reflectance[0] * ls.bValue * cosTheta;

	current_pixel->rValue += rV;
	current_pixel->gValue += gV;
	current_pixel->bValue += bV;

}

void Casting::SpecularReflection(float specular_reflectance, float shininess_exponent, LightSource ls, float VdotR, Pixel *current_pixel) {
	float rV, gV, bV;

	rV = specular_reflectance * ls.rValue * pow(VdotR, shininess_exponent);
	gV = specular_reflectance * ls.gValue * pow(VdotR, shininess_exponent);
	bV = specular_reflectance * ls.bValue * pow(VdotR, shininess_exponent);


	current_pixel->rValue += rV;
	current_pixel->gValue += gV;
	current_pixel->bValue += bV;
}
