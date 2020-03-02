#include "Shader.h"

Shader::Shader(const std::string& vertexShaderFilepath, const std::string& fragmentShaderFilepath)
    :
    m_VertexShaderFilePath(vertexShaderFilepath),
    m_FragmentShaderFilePath(fragmentShaderFilepath),
    m_ShaderProgramID(0)
{
    std::string vertexShaderCode = ParseShader(vertexShaderFilepath);
    std::string fragmentShaderCode = ParseShader(fragmentShaderFilepath);

    SetDefaultShaders();
    m_ShaderProgramID = CreateShader(vertexShaderCode, fragmentShaderCode);
}

Shader::~Shader()
{
    glDeleteProgram(m_ShaderProgramID);
}

std::string Shader::ParseShader(const std::string& filepath)
{
    std::ifstream file;
    std::string line;
    std::stringstream sourceCode;

    file.open(filepath);

    if (file.is_open())
        while (getline(file, line))
            sourceCode << line << std::endl;

    file.close();

    return sourceCode.str();
}

GLuint Shader::CreateShader(const std::string& vertextShaderSource, const std::string& fragmentShaderSource)
{
    GLuint shaderProgram = glCreateProgram();
    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertextShaderSource);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);
    glValidateProgram(shaderProgram);

    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

GLuint Shader::CompileShader(GLuint type, const std::string& source)
{
    GLuint id = glCreateShader(type);
    const GLchar* src = source.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    GLint result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        GLint length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        GLchar* message = (GLchar*)_malloca(length * sizeof(GLchar));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
        glDeleteShader(id);
        _freea(message);

        return 0;
    }

    return id;
}

void Shader::Bind()
{
    glUseProgram(m_ShaderProgramID);
}

void Shader::UnBind()
{
    glUseProgram(0);
}

void Shader::SetDefaultShaders()
{
    for (int i = 0; i < sizeof(GLfloat); i++)
        m_UniformFloats.push_back(1.0f);
}

void Shader::SetUniform1f(const std::string& name, GLfloat value)
{
    m_UniformFloats[0] = value;
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform2f(const std::string& name, GLfloat value)
{
    m_UniformFloats[1] = value;
    glUniform2f(GetUniformLocation(name), m_UniformFloats[0], value);
}

void Shader::SetUniform3f(const std::string& name, GLfloat value)
{
    m_UniformFloats[2] = value;
    glUniform3f(GetUniformLocation(name), m_UniformFloats[0], m_UniformFloats[1], value);
}

void Shader::SetUniform4f(const std::string& name, GLfloat value)
{
    m_UniformFloats[3] = value;
    glUniform4f(GetUniformLocation(name), m_UniformFloats[0], m_UniformFloats[1], m_UniformFloats[2], value);
}

GLuint Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLint location = glGetUniformLocation(m_ShaderProgramID, name.c_str());
    m_UniformLocationCache[name] = location;

    return location;
}
