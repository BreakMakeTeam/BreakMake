#include <OGL3D/Graphics/OVertexArrayObject.h>
#include <glad/glad.h>

OVertexArrayObject::OVertexArrayObject(const OVBufferData& data)
{
	glGenBuffers(1, &VBufferID);
	glGenVertexArrays(1, &VArrayID);

	glBindVertexArray(VArrayID);

	glBindBuffer(GL_ARRAY_BUFFER, VBufferID);
	glBufferData(GL_ARRAY_BUFFER, data.vertSize * data.listSize, data.vertList, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, data.vertSize, 0);
	glEnableVertexAttribArray(0);


	glBindVertexArray(0);
}

OVertexArrayObject::~OVertexArrayObject()
{
	glDeleteBuffers(1, &VBufferID);
	glDeleteVertexArrays(1, &VArrayID);
}

ui32 OVertexArrayObject::getID()
{
	return VArrayID;
}
