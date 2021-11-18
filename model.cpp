#include "model.h"

/*NOTA:Por el momento, el cargador de modelos solo cuenta con las siguientes características.

-Carga modelos de manera correcta siempre y cuando esten formados por primitivas triangulos.

-A pesar que puede leer y almacenar las coordenadas de textura, no se implemento su reconocimiento en las
caras ni su carga en memoria y por consiguiente en el modelo.

-Se pueden implementar modelos de luz y material sin problemas ya que si se tomaron en cuenta las normales indicadas
en cada cara

*/

bool obj3dmodel::readfile(const char* filename)
{   
    char linea[55];

    //Aqui leemos el archivo OBJ
    FILE* obj = fopen(filename, "r");
    if (obj == NULL) {
        printf("\nImpossible to open the file %s\n",filename);
        return false;
    }
    
    char *auxv;
    //Leemos linea a linea
    while (fgets(linea, sizeof(linea), obj)) {
        switch (linea[0])
        {
        case 'V':
        case 'v':
            //Si nuestra linea es Vt (coordenada de textura)
            if (linea[1]=='t') {
                text t;
                //strtok(); le el buffer de entrada del fichero hasta que el caracter concuerda con el proporcionado
                auxv = strtok(linea, " "); //Descartamos el primer espacio que es en donde comienzan los valores númericos
                //Obtenemos los valores posteriores separados por un espacio
                auxv = strtok(NULL, " "); t.u = atof(auxv);
                auxv = strtok(NULL, " "); t.v = atof(auxv);
                //Añadimos el valor leido a nuestro arreglo de vertices
                this->textura.push_back(t);
                break;
            }
            //Si nuestra linea es Vn (Normal)
            else if (linea[1]=='n') {
                vertex v;
                //strtok(); le el buffer de entrada del fichero hasta que el caracter concuerda con el proporcionado
                auxv = strtok(linea, " "); //Descartamos el primer espacio que es en donde comienzan los valores númericos
                //Obtenemos los valores posteriores separados por un espacio
                auxv = strtok(NULL, " "); v.x = atof(auxv);
                auxv = strtok(NULL, " "); v.y = atof(auxv);
                auxv = strtok(NULL, " "); v.z = atof(auxv);
                //Añadimos el valor leido a nuestro arreglo de vertices
                this->normales.push_back(v);
                break;
            }
            //Si nuestra linea es un simple vertice
            else {
                vertex v;
                //strtok(); le el buffer de entrada del fichero hasta que el caracter concuerda con el proporcionado
                auxv = strtok(linea, " "); //Descartamos el primer espacio que es en donde comienzan los valores númericos
                //Obtenemos los valores posteriores separados por un espacio
                auxv = strtok(NULL, " "); v.x = atof(auxv);
                auxv = strtok(NULL, " "); v.y = atof(auxv);
                auxv = strtok(NULL, " "); v.z = atof(auxv);
                //Añadimos el valor leido a nuestro arreglo de vertices
                this->vertices.push_back(v);
            }
            break;
        case 'F':
        case 'f':
            //Si nuestra linea es una cara (Face)
            face f;
            auxv = strtok(linea, " "); //Descartamos el primer espacio que es en donde comienzan los valores númericos
            //Obtenemos los valores posteriores separados por un espacio
            auxv = strtok(NULL, "/"); f.v1 = atoi(auxv);
            auxv = strtok(NULL, "/");
            auxv = strtok(NULL, " "); f.n1 = atoi(auxv);
            auxv = strtok(NULL, "/"); f.v2 = atoi(auxv);
            auxv = strtok(NULL, "/");
            auxv = strtok(NULL, " "); f.n2 = atoi(auxv);
            auxv = strtok(NULL, "/"); f.v3 = atoi(auxv);
            auxv = strtok(NULL, "/");
            auxv = strtok(NULL, " "); f.n3 = atoi(auxv);
            //Añadimos el valor leido a nuestro arreglo de caras
            this->caras.push_back(f);

            break;
        default:
            break;
        }
    }

    //Aqui leemos el archivo MTL
    char* mtlname = (char*)malloc(strlen(filename) * sizeof(char));
    strcpy(mtlname, filename);
    mtlname[strlen(mtlname) - 3] = NULL;
    strcat(mtlname, "mtl");


    FILE* mtl = fopen(mtlname, "r");
    if (mtl == NULL) {
        printf("\nImpossible to open the file %s\n", mtlname);
        return false;
    }

    while (fgets(linea, sizeof(linea), mtl)) {
        printf("\n%s\n", linea);
    }

    fclose(mtl);
    fclose(obj);
}

void obj3dmodel::solidDraw(GLfloat *ambient, GLfloat* diffuse, GLfloat* specular, GLfloat shininess)
{
    
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    glBegin(GL_TRIANGLES);
    //Dibujamos las caras
    for (int i = 0; i < caras.size(); i++)
    {
        //Almacenamos el valor de los vertices recorriendo cara por cara
        vertex v1 = vertices[caras[i].v1 - 1];
        vertex v2 = vertices[caras[i].v2 - 1];
        vertex v3 = vertices[caras[i].v3 - 1];

        //Almacenamos el valor de las normales recorriendo cara por cara
        vertex a1 = normales[caras[i].n1 - 1];
        vertex a2 = normales[caras[i].n2 - 1];
        vertex a3 = normales[caras[i].n3 - 1];
        //"indexamos" nuestros valores, simplemente es una forma sencilla de utilizar GLfloat
        GLfloat n1[3] = {a1.x,a1.y,a1.z};
        GLfloat n2[3]={ a2.x,a2.y,a2.z };
        GLfloat n3[3]= { a3.x,a3.y,a3.z };
        
        //Dibujamos con todo y normales
        glNormal3fv(n1);
        glVertex3f(v1.x, v1.y, v1.z);
        glNormal3fv(n2);
        glVertex3f(v2.x, v2.y, v2.z);
        glNormal3fv(n3);
        glVertex3f(v3.x, v3.y, v3.z);
    }
    glEnd();
}

void obj3dmodel::wireDraw()
{
    glBegin(GL_LINES);
    //Dibujamos las caras
    for (int i = 0; i < caras.size(); i++)
    {
        //Almacenamos el valor de los vertices recorriendo cara por cara
        vertex v1 = vertices[caras[i].v1 - 1];
        vertex v2 = vertices[caras[i].v2 - 1];
        vertex v3 = vertices[caras[i].v3 - 1];

        glVertex3f(v1.x, v1.y, v1.z);
        glVertex3f(v2.x, v2.y, v2.z);

        glVertex3f(v2.x, v2.y, v2.z);
        glVertex3f(v3.x, v3.y, v3.z);
    }
    glEnd();
}