#include <vector>
#include <string>
#include <stdio.h>
#include <SDL_opengl.h>


class Terrain
{
    //Estos serán nuestros vertices
    struct vertex {
        double x;
        double y;
        double z;
    };
    struct face {
        unsigned int v1, v2, v3;
        unsigned int n1, n2, n3;
    };
    //Declaramos los arreglos de vertices y de caras
    std::vector<vertex> vertices;
    std::vector<vertex> normales;
    std::vector<face> caras;

    GLuint width;
    GLuint depth;

public:
    //Función de lectura del archivo
    void generateMesh(GLuint width,GLuint depth);
    //Función de dibujo del modelo
    void solidDraw(GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLfloat shininess);
    void wireDraw();
    GLfloat getHeight(GLfloat x, GLfloat z);
};