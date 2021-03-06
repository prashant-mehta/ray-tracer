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

	for (int i = 0; i < anti_aliasing_pixels; i++) {

		pixel_colors[i].clear();

		pixel_colors[i].resize(uSize * vSize);

	}


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

	min_color = 1;
	max_color = 0;

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

			rV = pixel_colors[0].at((a - vMin) * uSize + (b - uMin)).rValue;
			gV = pixel_colors[0].at((a - vMin) * uSize + (b - uMin)).gValue;
			bV = pixel_colors[0].at((a - vMin) * uSize + (b - uMin)).bValue;

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
#pragma omp parallel for collapse(2)
	for (int a = vMin; a <= vMax; a++) {
		for (int b = uMin; b <= uMax; b++) {

			pixel_colors[0].at((a - vMin) * uSize + (b - uMin)).SetScaledPixels(max_color, min_color);


		}
	}

	cout << "Writing output ppm file" << endl;

	write_ppm = new WritePpm(output_filename.c_str(), uSize, vSize,	pixel_colors[0]);

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




	std::default_random_engine generator;
	uniform_real_distribution<> rand(-0.5, 0.5);

	// For all models


#pragma omp parallel for collapse(2)
	for (int a = vMin; a <= vMax; a++) {
		for (int b = uMin; b <= uMax; b++) {

			float random_scale;

			random_scale = rand(generator);


			for (int p = 0; p < anti_aliasing_pixels; p++) {

					pixel_colors[p].at((a - vMin) * uSize + (b - uMin)).random_scaleU = random_scale*scale_factorsU[p];
					pixel_colors[p].at((a - vMin) * uSize + (b - uMin)).random_scaleV = random_scale*scale_factorsV[p];
			}
		}
	}



	for (int model_index = 0; model_index < this->number_of_models;	model_index++) {


		//cout << "test" << model_index << endl;


		float radiusSquare = radii.at(model_index) * radii.at(model_index);
		//cout << "Radius is " << radius << endl;

		this->mean_vertex = mean_vertices.at(model_index);
		// Calculate c = (mean - fp) and csquare
		float c = this->vector_operations->Distance(this->focal_point,
				&this->mean_vertex);
		float cSquare = c * c;


		if (model_index != 0) {
			start_triangle += num_triangles_in_model.at(model_index-1);
		}
		last_triangle += num_triangles_in_model.at(model_index);

		//cout << start_triangle << " " << last_triangle << endl;


		// For every pixel calculate closest polygons from pixel

#pragma omp parallel for schedule(dynamic,50)
		for (int a = vMin; a <= vMax; a++) {
		//	#pragma omp parallel for schedule(dynamic,1)
			for (int b = uMin; b <= uMax; b++) {


				for (int p = 0; p < anti_aliasing_pixels; p++) {

					float scaleU, scaleV;

					Vertex L;
					Vertex *RayPolygonToFP, *RayFPToPolygon;

					scaleU = pixel_colors[p].at((a - vMin) * uSize + (b - uMin)).random_scaleU;
					scaleV = pixel_colors[p].at((a - vMin) * uSize + (b - uMin)).random_scaleV;

					// Ray - sphere intersection code

					// Step 1: Calculate location of pixel[a,b] in 3-D fp + dn + au + by
					L.x_coordinate = fpPlusdn.x_coordinate
							+ ( (a + scaleV) * this->vVec->x_coordinate)
							+ ( (b + scaleU) * this->uVec->x_coordinate);
					L.y_coordinate = fpPlusdn.y_coordinate
							+ ( (a + scaleV) * this->vVec->y_coordinate)
							+ ( (b + scaleU) * this->uVec->y_coordinate);
					L.z_coordinate = fpPlusdn.z_coordinate
							+ ( (a + scaleV) * this->vVec->z_coordinate)
							+ ( (b + scaleU) * this->uVec->z_coordinate);



					Pixel current_pixel;



					current_pixel.distance_closest_intersection = pixel_colors[p].at((a - vMin) * uSize + (b - uMin)).distance_closest_intersection;
					current_pixel.closest_polygon = pixel_colors[p].at((a - vMin) * uSize + (b - uMin)).closest_polygon;

					// Ray - sphere intersection code


					// Check if ray from pixel intersects with the sphere bounding the object
					bool intersectsSphere = false;
					intersectsSphere = RaySphereIntersection(&L, &RayFPToPolygon, radiusSquare, cSquare);


					if (intersectsSphere) {

						// Only if this is true then go for checking if the ray intersects each face



						RayPolygonToFP = this->vector_operations->GetVector(ZeroVertex, RayFPToPolygon);

						FindClosestPolygon(L, *RayPolygonToFP, &current_pixel, start_triangle, last_triangle, UINT64_MAX);

						pixel_colors[p].at((a - vMin) * uSize + (b - uMin)).distance_closest_intersection = current_pixel.distance_closest_intersection;
						pixel_colors[p].at((a - vMin) * uSize + (b - uMin)).closest_polygon = current_pixel.closest_polygon;


						delete RayPolygonToFP;

					}

					delete RayFPToPolygon;

				}


			}
		}

	}


	cout << "Calculated closest polygons. Now starting reflection." << endl;






	#pragma omp parallel for schedule(dynamic,50)
	for (int a = vMin; a <= vMax; a++) {
	//	#pragma omp parallel for schedule(dynamic,1)
		for (int b = uMin; b <= uMax; b++) {


			for (int p = 0; p < anti_aliasing_pixels; p++) {

				Vertex L;
				Pixel current_pixel;
				Vertex *RayFPToPolygon;

				float scaleU = pixel_colors[p].at((a - vMin) * uSize + (b - uMin)).random_scaleU;
				float scaleV = pixel_colors[p].at((a - vMin) * uSize + (b - uMin)).random_scaleV;


				// Ray - sphere intersection code

				// Step 1: Calculate location of pixel[a,b] in 3-D fp + dn + au + by
				L.x_coordinate = fpPlusdn.x_coordinate
						+ ( (a + scaleV) * this->vVec->x_coordinate)
						+ ( (b + scaleU) * this->uVec->x_coordinate);
				L.y_coordinate = fpPlusdn.y_coordinate
						+ ( (a + scaleV) * this->vVec->y_coordinate)
						+ ( (b + scaleU) * this->uVec->y_coordinate);
				L.z_coordinate = fpPlusdn.z_coordinate
						+ ( (a + scaleV) * this->vVec->z_coordinate)
						+ ( (b + scaleU) * this->uVec->z_coordinate);


				// Check if ray from pixel intersects with the sphere bounding the object
				ComputeRayFPToPolygon(&L, &RayFPToPolygon);

				current_pixel.distance_closest_intersection = pixel_colors[p].at((a - vMin) * uSize + (b - uMin)).distance_closest_intersection;
				current_pixel.closest_polygon = pixel_colors[p].at((a - vMin) * uSize + (b - uMin)).closest_polygon;

				//current_pixel.rValue = pixel_colors[p].at((a - vMin) * uSize + (b - uMin)).rValue;
				//current_pixel.gValue = pixel_colors[p].at((a - vMin) * uSize + (b - uMin)).gValue;
				//current_pixel.bValue = pixel_colors[p].at((a - vMin) * uSize + (b - uMin)).bValue;



				if (current_pixel.closest_polygon != UINT64_MAX && current_pixel.distance_closest_intersection != FLT_MAX) {

					// Only if this is true then go for checking if the ray intersects each face

					Vertex *RayPolygonToFP;
					RayPolygonToFP = this->vector_operations->GetVector(ZeroVertex, RayFPToPolygon);

					Reflection(L, *RayPolygonToFP, &current_pixel, 0);

					pixel_colors[p].at((a - vMin) * uSize + (b - uMin)).rValue = current_pixel.rValue;
					pixel_colors[p].at((a - vMin) * uSize + (b - uMin)).gValue = current_pixel.gValue;
					pixel_colors[p].at((a - vMin) * uSize + (b - uMin)).bValue = current_pixel.bValue;



					delete RayPolygonToFP;

				}

				delete RayFPToPolygon;


			}

		}
	}


#pragma omp parallel for collapse(2)
	for (int a = vMin; a <= vMax; a++) {
		for (int b = uMin; b <= uMax; b++) {

			pixel_colors[0].at((a - vMin) * uSize + (b - uMin)).rValue = meanRValue(pixel_colors, a, b);
			pixel_colors[0].at((a - vMin) * uSize + (b - uMin)).gValue = meanGValue(pixel_colors, a, b);
			pixel_colors[0].at((a - vMin) * uSize + (b - uMin)).bValue = meanBValue(pixel_colors, a, b);


		}
	}


	delete ZeroVertex;
	delete this->create_triangles;
}

void Casting::FindClosestPolygon(Vertex L, Vertex RayPolygonToFP, Pixel *current_pixel, uint64_t start_triangle,
		uint64_t last_triangle, uint64_t current_triangle) {

	// Base cases for recursion



	Vertex *RayFPToPolygon = this->vector_operations->GetVector(ZeroVertex, &RayPolygonToFP);




	// cout << "Coloring pixel " << endl;
	for (uint64_t k = start_triangle; k <last_triangle && k != current_triangle; k++) {


		Vertex A = all_triangles.at(k).getVertexFromFace(0);
		Vertex B = all_triangles.at(k).getVertexFromFace(1);
		Vertex C = all_triangles.at(k).getVertexFromFace(2);
		// cout << "going into solve intersection" << endl;

		bool no_solution = false;

		// For storing beta, gamma and t after solving for system of linear equations
		float *solution = this->vector_operations->SolveForIntersection(L,
				A, B, C, *RayFPToPolygon, no_solution);

		// cout << "out of solve intersection" << endl;


		if (no_solution == true) {
			delete solution;
			continue;

		}

		float t = solution[2];

		if (((solution[0] > -EPSILON) && (solution[1] > -EPSILON) && (solution[0] + solution[1] - 1 < EPSILON )
				&& (t > 0.001)) && (t - current_pixel->distance_closest_intersection < EPSILON) ) {
/*
			if (k == 599) {
				cout << "Solution 0 " << solution[0] << endl;
				cout << "Solution 1 " << solution[1] << endl;
				cout << "Solution 0+1 " << solution[0]+solution[1] << endl;
				cout << "t " << t << endl;
			}
*/
			// t < all other intersections


			current_pixel->distance_closest_intersection = t;
			current_pixel->closest_polygon = k;

		}

		delete solution;
	}

	delete RayFPToPolygon;

}



void Casting::Reflection(Vertex L, Vertex RayPolygonToFP, Pixel *current_pixel, int32_t recursion_level) {

	// Base cases for recursion



	Vertex A, B, C;

	bool ray_shadowed=false;

	uint64_t kmin = current_pixel->closest_polygon; // To keep track of closest polygon from pixel
	float tmin = current_pixel->distance_closest_intersection;

	Vertex LightSource;

	Vertex *RayFPToPolygon = this->vector_operations->GetVector(ZeroVertex, &RayPolygonToFP);


	float NdotL, source_point_distance, VdotR;


	Vertex *SurfaceNormal;


	Vertex *PointOfIntersection;


	// cout << "Coloring pixel " << endl;

	A = all_triangles.at(kmin).getVertexFromFace(0);
	B = all_triangles.at(kmin).getVertexFromFace(1);
	C = all_triangles.at(kmin).getVertexFromFace(2);
	/*
cout << "test1" << endl;
	// Calculate pixel color from ambient light source
	AmbientReflection(all_triangles.at(kmin).getDiffuseReflectance(),
			this->parse_materials->light_sources.at(this->parse_materials->ambient_light_source_index), current_pixel);
	cout << "test2" << endl;

	 */
	// Compute Point of intersection using t
	PointOfIntersection = ComputePointOfIntersection(L, tmin, *RayFPToPolygon);

	/*

	if (kmin == 571 && recursion_level == 1) {
		cout << "POI for kmin - 571 is " ;
		PointOfIntersection->PrintVertex();
	}

	 */
	SurfaceNormal = ComputeSurfaceNormal(A, B, C,&RayPolygonToFP);

	/*
	if (kmin == 599) {
		cout << "NdotL" << this->vector_operations->DotProduct(&RayPolygonToFP, SurfaceNormal) << endl;

	}
	 */
	// Calculate color -- Main part of ray casting
	// For each source of light (except ambient source)
	for (int curr_light = 0; curr_light	< this->parse_materials->light_sources.size(); curr_light++) {
		// Skip ambient light
		if (this->parse_materials->light_sources.at(curr_light).isAmbient != true) {

			Vertex * ReflectedRay, * LightRay, *UnitLightRay;

			LightSource.x_coordinate = this->parse_materials->light_sources.at(curr_light).x_coordinate;
			LightSource.y_coordinate = this->parse_materials->light_sources.at(curr_light).y_coordinate;
			LightSource.z_coordinate = this->parse_materials->light_sources.at(curr_light).z_coordinate;

			// Compute light ray from point of intersection to source
			LightRay = this->vector_operations->GetVector(&LightSource,	PointOfIntersection);

			source_point_distance = this->vector_operations->Distance(&LightSource, PointOfIntersection);

			UnitLightRay = this->vector_operations->Normalize(LightRay);

			// If N.L < 0 --> light and surface normal are in opposite directions, skip current light
			NdotL = this->vector_operations->DotProduct(UnitLightRay, SurfaceNormal);

			// Compute Reflected ray R from point of intersection
			ReflectedRay = ComputeReflectedRay(SurfaceNormal, LightRay);

			VdotR = this->vector_operations->DotProduct(&RayPolygonToFP, ReflectedRay);


			ray_shadowed = false;



			if (NdotL < EPSILON/* || VdotR < -EPSILON*/) {

				ray_shadowed = true;
				delete LightRay;
				delete UnitLightRay;
				delete ReflectedRay;
				break;
			}

			// Intersect ray with all other polygons

			for (uint64_t pIndex = 0; pIndex < all_triangles.size() && pIndex != kmin; pIndex++) {

				if (RayTriangleIntersection(all_triangles.at(pIndex), *UnitLightRay, *PointOfIntersection, source_point_distance) == true) {
					// Light ray is blocked by some polygon

					ray_shadowed = true;
					break;
				}

			}

			if (ray_shadowed != true) {
				// Compute diffuse and specular reflectance

				DiffuseReflection(all_triangles.at(kmin).getDiffuseReflectance(), this->parse_materials->light_sources.at(curr_light), NdotL, current_pixel);

				if (VdotR > -EPSILON) {
					SpecularReflection(all_triangles.at(kmin).getSpecularReflectance(), all_triangles.at(kmin).getShininessExponent(),
							this->parse_materials->light_sources.at(curr_light), VdotR, current_pixel);
				}


			}
			delete LightRay;
			delete UnitLightRay;
			delete ReflectedRay;

		}
		else {
			AmbientReflection(all_triangles.at(kmin).getDiffuseReflectance(),
					this->parse_materials->light_sources.at(this->parse_materials->ambient_light_source_index), current_pixel);
		}

	}


	// Recursive specular reflection
	float ks = all_triangles.at(kmin).getSpecularReflectance();



	if ((ks*current_pixel->rValue > 0.002 || ks*current_pixel->gValue > 0.002 || ks*current_pixel->bValue > 0.002)) {
		Pixel recursive_color;

		// cout << "recursing 1" << endl;
		// Calculate Reflected viewing ray R_v = 2(V.N)N-V


		// V is Ray from POI to FP (non-unit vector)
		Vertex *V = this->vector_operations->GetVector(&L, PointOfIntersection);
		// N is surface normal

		float VdotN = this->vector_operations->DotProduct(V, SurfaceNormal);

		// 2*(V.N)*N
		Vertex *Tv = this->vector_operations->ScaleVector(SurfaceNormal, 2*VdotN);
		Vertex *Rv = this->vector_operations->GetNormalizedVector( Tv, V);

		delete Tv;

		Vertex *InvRv = this->vector_operations->GetVector(ZeroVertex, Rv);



		recursive_color.closest_polygon = UINT64_MAX;
		recursive_color.distance_closest_intersection = FLT_MAX;



		FindClosestPolygon(*PointOfIntersection, *InvRv, &recursive_color, 0, all_triangles.size(), kmin);




		if (recursive_color.closest_polygon != UINT64_MAX && recursive_color.distance_closest_intersection != FLT_MAX) {


			//	if (kmin == 88)
			//cout << "kmin is " << kmin << " closest polygon to it " << recursive_color.closest_polygon << endl;

			recursion_level++;

			if (recursion_level > 20){
				delete Rv;
				delete V;
				delete InvRv;
				delete SurfaceNormal;
				delete PointOfIntersection;
				return;

			}

			/*				if (kmin == 539 | kmin == 599){
			cout << "VdotN " << VdotN << endl;

			cout << "POI of polygon - " << kmin;
			PointOfIntersection->PrintVertex();
			cout << "RvdotSurfaceNormal " << this->vector_operations->DotProduct(InvRv, SurfaceNormal)<< endl;

			cout << "Vertices of kmin polygon are " << endl;
			all_triangles.at(kmin).getVertexFromFace(0).PrintVertex();
			all_triangles.at(kmin).getVertexFromFace(1).PrintVertex();
			all_triangles.at(kmin).getVertexFromFace(2).PrintVertex();

			cout << "recursing - t is" << recursive_color.distance_closest_intersection << endl;

			cout << "Vertices of closest polygon are " << endl;
			all_triangles.at(recursive_color.closest_polygon).getVertexFromFace(0).PrintVertex();
			all_triangles.at(recursive_color.closest_polygon).getVertexFromFace(1).PrintVertex();
			all_triangles.at(recursive_color.closest_polygon).getVertexFromFace(2).PrintVertex();
						}

			 */



			/*cout << "invrv ";
			InvRv->PrintVertex();
			cout << "normal ";
			SurfaceNormal->PrintVertex();

			 */
			//cout << "closest polygon" << recursive_color.closest_polygon << endl;
			Reflection(*PointOfIntersection, *InvRv, &recursive_color, recursion_level);

			current_pixel->rValue += recursive_color.rValue*ks;
			current_pixel->gValue += recursive_color.gValue*ks;
			current_pixel->bValue += recursive_color.bValue*ks;

		}
		delete Rv;
		delete V;
		delete InvRv;


	}


	/*******
	 * For translucency
	 *
	 */

	float kt = all_triangles.at(kmin).getTranslucency();


	if ((kt*current_pixel->rValue > 0.002 || kt*current_pixel->gValue > 0.002 || kt*current_pixel->bValue > 0.002)) {

		uint64_t start_triangle, last_triangle;

		start_triangle = 0;
		last_triangle = 0;

		Pixel translucency_color;
		translucency_color.closest_polygon = UINT64_MAX;
		translucency_color.distance_closest_intersection = FLT_MAX;

		// Consider ray from FP to Polygon and find the next closest polygon to it from another model
		for (int model_index = 0; model_index < this->number_of_models;	model_index++) {

			if (model_index != 0) {
				start_triangle += num_triangles_in_model.at(model_index-1);
			}
			last_triangle += num_triangles_in_model.at(model_index);

			if (kmin >= start_triangle && kmin < last_triangle) {
				// If current triangle is in same model move to next model
				continue;
			}

			FindClosestPolygon(*PointOfIntersection, RayPolygonToFP, &translucency_color, start_triangle, last_triangle, UINT64_MAX);

		}


		if (translucency_color.closest_polygon != UINT64_MAX && translucency_color.distance_closest_intersection != FLT_MAX) {

			recursion_level++;

			if (recursion_level > 20){
				delete SurfaceNormal;
				delete PointOfIntersection;
				return;

			}

			Reflection(*PointOfIntersection, RayPolygonToFP, &translucency_color, recursion_level);

			current_pixel->rValue += translucency_color.rValue*kt;
			current_pixel->gValue += translucency_color.gValue*kt;
			current_pixel->bValue += translucency_color.bValue*kt;

		}

	}


	delete SurfaceNormal;
	delete PointOfIntersection;

}




float Casting::meanRValue(vector<Pixel> const (&pixels)[5], int a, int b) {
	return (pixels[0].at((a - vMin) * uSize + (b - uMin)).rValue + pixels[1].at((a - vMin) * uSize
			+ (b - uMin)).rValue + pixels[2].at((a - vMin) * uSize + (b - uMin)).rValue + pixels[3].at((a - vMin) * uSize + (b - uMin)).rValue
			+ pixels[4].at((a - vMin) * uSize + (b - uMin)).rValue) / 5;
}
float Casting::meanGValue(vector<Pixel> const (&pixels)[5], int a, int b) {
	return (pixels[0].at((a - vMin) * uSize + (b - uMin)).gValue + pixels[1].at((a - vMin) * uSize
			+ (b - uMin)).gValue + pixels[2].at((a - vMin) * uSize + (b - uMin)).gValue + pixels[3].at((a - vMin) * uSize + (b - uMin)).gValue
			+ pixels[4].at((a - vMin) * uSize + (b - uMin)).gValue) / 5;
}
float Casting::meanBValue(vector<Pixel> const (&pixels)[5], int a, int b) {
	return (pixels[0].at((a - vMin) * uSize + (b - uMin)).bValue + pixels[1].at((a - vMin) * uSize
			+ (b - uMin)).bValue + pixels[2].at((a - vMin) * uSize + (b - uMin)).bValue + pixels[3].at((a - vMin) * uSize + (b - uMin)).bValue
			+ pixels[4].at((a - vMin) * uSize + (b - uMin)).bValue) / 5;
}



void Casting::MergeTrianglesFromModels(void) {
	string input_model;

	for (int model_index = 0; model_index < this->number_of_models;
			model_index++) {

		input_model = this->input_models.at(model_index);

		//cout << "Processing input model - " << model_index + 1 << input_model << endl;

		this->parse_ply = new ParsePly(input_model);
		this->parse_ply->ParseAllVertices(this->parse_ply->GetVerticesFilename());

		// Get faces and convert them into triangles
		this->parse_ply->ParseFaces(this->parse_ply->GetFacesFilename());
		//this->parse_ply->PrintPlyAttributes();
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

		//cout << "Before parse materials" << endl;

		this->parse_materials = new ParseMaterials(materials_filename.c_str(),
				triangles, model_index);
		if (model_index == 0) {
			all_triangles = triangles;
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

		delete this->parse_ply;
	}
}


bool Casting::RaySphereIntersection(Vertex *L, Vertex **RayFPToPolygon, float radiusSquare, float cSquare) {

	Vertex LminusE, OminusE;

	float v, vSquare;

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
	*RayFPToPolygon = this->vector_operations->GetNormalizedVector(L,
			this->focal_point);


	// Calculate v = (O - E).U
	OminusE.x_coordinate = this->mean_vertex.x_coordinate
			- this->focal_point->x_coordinate;
	OminusE.y_coordinate = this->mean_vertex.y_coordinate
			- this->focal_point->y_coordinate;
	OminusE.z_coordinate = this->mean_vertex.z_coordinate
			- this->focal_point->z_coordinate;
	v = this->vector_operations->DotProduct(&OminusE, *RayFPToPolygon);

	// cout << "v is " << v << endl;
	vSquare = v * v;

	//L.PrintVertex();
	//U->PrintVertex();

	dSquare = radiusSquare - cSquare + vSquare;

	if (dSquare < EPSILON ) {
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

void Casting::ComputeRayFPToPolygon(Vertex *L, Vertex **RayFPToPolygon) {

	Vertex LminusE, OminusE;

	float v, vSquare;

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
	*RayFPToPolygon = this->vector_operations->GetNormalizedVector(L,
			this->focal_point);
}

bool Casting::RayTriangleIntersection(Face triangle, Vertex ray, Vertex point, float distance) {

	Vertex A, B, C;
	A = triangle.getVertexFromFace(0);
	B = triangle.getVertexFromFace(1);
	C = triangle.getVertexFromFace(2);

	bool no_solution = false;

	float *solution = this->vector_operations->SolveForIntersection(point,	A, B, C, ray, no_solution);

	if (no_solution == true) {
		delete solution;
		return false;
	}

	float t = solution[2];
	float beta = solution[1];
	float gamma = solution[0];


	if ((beta > -EPSILON) && (gamma > -EPSILON) && ( (beta + gamma - 1) < EPSILON ) && (t > EPSILON) && (t - distance < EPSILON)) {
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
	Vertex *CminusA;
	Vertex BminusAtemp, CminusAtemp;
	BminusAtemp.x_coordinate = B.x_coordinate - A.x_coordinate;
	BminusAtemp.y_coordinate = B.y_coordinate - A.y_coordinate;
	BminusAtemp.z_coordinate = B.z_coordinate - A.z_coordinate;

	CminusAtemp.x_coordinate = C.x_coordinate - A.x_coordinate;
	CminusAtemp.y_coordinate = C.y_coordinate - A.y_coordinate;
	CminusAtemp.z_coordinate = C.z_coordinate - A.z_coordinate;

	BminusA = this->vector_operations->Normalize(&BminusAtemp);
	CminusA = this->vector_operations->Normalize(&CminusAtemp);

	Ntemp = this->vector_operations->CrossProduct(BminusA, CminusA);

	N = this->vector_operations->Normalize(Ntemp);

	// If dot product is negative, V and N are in opposite directions compute the other cross product
	if (this->vector_operations->DotProduct(N, V) < -EPSILON) {
		delete Ntemp;
		Ntemp = N;
		N = this->vector_operations->GetVector(ZeroVertex, Ntemp);
	}

	delete BminusA;
	delete CminusA;
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

	temp = R;
	R = this->vector_operations->Normalize(temp);


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
