
#include "Model.hpp"

Model::Model() {

}

Model::Model(Mesh msh, glm::vec3 pos, int id, glm::vec3 rot) {
	this->mesh = msh;
	this->id = id;
	this->translate_matrix = glm::translate( pos );
	//this->rotation_matrix = glm::normalize(glm::quat(rot));
	this->rotation_matrix = glm::quat(vec3(radians(rot.x), radians(rot.y), radians(rot.z)));
	ModelMatrix = glm::mat4(1.0);
}

glm::mat4 Model::getTransformMatrix()
{
	return transform_matrix;
}

glm::mat4 Model::getModelMatrix()
{
	return this->ModelMatrix;
}

glm::mat4 Model::getTranslateMatrix()
{
	return translate_matrix;
}

glm::quat Model::getRotationMatrix()
{
	return this->rotation_matrix;
}

int Model::getId()
{
	return id;
}

GLuint Model::getTexture()
{
	return mesh.getTexture();
}

void Model::setTransformMatrix(glm::mat4 &matrix)
{
	this->transform_matrix = matrix;
}

void Model::translate(glm::mat4 trans_mat)
{
	//if(translate_matrix[3][0] >= 1)
	//	translate_matrix[3][0] -= trans_mat[3][0];

	//if (translate_matrix[3][1] <= -2)
	//	translate_matrix[3][1] -= trans_mat[3][1];

	translate_matrix[3][0] = trans_mat[3][0];
	translate_matrix[3][1] = trans_mat[3][1];
	translate_matrix[3][2] = trans_mat[3][2];

}

void Model::scale(glm::mat4 scale_mat)
{
	scale_matrix = scale_mat;
}

void Model::rotation(glm::quat rot_mat)
{
	rotation_matrix = rot_mat;
}

void Model::shear(glm::mat4 shear_mat)
{
	shear_matrix *= shear_mat;
}

void Model::setTransformation()
{
	transform_matrix = translate_matrix * shear_matrix * glm::toMat4(rotation_matrix) * scale_matrix;

	this->ModelMatrix = this->transform_matrix;
}

void Model::drawModel() {

	GLuint vertexbuffer = mesh.getVertexBuffer();
	GLuint uvbuffer = mesh.getUvBuffer();
	GLuint normalbuffer = mesh.getNormalBuffer();
	GLuint elementbuffer = mesh.getElementBuffer();

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,        // mode
		mesh.getIndices().size(),      // count
		GL_UNSIGNED_SHORT,   // type
		(void*)0             // element array buffer offset
	);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

}