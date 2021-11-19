#include "terreno.h"

void Terrain::generateMesh(GLuint width,GLuint depth)
{
    double inc = 1;
    this->width = width;
    this->depth = depth;
    int i, j,count;
    int aux[4];
  
    face f;
    vertex v;

    for (i = 0; i < depth;i++) {
        for (j = 0; j < width; j++) {
            v.x = (float(i) / (width - 1) * 2.0f - 1.0);
            if (i > depth / 2 )
                v.y = inc;
            else
                v.y = 0;

            v.z = (float(j) / (depth - 1) * 2.0f - 1.0);
            this->vertices.push_back(v);
            printf("\n( %lf, %lf)\n",v.x,v.z);
        }
        if (i > depth/2)
            inc++;
    }
    printf("\nNúmero de vertices %d\n",vertices.size());

    for (i = 0; i < depth - 1;i++) {
        for (j = 0; j < width - 1;j++) {
            aux[0] = (i * depth) + j;
            aux[1] = aux[0] + 1;
            aux[2] = ((i + 1) * depth) + j;
            aux[3] = aux[2] + 1;

            //printf("\n%d/%d/%d/%d\n", aux[0],aux[1],aux[2],aux[3]);
            //system("pause");


            //Primer triangulo
            f.v1 = aux[0];
            f.v2 = aux[2];
            f.v3 = aux[1];

            this->caras.push_back(f);

            //Segundo triangulo

            f.v1 = aux[1];
            f.v2 = aux[2];
            f.v3 = aux[3];

            this->caras.push_back(f);
        }
    }
    
    //printf("\nNúmero de caras %d\n", caras.size());
}
void Terrain::solidDraw(GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLfloat shininess)
{
    double u[3],v[3];
    GLfloat cruz[3];

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    glBegin(GL_TRIANGLES);
    //Dibujamos las caras
    for (int i = 0; i < caras.size(); i++)
    {
        //Almacenamos el valor de los vertices recorriendo cara por cara
        vertex v1 = vertices[caras[i].v1];
        vertex v2 = vertices[caras[i].v2];
        vertex v3 = vertices[caras[i].v3];

   /*     printf("v1= ( %.5lf, %.5lf, %.5lf )\n", v1.x, v1.y,v1.z);
        printf("v2= ( %.5lf, %.5lf, %.5lf )\n", v2.x, v2.y, v2.z);
        printf("v3= ( %.5lf, %.5lf, %.5lf )\n", v3.x, v3.y, v3.z);*/

        u[0] = v2.x - v1.x;
        u[1] = v2.y - v1.y;
        u[2] = v2.z - v1.z;

        v[0] = v3.x - v1.x;
        v[1] = v3.y - v1.y;
        v[2] = v3.z - v1.z;

        //printf("u= ( %.lf, %.lf, %.lf )\n", u[0], u[1], u[2]);
        //printf("v= ( %.lf, %.lf, %.lf )\n\n", v[0], v[1], v[2]);

        cruz[0] = -(u[1] * v[2]) + (u[2]*v[1]);
        cruz[1]= -(u[2] * v[0]) + (u[0] * v[2]);
        cruz[2]= -(u[0] * v[1]) + (u[1] * v[0]);

        //printf("Normal= ( %.lf, %.lf, %.lf )\n",cruz[0], cruz[1], cruz[2]);
        //system("pause");
        
        glNormal3f(cruz[0],cruz[1],cruz[2]);
        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);

    }
    glEnd();
}
void Terrain::wireDraw()
{
    glBegin(GL_LINES);
    //Dibujamos las caras
    for (int i = 0; i < caras.size(); i++)
    {
        //Almacenamos el valor de los vertices recorriendo cara por cara
        vertex v1 = vertices[caras[i].v1];
        vertex v2 = vertices[caras[i].v2];
        vertex v3 = vertices[caras[i].v3];



        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);

        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);

        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v3.x, v3.y, v3.z);
    }
    glEnd();
}
GLfloat Terrain::getHeight(GLfloat x, GLfloat z) {
    for (int i = 0; i < depth;i++) {
        for (int j = 0; j < width; j++) {

        }
    }
    return 0;
}
