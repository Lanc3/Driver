#include "ResourceManager.h"

std::map<std::string, Mesh> ResourceManager::madeMeshes;
//std::map<std::string, MeshData> ResourceManager::meshMap;
std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Textures> ResourceManager::textures;

Shader ResourceManager::LoadShader(const GLchar * vShaderFile, const GLchar * fShaderFile, const GLchar * gShaderFile, std::string name)
{
	shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return shaders[name];
}

Shader ResourceManager::GetShader(string name)
{
	return shaders[name];
}

Textures ResourceManager::LoadTexture(const GLchar * file, GLboolean alpha, std::string name)
{
	textures[name] = loadTextureFromFile(file, alpha);
	return textures[name];
}

Textures ResourceManager::GetTexture(string name)
{
	return textures[name];
}

Textures ResourceManager::loadTextureFromFile(const GLchar * file, GLboolean alpha)
{
	Textures texture;

	if (alpha)
	{
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}

	int width;
	int height;

	unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGB : SOIL_LOAD_RGB);

	texture.Generate(width, height, image);

	SOIL_free_image_data(image);
	return texture;
}

void ResourceManager::LoadMeshes(std::string path, string name)
{	

}

void ResourceManager::LoadModel(string path, string name)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "ERROR::ASSIMP:: " << import.GetErrorString() << endl;
		return;
	}

	this->directory = path.substr(0, path.find_last_of("\\"));
	this->processNode(scene->mRootNode, scene, name);
}

void ResourceManager::processNode(aiNode * node, const aiScene * scene, string name)
{

	for (GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->meshes.push_back(this->processMesh(mesh, scene, name));
	}

	for (GLuint i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(node->mChildren[i], scene, name);
	}
}

Mesh ResourceManager::processMesh(aiMesh * mesh, const aiScene * scene, string name)
{
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	for (GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;

			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
		{
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}

	for (GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (GLuint j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	MeshData m;
	m.indices = indices;
	m.vertexes = vertices;
	m.textures = textures;

	meshData = m;

	BuildMesh(name);

	return Mesh(vertices, indices, textures);
}

void ResourceManager::BuildMesh(string name)
{
	vector<Vertex> vs;
	vector<Texture> ts;
	vector<GLuint> gs;


	Mesh builtMesh = Mesh(meshData.vertexes, meshData.indices, meshData.textures);

	madeMeshes[name] = builtMesh;
}

Mesh ResourceManager::GetMesh(string name)
{
	return madeMeshes[name];
}

void ResourceManager::Clear()
{
	for (auto iter : shaders)
	{
		glDeleteProgram(iter.second.ID);
	}
}

Shader ResourceManager::loadShaderFromFile(const GLchar * vShaderFile, const GLchar * fShaderFile, const GLchar * gShaderFile)
{
	string vertexCode;
	string fragmentCode;
	string geometryCode;

	try
	{
		ifstream vertexShaderFile(vShaderFile);
		ifstream fragmentShaderFile(fShaderFile);
		stringstream vShaderStream, fShaderStream;

		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();

		vertexShaderFile.close();
		fragmentShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

		if (gShaderFile != nullptr)
		{
			ifstream geometryShaderFile(gShaderFile);
			stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (exception e)
	{
		cout << "ERROR::SHADER: Failed to read shader files" << endl;
	}

	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	const GLchar *gShaderCode = geometryCode.c_str();;

	Shader shader;
	shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);

	return shader;
}

vector<Texture> ResourceManager::loadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName)
{
	vector<Texture> textures;

	GLuint h = mat->GetTextureCount(type);

	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		GLboolean skip = false;

		for (GLuint j = 0; j < textures_loaded.size(); j++)
		{
			if (textures_loaded[j].path == str)
			{
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{

			Texture tex;
			tex.id = textureFromFile(str.C_Str(), this->directory);
			tex.type = typeName;
			tex.path = str;
			textures.push_back(tex);
			this->textures_loaded.push_back(tex);
		}
	}
	return textures;
}

GLint ResourceManager::textureFromFile(const char * path, string directory)
{
	string filename = string(path);
	filename = directory + '\\' + filename;

	GLuint textureID;
	glGenTextures(1, &textureID);
	int width, height;
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	//glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}