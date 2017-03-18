#include "static_sprite.h"
namespace Graphics
{

	StaticSprite::StaticSprite(glm::vec3 pos, glm::vec3 size, glm::vec4 color,Shader& shader, glm::mat4& model, glm::mat4& projection, glm::mat4& view)
		: Model(pos,size,color,model, projection, view) ,m_Shader(shader)
	{

		

		m_VertexArray = new VertexArray();

		GLfloat vertices[] =
		{
			//Back
			size.x,			0,			0,
			0,				0,			0,
			0,				size.y,		0,
			size.x,			size.y,		0,

			//Right-Side
			size.x,			0,			size.z,
			size.x,			0,			0,
			size.x,			size.y,		0,
			size.x,			size.y,		size.z,

			//Front
			0,				0,			size.z,
			size.x,			0,			size.z,
			size.x,			size.y,		size.z,
			0,				size.y,		size.z,

			//Left
			0,				0,			0,
			0,				0,			size.z,
			0,				size.y,		size.z,
			0,				size.y,		0,

			//Top
			0,				size.y,		size.z,
			size.x,			size.y,		size.z,
			size.x,			size.y,		0,
			0,				size.y,		0,

			//Bottom
			0,				0,			0,
			size.x,			0,			0,
			size.x,			0,			size.z,
			0,				0,			size.z

		};


		GLfloat normals[] = {
			// back
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,
			0.0f, 0.0f, -1.0f,

			// Right-Side
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f,

			// Front
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,

			// Left-Side
			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,
			-1.0f, 0.0f, 0.0f,

			// top
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 1.0f, 0.0f,

			// bottom
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,
			0.0f, -1.0f, 0.0f,

		};


		GLfloat colors[] =
		{
			color.x, color.y, color.z, color.a,
			color.x, color.y, color.z, color.a,
			color.x, color.y, color.z, color.a,
			color.x, color.y, color.z, color.a,

			color.x, color.y, color.z, color.a,
			color.x, color.y, color.z, color.a,
			color.x, color.y, color.z, color.a,
			color.x, color.y, color.z, color.a,

			color.x, color.y, color.z, color.a,
			color.x, color.y, color.z, color.a,
			color.x, color.y, color.z, color.a,
			color.x, color.y, color.z, color.a,

			color.x, color.y, color.z, color.a,
			color.x, color.y, color.z, color.a,
			color.x, color.y, color.z, color.a,
			color.x, color.y, color.z, color.a,

			color.x, color.y, color.z, color.a,
			color.x, color.y, color.z, color.a,
			color.x, color.y, color.z, color.a,
			color.x, color.y, color.z, color.a,

			color.x, color.y, color.z, color.a,
			color.x, color.y, color.z, color.a,
			color.x, color.y, color.z, color.a,
			color.x, color.y, color.z, color.a,
		};

		m_VertexArray->addBuffers(new Buffer(vertices, 6 * 4 * 3, 3), 0);
		m_VertexArray->addBuffers(new Buffer(colors, 4 * 4 * 6, 4), 1);
		m_VertexArray->addBuffers(new Buffer(normals, 6 * 4 * 3, 3), 2);

		GLushort indices[] =
		{
			0,	1,	2,
			2,	3,	0,

			4,	5,	6,
			6,	7,	4,

			8,	9,	10,
			10, 11,	8,

			12, 13, 14,
			14, 15, 12,

			16, 17, 18,
			18, 19, 16,

			20, 21, 22,
			22, 23, 20
		};

		m_IndexBuffer = new IndexBuffer(indices, 36);




	}

	StaticSprite::~StaticSprite()
	{
		delete m_VertexArray;
		delete m_IndexBuffer;
	}

}